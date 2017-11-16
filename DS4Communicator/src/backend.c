//
//  backend.c
//  DS4Communicator
//
//  Created by Connor Cumming on 10/24/17.
//  Copyright © 2017 Connor Cumming. All rights reserved.
//  MIT License
//

#include "backend.h"

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

void writeOutputReport(hid_device *DS4Controller, int* deviceFeatures) {
    
    unsigned char outputReportBuf[] = {
        0xa2, 0x11, 0xc0, 0x20, 0xf3, 0x04, 0x00,
        deviceFeatures[0],
        deviceFeatures[1],
        deviceFeatures[2],
        deviceFeatures[3],
        deviceFeatures[4],
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x43, 0x00, 0x4d, 0x85,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0, 0, 0 };
    
    uint32_t crc32 = crc_32(outputReportBuf, 75);
    
    // First byte (0xa2) needed for CRC32 but shouldn't be included in output report
    for (int i = 0; i < sizeof(outputReportBuf)-4; i++) {
        outputReportBuf[i] = outputReportBuf[i+1];
    }
    
    outputReportBuf[74] = crc32 & 0xFF;
    outputReportBuf[75] = crc32 >> 8 & 0xFF;
    outputReportBuf[76] = crc32 >> 16 & 0xFF;
    outputReportBuf[77] = crc32 >> 24;
    
    if (hid_write(DS4Controller, outputReportBuf, 78) == -1) {
        handleError();
    }
}

void printInputReport(hid_device *DS4Controller) {
    initscr();
    curs_set(0);
    while(1) {
        unsigned char inputReportBuf[10] = { 0 };
        if (hid_read(DS4Controller, inputReportBuf, 10) == -1) {
            endwin(); 
            handleError();
        }
        mvprintw(0,0,
                 "Left Stick: (%d, %d)\n"
                 "Right Stick: (%d, %d)\n"
                 "DPad: %s\n"
                 "Square: %d\n"
                 "X: %d\n"
                 "Circle: %d\n"
                 "Triangle: %d\n"
                 "L1: %d\n"
                 "Left Trigger: %d%%\n"
                 "R1: %d\n"
                 "Right Trigger: %d%%\n"
                 "Share: %d\n"
                 "Options: %d\n"
                 "L3: %d\n"
                 "R3: %d\n"
                 "PS: %d\n"
                 "TPAD: %d\n",
                 inputReportBuf[1],
                 inputReportBuf[2],
                 inputReportBuf[3],
                 inputReportBuf[4],
                 dpad[inputReportBuf[5] & 15],
                 (inputReportBuf[5] >> 4) & 1,
                 (inputReportBuf[5] >> 5) & 1,
                 (inputReportBuf[5] >> 6) & 1,
                 (inputReportBuf[5] >> 7) & 1,
                 inputReportBuf[6] & 1,
                 (inputReportBuf[8]*100)/255,
                 (inputReportBuf[6] >> 1) & 1,
                 (inputReportBuf[9]*100)/255,
                 (inputReportBuf[6] >> 4) & 1,
                 (inputReportBuf[6] >> 5) & 1,
                 (inputReportBuf[6] >> 6) & 1,
                 (inputReportBuf[6] >> 7) & 1,
                 inputReportBuf[7] & 1,
                 (inputReportBuf[7] >> 1) & 1);
        refresh();
        
        timeout(0);
        if (getch() != ERR) {
            break;
        }
    }
    endwin();
    
    //    printf("Left Stick: (%d, %d)\n", inputReportBuf[1], inputReportBuf[2]);
    //    printf("Right Stick: (%d, %d)\n", inputReportBuf[3], inputReportBuf[4]);
    //    printf("DPad: %s\n", dpad[inputReportBuf[5] & 15]);
    //    printf("Square: %d\n", (inputReportBuf[5] >> 4) & 1);
    //    printf("X: %d\n", (inputReportBuf[5] >> 5) & 1);
    //    printf("Circle: %d\n", (inputReportBuf[5] >> 6) & 1);
    //    printf("Triangle: %d\n", (inputReportBuf[5] >> 7) & 1);
    //    printf("L1: %d\n", inputReportBuf[6] & 1);
    //    printf("Left Trigger: %d%%\n", (inputReportBuf[8]*100)/255);
    //    printf("R1: %d\n", (inputReportBuf[6] >> 1) & 1);
    //    printf("Right Trigger: %d%%\n", (inputReportBuf[9]*100)/255);
    //    printf("Share: %d\n", (inputReportBuf[6] >> 4) & 1);
    //    printf("Options: %d\n", (inputReportBuf[6] >> 5) & 1);
    //    printf("L3: %d\n", (inputReportBuf[6] >> 6) & 1);
    //    printf("R3: %d\n", (inputReportBuf[6] >> 7) & 1);
    //    printf("PS: %d\n", inputReportBuf[7] & 1);
    //    printf("TPAD: %d\n", (inputReportBuf[7] >> 1) & 1);
}

void handleError() {
    fprintf(stderr, "An error has occured.  The controller may have been disconnected.\n");
    quit(EXIT_FAILURE);
}
