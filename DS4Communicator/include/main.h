//
//  main.h
//  DS4Communicator
//
//  Created by Connor Cumming on 10/30/17.
//  Copyright © 2017 Connor Cumming. All rights reserved.
//  MIT License
//

#ifndef main_h
#define main_h

#include <stdio.h>
#include <strings.h>
#include "backend.h"

#define MAX_INPUT_LENGTH 17 // Includes newline and null characters
#define NUM_DS4_CONTROLS 5 // Rumble (L,R), LED(R, G, B)

/*
    @desc Free hidapi resources and stop execution
    @param status: An exit status
*/
void quit(unsigned char status);

#endif
