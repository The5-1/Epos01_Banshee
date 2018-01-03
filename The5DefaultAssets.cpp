#include "The5DefaultAssets.h"
#include "The5Utility.h"

#include "The5Config.h"

using namespace bs;

namespace The5 
{
	bs::HShader DefaultAssets::defaultPBRShader;
	bs::HMaterial DefaultAssets::defaultPBRMaterial;

	bs::HTexture DefaultAssets::defaultTexture_Albedo;
	bs::HTexture DefaultAssets::defaultTexture_Normals;
	bs::HTexture DefaultAssets::defaultTexture_Roughness;
	bs::HTexture DefaultAssets::defaultTexture_Metalness;

	bs::HTexture DefaultAssets::defaultSkybox;

	bs::HTexture DefaultAssets::defaultUVchecker;

	bs::HMesh DefaultAssets::defaultCube;
	bs::HMesh DefaultAssets::defaultSphere;
	bs::HMesh DefaultAssets::defaultPlane;
	bs::HMesh DefaultAssets::defaultSponza;


	void DefaultAssets::init()
	{
		gDebug().logDebug("Loading Default Assets...");

		///Meshes
		The5::DefaultAssets::defaultCube = The5::Utility::loadMesh(MESH_CUBE.c_str());
		The5::DefaultAssets::defaultSphere = The5::Utility::loadMesh(MESH_SPHERE.c_str());
		The5::DefaultAssets::defaultPlane = The5::Utility::loadMesh(MESH_PLANE.c_str());

		The5::DefaultAssets::defaultSponza = The5::Utility::loadMesh(MESH_SPONZA.c_str());

		///Textures
		The5::DefaultAssets::defaultTexture_Albedo = The5::Utility::loadTexture(TEX_ALBEDO.c_str());
		The5::DefaultAssets::defaultTexture_Normals = The5::Utility::loadTexture(TEX_NORMAL.c_str());
		The5::DefaultAssets::defaultTexture_Roughness = The5::Utility::loadTexture(TEX_ROUGHNESS.c_str());
		The5::DefaultAssets::defaultTexture_Metalness = The5::Utility::loadTexture(TEX_METALNESS.c_str());
		
		The5::DefaultAssets::defaultSkybox = The5::Utility::loadTexture(TEX_SKYBOX.c_str(), false, true, true);

		The5::DefaultAssets::defaultUVchecker = The5::Utility::loadTexture(TEX_UVCHECKER.c_str());
		///Shader & Materials
		The5::DefaultAssets::defaultPBRShader = BuiltinResources::instance().getBuiltinShader(BuiltinShader::Standard);
		The5::DefaultAssets::defaultPBRMaterial = Material::create(defaultPBRShader);
		The5::DefaultAssets::defaultPBRMaterial->setTexture("gAlbedoTex", defaultTexture_Albedo);
		The5::DefaultAssets::defaultPBRMaterial->setTexture("gNormalTex", defaultTexture_Normals);
		The5::DefaultAssets::defaultPBRMaterial->setTexture("gRoughnessTex", defaultTexture_Roughness);
		The5::DefaultAssets::defaultPBRMaterial->setTexture("gMetalnessTex", defaultTexture_Metalness);

		

		gDebug().logDebug("Done loading Default Assets.");
	}
}
