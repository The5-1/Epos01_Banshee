#include "CActorBody.h"

using namespace bs;

namespace The5
{
	ActorBodySkeleton::ActorBodySkeleton()
	{
		createSceneObjects();
		refreshStature();
	}

	void ActorBodySkeleton::createSceneObjects()
	{
		createBone_macro(root);
		createBone_macro(pelvis);
		createBone_macro(belly);
		createBone_macro(chest);
		createBone_macro(neck);
		createBone_macro(head);
		createBone_macro(legUpperR);
		createBone_macro(legUpperL);
		createBone_macro(legLowerR);
		createBone_macro(legLowerL);
		createBone_macro(footR);
		createBone_macro(footL);
		createBone_macro(armUpperR);
		createBone_macro(armUpperL);
		createBone_macro(armLowerR);
		createBone_macro(armLowerL);
		createBone_macro(handR);
		createBone_macro(handL);
	}

	void ActorBodySkeleton::joinSceneObjects()
	{


	}

	void ActorBodySkeleton::refreshStature()
	{


	}

	void ActorBodySkeleton::createBone(bs::String name, HSceneObject & outSO)
	{
		outSO = SceneObject::create(name);
		//outSO->addComponent<CBone>();
	}


	CActorBody::CActorBody(const bs::HSceneObject & parent) : bs::Component(parent)
	{
		mActorSkeleton = std::make_unique<ActorBodySkeleton>();
	}

	void CActorBody::onInitialized()
	{
		setName("ActorBody");

		refreshStature();
	}

	void CActorBody::update()
	{

		debugDraw();
	}


	void CActorBody::refreshStature()
	{
		mActorSkeleton->refreshStature();
	}

	void CActorBody::debugDraw()
	{
		
		mDebugDrawer._update();
		mDebugDrawer.clear();
		mDebugDrawer.setColor(Color(0.0f, 0.0f, 1.0f, 1.0f));
		mDebugDrawer.drawCube(mActorSkeleton->root->getTransform().pos(), 
			Vector3(1.0f, 1.0f, 1.0f)*(
				mActorSkeleton->stature.hipHeight 
				+ mActorSkeleton->stature.chestHeight 
				+ mActorSkeleton->stature.headSize)*0.01f);
		mDebugDrawer.drawWireSphere(mActorSkeleton->head->getTransform().pos(), mActorSkeleton->stature.headSize);
		mDebugDrawer.drawWireSphere(mActorSkeleton->chest->getTransform().pos(), mActorSkeleton->stature.chestWidth);
		mDebugDrawer.drawWireSphere(mActorSkeleton->pelvis->getTransform().pos(), mActorSkeleton->stature.hipWidth);
		mDebugDrawer.drawWireSphere(mActorSkeleton->handR->getTransform().pos(), mActorSkeleton->stature.handSize);
		mDebugDrawer.drawWireSphere(mActorSkeleton->handL->getTransform().pos(), mActorSkeleton->stature.handSize);
		mDebugDrawer.drawWireSphere(mActorSkeleton->footL->getTransform().pos(), mActorSkeleton->stature.footSize);
		mDebugDrawer.drawWireSphere(mActorSkeleton->footR->getTransform().pos(), mActorSkeleton->stature.footSize);
		
	}

}


