#pragma once

#include "include_Banshee.h"

namespace The5
{
	class BansheeHelper
	{
	public:
		static bs::START_UP_DESC getStartupDesc();

		static void checkMesh(bs::HMesh mesh);
	};

}