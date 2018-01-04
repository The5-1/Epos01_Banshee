#pragma once
#include "include_STL.h"
#include "include_Banshee.h"
#include "ForwardDeclarations.h"

namespace The5 {

	struct ActorBodyStature
	{
		float headSize = 0.1f;
		float armLength = 1.0f;
		float handSize = 0.05f;
		float footSize = 0.07f;
		float chestHeight = 0.8f;
		float chestWidth = 0.3f;
		float hipHeight = 1.0f;
		float hipWidth = 0.2f;
	};

	class ActorBodySkeleton
	{
	public:
		ActorBodySkeleton();
		~ActorBodySkeleton() = default;

		void createSceneObjects();

		void joinSceneObjects();

		void refreshStature();

		void createBone(bs::String name, bs::HSceneObject& outSO);
#define createBone_macro(name) createBone(#name, name)

		ActorBodyStature stature;
	
		bs::HSceneObject root;
		bs::HSceneObject pelvis;
		bs::HSceneObject belly;
		bs::HSceneObject chest;
		bs::HSceneObject neck;
		bs::HSceneObject head;

		bs::HSceneObject legUpperR;
		bs::HSceneObject legUpperL;
		bs::HSceneObject legLowerR;
		bs::HSceneObject legLowerL;
		bs::HSceneObject footR;
		bs::HSceneObject footL;

		bs::HSceneObject armUpperR;
		bs::HSceneObject armUpperL;
		bs::HSceneObject armLowerR;
		bs::HSceneObject armLowerL;
		bs::HSceneObject handR;
		bs::HSceneObject handL;
	};

	/** documentation */
	class CActorBody : public bs::Component
	{
	public:

		CActorBody(const bs::HSceneObject& parent);

	protected:
		
		bs::DebugDraw mDebugDrawer;

		std::unique_ptr<ActorBodySkeleton> mActorSkeleton;

		ActorBodyStature mActorStature;

		virtual void onInitialized() override;

		virtual void update() override;

		//virtual void onDestroyed() override;

		void refreshStature();

		void debugDraw();

	};

	typedef bs::GameObjectHandle<CActorBody> HActorBody;
}