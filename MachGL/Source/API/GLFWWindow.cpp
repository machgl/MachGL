/*

Mach::GL (Alpha)

*/

#include "../../Headers/API/GLFWWindow.h"

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

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {

    MachGL::MACH_VULKAN_MSG("Validation layer: " + (std::string)pCallbackData->pMessage);
    return VK_FALSE;
}

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

namespace MachGL {
    
    #if defined(MACH_PLATFORM_WINDOWS)
        void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
            fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
                (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
                type, severity, message);
        }
    #endif

    GLFWWindow::GLFWWindow(const std::string& title, const uint32_t& width, const uint32_t& height) {
        
        m_title = title;
        m_width = (int)width;
        m_height = (int)height;
        m_icons[0] = GLFWimage();
    }

    void GLFWWindow::init() {
        
        m_previousTime = glfwGetTime();
        m_frameCount = 0;

        for (auto i : m_keys) i = false;
        for (auto i : m_mouseButtons) i = false;
        
        #if defined(MACH_VALID_PLATFORM)
            if (!glfwInit()) {
                
                MACH_ERROR_MSG("GLFW failed to initilize");
                return;
            }
        #endif

        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);

        #if defined(MACH_PLATFORM_MAC)
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #elif defined(MACH_PLATFORM_WINDOWS)
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        #endif

        glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_SAMPLES, m_aa);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

        if (m_fullscreen) m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), glfwGetPrimaryMonitor(), NULL);
        else m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);

        if (!m_window) {

            glfwTerminate();
            MACH_ERROR_MSG("Window failed to create");
            return;
        }

        initAudioDevice();

        if (!m_cursor) glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
       
        m_icons[0].pixels = stbi_load(m_iconPath.c_str(), &m_icons[0].width, &m_icons[0].height, 0, 4);
        glfwSetWindowIcon(m_window, 1, m_icons);
        stbi_image_free(m_icons[0].pixels);

        glfwMakeContextCurrent(m_window);

        #if defined(MACH_PLATFORM_WINDOWS)
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

                glfwTerminate();
                MACH_ERROR_MSG("Could not initilize OpenGL");
                return;
            }

            if (m_debug) {

                glEnable(GL_DEBUG_OUTPUT);
                glDebugMessageCallback(MessageCallback, 0);
            }
        #endif

        glfwGetFramebufferSize(m_window, (int*)&m_width, (int*)&m_height);
        glViewport(0, 0, m_width, m_height);
        #if defined(MACH_PLATFORM_MAC)
         glfwGetWindowContentScale(m_window, &m_xScale, &m_yScale);
        #endif
        glfwSetWindowUserPointer(m_window, this);
        glfwSetWindowUserPointer(m_window, this);
        
        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            
            GLFWWindow* win = (GLFWWindow*)glfwGetWindowUserPointer(window);
            win->m_keys[key] = action != GLFW_RELEASE;
        });
        
        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
            
            GLFWWindow* win = (GLFWWindow*)glfwGetWindowUserPointer(window);
            win->m_mouseButtons[button] = action != GLFW_RELEASE;
        });
        
        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
            MACH_CLOSE();
        });
        
        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
            
            GLFWWindow* win = (GLFWWindow*)glfwGetWindowUserPointer(window);
            win->mx = xpos;
            win->my = ypos;
        });
        
        m_APIVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
        m_graphicsCard = reinterpret_cast<const char*>(glGetString(GL_RENDERER));

        MACH_MSG("Mach::GL Version: " + MACH_GET_VERSION() + " | OpenGL Version: " + m_APIVersion + " | Graphics Card: " + m_graphicsCard);

        if (m_vsync) glfwSwapInterval(1);
        else glfwSwapInterval(0);

        m_splashImage = Graphics::Image::createImage("../MachGL/CoreAssets/CoreTextures/splash.png", Graphics::ImageType::RGBA);
        m_splashScreen = make_sPoint<Splash>(this->getWindowDimension(), m_splashImage);
    }

    void GLFWWindow::checkOpenGLError() {

        GLenum errorCode;

        while ((errorCode = glGetError()) != GL_NO_ERROR) {

            std::string error;

            switch (errorCode) {

                case GL_INVALID_ENUM: error = "INVALID ENUM"; break;
                case GL_INVALID_VALUE: error = "INVALID VALUE"; break;
                case GL_INVALID_OPERATION: error = "INVALID OPERATION"; break;
                case GL_OUT_OF_MEMORY: error = "OUT OF MEMORY"; break;
                case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID FRAMEBUFFER OPERATION"; break;
                #if defined(MACH_PLATFORM_WINDOWS)
                    case GL_STACK_OVERFLOW: error = "STACK OVERFLOW"; break;
                    case GL_STACK_UNDERFLOW: error = "STACK UNDERFLOW"; break;
                    case GL_CONTEXT_LOST: error = "CONTEXT LOST"; break;
                #endif
            }

            MACH_ERROR_MSG("OpenGL Error: " + error + " (" + std::to_string(errorCode) + ")");
        }
    }

    void GLFWWindow::update() {
        
        if (m_window == nullptr) {

            MACH_ERROR_MSG("Window is not initilized, make sure you call init()");
            return;
        }

        checkOpenGLError();
        checkOpenALError();

        if (m_aa) glEnable(GL_MULTISAMPLE);

        if (!m_isLoaded) {
            if (m_timer.elapsedTimeSeconds() > 2) {

                m_splashScreen->setAlpha(3 - (float)m_timer.elapsedTimeSeconds());
            }

            m_splashScreen->render();
        }

        if (m_timer.elapsedTimeSeconds() > 3) {

            windowLoaded();
            m_timer.~Timer();
        }

        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    void GLFWWindow::clear() {

        if (m_window == nullptr) {

            MACH_ERROR_MSG("Window is not initilized, make sure you call init()");
            return;
        }

        glViewport(0, 0, m_width, m_height);

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    bool GLFWWindow::closed() const {  return glfwWindowShouldClose(m_window) == 1; }

    void GLFWWindow::close() {

        glfwTerminate();
    }

    VulkanGLFWWindow::VulkanGLFWWindow(const std::string& title, const uint32_t& width, const uint32_t& height) {

        m_title = title;
        m_width = (int)width;
        m_height = (int)height;
        m_icons[0] = GLFWimage();
    }

    void VulkanGLFWWindow::init() {

        m_previousTime = glfwGetTime();
        m_frameCount = 0;

        for (auto i : m_keys) i = false;
        for (auto i : m_mouseButtons) i = false;

        #if defined(MACH_VALID_PLATFORM)
            if (!glfwInit()) {

                MACH_ERROR_MSG("GLFW failed to initilize");
                return;
            }
        #endif

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        
        m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

        if (!m_window) {

            glfwTerminate();
            MACH_ERROR_MSG("Window failed to create");
            return;
        }

        if (!m_cursor) glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        createInstance();
        setupDebugMessenger();
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice();
        createSwapChain();
        createImageViews();

        m_icons[0].pixels = stbi_load(m_iconPath.c_str(), &m_icons[0].width, &m_icons[0].height, 0, 4);

        glfwSetWindowIcon(m_window, 1, m_icons);
        stbi_image_free(m_icons[0].pixels);

        glfwSetWindowUserPointer(m_window, this);
        glfwSetWindowUserPointer(m_window, this);

        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {

            GLFWWindow* win = (GLFWWindow*)glfwGetWindowUserPointer(window);
            win->m_keys[key] = action != GLFW_RELEASE;
            });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {

            GLFWWindow* win = (GLFWWindow*)glfwGetWindowUserPointer(window);
            win->m_mouseButtons[button] = action != GLFW_RELEASE;
            });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
            MACH_CLOSE();
            });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {

            GLFWWindow* win = (GLFWWindow*)glfwGetWindowUserPointer(window);
            win->mx = xpos;
            win->my = ypos;
            });

        uint32_t vulkanVersion;
        vkEnumerateInstanceVersion(&vulkanVersion);
        m_APIVersion = vulkanPackedToString(vulkanVersion);

        MACH_MSG("Mach::GL Version: " + MACH_GET_VERSION() + " | Vulkan Version: " + m_APIVersion + " | Graphics Card: " + m_graphicsCard);

        if (m_vsync) glfwSwapInterval(1);
        else glfwSwapInterval(0);
    }

    void VulkanGLFWWindow::update() {

        glfwPollEvents();
    }

    void VulkanGLFWWindow::createInstance() {

        if (m_debug && !checkValidationLayerSupport())
            MACH_ERROR_MSG("Vulkan validation layers requested, but not available");
        
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = m_title.c_str();
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Mach::GL";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        
        if (m_debug) {
            
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();

            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
        }
        else {

            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }

        if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS)
            MACH_ERROR_MSG("Failed to create Vulkan instance");
    }

    void VulkanGLFWWindow::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
        
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
    }

    void VulkanGLFWWindow::setupDebugMessenger() {
        
        if (!m_debug) return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo;
        populateDebugMessengerCreateInfo(createInfo);

        if (CreateDebugUtilsMessengerEXT(m_instance, &createInfo, nullptr, &m_debugMessenger) != VK_SUCCESS)
            MACH_ERROR_MSG("Failed to set up Vulkan debug messenger");
    }

    void VulkanGLFWWindow::createSurface() {
        
        if (glfwCreateWindowSurface(m_instance, m_window, nullptr, &m_surface) != VK_SUCCESS) {
            MACH_ERROR_MSG("Failed to create Vulkan window surface");
        }
    }

    void VulkanGLFWWindow::pickPhysicalDevice() {
        
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);

        if (deviceCount == 0)
           MACH_ERROR_MSG("Failed to find GPUs with Vulkan support");

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());

        for (const auto& device : devices) {

            if (isDeviceSuitable(device)) {

                m_physicalDevice = device;
                break;
            }
        }

        if (m_physicalDevice == VK_NULL_HANDLE)
            MACH_ERROR_MSG("Failed to find a suitable GPU");
    }

    void VulkanGLFWWindow::createLogicalDevice() {

        QueueFamilyIndices indices = findQueueFamilies(m_physicalDevice);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceProperties deviceProperties{};
        vkGetPhysicalDeviceProperties(m_physicalDevice, &deviceProperties);
        m_graphicsCard = deviceProperties.deviceName;
        
        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();

        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();

        if (m_debug) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }

        vkGetDeviceQueue(m_device, indices.graphicsFamily.value(), 0, &m_graphicsQueue);
        vkGetDeviceQueue(m_device, indices.presentFamily.value(), 0, &m_presentQueue);
    }

    void VulkanGLFWWindow::createSwapChain() {

        SwapChainSupportDetails swapChainSupport = querySwapChainSupport(m_physicalDevice);

        VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
        VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
        VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = m_surface;

        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        QueueFamilyIndices indices = findQueueFamilies(m_physicalDevice);
        uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

        if (indices.graphicsFamily != indices.presentFamily) {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
        else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;

        createInfo.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(m_device, &createInfo, nullptr, &m_swapChain) != VK_SUCCESS) {
            throw std::runtime_error("failed to create swap chain!");
        }

        vkGetSwapchainImagesKHR(m_device, m_swapChain, &imageCount, nullptr);
        m_swapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(m_device, m_swapChain, &imageCount, m_swapChainImages.data());

        m_swapChainImageFormat = surfaceFormat.format;
        m_swapChainExtent = extent;
    }

    void VulkanGLFWWindow::createImageViews() {

        m_swapChainImageViews.resize(m_swapChainImages.size());

        for (size_t i = 0; i < m_swapChainImages.size(); i++) {

            VkImageViewCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.image = m_swapChainImages[i];
            createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            createInfo.format = m_swapChainImageFormat;
            createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            createInfo.subresourceRange.baseMipLevel = 0;
            createInfo.subresourceRange.levelCount = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount = 1;

            if (vkCreateImageView(m_device, &createInfo, nullptr, &m_swapChainImageViews[i]) != VK_SUCCESS)
                MACH_ERROR_MSG("Failed to create Vulkan image views");
        }
    }

    VkSurfaceFormatKHR VulkanGLFWWindow::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {

        for (const auto& availableFormat : availableFormats) {

            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
                return availableFormat;
        }

        return availableFormats[0];
    }

    VkPresentModeKHR VulkanGLFWWindow::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {

        for (const auto& availablePresentMode : availablePresentModes) {

            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
                return availablePresentMode;
        }

        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D VulkanGLFWWindow::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
       
        if (capabilities.currentExtent.width != UINT32_MAX) {

            return capabilities.currentExtent;
        }
        else {

            int width, height;
            glfwGetFramebufferSize(m_window, &width, &height);

            VkExtent2D actualExtent = {

                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)
            };

            actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
            actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

            return actualExtent;
        }
    }

    SwapChainSupportDetails VulkanGLFWWindow::querySwapChainSupport(VkPhysicalDevice device) {
        
        SwapChainSupportDetails details;

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, nullptr);

        if (formatCount != 0) {

            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {

            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, details.presentModes.data());
        }

        return details;
    }

    bool VulkanGLFWWindow::isDeviceSuitable(VkPhysicalDevice physicalDevice) {

        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

        bool extensionsSupported = checkDeviceExtensionSupport(physicalDevice);

        return indices.isComplete() && extensionsSupported;
    }

    bool VulkanGLFWWindow::checkDeviceExtensionSupport(VkPhysicalDevice device) {

        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto& extension : availableExtensions) requiredExtensions.erase(extension.extensionName);
        
        return requiredExtensions.empty();
    }
    QueueFamilyIndices VulkanGLFWWindow::findQueueFamilies(VkPhysicalDevice device) {
        
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;

        for (const auto& queueFamily : queueFamilies) {

            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                indices.graphicsFamily = i;
            
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface, &presentSupport);

            if (presentSupport) indices.presentFamily = i;
            if (indices.isComplete()) break;
            
            i++;
        }

        return indices;
    }

    std::vector<const char*> VulkanGLFWWindow::getRequiredExtensions() {

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (m_debug) extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    
        return extensions;
    }

    bool VulkanGLFWWindow::checkValidationLayerSupport() {

        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* layerName : validationLayers) {

            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {

                if (strcmp(layerName, layerProperties.layerName) == 0) {

                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) return false;
        }

        return true;
    }

    void VulkanGLFWWindow::clear() {

    }

    bool VulkanGLFWWindow::closed() const { return glfwWindowShouldClose(m_window) == 1; }

    void VulkanGLFWWindow::close() {

        vkDestroyDevice(m_device, nullptr);

        if (m_debug) DestroyDebugUtilsMessengerEXT(m_instance, m_debugMessenger, nullptr);
        
        vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
        vkDestroyInstance(m_instance, nullptr);
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }
}
