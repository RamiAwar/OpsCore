#include "Player.h"

void Player::OnCreate()
{
	OC_INFO("Player on create");

	m_InputHandler = oc::CreateRef<InputHandler>(this);
	m_PlayerController = oc::CreateRef<PlayerController>(this);

	AddComponent("InputHandler", m_InputHandler);
	AddComponent("PlayerController", m_PlayerController);
}

void Player::OnDestroy()
{
}

void Player::OnUpdate(oc::Timestep ts)
{
	OC_INFO("Player on update");
	Command* command = std::dynamic_pointer_cast<InputHandler>(GetComponent("InputHandler"))->HandleInput();
	if (command) {
		OC_INFO("Command received");
		command->execute(GetComponent("PlayerController"));
	}

}

void Player::OnLateUpdate(oc::Timestep ts)
{
}

void Player::Render()
{
}