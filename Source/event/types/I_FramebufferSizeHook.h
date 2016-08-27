#pragma once

class I_FramebufferSizeHook
{
public:
	virtual void framebufferSizeCallback(int width, int height) = 0;
};
