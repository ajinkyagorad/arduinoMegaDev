
#include <MPU6050.h>
#include <Nokia2.h>
    bool isAccelGyroInit=false;
    bool isLcdInit=false;

//ethernet Helper: 



bool lcdInit( LCD &lcd)
{
	
	if(isLcdInit==false)	//makes sure lcd is initialised;//return 0 if it is initialised now
	{
		lcd.Setup();
		lcd.Clear();
		lcd.lcd_contrast(9);
		isLcdInit=true;
		return true;
	}
	else 
		return false;
}; 
void displayAccelGyro(MPU6050 &accelgyro,LCD &lcd)
{
	if(isAccelGyroInit==false)
	{
		 Wire.begin();
		 accelgyro.initialize();
		 isAccelGyroInit=true;
	}
	lcdInit(lcd);
	int ax,ay,az,wx,wy,wz;
	accelgyro.getMotion6(&ax,&ay,&az,&wx,&wy,&wz);
	lcd.Clear();
	const int i=10;
	lcd.setCursor(5,i); lcd.print("ax : ");lcd.print(ax);
	lcd.setCursor(5,i+10); lcd.print("ay : ");lcd.print(ay);
	lcd.setCursor(5,i+20); lcd.print("az : ");lcd.print(az);
	
	lcd.Update();
	//delay(10);
	
};


void test(void)
{
	Wire.begin();
	
	Serial.begin(9600);
	Serial.println("\nI2C Scanner");
	    while(true)
	    {
		    byte error, address;
		    int nDevices;
		    
		    Serial.println("Scanning...");
		    
		    nDevices = 0;
		    for(address = 1; address < 127; address++ )
		    {
			    // The i2c_scanner uses the return value of
			    // the Write.endTransmisstion to see if
			    // a device did acknowledge to the address.
			    Wire.beginTransmission(address);
			    error = Wire.endTransmission();
			    
			    if (error == 0)
			    {
				    Serial.print("I2C device found at address 0x");
				    if (address<16)
				    Serial.print("0");
				    Serial.print(address,HEX);
				    Serial.println("  !");
				    
				    nDevices++;
			    }
			    else if (error==4)
			    {
				    Serial.print("Unknow error at address 0x");
				    if (address<16)
				    Serial.print("0");
				    Serial.println(address,HEX);
			    }
		    }
		    if (nDevices == 0)
		    Serial.println("No I2C devices found\n");
		    else
		    Serial.println("done\n");
		    
		    delay(5000);           // wait 5 seconds for next scan
	    }

	   
}