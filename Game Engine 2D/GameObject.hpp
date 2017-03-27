#ifndef _GAMEOBJECT_HPP_
#define _GAMEOBJECT_HPP_

#include "stdafx.h"

//Static classes can't have virtual or abstract methods, so I can't make this class static, hence read below!!
//Classes that inherit from GameObjects are not supposed to be instantiated by new!
//All you need to do override Init(...) to "define" your gameobject, which in turn is defining what componets to add
//to the parameter of the Init



class GameObject
{
public:
	GameObject();

	unsigned long int Instantiate(World* world); //world is a pointer here cause otherwise I'd have had to define the constructor in all subclasses of gameobject. because a reference can never be null at any time while a pointer can.

protected:
	virtual void Init() = 0; //add all the components that define the entity, like a prefab in Unity
	unsigned long int GetEntityIndex() const;
	World& GetWorld() const;

private:
	unsigned long int entityIndex;
	World* world;

	/*void static RegisterClassForReflection();

	void AddClassForReflection(World& world);*/

};

#endif