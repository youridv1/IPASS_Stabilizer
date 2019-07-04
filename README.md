# IPASS_Stabilizer
Everything needed to replicate my 3D printed, Arduino powered camera stabilizer. As well as MPU6050 and steppermotor libraries.
This project was meant primarily as a proof of concept of a relatively inexpensive home made Gimball. It's not really suited to 
carry a camera just yet, but that's where you come in. For my final project of the first year of my Computer Science major I've 
designed this base for others to build upon. As well as, of course, writing the necessary code to make the thing work. 

In this repository you will find libraries for all hardware used, excluding the Arduino Due.

To make it all work, there's actually one more thing you will require. The hwlib, which was not made by me, is what this project is
based on. The contents of this library are subject to change, but not to an extent that you can't figure out yourself.
It can be found here: https://github.com/wovo/installers

Used Hardware:
  - MPU6050
    An all in one device to do motion and acceleration based measurements with. Interfacing with the chip is done through i2c.
    It features an Accelerometer and a Gyroscope which both measure in 3 dimensions. It also contains a temperature sensor.
    The device is ideal for high precision, low power applications and is configurable.
    Datasheets and registermaps can be found at https://www.invensense.com/products/motion-tracking/6-axis/mpu-6050/
    
  - 28BYJ-48
    A 4 coil steppermotor which operates at 5V DC. It has sufficient torque for my application, but that doesn't mean it's able to
    "Do it all". For more torque-heavy applications the Nema17 will be a better fit.
    The Datasheet can be found at https://components101.com/motors/28byj-48-stepper-motor
    
  - Voron 1.6
    The printer used for printing my contraption is based on the Voron 1.6.
    http://vorondesign.com/voron1.6
    
  - ABS plastic
    The material out of which the contraption I made has been printed. It is a more durable and less brittle plastic than your 
    standard PLA, which is also a popular material when 3D printing. 
    
      
