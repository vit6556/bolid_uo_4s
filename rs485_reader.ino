#include <SoftwareSerial.h>

SoftwareSerial rsSerial(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  rsSerial.begin(9600);

  Serial.write("Отправлено: ");
  byte command[] = {0x03, 0x06, 0x00, 0x11, 0xBA, 0xBA, 0x8D};
  for (int i = 0; i < sizeof(command); i++) {
    rsSerial.write(command[i]);
    Serial.write(command[i]);
    
  }
  rsSerial.println();
  Serial.println();
}

void loop() {
  if (rsSerial.available() > 0) {
    byte receivedCommand[256];
    
    byte startByte = rsSerial.read();
    byte lengthByte = rsSerial.read();
    receivedCommand[0] = startByte;
    receivedCommand[1] = lengthByte;
    for (int i = 2; i <= lengthByte; i++) {
      if (rsSerial.available() > 0) {
        receivedCommand[i] = rsSerial.read();
      }
    }

    Serial.write("Получено: ");
    for (int i = 0; i <= lengthByte; i++) {
      Serial.print(receivedCommand[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}
