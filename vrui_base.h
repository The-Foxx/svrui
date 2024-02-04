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
#include "stdio.h"
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
	float X, Y, Z;
	float UVX, UVY;
	float A;

} vrui_vert;

typedef struct {
	void* CurrWindow;
	void* UserData;
	vrui_mutex UserMutex;

} vrui_onrender_info;

typedef struct {


//    Data that needs to be cleared every start
	float NextPosX, NextPosY, NextPosZ;

//    Scrolling
	float ScrollX, ScrollY, ScrollZ;

} vrui_layout;

typedef struct {
//    Update Data
	int DeltaTime;

//    Layout rendering
	vrui_layout RootLayour;
	vrui_layout* SubLayout;
	int SubLayoutSize;
	int SubLayoutAlloc;

//    Rendering data
	vrui_transform Pos;

//    User data
	void* DataPtr;
	vrui_mutex UserMutex;
	void (*FuncPtr)(vrui_onrender_info Onrenderinfo);
	void (*SteadyPtr)(vrui_onrender_info Onrenderinfo);

//    Cache line for rendering
	vrui_vert* VertBuf;
	int VertBufSize;
	int VertBufAlloc;
	vrui_vert* AlphaBuf;
	int AlphaBufSize;
	int AlphaBufAlloc;
	int* AOrdBuf;
	int AOrdBufSize;
	int AOrdBufAlloc;
	int* OrdBuf;
	int OrdBufSize;
	int OrdBufAlloc;

//    note(clara): This needs to be at the bottom for cache frienliness
//        because its a big enouth array that we dont want to have to pull up
//        two cache lines to get the window data for rendering and layout
	char Name[512];
	int NameSize;

} vrui_window;

typedef struct {
	float X, Y, Z, W;

} vrui_uva;

typedef struct {
//    TODO(clara): Implement texture handle !!!

} vrui_tex;

typedef struct {
	void* DataPtr;
	vrui_mutex Mutex;
	void (*FuncPtr)(vrui_onrender_info Onrenderinfo);
	void (*SteadyPtr)(vrui_onrender_info Onrenderinfo);

} vrui_job;

typedef struct {
	char Letter;
	vrui_uva TexCord;
	float XOffset;
	float YOffset;
	float YSize;

} vrui_letter;

typedef struct {
	vrui_letter* LetterArray;
	int LetterArraySize;
	vrui_tex AtlasTexture;

} vrui_font;

#endif
