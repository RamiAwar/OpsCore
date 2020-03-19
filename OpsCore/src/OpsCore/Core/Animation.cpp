#include "ocpch.h"
#include "OpsCore/Core/Animation.h"

namespace oc {
	
	bool Animation::UpdateFrame(Timestep ts) {

		if (m_Sprite->totalFrames > 0) {
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
		m_Sprite->currentIndex = m_StartIndex + (m_Sprite->currentIndex + 1) % m_TotalFrames;
	}

	void Animation::Reset() {
		m_CurrentFrame = 0;
		m_CurrentFrameTime = 0.0f;
	}


}