
ifdef R
	CC = arm-linux-gnueabi-gcc
	AR = arm-linux-gnueabi-ar
else
	CC = gcc
endif


TARGET = filter_by_rssi

$(TARGET): main.o /usr/bnxlibs/libBNXrfid.a /usr/bnxlibs/libBNXio.a
	$(CC) $^ -o $@ -lpthread -Wall

main.o: main.c
	$(CC) -c $< -o $@ 

clean:
	rm -f *.o *.a $(TARGET)





