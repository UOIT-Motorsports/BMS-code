#include <Serial_CAN_Module.h>
#include <SoftwareSerial.h>
Serial_CAN can;
#define can_tx  2           // tx of serial can module connect to D2
#define can_rx  3           // rx of serial can module connect to D3

byte ID;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);      // debugging
  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);
  can.begin(can_tx, can_rx, 115200);      // tx, rx
}

void loop() {
temp();
delay(10);
VMIN();
delay(10);
VMAX();
delay(10);
VPACK();
delay(10);
CURRENT();
delay(100);
temp1();
delay(10);
VMIN1();
delay(10);
VMAX1();
delay(10);
VPACK1();
delay(10);
CURRENT1();
delay(100);
temp2();
delay(10);
VMIN2();
delay(10);
VMAX2();
delay(10);
VPACK2();
delay(10);
CURRENT2();
delay(100);
}

void temp(){
  // put your main code here, to run repeatedly:
  byte message[] = {0xAA, 0x1B, 0x3F, 0x1B}; // address, function code, CRC, CRC
  byte snd [11];
  byte temporarray [11];
  byte tmps[8];
  
  float character;
  int count = 0;

Serial.println("\nBMS1:");
ID=0xAA;

Serial.println("TEMPS");
  Serial1.write(message, sizeof(message));
  //Requests

  while (Serial1.available()) {
    character = Serial1.read();
    float val = character;
    if (count < 12) {
      snd[count] = val;
      count++;
    } else {
      count = 0;
    }
  }
  //Prints BMS output into Byte Array

  Serial.println("\n");
  for (int i = 0; i < 11; i++) {
    Serial.print(snd[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
  //debugging reads byte message to user

  for (int i = 0; i < 11; i++) {
    if (i<3){
      temporarray[i]=snd[i];
    }else if ((i>=3)&&(i<9)){
    temporarray[i]=snd[i+1];
    i++;
    temporarray[i]=snd[i-1];
    }else{
      temporarray[i]=snd[i];
    }
  }

  tmps[0]=ID;
  tmps[1]=temporarray[1];
  tmps[2]=temporarray[5];
  tmps[3]=temporarray[6];
  tmps[4]=temporarray[7];
  tmps[5]=temporarray[8];
  tmps[6]=temporarray[9];
  tmps[7]=temporarray[10];
  //Sets the tmps array to 8 byte array: ID,Command,temp1,temp1,temp2,temp2,CRC,CRC

  Serial.println("\n");
  for (int i = 0; i < 11; i++) {
    Serial.print(temporarray[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
  
Serial.println("\n");
  for (int i = 0; i < 8; i++) {
    Serial.print(tmps[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
//debugging reads converted strings
  

  can.send(0x55, 0, 0, 8, tmps);   // SEND TO ID:0X55
  delay(100);
  //Sends Byte array though can, woohoo
}

void VMIN(){
  byte message[] = {0xAA,0x17,0x3F,0x1E}; // address, function code, CRC, CRC
  byte snd [6];
   float character;
  int count = 0;

Serial.println("VMIN");
  
  Serial1.write(message, sizeof(message));
  //Requests

  while (Serial1.available()) {
    character = Serial1.read();
    float val = character;
    if (count < 7) {
      snd[count] = val;
      count++;
    } else {
      count = 0;
    }
  }
  //Prints BMS output into Byte Array

  Serial.println("\n");
  for (int i = 0; i < 6; i++) {
    Serial.print(snd[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
  //debugging reads byte message to user

  can.send(0x55, 0, 0, 6, snd);   // SEND TO ID:0X55
  delay(100);
  //Sends Byte array though can, woohoo
}

void VMAX(){
   byte message[] = {0xAA,0x16,0xFE,0xDE}; // address, function code, CRC, CRC
  byte snd [6];
   float character;
  int count = 0;

  Serial.println("vMAX");
  Serial1.write(message, sizeof(message));
  //Requests

  while (Serial1.available()) {
    character = Serial1.read();
    float val = character;
    if (count < 7) {
      snd[count] = val;
      count++;
    } else {
      count = 0;
    }
  }
  //Prints BMS output into Byte Array

  Serial.println("\n");
  for (int i = 0; i < 6; i++) {
    Serial.print(snd[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
  //debugging reads byte message to user

  can.send(0x55, 0, 0, 6, snd);   // SEND TO ID:0X55
  //delay(100);
  //Sends Byte array though can, woohoo
}

void VPACK(){
   byte message[] = {0xAA,0x14,0x7F,0x1F}; // address, function code, CRC, CRC
  byte snd [8];
   float character;
  int count = 0;

  Serial.println("vPack");
  Serial1.write(message, sizeof(message));
  //Requests

  while (Serial1.available()) {
    character = Serial1.read();
    float val = character;
    if (count < 9) {
      snd[count] = val;
      count++;
    } else {
      count = 0;
    }
  }
  //Prints BMS output into Byte Array

  Serial.println("\n");
  for (int i = 0; i < 8; i++) {
    Serial.print(snd[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
  //debugging reads byte message to user

  can.send(0x55, 0, 0, 6, snd);   // SEND TO ID:0X55
  delay(100);
  //Sends Byte array though can, woohoo
}

void CURRENT(){
   byte message[] = {0xAA,0x15,0xBE,0xDF}; // address, function code, CRC, CRC
  byte snd [8];
   float character;
  int count = 0;

  Serial.println("CURRENT");
  Serial1.write(message, sizeof(message));
  //Requests

  while (Serial1.available()) {
    character = Serial1.read();
    float val = character;
    if (count < 9) {
      snd[count] = val;
      count++;
    } else {
      count = 0;
    }
  }
  //Prints BMS output into Byte Array

  Serial.println("\n");
  for (int i = 0; i < 8; i++) {
    Serial.print(snd[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
  //debugging reads byte message to user

  can.send(0x55, 0, 0, 8, snd);   // SEND TO ID:0X55
  delay(100);
  //Sends Byte array though can, woohoo
}
//******************************************************************************************************************
void temp1(){
  // put your main code here, to run repeatedly:
  byte message[] = {0xAA, 0x1B, 0x3F, 0x1B}; // address, function code, CRC, CRC
  byte snd [11];
  byte temporarray [11];
  byte tmps[8];
  
  float character;
  int count = 0;

Serial.println("\nBMS2:");
ID=0xBB;

Serial.println("TEMPS");
  Serial2.write(message, sizeof(message));
  //Requests

  while (Serial2.available()) {
    character = Serial2.read();
    float val = character;
    if (count < 12) {
      snd[count] = val;
      count++;
    } else {
      count = 0;
    }
  }
  //Prints BMS output into Byte Array

  Serial.println("\n");
  for (int i = 0; i < 11; i++) {
    Serial.print(snd[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
  //debugging reads byte message to user

  for (int i = 0; i < 11; i++) {
    if (i<3){
      temporarray[i]=snd[i];
    }else if ((i>=3)&&(i<9)){
    temporarray[i]=snd[i+1];
    i++;
    temporarray[i]=snd[i-1];
    }else{
      temporarray[i]=snd[i];
    }
  }

  tmps[0]=ID;
  tmps[1]=temporarray[1];
  tmps[2]=temporarray[5];
  tmps[3]=temporarray[6];
  tmps[4]=temporarray[7];
  tmps[5]=temporarray[8];
  tmps[6]=temporarray[9];
  tmps[7]=temporarray[10];
  //Sets the tmps array to 8 byte array: ID,Command,temp1,temp1,temp2,temp2,CRC,CRC

  Serial.println("\n");
  for (int i = 0; i < 11; i++) {
    Serial.print(temporarray[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
  
Serial.println("\n");
  for (int i = 0; i < 8; i++) {
    Serial.print(tmps[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
//debugging reads converted strings
  

  can.send(0x56, 0, 0, 8, tmps);   // SEND TO ID:0X56
  delay(100);
  //Sends Byte array though can, woohoo
}

void VMIN1(){
  byte message[] = {0xAA,0x17,0x3F,0x1E}; // address, function code, CRC, CRC
  byte snd [6];
   float character;
  int count = 0;

Serial.println("VMIN");
  
  Serial2.write(message, sizeof(message));
  //Requests

  while (Serial2.available()) {
    character = Serial2.read();
    float val = character;
    if (count < 7) {
      snd[count] = val;
      count++;
    } else {
      count = 0;
    }
  }
  //Prints BMS output into Byte Array

snd[0]="ID";

  Serial.println("\n");
  for (int i = 0; i < 6; i++) {
    Serial.print(snd[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
  //debugging reads byte message to user

  can.send(0x56, 0, 0, 6, snd);   // SEND TO ID:0X56
  delay(100);
  //Sends Byte array though can, woohoo
}

void VMAX1(){
   byte message[] = {0xAA,0x16,0xFE,0xDE}; // address, function code, CRC, CRC
  byte snd [6];
   float character;
  int count = 0;

  Serial.println("vMAX");
  Serial2.write(message, sizeof(message));
  //Requests

  while (Serial2.available()) {
    character = Serial2.read();
    float val = character;
    if (count < 7) {
      snd[count] = val;
      count++;
    } else {
      count = 0;
    }
  }
  //Prints BMS output into Byte Array

snd[0]="ID";

  Serial.println("\n");
  for (int i = 0; i < 6; i++) {
    Serial.print(snd[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
  //debugging reads byte message to user

  can.send(0x56, 0, 0, 6, snd);   // SEND TO ID:0X56
  delay(100);
  //Sends Byte array though can, woohoo
}

void VPACK1(){
   byte message[] = {0xAA,0x14,0x7F,0x1F}; // address, function code, CRC, CRC
  byte snd [8];
   float character;
  int count = 0;

  Serial.println("vPack");
  Serial2.write(message, sizeof(message));
  //Requests

  while (Serial2.available()) {
    character = Serial2.read();
    float val = character;
    if (count < 9) {
      snd[count] = val;
      count++;
    } else {
      count = 0;
    }
  }
  //Prints BMS output into Byte Array

snd[0]="ID";

  Serial.println("\n");
  for (int i = 0; i < 8; i++) {
    Serial.print(snd[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
  //debugging reads byte message to user

  can.send(0x56, 0, 0, 6, snd);   // SEND TO ID:0X56
  delay(100);
  //Sends Byte array though can, woohoo
}

void CURRENT1(){
   byte message[] = {0xAA,0x15,0xBE,0xDF}; // address, function code, CRC, CRC
  byte snd [8];
   float character;
  int count = 0;

  Serial.println("CURRENT");
  Serial2.write(message, sizeof(message));
  //Requests

  while (Serial2.available()) {
    character = Serial2.read();
    float val = character;
    if (count < 9) {
      snd[count] = val;
      count++;
    } else {
      count = 0;
    }
  }
  //Prints BMS output into Byte Array

snd[0]="ID";

  Serial.println("\n");
  for (int i = 0; i < 8; i++) {
    Serial.print(snd[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
  //debugging reads byte message to user

  can.send(0x56, 0, 0, 8, snd);   // SEND TO ID:0X56
  delay(100);
  //Sends Byte array though can, woohoo
}
//***************************************************************************************************************
void temp2(){
  // put your main code here, to run repeatedly:
  byte message[] = {0xAA, 0x1B, 0x3F, 0x1B}; // address, function code, CRC, CRC
  byte snd [11];
  byte temporarray [11];
  byte tmps[8];
  
  float character;
  int count = 0;

Serial.println("\nBMS3:");
ID=0xCC;

Serial.println("TEMPS");
  Serial3.write(message, sizeof(message));
  //Requests

  while (Serial3.available()) {
    character = Serial3.read();
    float val = character;
    if (count < 12) {
      snd[count] = val;
      count++;
    } else {
      count = 0;
    }
  }
  //Prints BMS output into Byte Array

  Serial.println("\n");
  for (int i = 0; i < 11; i++) {
    Serial.print(snd[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
  //debugging reads byte message to user

  for (int i = 0; i < 11; i++) {
    if (i<3){
      temporarray[i]=snd[i];
    }else if ((i>=3)&&(i<9)){
    temporarray[i]=snd[i+1];
    i++;
    temporarray[i]=snd[i-1];
    }else{
      temporarray[i]=snd[i];
    }
  }

  tmps[0]="ID";
  tmps[1]=temporarray[1];
  tmps[2]=temporarray[5];
  tmps[3]=temporarray[6];
  tmps[4]=temporarray[7];
  tmps[5]=temporarray[8];
  tmps[6]=temporarray[9];
  tmps[7]=temporarray[10];
  //Sets the tmps array to 8 byte array: ID,Command,temp1,temp1,temp2,temp2,CRC,CRC

  Serial.println("\n");
  for (int i = 0; i < 11; i++) {
    Serial.print(temporarray[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
  
Serial.println("\n");
  for (int i = 0; i < 8; i++) {
    Serial.print(tmps[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
//debugging reads converted strings
  

  can.send(0x57, 0, 0, 8, tmps);   // SEND TO ID:0X57
  delay(100);
  //Sends Byte array though can, woohoo
}

void VMIN2(){
  byte message[] = {0xAA,0x17,0x3F,0x1E}; // address, function code, CRC, CRC
  byte snd [6];
   float character;
  int count = 0;

Serial.println("VMIN");
  
  Serial3.write(message, sizeof(message));
  //Requests

  while (Serial3.available()) {
    character = Serial3.read();
    float val = character;
    if (count < 7) {
      snd[count] = val;
      count++;
    } else {
      count = 0;
    }
  }
  //Prints BMS output into Byte Array

snd[0]="ID";

  Serial.println("\n");
  for (int i = 0; i < 6; i++) {
    Serial.print(snd[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
  //debugging reads byte message to user

  can.send(0x57, 0, 0, 6, snd);   // SEND TO ID:0X57
  delay(100);
  //Sends Byte array though can, woohoo
}

void VMAX2(){
   byte message[] = {0xAA,0x16,0xFE,0xDE}; // address, function code, CRC, CRC
  byte snd [6];
   float character;
  int count = 0;

  Serial.println("vMAX");
  Serial3.write(message, sizeof(message));
  //Requests

  while (Serial3.available()) {
    character = Serial3.read();
    float val = character;
    if (count < 7) {
      snd[count] = val;
      count++;
    } else {
      count = 0;
    }
  }
  //Prints BMS output into Byte Array

snd[0]="ID";

  Serial.println("\n");
  for (int i = 0; i < 6; i++) {
    Serial.print(snd[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
  //debugging reads byte message to user

  can.send(0x57, 0, 0, 6, snd);   // SEND TO ID:0X57
  delay(100);
  //Sends Byte array though can, woohoo
}

void VPACK2(){
   byte message[] = {0xAA,0x14,0x7F,0x1F}; // address, function code, CRC, CRC
  byte snd [8];
   float character;
  int count = 0;

  Serial.println("vPack");
  Serial3.write(message, sizeof(message));
  //Requests

  while (Serial3.available()) {
    character = Serial3.read();
    float val = character;
    if (count < 9) {
      snd[count] = val;
      count++;
    } else {
      count = 0;
    }
  }
  //Prints BMS output into Byte Array

snd[0]="ID";

  Serial.println("\n");
  for (int i = 0; i < 8; i++) {
    Serial.print(snd[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
  //debugging reads byte message to user

  can.send(0x57, 0, 0, 6, snd);   // SEND TO ID:0X57
  delay(100);
  //Sends Byte array though can, woohoo
}

void CURRENT2(){
   byte message[] = {0xAA,0x15,0xBE,0xDF}; // address, function code, CRC, CRC
  byte snd [8];
   float character;
  int count = 0;

  Serial.println("CURRENT");
  Serial3.write(message, sizeof(message));
  //Requests

  while (Serial3.available()) {
    character = Serial3.read();
    float val = character;
    if (count < 9) {
      snd[count] = val;
      count++;
    } else {
      count = 0;
    }
  }
  //Prints BMS output into Byte Array

snd[0]="ID";

  Serial.println("\n");
  for (int i = 0; i < 8; i++) {
    Serial.print(snd[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
  //debugging reads byte message to user

  can.send(0x57, 0, 0, 8, snd);   // SEND TO ID:0X57
  delay(100);
  //Sends Byte array though can, woohoo
}
