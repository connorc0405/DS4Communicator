//
//  main.h
//  DS4Communicator
//
//  Created by Connor Cumming on 10/30/17.
//  Copyright © 2017 Connor Cumming. All rights reserved.
//

#ifndef backend_h
#define backend_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "hidapi.h"
#include "checksum.h"
#include "main.h"

#define VENDOR_ID 0x054C
#define PRODUCT_ID 0x05C4

void printInputReport(hid_device *DS4Controller);

void writeOutputReport(hid_device *DS4Controller, char* deviceFeatures);

void handleError(void);

void getFeature0x02(hid_device *DS4Controller);

#endif
