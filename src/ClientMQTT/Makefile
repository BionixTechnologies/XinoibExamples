ifdef R
	CC = arm-linux-gnueabi-gcc
	AR = arm-linux-gnueabi-ar
else
	CC = gcc
endif


TARGET = clientMQTT

$(TARGET): main.o /usr/bnxlibs/libBNXrfid.a /usr/bnxlibs/libBNXio.a
	$(CC) $^ -o $@ -lpthread -Wall -lmosquitto

main.o: main.c
	$(CC) -c $< -o $@ -lmosquitto

clean:
	rm -f *.o *.a $(TARGET)
