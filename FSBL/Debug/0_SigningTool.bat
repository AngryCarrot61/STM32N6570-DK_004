cd "C:\STM32CubeIDE\STM32N6570-DK_004\FSBL\Debug"
ATTRIB -R "STM32N6570-DK_004_FSBL_Trusted.bin"
del "STM32N6570-DK_004_FSBL_Trusted.bin"
"C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin\STM32_SigningTool_CLI.exe" -bin STM32N6570-DK_004_FSBL.bin -nk -of 0x80000000 -t fsbl -o STM32N6570-DK_004_FSBL_Trusted.bin -hv 2.3 -dump STM32N6570-DK_004_FSBL_Trusted.bin
ATTRIB -R "STM32N6570-DK_004_FSBL_Trusted.bin"
