#pragma once
#include <PumpkinBox.h>
#include "Command.h"

class PlayerController : public oc::Component
{
public:
	PlayerController(oc::GameObject* parent) : Component(parent) {}
	
	// Inherited via Component
	virtual void OnCreate() override {};
	virtual void OnDestroy() override {};
	virtual void OnEvent(oc::Event& e) override {};
	virtual void OnUpdate(oc::Timestep ts) override;
	virtual void OnLateUpdate(oc::Timestep ts) override {};
	virtual void Render() override {};

	// TODO: Queue this action for later execution during Update()
	void MoveRight(oc::Timestep ts);
	void MoveLeft(oc::Timestep ts);
	void Sheathe(oc::Timestep ts);
	void Shoot(oc::Timestep ts);

	inline void UpdatePosition(oc::Timestep ts) {
		//if (m_MovementDelay >= MOVEMENT_DELAY) {
			m_ParentGameObject->GetTransform()->position.x += ts * m_PlayerHorizontalSpeed;
		//}
		//m_MovementDelay += ts;
	}

	void _SetHorizontalSpeed(float f) { m_PlayerHorizontalSpeed = f; }
	float _GetHorizontalSpeed() { return m_PlayerHorizontalSpeed; }
	
public:
	float m_MovementDelay = 0.0f;
	const float MOVEMENT_DELAY = 0.2f;
	float m_PlayerHorizontalSpeed = 0.1f;

};
