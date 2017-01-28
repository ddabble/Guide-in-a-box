#pragma once

class FramebufferSizeHook_interface
{
public:
	virtual void framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight) = 0;
};
