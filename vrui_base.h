////////////////////////////////////////////////////////////////////////////
//
//  SVRUI Source File.
//  Copyright (C) 2024 Clara Lille
// -------------------------------------------------------------------------
//  File name:   vrui_base.h
//  Version:     v1.00
//  Created:     25/01/24 by Clara.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#include "pthread.h"
#include "stdbool.h"

#ifndef _VRUI_BASE_H_
#define _VRUI_BASE_H_
typedef pthread_mutex_t vrui_mutex;

typedef struct{


} vrui_init_struct;

typedef struct {

} vrui_st_gfx_func_struct;

typedef struct {

} vrui_onrender_info;

typedef struct {
	void* DataPtr;
	vrui_mutex Mutex;
	void (*FuncPtr)(vrui_onrender_info Onrenderinfo);

} vrui_job;

typedef struct {
	void* DataPtr;
	vrui_mutex Mutex;
	void (*FuncPtr)(vrui_onrender_info Onrenderinfo);
	int Index;
	bool ShouldRender;

} vrui_job_internal;

#endif
