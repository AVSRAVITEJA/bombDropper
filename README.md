# bombDropper
This project utilizes a stepper motor to precisely drop bombs from a drone. This project is split into 2 different parts.
# Drone construction:
The drone is a quadcopter that utilizes 4 U15 motors and is controlled using mission planner. The  drone has a top mount which consists of the telemetry system and the ESCs and in the bottom it has the battery pack. The drone has the bomb dropper setup near the legs of the drone, giving it ample space. 
U15 motors are one of the best argi-drone motors that have multipurpose applications, each motor provides about 35kg max thrust which leads to a 140kg maximum thrust and considering the weight of the battery pack, misslies and the frame, these motors fit perfectly to the requirements. The drone's VTOL requires around 20kg thrust and this can be achieved by running the motors at 80% throttle, this considerably reduces the burden on the motors and reduces the heating effects on it.  
  Two 12S battery packs of 16000mAh are used for this drone which provides almost 45min-60min endurance, the battery packs are customized to the drone's requrirements and the drone has enough space to accomodate more battery packs
  The ESC is from T motors and the drone uses Pixhawk for flight control
  # Bomb Dropper Configuration:
  The bomb dropper consists of a barrel which consits all the bombs, (initially the planned capacity of the barrel is 7 bombs but that can be altered). This barrel has a lock and key mechanism through with the bombs drop when the motor rotates. During the initial days of ideation, I thought the dropper can be automated and the bomb can be dropped on a specified location based on it's latitude and longitude, but after further research I found out that remote controlled bomb droppers were in demand in the market.
  I have worked on two iterations in this project, one with automated bomb dropper and the other with remote controlled setup 
  # Automated Setup
  For the automated bomb dropper I used ESP32 as my MCU and with GPS sensor I have accessed the location, the website interface is a map based drop location selector. The latitude and longitude of the drop location are set and the drone drops off the bomb when it is in the 2m radius of the drop location.
  
  
