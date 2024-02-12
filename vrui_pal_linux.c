////////////////////////////////////////////////////////////////////////////
//
//  SVRUI Source File.
//  Copyright (C) 2024 Clara Lille
// -------------------------------------------------------------------------
//  File name:   vrui_pal_linux.c
//  Version:     v1.00
//  Created:     25/01/24 by Clara.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#define PAL_IMPL
#include "vrui_pal.h"
#include "pthread.h"

//Temporary
#define VRUI_NO_MUTEX

void vrui_init_mutex(vrui_mutex Mutex){
#ifndef VRUI_NO_MUTEX
	int Result = pthread_mutex_init(&Mutex.Mutex, NULL);
#endif

}

void vrui_destroy_mutex(vrui_mutex Mutex) {
#ifndef VRUI_NO_MUTEX
	int Result = pthread_mutex_destroy(&Mutex.Mutex);
#endif

}

void vrui_lock_mutex(vrui_mutex Mutex) {
#ifndef VRUI_NO_MUTEX
	int Result = pthread_mutex_lock(&Mutex.Mutex);
#endif

}

void vrui_unlock_mutex(vrui_mutex Mutex) {
#ifndef VRUI_NO_MUTEX
	int Result = pthread_mutex_unlock(&Mutex.Mutex);
#endif

}
