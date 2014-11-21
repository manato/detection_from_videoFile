############
# Makefile #
############

TARGET	= ../libdeal_image.so

# Compile flag
GCC	= gcc -shared

# additional include path
INC_PATH	= -I/usr/local/include/opencv/ 

# additional library path
LIB_PATH	= -L/usr/local/lib/

# additional library
LIB	= -lopencv_highgui -fPIC


all:
	$(GCC) $(INC_PATH) $(LIB_PATH) -o $(TARGET) deal_image.c $(LIB)

clean:
	rm -f $(TARGET) ./*~
