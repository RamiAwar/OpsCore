#include "PlayerAnimationController.h"
#include "Components/PlayerController.h"

void PlayerAnimationController::OnCreate() {
	OC_CLIENT_INFO("Player animation controller on create");
	m_CurrentAnimationState = new IdleState();
	m_CurrentAnimationState->enter(m_ParentGameObject);
}

void PlayerAnimationController::Render() {
	m_Sprite->Render(
		m_ParentGameObject->transform.position,
		m_ParentGameObject->transform.scale.x, // note than only X scale matters since we are rendering square sprite and dont plan on changing that
		std::dynamic_pointer_cast<PlayerController>(m_ParentGameObject->GetComponent("PlayerController"))->_GetHorizontalSpeed() < 0.0f
	);
}

void PlayerAnimationController::OnUpdate(oc::Timestep ts) {
	OC_INFO("Updating current animation state");
	m_CurrentAnimationState->update(ts, m_ParentGameObject);
	OC_INFO("State updated successfully");
}

void PlayerAnimationController::MoveRight(oc::Timestep ts) {
	SpyAnimationState* state = m_CurrentAnimationState->MoveRight(m_ParentGameObject);
	if (state != NULL) {
		delete m_CurrentAnimationState;
		m_CurrentAnimationState = state;
		m_CurrentAnimationState->enter(m_ParentGameObject);
	}
}

void PlayerAnimationController::Idle(oc::Timestep ts) {
	SpyAnimationState* state = m_CurrentAnimationState->Idle(m_ParentGameObject);
	if (state != NULL) {
		delete m_CurrentAnimationState;
		m_CurrentAnimationState = state;
		m_CurrentAnimationState->enter(m_ParentGameObject);
	}
}

void PlayerAnimationController::MoveLeft(oc::Timestep ts) {
	SpyAnimationState* state = m_CurrentAnimationState->MoveLeft(m_ParentGameObject);
	if (state != NULL) {
		delete m_CurrentAnimationState;
		m_CurrentAnimationState = state;
		m_CurrentAnimationState->enter(m_ParentGameObject);
	}
}

void PlayerAnimationController::Sheathe(oc::Timestep ts) {
	SpyAnimationState* state = m_CurrentAnimationState->Sheathe(m_ParentGameObject);
	if (state != NULL) {
		delete m_CurrentAnimationState;
		m_CurrentAnimationState = state;
		m_CurrentAnimationState->enter(m_ParentGameObject);
	}
}

void PlayerAnimationController::Shoot(oc::Timestep ts) {
	SpyAnimationState* state = m_CurrentAnimationState->Shoot(m_ParentGameObject);
	if (state != NULL) {
		delete m_CurrentAnimationState;
		m_CurrentAnimationState = state;
		m_CurrentAnimationState->enter(m_ParentGameObject);
	}
}
