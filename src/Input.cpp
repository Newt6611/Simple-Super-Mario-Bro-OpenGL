#include "Input.h"

bool Input::keys[1024];
bool Input::keyUp[1024];

bool const Input::GetKey(int key)
{
	return keys[key];
}

bool const Input::GetKeyDown(int key) 
{
	if (!keyUp[key] && keys[key])
	{
		keyUp[key] = true;
		return true;
	}
	else 
	{
		return false;
	}
}