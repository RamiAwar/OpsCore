#include "pbpch.h"
//#include "AnimationController.h"
//
//
//void oc::AnimationController::OnCreate()
//{
//}
//
//void oc::AnimationController::OnDestroy()
//{
//}
//
//void oc::AnimationController::OnEvent(Event& e)
//{
//}
//
//void oc::AnimationController::OnUpdate(Timestep ts)
//{
//	// Make sure sprite consistent with animation
//
//}
//
//void oc::AnimationController::OnLateUpdate(Timestep ts)
//{
//	m_Sprite->currentIndex = m_CurrentAnimation->GetCurrentIndex();
//	//PB_CLIENT_INFO("Updated sprite index");
//	m_CurrentAnimation->Update(ts);
//}
//
//void oc::AnimationController::LoadSprite(const std::string& path, int rows, int cols, int nFrames)
//{
//	m_Sprite = CreateRef<Sprite>(oc::Sprite(path, rows, cols, nFrames));
//}
//
////void oc::AnimationController::AddAnimation(const std::string& name, Ref<Animation> animation)
////{
////	PB_ASSERT(!Find(name), "Animation with name '{}' already exists!", name);
////	m_AnimationList[name] = animation;
////}
//
//void oc::AnimationController::AddAnimation(const std::string& name, int startIndex, int endIndex, float timePerFrame, bool loop)
//{
//	PB_ASSERT(!Find(name), "Animation with name '{}' already exists!", name);
//	m_AnimationList[name] = oc::CreateRef<oc::Animation2D>(oc::Animation2D(startIndex, endIndex, timePerFrame, loop));
//}
//
//void oc::AnimationController::SetAnimation(const std::string& name)
//{
//	PB_ASSERT(Find(name), "Animation with name '{}' already exists!", name);
//	m_CurrentAnimation = m_AnimationList[name];
//}
//
//bool oc::AnimationController::Find(const std::string& name) {
//	return m_AnimationList.find(name) != m_AnimationList.end();
//}
