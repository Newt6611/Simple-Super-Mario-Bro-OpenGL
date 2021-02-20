#pragma once

#include "GLFW/glfw3.h"


class Input {
public:
	static bool keys[1024];
	static bool keyUp[1024];
	static bool const GetKey(int key);
	static bool const GetKeyDown(int key);

private:
};