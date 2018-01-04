#pragma once

#include <string>

namespace The5
{
	///Global Paths
	const std::string PROJECT_PATH = "D:/Dev/BansheeEngine/Build/Examples/Epos01_Banshee/";

	const std::string LOCAL_ASSET_PATH = PROJECT_PATH + "Assets/";
	const std::string GLOBAL_ASSET_PATH = "D:/Dev/Assets/";
	const std::string GLOBAL_ASSET_BANSHEE_PATH = GLOBAL_ASSET_PATH + "Banshee/";

	const std::string SHADER_PATH = GLOBAL_ASSET_PATH + "Shaders/";
	const std::string DEFAULT_SHADER_VERT = SHADER_PATH + "default.vert.glsl";
	const std::string DEFAULT_SHADER_FRAG = SHADER_PATH + "default.frag.glsl";

	const std::string GLOBAL_MESH_PATH = GLOBAL_ASSET_PATH + "Meshes/";
	const std::string GLOBAL_TEXTURE_PATH = GLOBAL_ASSET_PATH + "Textures/";


	///Global Sample Assets

	const std::string TEX_UVCHECKER = GLOBAL_TEXTURE_PATH + "UVchecker01.png";
	
	const std::string TEX_SKYBOX = GLOBAL_TEXTURE_PATH + "Environment/PaperMill_E_3k.hdr";


	const std::string TEX_ALBEDO = GLOBAL_TEXTURE_PATH + "Gray50.png";
	const std::string TEX_NORMAL = GLOBAL_TEXTURE_PATH + "Normal.png";
	const std::string TEX_ROUGHNESS = GLOBAL_TEXTURE_PATH + "Gray50.png";
	const std::string TEX_METALNESS = GLOBAL_TEXTURE_PATH + "Gray00.png";

	const std::string TEX_SOFA_ALBEDO = GLOBAL_TEXTURE_PATH + "sofa_albedo.png";
	const std::string TEX_SOFA_NORMAL = GLOBAL_TEXTURE_PATH + "sofa_normal.png";
	const std::string TEX_SOFA_ROUGHNESS = GLOBAL_TEXTURE_PATH + "sofa_roughness.png";
	const std::string TEX_SOFA_METALNESS = GLOBAL_TEXTURE_PATH + "sofa_metalness.png";

	const std::string MESH_CUBE = GLOBAL_MESH_PATH + "Cube.obj";
	const std::string MESH_SPHERE = GLOBAL_MESH_PATH + "Sphere.obj";
	const std::string MESH_PLANE = GLOBAL_MESH_PATH + "Plane.obj";

	const std::string MESH_SPONZA = GLOBAL_ASSET_PATH + "Sponza_Atrium_Png/sponza.obj";


}
