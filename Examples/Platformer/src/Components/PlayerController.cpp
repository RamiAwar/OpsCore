#include "PlayerController.h"

void PlayerController::OnCreate()
{
}

void PlayerController::OnDestroy()
{
}

void PlayerController::OnEvent(oc::Event& e)
{
}

void PlayerController::OnUpdate(oc::Timestep ts)
{
}

void PlayerController::OnLateUpdate(oc::Timestep ts)
{
}

void PlayerController::Render()
{
}

void PlayerController::MoveRight(oc::Timestep ts){
	m_ParentGameObject->GetTransform()->position.x += ts*m_PlayerHorizontalSpeed;
}

void PlayerController::MoveLeft(oc::Timestep ts) {
	m_ParentGameObject->GetTransform()->position.x -= ts*m_PlayerHorizontalSpeed;
}

void PlayerController::Sheathe(oc::Timestep ts) {
	//m_ParentGameObject->GetAnimationStateMachine()->SetState("sheathe");
}

void PlayerController::Shoot(oc::Timestep ts) {
	//m_ParentGameObject->GetAnimationStateMachine()->SetState("shoot");
}
