#pragma once

#include "include_STL.h"

#include "include_Banshee.h"

#include "ForwardDeclarations.h"

namespace The5 {

	enum CMoverType { RandomPhysics, RandomMove, ControlledPhysics, ControlledMove };


	/** documentation */
	class CMover : public bs::Component
	{
	public:
		CMover(const bs::HSceneObject& parent, CMoverType type = CMoverType::ControlledMove);
		

		virtual void update() override;

		CMoverType type = CMoverType::ControlledMove;

	protected:

		float mCurrentSpeed;

		bs::VirtualButton mMoveForward; 
		bs::VirtualButton mMoveBack;
		bs::VirtualButton mMoveLeft;
		bs::VirtualButton mMoveRight;

		bs::HRigidbody RB;
	};
	
	typedef bs::GameObjectHandle<CMover> HMover;
}