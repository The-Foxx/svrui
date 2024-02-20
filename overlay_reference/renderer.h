////////////////////////////////////////////////////////////////////////////
//
//  SVRUI Source File.
//  Copyright (C) 2024 Clara Lille
// -------------------------------------------------------------------------
//  File name:   renderer.h
//  Version:     v1.00
//  Created:     19/02/24 by Clara.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#define VK_NO_PROTOTYPES
#include "vulkan/vulkan_core.h"

#ifndef _RENDERER_H_
#define _RENDERER_H_
void init_renderer();
void renderer_device_type_to_string(VkPhysicalDeviceType Type, char* Str);

#endif
