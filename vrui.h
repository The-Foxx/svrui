////////////////////////////////////////////////////////////////////////////
//
//  SVRUI Source File.
//  Copyright (C) 2024 Clara Lille
// -------------------------------------------------------------------------
//  File name:   vrui.h
//  Version:     v1.00
//  Created:     24/01/24 by Clara.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////



#ifndef _VRUI_H_
#define _VRUI_H_

#ifdef VRUI_SHARED
#ifdef _WIN32
#define VRUI_EXPORT __declspec( dllexport )
#define VRUI_IMPORT __declspec( dllimport )

#else
#define VRUI_EXPORT __attribute__((visibility("default")))
#define VRUI_IMPORT

#endif

#ifdef VRUI_IMPL
#define VRUI_API VRUI_EXPORT

#else
#define VRUI_API VRUI_IMPORT

#endif
#else
#define VRUI_API

#endif

typedef struct{


} vrui_init_struct;

typedef struct {

} vrui_st_gfx_func_struct;

VRUI_API int vrui_init(vrui_init_struct Info);

VRUI_API void vrui_set_global_offset(float X, float Y, float Z);

#endif
