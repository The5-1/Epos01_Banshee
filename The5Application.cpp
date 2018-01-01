#include "The5Application.h"

#include "include_STL.h"
#include "The5_config.h"

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

		// Use default values as specified by the build system
		The5_ApplicationDesc.renderAPI = BS_RENDER_API_MODULE;
		The5_ApplicationDesc.renderer = BS_RENDERER_MODULE;
		The5_ApplicationDesc.audio = BS_AUDIO_MODULE;
		The5_ApplicationDesc.physics = BS_PHYSICS_MODULE;

		// Descriptor used for initializing the primary application window.
		The5_ApplicationDesc.primaryWindowDesc.videoMode = bs::VideoMode(1280,720);
		The5_ApplicationDesc.primaryWindowDesc.title = "Epos";
		The5_ApplicationDesc.primaryWindowDesc.fullscreen = false;
		The5_ApplicationDesc.primaryWindowDesc.depthBuffer = true; //deferred quad needs no depth in the on-screen buffer

		// List of importer plugins we plan on using for importing various resources
		The5_ApplicationDesc.importers.push_back("BansheeFreeImgImporter"); // For importing textures
		The5_ApplicationDesc.importers.push_back("BansheeFBXImporter"); // For importing meshes
		The5_ApplicationDesc.importers.push_back("BansheeFontImporter"); // For importing fonts
		The5_ApplicationDesc.importers.push_back("BansheeSL"); // For importing shaders);

		return The5_ApplicationDesc;
	}

	void The5Application::start()
	{
		Application::startUp<The5Application>(The5Application::defaultStartupDesc());
	}

	void The5Application::onStartUp()
	{
		gDebug().logDebug("Starting Banshee Engine...");
		Application::onStartUp(); //init banshee first!
		gDebug().logDebug("Banshee Engine started.");

		initDefaultKeyBindings();

		initDefaultAssets();

		initCallbacks();

		initMainCamera();
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

//-------------------------------------- Camera ---------------------------------------

	void The5Application::initMainCamera()
	{
		this->mMainCameraSO = SceneObject::create("Main Camera");
		this->mMainCameraC = mMainCameraSO->addComponent<CCamera>();

		SPtr<RenderWindow> window = gApplication().getPrimaryWindow();
		const RenderWindowProperties& windowProps = window->getProperties();

		mMainCameraC->getViewport()->setTarget(window);	// Set the camera to draw to the main window

		/// Set up camera component properties
		mMainCameraC->setPriority(1); //priority when multiple cameras write to the same buffer (e.g. GUI camera over main window)
		mMainCameraC->setNearClipDistance(0.005f);
		mMainCameraC->setFarClipDistance(1000.0f);
		mMainCameraC->setAspectRatio(windowProps.width / (float)windowProps.height);
		mMainCameraC->setMSAACount(0);

		/// Add Components
		mMainCameraSO->addComponent<CameraFlyer>();

		mMainCameraSO->setPosition(Vector3(0.0f, 0.0f, 1.0f));
		mMainCameraSO->lookAt(Vector3(0, 0, 0));
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
		inputConfig->registerButton("Back", BC_BACK);
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

		///Window Events
		SPtr<RenderWindow> window = gApplication().getPrimaryWindow();
		//Resize
		window->onResized.connect(std::bind(&The5Application::windowResizeCallback, this));

		///... Events
	}

	void The5Application::windowResizeCallback()
	{
		SPtr<RenderWindow> window = gApplication().getPrimaryWindow(); //shared poitner will be deleted when this goes out of scope
		const RenderWindowProperties& windowProps = window->getProperties();

		//recalculate Camera Aspect Ratio
		if(mMainCameraC != nullptr) mMainCameraC->setAspectRatio(windowProps.width / (float)windowProps.height);

		//resize FBOs
		//TODO
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

		gDebug().logDebug("Done loading Default Assets.");
	}
	
	bs::HMesh The5Application::loadMesh(const bs::Path& originalFilePath, float scale)
	{
		Path assetPath = originalFilePath;
		assetPath.setExtension(originalFilePath.getExtension() + ".asset");

		//Try loading existing exported Asset
		gDebug().logDebug("Trying to loading existing .asset from " + bs::toString(assetPath.toPlatformString()) + " ...");
		HMesh model = gResources().load<Mesh>(assetPath);
		if (model == nullptr) // If Mesh file doesn't exist, import from the source file.
		{
			gDebug().logDebug("Existing .asset not found, importing mesh from " + bs::toString(originalFilePath.toPlatformString()));
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
			gDebug().logDebug("Saving .asset to " + bs::toString(assetPath.toPlatformString()));
			gResources().save(model, assetPath, true);
		}
		else
		{
			gDebug().logDebug("Existing .asset loaded.");
		}

		return model;
	}

	bs::HTexture The5Application::loadTexture(const bs::Path & originalFilePath, bool isSRGB, bool isCubemap, bool isHDR)
	{
		Path assetPath = originalFilePath;
		assetPath.setExtension(originalFilePath.getExtension() + ".asset");

		gDebug().logDebug("Trying to loading existing .asset from " + bs::toString(assetPath.toPlatformString()) + " ...");
		HTexture texture = gResources().load<Texture>(assetPath);
		if (texture == nullptr) // Texture file doesn't exist, import from the source file.
		{
			gDebug().logDebug("Existing .asset not found, importing texture from " + bs::toString(originalFilePath.toPlatformString()));
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
			gDebug().logDebug("Saving .asset to " + bs::toString(assetPath.toPlatformString()));
			gResources().save(texture, assetPath, true);
		}
		else
		{
			gDebug().logDebug("Existing .asset loaded.");
		}

		return texture;
	}


	bs::HMaterial& The5Application::getDefaultPBRMaterial()
	{
		return The5Application::get().defaultPBRMaterial;
	}

}
