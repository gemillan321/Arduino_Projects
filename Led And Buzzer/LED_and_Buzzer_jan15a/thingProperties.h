#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include <Arduino_NetworkConfigurator.h>
#include "configuratorAgents/agents/BLEAgent.h"
#include "configuratorAgents/agents/SerialAgent.h"
void onButtonChange();
void onBuzzerOnChange();
void onLEDLIGHTChange();

bool button;
bool buzzerOn;
bool lED_LIGHT;

KVStore kvStore;
BLEAgentClass BLEAgent;
SerialAgentClass SerialAgent;
WiFiConnectionHandler ArduinoIoTPreferredConnection; 
NetworkConfiguratorClass NetworkConfigurator(ArduinoIoTPreferredConnection);

void initProperties(){
  NetworkConfigurator.addAgent(BLEAgent);
  NetworkConfigurator.addAgent(SerialAgent);
  NetworkConfigurator.setStorage(kvStore);
  // For changing the default reset pin uncomment and set your preferred pin. Use DISABLE_PIN for disabling the reset procedure.
  //NetworkConfigurator.setReconfigurePin(your_pin);
  ArduinoCloud.setConfigurator(NetworkConfigurator);

  ArduinoCloud.addProperty(button, READWRITE, ON_CHANGE, onButtonChange);
  ArduinoCloud.addProperty(buzzerOn, READWRITE, ON_CHANGE, onBuzzerOnChange);
  ArduinoCloud.addProperty(lED_LIGHT, READWRITE, ON_CHANGE, onLEDLIGHTChange);

}
