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
#include <stdlib.h>
#include <unistd.h>
#include "hidapi.h"
#include "checksum.h"

void printInputReport(hid_device *DS4Controller);

void writeOutputReport(hid_device *DS4Controller);

void getFeature0x02(hid_device *DS4Controller);

#endif
