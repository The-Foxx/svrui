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

	*ItPtr = { Rect->X, Rect->Y, ZPos };
	ItPtr++;
	*ItPtr = { Rect->A, Rect->Y, ZPos };
	ItPtr++;
	*ItPtr = { Rect->A, Rect->B, ZPos };
	ItPtr++;
	*ItPtr = { Rect->X, Rect->B, ZPos };

}

void vrui_gfx_grow_vert(vrui_window* Window, int Num, int Trans, int Ord) {
//    TODO(clara): Implement

}
