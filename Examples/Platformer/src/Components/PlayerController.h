#pragma once
#include <OpsCore.h>
#include "Command.h"

class PlayerController : public oc::Component
{
public:
	PlayerController(oc::GameObject* parent) : Component(parent) {}
	
	// Inherited via Component
	virtual void OnCreate() override;
	virtual void OnDestroy() override;
	virtual void OnEvent(oc::Event& e) override;
	virtual void OnUpdate(oc::Timestep ts) override;
	virtual void OnLateUpdate(oc::Timestep ts) override;
	virtual void Render() override;

	void MoveRight() {
		// TODO: Queue this action for later execution during Update()
		m_ParentGameObject->GetTransform()->position.x += m_PlayerHorizontalSpeed;
	}


public:
	float m_PlayerHorizontalSpeed = 0.045f;

};
