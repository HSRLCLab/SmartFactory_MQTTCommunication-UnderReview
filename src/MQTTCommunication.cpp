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

    // void pointer to receive translatet messagestruct to store in correct messagebuffer
    void *tempMessage = translateJsonToStruct(payload_str, length);

    // store messagestruct to correct buffer, check for dublicated messages
    switch (tempMessage->msgType)
    {
    case MessageType::Error:
        if (!(tempMessage->msgId == (errorMessageBuffer[1]->msgId))
        {
            delete errorMessageBuffer[1];
            errorMessageBuffer[1] = errorMessegeBuffer[0];
            errorMessageBuffer[0] = tempMessage;
        }
        else
        {
            DBINFO03("Duplicated Message");
        }
        break;
    #ifdef SORTIC
    case MessageType::SBAvailable:
        if (!(tempMessage->msgId == (sbAvailableMessageBuffer[1][(tempMessage->msgConsignor)]->msgId)))
        {
            delete sbAvailableMessageBuffer[1];
            sbAvailableMessageBuffer[1] = sbAvailableMessageBuffer[0];
            sbAvailableMessageBuffer[0] = tempMessage;
        }
        else
        {
            DBINFO03("Duplicated Message");
        }
        break;
    case MessageType::SBToSOHandshake:
        if (!(tempMessage->msgId == (handshakeMessageSBToSOBuffer[1][(tempMessage->msgConsignor)]->msgId)))
        {
            delete handshakeMessageSBToSOBuffer[1];
            handshakeMessageSBToSOBuffer[1] = handshakeMessageSBToSOBuffer[0];
            handshakeMessageSBToSOBuffer[0] = tempMessage;
        }
        else
        {
            DBINFO03("Duplicated Message");
        }
        break;
    #else
    // define storage of received messages
        // TODO
    case MessageType::SOPosition:
        break;
    case MessageType::SOState:
        break;
    case MessageType::SBToSVHandshake:
        break;
    case MessageType::SVAvailable:
        break;
    case MessageType::SVPosition:
        break;
    case MessageType::SVState:
        break;
    case MessageType::Package:
        break;
    #endif  
    default:
        break;
    }
    String currentMessage = topic_str + " " + payload_str;
    DBINFO3("CurrMessage: ");
    DBINFO3ln(currentMessage);    
}

Communication::Communication(String Hostname) : pHostname(Hostname) 
{
    init();
}
