#pragma once
#include "include_Banshee.h"

namespace The5
{

	/** Custom Class for Advanced Startup 
	* start like: Application::startUp<The5Application>(The5Application::defaultStartupDesc());
	*/
	class The5Application : public bs::Application
	{
	public:
		/** constructor */
		The5Application(const bs::START_UP_DESC& desc);
		/** generate a default startupDesc */
		static bs::START_UP_DESC defaultStartupDesc();

		///start
		//** shortcut that calls Application::startUp<The5Application>(The5Application::defaultStartupDesc()); */
		static void start();

		///static Access Points
		/** get the The5Application object */
		static The5Application& get();
		/** get the mainCamera Component */
		static bs::HCamera& mainCamera();

		///Asset Loading
		/** import a mesh and save it as Banshee .asset if it does not exist yet**/
		static bs::HMesh loadMesh(const bs::Path& originalFilePath, float scale = 1.0f);
		/** import a texture and save it as Banshee .asset if it does not exist yet**/
		static bs::HTexture loadTexture(const bs::Path& originalFilePath, bool isSRGB = false, bool isCubemap = false, bool isHDR = false);
		/** get default shader */
		static bs::HMaterial& getDefaultPBRMaterial();


	protected:
		///private Fields
		/** camea component */
		bs::HCamera mMainCameraC;
		/** camera SO */
		bs::HSceneObject mMainCameraSO;

		///bs::Application overrides
		void onStartUp() override;
		void onShutDown() override;
		void preUpdate() override;
		void postUpdate() override;

		///Setup
		/** loads default assets */
		void initDefaultAssets();
		/** create the main camera SO and Component and attach further components */
		void initMainCamera();
		/** set default key bindings */
		void initDefaultKeyBindings();

		///Callbacks
	    /** method registering all the Callbacks at their corresponding Events*/
		void initCallbacks();
		/** handles camera Aspect etc. */
		void windowResizeCallback();

		///Default Assets
		bs::HShader defaultPBRShader;
		bs::HMaterial defaultPBRMaterial;

		bs::HTexture defaultTexture_Albedo;
		bs::HTexture defaultTexture_Normals;
		bs::HTexture defaultTexture_Roughness;
		bs::HTexture defaultTexture_Metalness;

	};

}

