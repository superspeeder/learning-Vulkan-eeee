#pragma once

#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include "Utils.h"
#include "VulkanInstance.h"

#define VALIDATION_MSG_SEVERITY_VERBOSE VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
#define VALIDATION_MSG_SEVERITY_WARNING VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
#define VALIDATION_MSG_SEVERITY_ERROR VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT

#define VALIDATION_LEVEL_ALL VALIDATION_MSG_SEVERITY_VERBOSE | VALIDATION_MSG_SEVERITY_WARNING | VALIDATION_MSG_SEVERITY_ERROR;
#define VALIDATION_LEVEL_WARN VALIDATION_MSG_SEVERITY_WARNING | VALIDATION_MSG_SEVERITY_ERROR;
#define VALIDATION_LEVEL_ERROR VALIDATION_MSG_SEVERITY_ERROR;

#define VALIDATION_FILTER_GENERAL VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
#define VALIDATION_FILTER_VALIDATION VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
#define VALIDATION_FILTER_PERFORMANCE VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT

#define VALIDATION_FILTER_NONE VALIDATION_FILTER_GENERAL | VALIDATION_FILTER_VALIDATION | VALIDATION_FILTER_PERFORMANCE

using DebuggingLevel = uint32_t;

namespace Message {
    enum class Severity {
        Verbose = VALIDATION_MSG_SEVERITY_VERBOSE,
        Warning = VALIDATION_MSG_SEVERITY_WARNING,
        Error = VALIDATION_MSG_SEVERITY_ERROR
    };

    std::string stringifySeverity(Severity severity) {
        switch (severity) {
        case Severity::Verbose:
            return "Verbose";
        case Severity::Warning:
            return "Warning";
        case Severity::Error:
            return "Error";
        }
        return "Unknown Severity";
    }

    Severity get(uint32_t s) {
        return static_cast<Severity>(s);
    }
}


struct DebuggingLevels {
    static const DebuggingLevel Verbose = VALIDATION_LEVEL_ALL;
    static const DebuggingLevel Warn = VALIDATION_LEVEL_WARN;
    static const DebuggingLevel Error = VALIDATION_LEVEL_ERROR;
};

std::string stringifyDebugLevel(DebuggingLevel level) {
    std::string s = "";
    if (level & VALIDATION_MSG_SEVERITY_VERBOSE) {
        s += "Verbose";
        if (level & VALIDATION_MSG_SEVERITY_WARNING) {
            s += " + Warning";
            if (level & VALIDATION_MSG_SEVERITY_ERROR) {
                s += " + Error";
                return s;
            }
            return s;
        }
        return s;
    }
    else {
        if (level & VALIDATION_MSG_SEVERITY_WARNING) {
            s += "Warning";
            if (level & VALIDATION_MSG_SEVERITY_ERROR) {
                s += " + Error";
                return s;
            }
            return s;
        }
        else if (level & VALIDATION_MSG_SEVERITY_ERROR) {
            return "Error";
        }
    }
    return "Unknown";
}

struct DebugFilter {
    bool passGeneral = true;
    bool passValidation = true;
    bool passPerformance = true;

    uint32_t flag() {
        if (!(passGeneral || passValidation || passPerformance)) {
            std::cerr << "Warning: Debug Filter will block all messages. This is not the recommended method for doing this. Disable validation layers instead.\n";
        }
        uint32_t f = 0;
        if (passGeneral) f |= VALIDATION_FILTER_GENERAL;
        if (passValidation) f |= VALIDATION_FILTER_VALIDATION;
        if (passPerformance) f |= VALIDATION_FILTER_PERFORMANCE;
        return f;
    }

    std::string stringify() {
        std::string str = "<DebugFilter ";
        if (passGeneral) {
            str += "General";

            if (passValidation) str += "| Validation";
            if (passGeneral) str += "| Perfo";
        } else {
            if (passValidation) {
                str += "Validation";
                if (passPerformance) str += " | Performance";
            }
            else if (passPerformance) str += "Performance";
        }
        str += ">";
        return str;
    }
};

std::string stringifyMessageType(uint32_t type) {
    switch (type) {
    case VALIDATION_FILTER_GENERAL:
        return "General";
    case VALIDATION_FILTER_VALIDATION:
        return "Validation";
    case VALIDATION_FILTER_PERFORMANCE:
        return "Performance";
    }
}


VKAPI_ATTR VkBool32 VKAPI_CALL defaultDebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    std::cout << Message::stringifySeverity(Message::get(messageSeverity)) << ": " << stringifyMessageType(messageType) << ": " << pCallbackData;

    return VK_FALSE;
}


class DebugMessenger
{
private:
    VkDebugUtilsMessengerEXT m_DebugMessenger;

    VulkanInstance* m_Instance;
    DebugFilter m_Filter;
    DebuggingLevel m_Level;

    PFN_vkDebugUtilsMessengerCallbackEXT m_Callback;

    bool m_Built = false;

public:

    DebugMessenger(VulkanInstance* instance, DebugFilter typeFilter, DebuggingLevel level); // default debug callback
    DebugMessenger(VulkanInstance* instance, DebugFilter typeFilter, DebuggingLevel level, PFN_vkDebugUtilsMessengerCallbackEXT callback); // custom debug callback

    DebugMessenger() {};

    VulkanInstance* getInstance();
    void setInstance(VulkanInstance* inst);

    PFN_vkDebugUtilsMessengerCallbackEXT getCallback();
    void setCallback(PFN_vkDebugUtilsMessengerCallbackEXT callback);

    DebugFilter getFilter();
    void setFilter(DebugFilter filter);

    DebuggingLevel getLevel();
    void setLevel(DebuggingLevel level);

    void build();
    bool isBuilt();
    
};

