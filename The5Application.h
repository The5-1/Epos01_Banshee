#pragma once
#include "include_Banshee.h"

namespace The5
{

	class The5Application : public bs::Application
	{
	public:
		/** constructor */
		The5Application(const bs::START_UP_DESC& desc);

		///Fields
		/** camea component */
		bs::HCamera mainCamera;
		/** camera SO */
		bs::HSceneObject mainCameraSO;

		///Methods
		/** generate a default startupDesc */
		static bs::START_UP_DESC defaultStartupDesc();

	private:
		///bs::Application overrides
		void onStartUp() override;
		void onShutDown() override;
		void preUpdate() override;
		void postUpdate() override;

		//setup
		void createMainCamera();


		//Callbacks
		void subscribeCallbacksToEvents();
		void windowResizeCallback();
	};
}

