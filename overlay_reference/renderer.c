////////////////////////////////////////////////////////////////////////////
//
//  SVRUI Source File.
//  Copyright (C) 2024 Clara Lille
// -------------------------------------------------------------------------
//  File name:   renderer.c
//  Version:     v1.00
//  Created:     19/02/24 by Clara.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif
#include "openvr_capi.h"

#include "renderer.h"
#define VK_NO_PROTOTYPES
#include "vulkan/vulkan.h"
#include "lib/volk.h"
#include "string.h"
#include "stdio.h"
#include "stdbool.h"
#include "overlay_input.h"
#include "stdlib.h"

#define EXTENSION_COUNT 16
#define VK_DEBUG_HELPER
#define USE_BIND_MEMORY_2

// Openvr frw
intptr_t VR_InitInternal( EVRInitError *peError, EVRApplicationType eType );
void VR_ShutdownInternal();
bool VR_IsHmdPresent();
intptr_t VR_GetGenericInterface( const char *pchInterfaceVersion, EVRInitError *peError );
bool VR_IsRuntimeInstalled();
const char * VR_GetVRInitErrorAsSymbol( EVRInitError error );
const char * VR_GetVRInitErrorAsEnglishDescription( EVRInitError error );


static VkInstance Instance;
static VkPhysicalDevice PhysDevice;
static VkDevice Device;
static float GraphicsQueuePriority = 1.0f;
static VkQueue GraphicsQueue;
static VROverlayHandle_t OverlayHandle;

// VR
struct VR_IVROverlay_FnTable* IVROverlay;
struct VR_IVRSystem_FnTable* IVRSys;
struct VR_IVRCompositor_FnTable* IVRComp;

void renderer_device_type_to_string(VkPhysicalDeviceType Type, char* Str) {
    switch (Type) {
        case(VK_PHYSICAL_DEVICE_TYPE_OTHER):
            strcpy(Str, "VK_PHYSICAL_DEVICE_TYPE_OTHER");
            break;
        case(VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU):
            strcpy(Str, "VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU");
            break;
        case(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU):
            strcpy(Str, "VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU");
            break;
        case(VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU):
            strcpy(Str, "VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU");
            break;
        case(VK_PHYSICAL_DEVICE_TYPE_CPU):
            strcpy(Str, "VK_PHYSICAL_DEVICE_TYPE_CPU");
            break;

        default:
            strcpy(Str, "\"Unknown physical device type in to string\"");
            break;

    }

}

void* renderer_get_ovr_interface(const char* InName) {
    EVRInitError Error;
    char InterfaceName[256];
    snprintf(InterfaceName, 256, "FnTable:%s", InName);
    void* Result = (void*)VR_GetGenericInterface(&InterfaceName[0], &Error);
    printf("Gathering %s with error code %i\n", InName, Error);
    if (Result == NULL) {
        printf("Failed to gather interface %s, openvr returned a null pointer\n", InName);
        exit(1);

    }
    return Result;

}

void init_renderer(){

//    Vr setup
    {
        EVRInitError VrError = 0;
        VR_InitInternal(&VrError, EVRApplicationType_VRApplication_Overlay);
        printf("Initialized openvr with error code %u\n", VrError);
        printf("IsHmdPresent: %i\n", VR_IsHmdPresent());

        IVRSys = renderer_get_ovr_interface(IVRSystem_Version);
        IVRComp = renderer_get_ovr_interface(IVRCompositor_Version);
        IVROverlay = renderer_get_ovr_interface(IVROverlay_Version);

    }

//    Vr overlay setup
    {
        IVROverlay->CreateOverlay(VRUI_OVERLAY_KEY, VRUI_OVERLAY_NAME, &OverlayHandle);

    }

//    Create instance
    {
        unsigned int ExtensionCount = 0;
        char ExtensionName[EXTENSION_COUNT][VK_MAX_EXTENSION_NAME_SIZE];
        int ExtensionNameCount = 0;
        unsigned int LayerCount = 0;
        char WantedLayerName[EXTENSION_COUNT][VK_MAX_EXTENSION_NAME_SIZE];
        int WantedLayerCount = 0;

        if (volkInitialize() != VK_SUCCESS) {
            printf("Failed to initialize vulkan loader\n");

        }

        vkEnumerateInstanceExtensionProperties(NULL, &ExtensionCount, NULL);
        printf("Number of instance extensions: %u\n", ExtensionCount);
        VkExtensionProperties ExtensionProperties[ExtensionCount + 1];
        vkEnumerateInstanceExtensionProperties(NULL, &ExtensionCount, &ExtensionProperties[0]);
        for (int i = 0; i < ExtensionCount; i++) {
            printf("    Name: %s Ver: %u\n", ExtensionProperties[i].extensionName, ExtensionProperties[i].specVersion);

        }

        vkEnumerateInstanceLayerProperties(&LayerCount, NULL);
        printf("Number of instance layers: %u\n", LayerCount);
        VkLayerProperties LayerProperties[LayerCount + 1];
        vkEnumerateInstanceLayerProperties(&LayerCount, &LayerProperties[0]);
        for (int i = 0; i < LayerCount; i++) {
            printf("    Name: %s Spec ver: %u Impl ver: %u Description: %s\n", LayerProperties[i].layerName,
                   LayerProperties[i].specVersion, LayerProperties[i].implementationVersion, LayerProperties[i].description);

        }

//        TODO(clara): Add proper handling if the instance extension or layer is wanted but not present
//            and check for other layers we may want
        #ifdef VK_DEBUG_HELPER
        strcpy(WantedLayerName[WantedLayerCount], "VK_LAYER_KHRONOS_validation");
        WantedLayerCount++;

        #endif

        VkApplicationInfo AppInfo;
        AppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        AppInfo.pNext = NULL;
        const char* AppName = "VRUI Overlay";
        AppInfo.pApplicationName = AppName;
        AppInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        const char* EngineName = "DISRUPT";
        AppInfo.pEngineName = EngineName;
        AppInfo.engineVersion = 0;
        AppInfo.apiVersion = VK_API_VERSION_1_1;

        VkInstanceCreateInfo CreateInfo;
        CreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        CreateInfo.pNext = NULL;
        CreateInfo.flags = 0;
        CreateInfo.pApplicationInfo = &AppInfo;
        CreateInfo.enabledLayerCount = WantedLayerCount;

        char* LayerPtr[EXTENSION_COUNT];
        for (int i = 0; i < EXTENSION_COUNT; i++) {
            LayerPtr[i] = WantedLayerName[i];

        }

        CreateInfo.ppEnabledLayerNames = (const char* const*)LayerPtr;
        CreateInfo.enabledExtensionCount = ExtensionNameCount;

        char* ExtensionPtr[EXTENSION_COUNT];
        for (int i = 0; i < EXTENSION_COUNT; i++) {
            ExtensionPtr[i] = ExtensionName[i];

        }
        CreateInfo.ppEnabledExtensionNames = (const char* const *)ExtensionPtr;

        VkResult InstanceResult = vkCreateInstance(&CreateInfo, NULL, &Instance);
        printf("Instance creation error code: %i\n", InstanceResult);
        volkLoadInstance(Instance);

    }

//    Physical device
    {
        bool IsPhysicalDeviceSelected = false;
        unsigned int PhysicalDeviceCount = 0;
        vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, NULL);
        printf("Number of physical devices %u\n", PhysicalDeviceCount);
        VkPhysicalDevice PhysicalDeviceArray[PhysicalDeviceCount + 1];
        vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, &PhysicalDeviceArray[0]);

        for (int i = 0; i < PhysicalDeviceCount; i++) {
            VkPhysicalDeviceProperties LocalDevicePropertiesIt;
            vkGetPhysicalDeviceProperties(PhysicalDeviceArray[i], &LocalDevicePropertiesIt);
            char DeviceTypeName[128];
            renderer_device_type_to_string(LocalDevicePropertiesIt.deviceType, &DeviceTypeName[0]);
            printf("    Number: %i, Name: %s, ApiVersion: %u, DriverVersion: %u, VendorId: %u, DeviceId: %u, DeviceType: %s\n", i,
                   &LocalDevicePropertiesIt.deviceName[0], LocalDevicePropertiesIt.apiVersion,
                   LocalDevicePropertiesIt.driverVersion, LocalDevicePropertiesIt.vendorID,
                   LocalDevicePropertiesIt.deviceID, &DeviceTypeName[0]);
            if (LocalDevicePropertiesIt.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
                if (!IsPhysicalDeviceSelected) {
                    PhysDevice = PhysicalDeviceArray[i];
                    printf("Selected physical device number %i\n", i);
                    IsPhysicalDeviceSelected = true;

                }

            }

        }

    }

//    Device
    {
        unsigned int WantedDeviceLayersCount = 0;
        char WantedDeviceLayersArray[16][VK_MAX_EXTENSION_NAME_SIZE];

        unsigned int DeviceLayerCount = 0;
        vkEnumerateDeviceLayerProperties(PhysDevice, &DeviceLayerCount, NULL);
        printf("Number of device layers: %u\n", DeviceLayerCount);
        VkLayerProperties DeviceLayerArr[DeviceLayerCount];
        vkEnumerateDeviceLayerProperties(PhysDevice, &DeviceLayerCount, &DeviceLayerArr[0]);

        for (int i = 0; i < DeviceLayerCount; i++) {
            printf("    LayerName %s, Ver: %u, ImplVer: %u, Description: %s\n", &DeviceLayerArr[i].layerName[0],
                   DeviceLayerArr[i].specVersion, DeviceLayerArr[i].implementationVersion,
                   &DeviceLayerArr[i].description[0]);

        }

        unsigned int DeviceExtensionCount = 0;
        vkEnumerateDeviceExtensionProperties(PhysDevice, NULL, &DeviceExtensionCount, NULL);
        printf("Device extensionCount %u\n", DeviceExtensionCount);
        VkExtensionProperties ExtensionArr[DeviceExtensionCount + 1];
        vkEnumerateDeviceExtensionProperties(PhysDevice, NULL, &DeviceExtensionCount, &ExtensionArr[0]);
        for (int i = 0; i < DeviceExtensionCount; i++) {
            printf("    Name %s, Version %u\n", &ExtensionArr[i].extensionName[0], ExtensionArr[i].specVersion);

        }

        unsigned int WantedDeviceExtensionCount = 0;
        char WantedDeviceExtensionArr[16][VK_MAX_EXTENSION_NAME_SIZE];

        #ifdef USE_BIND_MEMORY_2
        strcpy(&WantedDeviceExtensionArr[WantedDeviceExtensionCount][0], "VK_KHR_bind_memory2");
        WantedDeviceExtensionCount++;

        #endif

        strcpy(&WantedDeviceExtensionArr[WantedDeviceExtensionCount][0], "VK_KHR_synchronization2");
        WantedDeviceExtensionCount++;

        unsigned int DeviceQueueCount;
        vkGetPhysicalDeviceQueueFamilyProperties(PhysDevice, &DeviceQueueCount, NULL);
        printf("Number of queues %u\n", DeviceQueueCount);
        VkQueueFamilyProperties QueueFamilyArr[DeviceQueueCount + 1];
        vkGetPhysicalDeviceQueueFamilyProperties(PhysDevice, &DeviceQueueCount, &QueueFamilyArr[0]);

        unsigned int WantedQueueIndex = 0;
        bool WantedQueue = false;
        for (int i = 0; i < DeviceQueueCount; i++) {
            printf("    Index: %i, Count: %u, Flags: %x, MinImageGranularity W%u H%u D%u\n",
                   i, QueueFamilyArr[i].queueCount, QueueFamilyArr[i].queueFlags, QueueFamilyArr[i].minImageTransferGranularity.width,
                   QueueFamilyArr[i].minImageTransferGranularity.height, QueueFamilyArr[i].minImageTransferGranularity.depth);

            if (!WantedQueue) {
                if (QueueFamilyArr[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                    WantedQueue = true;
                    WantedQueueIndex = i;
                    printf("      Chose queue number %u\n", WantedQueueIndex);

                }

            }

        }

        VkDeviceQueueCreateInfo GraphQueueInfo;
        GraphQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        GraphQueueInfo.pNext = NULL;
        GraphQueueInfo.flags = 0;
        GraphQueueInfo.queueFamilyIndex = 0;
        GraphQueueInfo.queueCount = 1;
        GraphQueueInfo.pQueuePriorities = &GraphicsQueuePriority;


        VkDeviceCreateInfo CreateInfo;
        CreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        CreateInfo.pNext = NULL;
        CreateInfo.flags = 0;
        CreateInfo.queueCreateInfoCount = 1;
        CreateInfo.pQueueCreateInfos = &GraphQueueInfo;
        CreateInfo.enabledLayerCount = WantedDeviceLayersCount;
        
        char* LayerPtr[WantedDeviceLayersCount + 1];
        for (int i = 0; i < WantedDeviceLayersCount; i++) {
            LayerPtr[i] = WantedDeviceLayersArray[i];

        }
        CreateInfo.ppEnabledLayerNames = (const char* const*)LayerPtr;
        CreateInfo.enabledExtensionCount = WantedDeviceExtensionCount;
        
        char* ExtensionPtr[WantedDeviceExtensionCount];
        for (int i = 0; i < WantedDeviceExtensionCount; i++) {
            ExtensionPtr[i] = WantedDeviceExtensionArr[i];

        }

        CreateInfo.ppEnabledExtensionNames = (const char* const*)ExtensionPtr;
        CreateInfo.pEnabledFeatures = NULL;

        VkResult CreateDeviceResult = vkCreateDevice(PhysDevice, (const VkDeviceCreateInfo*)&CreateInfo, NULL, &Device);
        printf("Device creation result %i\n", CreateDeviceResult);

    }

}

void renderer_quit() {
    VR_ShutdownInternal();

}

void renderer_loop() {


}
