#pragma once

#include <OpsCore.h>

class SpyAnimationState : public oc::AnimationState {
	
public:
	// Inherited via AnimationState
	virtual void enter(oc::GameObject*)=0;
	virtual void update(oc::Timestep ts, oc::GameObject*)=0;

	virtual SpyAnimationState* MoveRight(oc::GameObject* player)=0;
	virtual SpyAnimationState* MoveLeft(oc::GameObject* player)=0;
	virtual SpyAnimationState* Sheathe(oc::GameObject* player)=0;
	virtual SpyAnimationState* Shoot(oc::GameObject* player)=0;
	virtual SpyAnimationState* Idle(oc::GameObject* player)=0;


private:


};

class IdleState : public SpyAnimationState {

public:

	IdleState()
		: _boredTime(0)
	{}

	// Inherited via AnimationState
	virtual void enter(oc::GameObject* spy) override;

	virtual void update(oc::Timestep ts, oc::GameObject* spy) override {}

	virtual SpyAnimationState* MoveRight(oc::GameObject* player) override;
	virtual SpyAnimationState* MoveLeft(oc::GameObject* player) override;
	virtual SpyAnimationState* Sheathe(oc::GameObject* player) override;
	virtual SpyAnimationState* Shoot(oc::GameObject* player) override;
	virtual SpyAnimationState* Idle(oc::GameObject* player) override;



private:
	oc::Timestep _boredTime;

};

class IdleGunState : public SpyAnimationState {

public:

	IdleGunState()
		: _boredTime(0)
	{}

	// Inherited via AnimationState
	virtual void enter(oc::GameObject* spy) override;

	virtual void update(oc::Timestep ts, oc::GameObject* spy) override {}

	virtual SpyAnimationState* MoveRight(oc::GameObject* player) override;
	virtual SpyAnimationState* MoveLeft(oc::GameObject* player) override;
	virtual SpyAnimationState* Sheathe(oc::GameObject* player) override;
	virtual SpyAnimationState* Shoot(oc::GameObject* player) override;
	virtual SpyAnimationState* Idle(oc::GameObject* player) override;



private:
	oc::Timestep _boredTime;

};

class MoveState : public SpyAnimationState {

	// Inherited via SpyAnimationState
	virtual void enter(oc::GameObject*) override;
	virtual void update(oc::Timestep ts, oc::GameObject*) override;
	virtual SpyAnimationState* MoveRight(oc::GameObject* player) override;
	virtual SpyAnimationState* MoveLeft(oc::GameObject* player) override;
	virtual SpyAnimationState* Sheathe(oc::GameObject* player) override;
	virtual SpyAnimationState* Shoot(oc::GameObject* player) override;
	virtual SpyAnimationState* Idle(oc::GameObject* player) override;

};

class SheatheState : public SpyAnimationState {

	// Inherited via SpyAnimationState
	virtual void enter(oc::GameObject*) override;
	virtual void update(oc::Timestep ts, oc::GameObject*) override;
	virtual SpyAnimationState* MoveRight(oc::GameObject* player) override;
	virtual SpyAnimationState* MoveLeft(oc::GameObject* player) override;
	virtual SpyAnimationState* Sheathe(oc::GameObject* player) override;
	virtual SpyAnimationState* Shoot(oc::GameObject* player) override;
	virtual SpyAnimationState* Idle(oc::GameObject* player) override;

};

class ShootState : public SpyAnimationState {

	// Inherited via SpyAnimationState
	virtual void enter(oc::GameObject*) override;
	virtual void update(oc::Timestep ts, oc::GameObject*) override;
	virtual SpyAnimationState* MoveRight(oc::GameObject* player) override;
	virtual SpyAnimationState* MoveLeft(oc::GameObject* player) override;
	virtual SpyAnimationState* Sheathe(oc::GameObject* player) override;
	virtual SpyAnimationState* Shoot(oc::GameObject* player) override;
	virtual SpyAnimationState* Idle(oc::GameObject* player) override;

};

class MoveGunState : public SpyAnimationState {

	// Inherited via SpyAnimationState
	virtual void enter(oc::GameObject*) override;
	virtual void update(oc::Timestep ts, oc::GameObject*) override;
	virtual SpyAnimationState* MoveRight(oc::GameObject* player) override;
	virtual SpyAnimationState* MoveLeft(oc::GameObject* player) override;
	virtual SpyAnimationState* Sheathe(oc::GameObject* player) override;
	virtual SpyAnimationState* Shoot(oc::GameObject* player) override;
	virtual SpyAnimationState* Idle(oc::GameObject* player) override;

};