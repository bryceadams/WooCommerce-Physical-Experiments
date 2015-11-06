// This #include statement was automatically added by the Particle IDE.
#include "SparkFunMicroOLED/SparkFunMicroOLED.h"
#include "math.h"

// Declare a MicroOLED object
MicroOLED oled;

void setup()
{
    // Turn off onboard RGB LED
    RGB.control(true);
    RGB.color(0,0,0);
    
    // Initialize the OLED
    oled.begin();
    oled.clear(ALL);
    //oled.display();  // Display what's in the buffer (splashscreen)

    // Register 'sale' function
    Particle.function("sale", sale);
}

void loop()
{
    // Nothing to do
}

int sale(String amount)
{
    // Print 'Sale!' text
    int middleX = oled.getLCDWidth() / 2;
    oled.clear(PAGE);
    oled.setFontType(0);
    String title = "Sale!";
    oled.setCursor(middleX - (oled.getFontWidth() * (title.length()/2)), 10);
    oled.print(title);
    
    // Print amount text
    oled.setFontType(1);
    oled.setCursor(middleX - (oled.getFontWidth() * (amount.length()/2)), 25);
    oled.print(amount);
    
    // Display and clear after 10 seconds
    oled.display();
    delay(10000);
    oled.clear(ALL);

    return 1;
}