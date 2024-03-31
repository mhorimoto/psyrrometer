#include <DS18B20.h>

DS18B20 ds(10);
uint8_t address[8];
char    text[40];

void setup() {
  int i,nd;
  Serial.begin(115200);
  Serial.print("Number of Devices: ");
  nd = ds.getNumberOfDevices();
  Serial.println(nd);
  for(i=0;i<nd;i++) {
    ds.getAddress(address);
    Serial.print("Address:");
    sprintf(text,"%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X",
	    address[0],address[1],address[2],address[3],
	    address[4],address[5],address[6],address[7]);
    Serial.println(text);
    switch (ds.getFamilyCode()) {
      case MODEL_DS18S20:
        Serial.println("Model: DS18S20/DS1820");
        break;
      case MODEL_DS1822:
        Serial.println("Model: DS1822");
        break;
      case MODEL_DS18B20:
        Serial.println("Model: DS18B20");
        break;
      default:
        Serial.println("Unrecognized Device");
        break;
    }
    Serial.print("Resolution: ");
    Serial.println(ds.getResolution());
    ds.selectNext();
  }
}

void loop() {
  float tp;
  int   rp,mp;
  while (ds.selectNext()) {
    ds.getAddress(address);
    tp = ds.getTempC();
    rp = int(tp);
    mp = int((tp-rp)*100);
    sprintf(text,"%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X,%d.%02d",
	    address[0],address[1],address[2],address[3],
	    address[4],address[5],address[6],address[7],rp,mp);
    Serial.println(text);
  }
  delay(10000); // 10sec interval
}
