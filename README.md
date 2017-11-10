# DS4Communicator

## Description
DS4Communicator is an interactive command-line program for Mac that allows users to communicate with a Dualshock 4 controller over Bluetooth.  It can read input data from the controller as well as control the two rumble motors and set RGB values for the LED.
## Build and Run
DS4Communicator relies on [hidapi](https://github.com/signal11/hidapi) which can be installed using [homebrew](https://brew.sh)  
`brew install hidapi`  
  
Then download and build DS4Communicator  
`git clone https://github.com/connorc0405/DS4Communicator.git`  
`cd DS4Communicator/DS4Communicator`  
`make`  
  
To run:  
`./bin/DS4Communicator`  
or  
`cd bin`  
`./DS4Communicator`

## Usage
`print` : Read input data from the controller  
`rumble [0-255] [0-255]` : Set rumble intensity for left and right motors, respectively  
`led [0-255] [0-255] [0-255]` : Set red, green, and blue values for the LED, respectively  
`list` : Get last updated rumble and LED values  
`send` : Send an output report to set rumble and LED function  
`quit` : Stop DS4Communicator  

## Issues
The Dualshock 4 does not include one of its input reports in the HID report descriptor, which is sent after an output report has been written.  Because of this, input reports cannot be received after an output report is written, until:
* Dualshock 4 controller is disconnected
* Dualshock 4 is reconnected
* DS4Communicator is restarted
