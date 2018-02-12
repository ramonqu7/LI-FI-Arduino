/*
MIT License
Copyright (c) 2017 Yiren Qu
*/
String data = "";
String packet_size = "";
int sync = 1000;
bool thresholdCheck = true;
bool receive = false;
char inByte;
#define inf_pin 2
#define red_pin 3
#define blue_pin 4
#define yellow_pin 5
int mode = -1;

void setup(){
Serial.begin(115200);
Serial.setTimeout(10);
Serial.println("DONE");
DDRE = DDRE | B11111100;
DDRH = DDRH | B00010000;
randomSeed(analogRead(5));
receive = true;
  PORTE = B00101000;
  mode = 0;
}

void loop(){
while (Serial.available()>0){
  String s = Serial.readString();
   int temp = s.length();
     s = s.substring(0,temp-1);
    if(receive){
   if(s.length()>15){
    while (s.length()>0){
      if(s.length()>15){
    data = s.substring(0,15);
    s = s.substring(15);
 //   Serial.println("d");
    Transm();
    ResetLight();
    delayMicroseconds(2000);
      }else{
   //     Serial.println("s");
        
        data = s;
        s="";
         Transm();
        ResetLight();
        
      }
  }
   Serial.println("DONE");
   }else{
    data = s;
    s="";
    Transm();
    ResetLight();
    Serial.println("DONE");
   }
   
    
}
}
}
void Transm(){
  PORTE = B00100000;
  PORTH = B00010000;
    if(data.length()>0){
    Serial.println(data);
    SendData();
    }
   // delayMicroseconds(3000);
  }
  
/*
void sendZero(int pin){
  digitalWrite(pin,0);
  delayMicroseconds(sync); 
  //Serial.print(0);
//  digitalWrite(pin,1);
}


void sendOne(int pin){
  digitalWrite(pin,1);
  delayMicroseconds(sync); 
//  Serial.print(1);
}
*/

void ResetLight(){
  if(mode == 0){
   PORTE = B00101000;
   
  }
  
}


void SendData()
{
  if(mode ==0){
// Red

PORTE = B00111000;
for(int i = 0; i < data.length(); i++){
    if(data[i] == '1')
    {
      PORTE = B00111000;
  delayMicroseconds(sync); 
    }
    else
    {
     PORTE = B00010000;
  delayMicroseconds(sync); 
    }
  }
PORTE = B00101000;

  }
  else if(mode == 1){
// Two colors

int count=0;
  PORTE = B00110000;
  PORTH = B00010000;
int i=0;
while(i<data.length()){
   int pre = micros();
    if((data[i]=="1")&&(data[i+1]=="1")){
       PORTE = B00110000;
        PORTH = B00010000;
    }else if((data[i]=="1")&&(data[i+1]=="0")){
      PORTE = B00110000;
      PORTH = B00000000;
    }else if((data[i]=="0")&&(data[i+1]=="1")){
      PORTE = B00010000;
      PORTH = B00010000;
    }else{
      PORTE = B00010000;
      PORTH = B00000000;
    }
   
   
   

     //  while(micros()-pre<sync){}
      delayMicroseconds(sync);
    Serial.print(data[i]);
    Serial.print(data[i+1]);
      PORTE = B00110000;
      PORTH = B00010000;
  i+=2;

  
}
 PORTE = B00100000;
 PORTH = B00010000;

Serial.println();

  }else if(mode ==2){
  
  }else if(mode==3){

// Three colors


  }
}
