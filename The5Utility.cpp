#include "The5Utility.h"

#include "The5Config.h"
#include "include_Banshee.h"

using namespace bs;

namespace The5 {
	namespace Utility
	{
		bs::Path convertPathToBansheeAssetDir(const bs::Path& originalFilePath, const std::string& typeFolder)
		{		
			Path filename = originalFilePath.getFilename(true);

			std::string bansheepath = std::string(The5::GLOBAL_ASSET_BANSHEE_PATH + typeFolder);
			Path bansheeAssetPath = bansheepath.c_str();
			bansheeAssetPath.append(filename);
			bansheeAssetPath.setExtension(originalFilePath.getExtension() + ".asset");
			//std::wcout << bansheeAssetPath.toWString() << std::endl;
			return bansheeAssetPath;
		}


		bs::HMesh loadMesh(const bs::Path& originalFilePath, float scale, bool forceInport)
		{
			bool debugPrint = The5::Utility::showImportDebug;
			bool forcedInportActive = (forceInport == true || The5::Utility::forceRebuildAssetOnImport == true);

			Path assetPath = convertPathToBansheeAssetDir(originalFilePath,"Meshes");

			HMesh model = gResources().load<Mesh>(assetPath);
			if (model == nullptr || forcedInportActive) // If Mesh file doesn't exist, import from the source file.
			{
				if (debugPrint && model == nullptr) gDebug().logDebug("Existing .asset file not found!");
				else if (debugPrint && forcedInportActive) gDebug().logDebug("Forced re-import of raw mesh!");
				if (debugPrint) gDebug().logDebug("Inporting mesh from " + bs::toString(originalFilePath.toPlatformString()));
				// When importing you may specify optional import options that control how is the asset imported.
				SPtr<ImportOptions> meshImportOptions = Importer::instance().createImportOptions(originalFilePath);

				// rtti_is_of_type checks if the import options are of valid type, in case the provided path is pointing to a
				// non-mesh resource. This is similar to dynamic_cast but uses Banshee internal RTTI system for type checking.
				if (rtti_is_of_type<MeshImportOptions>(meshImportOptions))
				{
					MeshImportOptions* importOptions = static_cast<MeshImportOptions*>(meshImportOptions.get());
					importOptions->setImportScale(scale);

					model = gImporter().import<Mesh>(originalFilePath, meshImportOptions);

					if (debugPrint) gDebug().logDebug("Model dimensions: " + bs::toString(model->getProperties().getBounds().getBox().getSize()));

					// Save for later use, so we don't have to import on the next run.
					if (debugPrint) gDebug().logDebug("Saving .asset to " + bs::toString(assetPath.toPlatformString()));
					gResources().save(model, assetPath, true);
				}
				else
				{
					gDebug().logWarning("The provided path is pointing to a non-mesh resource!");
				}
			}
			else
			{
				if (debugPrint) gDebug().logDebug("Existing .asset loaded.");
			}

			return model;
		}

		bs::HTexture loadTexture(const bs::Path & originalFilePath, bool isSRGB, bool isCubemap, bool isHDR, bool forceInport)
		{
			const bool debugPrint = The5::Utility::showImportDebug;
			Path assetPath = convertPathToBansheeAssetDir(originalFilePath,"Textures");

			if (debugPrint) gDebug().logDebug("Trying to loading existing .asset from " + bs::toString(assetPath.toPlatformString()) + " ...");
			HTexture texture = gResources().load<Texture>(assetPath);
			if (texture == nullptr || forceInport == true || The5::Utility::forceRebuildAssetOnImport == true) // Texture file doesn't exist, import from the source file.
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

					// Import texture with specified import options
					texture = gImporter().import<Texture>(originalFilePath, textureImportOptions);

					// Save for later use, so we don't have to import on the next run.
					if (debugPrint) gDebug().logDebug("Saving .asset to " + bs::toString(assetPath.toPlatformString()));
					gResources().save(texture, assetPath, true);

				}
				else
				{
					gDebug().logWarning("The provided path is pointing to a non-texture resource!");
				}

			}
			else
			{
				if (debugPrint) gDebug().logDebug("Existing .asset loaded.");
			}

			return texture;
		}
	}
}