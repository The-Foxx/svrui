////////////////////////////////////////////////////////////////////////////
//
//  SVRUI Source File.
//  Copyright (C) 2024 Clara Lille
// -------------------------------------------------------------------------
//  File name:   vrui_window.c
//  Version:     v1.00
//  Created:     30/01/24 by Clara.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#define VRUI_IMPL
#include "vrui.h"
#include "vrui_window.h"

static vrui_window* WindowRegPtr = NULL;
static int WindowRegSize = 0;
static int WindowRegAlloc = 0;

void vrui_window_grow(int Size){
	if (Size > WindowRegAlloc) {
		int NewTargetSize = WindowRegAlloc * 2;
		WindowRegPtr = vrui_realloc(WindowRegPtr, NewTargetSize * sizeof(vrui_window));

	}

}

void vrui_window_init() {
	WindowRegPtr = vrui_alloc(sizeof(vrui_window) * 16);
	WindowRegAlloc = 16;

	return;

}

vrui_window* vrui_get_window(int Index) {
	if (Index > WindowRegSize) {
		VRC("Error trying to acces window at index %i but array is %i", Index, WindowRegSize);

	}

	vrui_window* Result = WindowRegPtr + Index;
	return Result;

}

vrui_window* vrui_new_window(vrui_job InJob) {
	vrui_window* Result;
	Result = WindowRegPtr + WindowRegSize;
	Result->FuncPtr = InJob.FuncPtr;
	Result->SteadyPtr = InJob.SteadyPtr;
	Result->DataPtr = InJob.DataPtr;
	Result->UserMutex = InJob.Mutex;
	vrui_new_window_init(Result);

	return Result;

}

void vrui_new_window_init(vrui_window* Window) {
	{
		Window->VertBuf = vrui_alloc(1024 * sizeof(vrui_vert));

	}

}
