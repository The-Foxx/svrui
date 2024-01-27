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



	return 0;

}

void vrui_setup_console_callback(void (*FuncPtr)(const char*)) {


}
