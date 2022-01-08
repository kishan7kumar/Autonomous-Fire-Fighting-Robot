# Autonomous Fire Fighting Robot

## Brief Description

The detection and prevention of ﬁre is a significant problem nowadays. Because of the inadequacy of conventional ﬁre detection techniques like a smoke alarm, we have developed a prototype of an autonomous robot that can detect ﬁre within its proximity and suppress it using water. The Autonomous Fire Fighting Bot (AFFB) developed here uses an image processing toolbox of MATLAB to detect ﬁre, which increases the speed and accuracy of ﬁre detection. Also, it uses readings from diﬀerent sensors to detect every aspect of ﬁre, like an increase in temperature, decrease in humidity, the release of smoke, change in light intensity, and emission of infrared waves. Arduino Mega microcontroller board is used to perform bot movements and read the values from the temperature, smoke, ultrasonic, and ﬂame sensor. Matlab and Arduino undergo serial communication to conﬁrm the ﬁre from image processing and sensor values. To capture live feed, a webcam is used. The robot can detect ﬁre in its proximity, and at the same time, it raises the alarm without any manual assistance, making it completely autonomous. It has dc fans to suck the smoke blocking the webcam vision in front of it. It is also equipped with a water tank inside its body used to put oﬀ ﬁre.

## Block Diagram

![image](https://user-images.githubusercontent.com/53033119/148652688-f2b97208-448b-44cb-954e-938621fe119d.png)

## Working of the Robot

After doing all connections properly the arduino program is compiled and MATLAB is also opened at same time. The robot will start to work. </br>
The working of the bot is described in following steps:-

Step 1:- Detection of Fire: When the robot is powered on. It starts to move in clockwise direction or in 360 degrees continuously. The ﬂame sensor starts to work as soon as ﬂame is detected within bots range. The sensor then sends this data to Arduino and bot stops rotating and starts to move towards the ﬂame source. When the bot reaches close enough to the ﬂame it stops and then wait for MATLAB serial data for fire confirmation.</br>
Step 2:- Conﬁrmation of Fire: After detection of ﬁre using ﬂame sensor and other sensors. The MATLAB's image processing part comes into the picture and using RGB color space and image thresholding, ﬁre pixels are separated out. The MATLAB sends this data serially to Arduino port. Arduino receives this data and conﬁrms that the ﬂame is detected </br>
Step 3:- Raising Alarm and Stopping Fire: After successful conﬁrmation of ﬁre using arduino sensors values and MATLAB image processing algorithm output, the robot raises an alarm and turns on the water pump to put out the ﬁre.</br>


## Video Demonstration

https://user-images.githubusercontent.com/53033119/148638579-df65fff1-12b2-458c-8bfa-2db42ac9161a.mp4

## Limitations & Future Scope

As the industries are searching for more autonomy, the demand for autonomous bots has increased. The bot designed here is autonomous, capable of detecting ﬁre using both sensor and image processing toolbox of Matlab. Currently, the robot uses Arduino Mega, a microcontroller that controls the sensor and bot movements. The Matlab software is used for the image processing part. As there is serial communication between Arduino and MATLAB, the Arduino needs to be connected to the computer via cables all the time. Therefore, restricting its movement to less than a few meters. So, in the future, a microprocessor like raspberry pi can be used to control all bot's movement. It can also handle the image processing process and provides a wireless solution. The need for cables will be eliminated, giving AFFB more freedom to move. 
The bot is now capable of detecting ﬁre within its proximity; it can't detect ﬁre beyond that. So, in the future, the bot will be programmed in a way that it can go into diﬀerent sections of a room, ﬂoors, or building and will reach the exact spot where the ﬁre source is present. Moreover, it will calculate the shortest distance to ﬁre source using line following techniques and feature extraction algorithm. The bot now uses water, which is not always reliable in putting oﬀ the ﬁre, so in the future, it will be replaced with a chemical powder-based ﬁre extinguisher which is more eﬀective. Despite all the current limitations, the robot can remove the dependency on the conventional ﬁre detection system, which is less accurate and sometimes gives a false reading. The use of image processing provides an edge to the robot for ﬁre detection.

