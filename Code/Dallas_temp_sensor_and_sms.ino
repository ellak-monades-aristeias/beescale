// Include the GSM library
#include <GSM.h>
//Libraries for temperature
#include <OneWire.h>
#include <DallasTemperature.h>
 
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// PIN Number
#define PINNUMBER ""

 
// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
// initialize the library instance

GSM gsmAccess;
GSMVoiceCall vcs;
GSM_SMS sms;
const int sensorPin = A2;
// Array to hold the number for the incoming call
char numtel[20];
float tmp = gettemp();
//float gettemp(); 


void setup()
{
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);

  Serial.println("kaneis klhsh pairneis mnm");
 
  // connection state
  boolean notConnected = true;
  sensors.begin();

  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while (notConnected)
  {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY)
      notConnected = false;
    else
    {
      Serial.println("Not connected");
     
      delay(1000);
    }
  }

  // This makes sure the modem correctly reports incoming events
  vcs.hangCall();
  Serial.println("GSM ok");
  Serial.println("pare thl");
}

void loop()
{
  // Check the status of the voice call
  switch (vcs.getvoiceCallStatus())
  {
    case IDLE_CALL: // Nothing is happening

      break;

    case RECEIVINGCALL: // Yes! Someone is calling us

      Serial.println("driiin driiin");

      // Retrieve the calling number
      vcs.retrieveCallingNumber(numtel, 20);

      // Print the calling number
      Serial.print("arithmos:");
      Serial.println(numtel);

      // Answer the call, establish the call
      vcs.answerCall();

//----------------
       // sms text
  Serial.print("h thermokrasia einai: ");
  Serial.print(tmp);
 
  // send the message
  sms.beginSMS(numtel);
  sms.print(tmp);
  sms.endSMS();
  Serial.println("\nto minima stalthike!\n");
//---------------
  vcs.hangCall();
      break;
  }
  delay(1000);
}

float gettemp()
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  //Serial.print(" Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  //Serial.print("Temperature for Device 1 is: ");
  //Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"?
   return float (sensors.getTempCByIndex(0));
    // You can have more than one IC on the same bus.
    // 0 refers to the first IC on the wire
 delay (10000);
}



