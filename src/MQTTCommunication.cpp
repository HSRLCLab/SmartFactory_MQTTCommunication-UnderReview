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
    const std::shared_ptr<Message> tempMessage = Message::translateJsonToStruct(payload_str, length);
    // store messagestruct to correct buffer, check for dublicated messages
    switch ((Message::MessageType)tempMessage->msgType)
    {
    case Message::MessageType::Error:
        for (int i = 0; i < errorMessageBuffer.size(); i++)
        {
            if ((errorMessageBuffer.at(i)->msgId == tempMessage->msgId) && (errorMessageBuffer.at(i)->msgConsignor == tempMessage->msgConsignor))
            {
                DBINFO3("Duplicated Message");
                break;
            } 
        }
        errorMessageBuffer.push_front(std::dynamic_pointer_cast<ErrorMessage, Message>(tempMessage));
        break;
    case Message::MessageType::SBAvailable:
        for (int i = 0; i < sbAvailableMessageBuffer.size(); i++)
        {
            if ((sbAvailableMessageBuffer.at(i)->msgId == tempMessage->msgId) && (sbAvailableMessageBuffer.at(i)->msgConsignor == tempMessage->msgConsignor))
            {
                DBINFO3("Duplicated Message");
                break;
            } 
        }
        sbAvailableMessageBuffer.push_front(std::dynamic_pointer_cast<SBAvailableMessage, Message>(tempMessage));
        break;
    case Message::MessageType::SBToSOHandshake:
        for (int i = 0; i < handshakeMessageSBToSOBuffer.size(); i++)
        {
            if ((handshakeMessageSBToSOBuffer.at(i)->msgId == tempMessage->msgId) && (handshakeMessageSBToSOBuffer.at(i)->msgConsignor == tempMessage->msgConsignor))
            {
                DBINFO3("Duplicated Message");
                break;
            } 
        }
        handshakeMessageSBToSOBuffer.push_front(std::dynamic_pointer_cast<SBToSOHandshakeMessage, Message>(tempMessage));
        break;
    // define storage of received messages
        // TODO
    case Message::MessageType::SOPosition:
        break;
    case Message::MessageType::SOState:
        break;
    case Message::MessageType::SBToSVHandshake:
        break;
    case Message::MessageType::SVAvailable:
        break;
    case Message::MessageType::SVPosition:
        break;
    case Message::MessageType::SVState:
        break;
    case Message::MessageType::Package:
        break;
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
