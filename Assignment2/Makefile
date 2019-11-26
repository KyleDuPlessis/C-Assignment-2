# DPLKYL002
# Makefile in ./Assignment2_DPLKYL002 project folder to compile the driver and link it against the newly created shared libraries

CPP=g++ 
INCLUDES=-I./libs/volimagelib
LIBDIRS=-L./libs/volimagelib
LIBS= -lvolimage
CPPFLAGS=-std=c++11 $(INCLUDES) $(LIBDIRS) $(LIBS)
TARGET=Driver

# first compile - IMPLICIT PATTERN RULE for creating binary object files
%.o: %.cpp
	$(CPP) -c -o $@ $< $(CPPFLAGS)

# then link - LINKING RULE for linking binary object files together to create an executable
$(TARGET): Driver.o 
	$(CPP) -o $(TARGET) Driver.o $(CPPFLAGS)
  
# other rules
# never submit binary object / executable files
clean:
	@rm *.o Driver
	@rm ./libs/*.so
	cd ./libs/volimagelib && make clean

# build entire project
all:
	cd ./libs/volimagelib && make
	@cp -f ./libs/volimagelib/*.so ./libs
	make

# run program
run volimage:
	chmod 700 Driver
	export LD_LIBRARY_PATH=./libs && ./Driver $(args)


