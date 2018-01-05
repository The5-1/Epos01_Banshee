#include "CMover.h"


using namespace bs;

namespace The5
{
	CMover::CMover(const bs::HSceneObject & parent, CMoverType type) : Component(parent), type(type)
	{
		setName("CMover");
		RB = SO()->getComponent<CRigidbody>();

		mMoveForward = VirtualButton("Arrow_Up");
		mMoveBack = VirtualButton("Arrow_Down");
		mMoveLeft = VirtualButton("Arrow_Left");
		mMoveRight = VirtualButton("Arrow_Right");
	}

	void CMover::update()
	{
		mCurrentSpeed += 0.00001;
		
#if 1
		Vector3 velocity = Vector3().ZERO;

		if (type == CMoverType::ControlledMove || type == CMoverType::ControlledPhysics)
		{
			bool goingForward = gVirtualInput().isButtonHeld(mMoveForward);
			bool goingBack = gVirtualInput().isButtonHeld(mMoveBack);
			bool goingLeft = gVirtualInput().isButtonHeld(mMoveLeft);
			bool goingRight = gVirtualInput().isButtonHeld(mMoveRight);

			const Transform& tfrm = SO()->getTransform();
			Vector3 direction = Vector3::ZERO;
			if (goingForward) direction += tfrm.getForward();
			if (goingBack) direction -= tfrm.getForward();
			if (goingRight) direction += tfrm.getRight();
			if (goingLeft) direction -= tfrm.getRight();

			float frameDelta = gTime().getFrameDelta();
			if (direction.squaredLength() != 0)
			{	
				direction.normalize();		
				mCurrentSpeed = Math::clamp(mCurrentSpeed + 0.001f * frameDelta, 5.0f, 10.0f);
				//gDebug().logDebug("moving: " + toString(direction) + "at speed: " + toString(mCurrentSpeed));
			}

			float tooSmall = std::numeric_limits<float>::epsilon();
			if (mCurrentSpeed > tooSmall)
			{
				velocity = direction*mCurrentSpeed*frameDelta;
			}
			else
			{
				velocity = Vector3().ZERO;
			}
		}

		switch (type)
		{
		case(CMoverType::ControlledMove):
		{
			SO()->move(velocity);
			return;
		}
		case(CMoverType::ControlledPhysics):
		{
			if (RB != nullptr)
				RB->addForce(velocity, ForceMode::Impulse);
			return;
		}
		case(CMoverType::RandomMove):
		{
			SO()->move((Vector3(rand() % 200, rand() % 200, rand() % 200) - 100.0f)*0.01f);
			return;
		}
		case(CMoverType::RandomPhysics):
		{
			if (RB != nullptr)
				RB->addForce((Vector3(rand() % 200, rand() % 200, rand() % 200) - 100.0f)*0.01f, ForceMode::Impulse);
			return;
		}
		default:
			return;
		}
#endif
	}
	
}