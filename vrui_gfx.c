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

int vrui_optimal_buffer_size(int StartSize, int TargetSize){
    int Result = StartSize;
    for (int i = 0; i < 100; i++) {
        if (Result > TargetSize) {
            return Result;

        }
        Result *= 2;

    }

    VRC("[ERROR] Could not determine adequate buffer size for target %i and start %i", TargetSize, StartSize);

}

void vrui_gfx_quad(vrui_window* Window, vrui_rect* Rect, vrui_tex Tex, vrui_uva Uvc, bool IsTransparent){
    vrui_gfx_grow_vert(Window, 4, 4, 6, 6);

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

#ifndef VRUI_NO_NULL_PTR_CHECK
    if (OrdPtr == NULL) {
        VRCNF("Error processing quad order generation");
        return;

    }

    if (ItPtr == NULL) {
        VRCNF("Error processing quad vertex generation");
        return;
    }

#endif

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

void vrui_gfx_grow_vert(vrui_window* Window, int Num, int Trans, int Ord, int AOrd) {
    if (Window->VertBufAlloc < (Window->VertBufSize + Num)) {
        //VRC("Not enouth vert space %i", vrui_optimal_buffer_size(Window->VertBufAlloc, Num));
        int NewTargetSize = vrui_optimal_buffer_size(Window->VertBufAlloc, Num);
        Window->VertBuf = (vrui_vert*)vrui_realloc(Window->VertBuf, NewTargetSize * sizeof(vrui_vert));
        Window->VertBufAlloc = NewTargetSize;

    }

    if (Window->OrdBufAlloc < (Window->OrdBufSize + Ord)) {
        //VRCNF("Not enouth ord space");
        int NewTargetsize = vrui_optimal_buffer_size(Window->OrdBufAlloc, Ord);
        Window->OrdBuf = (int*)vrui_realloc(Window->OrdBuf, NewTargetsize * sizeof(int));
        Window->OrdBufAlloc = NewTargetsize;

    }

    if (Window->AlphaBufAlloc < (Window->AlphaBufSize + Trans)) {
        //VRCNF("Not enouth Alpha space");
        int NewTargetSize = vrui_optimal_buffer_size(Window->AlphaBufAlloc, Trans);
        Window->AlphaBuf = (vrui_vert*)vrui_realloc(Window->AlphaBuf, NewTargetSize * sizeof(vrui_vert));
        Window->AlphaBufAlloc = NewTargetSize;

    }

    if (Window->AOrdBufAlloc < (Window->AOrdBufSize + AOrd)) {
        //VRCNF("Not enouth alpha ord space");
        int NewTargetSize = vrui_optimal_buffer_size(Window->AOrdBufAlloc, AOrd);
        Window->AOrdBuf = (int*)vrui_realloc(Window->AOrdBuf, NewTargetSize * sizeof(int));
        Window->AOrdBufAlloc = NewTargetSize;

    }

}
