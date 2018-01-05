///BansheeEngine includes
#include "include_Banshee.h"

///STL & Windows includes
#if BS_PLATFORM == BS_PLATFORM_WIN32
#include <windows.h>
#endif

///The5 includes
#include "The5Config.h"
#include "Logging.h"
#include "The5Application.h"
#include "The5Utility.h"
#include "The5DefaultAssets.h"
#include "The5InputConfig.h"
#include "CActorBody.h"
#include "CMover.h"

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

	The5::enableConsole();

#define USE_THE5_APPLICATION
#ifdef USE_THE5_APPLICATION
	The5Application::start();
#else
	Application::startUp(VideoMode(1280,720), "Epos", false);
	The5::DefaultAssets::init();
	The5::InputConfig::initDefaultKeyBindings();

	HSceneObject sceneCameraSO = SceneObject::create("SceneCamera");
	SPtr<RenderWindow> window = gApplication().getPrimaryWindow();
	//window->onResized.connect(&renderWindowResized);
	HCamera sceneCamera = sceneCameraSO->addComponent<CCamera>();
	sceneCamera->getViewport()->setTarget(window);
	sceneCamera->setPriority(1);
	sceneCamera->setNearClipDistance(0.005f);
	sceneCamera->setFarClipDistance(10000);
	sceneCamera->setAspectRatio(1280 / (float)720);
	sceneCameraSO->addComponent<CameraFlyer>();
	sceneCameraSO->setPosition(Vector3(-130.0f, 140.0f, 650.0f));
	sceneCameraSO->lookAt(Vector3(0, 0, 0));
#endif

	CrashHandler::shutDown(); //this keeps banshee from spamming crash logs

	Vector3 aabbsize = DefaultAssets::defaultCube->getProperties().getBounds().getBox().getSize();
	gDebug().logDebug("defaultCube AABB size: " + bs::toString(aabbsize));
	//The5::Utility::convertPathToBansheeAssetDir(MESH_SPONZA.c_str(), "Meshes");

	HSceneObject sunlightSO = SceneObject::create("Sun");
	sunlightSO->setPosition(Vector3(-20, 200, 0));
	sunlightSO->lookAt(Vector3(0.0, 0.0, 0.0));
	HLight sunlightC = sunlightSO->addComponent<CLight>();
	//sunlightC->setType(LightType::Directional);
	sunlightC->setSourceRadius(50.0); //Area light, must be 0.25 or so for sun
	sunlightC->setCastsShadow(true);
	sunlightC->setUseAutoAttenuation(false);
	sunlightC->setAttenuationRadius(1000.0f);
	sunlightC->setIntensity(500000.0f);

	//gPhysics().setGravity(-Vector3().UNIT_Y*0.1f);
	/*
	HSceneObject skyboxSO = SceneObject::create("Skybox");
	HSkybox skyboxC = skyboxSO->addComponent<CSkybox>();
	skyboxC->setTexture(DefaultAssets::defaultSkybox);
	skyboxC->setBrightness(0.1f);
	*/

	float sphereRadius = 0.5;
	HSceneObject sphereSO = SceneObject::create("Sphere");
	sphereSO->setPosition(Vector3(0.0f, 4.0f, 0.0f));
	sphereSO->setScale(Vector3(1.0f, 1.0f, 1.0f)*sphereRadius);
	HRigidbody sphereSO_RB = sphereSO->addComponent<CRigidbody>();
	sphereSO_RB->addForce(Vector3(1.0f, -5.0f, 1.0f));
	HSphereCollider sphereSO_Collider = sphereSO->addComponent<CSphereCollider>();
	sphereSO_Collider->setRadius(1.0f);
	HRenderable sphereSO_CRenderable = sphereSO->addComponent<CRenderable>();
	sphereSO_CRenderable->setMesh(DefaultAssets::defaultCube);
	//sphereSO_CRenderable->setMesh(BuiltinResources::instancePtr()->getMesh(BuiltinMesh::Sphere));
	sphereSO_CRenderable->setMaterial(DefaultAssets::defaultPBRMaterial);
	
	//DrawHelper::ShapeMeshData(ShapeMeshes3D::solidSphere()); //???

	HSceneObject groundSO = SceneObject::create("Ground");
	groundSO->setScale(Vector3(1.0f, 1.0f, 1.0f)*10000.0);
	//groundSO->lookAt(Vector3(0.1f, 0.1f, 1.0f),Vector3(0.0f,1.0f,0.0f));
	HPlaneCollider groundSO_Collider = groundSO->addComponent<CPlaneCollider>();
	groundSO_Collider->setNormal(Vector3(0.0f, 1.0f, 0.0f));
	HRenderable groundSO_CRenderable = groundSO->addComponent<CRenderable>();
	groundSO_CRenderable->setMesh(DefaultAssets::defaultPlane);
	groundSO_CRenderable->setMaterial(DefaultAssets::defaultPBRMaterial);
	
	HSceneObject player = SceneObject::create("Player");
	HActorBody player_body = player->addComponent<CActorBody>();
	HMover player_mover = player->addComponent<CMover>();


	//HCharacterController playerSO_Controller = playerSO->addComponent<CCharacterController>();
	//playerSO_Controller->setHeight(playerHeight);
	//playerSO_Controller->setRadius(playerRadius);
	//playerSO_Controller->setUp(Vector3::UNIT_Y);
	
	
	/*
	HSceneObject sponzaSO = SceneObject::create("Sponza");
	HRenderable sponzaSO_CRenderable = sponzaSO->addComponent<CRenderable>();
	sponzaSO_CRenderable->setMesh(DefaultAssets::defaultSponza);
	sponzaSO_CRenderable->setMaterial(DefaultAssets::defaultPBRMaterial);
	*/

	//DebugDraw::instancePtr()->setColor(Color(1.0f, 0.0f, 0.0f, 1.0f));
	//DebugDraw::instancePtr()->drawWireSphere(Vector3(0.0f, 0.0f, 0.0f), 1.0f);
	//DebugDraw::instancePtr()->drawWireCube(Vector3(0.0f, 0.5f, 0.0f), Vector3(0.5,0.5,0.5));
   
	//The5Application::getThe5Application().mainCamera()->setNearClipDistance(0.0001f);
	std::cout << "Camera Name: " << The5Application::getThe5Application().mainCamera()->getName() << std::endl;
	std::cout << "near: " << The5Application::getThe5Application().mainCamera()->getNearClipDistance() << std::endl;
	std::cout << "far: " << The5Application::getThe5Application().mainCamera()->getFarClipDistance() << std::endl;
	std::cout << "priority: " << The5Application::getThe5Application().mainCamera()->getPriority() << std::endl;
	/*
	HSceneObject testSO = SceneObject::create("Sphere");
	HRenderable testSO_CRenderable = testSO->addComponent<CRenderable>();
	testSO->setScale(Vector3(1000.0, 1000.0, 1000.0));
	testSO_CRenderable->setMesh(DefaultAssets::defaultSphere);
	testSO_CRenderable->setMaterial(DefaultAssets::defaultPBRMaterial);
	gDebug().logDebug(toString(testSO_CRenderable->getMesh()->getProperties().getNumVertices()));
	*/

	
	for (int x = -5; x <= 5; x++)
	{
		for (int z = -5; z <= 5; z++)
		{
			HSceneObject spam = SceneObject::create("Grid");
			spam->move(Vector3(x*1.0f, 0.0f, z*1.0f));
			spam->setScale(Vector3(1.0, 1.0, 1.0)*10.0f);
			HRenderable spamR = spam->addComponent<CRenderable>();
			spamR->setMesh(DefaultAssets::defaultCube);
			spamR->setMaterial(DefaultAssets::defaultPBRMaterial);
		}
	}
	

	/*
	for (int i = 0; i < 100; i++)
	{
		float r1 = (float)(rand()%100-50)*0.01;
		float r2 = (float)(rand()%100-50)*0.01;
		float r3 = (float)(rand()%100-50)*0.01;
		float r4 = (float)(rand()%100)*0.01;
		//std::cout << r1 << "," << r2 << "," << r3 << std::endl;
		std::string name = "Sphere_" + i;
		HSceneObject spam = SceneObject::create(name.c_str());
		spam->move(Vector3(r1, r2, r3));
		spam->setScale(Vector3(200.0, 200.0, 200.0)*(r1+r3)/(r2+r3));
		HRenderable spamR = spam->addComponent<CRenderable>();
		spamR->setMesh(DefaultAssets::defaultSphere);
		spamR->setMaterial(DefaultAssets::defaultPBRMaterial);
	}
	*/

	gDebug().logDebug("Starting Main Loop.");
	Application::instance().runMainLoop();

	Application::shutDown();

	/*
	DrawHelper drawhelper = DrawHelper();
	drawhelper.setLayer(2);
	drawhelper.setColor(Color(1.0f, 0.0f, 0.0f, 1.0f));
	drawhelper.wireCube(Vector3(0.0, 0.0, 0.0), Vector3(1.0, 1.0, 1.0)*200.0);
	drawhelper.buildMeshes();
	Vector<DrawHelper::ShapeMeshData> meshes = drawhelper.getMeshes();
	for (DrawHelper::ShapeMeshData s : meshes)
	{
	s.mesh
	}
	*/


	//testSO->setScale(Vector3(0.2,0.2,0.2));

	/*
	bs::Vector<bs::HComponent> components = SceneManager::instancePtr()->findComponents<Component>();
	for (auto c : components)
	{
		std::cout << c.getTypeName() << std::endl;
	}
	*/

	/*
	DrawHelper* dh = new DrawHelper();
	dh->cube(Vector3(0.0, 0.0, 0.0), Vector3(5.0, 5.0, 5.0));
	dh->setColor(Color(1.0, 0.0, 0.0, 1.0));
	dh->buildMeshes();
	dh->getMeshes();
	*/




#if 0 //this works with only The5App

	The5::enableConsole();

	The5Application::start();
	//Application::startUp(VideoMode(1280, 720),"My app",false);

	gDebug().logDebug("Loading Assets.");
	HMesh sponzaMesh = The5Application::loadMesh(MESH_SPONZA.c_str(), 1.0f);
	HTexture uvCheckerTexture = The5Application::loadTexture(TEX_UVCHECKER.c_str(), 1.0f);

	HSceneObject sponzaSO = SceneObject::create("Sponza");
	HRenderable renderable = sponzaSO->addComponent<CRenderable>();
	renderable->setMesh(sponzaMesh);
	renderable->setMaterial(The5Application::getDefaultPBRMaterial());

#if 0
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
#endif

#if 0
	HSceneObject lightASO = SceneObject::create("Light A");
	HSceneObject lightBSO = SceneObject::create("Light B");
	lightASO->setPosition(Vector3(0, 50, 0));
	lightBSO->setPosition(Vector3(-130, 140, 450));
	HLight lightA = lightASO->addComponent<CLight>();
	HLight lightB = lightBSO->addComponent<CLight>();
	lightA->setUseAutoAttenuation(false);
	lightB->setUseAutoAttenuation(false);
	lightA->setAttenuationRadius(500.0f);
	lightB->setAttenuationRadius(300.0f);
	lightA->setIntensity(10000.0f);
	lightB->setIntensity(10000.0f);
#endif

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
	//HSkybox skyboxC = skyboxSO->addComponent<CSkybox>();
	//skyboxC->setTexture(loadTexture(exampleSkyCubemapPath, false, true, true););

	//SPtr<RenderWindow> window = gApplication().getPrimaryWindow();
	//HSceneObject sceneCameraSO = SceneObject::create("MainCamera");
	//HCamera sceneCamera = sceneCameraSO->addComponent<CCamera>(window);
	//sceneCameraSO->setPosition(Vector3(40.0f, 30.0f, 230.0f));
	//sceneCameraSO->lookAt(Vector3(0, 0, 0));


	Application::instance().runMainLoop();

	Application::shutDown();
#endif
}