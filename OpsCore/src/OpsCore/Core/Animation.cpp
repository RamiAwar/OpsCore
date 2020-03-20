#include "ocpch.h"
#include "OpsCore/Core/Animation.h"

namespace oc {
	
	bool Animation::Update(Timestep ts) {

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

	void Animation::IncrementFrame() {

		// TODO: Deal with non-looping animations
		m_CurrentIndex = m_StartIndex + (m_CurrentIndex + 1) % m_TotalFrames;
	}

	void Animation::Reset() {
		m_CurrentIndex = 0;
		m_CurrentFrameTime = 0.0f;
	}


}