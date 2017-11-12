//
//  main.h
//  DS4Communicator
//
//  Created by Connor Cumming on 10/30/17.
//  Copyright © 2017 Connor Cumming. All rights reserved.
//

#ifndef main_h
#define main_h

#include <stdio.h>
#include <strings.h>
#include "backend.h"

#define MAX_INPUT_LENGTH 16 // Includes null character \0
#define NUM_DS4_CONTROLS 5 // Rumble (L,R), LED(R, G, B)

/*
    @desc Free hidapi resources and stop execution
    @param status: An exit status
*/
void quit(unsigned char status);

#endif
