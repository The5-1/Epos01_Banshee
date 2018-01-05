#include "CMover.h"


using namespace bs;

namespace The5
{
	CMover::CMover(const bs::HSceneObject & parent) : Component(parent)
	{
		RB = SO()->getComponent<CRigidbody>();
	}

	void CMover::update()
	{
		RB->addForce((Vector3(rand() % 200, rand() % 200, rand() % 200)-100.0f)*0.01f, ForceMode::Impulse);
	}

}