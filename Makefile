CXX=g++
CXXFLAGS=-std=c++14 -Wall -MMD -Werror=vla
EXEC=RAIInet
OBJECTS=main.o cell.o grid.o player.o link.o virus.o data.o textdisplay.o display.o graphicsdisplay.o window.o exception.o
DEPENDS=${OBJECTS:.o=.d}
${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11
-include ${DEPENDS}

.PHONY: clean

clean:  
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
