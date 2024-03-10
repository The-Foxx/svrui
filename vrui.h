////////////////////////////////////////////////////////////////////////////
//
//  SVRUI Source File.
//  Copyright (C) 2024 Clara Lille
// -------------------------------------------------------------------------
//  File name:   vrui.h
//  Version:     v1.00
//  Created:     24/01/24 by Clara.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#include "vrui_base.h"

#ifndef _VRUI_H_
#define _VRUI_H_

#ifdef VRUI_SHARED
#ifdef _WIN32
#define VRUI_EXPORT __declspec( dllexport )
#define VRUI_IMPORT __declspec( dllimport )

#else
#define VRUI_EXPORT __attribute__((visibility("default")))
#define VRUI_IMPORT

#endif

#ifdef VRUI_IMPL
#define VRUI_API VRUI_EXPORT

#else
#define VRUI_API VRUI_IMPORT

#endif
#else
#define VRUI_API

#endif

#ifdef __cplusplus
extern "c" {

#endif

//    TODO(clara): Implement !!!!!!!!!!
#define VRUI_ASSERT (expression)

#ifdef VRUI_LOG_DISABLE
#define VRC(string, ...)
#define VRCV(string, ...)
#define VRCNF(string)
#define VRCNFV(string)

#else
#define VRC(string, ...) { char String[1024]; \
    sprintf(&String[0], string, __VA_ARGS__); \
    vrui_log(String); }

#define VRCV(string, ...) { char String[1024]; \
    sprintf(&String[0], string, __VA_ARGS__); \
    vrui_log_verbose(String); }

#define VRCNF(string) vrui_log(string)
#define VRCNFV(string) vrui_log_verbose(string)

#endif

#define VRUI_MAX_MUTEX_DURATION 2000

    extern int vrui_frame_count;
    extern int vrui_steady_count;
    extern vrui_window* vrui_implicit_window;
    extern float vrui_global_scale;

//    internal funcs
    void vrui_log(const char* Str);
    void vrui_log_verbose(const char* Str);
    void* vrui_alloc(size_t Size);
    void* vrui_realloc(void* Ptr, size_t Size);
    void vrui_free(void* Ptr);

//    Pre init
    VRUI_API void vrui_setup_console_callback(void (*FuncPtr)(const char*));
    VRUI_API void vrui_set_console_state(bool Verbose);
//    Init
    VRUI_API int vrui_init(vrui_init_struct Info);
    VRUI_API void vrui_easy_init();
//    Debug
    VRUI_API void vrui_window_debug_dump_console(vrui_window* Window);
//    Update
    VRUI_API void vrui_update();
    VRUI_API vrui_window* vrui_get_implicit_window();

//        LIB STATE
    VRUI_API void vrui_set_global_offset(float X, float Y, float Z);
    VRUI_API void vrui_set_global_scale(float Rhs);
    VRUI_API bool vrui_scry();
    VRUI_API void vrui_set_scry();

//        WINDOW
    VRUI_API vrui_window* vrui_new_window(vrui_job InJob, const char* Name);
    VRUI_API void vrui_delete_window(vrui_window* Window);
    VRUI_API vrui_window* vrui_get_window(int Index);

//        GUI
    VRUI_API bool vrui_button(const char* Name);
    VRUI_API void vrui_checkbox(bool* Value, const char* Name);
    VRUI_API void vrui_text(const char* Text);

//    Notification
    VRUI_API void vrui_notif(const char* Text, float* Completion, unsigned int* NumberCompletion, vrui_tex Tex, vrui_uva Uva);
    VRUI_API void vrui_notif_text(const char* Text, vrui_tex Tex, vrui_uva Uva);

//        GFX
    VRUI_API void vrui_gfx_quad(vrui_window* Window, vrui_rect* Rect, vrui_tex Tex, vrui_uva Uvc, bool IsTransparent);
    VRUI_API void vrui_gfx_box(vrui_window* Window, vrui_rect* Rect, vrui_tex Tex, vrui_uva Uvc, bool IsTransparent);
    VRUI_API void vrui_gfx_tri_list(vrui_window* Window, vrui_vert* VertPtr, int VertNumber,
                                    int* OrdPtr, int OrdNumber, bool IsTransparent);
    
//    Raw gpu buffer
    VRUI_API void vrui_gfx_grow_vert(vrui_window* Window, int Num, int Trans, int Ord, int AOrd);

#ifdef __cplusplus
}
#endif

#endif
