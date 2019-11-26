/**
 * @file MQTTCommunication.cpp
 * @brief Implementation of the Connection class
 *
 * @author Luca Mazzoleni (luca.mazzoleni@hsr.ch)
 *
 * @version 1.0 - added Connection-Implementation - Luca Mazzoleni (luca.mazzoleni@hsr.ch) - 2019-04-16
 *
 * @date 2019-04-09
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

//==Global Vairable====
myJSON _myjson(MAX_JSON_PARSE_SIZE);                         ///< instance of myJSON
CircularBuffer<myJSONStr, MAX_JSON_MESSAGES_SAVED> _buffer;  ///< instance of CircularBuffer

//======Func====
/**
 * @todo Change global implementation of callback. Maybe with static?
 */
void callback(char* topic, byte* payload, unsigned int length) 
{
    DBFUNCCALLln("callback(const char[] topic, byte* payload, unsigned int length)");
    String topic_str = String((char*)topic);
    char payload_str[length];
    for (unsigned int i = 0; i < length; i++) 
    {  // iterate message till lentgh caus it's not 0-terminated
        payload_str[i] = (char)payload[i];
    }
    translateJsonToStruct(topic, payload_str, length);

    String currentMessage = topic_str + " " + payload_str;
    DBINFO3("CurrMessage: ");
    DBINFO3ln(currentMessage);    
}

Communication::Communication(String Hostname) : pHostname(Hostname) 
{
    init();
}
