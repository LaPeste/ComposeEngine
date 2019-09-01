#ifndef _BT_ENGINE_HPP_
#define _BT_ENGINE_HPP_

#include "stdafx.h"
#include "Systems/System.hpp"
#include "AI/BehaviourTree.hpp"

namespace BT
{
	/*!
	 * Behaviour Tree Engine
	 */
	class BTEngine : public System<BehaviourTree>
	{
	public:
		BTEngine(World& world);

	private:
		void Update(World& world, const unsigned long int entityIndex) override;
	};
}


#endif //_BT_ENGINE_HPP_