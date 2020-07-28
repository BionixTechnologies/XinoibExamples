# General

This repository contains an example for how to publish TAGs with a MQTT client.

# Content 

- main.c: A simple MQTT client integrated with Xinoid, who subsribes to a topic and print out a message, everytime it receives a TAG
- makefile: to build the example

# To run

To run the example just run ./clientMQTT You have the possibility to pass the topic, the address and port by parameter.

# Dependencies and usage

To run the script, you need the following packages. Here is the installation command for Debian based systems:

~~~~~
sudo apt install gcc mosquitto mosquitto-clients libmosquitto-dev
~~~~~

