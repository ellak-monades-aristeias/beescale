// Include the GSM library
#include <GSM.h>
#include <Hx711.h>



// PIN Number
#define PINNUMBER ""

// initialize the library instance
GSM gsmAccess;
GSMVoiceCall vcs;
GSM_SMS sms;
Hx711 scale(A4, A5);

// Array to hold the number for the incoming call
char numtel[20];

void setup()
{
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);

  Serial.println("kaneis klhsh pairneis mnm");

  // connection state
  boolean notConnected = true;

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
 
 Serial.print("ta kg einai: ");       
 Serial.print(scale.getGram());
 
 // send the message
 sms.beginSMS(numtel);
 sms.print("ta kg einai: ");       
 sms.println(scale.getGram());
 sms.endSMS();
  Serial.println("\n to minima stalthike!\n");
//---------------
  vcs.hangCall();
      break;
  }
  delay(1000);
}
