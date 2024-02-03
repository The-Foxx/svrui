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

static vrui_mutex* MutexPtr;

void vrui_log_impl(const char* Log){
	printf("%s\n", Log);

}

void vrui_func_impl(vrui_onrender_info Onrenderinfo) {
	vrui_lock_mutex(Onrenderinfo.UserMutex);
	vrui_window* WindowPtr = Onrenderinfo.CurrWindow;
	
	vrui_rect TestRect;
	TestRect.X = 0.2;
	TestRect.Y = 0.2;
	TestRect.Z = 0.2;
	TestRect.A = 0.8;
	TestRect.B = 0.8;
	TestRect.G = 0.8;

	vrui_tex TestTexture;
	vrui_uva TestUvc;
	TestUvc.X = 0.2;
	TestUvc.Y = 0.2;
	TestUvc.Z = 0.8;
	TestUvc.W = 0.8;

	vrui_gfx_quad(WindowPtr, &TestRect, TestTexture, TestUvc, false);
	vrui_gfx_quad(WindowPtr, &TestRect, TestTexture, TestUvc, false);
	vrui_gfx_quad(WindowPtr, &TestRect, TestTexture, TestUvc, false);

	vrui_unlock_mutex(Onrenderinfo.UserMutex);

}

int main(int argc, char* argv[]){
	vrui_gfx_init_struct InitGfx;
	InitGfx.OnGfxInit = NULL;
	InitGfx.OnGfxDraw = NULL;

	vrui_init_struct InitStruct;
	InitStruct.Gfx = InitGfx;

	vrui_setup_console_callback(&vrui_log_impl);
	vrui_init(InitStruct);

	vrui_window* TestWindow;
	vrui_job TestJob;
	TestJob.DataPtr = NULL;
	TestJob.SteadyPtr = NULL;
	MutexPtr = &TestJob.Mutex;
	TestJob.FuncPtr = &vrui_func_impl;

	TestWindow = vrui_new_window(TestJob, "test_window");

	vrui_window_debug_dump_console(TestWindow);

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

	vrui_update();

	vrui_gfx_quad(TestWindow, &TestRect, TestTexture, TestUvc, false);
	vrui_gfx_quad(TestWindow, &TestRect, TestTexture, TestUvc, false);

	vrui_window_debug_dump_console(TestWindow);
	vrui_gfx_grow_vert(TestWindow, 4680, 45000, 10000, 10000);
	vrui_update();
	vrui_window_debug_dump_console(TestWindow);

	return 0;

}
