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

	vrui_window TestWindow;
	//TestWindow.VertBufSize = 4;
	//TestWindow.OrdBufSize = 6;
	//TestWindow.VertBuf = &TestWindow.VertBuffer[0];
	//TestWindow.OrdBuf = &TestWindow.OrdBuffer[0];

	vrui_window_debug_dump_console(&TestWindow);

	vrui_rect TestRect;
	TestRect.X = 0.1;
	TestRect.Y = 0.1;
	TestRect.Z = 0.1;
	TestRect.A = 0.9;
	TestRect.B = 0.9;
	TestRect.G = 0.9;

	vrui_tex TestTexture;
	vrui_uva TestUvc;
	TestUvc.X = 0.1;
	TestUvc.Y = 0.1;
	TestUvc.Z = 0.9;
	TestUvc.W = 0.9;

	vrui_gfx_quad(&TestWindow, &TestRect, TestTexture, TestUvc, false);
	vrui_gfx_quad(&TestWindow, &TestRect, TestTexture, TestUvc, false);

	vrui_window_debug_dump_console(&TestWindow);

	return 0;

}
