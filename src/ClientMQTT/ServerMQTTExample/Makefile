all: mqtt_sub
	echo "Build finish!"
mqtt_sub: mqtt_sub.c
	gcc mqtt_sub.c -o mqtt_sub -lmosquitto
clean:
	rm mqtt_sub
