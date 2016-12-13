################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf *.lst *.lis *.lpp *.map *.x *.lbp src/*.src src/*.p src/*.pp *.bls *.libelf *.lbk *.abs *.dbg *.sni *.fsy

# All of the sources participating in the build are defined here
-include sources.mk
-include src/bsp/board/rdkrx63n/subdir.mk
-include src/driver/subdir.mk
-include src/r_glyph/src/glyph/drivers/subdir.mk
-include src/r_glyph/src/glyph/fonts/subdir.mk
-include src/r_glyph/src/glyph/subdir.mk
-include src/r_glyph/src/subdir.mk
-include src/r_rspi_rx600/src/subdir.mk
-include src/uip/apps/dhcpc/subdir.mk
-include src/uip/apps/webserver/subdir.mk
-include src/uip/uip/subdir.mk
-include src/uip/unix/subdir.mk
-include src/user-app/subdir.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_UPPER_DEPS)),)
-include $(CC_UPPER_DEPS)
endif
ifneq ($(strip $(C++_UPPER_DEPS)),)
-include $(C++_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_UPPER_DEPS)),)
-include $(CXX_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_UPPER_DEPS)),)
-include $(CPP_UPPER_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CP_DEPS)),)
-include $(CP_DEPS)
endif
ifneq ($(strip $(SRC_UPPER_DEPS)),)
-include $(SRC_UPPER_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(CP_UPPER_DEPS)),)
-include $(CP_UPPER_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(OBJ_DEPS)),)
-include $(OBJ_DEPS)
endif
ifneq ($(strip $(ABS_DEPS)),)
-include $(ABS_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(O_DEPS)),)
-include $(O_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

ifneq ($(strip $(SRC_UPPER_SRCS)),)
ALL_ASMS += $(SRC_UPPER_SRCS) 
endif
ifneq ($(strip $(SRC_SRCS)),)
ALL_ASMS += $(SRC_SRCS) 
endif
ifneq ($(strip $(S_UPPER_SRCS)),)
ALL_ASMS += $(S_UPPER_SRCS) 
endif
ifneq ($(strip $(S_SRCS)),)
ALL_ASMS += $(S_SRCS) 
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
CONVERTOR_OUTPUT_OUTPUTS += \
SISK_HTTP.mot \

LINKER_OUTPUT_OUTPUTS += \
SISK_HTTP.abs \

LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS += \
SISK_HTTP.lib \

# All Target
all: SISK_HTTP.mot
	@echo 'Build complete.'

# Tool invocations
SISK_HTTP.mot: $(LINKER_OUTPUT_OUTPUTS)
	@echo 'Invoking: Converter'
	rlink   "D:\Onedrive\Study\SiSK\workspace\SISK_HTTP\Debug\SISK_HTTP.abs" -form=stype  -output="D:\Onedrive\Study\SiSK\workspace\SISK_HTTP\Debug\SISK_HTTP.mot" -nomessage
	@echo 'Finished building target:'
	@echo.
	$(MAKE) --no-print-directory post-build

SISK_HTTP.abs: $(OBJS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) $(ALL_ASMS) 
	@echo 'Invoking: Linker'
	@echo 'Building target:'
	rlink  -subcommand="LinkerSubCommand.tmp"  -library="D:\Onedrive\Study\SiSK\workspace\SISK_HTTP\Debug\SISK_HTTP.lib" -noprelink -nooptimize -debug -output="D:\Onedrive\Study\SiSK\workspace\SISK_HTTP\Debug\SISK_HTTP.abs" -nocompress -nomessage -nologo -nomessage -rom=D=R,D_1=R_1,D_2=R_2
	@echo 'Finished building:'
	@echo.

SISK_HTTP.lib:  
	@echo 'Invoking: Standard Library'
	lbgrx -lang=c99 -head=runtime,stdio,stdlib,string,new -cpu=rx600 -output="SISK_HTTP.lib"
	@echo 'Finished building:'
	@echo.

# Other Targets
clean:
ifneq ($(strip $(OBJS)),)
	-$(file > clean_OBJS.tmp , $(OBJS))
	-@ xargs -s 6000 -t -a clean_OBJS.tmp $(RM)
	-@$(RM) clean_OBJS.tmp
endif
ifneq ($(strip $(C_DEPS)),)
	-$(file > clean_C_DEPS.tmp , $(C_DEPS))
	-@ xargs -s 6000 -t -a clean_C_DEPS.tmp $(RM)
	-@$(RM) clean_C_DEPS.tmp
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
	-$(file > clean_C_UPPER_DEPS.tmp , $(C_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_C_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_C_UPPER_DEPS.tmp
endif
ifneq ($(strip $(CPP_DEPS)),)
	-$(file > clean_CPP_DEPS.tmp , $(CPP_DEPS))
	-@ xargs -s 6000 -t -a clean_CPP_DEPS.tmp $(RM)
	-@$(RM) clean_CPP_DEPS.tmp
endif
ifneq ($(strip $(CPP_UPPER_DEPS)),)
	-$(file > clean_CPP_UPPER_DEPS.tmp , $(CPP_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_CPP_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_CPP_UPPER_DEPS.tmp
endif
ifneq ($(strip $(C++_DEPS)),)
	-$(file > clean_C++_DEPS.tmp , $(C++_DEPS))
	-@ xargs -s 6000 -t -a clean_C++_DEPS.tmp $(RM)
	-@$(RM) clean_C++_DEPS.tmp
endif
ifneq ($(strip $(C++_UPPER_DEPS)),)
	-$(file > clean_C++_UPPER_DEPS.tmp , $(C++_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_C++_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_C++_UPPER_DEPS.tmp
endif
ifneq ($(strip $(CP_DEPS)),)
	-$(file > clean_CP_DEPS.tmp , $(CP_DEPS))
	-@ xargs -s 6000 -t -a clean_CP_DEPS.tmp $(RM)
	-@$(RM) clean_CP_DEPS.tmp
endif
ifneq ($(strip $(CP_UPPER_DEPS)),)
	-$(file > clean_CP_UPPER_DEPS.tmp , $(CP_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_CP_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_CP_UPPER_DEPS.tmp
endif
ifneq ($(strip $(CXX_DEPS)),)
	-$(file > clean_CXX_DEPS.tmp , $(CXX_DEPS))
	-@ xargs -s 6000 -t -a clean_CXX_DEPS.tmp $(RM)
	-@$(RM) clean_CXX_DEPS.tmp
endif
ifneq ($(strip $(CXX_UPPER_DEPS)),)
	-$(file > clean_CXX_UPPER_DEPS.tmp , $(CXX_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_CXX_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_CXX_UPPER_DEPS.tmp
endif
ifneq ($(strip $(CC_DEPS)),)
	-$(file > clean_CC_DEPS.tmp , $(CC_DEPS))
	-@ xargs -s 6000 -t -a clean_CC_DEPS.tmp $(RM)
	-@$(RM) clean_CC_DEPS.tmp
endif
ifneq ($(strip $(CC_UPPER_DEPS)),)
	-$(file > clean_CC_UPPER_DEPS.tmp , $(CC_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_CC_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_CC_UPPER_DEPS.tmp
endif
ifneq ($(strip $(ASM_PRNS)),)
	-$(file > clean_ASM_PRNS.tmp , $(ASM_PRNS))
	-@ xargs -s 6000 -t -a clean_ASM_PRNS.tmp $(RM)
	-@$(RM) clean_ASM_PRNS.tmp
endif
ifneq ($(strip $(OBJ_DEPS)),)
	-$(file > clean_OBJ_DEPS.tmp , $(OBJ_DEPS))
	-@ xargs -s 6000 -t -a clean_OBJ_DEPS.tmp $(RM)
	-@$(RM) clean_OBJ_DEPS.tmp
endif
ifneq ($(strip $(ABS_DEPS)),)
	-$(file > clean_ABS_DEPS.tmp , $(ABS_DEPS))
	-@ xargs -s 6000 -t -a clean_ABS_DEPS.tmp $(RM)
	-@$(RM) clean_ABS_DEPS.tmp
endif
ifneq ($(strip $(O_DEPS)),)
	-$(file > clean_O_DEPS.tmp , $(O_DEPS))
	-@ xargs -s 6000 -t -a clean_O_DEPS.tmp $(RM)
	-@$(RM) clean_O_DEPS.tmp
endif
ifneq ($(strip $(S_DEPS)),)
	-$(file > clean_S_DEPS.tmp , $(S_DEPS))
	-@ xargs -s 6000 -t -a clean_S_DEPS.tmp $(RM)
	-@$(RM) clean_S_DEPS.tmp
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
	-$(file > clean_S_UPPER_DEPS.tmp , $(S_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_S_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_S_UPPER_DEPS.tmp
endif
ifneq ($(strip $(SRC_DEPS)),)
	-$(file > clean_SRC_DEPS.tmp , $(SRC_DEPS))
	-@ xargs -s 6000 -t -a clean_SRC_DEPS.tmp $(RM)
	-@$(RM) clean_SRC_DEPS.tmp
endif
ifneq ($(strip $(SRC_UPPER_DEPS)),)
	-$(file > clean_SRC_UPPER_DEPS.tmp , $(SRC_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_SRC_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_SRC_UPPER_DEPS.tmp
endif
ifneq ($(strip $(ASM_DEPS)),)
	-$(file > clean_ASM_DEPS.tmp , $(ASM_DEPS))
	-@ xargs -s 6000 -t -a clean_ASM_DEPS.tmp $(RM)
	-@$(RM) clean_ASM_DEPS.tmp
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
	-$(file > clean_ASM_UPPER_DEPS.tmp , $(ASM_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_ASM_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_ASM_UPPER_DEPS.tmp
endif
	-$(RM) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) $(CONVERTOR_OUTPUT_OUTPUTS) 
	-rm -rf "src/bsp/board/rdkrx63n"/*.obj "src/bsp/board/rdkrx63n"/*.d "src/bsp/board/rdkrx63n"/*.src "src/bsp/board/rdkrx63n"/*.p "src/bsp/board/rdkrx63n"/*.pp "src/bsp/board/rdkrx63n"/*.mrc "src/bsp/board/rdkrx63n"/*.prn "src/bsp/board/rdkrx63n"/*.asm "src/bsp/board/rdkrx63n"/*.lst
	-rm -rf "src/driver"/*.obj "src/driver"/*.d "src/driver"/*.src "src/driver"/*.p "src/driver"/*.pp "src/driver"/*.mrc "src/driver"/*.prn "src/driver"/*.asm "src/driver"/*.lst
	-rm -rf "src/r_glyph/src/glyph/drivers"/*.obj "src/r_glyph/src/glyph/drivers"/*.d "src/r_glyph/src/glyph/drivers"/*.src "src/r_glyph/src/glyph/drivers"/*.p "src/r_glyph/src/glyph/drivers"/*.pp "src/r_glyph/src/glyph/drivers"/*.mrc "src/r_glyph/src/glyph/drivers"/*.prn "src/r_glyph/src/glyph/drivers"/*.asm "src/r_glyph/src/glyph/drivers"/*.lst
	-rm -rf "src/r_glyph/src/glyph/fonts"/*.obj "src/r_glyph/src/glyph/fonts"/*.d "src/r_glyph/src/glyph/fonts"/*.src "src/r_glyph/src/glyph/fonts"/*.p "src/r_glyph/src/glyph/fonts"/*.pp "src/r_glyph/src/glyph/fonts"/*.mrc "src/r_glyph/src/glyph/fonts"/*.prn "src/r_glyph/src/glyph/fonts"/*.asm "src/r_glyph/src/glyph/fonts"/*.lst
	-rm -rf "src/r_glyph/src/glyph"/*.obj "src/r_glyph/src/glyph"/*.d "src/r_glyph/src/glyph"/*.src "src/r_glyph/src/glyph"/*.p "src/r_glyph/src/glyph"/*.pp "src/r_glyph/src/glyph"/*.mrc "src/r_glyph/src/glyph"/*.prn "src/r_glyph/src/glyph"/*.asm "src/r_glyph/src/glyph"/*.lst
	-rm -rf "src/r_glyph/src"/*.obj "src/r_glyph/src"/*.d "src/r_glyph/src"/*.src "src/r_glyph/src"/*.p "src/r_glyph/src"/*.pp "src/r_glyph/src"/*.mrc "src/r_glyph/src"/*.prn "src/r_glyph/src"/*.asm "src/r_glyph/src"/*.lst
	-rm -rf "src/r_rspi_rx600/src"/*.obj "src/r_rspi_rx600/src"/*.d "src/r_rspi_rx600/src"/*.src "src/r_rspi_rx600/src"/*.p "src/r_rspi_rx600/src"/*.pp "src/r_rspi_rx600/src"/*.mrc "src/r_rspi_rx600/src"/*.prn "src/r_rspi_rx600/src"/*.asm "src/r_rspi_rx600/src"/*.lst
	-rm -rf "src/uip/apps/dhcpc"/*.obj "src/uip/apps/dhcpc"/*.d "src/uip/apps/dhcpc"/*.src "src/uip/apps/dhcpc"/*.p "src/uip/apps/dhcpc"/*.pp "src/uip/apps/dhcpc"/*.mrc "src/uip/apps/dhcpc"/*.prn "src/uip/apps/dhcpc"/*.asm "src/uip/apps/dhcpc"/*.lst
	-rm -rf "src/uip/apps/webserver"/*.obj "src/uip/apps/webserver"/*.d "src/uip/apps/webserver"/*.src "src/uip/apps/webserver"/*.p "src/uip/apps/webserver"/*.pp "src/uip/apps/webserver"/*.mrc "src/uip/apps/webserver"/*.prn "src/uip/apps/webserver"/*.asm "src/uip/apps/webserver"/*.lst
	-rm -rf "src/uip/uip"/*.obj "src/uip/uip"/*.d "src/uip/uip"/*.src "src/uip/uip"/*.p "src/uip/uip"/*.pp "src/uip/uip"/*.mrc "src/uip/uip"/*.prn "src/uip/uip"/*.asm "src/uip/uip"/*.lst
	-rm -rf "src/uip/unix"/*.obj "src/uip/unix"/*.d "src/uip/unix"/*.src "src/uip/unix"/*.p "src/uip/unix"/*.pp "src/uip/unix"/*.mrc "src/uip/unix"/*.prn "src/uip/unix"/*.asm "src/uip/unix"/*.lst
	-rm -rf "src/user-app"/*.obj "src/user-app"/*.d "src/user-app"/*.src "src/user-app"/*.p "src/user-app"/*.pp "src/user-app"/*.mrc "src/user-app"/*.prn "src/user-app"/*.asm "src/user-app"/*.lst
	@echo.
	@echo 'Clean complete.'

post-build:
	@echo.
	-C:\Renesas\DEBUGC~1\RENESA~1.EXE SISK_HTTP.abs SISK_HTTP.x 
	@echo.

.PHONY: all clean dependents $(LINKER_OUTPUT_OUTPUTS)
.SECONDARY: post-build

-include ../makefile.targets
