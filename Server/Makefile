servermain: servermain.o serverclass.o
	g++ -o servermain servermain.o serverclass.o
servermain.o: servermain.cc package.hpp
	g++ -c servermain.cc
serverclass.o: serverclass.cc package.hpp
	g++ -c serverclass.cc
