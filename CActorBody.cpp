#include "CActorBody.h"

using namespace bs;

namespace The5
{
	ActorBodySkeleton::ActorBodySkeleton()
	{
		mPhysicsMat = PhysicsMaterial::create();
		mPhysicsMat->setDynamicFriction(0.8);
		mPhysicsMat->setStaticFriction(1.0);

		createSceneObjects();
		parentSceneObjects();
		refreshStature();
		joinAllBones();
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

	void ActorBodySkeleton::parentSceneObjects()
	{
		pelvis.SO->setParent(root.SO);

		belly.SO->setParent(pelvis.SO);
		chest.SO->setParent(belly.SO);
		neck.SO->setParent(chest.SO);
		head.SO->setParent(neck.SO);

		armUpperL.SO->setParent(chest.SO);
		armLowerL.SO->setParent(armUpperL.SO);
		handL.SO->setParent(armLowerL.SO);

		armUpperR.SO->setParent(chest.SO);
		armLowerR.SO->setParent(armUpperR.SO);
		handR.SO->setParent(armLowerR.SO);

		legUpperL.SO->setParent(pelvis.SO);
		legLowerL.SO->setParent(legUpperL.SO);
		footL.SO->setParent(legLowerL.SO);

		legUpperR.SO->setParent(pelvis.SO);
		legLowerR.SO->setParent(legUpperR.SO);
		footR.SO->setParent(legLowerR.SO);
	}

	void ActorBodySkeleton::joinAllBones()
	{
		//http://docs.banshee3d.com/Native/joints.html
		//root.joint = root.SO->addComponent<CSphericalJoint>();
		//root.joint->setBody(JointBody::Target, belly.RB);

		attachBoneTo(handR, armLowerR);
		attachBoneTo(armLowerR, armUpperR);
		attachBoneTo(armUpperR, chest);

		attachBoneTo(handL, armLowerL);
		attachBoneTo(armLowerL, armUpperL);
		attachBoneTo(armUpperL, chest);

		attachBoneTo(head, neck);
		attachBoneTo(neck, chest);

		attachBoneTo(chest, belly);
		attachBoneTo(belly, pelvis);

		attachBoneTo(footR, legLowerR);
		attachBoneTo(legLowerR, legUpperR);
		attachBoneTo(legUpperR, pelvis);

		attachBoneTo(footL, legLowerL);
		attachBoneTo(legLowerL, legUpperL);
		attachBoneTo(legUpperL, pelvis);

		attachBoneTo(pelvis, root);


		/*
		LimitConeRange limit;
		limit.yLimitAngle = Degree(10.0f);
		limit.zLimitAngle = Degree(10.0f);

		chest.joint = chest.SO->addComponent<CSphericalJoint>();
		chest.joint->setBody(JointBody::Anchor, chest.RB);
		chest.joint->setBody(JointBody::Target, armUpperR.RB);
		chest.joint->setBody(JointBody::Target, armUpperL.RB);
		((HSphericalJoint)chest.joint)->setLimit(limit);
		chest.joint->setEnableCollision(false);

		armUpperR.joint = armUpperR.SO->addComponent<CSphericalJoint>();
		//armUpperR.joint->setBody(JointBody::Anchor, armUpperR.RB);
		armUpperR.joint->setBody(JointBody::Target, armLowerR.RB);
		((HSphericalJoint)chest.joint)->setLimit(limit);
		chest.joint->setEnableCollision(false);

		armLowerR.joint = armLowerR.SO->addComponent<CSphericalJoint>();
		//armLowerR.joint->setBody(JointBody::Anchor, armLowerR.RB);
		armLowerR.joint->setBody(JointBody::Target, handR.RB);
		((HSphericalJoint)chest.joint)->setLimit(limit);
		chest.joint->setEnableCollision(false);

		armUpperL.joint = armUpperL.SO->addComponent<CSphericalJoint>();
		//armUpperL.joint->setBody(JointBody::Anchor, armUpperL.RB);
		armUpperL.joint->setBody(JointBody::Target, armLowerL.RB);
		((HSphericalJoint)chest.joint)->setLimit(limit);
		chest.joint->setEnableCollision(false);

		armLowerL.joint = armLowerL.SO->addComponent<CSphericalJoint>();
		//armLowerL.joint->setBody(JointBody::Anchor, armLowerL.RB);
		armLowerL.joint->setBody(JointBody::Target, handL.RB);
		((HSphericalJoint)chest.joint)->setLimit(limit);
		chest.joint->setEnableCollision(false);
		*/

	}

	void ActorBodySkeleton::attachBoneTo(ActorBodyBone & child, ActorBodyBone & parent)
	{

#if 1
		//sphere joint keeps the origins identical!
		LimitConeRange limit;
		limit.yLimitAngle = Degree(45.0f);
		limit.zLimitAngle = Degree(45.0f);
		child.joint = child.SO->addComponent<CSphericalJoint>();
		child.joint->setBody(JointBody::Anchor, parent.RB); //Body the joint is attached to (if any)
		child.joint->setBody(JointBody::Target, child.RB); //Body the joint is influencing
		child.joint->setTransform(JointBody::Target, Vector3(0.3f, 0.0f, 0.0f), Quaternion().IDENTITY);
		((HSphericalJoint)child.joint)->setLimit(limit);
		((HSphericalJoint)child.joint)->setFlag(SphericalJointFlag::Limit,true);
		child.joint->setEnableCollision(false);
#elif 0
		child.joint = child.SO->addComponent<CDistanceJoint>();
		child.joint->setBody(JointBody::Anchor, parent.RB);
		child.joint->setBody(JointBody::Target, child.RB);
		((HDistanceJoint)child.joint)->setMinDistance(0.2f);
		((HDistanceJoint)child.joint)->setMaxDistance(0.2f);
		((HDistanceJoint)child.joint)->setFlag(DistanceJointFlag::MinDistance, true);
		((HDistanceJoint)child.joint)->setFlag(DistanceJointFlag::MaxDistance, true);
		child.joint->setEnableCollision(false);
#elif 1
		child.joint = child.SO->addComponent<CD6Joint>();
		child.joint->setBody(JointBody::Target, child.RB); //Body the joint is influencing
		child.joint->setBody(JointBody::Anchor, parent.RB); //Body the joint is attached to (if any)
															// A limit representing a maximum distance of 20 units
		LimitLinear limitX;
		limitX.extent = 20.0f;
		child.joint->setTransform(JointBody::Target, Vector3(0.0f,1.0f,1.0f), Quaternion().IDENTITY);
		((HD6Joint)child.joint)->setLimitLinear(limitX);
		((HD6Joint)child.joint)->setMotion(D6JointAxis::X, D6JointMotion::Limited);
		((HD6Joint)child.joint)->setMotion(D6JointAxis::Y, D6JointMotion::Locked);
		((HD6Joint)child.joint)->setMotion(D6JointAxis::Z, D6JointMotion::Locked);
		((HD6Joint)child.joint)->setMotion(D6JointAxis::Twist, D6JointMotion::Locked);
		((HD6Joint)child.joint)->setMotion(D6JointAxis::SwingY, D6JointMotion::Locked);
		((HD6Joint)child.joint)->setMotion(D6JointAxis::SwingZ, D6JointMotion::Locked);
		child.joint->setEnableCollision(false);

#endif

	}

	void ActorBodySkeleton::refreshStature()
	{
		root.SO->setPosition(Vector3(0.0f, 0.0f, 0.0f));
		pelvis.SO->setPosition(Vector3(0.0f, stature.hipHeight, 0.0f));
		belly.SO->setPosition(Vector3(0.0f, 0.0f, 0.0f));
		chest.SO->setPosition(Vector3(0.0f, stature.chestHeight*0.5, 0.0f));
		neck.SO->setPosition(Vector3(0.0f, stature.chestHeight*0.5, 0.0f));
		head.SO->setPosition(Vector3(0.0f, stature.neckHeight, 0.0f));

		armUpperR.SO->setPosition(Vector3(+stature.chestWidth*0.5f, stature.chestHeight*0.5, 0.0f));
		armUpperL.SO->setPosition(Vector3(-stature.chestWidth*0.5f, stature.chestHeight*0.5, 0.0f));
		armLowerR.SO->setPosition(Vector3(0.0f, -stature.armLength*0.5, 0.0f));
		armLowerL.SO->setPosition(Vector3(0.0f, -stature.armLength*0.5, 0.0f));
		handR.SO->setPosition(Vector3(0.0f, -stature.armLength*0.5, 0.0f));
		handL.SO->setPosition(Vector3(0.0f, -stature.armLength*0.5, 0.0f));

		legUpperR.SO->setPosition(Vector3(+stature.hipWidth*0.5f, 0.0, 0.0f));
		legUpperL.SO->setPosition(Vector3(-stature.hipWidth*0.5f, 0.0, 0.0f));
		legLowerR.SO->setPosition(Vector3(0.0f, -stature.hipHeight*0.5, 0.0f));
		legLowerL.SO->setPosition(Vector3(0.0f, -stature.hipHeight*0.5, 0.0f));
		footL.SO->setPosition(Vector3(0.0f, -stature.hipHeight*0.5, 0.0f));
		footR.SO->setPosition(Vector3(0.0f, -stature.hipHeight*0.5, 0.0f));
	}

	void ActorBodySkeleton::createBone(bs::String name, ActorBodyBone& outBone)
	{
		//http://docs.banshee3d.com/Native/bones.html
		outBone.SO = SceneObject::create(name);
		outBone.RB = outBone.SO->addComponent<CRigidbody>();
		//outBone.RB->setMass(5.0f);
		outBone.collider = outBone.SO->addComponent<CSphereCollider>();
		((bs::HSphereCollider)outBone.collider)->setRadius(0.1f);
		outBone.collider->setMaterial(mPhysicsMat);
	}

	void ActorBodySkeleton::createJoint(bs::String name, ActorBodyBone& outBone)
	{
		//outBone.joint = outBone.SO->addComponent<CJoint>();
	}


	void CActorBody::onInitialized()
	{

		setName("ActorBody");

		mActorSkeleton = std::make_unique<ActorBodySkeleton>();
	}

	void CActorBody::update()
	{
		debugDrawSkeleton();
	}


	void CActorBody::onDisabled()
	{

	}

	void CActorBody::onEnabled()
	{


	}


	void CActorBody::refreshStature()
	{
		mActorSkeleton->refreshStature();
	}

	void CActorBody::debugDrawSkeleton()
	{
		
		mDebugDrawer._update();
		mDebugDrawer.clear();
		mDebugDrawer.setColor(Color(1.0f, 1.0f, 0.25f, 1.0f));
		mDebugDrawer.drawCube(mActorSkeleton->root.SO->getTransform().pos(), 
			Vector3(1.0f, 1.0f, 1.0f)*(
				mActorSkeleton->stature.hipHeight 
				+ mActorSkeleton->stature.chestHeight 
				+ mActorSkeleton->stature.headSize)*0.01f);

		mDebugDrawer.setColor(Color(0.0f, 1.0f, 0.0f, 1.0f));
		mDebugDrawer.drawWireSphere(mActorSkeleton->head.SO->getTransform().pos(), mActorSkeleton->stature.headSize*0.5);
		mDebugDrawer.setColor(Color(0.0f, 0.0f, 1.0f, 1.0f));
		mDebugDrawer.drawWireSphere(mActorSkeleton->chest.SO->getTransform().pos(), mActorSkeleton->stature.chestWidth*0.5);
		mDebugDrawer.setColor(Color(1.0f, 1.0f, 0.0f, 1.0f));
		mDebugDrawer.drawWireSphere(mActorSkeleton->pelvis.SO->getTransform().pos(), mActorSkeleton->stature.hipWidth*0.5);

		mDebugDrawer.setColor(Color(1.0f, 0.0f, 0.25f, 1.0f));
		mDebugDrawer.drawWireSphere(mActorSkeleton->handR.SO->getTransform().pos(), mActorSkeleton->stature.handSize*0.5);
		mDebugDrawer.drawWireSphere(mActorSkeleton->footR.SO->getTransform().pos(), mActorSkeleton->stature.footSize*0.5);

		mDebugDrawer.setColor(Color(0.0f, 1.0f, 0.25f, 1.0f));
		mDebugDrawer.drawWireSphere(mActorSkeleton->footL.SO->getTransform().pos(), mActorSkeleton->stature.footSize*0.5);
		mDebugDrawer.drawWireSphere(mActorSkeleton->handL.SO->getTransform().pos(), mActorSkeleton->stature.handSize*0.5);


		debugDrawBone(mActorSkeleton->root, mActorSkeleton->pelvis);
		
		debugDrawBone(mActorSkeleton->pelvis, mActorSkeleton->belly);
		debugDrawBone(mActorSkeleton->belly, mActorSkeleton->chest);
		debugDrawBone(mActorSkeleton->chest, mActorSkeleton->neck);
		debugDrawBone(mActorSkeleton->neck, mActorSkeleton->head);

		debugDrawBone(mActorSkeleton->chest, mActorSkeleton->armUpperR);
		debugDrawBone(mActorSkeleton->armUpperR, mActorSkeleton->armLowerR);
		debugDrawBone(mActorSkeleton->armLowerR,mActorSkeleton->handR);

		debugDrawBone(mActorSkeleton->chest, mActorSkeleton->armUpperL);
		debugDrawBone(mActorSkeleton->armUpperL, mActorSkeleton->armLowerL);
		debugDrawBone(mActorSkeleton->armLowerL, mActorSkeleton->handL);

		debugDrawBone(mActorSkeleton->pelvis, mActorSkeleton->legUpperL);
		debugDrawBone(mActorSkeleton->legUpperL, mActorSkeleton->legLowerL);
		debugDrawBone(mActorSkeleton->legLowerL, mActorSkeleton->footL);

		debugDrawBone(mActorSkeleton->pelvis, mActorSkeleton->legUpperR);
		debugDrawBone(mActorSkeleton->legUpperR, mActorSkeleton->legLowerR);
		debugDrawBone(mActorSkeleton->legLowerR, mActorSkeleton->footR);

	}

	void CActorBody::debugDrawBone(const ActorBodyBone & start, const ActorBodyBone & end)
	{
		float coneRadius = 0.02f;
		Vector3 vec = Vector3(end.SO->getTransform().pos()) - Vector3(start.SO->getTransform().pos());
		Vector3 normal = vec;
		normal.normalize();
		mDebugDrawer.setColor(Color(0.1f, 0.1f, 0.1f, 1.0f));
		mDebugDrawer.drawCone(start.SO->getTransform().pos(), normal, vec.length(), coneRadius);
		mDebugDrawer.setColor(Color(0.0f, 0.0f, 1.0f, 1.0f));
		mDebugDrawer.drawWireCone(start.SO->getTransform().pos(), normal, vec.length(), coneRadius +std::numeric_limits<float>().epsilon());
		mDebugDrawer.drawLine(start.SO->getTransform().pos(), end.SO->getTransform().pos());
		mDebugDrawer.setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
		mDebugDrawer.drawWireSphere(start.SO->getTransform().pos(), 0.1f);
	}

}


