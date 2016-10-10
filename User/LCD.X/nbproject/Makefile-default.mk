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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/LCD.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/LCD.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=XLCD/writdata.c XLCD/openxlcd.c XLCD/putrxlcd.c XLCD/putsxlcd.c XLCD/readaddr.c XLCD/readdata.c XLCD/setcgram.c XLCD/setddram.c XLCD/wcmdxlcd.c XLCD/busyxlcd.c xlcddelays.c LCDWrite.c Main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/XLCD/writdata.o ${OBJECTDIR}/XLCD/openxlcd.o ${OBJECTDIR}/XLCD/putrxlcd.o ${OBJECTDIR}/XLCD/putsxlcd.o ${OBJECTDIR}/XLCD/readaddr.o ${OBJECTDIR}/XLCD/readdata.o ${OBJECTDIR}/XLCD/setcgram.o ${OBJECTDIR}/XLCD/setddram.o ${OBJECTDIR}/XLCD/wcmdxlcd.o ${OBJECTDIR}/XLCD/busyxlcd.o ${OBJECTDIR}/xlcddelays.o ${OBJECTDIR}/LCDWrite.o ${OBJECTDIR}/Main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/XLCD/writdata.o.d ${OBJECTDIR}/XLCD/openxlcd.o.d ${OBJECTDIR}/XLCD/putrxlcd.o.d ${OBJECTDIR}/XLCD/putsxlcd.o.d ${OBJECTDIR}/XLCD/readaddr.o.d ${OBJECTDIR}/XLCD/readdata.o.d ${OBJECTDIR}/XLCD/setcgram.o.d ${OBJECTDIR}/XLCD/setddram.o.d ${OBJECTDIR}/XLCD/wcmdxlcd.o.d ${OBJECTDIR}/XLCD/busyxlcd.o.d ${OBJECTDIR}/xlcddelays.o.d ${OBJECTDIR}/LCDWrite.o.d ${OBJECTDIR}/Main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/XLCD/writdata.o ${OBJECTDIR}/XLCD/openxlcd.o ${OBJECTDIR}/XLCD/putrxlcd.o ${OBJECTDIR}/XLCD/putsxlcd.o ${OBJECTDIR}/XLCD/readaddr.o ${OBJECTDIR}/XLCD/readdata.o ${OBJECTDIR}/XLCD/setcgram.o ${OBJECTDIR}/XLCD/setddram.o ${OBJECTDIR}/XLCD/wcmdxlcd.o ${OBJECTDIR}/XLCD/busyxlcd.o ${OBJECTDIR}/xlcddelays.o ${OBJECTDIR}/LCDWrite.o ${OBJECTDIR}/Main.o

# Source Files
SOURCEFILES=XLCD/writdata.c XLCD/openxlcd.c XLCD/putrxlcd.c XLCD/putsxlcd.c XLCD/readaddr.c XLCD/readdata.c XLCD/setcgram.c XLCD/setddram.c XLCD/wcmdxlcd.c XLCD/busyxlcd.c xlcddelays.c LCDWrite.c Main.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/LCD.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F4520
MP_PROCESSOR_OPTION_LD=18f4520
MP_LINKER_DEBUG_OPTION= -u_DEBUGCODESTART=0x7dc0 -u_DEBUGCODELEN=0x240 -u_DEBUGDATASTART=0x5f4 -u_DEBUGDATALEN=0xb
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/XLCD/writdata.o: XLCD/writdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/XLCD" 
	@${RM} ${OBJECTDIR}/XLCD/writdata.o.d 
	@${RM} ${OBJECTDIR}/XLCD/writdata.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/XLCD/writdata.o   XLCD/writdata.c 
	@${DEP_GEN} -d ${OBJECTDIR}/XLCD/writdata.o 
	@${FIXDEPS} "${OBJECTDIR}/XLCD/writdata.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/XLCD/openxlcd.o: XLCD/openxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/XLCD" 
	@${RM} ${OBJECTDIR}/XLCD/openxlcd.o.d 
	@${RM} ${OBJECTDIR}/XLCD/openxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/XLCD/openxlcd.o   XLCD/openxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/XLCD/openxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/XLCD/openxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/XLCD/putrxlcd.o: XLCD/putrxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/XLCD" 
	@${RM} ${OBJECTDIR}/XLCD/putrxlcd.o.d 
	@${RM} ${OBJECTDIR}/XLCD/putrxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/XLCD/putrxlcd.o   XLCD/putrxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/XLCD/putrxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/XLCD/putrxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/XLCD/putsxlcd.o: XLCD/putsxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/XLCD" 
	@${RM} ${OBJECTDIR}/XLCD/putsxlcd.o.d 
	@${RM} ${OBJECTDIR}/XLCD/putsxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/XLCD/putsxlcd.o   XLCD/putsxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/XLCD/putsxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/XLCD/putsxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/XLCD/readaddr.o: XLCD/readaddr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/XLCD" 
	@${RM} ${OBJECTDIR}/XLCD/readaddr.o.d 
	@${RM} ${OBJECTDIR}/XLCD/readaddr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/XLCD/readaddr.o   XLCD/readaddr.c 
	@${DEP_GEN} -d ${OBJECTDIR}/XLCD/readaddr.o 
	@${FIXDEPS} "${OBJECTDIR}/XLCD/readaddr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/XLCD/readdata.o: XLCD/readdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/XLCD" 
	@${RM} ${OBJECTDIR}/XLCD/readdata.o.d 
	@${RM} ${OBJECTDIR}/XLCD/readdata.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/XLCD/readdata.o   XLCD/readdata.c 
	@${DEP_GEN} -d ${OBJECTDIR}/XLCD/readdata.o 
	@${FIXDEPS} "${OBJECTDIR}/XLCD/readdata.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/XLCD/setcgram.o: XLCD/setcgram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/XLCD" 
	@${RM} ${OBJECTDIR}/XLCD/setcgram.o.d 
	@${RM} ${OBJECTDIR}/XLCD/setcgram.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/XLCD/setcgram.o   XLCD/setcgram.c 
	@${DEP_GEN} -d ${OBJECTDIR}/XLCD/setcgram.o 
	@${FIXDEPS} "${OBJECTDIR}/XLCD/setcgram.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/XLCD/setddram.o: XLCD/setddram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/XLCD" 
	@${RM} ${OBJECTDIR}/XLCD/setddram.o.d 
	@${RM} ${OBJECTDIR}/XLCD/setddram.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/XLCD/setddram.o   XLCD/setddram.c 
	@${DEP_GEN} -d ${OBJECTDIR}/XLCD/setddram.o 
	@${FIXDEPS} "${OBJECTDIR}/XLCD/setddram.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/XLCD/wcmdxlcd.o: XLCD/wcmdxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/XLCD" 
	@${RM} ${OBJECTDIR}/XLCD/wcmdxlcd.o.d 
	@${RM} ${OBJECTDIR}/XLCD/wcmdxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/XLCD/wcmdxlcd.o   XLCD/wcmdxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/XLCD/wcmdxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/XLCD/wcmdxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/XLCD/busyxlcd.o: XLCD/busyxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/XLCD" 
	@${RM} ${OBJECTDIR}/XLCD/busyxlcd.o.d 
	@${RM} ${OBJECTDIR}/XLCD/busyxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/XLCD/busyxlcd.o   XLCD/busyxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/XLCD/busyxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/XLCD/busyxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/xlcddelays.o: xlcddelays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/xlcddelays.o.d 
	@${RM} ${OBJECTDIR}/xlcddelays.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/xlcddelays.o   xlcddelays.c 
	@${DEP_GEN} -d ${OBJECTDIR}/xlcddelays.o 
	@${FIXDEPS} "${OBJECTDIR}/xlcddelays.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/LCDWrite.o: LCDWrite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LCDWrite.o.d 
	@${RM} ${OBJECTDIR}/LCDWrite.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCDWrite.o   LCDWrite.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCDWrite.o 
	@${FIXDEPS} "${OBJECTDIR}/LCDWrite.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Main.o: Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Main.o.d 
	@${RM} ${OBJECTDIR}/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Main.o   Main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/XLCD/writdata.o: XLCD/writdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/XLCD" 
	@${RM} ${OBJECTDIR}/XLCD/writdata.o.d 
	@${RM} ${OBJECTDIR}/XLCD/writdata.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/XLCD/writdata.o   XLCD/writdata.c 
	@${DEP_GEN} -d ${OBJECTDIR}/XLCD/writdata.o 
	@${FIXDEPS} "${OBJECTDIR}/XLCD/writdata.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/XLCD/openxlcd.o: XLCD/openxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/XLCD" 
	@${RM} ${OBJECTDIR}/XLCD/openxlcd.o.d 
	@${RM} ${OBJECTDIR}/XLCD/openxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/XLCD/openxlcd.o   XLCD/openxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/XLCD/openxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/XLCD/openxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/XLCD/putrxlcd.o: XLCD/putrxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/XLCD" 
	@${RM} ${OBJECTDIR}/XLCD/putrxlcd.o.d 
	@${RM} ${OBJECTDIR}/XLCD/putrxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/XLCD/putrxlcd.o   XLCD/putrxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/XLCD/putrxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/XLCD/putrxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/XLCD/putsxlcd.o: XLCD/putsxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/XLCD" 
	@${RM} ${OBJECTDIR}/XLCD/putsxlcd.o.d 
	@${RM} ${OBJECTDIR}/XLCD/putsxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/XLCD/putsxlcd.o   XLCD/putsxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/XLCD/putsxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/XLCD/putsxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/XLCD/readaddr.o: XLCD/readaddr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/XLCD" 
	@${RM} ${OBJECTDIR}/XLCD/readaddr.o.d 
	@${RM} ${OBJECTDIR}/XLCD/readaddr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/XLCD/readaddr.o   XLCD/readaddr.c 
	@${DEP_GEN} -d ${OBJECTDIR}/XLCD/readaddr.o 
	@${FIXDEPS} "${OBJECTDIR}/XLCD/readaddr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/XLCD/readdata.o: XLCD/readdata.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/XLCD" 
	@${RM} ${OBJECTDIR}/XLCD/readdata.o.d 
	@${RM} ${OBJECTDIR}/XLCD/readdata.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/XLCD/readdata.o   XLCD/readdata.c 
	@${DEP_GEN} -d ${OBJECTDIR}/XLCD/readdata.o 
	@${FIXDEPS} "${OBJECTDIR}/XLCD/readdata.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/XLCD/setcgram.o: XLCD/setcgram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/XLCD" 
	@${RM} ${OBJECTDIR}/XLCD/setcgram.o.d 
	@${RM} ${OBJECTDIR}/XLCD/setcgram.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/XLCD/setcgram.o   XLCD/setcgram.c 
	@${DEP_GEN} -d ${OBJECTDIR}/XLCD/setcgram.o 
	@${FIXDEPS} "${OBJECTDIR}/XLCD/setcgram.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/XLCD/setddram.o: XLCD/setddram.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/XLCD" 
	@${RM} ${OBJECTDIR}/XLCD/setddram.o.d 
	@${RM} ${OBJECTDIR}/XLCD/setddram.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/XLCD/setddram.o   XLCD/setddram.c 
	@${DEP_GEN} -d ${OBJECTDIR}/XLCD/setddram.o 
	@${FIXDEPS} "${OBJECTDIR}/XLCD/setddram.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/XLCD/wcmdxlcd.o: XLCD/wcmdxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/XLCD" 
	@${RM} ${OBJECTDIR}/XLCD/wcmdxlcd.o.d 
	@${RM} ${OBJECTDIR}/XLCD/wcmdxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/XLCD/wcmdxlcd.o   XLCD/wcmdxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/XLCD/wcmdxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/XLCD/wcmdxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/XLCD/busyxlcd.o: XLCD/busyxlcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/XLCD" 
	@${RM} ${OBJECTDIR}/XLCD/busyxlcd.o.d 
	@${RM} ${OBJECTDIR}/XLCD/busyxlcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/XLCD/busyxlcd.o   XLCD/busyxlcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/XLCD/busyxlcd.o 
	@${FIXDEPS} "${OBJECTDIR}/XLCD/busyxlcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/xlcddelays.o: xlcddelays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/xlcddelays.o.d 
	@${RM} ${OBJECTDIR}/xlcddelays.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/xlcddelays.o   xlcddelays.c 
	@${DEP_GEN} -d ${OBJECTDIR}/xlcddelays.o 
	@${FIXDEPS} "${OBJECTDIR}/xlcddelays.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/LCDWrite.o: LCDWrite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/LCDWrite.o.d 
	@${RM} ${OBJECTDIR}/LCDWrite.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/LCDWrite.o   LCDWrite.c 
	@${DEP_GEN} -d ${OBJECTDIR}/LCDWrite.o 
	@${FIXDEPS} "${OBJECTDIR}/LCDWrite.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/Main.o: Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Main.o.d 
	@${RM} ${OBJECTDIR}/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/Main.o   Main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/LCD.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_ICD3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/LCD.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/LCD.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/LCD.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
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
