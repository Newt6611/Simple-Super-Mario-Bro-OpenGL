#pragma once

#include <box2d/box2d.h>
#include "IObject.h"

class ContactListener : public b2ContactListener
{
public:
	ContactListener(b2World& physicsWorld);
	~ContactListener();

	void BeginContact(b2Contact* contact) override;
};