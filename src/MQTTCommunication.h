/**
 * @file MQTTCommunication.h
 * @brief The Connection-class is used as interface
 * 
 * @author Luca Mazzoleni (luca.mazzoleni@hsr.ch)
 * 
 * @version 1.0 - added Connection-Implementation - Luca Mazzoleni (luca.mazzoleni@hsr.ch) - 2019-04-16
 * 
 * @date 2019-04-09
 * @copyright Copyright (c) 2019
 * 
 * @todo Split the Code into two Repos: SmartFactory_Communication-Sortic\n
 * and SmartFactory_MQTTCommunication-Basis to simplify modular use.
 * 
 */

#ifndef MQTTCOMMUNICATION_H__
#define MQTTCOMMUNICATION_H__

#include <Arduino.h>
#include <memory>

#include "CommunicationConfiguration.h"
#include "Network/Network.h"
#include "myMQTT/myMQTT.h"
#include "MessageTranslation.h"
#include "MainConfiguration.h"
#include "LogConfiguration.h"


/**
* @brief If the client is used to subscribe to topics,
* a callback function must be provided in the constructor. 
* his function is called when new messages arrive at the client.
* 
* Internally, the client uses the same buffer for both inbound and outbound messages.
* After the callback function returns, or if a call to either publish or subscribe
* is made from within the callback function,
* the topic and payload values passed to the function will be overwritten.
* The application should create its own copy of the values if they are required beyond this.
* 
* https://pubsubclient.knolleary.net/api.html#callback
* 
* This Function is global because you need to access it from a diffrent class and pass it as pointer.
* This would be possible if it's static but then all function which get called in callback need to be static too.
* 
* @param topic - the topic the message arrived on (const char[])
* @param payload - the message payload (byte array)
* @param length - the length of the message payload (unsigned int)
*/
void callback(char* topic, byte* payload, unsigned int length);

/**
 * @brief The Connection-class provides the interface
 * 
 */
class Communication {
   public:

    Communication(){};

    /**
    * @brief Construct a new Communication object
    * 
    */
    Communication(String Hostname);

    //==INTERFACE===================================
    /**
     * @brief Initializes the Hard- and Software for WLAN and MQTT-Connection
     * 
     */
    inline void init() {
        pNetwork.init();
        pMymqtt.init(&pClient, funcPointer);
    }

    /**
     * @brief This should be called regularly
     * to allow the client to process incoming messages
     * and maintain its connection to the server.
     * 
     * @return true - he client is still connected
     * @return false - the client is no longer connected
     */
    bool loop() {
        if (!pMymqtt.loop()) {
            pNetwork.connectToWiFi();
        } else {
            return true;
        }
        return pMymqtt.loop();
    }

    //=======NETWORK============
    // inline void connectToWiFi() {
    //     pNetwork.connectToWiFi();
    // }

    inline void printNetworkInfo() {
        pNetwork.printNetworkInfo();
    }

    //=======myMQTT============
    /**
     * @brief subsribes to MQTT topic on Server
     * 
     *  Checks if the Board is connected to a newtork and reconects if not
     *  Check if the client is connected to the server
     *  if not call connectToMQTT()
     * 
     * @param topic - the topic to subscribe to (const char[])
     * @return true -  sending the subscribe succeeded. The request completes asynchronously.
     * @return false - sending the subscribe failed, either connection lost, or message too large.
     */
    inline bool subscribe(const String topic) {
        pNetwork.connectToWiFi();
        return pMymqtt.subscribe(topic);
    }

    /**
     * @brief unsubsribes from MQTT topic on Server
     * 
     *  Checks if the Board is connected to a newtork and reconects if not
     *  Check if the client is connected to the server
     * 
     * @param topic - the topic to unsubscribe from (const char[])
     * @return true - sending the unsubscribe succeeded. The request completes asynchronously.
     * @return false - sending the unsubscribe failed, either connection lost, or message too large.
     */
    inline bool unsubscribe(const String topic) {
        pNetwork.connectToWiFi();
        return pMymqtt.unsubscribe(topic);
    }

    /**
     * @brief handles outgoing MQTT messages to Server
     * 
     * Checks if the Board is connected to a newtork and reconects if not
     * 
     * Beware though that the default packet size
     * supported by the PubSub client is 128 bytes.
     * You can increase this limit by editing the value
     * lof MQTT_MAX_PACKET_SIZE in PubSubClient.h
     * 
     * @param topic - the topic to publish to (const char[])
     * @param msg - the message to publish (const char[])
     * @return true - publish succed
     * @return false - publish failes
     */
    inline bool publishMessage(const String topic, const String msg) {
        pNetwork.connectToWiFi();
        return pMymqtt.publishMessage(topic, msg);
    }

    //=======myJSON/Buffer============
    //https://github.com/rlogiacco/CircularBuffer
    /**
     * @brief Retriev data from the Tail (oldest Element) of the Buffer
     * 
     * This operation is non destructiv and the element will NOT be removed from the buffer
     * Reading from an empty buffer is forbidden!!
     * @return myJSONStr - The Element at the Tail
     */

    
    inline bool checkForNewError()
    {
        if(errorMessageBuffer.empty())
        {
            return false;
        }
        return true;        
    }

    inline bool checkForNewAvailableBox()
    {
        if(sbAvailableMessageBuffer.empty())
        {
            return false;
        }
        return true;
    }

    inline bool checkForNewPositionBox()
    {
        if (sbPositionMessageBuffer.empty())
        {
            return false;
        }
        
        return true;
    }

    inline bool checkForNewStateBox()
    {
        if (sbStateMessageBuffer.empty())
        {
            return false;
        }
        
        return true;        
    }

    inline bool checkForNewHandshakeSBToSO()
    {
        if (handshakeMessageSBToSOBuffer.empty())
        {
            return false;
        }
        
        return true;        
    }
    
    
    private:
    String pHostname;
    WiFiClient pClient = WiFiClient();  ///< instance of WiFiClient
    Network pNetwork = Network(DEFAULT_WIFI_SSID,
                               DEFAULT_WIFI_PASSWORD);  ///< instance of Network
    myMQTT pMymqtt = myMQTT(pHostname,
                            DEFAULT_MQTT_BROKER_IP1,
                            DEFAULT_MQTT_BROKER_IP2,
                            DEFAULT_MQTT_BROKER_IP3,
                            DEFAULT_MQTT_BROKER_IP4,
                            DEFAULT_MQTT_PORT);  ///< instance of myMQTT

    //std::deque<std::shared_ptr<ErrorMessage>> errorMessageBuffer;

    void (*funcPointer)(char*, unsigned char*, unsigned int) = callback;  ///< functionpointer to callback-function
};
#endif