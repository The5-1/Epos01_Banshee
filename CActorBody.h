#pragma once
#include "include_STL.h"
#include "include_Banshee.h"
#include "ForwardDeclarations.h"

namespace The5 {

	struct ActorBodyStature
	{
		float hipHeight = 1.0f;
		float chestHeight = 0.6f;
		float neckHeight = 0.15f;
		float armLength = 0.8f;

		float chestWidth = 0.4f; //Shoulder
		float hipWidth = 0.25f; //Pelvis

		float headSize = 0.2f;
		float handSize = 0.1f;
		float footSize = 0.15f;
	};

	struct ActorBodyBone
	{
		bs::HSceneObject SO;
		bs::HRigidbody RB;
		bs::HCollider collider;
		bs::HJoint joint;
		bs::HBone bone;
	};

	class ActorBodySkeleton
	{
	public:
		ActorBodySkeleton();
		~ActorBodySkeleton() = default;

		void createSceneObjects();

		void parentSceneObjects();

		void joinSceneObjects();


		void refreshStature();

		void createBone(bs::String name, ActorBodyBone& outBone);
#define createBone_macro(name) createBone(#name, name)

		void createJoint(bs::String name, ActorBodyBone& outBone);
#define createBone_macro(name) createBone(#name, name)

		ActorBodyStature stature;
	
		ActorBodyBone root;

		ActorBodyBone pelvis;
		ActorBodyBone belly;
		ActorBodyBone chest;
		ActorBodyBone neck;
		ActorBodyBone head;

		ActorBodyBone legUpperR;
		ActorBodyBone legUpperL;
		ActorBodyBone legLowerR;
		ActorBodyBone legLowerL;
		ActorBodyBone footR;
		ActorBodyBone footL;

		ActorBodyBone armUpperR;
		ActorBodyBone armUpperL;
		ActorBodyBone armLowerR;
		ActorBodyBone armLowerL;
		ActorBodyBone handR;
		ActorBodyBone handL;
	};

	/** documentation */
	class CActorBody : public bs::Component
	{
	public:

		CActorBody(const bs::HSceneObject& parent);

	protected:
		
		bs::DebugDraw mDebugDrawer;

		std::unique_ptr<ActorBodySkeleton> mActorSkeleton;

		virtual void onInitialized() override;

		virtual void update() override;

		//virtual void onDestroyed() override;

		void refreshStature();

		void debugDraw();
		void debugDrawBone(const ActorBodyBone& start, const ActorBodyBone& end);
		void debugDrawName(const ActorBodyBone& bone);

	};

	typedef bs::GameObjectHandle<CActorBody> HActorBody;
}