#include "PlayerController.h"



void PlayerController::OnUpdate(oc::Timestep ts)
{
}

void PlayerController::MoveRight(oc::Timestep ts){
	m_PlayerHorizontalSpeed = abs(m_PlayerHorizontalSpeed);
	UpdatePosition(ts);
}

void PlayerController::MoveLeft(oc::Timestep ts) {
	//m_ParentGameObject->GetTransform()->position.x -= ts*m_PlayerHorizontalSpeed;
	m_PlayerHorizontalSpeed = -1.0f * abs(m_PlayerHorizontalSpeed);
	UpdatePosition(ts);
}

void PlayerController::Sheathe(oc::Timestep ts) {
	//m_ParentGameObject->GetAnimationStateMachine()->SetState("sheathe");
}

void PlayerController::Shoot(oc::Timestep ts) {
	//m_ParentGameObject->GetAnimationStateMachine()->SetState("shoot");
}
