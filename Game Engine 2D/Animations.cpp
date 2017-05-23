#include "Animations.hpp"

#include "Animation.hpp"
#include "Controller.hpp"

//in this class I could avoid to use controller rasing an event when the entity touches the ground. I'll see if I'll have the will of doing this.

//FMS(sort of) for animation, basically listening for events will trigger changes in AnimationState
void Animations::BasicInputAnimation(World& world, unsigned long int entityIndex, const InputEvent& event)
{
	std::map<unsigned long int, ComponentBase*>& entity = world.EntitiesComponentsMatrix[entityIndex];
	Animation* animation = static_cast<Animation*>(entity[Animation::Id]);
	Controller* controller = static_cast<Controller*>(entity[Controller::Id]);
	InputEventType e = event.GetContent();

	if (e == InputEventType::RIGHT_DOWN)
	{
		if (!controller->IsJumping())
		{
			animation->CurrentAnimationState = AnimationState::WALKING;
		}
		animation->FlipAnimation = false;
	}
	else if (e == InputEventType::LEFT_DOWN)
	{
		if (!controller->IsJumping())
		{
			animation->CurrentAnimationState = AnimationState::WALKING;
		}
		animation->FlipAnimation = true;
	}
	else if (e == InputEventType::LEFT_UP)
	{
		if (!controller->IsJumping())
		{
			animation->CurrentAnimationState = AnimationState::IDLE;
		}
	}
	else if (e == InputEventType::RIGHT_UP)
	{
		if (!controller->IsJumping())
		{
			animation->CurrentAnimationState = AnimationState::IDLE;
		}
	}
	else if (e == InputEventType::JUMP_START)
	{
		animation->CurrentAnimationState = AnimationState::JUMPING;
	}
	else if (e == InputEventType::FREE_FALLING_STOP)
	{
		if (!controller->GetMoveRight() && !controller->GetMoveLeft())
		{
			animation->CurrentAnimationState = AnimationState::IDLE;
		}
		else
		{
			animation->CurrentAnimationState = AnimationState::WALKING;
		}
	}
	else if (e == InputEventType::FREE_FALLING_START)
	{
		animation->CurrentAnimationState = AnimationState::IDLE;
	}
}