
ifdef R
	CC = arm-linux-gnueabi-gcc
	AR = arm-linux-gnueabi-ar
else
	CC = gcc
endif


TARGET = enable_impinj_extensions

$(TARGET): main.o ../../lib/libBNXrfid.a
	$(CC) $^ -o $@ -lpthread -Wall

main.o: main.c
	$(CC) -c $< -o $@ 

clean:
	rm -f *.o *.a $(TARGET)





