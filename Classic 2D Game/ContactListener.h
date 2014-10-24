#pragma once
#include <Box2D\Box2D.h>
class ContactListener : public b2ContactListener
{
public:

	ContactListener() 
	{
	/*	nPlayerFootSensor = 0;
		nPlayerLeftSensor = 0;
		nPlayerRightSensor = 0;
		nPlayerHeadSensor = 0;*/
	}
	~ContactListener() {}

	/// Called when two fixtures begin to touch.
	void BeginContact(b2Contact* contact) 
	{  
		//std::cout << "BeginContact" << std::endl;
		//check if fixture A was the foot sensor
		void* fixtureUserData = contact->GetFixtureA()->GetUserData();
		if (contact->GetFixtureA()->IsSensor())
		{
			if ((int)fixtureUserData == 1)
				nPlayerFootSensor++;
			if ((int)fixtureUserData == 2)
				nPlayerLeftSensor++;
			if ((int)fixtureUserData == 3)
				nPlayerRightSensor++;
			if ((int)fixtureUserData == 4)
				nPlayerHeadSensor++;
		}


		//check if fixture B was the foot sensor
		fixtureUserData = contact->GetFixtureB()->GetUserData();
		if (contact->GetFixtureB()->IsSensor())
		{
			if ((int)fixtureUserData == 1)
				nPlayerFootSensor++;
			if ((int)fixtureUserData == 2)
				nPlayerLeftSensor++;
			if ((int)fixtureUserData == 3)
				nPlayerRightSensor++;
			if ((int)fixtureUserData == 4)
				nPlayerHeadSensor++;
		}
		
	}

	/// Called when two fixtures cease to touch.
	void EndContact(b2Contact* contact)
	{ 
		//std::cout << "EndContact" << std::endl;
		//check if fixture A was the foot sensor
		void* fixtureUserData = contact->GetFixtureA()->GetUserData();
		if (contact->GetFixtureA()->IsSensor())
		{
			if ((int)fixtureUserData == 1)
				nPlayerFootSensor--;
			if ((int)fixtureUserData == 2)
				nPlayerLeftSensor--;
			if ((int)fixtureUserData == 3)
				nPlayerRightSensor--;
			if ((int)fixtureUserData == 4)
				nPlayerHeadSensor--;
		}


		//check if fixture B was the foot sensor
		fixtureUserData = contact->GetFixtureB()->GetUserData();
		if (contact->GetFixtureB()->IsSensor())
		{
			if ((int)fixtureUserData == 1)
				nPlayerFootSensor--;
			if ((int)fixtureUserData == 2)
				nPlayerLeftSensor--;
			if ((int)fixtureUserData == 3)
				nPlayerRightSensor--;
			if ((int)fixtureUserData == 4)
				nPlayerHeadSensor--;
		}
	}

	///// This is called after a contact is updated. This allows you to inspect a
	///// contact before it goes to the solver. If you are careful, you can modify the
	///// contact manifold (e.g. disable contact).
	///// A copy of the old manifold is provided so that you can detect changes.
	///// Note: this is called only for awake bodies.
	///// Note: this is called even when the number of contact points is zero.
	///// Note: this is not called for sensors.
	///// Note: if you set the number of contact points to zero, you will not
	///// get an EndContact callback. However, you may get a BeginContact callback
	///// the next step.
	//virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	//{
	//	B2_NOT_USED(contact);
	//	B2_NOT_USED(oldManifold);
	//}

	///// This lets you inspect a contact after the solver is finished. This is useful
	///// for inspecting impulses.
	///// Note: the contact manifold does not include time of impact impulses, which can be
	///// arbitrarily large if the sub-step is small. Hence the impulse is provided explicitly
	///// in a separate data structure.
	///// Note: this is only called for contacts that are touching, solid, and awake.
	//virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	//{
	//	B2_NOT_USED(contact);
	//	B2_NOT_USED(impulse);
	//}

	static bool PlayerOnGround(){ return nPlayerFootSensor > 0; }
	static bool PlayerTouchLeft(){ return nPlayerLeftSensor > 0; }
	static bool PlayerTouchRight(){ return nPlayerRightSensor > 0; }
	static bool PlayerHeadTouched(){ return nPlayerHeadSensor > 0; }

private:
	static int nPlayerFootSensor;
	static int nPlayerLeftSensor;
	static int nPlayerRightSensor;
	static int nPlayerHeadSensor;
};

int ContactListener::nPlayerFootSensor = 0;
int ContactListener::nPlayerLeftSensor = 0;
int ContactListener::nPlayerRightSensor = 0;
int ContactListener::nPlayerHeadSensor = 0;