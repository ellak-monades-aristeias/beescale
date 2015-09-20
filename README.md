Απομακρισμένη Ζυγαριά μελισσιού - Beescale




Eισαγωγή
Παρουσίαση των επιμέρους στοιχείων
Αισθητήρας Θερμοκρασίας
Αισθητήρας Yγρασίας
Αισθητήρας μέτρησης μάζας (Load cell)
GSM Shield
Κώδικας
Βιβλιογραφία
Παράρτημα


Εισαγωγή

O arduino ειναι μια ανοιχτού-κώδικα πλατφόρμα πρωτοτυποποίσης, βασισμένη σε ένα εύκολο στη χρήση λογισμικό(software) και υλισμικό(hardware). Οι πλακέτες Arduino έχουν την ικανότητα να δέχονται εισόδους -το φώς σε εναν αισθητήρα, το δάχτυλο σε ενα διακόπτη, ή ενα μήνυμα στο Twitter - και να το μετατρέψουν σε μια έξοδο - να ενεργοποιήσουν εναν κινητήρα, να ανάψουν ενα LED, να δημοσιεύσουν κατι στο ίντερνετ. Όλα αυτά καθορίζονται απο ένα σετ οδηγιών που έχουν προγραμματιστεί μέσω του λογισμικού του Arduino (IDE).

Αν δεν έχετε προηγούμενη εμπειρία με τον Arduino ή άλλον μικροεπεξεργαστή και κυκλώματα, θα ήταν προτιμότερο να δείτε απλούστερα παραδείγματα πριν επιχειρήσετε να φτιάξετε μόνοι σας την ζυγαριά.

Για το εγχείρημα της ζυγαριάς του μελλισιού (beescale) θα χρησιμοποιήσουμε τον Arduino Uno, εναν αισθητήρα θερμοκρασίας, εναν αισθητήρα υγρασίας, έναν αισθητήρα μέτρησης της μάζας και ενα πρόσθετο gsm shield ωστε να λαμβάνουμε τις μετρήσεις μεσω δικτύου κινητής τηλεφωνίας. Για την μέτρηση της μάζας απαιτείται η ενίσχυση του σήματος του αισθητήρα μάζας, οπότε θα χρησιμοποιήσουμε και ένα τυπωμένο κύκλωμα σε πλακέτα (printed circuit board - PCB) με τον HX711 ενισχυτή.


Arduino Uno        Μικροεπεξεργαστής
Dallas DS18S20     Αισθητήρας Θερμοκρασίας
            Αισθητήρας Υγρασίας
Load cell 100 kg    Αισθητήρας μέτρησης μάζας
HX711            Ενισχυτής
Adafruit Gsm Shield    Πρόσθετο PCB για σύνδεση στο δίκτυο κινητής τηλεφωνίας


Πιο συγκεκριμένα, oποιαδήποτε στιγμή ο μελισσοκόμος θέλει να ενημερωθεί για τις συνθήκες που επικρατούν στην κυψέλη του, θα λαμβάνει ένα μήνυμα στο κινητό του τηλέφωνο με τις τρέχουσες μετρήσεις της ζυγαριάς, η οποία θα τίθεται αυτόματα σε λειτουργία, καθώς και τις ενδείξεις των αισθητήρων. Επιπροσθέτως, ο μικροεπεξεργαστής θα δημιουργεί ένα αρχείο μετρήσεων, έτσι ώστε να είναι δυνατή η περαίτερω επεξεργασία τους με σκοπό την μακροπρόθεσμη εξαγωγήσυμπερασμάτων για τη βελτίωση της παραγωγής.

Σε αυτον τον οδηγό θα αναλύσουμε βήμα βήμα πως μπορείτε να κατασκευάσετε ένα προτότυπο beescale.









Παρουσίαση των επιμέρους στοιχείων
Αισθητήρας Θερμοκρασίας
Ο αισθητήρας ,έχει 3 Pin , GND, DQ και VDD. Ο αισθητηρας μπορεί να τροφοδοτηθεί με τασή μεταξυ 3.0V και 5.5 V. Το GND συνδέεται με τη γείωση και το VDD με +5V απο τον Arduino. Ο DS1820 έχει τη δυνατότητα να τροφοδοτηθεί απο το Pin που μεταφερει δεδομένα. Οπότε θα συνδέσουμε με τη γείωση τα δυο PIN , GND και VDD, το μεσαίο Pin θα τον συνδέσουμε με το Pin 2 και μεσω μιας αντίστασης 4.7 kΩ με τα +5V του Arduino.








O αισθητήρας DS18S20.



Συνδεσμολογία του DS18S20



Ο κώδικας που θα τρέξουμε για να λάβουμε τιμές θερμοκρασίας είναι ο εξής

#include <OneWire.h> // κανουμε include τη βιβλιοθηκη Onewire
#include <DallasTemperature.h> // κανουμε include τη βιβλιοθηκη DallasTemperature
 
// Ο ακροδέκτης για τα δεδομένα ειναι συνδεδεμένο στο pin2
#define ONE_WIRE_BUS 2
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
 
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();
}
 
 
void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print(" Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");

  Serial.print("Temperature for Device 1 is: ");
  Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"? 
    // You can have more than one IC on the same bus. 
    // 0 refers to the first IC on the wire
 


}





Όταν  έχουμε έτοιμη τη ζυγαριά, δεν θα θέλουμε να ξέρουμε τι ζυγίζει συνεχώς, και επίσης θέλουμε η μπαταρία να μην καταναλωθεί σε μια μέρα. Οπότε θα χρησιμοποιήσουμε τα Sleeping modes του atmega για να μειώσουμε την κατανάλωση ρεύματος. Σε αυτό θα μας βοηθήσει η βιβλιοθήκη LowPower.h. Ο μέγιστος χρόνος που μπορούμε να επιβάλουμε sleeping mode είναι 8s. Έστω εμείς στο παράδειγμά μας οτι θέλουμε να παίρνουμε 1 μέτρηση ανα λεπτό. το ένα λεπτο είναι 60 sec /8 s = 7.5, άρα αν του πουμε να παίρνει μία μέτρηση ανα 8 φορές που ξυπνάει, τότε θα έχουμε μια μέτρη ανα περιπου 1 λεπτό.

#include <OneWire.h>
#include <DallasTemperature.h>
#include <LowPower.h> // include LowPower library
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
 int wait=1;// μεταβλητή για να μετράει πόσες φορές ξυπνάει απο sleeping mode
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
  // Start up the library
  sensors.begin();
}
 
void loop(void) {
Serial.print("wait =");// debugging
Serial.println(wait); //debugging
  if(wait>=8){
     // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print(" Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  Serial.print("Temperature for Device 1 is: ");
  Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"? 
    // You can have more than one IC on the same bus. 
    // 0 refers to the first IC on the wire
    wait=0;// αρχικοποιεί την μεταβλητή wait
    }            
    delay(100);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);      
  wait++;// αυξάνει κατα 1 την μεταβλητή wait
}
