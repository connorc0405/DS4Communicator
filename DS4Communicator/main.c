//
//  main.c
//  DS4Communicator
//
//  Created by Connor Cumming on 10/24/17.
//  Copyright © 2017 Connor Cumming. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "hidapi.h"
#include "checksum.h"

#define MAX_STR 255
#define PRODUCT_ID 0x05C4
#define VENDOR_ID 0x054C

void printInputReport(unsigned char* data);

const char* dpad[] = {
    [0] = "N",
    [1] = "NE",
    [2] = "E",
    [3] = "SE",
    [4] = "S",
    [5] = "SW",
    [6] = "W",
    [7] = "NW",
    [8] = "None"
};

int main(int argc, char* argv[]) {
    int res;
    unsigned char inputReportBuf[15];
    unsigned char outputReportBuf[78];
    
    hid_init();
    hid_device *DS4Controller = hid_open(VENDOR_ID, PRODUCT_ID, NULL);
    
    // Input Report
    //res = hid_read(DS4Controller, inputReportBuf, 15);
    //printInputReport(inputReportBuf);
    
    
    // Create array with first byte at front (75 bytes)
    // Generate crc32 (4 bytes) 4 bytes can be in decimal representation
    // Create array with crc32 at end (reversed) and no first byte (78 bytes)
    
    // Output Report (red led)
    unsigned char newbuf[] = {0xa2, 0x11, 0xc0, 0x20, 0xf3, 0x04, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x43, 0x00, 0x4d, 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0}; //, 0xf6, 0xbe, 0xae, 0x2f };
    
    uint32_t crc32 = crc_32(newbuf, 75);
    printf("CRC32: %u\n", crc32);
    
    //PLAN: BITWISE OPERATORS TO CONVERT DECIMAL TO BYTE ARRAY
    
    printf("%d\n", crc32 >> 24); //4th byte
    printf("%d\n", crc32 >> 16 & 0xFF); // 3rd byte
    printf("%d\n", crc32 >> 8 & 0xFF); // 2nd byte
    printf("%d\n", crc32 & 0xFF); // 1st byte
    
    // move bytes back by 1
    for (int i = 0; i < sizeof(newbuf); i++) {
        newbuf[i] = newbuf[i+1];
    }
    
    newbuf[74] = crc32 & 0xFF;
    newbuf[75] = crc32 >> 8 & 0xFF;
    newbuf[76] = crc32 >> 16 & 0xFF;
    newbuf[77] = crc32 >> 24;
    
    printf("%d %d %d %d", newbuf[73], newbuf[74], newbuf[75], newbuf[76]);

    res = hid_write(DS4Controller, newbuf, 78);
    //printf("Result: %d\n", res);
    
    return 0;
}

void printInputReport(unsigned char* report) {
    printf("Left Stick: (%d, %d)\n", report[1], report[2]);
    printf("Right Stick: (%d, %d)\n", report[3], report[4]);
    printf("DPad: %s\n", dpad[report[5] & 15]);
    printf("Square: %d\n", (report[5] >> 4) & 1);
    printf("X: %d\n", (report[5] >> 5) & 1);
    printf("Circle: %d\n", (report[5] >> 6) & 1);
    printf("Triangle: %d\n", (report[5] >> 7) & 1);
    printf("L1: %d\n", report[6] & 1);
    printf("Left Trigger: %d%%\n", (report[8]*100)/255);
    printf("R1: %d\n", (report[6] >> 1) & 1);
    printf("Right Trigger: %d%%\n", (report[9]*100)/255);
    printf("Share: %d\n", (report[6] >> 4) & 1);
    printf("Options: %d\n", (report[6] >> 5) & 1);
    printf("L3: %d\n", (report[6] >> 6) & 1);
    printf("R3: %d\n", (report[6] >> 7) & 1);
    printf("PS: %d\n", report[7] & 1);
    printf("TPAD: %d\n", (report[7] >> 1) & 1);
}

