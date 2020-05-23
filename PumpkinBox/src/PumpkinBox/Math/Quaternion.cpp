#include "pbpch.h"

#include "Quaternion.h"

namespace pb {

	float& Quaternion::operator[](int index)
	{
		PB_ASSERT(index >= 0 && index < 4, "Quaternion index {} out of range!", index);
		switch (index) {
		case 0: return m_Quaternion.x;
		case 1: return m_Quaternion.y;
		case 2: return m_Quaternion.z;
		case 3: return m_Quaternion.w;
		}
	}

}