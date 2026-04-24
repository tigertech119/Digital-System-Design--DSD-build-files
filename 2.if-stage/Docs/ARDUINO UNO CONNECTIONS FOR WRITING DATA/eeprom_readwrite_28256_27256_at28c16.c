// 28256 / 27256 / AT28C16 EEPROM write/read example (A0-A3 only)
const int CE = A0;
const int OE = A1;
const int WE = A2;

int addressPins[4] = {2,3,4,5};          // A0-A3
int dataPins[8] = {6,7,8,9,10,11,12,13}; // D0-D7

void setup() {
  Serial.begin(9600);
  
  pinMode(CE, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(WE, OUTPUT);

  for(int i=0;i<4;i++) pinMode(addressPins[i], OUTPUT);
  for(int i=0;i<8;i++) pinMode(dataPins[i], OUTPUT);

  digitalWrite(CE, HIGH);
  digitalWrite(OE, HIGH);
  digitalWrite(WE, HIGH);
}

void writeEEPROM(byte addr, byte data) {
  // Set address
  for(int i=0;i<4;i++) digitalWrite(addressPins[i], (addr>>i)&1);
  
  // Set data
  for(int i=0;i<8;i++) digitalWrite(dataPins[i], (data>>i)&1);
  
  // Write pulse
  digitalWrite(CE, LOW);
  digitalWrite(OE, HIGH);
  digitalWrite(WE, LOW);
  delayMicroseconds(1);
  digitalWrite(WE, HIGH);
  delay(10);   // EEPROM internal write time
  digitalWrite(CE, HIGH);
}

byte readEEPROM(byte addr) {
  byte data = 0;
  
  // Set address
  for(int i=0;i<4;i++) digitalWrite(addressPins[i], (addr>>i)&1);
  
  // Set data pins as input
  for(int i=0;i<8;i++) pinMode(dataPins[i], INPUT);
  
  digitalWrite(CE, LOW);
  digitalWrite(OE, LOW);
  digitalWrite(WE, HIGH);
  delayMicroseconds(1);

  // Read data
  for(int i=0;i<8;i++) {
    if(digitalRead(dataPins[i])) data |= (1<<i);
  }

  digitalWrite(CE, HIGH);
  digitalWrite(OE, HIGH);

  // Set data pins back to output
  for(int i=0;i<8;i++) pinMode(dataPins[i], OUTPUT);

  return data;
}

void loop() {
  byte testData[16] = {
    0xCC,0xAA,0x55,0xF0,
    0x0F,0x96,0x69,0xFF,
    0x00,0x81,0x42,0x24,
    0x18,0xC3,0x3C,0x87
  };
  
  // Write 16-byte test table
  for(byte addr=0; addr<16; addr++) {
    writeEEPROM(addr, testData[addr]);
  }

  // Read back and print
  Serial.println("Reading EEPROM:");
  for(byte addr=0; addr<16; addr++) {
    byte val = readEEPROM(addr);
    Serial.print("Addr 0x");
    Serial.print(addr, HEX);
    Serial.print(" = 0x");
    Serial.println(val, HEX);
  }

  while(1); // stop after one run
}