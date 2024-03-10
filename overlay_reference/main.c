////////////////////////////////////////////////////////////////////////////
//
//  SVRUI Source File.
//  Copyright (C) 2024 Clara Lille
// -------------------------------------------------------------------------
//  File name:   main.c
//  Version:     v1.00
//  Created:     19/02/24 by Clara.
//  Description: 
// -------------------------------------------------------------------------
//  This project is licensed under the MIT License
//
////////////////////////////////////////////////////////////////////////////

#include "renderer.h"
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char* argv[]){
    init_renderer();

    renderer_quit();
    printf("Quitting...\n");
    return 0;

}
