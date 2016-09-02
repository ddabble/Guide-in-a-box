#pragma once

class I_FramebufferSizeHook
{
public:
	virtual void framebufferSizeCallback(int lastWidth, int lastHeight, int newWidth, int newHeight) = 0;
};
