////////////////////////////////////////////////////////////////////////////
//
//  SVRUI Source File.
//  Copyright (C) 2024 Clara Lille
// -------------------------------------------------------------------------
//  File name:   vrui.c
//  Version:     v1.00
//  Created:     24/01/24 by Clara.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#define VRUI_IMPL
#include "vrui.h"
#include "string.h"
#include "vrui_window.h"

static void (*ConsoleCallback)(const char*) = NULL;
static bool IsConsoleVerbose = true;

void vrui_log(const char* Str){
	if (ConsoleCallback != NULL) {
		ConsoleCallback(Str);

	}

}

void vrui_log_verbose(const char* Str) {
	if (IsConsoleVerbose) {
		if (ConsoleCallback != NULL) {
			ConsoleCallback(Str);

		}

	}

}

void vrui_set_console_state(bool Verbose) {
	IsConsoleVerbose = Verbose;

}

int vrui_init(vrui_init_struct Info){
	VRCNFV("Initializing SVRUI");
	vrui_window_init();

	return 0;

}

void vrui_setup_console_callback(void (*FuncPtr)(const char*)) {
	ConsoleCallback = FuncPtr;

}

void vrui_window_debug_dump_console(vrui_window* Window) {
	VRCNF("Window vert buffer :");

	{
		vrui_vert* VertIter = Window->VertBuf;
		for (int i = 0; i < Window->VertBufSize; i++) {
			VRC("    Vert %i X %f Y %f Z %f UVX %f UVY %f", i, VertIter->X, VertIter->Y, VertIter->Z, VertIter->UVX, VertIter->UVY);
			VertIter++;

		}

	}

	VRCNF("Window ord buffer :");
	{
		int* Iter = Window->OrdBuf;
		for (int i = 0; i < Window->OrdBufSize; i++) {
			VRC("    Index %i Vert %i", i, *Iter);
			Iter++;

		}

	}

}
