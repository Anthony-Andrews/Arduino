// LED on GPIO2
int ledPin = 2;
 
void setup()
{
    // Set LED as output
    pinMode(ledPin, OUTPUT);
    
    // Serial monitor setup
    Serial.begin(115200);
}
 
void loop()
{
    Serial.print("Hello");
    digitalWrite(ledPin, HIGH);
    
    delay(5);
    
    Serial.println(" world!");
    digitalWrite(ledPin, LOW);
    
    delay(5);
}
