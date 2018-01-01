///BansheeEngine includes
#include "include_Banshee.h"
#include "BansheeHelper.h"

///STL & Windows includes
#if BS_PLATFORM == BS_PLATFORM_WIN32
#include <windows.h>
#endif

///The5 includes
#include "The5_config.h"
#include "Logging.h"

using namespace bs;
using namespace The5;

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
	The5::enableConsole();

	Application::startUp(The5::BansheeHelper::getStartupDesc());

	std::string sponzaPathFBX = GLOBAL_ASSET_PATH + "Sponza_Atrium_Png/sponza.FBX";
	std::string sponzaPathOBJ = GLOBAL_ASSET_PATH + "Sponza_Atrium_Png/sponza.obj";
	HMesh sponzaMeshFBX = gImporter().import<Mesh>(sponzaPathFBX.c_str());
	if (sponzaMeshFBX == nullptr) ERR("sponzaMeshFBX was not loaded!");
	HMesh sponzaMeshOBJ = gImporter().import<Mesh>(sponzaPathOBJ.c_str());
	if (sponzaMeshOBJ == nullptr) ERR("sponzaMeshOBJ was not loaded!");

	HSceneObject sponzaSO = SceneObject::create("Sponza");
	HRenderable renderable = sponzaSO->addComponent<CRenderable>();
	renderable->setMesh(sponzaMeshFBX);
	//renderable->setMaterial(dragonMaterial);

	//SPtr<RenderWindow> window = gApplication().getPrimaryWindow();
	//HSceneObject sceneCameraSO = SceneObject::create("MainCamera");
	//HCamera sceneCamera = sceneCameraSO->addComponent<CCamera>(window);
	//sceneCameraSO->setPosition(Vector3(40.0f, 30.0f, 230.0f));
	//sceneCameraSO->lookAt(Vector3(0, 0, 0));


	Application::instance().runMainLoop();

	Application::shutDown();
}