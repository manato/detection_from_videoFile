##############################################
# Makefile for line detection sample program #
##############################################
TARGET	= line_detect

# Compiler option
G++	= g++


# Additional include path
INC_PATH	= -I./ -I/usr/local/include/opencv -I/usr/local/include/opencv2 

# Additional library path
LIB_PATH	= -L./ -L/usr/local/lib 


# Additional library
 LIB	= -lopencv_highgui -lopencv_core -lopencv_imgproc -lm -ldeal_image -lpthread

all:
	$(G++) $(INC_PATH) $(LIB_PATH) -o $(TARGET)  operate_ShareMem.cpp line_detection.cpp $(LIB)

clean:
	rm -f ./*~ ./$(TARGET)

install:
	cp ./line_detect ../../bin/line_detecter/line_detecter
