#include "PlayerController.h"
#include "Player.h"


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
}

void PlayerController::Shoot(oc::Timestep ts) {
	if (dynamic_cast<Player*>(m_ParentGameObject)->m_Sheathed) return;
	else {
		// shoot

	}
}
