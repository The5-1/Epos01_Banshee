#pragma once

#include "ForwardDeclarations.h"
#include "include_Banshee.h"

namespace The5 {

	class DefaultAssets
	{
	public:
		static void init();

		///Meshes
		static bs::HMesh defaultCube;
		static bs::HMesh defaultSphere;
		static bs::HMesh defaultPlane;

		static bs::HMesh defaultSponza;

		///Textures
		static bs::HTexture defaultUVchecker;

		static bs::HTexture defaultSkybox;

		static bs::HTexture defaultTexture_Albedo;
		static bs::HTexture defaultTexture_Normals;
		static bs::HTexture defaultTexture_Roughness;
		static bs::HTexture defaultTexture_Metalness;

		///Shader and Material
		static bs::HShader defaultPBRShader;
		static bs::HMaterial defaultPBRMaterial;

	};
}