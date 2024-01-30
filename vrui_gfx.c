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
	int* OrdPtr;
	int OrdFirst;
	if (IsTransparent) {
		OrdFirst = Window->AlphaBufSize;

		ItPtr = Window->AlphaBuf;
		ItPtr += Window->AlphaBufSize;
		Window->AlphaBufSize += 4;

		OrdPtr = Window->AOrdBuf;
		OrdPtr += Window->AOrdBufSize;
		Window->AOrdBufSize += 6;

	} else {
		OrdFirst = Window->VertBufSize;

		ItPtr = Window->VertBuf;
		ItPtr += Window->VertBufSize;
		Window->VertBufSize += 4;

		OrdPtr = Window->OrdBuf;
		OrdPtr += Window->OrdBufSize;
		Window->OrdBufSize += 6;

	}

	const float ZPos = Rect->Z;

	vrui_vert Vert1 = { .X = Rect->X, .Y = Rect->Y, .Z = ZPos, .UVX = Uvc.X, .UVY = Uvc.W };
	*ItPtr = Vert1;
	ItPtr++;

	vrui_vert Vert2 = { .X = Rect->A, .Y = Rect->Y, .Z = ZPos, .UVX = Uvc.Z, .UVY = Uvc.W };
	*ItPtr = Vert2;
	ItPtr++;

	vrui_vert Vert3 = { .X = Rect->A, .Y = Rect->B, .Z = ZPos, .UVX = Uvc.Z, .UVY = Uvc.Y };
	*ItPtr = Vert3;
	ItPtr++;

	vrui_vert Vert4 = { .X = Rect->X, .Y = Rect->B, .Z = ZPos, .UVX = Uvc.X, .UVY = Uvc.Y };
	*ItPtr = Vert4;

	*OrdPtr = OrdFirst;
	OrdPtr++;

	*OrdPtr = OrdFirst + 2;
	OrdPtr++;

	*OrdPtr = OrdFirst + 3;
	OrdPtr++;

	*OrdPtr = OrdFirst;
	OrdPtr++;
	
	*OrdPtr = OrdFirst + 1;
	OrdPtr++;

	*OrdPtr = OrdFirst + 2;

}

void vrui_gfx_grow_vert(vrui_window* Window, int Num, int Trans, int Ord) {
//    TODO(clara): Implement

}
