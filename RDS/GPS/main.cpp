#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <cstddef>
#include <unistd.h>

/*Ownlibraries*/
#include "UBX_Protocol_Constants.hpp"
#include "Neo7.hpp"

int main()
{
  /* VARIABLES */
  char GPS_data;
  /* Hvis default values skulle laves char def_1[] = "0";
  char def_2[] = "N/A";

  char* d1 = def_1;
  char* d2 = def_2; */

  float Long = 0.0, Lat = 0.0;

  int serial_port;
  char NS[1];
  char EW[1];

  GPS NEO1;

  /* OPEN UART */
  serial_port = NEO1.openUART(serial_port);

  printf("Serial port is open! %d \n", serial_port);

  /* CONFIGURATION */

  /*NMEA Config*/
  NEO1.config(serial_port, UBX_protocol::NMEA_CFG, UBX_protocol::NMEA_CFG_Length); // disable SBAS QZSS GLONASS BeiDou Galileo

  /*Update Rate*/
  NEO1.config(serial_port, UBX_protocol::RATE, UBX_protocol::RATE_Length); // Measurement frequency: 10 hz, navigation frequency 10 hz

  /*NMEA messages*/
  NEO1.config(serial_port, UBX_protocol::GLL, UBX_protocol::GP_Length); // disable GPGLL
  NEO1.config(serial_port, UBX_protocol::GSA, UBX_protocol::GP_Length); // disable GSA
  NEO1.config(serial_port, UBX_protocol::GSV, UBX_protocol::GP_Length); // disable GPGSV
  NEO1.config(serial_port, UBX_protocol::RMC, UBX_protocol::GP_Length); // disable RMC
  NEO1.config(serial_port, UBX_protocol::VTG, UBX_protocol::GP_Length); // disable VTG
  printf("Configuration is done! \n");

  /* START LOGGING*/
  // NEO1.startLogging(); //Der er 2 måder logger alt eller logger kun når fil bliver kaldt. Det nemmeste er nok alt for at slippe for en klasse hovedpine for alt data.
  printf("Logging initialize! \n");

  printf("STARTING LOOP\n");
  /* STARTING LOOP*/
  while (1)
  {

    NEO1.readGPS(serial_port, GPS_data); // reads NMEA message

    Long = NEO1.getLongitude(); // returns longitude
    Lat = NEO1.getLatitude();   // returns latitude
    NEO1.getNorthSouth(NS);     // returns either a north pole or south pole
    NEO1.getEastWest(EW);       // returns either a East pole or West pole

    NEO1.convertData(Long, Lat, NS, EW); // converts to decimal degrees format

    usleep(1000000); // delay 1 second
  }

  return 0;
}