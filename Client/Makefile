clientmain: clientmain.o clientclass.o
	g++ -o clientmain clientmain.o clientclass.o
clientmain.o: clientmain.cc package.hpp
	g++ -c clientmain.cc
clientclass.o: clientclass.cc package.hpp
	g++ -c clientclass.cc
