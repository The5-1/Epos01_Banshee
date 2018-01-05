#pragma once

#include "include_STL.h"
#include "include_Banshee.h"
#include "ForwardDeclarations.h"

namespace The5 {

	/** documentation */
	class CMover : public bs::Component
	{
	public:
		CMover(const bs::HSceneObject& parent);

		void update();

	protected:

		bs::HRigidbody RB;
	};
}