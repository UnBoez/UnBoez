 void setup() {
  Serial.begin(9600);
  Serial2.begin(115200);
  Serial1.begin(115200);
  delay(3000);
  pinMode(A13,OUTPUT);
  pinMode(A12,OUTPUT);
}

int loopC = 0;
int ch;

char pkg[50];

int state = 0;
int restCnt;
int ledCnt = 101;
int Xacc;
int Yacc;
int Zacc;
int Chone;
int Chtwo;

void doLED()
{
  digitalWrite(13, !digitalRead(13));
 
  return;
  ledCnt++;
  if (100 <= ledCnt) {

    ledCnt = 0;
  }

}

char chksum(char *pk, int lgt)
{
  char s = 0;
  for (int i = 0; i < lgt; i++)
    s += *(pk + i);
  return s;
}

int x;
char chksumB;
char chh;
void loop() {

   if (Serial2.available() ) {

    ch = Serial2.read();
    chh = (char)ch;
     

    if (ch == 0x7e && state == 0) {
      pkg[state] = 0x7e;
      state++;
 
      //doLED();

    }
    else if ( ch == 0x00 && state == 1) {
      pkg[state] = 0x00;
      state++;
      // doLED();
    }
    else if ( ch == 0x14 && state == 2) {
      pkg[state] = 0x14;
      state++;
      // doLED();
    }
    else if ( ch == 0x83 && state == 3) {
      pkg[state] = 0x83;
      state++;
       // doLED();
    }
    else if ( ch == 0x56 && state == 4) {
      pkg[state] = 0x56;
      state++;
      //  doLED();
    }
    else if ( ch == 0x78 && state == 5) {
      pkg[state] = 0x78;
      state++;
      restCnt = 18;
      //  doLED();

    }
    else if (6 <= state ) {
           
      

     
      
      
      if (state == 19)
     x = chh;
      if (state == 20) {
        x = x << 8 | chh;
        Chone = x;
        
      }

       if (state == 21)
       x = chh;
      if (state == 22) {
        x = x << 8 | chh;
        Chtwo = x;
      
      }
      // 18 more bytes to read !!
      pkg[state] = ch;
      state ++;
      //      if (24 <= state) {
      // finished receiving
      chksumB = 0xff - chksum(pkg + 3, 23 - 2);
      if (chksumB == pkg[23]) {
        doLED();

        state = 0; // startover
      }
      if (24 <= state) state = 0;
    }
  }

Serial.print(" CH1  >"); Serial.println(Chone);
Serial.print(" CH2  >"); Serial.println(Chtwo);
if(Chone>300){
  digitalWrite(A12,HIGH);
}
if(Chone<300){
  digitalWrite(A12,LOW);
}



if(Chtwo>300){
  digitalWrite(A13,HIGH);
}

if(Chtwo<300){
  digitalWrite(A13,LOW);
}

  
}
