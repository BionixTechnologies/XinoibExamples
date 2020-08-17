
ifdef R
	CC = arm-linux-gnueabi-gcc
	AR = arm-linux-gnueabi-ar
else
	CC = gcc
endif


TARGET = blinkLed

bin/$(TARGET): obj/main.o /usr/bnxlibs/libBNXio.a
	$(CC) $^ -o $@ -lpthread -Wall

obj/main.o: main.c
	$(CC) -c $< -o $@ 
clean:
	rm -f obj/*.o $(TARGET)





