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

#include "stdbool.h"
#include "vrui_pal.h"

#ifndef _VRUI_BASE_H_
#define _VRUI_BASE_H_

typedef struct {
	void (*OnGfxInit)();
	void (*OnGfxDraw)();

} vrui_gfx_init_struct;

typedef struct{
	vrui_gfx_init_struct Gfx;

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

typedef struct {
	float X, Y, Z;
	float A, B, G;

} vrui_rect;

typedef struct {
	float X0, Y0, Z0, W0;
	float X1, Y1, Z1, W1;
	float X2, Y2, Z2, W2;
	float X3, Y3, Z3, W3;

} vrui_transform;

typedef struct {


	char Name[512];

} vrui_window;

typedef struct {
	float X, Y, Z;
	float UVX, UVY;

} vrui_vert;

#endif
