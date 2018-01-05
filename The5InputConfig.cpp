#include "The5InputConfig.h"

#include "include_Banshee.h"

using namespace bs;

namespace The5
{


	void InputConfig::initDefaultKeyBindings()
	{
		auto inputConfig = VirtualInput::instance().getConfiguration();

		// 0 or 1
		inputConfig->registerButton("W", BC_W);
		inputConfig->registerButton("A", BC_A);
		inputConfig->registerButton("D", BC_D);
		inputConfig->registerButton("S", BC_S);
		inputConfig->registerButton("Arrow_Up", BC_UP);
		inputConfig->registerButton("Arrow_Down", BC_DOWN);
		inputConfig->registerButton("Arrow_Left", BC_LEFT);
		inputConfig->registerButton("Arrow_Right", BC_RIGHT);
		inputConfig->registerButton("LShift", BC_LSHIFT);
		inputConfig->registerButton("RMB", BC_MOUSE_RIGHT);

		//[-1.0, 1.0]
		inputConfig->registerAxis("MouseX", VIRTUAL_AXIS_DESC((UINT32)InputAxis::MouseX));
		inputConfig->registerAxis("MouseY", VIRTUAL_AXIS_DESC((UINT32)InputAxis::MouseY));

	}

}