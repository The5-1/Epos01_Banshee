#pragma once
#include "include_STL.h"
#include "include_Banshee.h"
#include "ForwardDeclarations.h"

namespace The5 {

	class CActorBody;

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
		ActorBodySkeleton(CActorBody& actorBodyComponent);
		~ActorBodySkeleton() = default;

		void createSceneObjects();

		void parentSceneObjects();

		

		void joinAllBones();

		void attachToRoot(ActorBodyBone & pelvis);

		void attachBoneTo(ActorBodyBone & child, ActorBodyBone & parent);


		void refreshStature();

		void createBone(bs::String name, ActorBodyBone& outBone);
#define createBone_macro(name) createBone(#name, name)

		void createJoint(bs::String name, ActorBodyBone& outBone);
#define createBone_macro(name) createBone(#name, name)

		ActorBodyStature stature;

		CActorBody& mActorBodyComponent;
	
		bs::HPhysicsMaterial mPhysicsMat;

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

		/** the constructor should just pass the parent, initialization is done in onInitialized() */
		CActorBody(const bs::HSceneObject& parent) : bs::Component(parent) {};

	protected:
		
		bs::DebugDraw mDebugDrawer;

		std::unique_ptr<ActorBodySkeleton> mActorSkeleton;

		virtual void onInitialized() override;

		virtual void update() override;

		void onDisabled() override;

		void onEnabled() override;

		//virtual void onDestroyed() override;

		void refreshStature();

		void debugDrawSkeleton();
		void debugDrawBone(const ActorBodyBone& start, const ActorBodyBone& end);
	};

	typedef bs::GameObjectHandle<CActorBody> HActorBody;
}