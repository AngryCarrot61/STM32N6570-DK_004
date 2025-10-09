# STM32N6570-DK_004
FSBL and Appl XiP

In FSBL I try to initialize external PSRAM connectod to XSPI1.

We try to map PSRAM, so we change this line 35 in stm32_extmem_conf.h from

#define EXTMEM_DRIVER_PSRAM      0

to

#define EXTMEM_DRIVER_PSRAM      1

The FSBL generates a HardFault when executing SAL_XSPI_EnableMapMode, because the function HAL_XSPI_MemoryMapped fails.

What can be wrong?

How to test it:

Set the BOOT switches to the right position and press the reset button, so the internal bootloader activates.

Run debug on the FSBL.

Flashing:
the debug directories for FSBL and Appl contain a batch file: '0_SigningTool.bat'.
After compiling, run the batch files to sign the binaries.
Using STM32CubeProgrammer we select EL 'MX66UW1G45G_STM32N6570-DK'.
FSBL will be loaded at 0x70000000, and Appl at 0x70100000.

