CXX = u++					# compiler
CXXFLAGS = -g -multi -Wall -Wno-unused-label -MMD -O2
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS1 = soda.o config.o bank.o bottlingPlant.o groupOff.o nameServer.o parent.o printer.o student.o truck.o vendingMachine.o watcard.o watcardOffice.o # list of object files for question 1 prefixed with "q3"
EXEC1 = soda

OBJECTS = ${OBJECTS1}				# all object files
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXECS = ${EXEC1}				# all executables

#############################################################

.PHONY : all clean

all : ${EXECS}					# build all executables

${EXEC1} : ${OBJECTS1}
	${CXX} ${CXXFLAGS} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC01} ${EXECS}
