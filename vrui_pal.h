////////////////////////////////////////////////////////////////////////////
//
//  SVRUI Source File.
//  Copyright (C) 2024 Clara Lille
// -------------------------------------------------------------------------
//  File name:   vrui_pal.h
//  Version:     v1.00
//  Created:     25/01/24 by Clara.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
//#include "windows.h"
// Substituting windows.h for a few manual forward declarations
typedef void* HANDLE;

#else
#include "pthread.h"

#endif

#ifndef _VRUI_PAL_H_
#define _VRUI_PAL_H_
#ifdef VRUI_SHARED
#ifdef _WIN32
#define PAL_EXPORT __declspec( dllexport )
#define PAL_IMPORT __declspec( dllimport )

#else
#define PAL_EXPORT __attribute__((visibility("default")))
#define PAL_IMPORT

#endif

#ifdef PAL_IMPL
#define PAL_API PAL_EXPORT

#else
#define PAL_API PAL_IMPORT

#endif
#else
#define PAL_API

#endif

typedef struct{
#ifdef _WIN32
	HANDLE Mutex;

#else
	pthread_mutex_t Mutex;

#endif

} vrui_mutex;

PAL_API void vrui_init_mutex(vrui_mutex Mutex);
PAL_API void vrui_destroy_mutex(vrui_mutex Mutex);
PAL_API void vrui_lock_mutex(vrui_mutex Mutex);
PAL_API void vrui_unlock_mutex(vrui_mutex Mutex);

#endif
