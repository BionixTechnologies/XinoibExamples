
ifdef R
	CC = arm-linux-gnueabi-gcc
	AR = arm-linux-gnueabi-ar
else
	CC = gcc
endif


TARGET = inventory_unique_button

bin/$(TARGET): obj/main.o obj/tag_list.o /usr/bnxlibs/libBNXrfid.a /usr/bnxlibs/libBNXio.a
	$(CC) $^ -o $@ -lpthread -Wall

obj/main.o: main.c
	$(CC) -c $< -o $@ 
obj/tag_list.o: tag_list.c
	$(CC) -c $< -o $@

clean:
	rm -f obj/*.o $(TARGET)





