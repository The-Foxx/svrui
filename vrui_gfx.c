////////////////////////////////////////////////////////////////////////////
//
//  SVRUI Source File.
//  Copyright (C) 2024 Clara Lille
// -------------------------------------------------------------------------
//  File name:   vrui_gfx.c
//  Version:     v1.00
//  Created:     27/01/24 by Clara.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#include "vrui_gfx.h"
#define VRUI_IMPL
#include "vrui.h"

void vrui_gfx_quad(vrui_window* Window, vrui_rect* Rect, vrui_tex Tex, vrui_uva Uvc, bool IsTransparent){
	vrui_gfx_grow_vert(Window, 4, 4, 6);

	vrui_vert* ItPtr;
	if (IsTransparent) {
		ItPtr = Window->AlphaBuf;
		ItPtr += Window->AlphaBufSize;

	} else {
		ItPtr = Window->VertBuf;
		ItPtr += Window->VertBufSize;

	}

	const float ZPos = Rect->Z;

	vrui_vert Vert1 = { .X = Rect->X, .Y = Rect->Y, .Z = ZPos, .UVX = 0, .UVY = 0 };
	*ItPtr = Vert1;
	ItPtr++;

	vrui_vert Vert2 = { .X = Rect->A, .Y = Rect->Y, .Z = ZPos, .UVX = 0, .UVY = 0 };
	*ItPtr = Vert2;
	ItPtr++;

	vrui_vert Vert3 = { .X = Rect->A, .Y = Rect->B, .Z = ZPos, .UVX = 0, .UVY = 0 };
	*ItPtr = Vert3;
	ItPtr++;

	vrui_vert Vert4 = { .X = Rect->X, .Y = Rect->B, .Z = ZPos, .UVX = 0, .UVY = 0 };
	*ItPtr = Vert4;

}

void vrui_gfx_grow_vert(vrui_window* Window, int Num, int Trans, int Ord) {
//    TODO(clara): Implement

}
