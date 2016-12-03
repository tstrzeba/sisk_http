################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\src/r_glyph/src/glyph/glyph.c 

C_DEPS += \
./src/r_glyph/src/glyph/glyph.d 

OBJS += \
./src/r_glyph/src/glyph/glyph.obj 


# Each subdirectory must supply rules for building sources it contributes
src/r_glyph/src/glyph/%.obj: ../src/r_glyph/src/glyph/%.c src/r_glyph/src/glyph/c.sub
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c99   -include="D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/bsp","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/driver","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/user-app","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/uip","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/unix","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/apps/dhcpc","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/apps/webserver","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_glyph","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_glyph/src","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_glyph/src/glyph","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_rspi_rx600","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_rspi_rx600/src","C:\PROGRA~2\Renesas\RX\2_5_0/include"  -debug -nomessage -cpu=rx600 -optimize=0 -alias=noansi -nologo -change_message=information=5550  -define=PLATFORM_RDK63N=1,__RX   "$<"
	ccrx -lang=c99 -output=obj="$(@:%.d=%.obj)"  -include="D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/bsp","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/driver","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/user-app","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/uip","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/unix","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/apps/dhcpc","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/apps/webserver","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_glyph","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_glyph/src","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_glyph/src/glyph","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_rspi_rx600","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_rspi_rx600/src","C:\PROGRA~2\Renesas\RX\2_5_0/include"  -debug -nomessage -cpu=rx600 -optimize=0 -alias=noansi -nologo -change_message=information=5550  -define=PLATFORM_RDK63N=1,__RX   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

