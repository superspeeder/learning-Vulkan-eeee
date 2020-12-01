#include "VulkanInstance.h"
#include <iostream>

VulkanInstance::VulkanInstance(std::string appName, InstanceVersion appVersion, std::string engineName, InstanceVersion engineVersion, uint32_t vulkanApiVersion, bool enableValidationLayers) {
	setAppName(appName);
	setAppVersion(appVersion);
	setEngineName(engineName);
	setEngineVersion(engineVersion);
	setVulkanApiVersion(vulkanApiVersion);
	setUseValidationLayers(enableValidationLayers);
}

VulkanInstance::VulkanInstance() {
	for (std::string name : getRequiredInstanceExtensions()) {
		requireExtension(name);
	}
}

void VulkanInstance::setAppName(std::string appName) {
	m_AppName = appName;
}

void VulkanInstance::setAppVersion(InstanceVersion appVersion) {
	m_AppVersion = appVersion;
}

void VulkanInstance::setEngineName(std::string engineName) {
	m_EngineName = engineName;
}

void VulkanInstance::setEngineVersion(InstanceVersion engineVersion) {
	m_EngineVersion = engineVersion;
}

void VulkanInstance::setVulkanApiVersion(uint32_t vulkanApiVersion) {
	m_VulkanAPIVerison = vulkanApiVersion;
}

std::string VulkanInstance::getAppName() {
	return m_AppName;
}

std::string VulkanInstance::getEngineName() {
	return m_EngineName;
}

InstanceVersion VulkanInstance::getAppVersion() {
	return m_AppVersion;
}

InstanceVersion VulkanInstance::getEngineVersion() {
	return m_EngineVersion;
}

std::vector<VkExtensionProperties> VulkanInstance::getAvailableInstanceExtensions() {
	if (!gatheredInstanceExtensions) {
		uint32_t numInstExt = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &numInstExt, nullptr);
		m_AvailableInstanceExtensions.resize(numInstExt);
		vkEnumerateInstanceExtensionProperties(nullptr, &numInstExt, m_AvailableInstanceExtensions.data());
	}

	return m_AvailableInstanceExtensions;
}

std::vector<std::string> VulkanInstance::getRequiredInstanceExtensions() {
	std::vector<std::string> req; 
	uint32_t req_count;

	const char** req_arr = glfwGetRequiredInstanceExtensions(&req_count);

	for (uint32_t i = 0; i < req_count; i++) {
		req.push_back(std::string(req_arr[i]));
	}
	return req;
}

std::vector<std::string> VulkanInstance::getRequstedInstanceExtensions() {
	return m_InstanceExtensionNames;
}

bool VulkanInstance::verifyExtensionCompatibility(std::string extensionName) {
	for (VkExtensionProperties prop : getAvailableInstanceExtensions()) {
		if (prop.extensionName == extensionName) {
			return true;
		}
	}
	return false;
}

void VulkanInstance::requireExtension(std::string extensionName) {
	if (verifyExtensionCompatibility(extensionName)) {
		for (std::string name : getRequstedInstanceExtensions()) {
			if (name == extensionName) {
				return;
			}
		}
		m_InstanceExtensionNames.push_back(extensionName);
	}

	std::cerr << "Instance extension " << extensionName << " is not available";
}


void VulkanInstance::build() {

}

bool VulkanInstance::isBuilt() {
	return m_Built;
}

void VulkanInstance::setUseValidationLayers(bool useValidationLayers) {

}

bool VulkanInstance::getUseValidationLayers() {
	return false;
}

bool VulkanInstance::areValidationLayersSupported() {
	return false;
}

std::vector<VkLayerProperties> VulkanInstance::getAvailableLayers() {
	return std::vector<VkLayerProperties>();
}

std::vector<std::string> VulkanInstance::getRequestedLayers() {
	return std::vector<std::string>();

}

VkInstance VulkanInstance::getInternalInstance() {
	return nullptr;
}


std::vector<std::string> fromExtPropertiesList(std::vector<VkExtensionProperties> prop_vec) {
	std::vector<std::string> names;
	for (VkExtensionProperties ext : prop_vec) {
		names.push_back(ext.extensionName);
	}
	return names;
}
