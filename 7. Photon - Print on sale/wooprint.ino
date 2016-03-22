/*************************************************************************
  This is an Arduino library for the Adafruit Thermal Printer.
  Pick one up at --> http://www.adafruit.com/products/597
  These printers use TTL serial to communicate, 2 pins are required.

  Adafruit invests time and resources providing this open source code.
  Please support Adafruit and open-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution.
 *************************************************************************/

#include "Adafruit_Thermal.h"

#if !defined (SPARK)
// If you're using Arduino 1.0 uncomment the next line:
#include "SoftwareSerial.h"
// If you're using Arduino 23 or earlier, uncomment the next line:
//#include "NewSoftSerial.h"
#include <avr/pgmspace.h>
#endif

#include "Adafruit_Thermal.h"
#include "woologo.h"

#if defined (SPARK)
int printer_RX_Pin = 0;  // Serial1 Rx pin on Spark to the green wire on printer
int printer_TX_Pin = 0;  // Serial1 Tx pin on Spark to the yellow wire on printer
#else
int printer_RX_Pin = 5;  // This is the green wire
int printer_TX_Pin = 6;  // This is the yellow wire
#endif

Adafruit_Thermal printer(printer_RX_Pin, printer_TX_Pin);

void setup(){
  Serial.begin(9600);
  
#if defined (SPARK)
  pinMode(D2, OUTPUT); digitalWrite(D2, LOW); // To also work w/IoTP printer
#else
  pinMode(7, OUTPUT); digitalWrite(7, LOW); // To also work w/IoTP printer
#endif

  printer.begin();
  // The following function calls are in setup(), but do not need to be.
  // Use them anywhere!  They're just here so they're run only one time
  // and not printed over and over.
  // Some functions will feed a line when called to 'solidify' setting.
  // This is normal.
  
  Particle.function("print", printTest);
  Particle.function("sale", wooPrint);
}

void loop() {
}

int wooPrint(String command) {
    int loc1 = 0;
    int loc2 = 0;
    int loc3 = 0;
    int loc4 = 0;

    String orderid;
    String total;
    String item1;
    String name;
    
    loc1 = command.indexOf(",");
    orderid = command.substring(0,loc1);

    loc2 = command.indexOf(",",loc1+1);
    total = command.substring(loc1+1,loc2);
    
    loc3 = command.indexOf(",",loc2+1);
    item1 = command.substring(loc2+1,loc3);
    
    loc4 = command.indexOf(",",loc3+1);
    name = command.substring(loc3+1,loc4);
    
    
    printer.justify('C');
    printer.setSize('L');
    printer.println("New WooCommerce Sale for " + total + "!");
    
    printer.justify('L');
    printer.setSize('S');
    printer.println("Nice! You just made a new sale.");
    
    printer.setSize('M');
    
    printer.println("Order Number: #" + orderid);
    
    printer.println("Item: " + item1);
    
    printer.println("Customer: " + name);
    
    printer.feed(1);
    
    printer.justify('C');
    printer.setSize('L');
    printer.println("Love...");
    
    printer.feed(1);
    
    printer.printBitmap(woologo_width, woologo_height, woologo_data);
    
    printer.feed(2);

    printer.sleep();      // Tell printer to sleep
    printer.wake();       // MUST call wake() before printing again, even if reset
    printer.setDefault(); // Restore printer to defaults
    
    return 1;
}

int printTest(String command) {
    // Test inverse on & off
  printer.inverseOn();
  printer.println(command);
  printer.inverseOff();
  
  printer.feed(1);

  printer.sleep();      // Tell printer to sleep
  printer.wake();       // MUST call wake() before printing again, even if reset
  printer.setDefault(); // Restore printer to defaults
  
  return 1;
}