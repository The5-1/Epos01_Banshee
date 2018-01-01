#include "BansheeHelper.h"

///Cusom Components
#include "CameraFlyer.h"

using namespace bs;

namespace The5
{
	
	void BansheeHelper::checkMesh(bs::HMesh mesh)
	{
		//gDebug().logDebug("Num. vertices: " + toString(props.getNumVertices()));
		//gDebug().logDebug("Num. indices: " + toString(props.getNumIndices()));
		//gDebug().logDebug("Radius: " + toString(props.getBounds().getSphere().getRadius()));
	}

	HMesh& BansheeHelper::loadMesh(Path path, float scale)
	{
		Path assetPath = path;
		assetPath.setExtension(path.getExtension() + ".asset");

		HMesh model = gResources().load<Mesh>(assetPath);
		if (model == nullptr) // Mesh file doesn't exist, import from the source file.
		{
			// When importing you may specify optional import options that control how is the asset imported.
			SPtr<ImportOptions> meshImportOptions = Importer::instance().createImportOptions(path);

			// rtti_is_of_type checks if the import options are of valid type, in case the provided path is pointing to a
			// non-mesh resource. This is similar to dynamic_cast but uses Banshee internal RTTI system for type checking.
			if (rtti_is_of_type<MeshImportOptions>(meshImportOptions))
			{
				MeshImportOptions* importOptions = static_cast<MeshImportOptions*>(meshImportOptions.get());

				importOptions->setImportScale(scale);
			}

			model = gImporter().import<Mesh>(path, meshImportOptions);

			// Save for later use, so we don't have to import on the next run.
			gResources().save(model, assetPath, true);
		}

		return model;
	}

	HTexture& BansheeHelper::loadTexture(Path path, bool isSRGB, bool isCubemap, bool isHDR)
	{
		Path assetPath = path;
		assetPath.setExtension(path.getExtension() + ".asset");

		HTexture texture = gResources().load<Texture>(assetPath);
		if (texture == nullptr) // Texture file doesn't exist, import from the source file.
		{
			// When importing you may specify optional import options that control how is the asset imported.
			SPtr<ImportOptions> textureImportOptions = Importer::instance().createImportOptions(path);

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
				if (isHDR)
					importOptions->setFormat(PF_RG11B10F);
			}

			// Import texture with specified import options
			texture = gImporter().import<Texture>(path, textureImportOptions);

			// Save for later use, so we don't have to import on the next run.
			gResources().save(texture, assetPath, true);
		}

		return texture;
	}

	/*
	HSceneObject* BansheeHelper::createCamera(std::string name, bs::UINT32 width, bs::UINT32 height, float near, float far, bs::UINT32 masaa)
	{
		
		BansheeHelper::mainCameraSO = SceneObject::create(name.c_str());
		BansheeHelper::mMainCameraC = cameraSO->addComponent<CCamera>();

		SPtr<RenderWindow> window = gApplication().getPrimaryWindow();

		// Add a Camera component that will output whatever it sees into that window 
		// (You could also use a render texture or another window you created).
		BansheeHelper::mMainCameraC->getViewport()->setTarget(window);

		/// Set up camera component properties
		// Set closest distance that is visible. Anything below that is clipped.
		BansheeHelper::mMainCameraC->setNearClipDistance(near);
		// Set farthest distance that is visible. Anything above that is clipped.
		BansheeHelper::mMainCameraC->setFarClipDistance(far);
		// Set aspect ratio depending on the current resolution
		BansheeHelper::mMainCameraC->setAspectRatio(width / (float)height);
		// camera multi-sample anti-aliasing for better quality
		BansheeHelper::mMainCameraC->setMSAACount(masaa);
		// Add a CameraFlyer component that allows us to move the camera. See CameraFlyer for more information.
		BansheeHelper::mainCameraSO->addComponent<CameraFlyer>();
		// Position and orient the camera scene object
		BansheeHelper::mainCameraSO->setPosition(Vector3(0.0f, 0.0f, 1.0f));
		BansheeHelper::mainCameraSO->lookAt(Vector3(0, 0, 0));
		
		return &mainCameraSO;
	}

	void BansheeHelper::renderWindowResizedCallback()
	{
		SPtr<RenderWindow> window = gApplication().getPrimaryWindow();
		const RenderWindowProperties& rwProps = window->getProperties();

		BansheeHelper::Window_Width = rwProps.width;
		BansheeHelper::Window_Height = rwProps.height;

		mMainCameraC->setAspectRatio(Window_Width / (float)Window_Height);
	}
	*/
}
