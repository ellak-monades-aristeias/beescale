//using this library https://github.com/bogde/HX711
//for a known zero factor to remove the need to tare the scale. Useful in permanent scale projects.
//read this https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide
//and this example SparkFun_HX711_Calibration by sarahalmutlaq
#include "HX711.h"

// HX711.DOUT	- pin #A4
// HX711.PD_SCK	- pin #A3

HX711 scale(A4, A3);		// parameter "gain" is ommited; the default value 128 is used by the library

void setup() {
  Serial.begin(38400);
  Serial.println("HX711 Demo");

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());			// print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));  	// print the average of 20 readings from the ADC

// zero factor from SparkFun_HX711_Calibration by sarahalmutlaq
 //long zero_factor = scale.read_average(); //Get a baseline reading
  long zero_factor = 8510214;
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
 
  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);	// print the average of 5 readings from the ADC minus tare weight (not set) divided 
						// by the SCALE parameter (not set yet)  
						
						

  scale.set_scale(2280.f);          // this value is obtained by calibrating the scale with known weights; see the README for details
 //scale.tare();				        // reset the scale to 0
	scale.set_offset(zero_factor); //Zero out the scale using a previously known zero_factor for a permanent weight on the scale
  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided 
						// by the SCALE parameter set with set_scale

  Serial.println("Readings:");
}

void loop() {
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 1);

  scale.power_down();			        // put the ADC in sleep mode
  delay(5000);
  scale.power_up();
}
