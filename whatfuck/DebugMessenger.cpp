#include "DebugMessenger.h"

#include "VulkanInstance.h"


VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr) {
		func(instance, debugMessenger, pAllocator);
	}
}


DebugMessenger::DebugMessenger(VulkanInstance* instance, DebugFilter typeFilter, DebuggingLevel level) { // default debug callback
	setInstance(instance);
	setFilter(typeFilter);
	setLevel(level);
}

DebugMessenger::DebugMessenger(VulkanInstance* instance, DebugFilter typeFilter, DebuggingLevel level, PFN_vkDebugUtilsMessengerCallbackEXT callback) { // custom debug callback
	setInstance(instance);
	setFilter(typeFilter);
	setLevel(level);
	setCallback(callback);
}

VulkanInstance* DebugMessenger::getInstance() {
	return m_Instance;
}

void DebugMessenger::setInstance(VulkanInstance* inst) {
	m_Instance = inst;
}

PFN_vkDebugUtilsMessengerCallbackEXT DebugMessenger::getCallback() {
	return m_Callback;
}

void DebugMessenger::setCallback(PFN_vkDebugUtilsMessengerCallbackEXT callback) {
	m_Callback = callback;
}

DebugFilter DebugMessenger::getFilter() {
	return m_Filter;
}

void DebugMessenger::setFilter(DebugFilter filter) {
	m_Filter = filter;
}

DebuggingLevel DebugMessenger::getLevel() {
	return m_Level;
}

void DebugMessenger::setLevel(DebuggingLevel level) {
	m_Level = level;
}

void DebugMessenger::build() {
	VkDebugUtilsMessengerCreateInfoEXT createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = m_Level;
	createInfo.messageType = m_Filter.flag();
	createInfo.pfnUserCallback = m_Callback;
	createInfo.pUserData = nullptr; // Optional

	if (CreateDebugUtilsMessengerEXT(m_Instance->getInternalInstance(), &createInfo, nullptr, &m_DebugMessenger) != VK_SUCCESS) {
		throw std::runtime_error("failed to set up debug messenger!");
	}
	m_Built = true;
}

bool DebugMessenger::isBuilt() {
	return m_Built;
}