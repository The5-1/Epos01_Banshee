///BansheeEngine includes
#include "BsApplication.h"
#include "Resources/BsResources.h"
#include "Resources/BsBuiltinResources.h"
#include "Importer/BsImporter.h"
#include "Importer/BsTextureImportOptions.h"
#include "Importer/BsMeshImportOptions.h"
#include "Material/BsMaterial.h"
#include "Material/BsShader.h"
#include "Input/BsVirtualInput.h"
#include "Components/BsCCamera.h"
#include "Components/BsCRenderable.h"
#include "Components/BsCLight.h"
#include "GUI/BsCGUIWidget.h"
#include "GUI/BsGUILayoutX.h"
#include "GUI/BsGUILayoutY.h"
#include "GUI/BsGUIPanel.h"
#include "GUI/BsGUISpace.h"
#include "GUI/BsGUILabel.h"
#include "GUI/BsGUIButton.h"
#include "GUI/BsGUIListBox.h"
#include "GUI/BsProfilerOverlay.h"
#include "RenderAPI/BsRenderAPI.h"
#include "RenderAPI/BsRenderWindow.h"
#include "Scene/BsSceneObject.h"
#include "BsEngineConfig.h"

///STL & Windows includes
#if BS_PLATFORM == BS_PLATFORM_WIN32
#include <windows.h>
#endif

///The5 includes
#include "The5_config.h"

namespace The5
{
	void initBansheeApplication()
	{
		// Descriptor used for initializing the engine
		bs::START_UP_DESC startUpDesc;

		// Use default values as specified by the build system
		startUpDesc.renderAPI = BS_RENDER_API_MODULE;
		startUpDesc.renderer = BS_RENDERER_MODULE;
		startUpDesc.audio = BS_AUDIO_MODULE;
		startUpDesc.physics = BS_PHYSICS_MODULE;
	}

}

using namespace bs;

/** Main entry point into the application. */
#if BS_PLATFORM == BS_PLATFORM_WIN32
int CALLBACK WinMain(
	_In_  HINSTANCE hInstance,
	_In_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,
	_In_  int nCmdShow
)
#else
int main()
#endif
{
	Application::startUp( VideoMode(1280, 720),"Epos", false);

	Application::instance().runMainLoop();

	Application::shutDown();
}