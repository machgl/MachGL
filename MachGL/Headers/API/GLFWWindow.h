/*

Mach::GL (Alpha)

*/

#pragma once

#include "MachPCH.h"
#include "../Core/DataStructures.h"
#include "../Core/Window.h"

namespace MachGL {

	class GLFWWindow : public Window {

		private:
			GLFWwindow* m_window;
            GLFWimage m_icons[1];

		public:
			GLFWWindow(const std::string& title, const uint32_t& width, const uint32_t& height);
            ~GLFWWindow() = default;
        
            void init() override;
            void update() override;
            void clear() override;
            bool closed() const override;
            void close() override;
        private:
            void checkOpenGLError();
	};

    class VulkanGLFWWindow : public Window {

        private: 
            GLFWwindow* m_window;
            GLFWimage m_icons[1];
            VkInstance m_instance;
            VkDebugUtilsMessengerEXT m_debugMessenger;
            VkSurfaceKHR m_surface;
            VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
            VkDevice m_device;
            VkQueue m_graphicsQueue;
            VkQueue m_presentQueue;
            VkSwapchainKHR m_swapChain;
            std::vector<VkImage> m_swapChainImages;
            VkFormat m_swapChainImageFormat;
            VkExtent2D m_swapChainExtent;
            std::vector<VkImageView> m_swapChainImageViews;
            ALCdevice* m_audioDevice = nullptr;
            ALboolean m_enumeration;
            ALCcontext* m_audioContext;
            
    public:
        VulkanGLFWWindow(const std::string& title, const uint32_t& width, const uint32_t& height);
        ~VulkanGLFWWindow() = default;

        void init() override;
        void update() override;
        void clear() override;
        bool closed() const override;
        void close() override;
        void createInstance();
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        void setupDebugMessenger();
        void createSurface();
        void pickPhysicalDevice();
        void createLogicalDevice();
        void createSwapChain();
        void createImageViews();
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        bool isDeviceSuitable(VkPhysicalDevice phsycialDevice);
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        std::vector<const char*> getRequiredExtensions();
        bool checkValidationLayerSupport();
    };
}
