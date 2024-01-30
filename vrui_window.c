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
#include "stdlib.h"

static vrui_window* WindowRegPtr = NULL;
static int WindowRegSize = 0;
static int WindowRegAlloc = 0;

void vrui_window_grow(int Size){
	if (Size > WindowRegAlloc) {
		int NewTargetSize = WindowRegAlloc * 2;
		WindowRegPtr = Realloc(WindowRegPtr, NewTargetSize * sizeof(vrui_window));

	}

}

void vrui_window_init() {
	WindowRegPtr = malloc(sizeof(vrui_window) * 16);
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
