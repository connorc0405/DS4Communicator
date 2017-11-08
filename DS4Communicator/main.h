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

// Includes null character \0
#define MAX_INPUT_LENGTH 16
#define NUM_DS4_CONTROLS 5

const char rumbleUsage[] = "rumble [0-255] [0-255] :      Set left and right rumble motor intensity\n";
const char ledUsage[] =  "led [0-255] [0-255] [0-255] : Set red, green, blue led values\n";

void quit(void);

#endif
