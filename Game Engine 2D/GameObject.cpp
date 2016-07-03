#include "GameObject.hpp"
#include "Engine.hpp"
#include "FPS.hpp"
#include "GameObjectManager.hpp"
#include "Camera.hpp"
#include <tmx/MapLoader.h>

using namespace tmx;
using namespace sf;

inline GameObjectFlags operator|(GameObjectFlags a, GameObjectFlags b)
{return static_cast<GameObjectFlags>(static_cast<int>(a) | static_cast<int>(b));}

inline GameObjectFlags operator&(GameObjectFlags a, GameObjectFlags b)
{return static_cast<GameObjectFlags>(static_cast<int>(a) & static_cast<int>(b));}

GameObject::GameObject(bool toAnimate, int spriteMaxFrame, int animationFrameRate, bool reverseAnimation,
                       float startingPosX, float startingPosY,
                       float maxSpeedX, float maxSpeedY,
                       float customAccelerationX, float customAccelerationY,
                       float offsetColX, float offsetColY,
                       GameObjectFlags flags,
                       std::string name,
                       const GameObjectType& type) :
    isLoaded (false),
    MoveLeft(false), MoveRight(false), canJump(false),
    toAnimate(toAnimate),
    dead(false),
    animator(spriteMaxFrame, animationFrameRate, reverseAnimation),
    accelerationX(0), accelerationY(0),
    speedX(0), speedY(0),
    maxSpeedX(maxSpeedX), maxSpeedY(maxSpeedY),
    customAccelerationX(customAccelerationX), customAccelerationY(customAccelerationY),
    offsetColX(offsetColX), offsetColY(offsetColY),
    Flags(flags),
    mapObject(nullptr),
    name(name),
    gameObjectType(type)
{
    collisionPoints[0] = Vector2f{0, 0};
    collisionPoints[1] = Vector2f{sprite.getLocalBounds().width, 0};
    collisionPoints[2] = Vector2f{0, sprite.getLocalBounds().height};
    collisionPoints[3] = Vector2f{sprite.getLocalBounds().width, sprite.getLocalBounds().height};
    id = GameObjectManager::GetUniqueID();
}

GameObject::GameObject(tmx::MapObject* mapObject,
                       bool toAnimate, int spriteMaxFrame, int animationFrameRate, bool reverseAnimation,
                       float offsetColX, float offsetColY,
                       GameObjectFlags flags) :
    MoveLeft(false), MoveRight(false),
    toAnimate(toAnimate),
    dead(false),
    animator(spriteMaxFrame, animationFrameRate, reverseAnimation),
    accelerationX(0), accelerationY(0),
    speedX(0), speedY(0),
    maxSpeedX(0), maxSpeedY(0),
    customAccelerationX(0), customAccelerationY(0),
    offsetColX(offsetColX), offsetColY(offsetColY),
    Flags(flags),
    mapObject(mapObject)
{
    if(mapObject == nullptr)
    {
        Utils::PrintDebugError("GameObject()", "The MapObject supplied was null!");
        std::abort();
    }
    
    isLoaded = true;
    name = mapObject->GetName();
    id = GameObjectManager::GetUniqueID();
    gameObjectType = GameObjectType::MapCollisionObject;
    mapObject->SetProperty(GameObjectManager::TmxIdStringField, std::to_string(id));
}

GameObject::GameObject(tmx::MapObject* mapObject,
                       float offsetColX, float offsetColY,
                       GameObjectFlags flags) :
    MoveLeft(false), MoveRight(false),
    toAnimate(false),
    dead(false),
    animator(0, 0, 0),
    accelerationX(0), accelerationY(0),
    speedX(0), speedY(0),
    maxSpeedX(0), maxSpeedY(0),
    customAccelerationX(0), customAccelerationY(0),
    offsetColX(offsetColX), offsetColY(offsetColY),
    Flags(flags),
    mapObject(mapObject)
{
    if(mapObject == nullptr)
    {
        Utils::PrintDebugError("GameObject()", "The MapObject supplied was null!");
        std::abort();
    }
    
    isLoaded = true;
    name = mapObject->GetName();
    id = GameObjectManager::GetUniqueID();
    gameObjectType = GameObjectType::MapCollisionObject;
    mapObject->SetProperty(GameObjectManager::TmxIdStringField, std::to_string(id));
}

GameObject::~GameObject()
{

}

void GameObject::Load(const std::string& filename)
{
	if (texture.loadFromFile(filename) == false)
	{
		isLoaded = false;
	}
	else
	{
		GameObject::filename = filename;
		sprite.setTexture(texture);
		isLoaded = true;
	}
}

///Loads only a part of the texture
void GameObject::Load(const std::string& filename, int startingLeft, int startingTop, int width, int height)
{
	if (texture.loadFromFile(filename) == false)
	{
//		filename = "";
		isLoaded = false;
	}
	else
	{
		GameObject::filename = filename;
        sprite.setTexture(texture);
//		sf::Rect<int> subTextureRect(startingLeft, startingTop, width, height);
//		sprite.setTextureRect(subTextureRect);
        SetSubTexture(startingLeft, startingTop, width, height);
        
        if(sprite.getTexture() != nullptr)
        {
            isLoaded = true;
#ifdef DEBUG
            Utils::PrintDebugLog("GameObject::Load", "texture correctly loaded!");
#endif
        }
        else
        {
            isLoaded = false;
#ifdef DEBUG
            Utils::PrintDebugError("GameObject::Load", "texture not correctly loaded!");
#endif

        }
    }
}

void GameObject::Draw(sf::RenderWindow& window)
{
	if (isLoaded)
	{
        if(toAnimate) animator.Animate(sprite);
        
        window.draw(sprite);
	}
}

void GameObject::SetSubTexture(int startingLeft, int startingTop, int width, int height)
{
    sf::Rect<int> subTextureRect(startingLeft, startingTop, width, height);
    sprite.setTextureRect(subTextureRect);
}

void GameObject::Update()
{
    if(!MoveLeft && !MoveRight)
    {
        StopMove();
    }
    
    if(MoveLeft)
    {
        accelerationX = -customAccelerationX;
    }
    else if(MoveRight)
    {
        accelerationX = customAccelerationX;
    }
    
    if((Flags & GameObjectFlags::GRAVITY) == GameObjectFlags::GRAVITY) //TODO fix gravity! Create a floor below which the player won't go
    {
        accelerationY = Constants::IN_GAME_GRAVITY;
    }
    
    speedX += accelerationX * FPS::GetSpeedFactor();
    speedY += accelerationY * FPS::GetSpeedFactor();
    
    if(speedX > maxSpeedX) speedX = maxSpeedX;
    if(speedX < -maxSpeedX) speedX = -maxSpeedX;
    if(speedY > maxSpeedY) speedY = maxSpeedY;
    if(speedY < -maxSpeedY) speedY = -maxSpeedY;
    
    Animate();
    MoveTo(speedX, speedY);
    
    //UpdatePosition();
}

void GameObject::Cleanup()
{

}

bool GameObject::IsLoaded() const
{
	if (isLoaded) return true;

	return false;
}

void GameObject::UpdatePosition()
{
    
    
    //OLD, without accelaration and speed concepts
    //    if(MoveLeft)
    //    {
    //        if(toAnimate)
    //        {
    //            animator.FlipSprite(true);
    //            animator.AnimateSprite(true);
    //        }
    //        if((GetPosition().x - Constants::PLAYER_STEP_SIZE) >= 0)
    //        {
    //            sf::Vector2<float> pos = GetPosition();
    //            SetPosition(pos.x - Constants::PLAYER_STEP_SIZE * FPS::GetSpeedFactor(), pos.y);
    ////            posX -= Constants::PLAYER_STEP_SIZE * FPS::GetSpeedFactor();
    //        }
    //    }
    //    else if(MoveRight)
    //    {
    //        if(toAnimate)
    //        {
    //            animator.FlipSprite(false);
    //            animator.AnimateSprite(true);
    //        }
    //        if((GetPosition().x + Constants::PLAYER_STEP_SIZE + Constants::PLAYER_WIDTH) <= Constants::SCREEN_WIDTH)
    //        {
    //            sf::Vector2<float> pos = GetPosition();
    //            SetPosition(pos.x + Constants::PLAYER_STEP_SIZE * FPS::GetSpeedFactor(), pos.y);
    ////            posX += Constants::PLAYER_STEP_SIZE * FPS::GetSpeedFactor();
    //        }
    //    }
    //    else if(Jump)
    //    {
    //        //TODO
    //    }
    //    else if(Crouch)
    //    {
    //        //TODO
    //    }
    //    else
    //    {
    //        animator.AnimateSprite(false);
    //    }
    
}

void GameObject::Animate()
{
    if(!toAnimate) return;
    
    if(MoveLeft)
    {
        animator.FlipSprite(true);
        animator.AnimateSprite(true);
    }
    else if(MoveRight)
    {
        animator.FlipSprite(false);
        animator.AnimateSprite(true);
    }
    else
    {
        animator.AnimateSprite(false);
    }
}

void GameObject::StopMove()
{
    if(speedX > 0) accelerationX = -2 * customAccelerationX;
    if(speedX < 0) accelerationX = 2 * customAccelerationX;
    
    if(speedX < 2.0f && speedX > -2.0f) {
        accelerationX = 0;
        speedX = 0;
    }
}

bool GameObject::Jump()
{
    if(!canJump) return false;
    
    speedY = -maxSpeedY;
    return true;
}

void GameObject::MoveTo(float x, float y)
{
    if(x > 2344){ //Debug TODO to remove!
        std::cout << "It's a big mess";
    }
    if(x == 0 && y == 0) return;
    
    double stepX = 0; // atomic step on x axis
    double stepY = 0; // atomic step on y axis
    
    x *= FPS::GetSpeedFactor();
    y *= FPS::GetSpeedFactor();
    
    if(x != 0)
    {
        if(x >= 0)
        {
            stepX = FPS::GetSpeedFactor();
        }
        else
        {
            stepX = -FPS::GetSpeedFactor();
        }
    }
    if(y != 0)
    {
        if(y >= 0)
        {
            stepY = FPS::GetSpeedFactor();
        }
        else
        {
            stepY = -FPS::GetSpeedFactor();
        }
    }
    
    while(true)
    {
        if((Flags & GameObjectFlags::GHOST) == GameObjectFlags::GHOST)
        {
            if(PosValid(GetPosition().x + stepX, GetPosition().y + stepY))
            {
                SetPosition(GetPosition().x + stepX, GetPosition().y + stepY);
            }
        }
        else
        {
            // movement on X axis
            if(PosValid(GetPosition().x + stepX, GetPosition().y))
            {
                SetPosition(GetPosition().x + stepX, GetPosition().y);
            }
            else
            {
                speedX = 0;
            }
            
            // movement on Y axis
            if(PosValid(GetPosition().x, GetPosition().y + stepY))
            {
                SetPosition(GetPosition().x, GetPosition().y + stepY);
            }
            else
            {
                speedY = 0;
            }
            canJump = speedY == 0;
        }
        
        x -= stepX;
        y -= stepY;
        
        if(stepX > 0 && x <= 0) stepX = 0; // if going to the right but reached/passed the x point
        if(stepX < 0 && x >= 0) stepX = 0; // if going to the left but reached/passed the x point
        if(stepY > 0 && y <= 0) stepY = 0; // same as above but for downward direction
        if(stepY < 0 && y >= 0) stepY = 0; // same as above but for upward direction
        if(x == 0) stepX = 0;
        if(y == 0) stepY = 0;
        if(x == 0 && y == 0) break;
        if(stepX == 0 && stepY == 0) break;
    }
    
}

bool GameObject::OnCollision(GameObject* otherEntity)
{
    Utils::PrintDebugLog("GameObject::OnCollision", name + " collided with " + otherEntity->GetName());
    return true; //for now
//    switch(/*collision type*/)
//    {
//        case /*enemy*/:
//            //die;
//            break;
//        case /*solid object*/:
//            //don't walk anymore;
//            break;
//    }
}

//bool GameObject::Collides(sf::Sprite sprite)
//{
//    return Collides(sprite.getPosition().x, sprite.getPosition().y, sprite.getLocalBounds().width, sprite.getLocalBounds().height);
//}

bool GameObject::Collides()//float originX, float originY, float width, float height)
{
    sf::FloatRect rootNode(Camera::GetInstance()->GetPosition().x, Camera::GetInstance()->GetPosition().y, Camera::GetInstance()->GetWidth(), Camera::GetInstance()->GetHeight());
    Engine::GetInstance().GetMapLoader().UpdateQuadTree(rootNode); //update quadtree's rootnode to what's visible in the screen
    std::vector<MapObject*> objects = Engine::GetInstance().GetMapLoader().QueryQuadTree(sprite.getGlobalBounds()); // grab all the MapObjects contained in the quads intersected by the bounds of sprite
    if(!Engine::GetInstance().GetMapLoader().QuadTreeAvailable())
    {
        Utils::PrintDebugError("Collides()", "No MapTree to query is available");
        return false;
    }
    bool collision = false;

    for(auto object = objects.begin(); object != objects.end(); ++object)
    {
        if((*object)->GetParent() == Constants::COLLISION_LAYER)
        {
            for(int i = 0; i < 4; i++) //where 4 is the amount of collisionPoints we have. Those are the 4 corners of the sprite of a gameObject.
            {
                collision = (*object)->Contains(GetPosition() + collisionPoints[i]);
                
                if(collision)
                {
                    break;
                }
            }
        }
        if(collision)
        {
//            std::cout << "addr " << ((void*)&(*object)) << " , property " << GameObjectManager::TmxIdStringField << ": " << (*object)->GetPropertyString(GameObjectManager::TmxIdStringField) << ", name: " << (*object)->GetName() << std::endl;
            if((*object)->GetPropertyString(GameObjectManager::TmxIdStringField) != "")
            {
                long searchId = std::stol((*object)->GetPropertyString(GameObjectManager::TmxIdStringField));
                GameObject* mapGameObject = GameObjectManager::GetGameObject(searchId);
                if(mapGameObject != nullptr && mapGameObject->GetGameObjectType() == GameObjectType::MapCollisionObject)
                {
                    CollisionEvent coll(this, mapGameObject);
                    GameObjectManager::collisionEvents.push_back(coll); //TODO try to get this list through its getter
                }
            }
            break;
        }
    }
    
//    solution I'm proud of but unnecessary because of the quadtree implemented by the tmx library :'(
    /*
     foreach(layer)
     | if(layer type is ObjectGroup)
     |  | foreach(object in such layer)
     |  |   | if(collision type of layer of interest "collision for example")
     |  |   |   | foreach(collision point of player)
     |  |   |   |   |if(player's collision point is content in current object)
     |  |   |   |   |   | then it collides!
     |  |   |   |   |   | break because you know it's a collision
     |  |   |   |
     |  |   | else if(collision type of trigger)
     |  |   |   | manage trigger stuff
     |  |   |   |
     |  |   | else if... all the rest of the type you need
     */
//    std::vector<MapLayer>& layers = Engine::GetInstance().GetMapLoader().GetLayers();
//    std::sort(objects.begin(), objects.end());
//    std::vector<MapObject*> intersection;
//    for(auto layer = layers.begin(); layer != layers.end(); ++layer)
//    {
//        if(layer->name == "Collision Objects")
//        {
//            std::vector<MapObject*> layerPointerObjects;
//            layerPointerObjects.resize(layer->objects.size());
//            intersection.resize(layer->objects.size());
//            std::transform(layer->objects.begin(), layer->objects.end(), layerPointerObjects.begin(), []( MapObject& a) -> MapObject* { return &a; });
//            std::sort(layerPointerObjects.begin(), layerPointerObjects.end(),
//                          [](const MapObject* const a, const MapObject* const b) -> bool
//                          {
//                              return (a <= b);
//                          });
//            std::set_intersection(objects.begin(), objects.end(), layerPointerObjects.begin(), layerPointerObjects.end(), intersection.begin(),
//                                  [](const MapObject* const a, const MapObject* const b) -> bool
//                                  {
//                                      return (a < b);
//                                  });
//            for(auto object = intersection.begin(); object != intersection.end(); ++object)
//            {
//                if(*object != nullptr)
//                {
//                    for(int i = 0; i < 4; i++) //where 4 is the amount of collisionPoints we have. Those are the 4 corners of the sprite of a gameObject.
//                    {
//                        collision = (*object)->Contains(GetPosition() + collisionPoints[i]);
//                        
//                        if(collision)
//                        {
//                            std::cout << "Collision!!!" << std::endl;
//                            break;
//                        }
//                    }
//                }
//            }
//            break;
//        }
//    }
//    
    return collision;
}
                          

bool GameObject::PosValid(float x, float y)
{
    Vector2f originalPosition = this->GetPosition();
    this->SetPosition(x, y);
    bool posValid = false;
    
    //prevent player from falling from map's limits
    if(GetPosition().x <= 0 || GetPosition().x + GetSprite().getLocalBounds().width >= Engine::GetInstance().GetMapLoader().GetMapSize().x)
    {
        this->SetPosition(originalPosition);
        posValid = false;
    }
    else
    {
        posValid = Collides() ? false : true;
    }
    this->SetPosition(originalPosition);
    return posValid;
}

//*************
//Getters and Setters
//*************

sf::Sprite GameObject::GetSprite() const
{
    return sprite;
}


const sf::Vector2f GameObject::GetPosition() const
{
    if (isLoaded)
    {
        return sprite.getPosition();
    }
    Utils::PrintDebugError("GameObject::GetPosition()", "the gameObject doesn't have a loaded sprite!");
    return sf::Vector2f();
}

void GameObject::SetPosition(float x, float y)
{
    if (isLoaded)
    {
        sprite.setPosition(x, y);
    }
}

void GameObject::SetPosition(sf::Vector2f position)
{
    SetPosition(position.x, position.y);
}
                                               
MapObject* GameObject::GetMapObject() const
{
    if(!IsMapObject())
    {
        Utils::PrintDebugError("GameObject::GetMapObject", "Queried for MapObject, but this GameObject is not a MapObject");
        std::abort(); //not sure I should abort like this but the error is pretty big, so I want the code to end
        
    }

    return mapObject;
}

long GameObject::GetID() const
{
    return id;
}

void GameObject::SetID(long id)
{
    if(GameObject::id == -1) //if the ID hasn't been set yet
    {
        GameObject::id = id;
    }
    else
    {
        Utils::PrintDebugError("GameObject::SetID", "Someone is trying to change the ID of the GameObject " + GameObject::name + "! This is not allowed!");
    }
}

std::string GameObject::GetName() const
{
    return name;
}

const GameObjectType& GameObject::GetGameObjectType() const
{
    return gameObjectType;
}

bool GameObject::IsMapObject() const
{
    return mapObject != nullptr;
}

const bool GameObject::IsDead() const
{
    return dead;
}

void GameObject::SetDeath(bool dead)
{
    GameObject::dead = dead;
}


/* 
 THEORY:
 STATIC CAST ==> is used for cases where you want to reverse an implicit conversion, with a few restrictions and additions. static_cast performs no runtime checks. This should be used if you know that you refer to an object of a specific type, and thus a check would be unnecessary.
 */
