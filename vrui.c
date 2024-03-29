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
#include "stdlib.h"

int vrui_frame_count = 0;
int vrui_steady_count = 0;
vrui_window* vrui_implicit_window = NULL;
float vrui_global_scale = 1.00f;

static void (*ConsoleCallback)(const char*) = NULL;
static bool IsConsoleVerbose = true;
static void* (*MallocCallback)(size_t) = NULL;
static void* (*ReallocCallback)(void*, size_t) = NULL;
static void (*FreeCallback)(void*) = NULL;

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

void* vrui_alloc(size_t Size) {
    if (MallocCallback == NULL) {
        return malloc(Size);

    }
    return MallocCallback(Size);

}

void* vrui_realloc(void* Ptr, size_t Size) {
    if (ReallocCallback == NULL) {
        return realloc(Ptr, Size);

    }
    return ReallocCallback(Ptr, Size);

}

void vrui_free(void* Ptr) {
    if (FreeCallback == NULL) {
        return free(Ptr);

    }
    return FreeCallback(Ptr);

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
    VRC("Printing debug for window name %s", Window->Name);
    VRC("VertBufSize: %i VertBufAlloc: %i OrdBufSize: %i OrdBufAlloc: %i",
        Window->VertBufSize, Window->VertBufAlloc, Window->OrdBufSize, Window->OrdBufAlloc);
    VRC("AlphaBufSize: %i AlphaBufAlloc: %i AOrdBufSize: %i AOrdBufAlloc: %i",
        Window->AlphaBufSize, Window->AlphaBufAlloc, Window->AOrdBufSize, Window->AOrdBufAlloc);
    
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
            VRC("    Index %i Vert %i", i, *Iter)
            Iter++;

        }

    }

}

void vrui_update() {
    vrui_window_render();

}

vrui_window* vrui_get_implicit_window() {
    return vrui_implicit_window;

}

void vrui_set_global_scale(float Rhs) {
    vrui_global_scale = Rhs;

}
