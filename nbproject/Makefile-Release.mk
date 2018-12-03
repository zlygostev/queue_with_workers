#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=cc
CCC=CC
CXX=CC
FC=f95
AS=as

# Macros
CND_PLATFORM=OracleSolarisStudio-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/CGoogleLoggining.o \
	${OBJECTDIR}/CStateController.o \
	${OBJECTDIR}/Request.o \
	${OBJECTDIR}/Stopper.o \
	${OBJECTDIR}/CMainQueueHandler.o \
	${OBJECTDIR}/CMsgQueue.o \
	${OBJECTDIR}/CRequestCreater.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Release.mk dist/Release/OracleSolarisStudio-Linux-x86/threadsandqueue

dist/Release/OracleSolarisStudio-Linux-x86/threadsandqueue: ${OBJECTFILES}
	${MKDIR} -p dist/Release/OracleSolarisStudio-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/threadsandqueue ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -fast -g0 -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/CGoogleLoggining.o: CGoogleLoggining.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -fast -g0 -o ${OBJECTDIR}/CGoogleLoggining.o CGoogleLoggining.cpp

${OBJECTDIR}/CStateController.o: CStateController.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -fast -g0 -o ${OBJECTDIR}/CStateController.o CStateController.cpp

${OBJECTDIR}/Request.o: Request.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -fast -g0 -o ${OBJECTDIR}/Request.o Request.cpp

${OBJECTDIR}/Stopper.o: Stopper.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -fast -g0 -o ${OBJECTDIR}/Stopper.o Stopper.cpp

${OBJECTDIR}/CMainQueueHandler.o: CMainQueueHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -fast -g0 -o ${OBJECTDIR}/CMainQueueHandler.o CMainQueueHandler.cpp

${OBJECTDIR}/CMsgQueue.o: CMsgQueue.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -fast -g0 -o ${OBJECTDIR}/CMsgQueue.o CMsgQueue.cpp

${OBJECTDIR}/CRequestCreater.o: CRequestCreater.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -fast -g0 -o ${OBJECTDIR}/CRequestCreater.o CRequestCreater.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/OracleSolarisStudio-Linux-x86/threadsandqueue
	${CCADMIN} -clean

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
