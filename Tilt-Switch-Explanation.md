#Tilt-Switch
I created this tilt switch to learn more about GPIO and interacting with physical input.
The red LED indicates that the X axis is level.
The green LED indicates that the Y axis is level.
I used the wirinPi and the wiringPiI2C libraries, as well as skeleton code for interacting with the accelerometer from:
https://github.com/sunfounder/Sunfounder_SuperKit_C_code_for_RaspberryPi/blob/master/14_ADXL345/adxl345.c
I added my own logic to take the input from the accelerometer and light the LEDs when the axes were level.
