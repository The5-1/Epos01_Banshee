#include "include_STL.h"
#include "The5Application.h"
#include "Logging.h"
#include "CameraFlyer.h"

using namespace bs;

namespace The5
{
	The5Application::The5Application(const bs::START_UP_DESC & desc) :Application(desc) // Pass along the start-up structure to the parent
	{ }

	bs::START_UP_DESC The5Application::defaultStartupDesc()
	{
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
		The5_ApplicationDesc.primaryWindowDesc.videoMode = bs::VideoMode(1280,720);
		The5_ApplicationDesc.primaryWindowDesc.title = "Epos";
		The5_ApplicationDesc.primaryWindowDesc.fullscreen = false;
		The5_ApplicationDesc.primaryWindowDesc.depthBuffer = false; //deferred quad needs no depth in the on-screen buffer

		// List of importer plugins we plan on using for importing various resources
		The5_ApplicationDesc.importers.push_back("BansheeFreeImgImporter"); // For importing textures
		The5_ApplicationDesc.importers.push_back("BansheeFBXImporter"); // For importing meshes
		The5_ApplicationDesc.importers.push_back("BansheeFontImporter"); // For importing fonts
		The5_ApplicationDesc.importers.push_back("BansheeSL"); // For importing shaders);

		return The5_ApplicationDesc;
	}

	void The5Application::onStartUp()
	{
		Application::onStartUp(); //init banshee first!

		subscribeCallbacksToEvents();

	}

	void The5Application::subscribeCallbacksToEvents()
	{
		//http://docs.banshee3d.com/Native/events.html "Class methods as event callbacks" ---> std::bind to bind the this-pointer into the callback

		///Window Events
		SPtr<RenderWindow> window = gApplication().getPrimaryWindow();
		//Resize
		window->onResized.connect(std::bind(&The5Application::windowResizeCallback, this));

		///... Events
	}

	void The5Application::onShutDown()
	{
		// Do your own shut-down (i.e. shut down your custom systems, autossave)

		Application::onShutDown(); //shut down banshee last
	}

	void The5Application::preUpdate()
	{
		
	}

	void The5Application::postUpdate()
	{
		
	}

	void The5Application::createMainCamera()
	{
		this->mainCameraSO = SceneObject::create("Main Camera");
		this->mainCamera = mainCameraSO->addComponent<CCamera>();

		SPtr<RenderWindow> window = gApplication().getPrimaryWindow();
		const RenderWindowProperties& windowProps = window->getProperties();

		// Add a Camera component that will output whatever it sees into that window 
		// (You could also use a render texture or another window you created).
		mainCamera->getViewport()->setTarget(window);

		/// Set up camera component properties
		// Set closest distance that is visible. Anything below that is clipped.
		mainCamera->setNearClipDistance(0.005f);
		// Set farthest distance that is visible. Anything above that is clipped.
		mainCamera->setFarClipDistance(1000.0f);
		// Set aspect ratio depending on the current resolution
		mainCamera->setAspectRatio(windowProps.width / (float)windowProps.height);
		// camera multi-sample anti-aliasing for better quality
		mainCamera->setMSAACount(0);
		// Add a CameraFlyer component that allows us to move the camera. See CameraFlyer for more information.
		mainCameraSO->addComponent<CameraFlyer>();
		// Position and orient the camera scene object
		mainCameraSO->setPosition(Vector3(0.0f, 0.0f, 1.0f));
		mainCameraSO->lookAt(Vector3(0, 0, 0));
	}

	
	void The5Application::windowResizeCallback()
	{
		SPtr<RenderWindow> window = gApplication().getPrimaryWindow(); //shared poitner will be deleted when this goes out of scope
		const RenderWindowProperties& windowProps = window->getProperties();

		//recalculate Camera Aspect Ratio
		if(mainCamera != nullptr) mainCamera->setAspectRatio(windowProps.width / (float)windowProps.height);

		//resize FBOs
		//TODO
	}

}
