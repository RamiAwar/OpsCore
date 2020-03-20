
#include "SpyStates.h"
#include "Components/PlayerController.h"
#include "Components/PlayerAnimationController.h"
#include "Player.h"

void IdleState::enter(oc::GameObject* spy) {
	std::dynamic_pointer_cast<PlayerAnimationController>(spy->GetComponent("PlayerAnimationController"))->SetAnimation("idle");
}

SpyAnimationState* IdleState::MoveRight(oc::GameObject* player) {
	//std::dynamic_pointer_cast<PlayerController>(player->GetComponent("PlayerController"))->_FlipDirection();
	return new MoveState();
}

SpyAnimationState* IdleState::MoveLeft(oc::GameObject* player)
{
	//std::dynamic_pointer_cast<PlayerController>(player->GetComponent("PlayerController"))->_FlipDirection();
	return new MoveState();
}

SpyAnimationState* IdleState::Sheathe(oc::GameObject* player)
{
	return nullptr;
}

SpyAnimationState* IdleState::Shoot(oc::GameObject* player)
{
	return nullptr;
}

SpyAnimationState* IdleState::Idle(oc::GameObject* player)
{
	return nullptr;
}

// -------------- IDLE GUN ----------------

void IdleGunState::enter(oc::GameObject* spy) {
	std::dynamic_pointer_cast<PlayerAnimationController>(spy->GetComponent("PlayerAnimationController"))->SetAnimation("idlegun");
}

SpyAnimationState* IdleGunState::MoveRight(oc::GameObject* player) {
	//std::dynamic_pointer_cast<PlayerController>(player->GetComponent("PlayerController"))->_FlipDirection();
	return new MoveState();
}

SpyAnimationState* IdleGunState::MoveLeft(oc::GameObject* player)
{
	//std::dynamic_pointer_cast<PlayerController>(player->GetComponent("PlayerController"))->_FlipDirection();
	return new MoveState();
}

SpyAnimationState* IdleGunState::Sheathe(oc::GameObject* player)
{
	return nullptr;
}

SpyAnimationState* IdleGunState::Shoot(oc::GameObject* player)
{
	return nullptr;
}

SpyAnimationState* IdleGunState::Idle(oc::GameObject* player)
{
	return nullptr;
}


// ------------- MOVE STATE ---------------
void MoveState::enter(oc::GameObject* spy) {
	std::dynamic_pointer_cast<PlayerAnimationController>(spy->GetComponent("PlayerAnimationController"))->SetAnimation("run");
}

void MoveState::update(oc::Timestep ts, oc::GameObject* player){}

SpyAnimationState* MoveState::MoveRight(oc::GameObject* player)
{
	return nullptr;
}

SpyAnimationState* MoveState::MoveLeft(oc::GameObject* player)
{
	return nullptr;
}

SpyAnimationState* MoveState::Sheathe(oc::GameObject* player)
{
	return new SheatheState();
}

SpyAnimationState* MoveState::Shoot(oc::GameObject* player)
{
	return new ShootState();
}

SpyAnimationState* MoveState::Idle(oc::GameObject* player)
{
	return new IdleState();
}



// ------------- MOVE GUN STATE ---------------
void MoveGunState::enter(oc::GameObject* spy) {
	std::dynamic_pointer_cast<PlayerAnimationController>(spy->GetComponent("PlayerAnimationController"))->SetAnimation("rungun");
}

void MoveGunState::update(oc::Timestep ts, oc::GameObject* player) {}

SpyAnimationState* MoveGunState::MoveRight(oc::GameObject* player)
{
	return new MoveGunState();
}

SpyAnimationState* MoveGunState::MoveLeft(oc::GameObject* player)
{
	return new MoveGunState();
}

SpyAnimationState* MoveGunState::Sheathe(oc::GameObject* player)
{
	return new SheatheState();
}

SpyAnimationState* MoveGunState::Shoot(oc::GameObject* player)
{
	return new ShootState();
}

SpyAnimationState* MoveGunState::Idle(oc::GameObject* player)
{
	return new IdleGunState();
}


// ------------- SHEATHE STATE ---------------
void SheatheState::enter(oc::GameObject* spy)
{
	if (dynamic_cast<Player*>(spy)->m_Sheathed) {
		std::dynamic_pointer_cast<PlayerAnimationController>(spy->GetComponent("PlayerAnimationController"))->SetAnimation("sheathe");
	}
	else {
		std::dynamic_pointer_cast<PlayerAnimationController>(spy->GetComponent("PlayerAnimationController"))->SetAnimation("unsheathe");
	}
}

void SheatheState::update(oc::Timestep ts, oc::GameObject* player)
{
}

SpyAnimationState* SheatheState::MoveRight(oc::GameObject* player)
{
	// Moves to MoveGun state but only after a certain delay processed in update function
	return nullptr;
}

SpyAnimationState* SheatheState::MoveLeft(oc::GameObject* player)
{
	return nullptr;
}

SpyAnimationState* SheatheState::Sheathe(oc::GameObject* player)
{
	return nullptr;
}

SpyAnimationState* SheatheState::Shoot(oc::GameObject* player)
{
	return nullptr;
}

SpyAnimationState* SheatheState::Idle(oc::GameObject* player)
{
	return new IdleState();
}


// ------------- SHOOT STATE ---------------
void ShootState::enter(oc::GameObject* spy)
{
	std::dynamic_pointer_cast<PlayerAnimationController>(spy->GetComponent("PlayerAnimationController"))->SetAnimation("run");
}

void ShootState::update(oc::Timestep ts, oc::GameObject* player)
{
}

SpyAnimationState* ShootState::MoveRight(oc::GameObject* player)
{
	return nullptr;
}

SpyAnimationState* ShootState::MoveLeft(oc::GameObject* player)
{
	return nullptr;
}

SpyAnimationState* ShootState::Sheathe(oc::GameObject* player)
{
	return nullptr;
}

SpyAnimationState* ShootState::Shoot(oc::GameObject* player)
{
	return nullptr;
}


SpyAnimationState* ShootState::Idle(oc::GameObject* player)
{
	return new IdleState();
}
