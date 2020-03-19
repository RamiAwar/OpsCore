#pragma once

#include "OpsCore/Core/Timestep.h"
#include "OpsCore/Core/Sprite.h"

namespace oc {

	class Animation
	{
	public:
		Animation(Ref<Sprite> sprite, int startIndex, int endIndex) 
			: m_CurrentFrame(0), m_CurrentFrameTime(0.0f), m_TimePerFrame(0.1f),
			  m_Sprite(sprite), m_StartIndex(startIndex), m_EndIndex(endIndex)
		{
			m_TotalFrames = m_EndIndex - m_StartIndex + 1;
		}

		int GetCurrentFrame() { return m_CurrentFrame; }

		bool UpdateFrame(Timestep ts);

		void Reset();

		// TODO: Remove and set customizable per frame?
		void SetTimePerFrame(float f) { m_TimePerFrame = f; }

	private:

		Ref<Sprite> m_Sprite;
		void IncrementFrame();

		int m_CurrentFrame;
		float m_CurrentFrameTime;
		float m_TimePerFrame;

		int m_StartIndex, m_EndIndex;
		int m_TotalFrames;

	
	};



}

