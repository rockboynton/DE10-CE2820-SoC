# Joystick + Accelerometer Controlled Camera Mount

*	Utilizes a DE10-Lite SoC with Nios II processor to produce a multifunctional camera mount with hobby servos
*	Includes custom hardware such as:
    *	A dual PWM signal generator controlled via an output-only GPIO peripheral to control pan and tilt servos with 8-bit precision.
    *	A 1MHz ADC circuit with up to 18 channels for analog measurement with modes for single and continuous conversion for joystick control over pan and tilt servos
    *	A 4-wire SPI component with memory mapped address and data registers controlling the 10-bit ADXL345 accelerometer chip
    *	An I2C Master component to control an OV7670 camera module at 100kbits/sec with a FIFO queue.
*	Also comes with an API for application developers in C plus a complete user manual outlining features, architecture, usage, memory map, and example code
