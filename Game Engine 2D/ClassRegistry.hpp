#ifndef _CLASS_REGISTRY_HPP_
#define _CLASS_REGISTRY_HPP_

#include "stdafx.h"
#include <functional>
class EntityManager;

//This class doesn't care to know how a World and GameObject are made, it just need to know that they exist.
//This allows not recursive definitions
class World;
class GameObject;

typedef std::map<std::string, std::function<GameObject* (World&)>> EntitiesRegistry;

namespace Registry
{
	template<typename TYPE>
	class RegistryEntry
	{
	public:
		static RegistryEntry<TYPE>& Instance(const std::string& name, World& world)
		{
			// Because I use a singleton here, even though `COMPONENT_REGISTER`
			// is expanded in multiple translation units, the constructor
			// will only be executed once. Only this cheap `Instance` function
			// (which most likely gets inlined) is executed multiple times.

			static RegistryEntry<TYPE> inst(name, world);
			return inst;
		}

	private:
		RegistryEntry(const std::string& name, World& world)
		{
			if (GetGameObjectsRegistry().find(name) == GetGameObjectsRegistry().end())
			{
				GetGameObjectsRegistry().insert(std::make_pair(name, std::bind(&EntityManager::Instantiate<TYPE>, std::ref(world)))); //std::ref is crucial since without we're passing a copy of world, which will be destroyed (with destructor) right after the std::bind ends. For better info check this out  http://stackoverflow.com/questions/19859288/why-will-stdfunction-call-destructor-when-an-object-was-bound-to-a-member-func
#ifdef LOG_OUTPUT_CONSOLE
				std::string methodName = _FUNCION_NAME_;
				std::ostringstream oss;
				oss << typeid(TYPE).name() << " added with string \"" << name << "\"";
				Utils::PrintDebugLog(methodName, oss.str());
#endif
			}
			else
			{
				std::string methodName = _FUNCION_NAME_;
				std::ostringstream oss;
				oss << "string= " << name << " for " << typeid(TYPE).name() << " already used. Use a different string!!";
				Utils::PrintDebugLog(methodName, oss.str());
				throw 1;
			}
		}

		RegistryEntry(const RegistryEntry<TYPE>&) = delete;
		RegistryEntry& operator=(const RegistryEntry<TYPE>&) = delete;
	};

	//Making reg static would make possible for the private constructor of RegistryEntry to reference reg when it's still not initialized
	//because static initialization can't be controlled. In this way I force the instantiation when I use it the first time.
	EntitiesRegistry& GetGameObjectsRegistry();
}

#define GAMEOBJECT_REGISTER(TYPE, NAME, WORLD)			\
namespace												\
{														\
	template<typename T>								\
	class GameObjectRegistration;						\
														\
	template<>											\
	class GameObjectRegistration<TYPE>					\
	{													\
	private:											\
		static const RegistryEntry<TYPE>& reg;			\
	};													\
														\
	const RegistryEntry<TYPE>&							\
	GameObjectRegistration<TYPE>::reg =					\
	RegistryEntry<TYPE>::Instance(NAME, WORLD);			\
}

/************* THEORY *********
Nameless templates (Anonymous Namespace) allow same named variable in multiple cpp. In our example, without an anonymous namespace
the definition of reg would appear multiple times in the same namespace which is clearly not allowed.

*/
#endif