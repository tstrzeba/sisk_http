################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\src/uip/uip/main.c \
..\src/uip/uip/psock.c \
..\src/uip/uip/timer.c \
..\src/uip/uip/uip-fw.c \
..\src/uip/uip/uip-neighbor.c \
..\src/uip/uip/uip-split.c \
..\src/uip/uip/uip.c \
..\src/uip/uip/uip_arp.c \
..\src/uip/uip/uiplib.c 

C_DEPS += \
./src/uip/uip/main.d \
./src/uip/uip/psock.d \
./src/uip/uip/timer.d \
./src/uip/uip/uip-fw.d \
./src/uip/uip/uip-neighbor.d \
./src/uip/uip/uip-split.d \
./src/uip/uip/uip.d \
./src/uip/uip/uip_arp.d \
./src/uip/uip/uiplib.d 

OBJS += \
./src/uip/uip/main.obj \
./src/uip/uip/psock.obj \
./src/uip/uip/timer.obj \
./src/uip/uip/uip-fw.obj \
./src/uip/uip/uip-neighbor.obj \
./src/uip/uip/uip-split.obj \
./src/uip/uip/uip.obj \
./src/uip/uip/uip_arp.obj \
./src/uip/uip/uiplib.obj 


# Each subdirectory must supply rules for building sources it contributes
src/uip/uip/%.obj: ../src/uip/uip/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c99   -include="D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/bsp","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/driver","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/user-app","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/uip","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/unix","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/apps/dhcpc","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/apps/webserver","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_glyph","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_glyph/src","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_glyph/src/glyph","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_rspi_rx600","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_rspi_rx600/src","C:\PROGRA~2\Renesas\RX\2_5_0/include"  -debug -nomessage -cpu=rx600 -optimize=0 -alias=noansi -nologo -change_message=information=5550  -define=PLATFORM_RDK63N=1,__RX   "$<"
	ccrx -lang=c99 -output=obj="$(@:%.d=%.obj)"  -include="D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/bsp","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/driver","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/user-app","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/uip","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/unix","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/apps/dhcpc","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/apps/webserver","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_glyph","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_glyph/src","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_glyph/src/glyph","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_rspi_rx600","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_rspi_rx600/src","C:\PROGRA~2\Renesas\RX\2_5_0/include"  -debug -nomessage -cpu=rx600 -optimize=0 -alias=noansi -nologo -change_message=information=5550  -define=PLATFORM_RDK63N=1,__RX   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

