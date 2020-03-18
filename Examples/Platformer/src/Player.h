#pragma once
#include <OpsCore.h>
#include "Components/InputHandler.h"
#include "Components/PlayerController.h"

class Player : public oc::GameObject {

public:

	Player() {}

	// Inherited via GameObject
	virtual void OnCreate() override;
	virtual void OnDestroy() override;
	virtual void OnUpdate(oc::Timestep ts) override;
	virtual void OnLateUpdate(oc::Timestep ts) override;
	virtual void Render() override;

private:

	oc::Ref<InputHandler> m_InputHandler;
	oc::Ref<PlayerController> m_PlayerController;

};