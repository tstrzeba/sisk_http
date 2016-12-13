################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
SRC_SRCS += \
..\src/bsp/board/rdkrx63n/lowlvl.src 

C_SRCS += \
..\src/bsp/board/rdkrx63n/dbsct.c \
..\src/bsp/board/rdkrx63n/flash_options.c \
..\src/bsp/board/rdkrx63n/hwsetup.c \
..\src/bsp/board/rdkrx63n/lcd.c \
..\src/bsp/board/rdkrx63n/lowsrc.c \
..\src/bsp/board/rdkrx63n/resetprg.c \
..\src/bsp/board/rdkrx63n/sbrk.c \
..\src/bsp/board/rdkrx63n/vecttbl.c 

C_DEPS += \
./src/bsp/board/rdkrx63n/dbsct.d \
./src/bsp/board/rdkrx63n/flash_options.d \
./src/bsp/board/rdkrx63n/hwsetup.d \
./src/bsp/board/rdkrx63n/lcd.d \
./src/bsp/board/rdkrx63n/lowsrc.d \
./src/bsp/board/rdkrx63n/resetprg.d \
./src/bsp/board/rdkrx63n/sbrk.d \
./src/bsp/board/rdkrx63n/vecttbl.d 

SRC_DEPS += \
./src/bsp/board/rdkrx63n/lowlvl.d 

OBJS += \
./src/bsp/board/rdkrx63n/dbsct.obj \
./src/bsp/board/rdkrx63n/flash_options.obj \
./src/bsp/board/rdkrx63n/hwsetup.obj \
./src/bsp/board/rdkrx63n/lcd.obj \
./src/bsp/board/rdkrx63n/lowlvl.obj \
./src/bsp/board/rdkrx63n/lowsrc.obj \
./src/bsp/board/rdkrx63n/resetprg.obj \
./src/bsp/board/rdkrx63n/sbrk.obj \
./src/bsp/board/rdkrx63n/vecttbl.obj 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/board/rdkrx63n/%.obj: ../src/bsp/board/rdkrx63n/%.c src/bsp/board/rdkrx63n/c.sub
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx  -MM -MP -output=dep="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)" -lang=c99   -include="D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/bsp","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/driver","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/user-app","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/uip","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/unix","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/apps/dhcpc","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/apps/webserver","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_glyph","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_glyph/src","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_glyph/src/glyph","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_rspi_rx600","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_rspi_rx600/src","C:\PROGRA~2\Renesas\RX\2_5_0/include"  -debug -nomessage -cpu=rx600 -optimize=0 -alias=noansi -nologo -change_message=information=5550  -define=PLATFORM_RDK63N=1,__RX   "$<"
	ccrx -lang=c99 -output=obj="$(@:%.d=%.obj)"  -include="D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/bsp","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/driver","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/user-app","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/uip","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/unix","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/apps/dhcpc","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/uip/apps/webserver","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_glyph","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_glyph/src","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_glyph/src/glyph","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_rspi_rx600","D:/Onedrive/Study/SiSK/workspace/SISK_HTTP/src/r_rspi_rx600/src","C:\PROGRA~2\Renesas\RX\2_5_0/include"  -debug -nomessage -cpu=rx600 -optimize=0 -alias=noansi -nologo -change_message=information=5550  -define=PLATFORM_RDK63N=1,__RX   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

src/bsp/board/rdkrx63n/%.obj: ../src/bsp/board/rdkrx63n/%.src src/bsp/board/rdkrx63n/src.sub
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Assembler'
	asrx  -MM -MP -MF="$(@:%.obj=%.d)" -MT="$(@:%.obj=%.obj)" -MT="$(@:%.obj=%.d)"  -nolistfile -cpu=rx600 -debug -nologo   "$<"
	asrx -output="$(@:%.d=%.obj)" -nolistfile -cpu=rx600 -debug -nologo   "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

