////////////////////////////////////////////////////////////////////////////
//
//  SVRUI Source File.
//  Copyright (C) 2024 Clara Lille
// -------------------------------------------------------------------------
//  File name:   vrui_iter.c
//  Version:     v1.00
//  Created:     29/01/24 by Clara.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#include "../vrui.h"
#include "stdio.h"

void vrui_log_impl(const char* Log){
	printf("%s\n", Log);

}

int main(int argc, char* argv[]){
	vrui_gfx_init_struct InitGfx;
	InitGfx.OnGfxInit = NULL;
	InitGfx.OnGfxDraw = NULL;

	vrui_init_struct InitStruct;
	InitStruct.Gfx = InitGfx;

	vrui_setup_console_callback(&vrui_log_impl);
	vrui_init(InitStruct);

	return 0;

}
