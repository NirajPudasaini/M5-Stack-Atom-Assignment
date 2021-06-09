# M5 Stack Atom Assignment

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
1. Shows Active temperature + Units
2. Shows average temperature of the device since it was running (temperature + Units), with average measured in an interval of 10 seconds.
3. Shows color scale of temperature range + current temperature as color. The four rows and the 5 columns are used to show the actual temperature in color in the matrix. The last five LEDs of the fifth row is used to show the  the range of colors for the temperature.
The range being : T<24 (white), 24=<T<31 (green),31=<T<40 (yellow), and T>=40 (red), where T is the temperature in celcius.
4. Shows graph of temperature across a predefined range. For the graph, the temperature of the last 50 seconds is taken in an array, and plotted on the third row, with the latest temperature shown in the leftmost LED.
5. Changes units. Changes the unit from Fahrenheit to celcius, and vice versa.


## Part 2 

The code implements a die-based(LUDO) and a spinning based(ROULETTE) game as a real and virtual game spinner.
The device can be interacted virtually with the network named "Group22", and the password "DandI01234" through a webpage. 
For the webpage version, the display is shown the device, depending on the button pressed (Rool the dice or Spin the roullete).
For the physical version, the output of LUDO is shown when the device is shaked with a certain threshold. And the output of ROULETTE is shown when the device is spinned.
If you want to learn more about how to play these games, refer to the following links:
[Ludo game](https://www.youtube.com/watch?v=IHkRjn8XVtw&ab_channel=TripleSGames)
[Roullete Game](https://www.youtube.com/watch?v=Gcy3_HhFbyY&ab_channel=TripleSGamesTripleSGames)

