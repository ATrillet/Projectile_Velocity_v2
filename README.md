# Projectile_Velocity_v2
Projectile velocity code with implementation of interrupts

This is the second version of the projectile velocity design code.

Instead of using while loops to check the state of the read pins, we use interrupts to catch and record the time of an arduino digitalpin change.  Interrupts are theoretically faster than looping, and has so far been a worthwhile change.  This change also allows for simplifications within our code as we no longer need to check the state of pins, the arduino will do that for us.  This helps us to provide better user feedback from the system as we no longer get stuck inside of a loop as we prepare to fire.

Current issue with the interrupts is that because they are always looking for changes, if a projectile passes back through a sensor data is lost.  The current solution is to output within the interupt functions, and have the loop doing as little as possible. Simplifications to the loop are in progress, and commented out code is still being reviewed for its usefulness.

We learned about different methods of detecting a change within our arduino, and the simplicity that learning a new method can bring to a program.  

Work in progress, we have currently been able to accurately measure velocities up to 120 m/s, approaching the maximum velocity possible out of the system we are working with.
