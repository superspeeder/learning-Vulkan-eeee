#pragma once

#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>


#include <cstdint>

#include "VulkanInstance.h"



class Application
{

private:

	void initWindow();
	void initVulkan();
	void constructConfigs();

protected:

	const char* m_Title;
	const uint32_t m_Width, m_Height;

	VulkanInstance *m_vkInstance;


	virtual void postInit() {};
	virtual void preInit() {};
	virtual void onupdate() {};
	virtual void ondestroy() {};

public:

	Application(const uint32_t width, const uint32_t height, const char* title) : m_Width{ width }, m_Height{ height }, m_Title{ title } { constructConfigs(); }

	
	void run();
};

