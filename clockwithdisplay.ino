// Include the libraries
#include "uRTCLib.h"
#include <TM1637Display.h>

// Define the connections pins
#define CLK 3
#define DIO 4

// Create rtc and display object
  uRTCLib rtc(0x68);
  TM1637Display display = TM1637Display(CLK, DIO);

void setup() {
	// Begin serial communication
	Serial.begin(9600);

	 
		Serial.println("Rtc time:");
    
		#ifdef ARDUINO_ARCH_ESP8266
		URTCLIB_WIRE.begin(0, 2); // D3 and D4 on ESP8266
	#else
		URTCLIB_WIRE.begin();
	#endif

	rtc.set(0, 17, 22, 2, 3, 5, 24);
	//  RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
	

	// Set the display brightness (0= lowest, 7=highest)
	display.setBrightness(2);
	

}

void loop() {


  //Here the rtc displays the current time (according to what was set) in the serial monitor.
	rtc.refresh();
  Serial.print(rtc.hour());
  Serial.print(':');
  Serial.println(rtc.minute());
  
 

	//Here the TM1637 displays the time according to the one printed by the rtc as above.
  display.showNumberDec(rtc.hour() *100 + rtc.minute(), false); 
delay(1000);
  

  //This is just a simple code for making the colon in the TM1637 blink 
 uint8_t segto;
  int value = 1244;
  segto = 0x80 | display.encodeDigit((value / 100)%10);
  display.setSegments(&segto, 1, 1);
  delay(800); //You can adjust the interval in which the colon blinks upon your liking
}