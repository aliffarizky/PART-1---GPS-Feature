#include <TinyGPS++.h> //Using TinyGPSplus library to parse the NMEA output
#include <SoftwareSerial.h> 
static const int RXPin = 3, TXPin = 4; //set Commmunication pin 
static const uint32_t GPSBaud = 9600; //set modules baudrate

// The TinyGPS++ object
TinyGPSPlus gps; //object to pull gps value
TinyGPSCustom snr(gps, "GPGSV", 7); //custom object to pull SNR (Signal to Noise Ratio/GPS Strength) from GPSV NMEA  

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(9600); //Serial begin
  ss.begin(GPSBaud); //begin modules with baudrate
}

void loop()
{
  while (ss.available() > 0)
    if (gps.encode(ss.read())) //encode module response
      displayInfo(); //function to print the info

  if (millis() > 5000 && gps.charsProcessed() < 10) //timeout
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6); //print latitude
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6); //print longitude
    Serial.println();
    Serial.print(F("GPS Strength: ")); Serial.print(snr.value()); //print gps strength (SNR) 
    
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.println();
}
