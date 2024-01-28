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

//    Rendering data
	vrui_transform Pos;
	vrui_vert* VertBuf;
	int VertBufSize;
	int VertBufAlloc;
	vrui_vert* AlphaBuf;
	int AlphaBufSize;
	int AlphaBufAlloc;
	int* OrdBuf;
	int OrdBufSize;
	int OrdBufAlloc;
//    TODO(clara): Make this a dynamic size buffer on the heap !!!
	vrui_vert VertBuffer[5000];
	vrui_vert AlphaBuffer[1000];
	int OrdBuffer[15000];

//    note(clara): This needs to be at the bottom for cache frienliness
//        because its a big enouth array that we dont want to have to pull up
//        two cache lines to get the window data for rendering and layout
	char Name[512];
	int NameSize;

} vrui_window;

typedef struct {
	float X, Y, Z;
	float UVX, UVY;

} vrui_vert;

typedef struct {
	float X, Y, Z, W;

} vrui_uva;

typedef struct {
//    TODO(clara): Implement texture handle !!!

} vrui_tex;

#endif
