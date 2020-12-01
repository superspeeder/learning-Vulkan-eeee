#pragma once

#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>

#include <vector>
#include <string>

struct InstanceVersion {
	uint32_t major, minor, patch;
};


std::vector<std::string> fromExtPropertiesList(std::vector<VkExtensionProperties> prop_vec);

class VulkanInstance
{

private:

	std::vector<std::string> m_InstanceExtensionNames;

	std::vector<VkExtensionProperties> m_AvailableInstanceExtensions;
	bool gatheredInstanceExtensions;

	std::vector<std::string> m_LayerNames;
	bool gatheredLayerNames;

	std::string m_AppName, m_EngineName;
	InstanceVersion m_AppVersion, m_EngineVersion;
	uint32_t m_VulkanAPIVerison;

	VkInstance m_VkInstance;

	bool m_Built;

public:

	VulkanInstance(std::string appName, InstanceVersion appVersion, std::string engineName, InstanceVersion engineVersion, uint32_t vulkanApiVersion, bool enableValidationLayers);

	VulkanInstance();

	void setAppName(std::string appName);
	void setAppVersion(InstanceVersion appVersion);
	void setEngineName(std::string engineName);
	void setEngineVersion(InstanceVersion engineVersion);
	void setVulkanApiVersion(uint32_t vulkanApiVersion);

	std::string getAppName();
	std::string getEngineName();

	InstanceVersion getAppVersion();
	InstanceVersion getEngineVersion();

	std::vector<VkExtensionProperties> getAvailableInstanceExtensions();
	std::vector<std::string> getRequiredInstanceExtensions();
	std::vector<std::string> getRequstedInstanceExtensions();
	bool verifyExtensionCompatibility(std::string extensionName);
	void requireExtension(std::string extensionName);


	void build();
	bool isBuilt();

	void setUseValidationLayers(bool useValidationLayers);
	bool getUseValidationLayers();

	bool areValidationLayersSupported();

	std::vector<VkLayerProperties> getAvailableLayers();
	std::vector<std::string> getRequestedLayers();

	VkInstance getInternalInstance();
};

