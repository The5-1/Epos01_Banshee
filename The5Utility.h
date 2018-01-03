#pragma once

#include "ForwardDeclarations.h"
#include "include_Banshee.h"

namespace The5 {
	namespace Utility
	{

		/** show verbose output on import */
		const bool showImportDebug = false;

		/** force to rebuild .asset files */
		const bool forceRebuildAssetOnImport = false;

		/** import a mesh and save it as Banshee .asset if it does not exist yet**/
		bs::HMesh loadMesh(const bs::Path& originalFilePath, float scale = 1.0f, bool forceInport = false);
		/** import a texture and save it as Banshee .asset if it does not exist yet**/
		bs::HTexture loadTexture(const bs::Path& originalFilePath, bool isSRGB = false, bool isCubemap = false, bool isHDR = false, bool forceInport = false);
	}
}