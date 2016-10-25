#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/CommanderMain.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/CommanderMain.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=UISourcefiles/XLCD/busyxlcd.c UISourcefiles/XLCD/openxlcd.c UISourcefiles/XLCD/putrxlcd.c UISourcefiles/XLCD/putsxlcd.c UISourcefiles/XLCD/readaddr.c UISourcefiles/XLCD/readdata.c UISourcefiles/XLCD/setcgram.c UISourcefiles/XLCD/setddram.c UISourcefiles/XLCD/UserinterfaceInitialise.c UISourcefiles/XLCD/wcmdxlcd.c UISourcefiles/XLCD/writdata.c UISourcefiles/LCDWrite.c UISourcefiles/PrimaryInterfaceOutput.c UISourcefiles/SecondaryInterfaceOutput.c UISourcefiles/StateTransition.c UISourcefiles/UserInput.c UISourcefiles/UserInterface.c UISourcefiles/xlcddelays.c UISourcefiles/servo.c putsuart.c readuart.asm writuart.asm Communications.c Navigation.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/UISourcefiles/XLCD/busyxlcd.o ${OBJECTDIR}/UISourcefiles/XLCD/openxlcd.o ${OBJECTDIR}/UISourcefiles/XLCD/putrxlcd.o ${OBJECTDIR}/UISourcefiles/XLCD/putsxlcd.o ${OBJECTDIR}/UISourcefiles/XLCD/readaddr.o ${OBJECTDIR}/UISourcefiles/XLCD/readdata.o ${OBJECTDIR}/UISourcefiles/XLCD/setcgram.o ${OBJECTDIR}/UISourcefiles/XLCD/setddram.o ${OBJECTDIR}/UISourcefiles/XLCD/UserinterfaceInitialise.o ${OBJECTDIR}/UISourcefiles/XLCD/wcmdxlcd.o ${OBJECTDIR}/UISourcefiles/XLCD/writdata.o ${OBJECTDIR}/UISourcefiles/LCDWrite.o ${OBJECTDIR}/UISourcefiles/PrimaryInterfaceOutput.o ${OBJECTDIR}/UISourcefiles/SecondaryInterfaceOutput.o ${OBJECTDIR}/UISourcefiles/StateTransition.o ${OBJECTDIR}/UISourcefiles/UserInput.o ${OBJECTDIR}/UISourcefiles/UserInterface.o ${OBJECTDIR}/UISourcefiles/xlcddelays.o ${OBJECTDIR}/UISourcefiles/servo.o ${OBJECTDIR}/putsuart.o ${OBJECTDIR}/readuart.o ${OBJECTDIR}/writuart.o ${OBJECTDIR}/Communications.o ${OBJECTDIR}/Navigation.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/UISourcefiles/XLCD/busyxlcd.o.d ${OBJECTDIR}/UISourcefiles/XLCD/openxlcd.o.d ${OBJECTDIR}/UISourcefiles/XLCD/putrxlcd.o.d ${OBJECTDIR}/UISourcefiles/XLCD/putsxlcd.o.d ${OBJECTDIR}/UISourcefiles/XLCD/readaddr.o.d ${OBJECTDIR}/UISourcefiles/XLCD/readdata.o.d ${OBJECTDIR}/UISourcefiles/XLCD/setcgram.o.d ${OBJECTDIR}/UISourcefiles/XLCD/setddram.o.d ${OBJECTDIR}/UISourcefiles/XLCD/UserinterfaceInitialise.o.d ${OBJECTDIR}/UISourcefiles/XLCD/wcmdxlcd.o.d ${OBJECTDIR}/UISourcefiles/XLCD/writdata.o.d ${OBJECTDIR}/UISourcefiles/LCDWrite.o.d ${OBJECTDIR}/UISourcefiles/PrimaryInterfaceOutput.o.d ${OBJECTDIR}/UISourcefiles/SecondaryInterfaceOutput.o.d ${OBJECTDIR}/UISourcefiles/StateTransition.o.d ${OBJECTDIR}/UISourcefiles/UserInput.o.d ${OBJECTDIR}/UISourcefiles/UserInterface.o.d ${OBJECTDIR}/UISourcefiles/xlcddelays.o.d ${OBJECTDIR}/UISourcefiles/servo.o.d ${OBJECTDIR}/putsuart.o.d ${OBJECTDIR}/readuart.o.d ${OBJECTDIR}/writuart.o.d ${OBJECTDIR}/Communications.o.d ${OBJECTDIR}/Navigation.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/UISourcefiles/XLCD/busyxlcd.o ${OBJECTDIR}/UISourcefiles/XLCD/openxlcd.o ${OBJECTDIR}/UISourcefiles/XLCD/putrxlcd.o ${OBJECTDIR}/UISourcefiles/XLCD/putsxlcd.o ${OBJECTDIR}/UISourcefiles/XLCD/readaddr.o ${OBJECTDIR}/UISourcefiles/XLCD/readdata.o ${OBJECTDIR}/UISourcefiles/XLCD/setcgram.o ${OBJECTDIR}/UISourcefiles/XLCD/setddram.o ${OBJECTDIR}/UISourcefiles/XLCD/UserinterfaceInitialise.o ${OBJECTDIR}/UISourcefiles/XLCD/wcmdxlcd.o ${OBJECTDIR}/UISourcefiles/XLCD/writdata.o ${OBJECTDIR}/UISourcefiles/LCDWrite.o ${OBJECTDIR}/UISourcefiles/PrimaryInterfaceOutput.o ${OBJECTDIR}/UISourcefiles/SecondaryInterfaceOutput.o ${OBJECTDIR}/UISourcefiles/StateTransition.o ${OBJECTDIR}/UISourcefiles/UserInput.o ${OBJECTDIR}/UISourcefiles/UserInterface.o ${OBJECTDIR}/UISourcefiles/xlcddelays.o ${OBJECTDIR}/UISourcefiles/servo.o ${OBJECTDIR}/putsuart.o ${OBJECTDIR}/readuart.o ${OBJECTDIR}/writuart.o ${OBJECTDIR}/Communications.o ${OBJECTDIR}/Navigation.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=UISourcefiles/XLCD/busyxlcd.c UISourcefiles/XLCD/openxlcd.c UISourcefiles/XLCD/putrxlcd.c UISourcefiles/XLCD/putsxlcd.c UISourcefiles/XLCD/readaddr.c UISourcefiles/XLCD/readdata.c UISourcefiles/XLCD/setcgram.c UISourcefiles/XLCD/setddram.c UISourcefiles/XLCD/UserinterfaceInitialise.c UISourcefiles/XLCD/wcmdxlcd.c UISourcefiles/XLCD/writdata.c UISourcefiles/LCDWrite.c UISourcefiles/PrimaryInterfaceOutput.c UISourcefiles/SecondaryInterfaceOutput.c UISourcefiles/StateTransition.c UISourcefiles/UserInput.c UISourcefiles/UserInterface.c UISourcefiles/xlcddelays.c UISourcefiles/servo.c putsuart.c readuart.asm writuart.asm Communications.c Navigation.c main.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/CommanderMain.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F4520
MP_PROCESSOR_OPTION_LD=18f4520
MP_LINKER_DEBUG_OPTION= -u_DEBUGCODESTART=0x7d30 -u_DEBUGCODELEN=0x2d0 -u_DEBUGDATASTART=0x5ef -u_DEBUGDATALEN=0x10
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/readuart.o: readuart.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/readuart.o.d 
	@${RM} ${OBJECTDIR}/readuart.o 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/readuart.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -d__DEBUG -d__MPLAB_DEBUGGER_ICD3=1 -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/readuart.lst\" -e\"${OBJECTDIR}/readuart.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/readuart.o\" \"readuart.asm\"
	@${DEP_GEN} -d "${OBJECTDIR}/readuart.o"
	@${FIXDEPS} "${OBJECTDIR}/readuart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/writuart.o: writuart.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/writuart.o.d 
	@${RM} ${OBJECTDIR}/writuart.o 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/writuart.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -d__DEBUG -d__MPLAB_DEBUGGER_ICD3=1 -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/writuart.lst\" -e\"${OBJECTDIR}/writuart.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/writuart.o\" \"writuart.asm\"
	@${DEP_GEN} -d "${OBJECTDIR}/writuart.o"
	@${FIXDEPS} "${OBJECTDIR}/writuart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/readuart.o: readuart.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/readuart.o.d 
	@${RM} ${OBJECTDIR}/readuart.o 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/readuart.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/readuart.lst\" -e\"${OBJECTDIR}/readuart.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/readuart.o\" \"readuart.asm\"
	@${DEP_GEN} -d "${OBJECTDIR}/readuart.o"
	@${FIXDEPS} "${OBJECTDIR}/readuart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/writuart.o: writuart.asm  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/writuart.o.d 
	@${RM} ${OBJECTDIR}/writuart.o 
	@${FIXDEPS} dummy.d -e "${OBJECTDIR}/writuart.err" $(SILENT) -c ${MP_AS} $(MP_EXTRA_AS_PRE) -q -p$(MP_PROCESSOR_OPTION)  -l\"${OBJECTDIR}/writuart.lst\" -e\"${OBJECTDIR}/writuart.err\" $(ASM_OPTIONS)  -o\"${OBJECTDIR}/writuart.o\" \"writuart.asm\"
	@${DEP_GEN} -d "${OBJECTDIR}/writuart.o"
	@${FIXDEPS} "${OBJECTDIR}/writuart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/UISourcefiles/XLCD/busyxlcd.o: UISourcefiles/XLCD/busyxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/busyxlcd.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/busyxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/busyxlcd.o   UISourcefiles/XLCD/busyxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/busyxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/busyxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/XLCD/openxlcd.o: UISourcefiles/XLCD/openxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/openxlcd.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/openxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/openxlcd.o   UISourcefiles/XLCD/openxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/openxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/openxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/XLCD/putrxlcd.o: UISourcefiles/XLCD/putrxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/putrxlcd.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/putrxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/putrxlcd.o   UISourcefiles/XLCD/putrxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/putrxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/putrxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/XLCD/putsxlcd.o: UISourcefiles/XLCD/putsxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/putsxlcd.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/putsxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/putsxlcd.o   UISourcefiles/XLCD/putsxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/putsxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/putsxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/XLCD/readaddr.o: UISourcefiles/XLCD/readaddr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/readaddr.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/readaddr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/readaddr.o   UISourcefiles/XLCD/readaddr.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/readaddr.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/readaddr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/XLCD/readdata.o: UISourcefiles/XLCD/readdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/readdata.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/readdata.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/readdata.o   UISourcefiles/XLCD/readdata.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/readdata.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/readdata.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/XLCD/setcgram.o: UISourcefiles/XLCD/setcgram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/setcgram.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/setcgram.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/setcgram.o   UISourcefiles/XLCD/setcgram.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/setcgram.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/setcgram.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/XLCD/setddram.o: UISourcefiles/XLCD/setddram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/setddram.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/setddram.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/setddram.o   UISourcefiles/XLCD/setddram.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/setddram.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/setddram.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/XLCD/UserinterfaceInitialise.o: UISourcefiles/XLCD/UserinterfaceInitialise.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/UserinterfaceInitialise.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/UserinterfaceInitialise.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/UserinterfaceInitialise.o   UISourcefiles/XLCD/UserinterfaceInitialise.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/UserinterfaceInitialise.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/UserinterfaceInitialise.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/XLCD/wcmdxlcd.o: UISourcefiles/XLCD/wcmdxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/wcmdxlcd.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/wcmdxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/wcmdxlcd.o   UISourcefiles/XLCD/wcmdxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/wcmdxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/wcmdxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/XLCD/writdata.o: UISourcefiles/XLCD/writdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/writdata.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/writdata.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/writdata.o   UISourcefiles/XLCD/writdata.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/writdata.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/writdata.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/LCDWrite.o: UISourcefiles/LCDWrite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles" 
	@${RM} ${OBJECTDIR}/UISourcefiles/LCDWrite.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/LCDWrite.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/LCDWrite.o   UISourcefiles/LCDWrite.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/LCDWrite.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/LCDWrite.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/PrimaryInterfaceOutput.o: UISourcefiles/PrimaryInterfaceOutput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles" 
	@${RM} ${OBJECTDIR}/UISourcefiles/PrimaryInterfaceOutput.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/PrimaryInterfaceOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/PrimaryInterfaceOutput.o   UISourcefiles/PrimaryInterfaceOutput.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/PrimaryInterfaceOutput.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/PrimaryInterfaceOutput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/SecondaryInterfaceOutput.o: UISourcefiles/SecondaryInterfaceOutput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles" 
	@${RM} ${OBJECTDIR}/UISourcefiles/SecondaryInterfaceOutput.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/SecondaryInterfaceOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/SecondaryInterfaceOutput.o   UISourcefiles/SecondaryInterfaceOutput.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/SecondaryInterfaceOutput.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/SecondaryInterfaceOutput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/StateTransition.o: UISourcefiles/StateTransition.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles" 
	@${RM} ${OBJECTDIR}/UISourcefiles/StateTransition.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/StateTransition.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/StateTransition.o   UISourcefiles/StateTransition.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/StateTransition.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/StateTransition.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/UserInput.o: UISourcefiles/UserInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles" 
	@${RM} ${OBJECTDIR}/UISourcefiles/UserInput.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/UserInput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/UserInput.o   UISourcefiles/UserInput.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/UserInput.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/UserInput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/UserInterface.o: UISourcefiles/UserInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles" 
	@${RM} ${OBJECTDIR}/UISourcefiles/UserInterface.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/UserInterface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/UserInterface.o   UISourcefiles/UserInterface.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/UserInterface.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/UserInterface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/xlcddelays.o: UISourcefiles/xlcddelays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles" 
	@${RM} ${OBJECTDIR}/UISourcefiles/xlcddelays.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/xlcddelays.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/xlcddelays.o   UISourcefiles/xlcddelays.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/xlcddelays.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/xlcddelays.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/servo.o: UISourcefiles/servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles" 
	@${RM} ${OBJECTDIR}/UISourcefiles/servo.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/servo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/servo.o   UISourcefiles/servo.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/servo.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/putsuart.o: putsuart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/putsuart.o.d 
	@${RM} ${OBJECTDIR}/putsuart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/putsuart.o   putsuart.c 
	@${DEP_GEN} -d ${OBJECTDIR}/putsuart.o 
	@${FIXDEPS} "${OBJECTDIR}/putsuart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Communications.o: Communications.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Communications.o.d 
	@${RM} ${OBJECTDIR}/Communications.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Communications.o   Communications.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Communications.o 
	@${FIXDEPS} "${OBJECTDIR}/Communications.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Navigation.o: Navigation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Navigation.o.d 
	@${RM} ${OBJECTDIR}/Navigation.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Navigation.o   Navigation.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Navigation.o 
	@${FIXDEPS} "${OBJECTDIR}/Navigation.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/main.o   main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/UISourcefiles/XLCD/busyxlcd.o: UISourcefiles/XLCD/busyxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/busyxlcd.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/busyxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/busyxlcd.o   UISourcefiles/XLCD/busyxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/busyxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/busyxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/XLCD/openxlcd.o: UISourcefiles/XLCD/openxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/openxlcd.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/openxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/openxlcd.o   UISourcefiles/XLCD/openxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/openxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/openxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/XLCD/putrxlcd.o: UISourcefiles/XLCD/putrxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/putrxlcd.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/putrxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/putrxlcd.o   UISourcefiles/XLCD/putrxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/putrxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/putrxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/XLCD/putsxlcd.o: UISourcefiles/XLCD/putsxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/putsxlcd.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/putsxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/putsxlcd.o   UISourcefiles/XLCD/putsxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/putsxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/putsxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/XLCD/readaddr.o: UISourcefiles/XLCD/readaddr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/readaddr.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/readaddr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/readaddr.o   UISourcefiles/XLCD/readaddr.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/readaddr.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/readaddr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/XLCD/readdata.o: UISourcefiles/XLCD/readdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/readdata.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/readdata.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/readdata.o   UISourcefiles/XLCD/readdata.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/readdata.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/readdata.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/XLCD/setcgram.o: UISourcefiles/XLCD/setcgram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/setcgram.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/setcgram.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/setcgram.o   UISourcefiles/XLCD/setcgram.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/setcgram.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/setcgram.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/XLCD/setddram.o: UISourcefiles/XLCD/setddram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/setddram.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/setddram.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/setddram.o   UISourcefiles/XLCD/setddram.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/setddram.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/setddram.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/XLCD/UserinterfaceInitialise.o: UISourcefiles/XLCD/UserinterfaceInitialise.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/UserinterfaceInitialise.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/UserinterfaceInitialise.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/UserinterfaceInitialise.o   UISourcefiles/XLCD/UserinterfaceInitialise.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/UserinterfaceInitialise.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/UserinterfaceInitialise.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/XLCD/wcmdxlcd.o: UISourcefiles/XLCD/wcmdxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/wcmdxlcd.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/wcmdxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/wcmdxlcd.o   UISourcefiles/XLCD/wcmdxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/wcmdxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/wcmdxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/XLCD/writdata.o: UISourcefiles/XLCD/writdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles/XLCD" 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/writdata.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/XLCD/writdata.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/XLCD/writdata.o   UISourcefiles/XLCD/writdata.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/XLCD/writdata.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/XLCD/writdata.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/LCDWrite.o: UISourcefiles/LCDWrite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles" 
	@${RM} ${OBJECTDIR}/UISourcefiles/LCDWrite.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/LCDWrite.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/LCDWrite.o   UISourcefiles/LCDWrite.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/LCDWrite.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/LCDWrite.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/PrimaryInterfaceOutput.o: UISourcefiles/PrimaryInterfaceOutput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles" 
	@${RM} ${OBJECTDIR}/UISourcefiles/PrimaryInterfaceOutput.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/PrimaryInterfaceOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/PrimaryInterfaceOutput.o   UISourcefiles/PrimaryInterfaceOutput.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/PrimaryInterfaceOutput.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/PrimaryInterfaceOutput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/SecondaryInterfaceOutput.o: UISourcefiles/SecondaryInterfaceOutput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles" 
	@${RM} ${OBJECTDIR}/UISourcefiles/SecondaryInterfaceOutput.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/SecondaryInterfaceOutput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/SecondaryInterfaceOutput.o   UISourcefiles/SecondaryInterfaceOutput.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/SecondaryInterfaceOutput.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/SecondaryInterfaceOutput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/StateTransition.o: UISourcefiles/StateTransition.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles" 
	@${RM} ${OBJECTDIR}/UISourcefiles/StateTransition.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/StateTransition.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/StateTransition.o   UISourcefiles/StateTransition.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/StateTransition.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/StateTransition.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/UserInput.o: UISourcefiles/UserInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles" 
	@${RM} ${OBJECTDIR}/UISourcefiles/UserInput.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/UserInput.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/UserInput.o   UISourcefiles/UserInput.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/UserInput.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/UserInput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/UserInterface.o: UISourcefiles/UserInterface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles" 
	@${RM} ${OBJECTDIR}/UISourcefiles/UserInterface.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/UserInterface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/UserInterface.o   UISourcefiles/UserInterface.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/UserInterface.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/UserInterface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/xlcddelays.o: UISourcefiles/xlcddelays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles" 
	@${RM} ${OBJECTDIR}/UISourcefiles/xlcddelays.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/xlcddelays.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/xlcddelays.o   UISourcefiles/xlcddelays.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/xlcddelays.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/xlcddelays.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/UISourcefiles/servo.o: UISourcefiles/servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/UISourcefiles" 
	@${RM} ${OBJECTDIR}/UISourcefiles/servo.o.d 
	@${RM} ${OBJECTDIR}/UISourcefiles/servo.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/UISourcefiles/servo.o   UISourcefiles/servo.c 
	@${DEP_GEN} -d ${OBJECTDIR}/UISourcefiles/servo.o 
	@${FIXDEPS} "${OBJECTDIR}/UISourcefiles/servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/putsuart.o: putsuart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/putsuart.o.d 
	@${RM} ${OBJECTDIR}/putsuart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/putsuart.o   putsuart.c 
	@${DEP_GEN} -d ${OBJECTDIR}/putsuart.o 
	@${FIXDEPS} "${OBJECTDIR}/putsuart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Communications.o: Communications.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Communications.o.d 
	@${RM} ${OBJECTDIR}/Communications.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Communications.o   Communications.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Communications.o 
	@${FIXDEPS} "${OBJECTDIR}/Communications.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Navigation.o: Navigation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Navigation.o.d 
	@${RM} ${OBJECTDIR}/Navigation.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Navigation.o   Navigation.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Navigation.o 
	@${FIXDEPS} "${OBJECTDIR}/Navigation.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa- -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/main.o   main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/CommanderMain.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_ICD3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/CommanderMain.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/CommanderMain.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/CommanderMain.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
