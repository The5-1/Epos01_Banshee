#pragma once

#include <string>

namespace The5
{
	///Global Paths
	const std::string PROJECT_PATH = "D:/Dev/BansheeEngine/Build/Examples/Epos01_Banshee/";

	const std::string LOCAL_ASSET_PATH = PROJECT_PATH + "Assets/";
	const std::string GLOBAL_ASSET_PATH = "D:/Dev/Assets/";

	const std::string SHADER_PATH = GLOBAL_ASSET_PATH + "Shaders/";
	const std::string DEFAULT_SHADER_VERT = SHADER_PATH + "default.vert.glsl";
	const std::string DEFAULT_SHADER_FRAG = SHADER_PATH + "default.frag.glsl";

	const std::string GLOBAL_MESH_PATH = GLOBAL_ASSET_PATH + "Meshes/";
	const std::string GLOBAL_TEXTURE_PATH = GLOBAL_ASSET_PATH + "Textures/";


	///Global Sample Assets
	const std::string SPONZA_FBX = GLOBAL_ASSET_PATH + "Sponza_Atrium_Png/sponza.FBX";
	const std::string SPONZA_OBJ = GLOBAL_ASSET_PATH + "Sponza_Atrium_Png/sponza.obj";

	const std::string TEX_UVCHECKER = GLOBAL_TEXTURE_PATH + "UVchecker01.png";
	const std::string TEX_ALBEDO = GLOBAL_TEXTURE_PATH + "sofa_albedo.png";
	const std::string TEX_NORMAL = GLOBAL_TEXTURE_PATH + "sofa_normal.png";
	const std::string TEX_ROUGHNESS = GLOBAL_TEXTURE_PATH + "sofa_roughness.png";
	const std::string TEX_METALNESS = GLOBAL_TEXTURE_PATH + "sofa_metalness.png";

	const std::string MESH_CUBE = GLOBAL_MESH_PATH + "Cube.FBX";
	const std::string MESH_SPHERE = GLOBAL_MESH_PATH + "Sphere.FBX";


	const std::string SKYBOX = GLOBAL_TEXTURE_PATH + "Environment/PaperMill_E_3k.hdr";
}
