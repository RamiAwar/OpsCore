#pragma once

#include "OpsCore/Core/Core.h"
#include "OpsCore/Core/Component.h"
#include "OpsCore/Core/Animation.h"
#include "OpsCore/Core/Sprite.h"
#include "OpsCore/Core/AnimationState.h"

namespace oc {


	class AnimationController : public Component {

	public:

		AnimationController(GameObject* parent) :Component(parent) 
		{}

		// Inherited via Component
		virtual void OnCreate() override;
		virtual void OnDestroy() override;
		virtual void OnEvent(Event& e) override;
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnLateUpdate(Timestep ts) override;
		virtual void Render()=0;

		inline void BindSprite(Ref<Sprite> sprite) { m_Sprite = sprite; }
		void LoadSprite(const std::string& path, int rows, int cols, int nFrames);

		void AddAnimation(const std::string& name, Ref<Animation> animation);
		void AddAnimation(const std::string& name, int startIndex, int endIndex, float timePerFrame = 0.01f);
		void SetAnimation(const std::string& name);
		bool Find(const std::string& name);

	protected:
		
		Ref<Sprite> m_Sprite;
		Ref<Animation> m_CurrentAnimation;
		//AnimationState* m_CurrentAnimationState;

		std::unordered_map<std::string, Ref<Animation>> m_AnimationList;
	};
}