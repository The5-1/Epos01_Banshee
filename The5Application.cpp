#include "The5Application.h"

#include "include_STL.h"
#include "The5Config.h"
#include "Logging.h"

#include "CameraFlyer.h"

using namespace bs;

namespace The5
{

//---------------------------------Application-------------------------------

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
		The5_ApplicationDesc.scripting = false; //NOTE: enable scripting here

		// Descriptor used for initializing the primary application window.
		The5_ApplicationDesc.primaryWindowDesc.videoMode = bs::VideoMode(1280,720);
		The5_ApplicationDesc.primaryWindowDesc.title = "Epos";
		//The5_ApplicationDesc.primaryWindowDesc.vsync = true; //true is default, setting it to true again crashes
		The5_ApplicationDesc.primaryWindowDesc.vsyncInterval = 2;
		The5_ApplicationDesc.primaryWindowDesc.fullscreen = false;
		The5_ApplicationDesc.primaryWindowDesc.depthBuffer = false; //deferred quad needs no depth in the on-screen buffer
		The5_ApplicationDesc.primaryWindowDesc.allowResize = true;

		// List of importer plugins we plan on using for importing various resources
		The5_ApplicationDesc.importers.push_back("BansheeFreeImgImporter"); // For importing textures
		The5_ApplicationDesc.importers.push_back("BansheeFBXImporter"); // For importing meshes
		The5_ApplicationDesc.importers.push_back("BansheeFontImporter"); // For importing fonts
		The5_ApplicationDesc.importers.push_back("BansheeSL"); // For importing shaders);

		return The5_ApplicationDesc;
	}

	bs::SPtr<RenderSettings> The5Application::defaultRenderSettings()
	{
		SPtr<RenderSettings> settings = bs_shared_ptr_new<RenderSettings>();
		settings->enableLighting = true;
		settings->enableIndirectLighting = false; //without this everything is black if you dont place lights manually
		settings->enableShadows = false;
		settings->enableAutoExposure = false;
		settings->enableFXAA = false;
		settings->enableHDR = false;
		settings->enableTonemapping = false;
		ScreenSpaceReflectionsSettings ssr_settings;
		ssr_settings.enabled = false;
		settings->screenSpaceReflections = ssr_settings;
		AmbientOcclusionSettings ao_settings;
		ao_settings.enabled = false;
		settings->ambientOcclusion = ao_settings;
		ColorGradingSettings color_settings;
		color_settings.saturation = 0.0f;
		color_settings.contrast = 0.0f;
		color_settings.gain = 0.0f;
		color_settings.offset = 0.0f;
		settings->colorGrading = color_settings;

		return settings;
	}

	void The5Application::start()
	{
		Application::startUp<The5Application>(The5Application::defaultStartupDesc());
	}

	void The5Application::initUtilityOnly()
	{
		initDefaultKeyBindings();

		initDefaultAssets();

		initMainCamera();

		initGUI();

		initCallbacks();
	}

	void The5Application::onStartUp()
	{
		gDebug().logDebug("Starting Banshee Engine...");
		Application::onStartUp(); //init banshee first!
		gDebug().logDebug("Banshee Engine started.");

		initDefaultKeyBindings();

		initDefaultAssets();

		initMainCamera();

		initGUI();

		initCallbacks();
	}

	void The5Application::onShutDown()
	{
		// Do your own shut-down (i.e. shut down your custom systems, autossave)

		Application::onShutDown(); //shut down banshee last
	}

	void The5Application::preUpdate()
	{
		Application::preUpdate();
	}

	void The5Application::postUpdate()
	{	
		Application::postUpdate();
	}

//------------------------------------- Renderer --------------------------------------
	void The5Application::initRenderer()
	{
		
	}

//-------------------------------------- Camera ---------------------------------------

	void The5Application::initMainCamera()
	{
		this->mMainCameraSO = SceneObject::create("Main Camera");
		this->mMainCameraC = mMainCameraSO->addComponent<CCamera>();
		mMainCameraC->setMain(true);
		mMainCameraC->setRenderSettings(The5Application::defaultRenderSettings());


		mMainCameraSO->setPosition(Vector3(8.0, 1.0f, 0.0f));
		mMainCameraSO->lookAt(Vector3(0.0, 3.0, 0.0));

		SPtr<RenderWindow> window = gApplication().getPrimaryWindow();
		const RenderWindowProperties& windowProps = window->getProperties();
		mMainCameraC->getViewport()->setTarget(window);	// Set the camera to draw to the main window

		/// Set up camera component properties
		//mMainCameraC->setPriority(1); //priority when multiple cameras write to the same buffer (e.g. GUI camera over main window)
		mMainCameraC->setNearClipDistance(9.9f);
		mMainCameraC->setFarClipDistance(10.0f);
		mMainCameraC->setAspectRatio(windowProps.width / (float)windowProps.height);
		mMainCameraC->setMSAACount(1); //needs to be at least 1!!!

		/// Add Components
		mMainCameraSO->addComponent<CameraFlyer>();
	}

	void The5Application::initGUI()
	{
		this->mGUI_SO = SceneObject::create("GUI Camera");
		this->mGUI_CameraC = mGUI_SO->addComponent<CCamera>();
	
		SPtr<RenderWindow> window = gApplication().getPrimaryWindow();
		const RenderWindowProperties& windowProps = window->getProperties();
		mGUI_CameraC->getViewport()->setTarget(window);	// Set the camera to draw to the main window


		/// Set up camera component properties
		// Notify the renderer that the camera will only be used for overlays (e.g. GUI) so it can optimize its usage
		SPtr<RenderSettings> settings = mGUI_CameraC->getRenderSettings();
		settings->overlayOnly = true;
		//render order for multiple cameras writing to the same buffer, 0 for gui
		mGUI_CameraC->setPriority(0);
		// We don't care about aspect ratio for GUI camera.
		mGUI_CameraC->setAspectRatio(1.0f);
		// This camera should ignore any Renderable objects in the scene
		mGUI_CameraC->setLayers(0);
		// Don't clear this camera as that would clear anything the main camera has rendered.
		mGUI_CameraC->getViewport()->setClearFlags(ClearFlagBits::Empty);

		///Add Profiler Component
		HProfilerOverlay profilerOverlay = mGUI_SO->addComponent<CProfilerOverlay>(mGUI_CameraC->_getCamera());
		profilerOverlay->show(ProfilerOverlayType::GPUSamples);
		profilerOverlay->hide();

		///Setup GUI Widget with main Panel
		// Add a GUIWidget, the top-level GUI component, parent to all GUI elements. GUI widgets
		// require you to specify a viewport that they will output rendered GUI elements to.
		HGUIWidget mGUI_Widget = mGUI_SO->addComponent<CGUIWidget>(mGUI_CameraC);
		// GUI skin defines how are all child elements of the GUI widget renderered. It contains all their styles
		// and default layout properties. We use the default skin that comes built into Banshee.
		mGUI_Widget->setSkin(BuiltinResources::instance().getGUISkin());
		// Depth allows you to control how is a GUI widget rendered in relation to other widgets
		// Lower depth means the widget will be rendered in front of those with higher. In this case we just
		// make the depth mid-range as there are no other widgets.
		mGUI_Widget->setDepth(128);

		///GUI Layout
		//The GUIPanel class has no automatic layouting, create a GUILayoutX or GUILayoutX first
		GUILayout* layoutY = mGUI_Widget->getPanel()->addNewElement<GUILayoutY>();
		GUILayout* topRow = layoutY->addNewElement<GUILayoutX>();
		topRow->setHeight(22);
		GUILayout* centerRow = layoutY->addNewElement<GUILayoutX>();
		GUILayout* bottomRow = layoutY->addNewElement<GUILayoutX>();
		bottomRow->setHeight(22);

		GUILayout* leftSide = centerRow->addNewElement<GUILayoutY>();
		leftSide->setWidth(120);
		centerRow->addNewElement<GUIFlexibleSpace>(); //viewport
		GUILayout* rightSide = centerRow->addNewElement<GUILayoutY>();
		rightSide->setWidth(120);


		topRow->addElement(GUIButton::create(HString(L"Button Top 1")));
		topRow->addElement(GUIButton::create(HString(L"Button Top 2")));
		topRow->addElement(GUIButton::create(HString(L"Button Top 3")));

		bottomRow->addElement(GUIButton::create(HString(L"Button Bottom 1")));
		bottomRow->addElement(GUIButton::create(HString(L"Button Bottom 2")));
		bottomRow->addElement(GUIButton::create(HString(L"Button Bottom 3")));

		leftSide->addElement(GUIButton::create(HString(L"Button L 1")));
		leftSide->addElement(GUIButton::create(HString(L"Button L 2")));
		leftSide->addElement(GUIButton::create(HString(L"Button L 3")));

		rightSide->addElement(GUIButton::create(HString(L"Button R 1")));
		rightSide->addElement(GUIButton::create(HString(L"Button R 2")));
		rightSide->addElement(GUIButton::create(HString(L"Button R 3")));

		/*
		GUILayout* layoutX = mGUI_Widget->getPanel()->addNewElement<GUILayoutX>();
		GUILayout* sideBarL = layoutX->addNewElement<GUILayoutY>();
		sideBarL->addNewElement<GUIFlexibleSpace>();
		sideBarL->addElement(GUIButton::create(HString(L"Side L Button 1")));
		sideBarL->addElement(GUIButton::create(HString(L"Side L Button 2")));
		sideBarL->addElement(GUIButton::create(HString(L"Side L Button 3")));
		layoutX->addNewElement<GUIFlexibleSpace>();
		GUILayout* sideBarR = layoutX->addNewElement<GUILayoutY>();
		sideBarR->addElement(GUIButton::create(HString(L"Side R Button 1")));
		sideBarR->addElement(GUIButton::create(HString(L"Side R Button 2")));
		sideBarR->addElement(GUIButton::create(HString(L"Side R Button 3")));

		GUILayout* layoutY = mGUI_Widget->getPanel()->addNewElement<GUILayoutY>();
		layoutY->addNewElement<GUIFlexibleSpace>();
		GUILayout* bottomBar = layoutY->addNewElement<GUILayoutX>();
		bottomBar->addElement(GUIButton::create(HString(L"Bottom Button 1")));
		bottomBar->addElement(GUIButton::create(HString(L"Bottom Button 2")));
		bottomBar->addElement(GUIButton::create(HString(L"Bottom Button 3")));
		*/


	}

//-------------------------------------- Input ----------------------------------------

	void The5Application::initDefaultKeyBindings()
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

//------------------------------------- Callbacks -------------------------------------

	void The5Application::initCallbacks()
	{
		//http://docs.banshee3d.com/Native/events.html "Class methods as event callbacks" ---> std::bind to bind the this-pointer into the callback

		///------------ Window Events ------------------
		SPtr<RenderWindow> window = gApplication().getPrimaryWindow();
		//Resize
		window->onResized.connect(std::bind(&The5Application::windowResizeCallback, this));

		///... Events
	}

	void The5Application::windowResizeCallback()
	{
		SPtr<RenderWindow> window = gApplication().getPrimaryWindow(); //shared poitner will be deleted when this goes out of scope
		const RenderWindowProperties& windowProps = window->getProperties();

		//Window Resize
		//recalculate Camera Aspect Ratio
		if(mMainCameraC != nullptr) mMainCameraC->setAspectRatio(windowProps.width / (float)windowProps.height);
		//resize FBOs
		//...
	}

//--------------------------------- static access points ------------------------------

	The5Application& The5Application::get()
	{
		//I need to get the instance by pointer, since I can't cast a object! Then dereference with *
		return *static_cast<The5Application*>(Application::instancePtr());
	}

	bs::HCamera& The5Application::mainCamera()
	{
		return The5Application::get().mMainCameraC;
	}

//-------------------------------------- Assets -------------------------------------
	
	void The5Application::initDefaultAssets()
	{
		gDebug().logDebug("Loading Default Assets...");
		defaultPBRShader = BuiltinResources::instance().getBuiltinShader(BuiltinShader::Standard);
		defaultPBRMaterial = Material::create(defaultPBRShader);

		HTexture defaultTexture_Albedo = loadTexture(TEX_ALBEDO.c_str());
		HTexture defaultTexture_Normals = loadTexture(TEX_NORMAL.c_str());
		HTexture defaultTexture_Roughness = loadTexture(TEX_ROUGHNESS.c_str());
		HTexture defaultTexture_Metalness = loadTexture(TEX_METALNESS.c_str());

		defaultPBRMaterial->setTexture("gAlbedoTex", defaultTexture_Albedo);
		defaultPBRMaterial->setTexture("gNormalTex", defaultTexture_Normals);
		defaultPBRMaterial->setTexture("gRoughnessTex", defaultTexture_Roughness);
		defaultPBRMaterial->setTexture("gMetalnessTex", defaultTexture_Metalness);

		defaultCube = The5Application::loadMesh(MESH_CUBE.c_str());
		defaultSphere = The5Application::loadMesh(MESH_SPHERE.c_str());
		defaultPlane = The5Application::loadMesh(MESH_PLANE.c_str());

		gDebug().logDebug("Done loading Default Assets.");
	}
	
	bs::HMesh The5Application::loadMesh(const bs::Path& originalFilePath, float scale, bool forceInport)
	{
		const bool debugPrint = _showImportDebug;
		Path assetPath = originalFilePath;
		assetPath.setExtension(originalFilePath.getExtension() + ".asset");

		//Try loading existing exported Asset
		if(debugPrint) Debug().logDebug("Trying to loading existing .asset from " + bs::toString(assetPath.toPlatformString()) + " ...");
		HMesh model = gResources().load<Mesh>(assetPath);
		if (model == nullptr || forceInport == true || _forceRebuildAssetOnInport == true) // If Mesh file doesn't exist, import from the source file.
		{
			if(debugPrint) gDebug().logDebug("Existing .asset not found, importing mesh from " + bs::toString(originalFilePath.toPlatformString()));
			// When importing you may specify optional import options that control how is the asset imported.
			SPtr<ImportOptions> meshImportOptions = Importer::instance().createImportOptions(originalFilePath);

			// rtti_is_of_type checks if the import options are of valid type, in case the provided path is pointing to a
			// non-mesh resource. This is similar to dynamic_cast but uses Banshee internal RTTI system for type checking.
			if (rtti_is_of_type<MeshImportOptions>(meshImportOptions))
			{
				MeshImportOptions* importOptions = static_cast<MeshImportOptions*>(meshImportOptions.get());

				importOptions->setImportScale(scale);
			}

			model = gImporter().import<Mesh>(originalFilePath, meshImportOptions);

			// Save for later use, so we don't have to import on the next run.
			if(debugPrint) gDebug().logDebug("Saving .asset to " + bs::toString(assetPath.toPlatformString()));
			gResources().save(model, assetPath, true);
		}
		else
		{
			if(debugPrint) gDebug().logDebug("Existing .asset loaded.");
		}

		return model;
	}

	bs::HTexture The5Application::loadTexture(const bs::Path & originalFilePath, bool isSRGB, bool isCubemap, bool isHDR, bool forceInport)
	{
		const bool debugPrint = _showImportDebug;
		Path assetPath = originalFilePath;
		assetPath.setExtension(originalFilePath.getExtension() + ".asset");

		if (debugPrint) gDebug().logDebug("Trying to loading existing .asset from " + bs::toString(assetPath.toPlatformString()) + " ...");
		HTexture texture = gResources().load<Texture>(assetPath);
		if (texture == nullptr || forceInport == true || _forceRebuildAssetOnInport == true) // Texture file doesn't exist, import from the source file.
		{
			if (debugPrint) gDebug().logDebug("Existing .asset not found, importing texture from " + bs::toString(originalFilePath.toPlatformString()));
			// When importing you may specify optional import options that control how is the asset imported.
			SPtr<ImportOptions> textureImportOptions = Importer::instance().createImportOptions(originalFilePath);

			// rtti_is_of_type checks if the import options are of valid type, in case the provided path is pointing to a 
			// non-texture resource. This is similar to dynamic_cast but uses Banshee internal RTTI system for type checking.
			if (rtti_is_of_type<TextureImportOptions>(textureImportOptions))
			{
				TextureImportOptions* importOptions = static_cast<TextureImportOptions*>(textureImportOptions.get());

				// We want maximum number of mipmaps to be generated
				importOptions->setGenerateMipmaps(true);

				// If the texture is in sRGB space the system needs to know about it
				importOptions->setSRGB(isSRGB);

				// Ensures we can save the texture contents
				importOptions->setCPUCached(true);

				// Import as cubemap if needed
				importOptions->setIsCubemap(isCubemap);

				// If importing as cubemap, assume source is a panorama
				importOptions->setCubemapSourceType(CubemapSourceType::Cylindrical);

				// Importing using a HDR format if requested
				if (isHDR) importOptions->setFormat(PF_RG11B10F);

			}

			// Import texture with specified import options
			texture = gImporter().import<Texture>(originalFilePath, textureImportOptions);

			// Save for later use, so we don't have to import on the next run.
			if (debugPrint) gDebug().logDebug("Saving .asset to " + bs::toString(assetPath.toPlatformString()));
			gResources().save(texture, assetPath, true);
		}
		else
		{
			if (debugPrint) gDebug().logDebug("Existing .asset loaded.");
		}

		return texture;
	}

	bs::HMaterial& The5Application::getDefaultPBRMaterial()
	{
		return The5Application::get().defaultPBRMaterial;
	}

	bs::HMesh & The5Application::getDefaultCube()
	{
		return The5Application::get().defaultCube;
	}

	bs::HMesh & The5Application::getDefaultSphere()
	{
		return The5Application::get().defaultSphere;
	}

	bs::HMesh & The5Application::getDefaultPlane()
	{
		return The5Application::get().defaultPlane;
	}

}
