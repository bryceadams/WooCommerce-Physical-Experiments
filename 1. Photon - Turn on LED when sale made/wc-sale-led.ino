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

int ledToggle(String command)
{
    // Turn the light on for a sale
    digitalWrite(led1,HIGH);
    ledState = HIGH;
    ledCameOn = millis();
    return 1;
}