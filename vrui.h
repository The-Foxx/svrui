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

#include "vrui_base.h"

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

#ifdef __cplusplus
extern "c" {

#endif

#define VRC(string, ...) char[1024] String; \
	sprintf(&String, string, __VA_ARGS__); \
	vrui_log(String)

#define VRCV(string, ...) char[1024] String; \
	sprintf(&String, string, __VA_ARGS__); \
	vrui_log_verbose(String)

#define VRCNF(string) vrui_log(string)
#define VRCNFV(string) vrui_log_verbose(string)

//    internal funcs
	void vrui_log(const char* Str);
	void vrui_log_verbose(const char* Str);

	VRUI_API void vrui_setup_console_callback(void (*FuncPtr)(const char*));
	VRUI_API void vrui_set_console_state(bool Verbose);
	VRUI_API int vrui_init(vrui_init_struct Info);

	VRUI_API void vrui_set_global_offset(float X, float Y, float Z);

//    ui api
	VRUI_API bool vrui_button(const char* Name);
	VRUI_API void vrui_checkbox(bool* Value, const char* Name);
	VRUI_API void vrui_text(const char* Text);

#ifdef __cplusplus
}
#endif

#endif
