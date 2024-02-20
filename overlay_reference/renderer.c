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

#include "renderer.h"
#define VK_NO_PROTOTYPES
#include "vulkan/vulkan.h"
#include "lib/volk.h"
#include "string.h"
#include "stdio.h"
#include "stdbool.h"

#define EXTENSION_COUNT 16
#define VK_DEBUG_HELPER

static VkInstance Instance;
static VkPhysicalDevice PhysDevice;
static VkDevice Device;

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

	}

}

void init_renderer(){

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
//        	and check for other layers we may want
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

		VkDeviceCreateInfo CreateInfo;
		CreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		CreateInfo.pNext = NULL;
		CreateInfo.flags = 0;
		//CreateInfo.queueCreateInfoCount
		//CreateInfo.pQueueCreateInfos
		CreateInfo.enabledLayerCount = WantedDeviceLayersCount;

		VkResult CreateDeviceResult = vkCreateDevice(PhysDevice, (const VkDeviceCreateInfo*)&CreateInfo, NULL, &Device);
		printf("Device creation result %i", CreateDeviceResult);

	}

}


