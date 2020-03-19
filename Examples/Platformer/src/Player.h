#pragma once
#include <OpsCore.h>
#include "Components/InputHandler.h"
#include "Components/PlayerController.h"

class Player : public oc::GameObject {

public:

	Player() 
		// TODO: Refactor this code to make setting a sprite more friendly (turn into component with input)
		: m_Sprite(oc::Sprite("assets/sprites/spy/spy.atlas.png", 20, 4, 80))
	{}

	// Inherited via GameObject
	virtual void OnCreate() override;
	virtual void OnDestroy() override;
	virtual void OnUpdate(oc::Timestep ts) override;
	virtual void OnLateUpdate(oc::Timestep ts) override;
	virtual void Render() override;

	oc::Sprite* GetSprite() { return &m_Sprite; }

private:

	oc::Sprite m_Sprite;
	oc::Ref<InputHandler> m_InputHandler;
	oc::Ref<PlayerController> m_PlayerController;

};