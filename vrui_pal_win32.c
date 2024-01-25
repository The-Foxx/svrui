////////////////////////////////////////////////////////////////////////////
//
//  SVRUI Source File.
//  Copyright (C) 2024 Clara Lille
// -------------------------------------------------------------------------
//  File name:   vrui_pal_win32.c
//  Version:     v1.00
//  Created:     25/01/24 by Clara.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#define PAL_IMPL
#include "vrui_pal.h"
#include "vrui.h"

void vrui_init_mutex(vrui_mutex Mutex){
	Mutex.Mutex = CreateMutex(NULL, FALSE, NULL);

	if (Mutex.Mutex == NULL) {
		VRCNF("[ERROR] Could not create mutex");

	}

}

void vrui_destroy_mutex(vrui_mutex Mutex) {
	CloseHandle(Mutex.Mutex);

}

void vrui_lock_mutex(vrui_mutex Mutex) {
	DWORD Result = WaitForSingleObject(Mutex.Mutex, VRUI_MAX_MUTEX_DURATION);

	if (Result == 0x00000080L) {
		VRCNF("Mutex owning thread has being terminated without mutex unlock");

	}

	if (Result == 0x00000102L) {
		VRCNF("[ERROR] Mutex has reatched timeout");

	}

	if (Result == (DWORD)0xFFFFFFFF) {
		VRCNF("[ERROR] Unknown mutex error");

	}

}

void vrui_unlock_mutex(vrui_mutex Mutex) {
	BOOL Result = ReleaseMutex(Mutex.Mutex);
	if (Result == 0) {
		VRCNF("[ERROR] Failed to unlock mutex");

	}

}
