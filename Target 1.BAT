SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;C:\WinAVR-20100110\bin;C:\WinAVR-20100110\utils\bin;C:\ProgramData\Oracle\Java\javapath;C:\WinAVR-20080610\bin;C:\WinAVR-20080610\utils\bin;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\Skype\Phone\;C:\Program Files (x86)\Microchip\xc8\v1.33\bin;C:\Program Files (x86)\Java\jdk1.7.0_79\bin;C:\Users\KEVIN\AppData\Local\Microsoft\WindowsApps;
SET CPU_TYPE=LPC1768
SET CPU_VENDOR=NXP
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00B71B00
"C:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\objects\startup_lpc17xx._ia"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\system_lpc17xx.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\main.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\delay.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\uart.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\Objects\ADC.lnp"
"C:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\Objects\ADC.axf" --i32combined --output ".\Objects\ADC.hex"
