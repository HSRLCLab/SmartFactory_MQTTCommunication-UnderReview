# SmartFactory_MQTTCommunication

The SmartFactroy_MQTTCommunication is an modular part of the SmartFactory project. MQTTCommunication establishes a WLAN-connection and allows you to connect with an MQTT-Broker to send and receive message.  
Incomming messages have to be in a known JSON-format and will be serialized with the [SmartFactory_Messages](https://github.com/philipzellweger/SmartFactory_Messages) library.
This library is an redundant library with [SmartFacotry_MQTTCommunication](https://github.com/LMazzole/SmartFactory_MQTTCommunication). It uses the WiFi.h library to work with an [Esp32 DevKitC](https://www.espressif.com/en/products/hardware/esp32-devkitc/overview). In addition the callback function and the buffers are no longer implemented in this class.

<!-- add Pagebreak in Print: <div style="page-break-after: always;"></div> -->

## Table of contents
<!-- TOC Generated with https://magnetikonline.github.io/markdown-toc-generate/ -->

- [Tools and technologies](#tools-and-technologies)
	- [Doxygen](#doxygen)
	- [VSCode PlatformIO](#vscode-platformio)
	- [MQTT](#mqtt)
	- [Circular buffer](#circular-buffer)
- [Documentation](#documentation)
	- [Hardware](#hardware)
	- [Software](#software)
		- [Dependency graph](#dependency-graph)
		- [Collaboration diagram](#collaboration-diagram)
		- [Important functions and files](#important-functions-and-files)
			- [MQTTCommunication.h](#mqttcommunicationh)
			- [CommunicationConfiguration.h](#communicationconfigurationh)
			- [myJSONStr.h](#myjsonstrh)
- [FAQ's](#faqs)
	- [I'd like to use this code in my project. What do I need to know?](#id-like-to-use-this-code-in-my-project-what-do-i-need-to-know)
	- [Where can I change the configurations like MQTT-Broker IP and WLAN-Credentials?](#where-can-i-change-the-configurations-like-mqtt-broker-ip-and-wlan-credentials)
	- [I'd like to change the incoming JSON-Message. How can I do that?](#id-like-to-change-the-incoming-json-message-how-can-i-do-that)
- [ToDo's](#todos)
- [Contributors](#contributors)
- [Changelog](#changelog)
- [License](#license)


<div style="page-break-after: always;"></div>


## Tools and technologies

The Source-code is written in C++.
To achieve this project, the following tools and technologies were used.

### Doxygen
Doxygen is used for the documentation of the source code.  
An intorduction to *Doxygen* and how to install it can be found in the [ArdFSM-Repo](https://github.com/LMazzole/ArdFSM#documentation-with-doxygen).  

### VSCode PlatformIO
The used IDE is [VSCode](https://code.visualstudio.com/) with the [PlatformIO](https://platformio.org/platformio-ide)-extension.

### MQTT
MQTT (Message Queuing Telemetry Transport) is a lightweight publish-subscribe messaging protocol and requires a broker to relay the messages. It's used for M2M (machine-to-machine) communication.  
An MQTT-system always consist of a broker and one or multiple clients, which can be either subscriber or publisher. 

![mqtt](https://www.eclipse.org/community/eclipse_newsletter/2014/october/images/article1.1.png)

[Image: [MQTT101 - Eclispe Foundation](<https://www.eclipse.org/community/eclipse_newsletter/2014/october/article2.php>)]

A client can subscribe and publish to one or multiple topics. Topics are organized in a tree similar to a folder-structure in Windows. Here's an example of how such a topic-tree and published message can look like:

<p align="center"><img src="./docs/MQTTTopics.png" height="600"/></p>

This images also illustrates the scalability of MQTT appropriately.  
For more Infos about MQTT and MQTT-topics check out the MQTT-Wiki on [Github](https://github.com/mqtt/mqtt.github.io/wiki).   
[Source: [Wiki:MQTT](https://en.wikipedia.org/wiki/MQTT), [MQTT](https://mqtt.org/) ]  

<div style="page-break-after: always;"></div>

# Documentation
## Hardware
This code needs a WLAN-shield to function properly.  
It's tested with a [Esp32 DevKitC](https://www.espressif.com/en/products/hardware/esp32-devkitc/overview) from Espressif.

## Software
All functions and files are documented on the [GitHub-Page with Doxygen](https://lmazzole.github.io/SmartFactory_MQTTCommunication/)


### UML

The figure below shows the data model in UML notation.

<p align="center">
    <a href=https://github.com/philipzellweger/SmartFactory_MQTTCommunication/blob/master/docs/html/class_communication.html>
        <img src="https://github.com/philipzellweger/SmartFactory_MQTTCommunication/blob/master/docs/html/class_communication__coll__graph.png" style="border:none;"/>
    </a>
    <p align="center"><small>Click on the image to open doxygen-documentation.</p>
</p>

### Include graph

<p align="center">
    <a href=https://github.com/philipzellweger/SmartFactory_MQTTCommunication/blob/master/docs/html/_m_q_t_t_communication_8h.html>
        <img src="https://github.com/philipzellweger/SmartFactory_MQTTCommunication/blob/master/docs/html/_m_q_t_t_communication_8h__incl.png" style="border:none;"/>
    </a>
    <p align="center"><small>Click on the image to open doxygen-documentation.</p>
</p>

External libraries:  
* [PubSubClient](https://pubsubclient.knolleary.net/)
* [WiFi](https://www.arduino.cc/en/Reference/WiFi)
* [ArduinoJson](https://arduinojson.org/)


### Important functions and files

#### MQTTCommunication.h  
The *MQTTCommunication.h*-file serves as interface.
It provides the functions for:
* Network-connection
* MQTT-functionalities
* access the message-storage (circular buffer)

#### CommunicationConfiguration.h
In the *CommunicationConfiguration.h*-file are all important settings defined:
* WLAN SSID
* WLAN password
* MQTT Broker IP
* JSON parse size


<div style="page-break-after: always;"></div>

# FAQ's
#### I'd like to use this code in my project. What do I need to know?  
> All you need to do is add the GitHub-Link to this Repo under *lib_deps* in your platformio.ini File and you're set up. All dependencies are downloaded automatic.

#### Where can I change the configurations like MQTT-Broker IP and WLAN-Credentials?  
> All the Configuration data is stored in the *CommunicationConfiguration.h* file and can be edited there.




# ToDo's

All the ToDo's are documented in the source code with Doxygen.

# Contributors
- [Philip Zellweger](https://github.com/philipzellweger)
- [Luca Mazzoleni](https://github.com/LMazzole)
- Luciano Bettinaglio

# Changelog
V 1.0	-	Release BA FS19	-	[Luca Mazzoleni](https://github.com/LMazzole)

V 2.0   -	Release SA HS20 -	[Philip Zellweger](https://github.com/philipzellweger)

# License

MIT License

# Links to SmartFactory
- [SmartFactory-Sortic](https://github.com/LMazzole/SmartFactory-Sortic)
- [SmartFactory_Box-Sortic](https://github.com/LMazzole/SmartFactory_Box-Sortic)
- [SmartFactory_Vehicle-Sortic](https://github.com/LMazzole/SmartFactory_Vehicle-Sortic)
- [SmartFactory_Vehicle-Basis](https://github.com/LMazzole/SmartFactory_Vehicle-Basis)
- [SmartFactory_SorticRoboter](https://github.com/philipzellweger/SmartFactory_SorticRoboter)
- [SmartFactory_SorticRoboter_CommunicationHub](https://github.com/philipzellweger/SmartFactory_SorticRoboter_CommunicationHub)
- [SmartFactory_MQTTCommunication](https://github.com/LMazzole/SmartFactory_MQTTCommunication) for Adafruit Feather M0 Wifi
- [SmartFactory_MQTTCommunication](https://github.com/philipzellweger/SmartFactory_MQTTCommunication) for Esp32 DevKitC
- [SmartFactory_I2cCommunication](https://github.com/philipzellweger/SmartFactory_I2cCommunication)
- [SmartFactory_Messages](https://github.com/philipzellweger/SmartFactory_Messages)
