//
//  utils.h
//  DS4Communicator
//
//  Created by Connor Cumming on 10/30/17.
//  Copyright © 2017 Connor Cumming. All rights reserved.
//  MIT License
//

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include "checksum.h"
#include "hidapi.h"

#define VENDOR_ID 0x054C
#define PRODUCT_ID 0x05C4
#define MAX_INPUT_LENGTH 17 // Includes newline and null characters
#define NUM_DS4_CONTROLS 5 // Rumble (L,R), LED(R, G, B)

/*
    @desc Print an input report from the Dualshock 4 controller
    @param *DS4Controller: The Dualshock 4 controller that is connected through Bluetooth
*/
void printInputReport(hid_device *DS4Controller);

/*
    @desc Write an output report to the Dualshock 4 controller
    @param *DS4Controller: The Dualshock 4 controller that is connected through Bluetooth
    @param *DeviceFeatures: Array of rumble and led values to send to the Dualshock 4 controller
*/
void writeOutputReport(hid_device *DS4Controller, int *deviceFeatures);

/*
    @desc Notify the user that a failure has occured and quit DS4Communicator
*/
void handleError(void);

/*
    @desc Free hidapi resources and stop execution
    @param code: An exit code
*/
void quit(signed char code); 

#endif
