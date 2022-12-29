# reversed_pendulum

here is a Reversed Pendulum sample using M5Stack IMU.

(BOM)

DC moter : FM90

Battery case : ４AA batteries with on\off switch

M5Stack gray

Wheels : for FS90R

DC motor control module : L298N

Interface cable : jumper wire

    DC motor driver pin assignment

    int pwm_a = 26;
    int fw_a = 5;
    int rv_a = 25;
    int pwm_b = 16;
    int fw_b = 17;
    int rv_b = 2;

battery : 4 NiMh AA size

(screws)

M3/25mm : 2 (for M5Stack; one nut need to be placed beneath the screw head to ajust the screw length)

M3/15mm : 4 (for DC motor driver)

M3/10mm : 2 (to fix the upper plastic to the lower)

M2/10mm : 4 (for DC motors)

(Files)

stl_file directory : 3D printer data files

(PID adjustment procedure)

1st step : set P to set adequate level hunting

2nd step : set I to supress hunting

3rd step : set D to keep stable operation when disturbance is applied(still TBD)

(source code)
*.ino : M5Stack code, 
*.pde : Prcessing code to update M5Stack PID parameter dynamically via UDP protocol
