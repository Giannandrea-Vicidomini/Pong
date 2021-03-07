SFML = /usr/local/Cellar/sfml/2.5.1_1
JSONCPP =  /usr/local/Cellar/jsoncpp/1.9.4_1
INCFOLDER = -I ${SFML}/include -I ${JSONCPP}/include
LIBFOLDER = -L ${SFML}/lib -L ${JSONCPP}/lib
CC = g++ 
STD = -std=c++17
ALIAS =  -o sfml

LIBS =  -l sfml-audio.2.5.1 -l sfml-graphics.2.5.1  -l sfml-network.2.5.1 -l sfml-system.2.5.1  -l sfml-window.2.5.1
LIBS+= -l jsoncpp.24

MAIN = main.cpp

exe:
	${CC} ${MAIN} ${INCFOLDER} ${LIBFOLDER} ${LIBS} ${ALIAS} ${STD}