//
//  Appearance.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 22/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _APPEARANCE_HPP_
#define _APPEARANCE_HPP_

#include "stdafx.h"
#include "Component.hpp"

class Appearance : public Component<Appearance>
{
public:
    Appearance(World& world, const unsigned long int entityIndex, std::string spritePath);
    ~Appearance() override;
    
    //TODO maybe make them private and make them setable only from constructor?
    std::string SpritePath;
    
    sf::Sprite* const GetSprite() const; //returns null if not loaded
    void SetSprite(sf::Sprite* const sprite);
    bool IsTextureLoaded() const;
    
private:
    sf::Sprite* sprite;
    sf::Texture* texture;
    
};

#endif /* _APPEARANCE_HPP_ */
