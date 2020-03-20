#pragma once

#include "OpsCore/Core/Timestep.h"
#include "OpsCore/Core/Sprite.h"

namespace oc {

	class Animation
	{
	public:
		Animation(int startIndex, int endIndex, float timePerFrame = 0.01f) 
			: m_CurrentIndex(0), m_CurrentFrameTime(0.0f), m_TimePerFrame(timePerFrame), 
			m_StartIndex(startIndex), m_EndIndex(endIndex)
		{
			m_TotalFrames = m_EndIndex - m_StartIndex + 1;
		}

		int GetCurrentIndex() { return m_CurrentIndex; }

		bool Update(Timestep ts);

		void Reset();

		// TODO: Remove and set customizable per frame?
		void _SetTimePerFrame(float f) { m_TimePerFrame = f; }

	private:

		void IncrementFrame();

		int m_CurrentIndex;
		float m_CurrentFrameTime;
		float m_TimePerFrame;

		int m_StartIndex, m_EndIndex;
		int m_TotalFrames;

	
	};



}

