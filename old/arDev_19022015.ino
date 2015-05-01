#ifndef arDev
#define arDev
#endif
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Ethercard/EtherCard.h"
#define etherPin 28
#include <stdlib.h>
// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h

#include "Wire.h"
#include <Nokia2.h>
#include <NokiaChars.h>

MPU6050 accelgyro(0x69);
int16_t ax, ay, az;
int16_t gx, gy, gz;
#include  "helper.h"
#include <tinyFAT.h>
LCD lcd;

static byte myip[]={10,16,18,33};
static byte gwip[]={10,16,18,250};
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
byte Ethernet::buffer[400];
BufferFiller bfill;
static word homePage()
{
	int ax,ay,az,gx,gy,gz,mx,my,mz;
	accelgyro.getMotion9(&ax,&ay,&az,&gx,&gy,&gz,&mx,&my,&mz);
	bfill=ether.tcpOffset();
	bfill.emit_p(
	"HTTP/1.0 200 OK\r\n"
	"Content-Type: text/html\r\n"
	"Pragma: no-cache\r\n"
	"\r\n"
	"<meta http-equiv='refresh' content='0'/>"
	"<title>arDev Server</title>"
	"<h2>$D\r\n$D\r\n$D\r\n$D\r\n$D\r\n$D\r\n$D\r\n$D\r\n$D\r\n</h2>"
	,ax,ay,az,gx,gy,gz,mx,my,mz);
	return bfill.position();
}
void setup() {

 lcd.Setup();
 lcd.lcd_contrast(10);
 lcd.Clear();
 lcd.Update();
 Wire.begin();
accelgyro.initialize();
ether.begin(sizeof Ethernet::buffer,mymac,etherPin)
ether.staticSetup(myip);

	
}
int nReq=0;
void loop() {
	lcd.setCursor(5, 5);
	lcd.println("Carrying out\n data handling .. \n ");
	lcd.println("\nexecuted loop ");
	lcd.print(nReq);
	lcd.print(" times");
	lcd.Update();
	word len =ether.packetReceive();
	word pos =ether.packetLoop(len);
	if(pos)ether.httpServerReply(homePage());
	nReq++;
}
