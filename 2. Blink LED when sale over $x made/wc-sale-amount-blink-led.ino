// -----------------------------------
// Controlling LEDs over the Internet
// -----------------------------------

// First, let's create our "shorthand" for the pins
int led1 = D0;

// And also the ledState and ledCameOn variables, as we
// need them in both the loop() function and in the
// ledToggle function()
char ledState = LOW;
long ledCameOn = 0;

void setup()
{
   // Configure pins
   pinMode(led1, OUTPUT);

   // Register 'sale' function
   Spark.function("sale",ledToggle);

   // Turn off led to begin with
   digitalWrite(led1, LOW);
}

void loop()
{
    // Turn off the light if it's been on for 30 seconds
    if(ledState == HIGH) {
        if(millis()-ledCameOn > 30000) {
            digitalWrite(led1, LOW);
            ledState = LOW;
        }
    }
}

int ledToggle(String amount) {
    // Convert total to a float
    float total = amount.toFloat();
    
    // Turn the light on for a sale
    // If greater than 50.00, blink a few times first
    if (total > 50.00) {
        blinkLights(5);
        digitalWrite(led1,HIGH);
        ledState = HIGH;
        ledCameOn = millis();
        return 1;
    // Otherwise, just turn the led on
    } else {
        digitalWrite(led1,HIGH);
        ledState = HIGH;
        ledCameOn = millis();
        return 0;
    }
}

void blinkLights(int count)
{
    for(int i=1; i<=count; i++) {
        digitalWrite(led1,HIGH);
        delay(500);
        digitalWrite(led1,LOW);
        delay(500);
    }
}