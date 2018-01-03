#include "The5InputConfig.h"

#include "include_Banshee.h"

using namespace bs;

namespace The5
{


	void InputConfig::initDefaultKeyBindings()
	{
		auto inputConfig = VirtualInput::instance().getConfiguration();

		// 0 or 1
		inputConfig->registerButton("Forward", BC_W);
		inputConfig->registerButton("Back", BC_S);
		inputConfig->registerButton("Left", BC_A);
		inputConfig->registerButton("Right", BC_D);
		inputConfig->registerButton("Forward", BC_UP);
		inputConfig->registerButton("Back", BC_DOWN);
		inputConfig->registerButton("Left", BC_LEFT);
		inputConfig->registerButton("Right", BC_RIGHT);
		inputConfig->registerButton("Shift", BC_LSHIFT);
		inputConfig->registerButton("RMB", BC_MOUSE_RIGHT);

		//[-1.0, 1.0]
		inputConfig->registerAxis("Horizontal", VIRTUAL_AXIS_DESC((UINT32)InputAxis::MouseX));
		inputConfig->registerAxis("Vertical", VIRTUAL_AXIS_DESC((UINT32)InputAxis::MouseY));

	}

}