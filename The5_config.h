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

	const std::string MESH_PATH = GLOBAL_ASSET_PATH + "Meshes/";
	const std::string TEXTURE_PATH = GLOBAL_ASSET_PATH + "Textures/";


	///Global Sample Assets
	const std::string SPONZA_FBX = GLOBAL_ASSET_PATH + "Sponza_Atrium_Png/sponza.FBX";
	const std::string SPONZA_OBJ = GLOBAL_ASSET_PATH + "Sponza_Atrium_Png/sponza.obj";

	const std::string UVCHECKER01_PNG = TEXTURE_PATH + "UVchecker01.png";

}
