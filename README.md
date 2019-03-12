# Projectile_Velocity_v2
Implementation of Interrupts

This is the second version of the projectile velocity design code.

Instead of using while loops to check the state of our read pins, we use interrupts to catch and record the time of an arduino pin change.  This allows for the potential for more code to be run at the same time that we are reading the pins.  This also allows for better user input to the system as we no longer get stuck inside of a loop as we prepare to fire.

We learned about different methods of detecting a change within our arduino, and the simplicity that learning a new method can bring to a program.  

Work in progress, but can detect velocities up to 90 m/s at the moment, and changes are to be made soon that will increase this velocity, and the reliability of the program.
