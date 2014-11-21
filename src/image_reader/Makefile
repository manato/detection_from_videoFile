#########################################################
# Makefile for camera server for PGR grasshopper camera #
#########################################################
TARGET	= image_reader

# Compile flag
GCC = gcc


# additional include path
INC_PATH	= -I/usr/local/include/opencv -I./ -I/usr/include/flycapture

# additional library path
LIB_PATH	= -L/usr/locla/lib -L./

#additional library
LIB	= -lopencv_highgui -lopencv_core -lopencv_imgproc -lpthread -ldeal_image -lflycapture-c

all:
	$(GCC) $(INC_PATH) $(LIB_PATH) -o $(TARGET) image_reader.c $(LIB)

clean:
	rm -f $(TARGET) $(TARGET_NO_LINE_DETECT) ./*~

install:
	cp ./$(TARGET) ../../bin/image_receiver/$(TARGET)
	cp ./libdeal_image.so ../../lib/libdeal_image.so
