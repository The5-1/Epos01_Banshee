#include "BansheeHelper.h"

using namespace bs;

namespace The5
{

	bs::START_UP_DESC BansheeHelper::getStartupDesc()
	{
		bs::UINT32 windowResWidth = 1280;
		bs::UINT32 windowResHeight = 720;
		
		bs::START_UP_DESC The5_ApplicationDesc;

		// Use default values as specified by the build system
		The5_ApplicationDesc.renderAPI = BS_RENDER_API_MODULE;
		The5_ApplicationDesc.renderer = BS_RENDERER_MODULE;
		The5_ApplicationDesc.audio = BS_AUDIO_MODULE;
		The5_ApplicationDesc.physics = BS_PHYSICS_MODULE;

		// Use default values as specified by the build system
		The5_ApplicationDesc.renderAPI = BS_RENDER_API_MODULE;
		The5_ApplicationDesc.renderer = BS_RENDERER_MODULE;
		The5_ApplicationDesc.audio = BS_AUDIO_MODULE;
		The5_ApplicationDesc.physics = BS_PHYSICS_MODULE;

		// Descriptor used for initializing the primary application window.
		The5_ApplicationDesc.primaryWindowDesc.videoMode = bs::VideoMode(windowResWidth, windowResHeight);
		The5_ApplicationDesc.primaryWindowDesc.title = "Epos";
		The5_ApplicationDesc.primaryWindowDesc.fullscreen = false;
		The5_ApplicationDesc.primaryWindowDesc.depthBuffer = true;

		// List of importer plugins we plan on using for importing various resources
		The5_ApplicationDesc.importers.push_back("BansheeFreeImgImporter"); // For importing textures
		The5_ApplicationDesc.importers.push_back("BansheeFBXImporter"); // For importing meshes
		The5_ApplicationDesc.importers.push_back("BansheeFontImporter"); // For importing fonts
		The5_ApplicationDesc.importers.push_back("BansheeSL"); // For importing shaders

		return The5_ApplicationDesc;
	}
	
	void BansheeHelper::checkMesh(bs::HMesh mesh)
	{
		//gDebug().logDebug("Num. vertices: " + toString(props.getNumVertices()));
		//gDebug().logDebug("Num. indices: " + toString(props.getNumIndices()));
		//gDebug().logDebug("Radius: " + toString(props.getBounds().getSphere().getRadius()));
	}
}
