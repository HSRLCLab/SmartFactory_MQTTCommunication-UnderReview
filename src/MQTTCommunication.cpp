/**
 * @file MQTTCommunication.cpp
 * @brief Implementation of the Connection class
 *
 * @author Luca Mazzoleni (luca.mazzoleni@hsr.ch)
 *
 * @version 1.0 - added Connection-Implementation - Luca Mazzoleni (luca.mazzoleni@hsr.ch) - 2019-04-16
 * @version 2.0 - removed callback function and buffers - Philip Zellweger (philip.zellweger@hsr.ch) - 2019-12-16
 *
 * @date 2019-12-16
 * @copyright Copyright (c) 2019
 *
 */

/*
Useful Links
https://techtutorialsx.com/2017/04/29/esp32-sending-json-messages-over-mqtt/
https://randomnerdtutorials.com/decoding-and-encoding-json-with-arduino-or-esp8266/
https://arduinodiy.wordpress.com/2017/07/30/json-mqtt-and-openhab/
https://assetwolf.com/learn/sending-data-from-arduino-to-cloud
*/

#include "MQTTCommunication.h"


Communication::Communication(String Hostname, void (*callbackFPtr)(char*, unsigned char*, unsigned int)) : pHostname(Hostname), funcPointer(callbackFPtr)
{
    init();
}

