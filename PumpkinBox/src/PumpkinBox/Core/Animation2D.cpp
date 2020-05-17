#include "pbpch.h"
#include "PumpkinBox/Core/Animation2D.h"

namespace pb {
	
	bool Animation2D::Update(Timestep ts) {
		
		PB_INFO("Current frame: {}", m_CurrentIndex);

		if (m_TotalFrames > 0) {
			m_CurrentFrameTime += ts;

			if (m_CurrentFrameTime >= m_TimePerFrame) {
				m_CurrentFrameTime = 0.0f;
				IncrementFrame();
				return true;
			}
		}
		return false;
	}

	void Animation2D::IncrementFrame() {

		// TODO: Deal with non-looping animations
		if (m_Loop) {
			m_LocalIndex = (m_LocalIndex + 1) % m_TotalFrames;
			m_CurrentIndex = m_StartIndex + m_LocalIndex;
		} 
		else {
			if(m_CurrentIndex < m_EndIndex) m_CurrentIndex++;
		}
	}

	void Animation2D::Reset() {
		m_CurrentIndex = m_StartIndex;
		m_CurrentFrameTime = 0.0f;
		m_LocalIndex = 0;
	}


}