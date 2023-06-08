
CXX    = g++
CXXLINK  = $(CXX)
CXXFLAGS = -Wall -g -std=c++11
OBJS   = string.o ip.o port.o 
EXEC   = firewall.exe
LIBS   = libfirewall.so main.o libinput.so
RM     = rm -fr *.exe *.o libfirewall.so 

$(EXEC) : $(LIBS) 
	$(CXXLINK) $(CXXFLAGS) main.o -o $(EXEC) -lfirewall -linput -L.
	
libfirewall.so : string.o ip.o port.o 
	$(CXXLINK) -shared $(OBJS) -o libfirewall.so -L.
	
main.o : main.cpp string.h ip.h port.h generic-field.h
	$(CXX) $(CXXFLAGS) -c -fPIC main.cpp

string.o : string.cpp string.h
	$(CXX) $(CXXFLAGS) -c -fpic string.cpp
	
ip.o : ip.cpp ip.h string.h generic-field.h
	$(CXX) $(CXXFLAGS) -c -fpic ip.cpp

port.o : port.cpp port.h string.h generic-field.h
	$(CXX) $(CXXFLAGS) -c -fpic port.cpp
							
clean:
	$(RM)
