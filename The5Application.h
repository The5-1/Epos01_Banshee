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
		/** generate a default startupDesc */
		static bs::SPtr<bs::RenderSettings> defaultRenderSettings();

		///start
		//** shortcut that calls Application::startUp<The5Application>(The5Application::defaultStartupDesc()); */
		static void start();

		///static Access Points
		/** get the The5Application object */
		static The5Application& get();
		/** get the mainCamera Component */
		static bs::HCamera& mainCamera();

	protected:
		///private Fields
		/** camea component */
		bs::HCamera mMainCameraC;
		/** camera SO */
		bs::HSceneObject mMainCameraSO;
		/** GUI SO */
		bs::HSceneObject mGUI_SO;
		/** GUI camera */
		bs::HCamera mGUI_CameraC;
		/** GUI Widget */
		bs::HGUIWidget  mGUI_Widget;

		///bs::Application overrides
		// ---- Don't forget to call the default application methods! ----
		// ---- Or check ".../BansheeEngine/Source/BansheeEngine/BsApplication.cpp" ----
		/** calls Application::onStartUp() */
		void onStartUp() override;
		/** calls Application::onShutDown() */
		void onShutDown() override;
		/** calls Application::preUpdate() */
		void preUpdate() override;
		/** calls Application::postUpdate() */
		void postUpdate() override;

		///Setup
		/** configures the Renderer */
		void initRenderer();
		/** create the main camera SO and Component and attach further components */
		void initMainCamera();
		/** create the GUI camera SO and Component and attach further components */
		void initGUI();

		///Callbacks
	    /** method registering all the Callbacks at their corresponding Events*/
		void initCallbacks();
		/** handles camera Aspect etc. */
		void windowResizeCallback();

	};

}

