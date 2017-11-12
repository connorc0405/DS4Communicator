//
//  main.c
//  DS4Communicator
//
//  Created by Connor Cumming on 10/30/17.
//  Copyright © 2017 Connor Cumming. All rights reserved.
//

#include "main.h"

int main() {

    char hasWritten = 0;
    
    hid_init();
    hid_device *DS4Controller = hid_open(VENDOR_ID, PRODUCT_ID, NULL);
    if (DS4Controller == NULL) {
        fprintf(stderr, "No Dualshock 4 controller connected\n");
        quit(EXIT_FAILURE);
    }
    puts("Controller Connected.  Type \"help\" for options");
    
    char inputBuffer[MAX_INPUT_LENGTH]; // Raw user input capped to longest possible command length

    // [0] = rumbleL, [1] = rumbleR, [2] = ledR, [3] = ledG, [4] = ledB
    int deviceFeatures[NUM_DS4_CONTROLS] = {0};
    
    while(1) {
        printf("> ");
        fgets(inputBuffer, MAX_INPUT_LENGTH, stdin);
        
        // Command arguments
        char arg0[7];
        int arg1 = -1, arg2 = -1, arg3 = -1; // Don't allow leaving out arguments
        sscanf(inputBuffer, "%s %d %d %d", arg0, &arg1, &arg2, &arg3);
        
        // Handle commands
        if (strcmp(arg0, "help") == 0) {
            puts("Usage:\n"
                   "print :                       Read input from controller\n"
                   "rumble [0-255] [0-255] :      Set left and right rumble motor intensity\n"
                   "led [0-255] [0-255] [0-255] : Set red, green, blue led values\n"
                   "list:                         List set rumble and led values\n"
                   "send :                        Send features to the controller\n"
                   "quit :                        Quit DS4Communicator");
        }
        else if (strcmp(arg0, "print") == 0) {
            if (hasWritten == 1) {
                fprintf(stderr, "Cannot print after write. To print again, reconnect the "
                                "controller and restart DS4Communicator\n");
            }
            else printInputReport(DS4Controller);
        }
        else if (strcmp(arg0, "rumble") == 0) {
            if (arg1 >= 0 && arg1 <= 255 && arg2 >=0 && arg2 <= 255) {
                deviceFeatures[0] = arg1;
                deviceFeatures[1] = arg2;
            }
            else {
                puts("rumble [0-255] [0-255]");
            }
        }
        else if (strcmp(arg0, "led") == 0) {
            if (arg1 >= 0 && arg1 <=255 && arg2 >= 0 && arg2 <= 255 && arg3 >= 0 && arg3 <= 255) {
                deviceFeatures[2] = arg1;
                deviceFeatures[3] = arg2;
                deviceFeatures[4] = arg3;
            }
            else {
                puts("led [0-255] [0-255] [0-255]");
            }
        }
        else if(strcmp(arg0, "list") == 0) {
            printf("Rumble Left: %d\n"
                   "Rumble Right: %d\n"
                   "Led Red: %d\n"
                   "Led Green: %d\n"
                   "Led Blue: %d\n",
                   deviceFeatures[0],
                   deviceFeatures[1],
                   deviceFeatures[2],
                   deviceFeatures[3],
                   deviceFeatures[4]);
        }
        else if (strcmp(arg0, "send") == 0) {
            writeOutputReport(DS4Controller, deviceFeatures);
            hasWritten = 1;
        }
        else if (strcmp(arg0, "quit") == 0) {
            quit(EXIT_SUCCESS);
        }
        else {
            fprintf(stderr, "Bad input. Type \"help\" for usage commands\n");
        }
        
        // Clear stdin if stdin input is too long for inputBuffer
        if (strchr(inputBuffer, '\n') == NULL) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    }
}

void quit(unsigned char status) {
    hid_exit();
    exit(status);
}
