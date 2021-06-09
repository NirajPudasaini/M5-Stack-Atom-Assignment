# M5 Stack Atom Assignment
 Assignment 2

<<<<<<< Updated upstream
This is a readme file that contains instructions on how to run th
=======
This is a readme file that contains instructions on what to expect while running codes on M5 Stack Atom Matrix.

## Part 1, the first (Bike light) 

After connecting the Atom Matrix with a power source, you can carry out different modes as follows:

* The screen is completely blank at the first mode or all the LEDs are in off state initially.
* After you press the button, LEDs strobe in red color at a predetermined interval of 100 milli seconds.
* Similarly, after pressing button again, LEDs strobe at a predetermined interval of 100 milli seconds, but in white color.
* Now, after the third press of button, the device constantly checks if there is a deacceleration to detect the braking event.
If a braking event is detected then the lights turn solid for that interval then returns to strobe when the devices isn't in braking event.
Red light is used to mimic the Automatic Rear Mode of the vehicle.
* Similar to the previous point, white light turns solid in the braking event, and returns to strobe at other conditions. White light is used to mimic the Automatic Front Mode of the vehicle.
Note that the code is implemented in a way that it will work in any orientation of the device.

## Part 1, the second (Sensing Temperature)

After connecting the Atom Matrix with a power source, the device is measuring temperature and recording it at a predetermined interval of 10 seconds, and the
screen displays nothing.

* When holding the device in the hand with the screen facing relatively upwards, pressing the screen button activates the screen, with current mode shown to be 1.
*  There are five different modes, and the user is able to change modes by tipping the device left or right (assuming the bottom of the device is where the USB-C port resides)
* When the user presses the button while the screen is activated,, the user activates the current mode shown on the screen of the matrix.
* If the user turns the device to face-down ,exit mode is activated and the screen is deactivated but the readings of the temperature is still taken in the background.
mode with screen off.
* The five different modes labelled 1 to 5, are :
1. Show Active temperature + Units
2. Show average of last 24 hours of temperature + Units
3. Show color scale of temperature range + current temperature as color
4. Show graph of temperature across a predefined range.
5. Change units


## Part 2,  
>>>>>>> Stashed changes
