#include <NMEAGPS.h>
#include <GPSport.h>
#include "thingProperties.h"

NMEAGPS gps;
gps_fix fix;

void setup()
{
  p_ArduinoStatus = false;
  p_GPSFound = false;
  p_LookingForGPS = false;
  
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  gpsPort.begin(9600);
  
  p_ArduinoStatus = true;
}

void loop()
{
  ArduinoCloud.update();
  
  while (gps.available(gpsPort))
  {
    fix = gps.read();

    if (fix.valid.location)
    {
      p_GPSFound = true;
      p_LookingForGPS = false;
      p_GPSCoords = {fix.latitude(), fix.longitude()};
    }
    else
    {
      p_LookingForGPS = true;
    }
  }
  else
  {
    // GPS Not Found.
  }
}
