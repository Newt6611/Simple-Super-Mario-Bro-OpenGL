#include "ContactListener.h"

#include "Mario.h"

ContactListener::ContactListener(b2World& physicsWorld)
{
	physicsWorld.SetContactListener(this);
}

ContactListener::~ContactListener()
{

}

void ContactListener::BeginContact(b2Contact* contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	IObject* objA = (IObject*)bodyA->GetUserData().pointer;
	IObject* objB = (IObject*)bodyB->GetUserData().pointer;

	if (objA && objB)
	{
		objA->OnTriggerEnter(objB);
		objB->OnTriggerEnter(objA);
	}
}
