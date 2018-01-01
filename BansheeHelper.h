#pragma once

#include "include_Banshee.h"

namespace The5
{
	class BansheeHelper
	{
	public:
		//static void startApplication(bs::UINT32 width, bs::UINT32 height);

		static void checkMesh(bs::HMesh mesh);

		static bs::HMesh loadMesh(bs::Path path, float scale);

		static bs::HTexture loadTexture(bs::Path path, bool isSRGB, bool isCubemap, bool isHDR);

		//static bs::HSceneObject createCamera(std::string name, bs::UINT32 width, bs::UINT32 height, float near = 0.005f, float far = 1000.0, bs::UINT32 masaa = 0);

		//static void renderWindowResizedCallback();

	};

}