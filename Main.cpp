///BansheeEngine includes
#include "include_Banshee.h"

///STL & Windows includes
#if BS_PLATFORM == BS_PLATFORM_WIN32
#include <windows.h>
#endif

///The5 includes
#include "The5_config.h"
#include "Logging.h"
#include "The5Application.h"
//#include "BansheeHelper.h"

///Components
#include "CameraFlyer.h"

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

#if 1

	The5::enableConsole();

	The5Application::start();
	//Application::startUp(VideoMode(1280, 720),"My app",false);

	gDebug().logDebug("Loading Assets.");
	HMesh sponzaMesh = The5Application::loadMesh(SPONZA_FBX.c_str(), 1.0f);
	HTexture uvCheckerTexture = The5Application::loadTexture(TEX_UVCHECKER.c_str(), 1.0f);

	HShader standartShader = BuiltinResources::instance().getBuiltinShader(BuiltinShader::Standard);
	HMaterial sponzaMat = Material::create(standartShader);
	sponzaMat->setTexture("gAlbedoTex", uvCheckerTexture);

	HSceneObject sponzaSO = SceneObject::create("Sponza");
	HRenderable renderable = sponzaSO->addComponent<CRenderable>();
	renderable->setMesh(sponzaMesh);
	renderable->setMaterial(The5Application::getDefaultPBRMaterial());

	HSceneObject sceneCameraSO = SceneObject::create("SceneCamera");
	SPtr<RenderWindow> window = gApplication().getPrimaryWindow();
	const RenderWindowProperties& windowProps = window->getProperties();
	//window->onResized.connect(&renderWindowResized);
	HCamera sceneCamera = sceneCameraSO->addComponent<CCamera>();
	sceneCamera->getViewport()->setTarget(window);
	sceneCamera->setPriority(1);
	sceneCamera->setNearClipDistance(0.01);
	sceneCamera->setFarClipDistance(1000.0);
	sceneCamera->setAspectRatio(windowProps.width / (float)windowProps.height);
	sceneCameraSO->addComponent<CameraFlyer>();
	sceneCameraSO->setPosition(Vector3(8.0f, 1.0f, 0.0f));
	sceneCameraSO->lookAt(Vector3(0, 3.0f, 0));

	//HSceneObject lightASO = SceneObject::create("Light A");
	//HSceneObject lightBSO = SceneObject::create("Light B");
	//lightASO->setPosition(Vector3(0, 50, 0));
	//lightBSO->setPosition(Vector3(-130, 140, 450));
	//HLight lightA = lightASO->addComponent<CLight>();
	//HLight lightB = lightBSO->addComponent<CLight>();
	//lightA->setUseAutoAttenuation(false);
	//lightB->setUseAutoAttenuation(false);
	//lightA->setAttenuationRadius(500.0f);
	//lightB->setAttenuationRadius(300.0f);
	//lightA->setIntensity(10000.0f);
	//lightB->setIntensity(10000.0f);


	gDebug().logDebug("Starting Main Loop.");
	Application::instance().runMainLoop();

	Application::shutDown();

#endif


#if 0
	Application::startUp(The5::BansheeHelper::getStartupDesc(WIDTH,HEIGHT));
	SPtr<RenderWindow> window = gApplication().getPrimaryWindow();
	window->onResized.connect(&The5::BansheeHelper::renderWindowResizedCallback);

	//gDebug().logDebug("Banshee Debug Message");
	//gDebug().logWarning("Banshee Warning Message");
	//gDebug().logError("Banshee Error Message");

	std::string sponzaPathFBX = GLOBAL_ASSET_PATH + "Sponza_Atrium_Png/sponza.FBX";
	std::string sponzaPathOBJ = GLOBAL_ASSET_PATH + "Sponza_Atrium_Png/sponza.obj";
	HMesh sponzaMeshFBX = gImporter().import<Mesh>(sponzaPathFBX.c_str());
	if (sponzaMeshFBX == nullptr) ERR("sponzaMeshFBX was not loaded!");
	HMesh sponzaMeshOBJ = gImporter().import<Mesh>(sponzaPathOBJ.c_str());
	if (sponzaMeshOBJ == nullptr) ERR("sponzaMeshOBJ was not loaded!");

	LOG(BuiltinResources::getShaderIncludeFolder().toString());

	HShader standartShader = BuiltinResources::instance().getBuiltinShader(BuiltinShader::Standard);
	HMaterial sponzaMat = Material::create(standartShader);

	/*
	GPU_PROGRAM_DESC vertProgDesc;
	vertProgDesc.type = GPT_VERTEX_PROGRAM;
	vertProgDesc.entryPoint = "main";
	vertProgDesc.language = "glsl";
	vertProgDesc.source = DEFAULT_SHADER_VERT.c_str();
	SPtr<GpuProgram> vertProg = GpuProgram::create(vertProgDesc);

	GPU_PROGRAM_DESC fragProgDesc;
	fragProgDesc.type = GPT_FRAGMENT_PROGRAM;
	fragProgDesc.entryPoint = "main";
	fragProgDesc.language = "glsl";
	fragProgDesc.source = DEFAULT_SHADER_FRAG.c_str();
	SPtr<GpuProgram> fragProg = GpuProgram::create(fragProgDesc);
	*/

	//HShader defaultShaderVert = gImporter().import<Shader>(DEFAULT_SHADER_VERT.c_str());
	//HShader defaultShaderFrag = gImporter().import<Shader>(DEFAULT_SHADER_FRAG.c_str());

	HSceneObject sponzaSO = SceneObject::create("Sponza");
	HRenderable renderable = sponzaSO->addComponent<CRenderable>();
	renderable->setMesh(sponzaMeshFBX);
	renderable->setMaterial(sponzaMat);

	HSceneObject mainCAmera = BansheeHelper::createCamera(WIDTH, HEIGHT);

	//HSceneObject skyboxSO = SceneObject::create("Skybox");
	//HSkybox skybox = skyboxSO->addComponent<CSkybox>();
	//skybox->setTexture(loadTexture(exampleSkyCubemapPath, false, true, true););

	//SPtr<RenderWindow> window = gApplication().getPrimaryWindow();
	//HSceneObject sceneCameraSO = SceneObject::create("MainCamera");
	//HCamera sceneCamera = sceneCameraSO->addComponent<CCamera>(window);
	//sceneCameraSO->setPosition(Vector3(40.0f, 30.0f, 230.0f));
	//sceneCameraSO->lookAt(Vector3(0, 0, 0));


	Application::instance().runMainLoop();

	Application::shutDown();
#endif
}