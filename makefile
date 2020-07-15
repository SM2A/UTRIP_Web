COMPILER = g++
COMPILE = -c
VERSION = -std=c++11
CF = -pedantic
CC = ${COMPILER} ${COMPILE} ${VERSION} ${CF}

SOURCES := ${shell find * -type f -name "*.cpp"}
OBJDIR  := Build
OBJECTS := ${addprefix ${OBJDIR}/,${SOURCES:.cpp=.o}}

all: utrip.out

utrip.out: ${OBJECTS}
	${COMPILER} ${VERSION} ${CF} $^ -o $@

${OBJECTS}: ${OBJDIR}/%.o: %.cpp
	mkdir -p ${@D}
	${CC} $< -o $@

-include $(OBJECTS:.o=.d)

clean:
	rm utrip.out
	rm -rfv Build