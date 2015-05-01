#include "arDev.h"
MPU6050 accelgyro(0x69);
static byte mymac[]={0x02,0x02,0x03,0x04,0x07,0x07};
static byte myip[]={10,16,18,37};
static byte gwip[]={10,16,18,250};
static byte mask[]={255,255,255,0};
static byte dnsip[]={10,200,1,11};
byte Ethernet::buffer[1000];
char website[]="www.lucadentella.it";
LCD lcd;


void setup ()
{
	Serial1.begin(57600);
	lcd.Setup();
	lcd.lcd_contrast(9);
	lcd.Clear();
	lcd.Update();
	int res=ether.begin(sizeof Ethernet::buffer,mymac,etherPin);
	if(res==0)Serial1.println("failed to access Ethernet Controller");
	else Serial1.println("\nEthernet controller initialised");
	//if(!ether.dhcpSetup())
	//	Serial.println("Failed to get configuration form DHCP");
	//else
	//	Serial.println("DHCP configuration done ");
	res=ether.staticSetup(myip,gwip,dnsip,mask);
	if(res==0)Serial1.println("Failed to set IP address");
	for(int i=0;i<4;i++){Serial1.print(ether.myip[i]);Serial1.print(".");}
	Serial1.println("");
	
	if(!ether.dnsLookup(website))
		Serial.println("DNS Failed");
	else
		Serial1.println("DNS resolution Done");
		
	for(int i=0;i<4;i++){Serial1.print(ether.hisip[i]);Serial1.print(".");}
	
	
}
void loop()
{
	ether.packetLoop(ether.packetReceive());
	
	
}
