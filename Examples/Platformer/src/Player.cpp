#include "Player.h"

void Player::OnCreate()
{

	OC_INFO("Player on create");

	m_Sheathed = true;

	m_InputHandler = oc::CreateRef<InputHandler>(this);
	m_PlayerController = oc::CreateRef<PlayerController>(this);
	m_PlayerAnimationController = oc::CreateRef<PlayerAnimationController>(this);


	AddComponent("InputHandler", m_InputHandler);
	AddComponent("PlayerController", m_PlayerController);
	AddComponent("PlayerAnimationController", m_PlayerAnimationController);


	m_PlayerController->_SetHorizontalSpeed(0.3f);
	m_PlayerAnimationController->LoadSprite(_spy_texture_atlas, 20, 4, 80);


	m_PlayerAnimationController->AddAnimation("idle", 12, 15, 0.15f);
	m_PlayerAnimationController->AddAnimation("run", 37, 44, 0.12f);
	m_PlayerAnimationController->AddAnimation("shoot", 61, 68, 0.14f, false);
	m_PlayerAnimationController->AddAnimation("sheathe", 53, 60, 0.13f, false);
	m_PlayerAnimationController->AddAnimation("rungun", 45, 52, 0.14f);
	m_PlayerAnimationController->AddAnimation("unsheathe", 69, 78, 0.13f, false);
	m_PlayerAnimationController->AddAnimation("idlegun", 16, 19, 0.14f);


	oc::GameObject::OnCreate();

}

void Player::OnDestroy()
{
	oc::GameObject::OnDestroy();
}

void Player::OnUpdate(oc::Timestep ts)
{
	//OC_CLIENT_INFO("Player on update");
	Command* command = std::dynamic_pointer_cast<InputHandler>(GetComponent("InputHandler"))->HandleInput();
	if (command) {
		//OC_CLIENT_INFO("Command received");
		command->execute(ts, std::dynamic_pointer_cast<PlayerController>(GetComponent("PlayerController")));
		command->animate(ts, std::dynamic_pointer_cast<PlayerAnimationController>(GetComponent("PlayerAnimationController")));
	}

	oc::GameObject::OnUpdate(ts);

	//OC_CLIENT_INFO("Finished processing input");

}

void Player::OnLateUpdate(oc::Timestep ts)
{
	//OC_CLIENT_INFO("player on late Update");
	oc::GameObject::OnLateUpdate(ts);
	//OC_CLIENT_INFO("Finished player on late update");
}

void Player::Render()
{
	//OC_CLIENT_INFO("Player render");
	oc::GameObject::Render();
	//OC_CLIENT_INFO("Finished player render");
}
