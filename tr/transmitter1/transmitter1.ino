String data = "";
String packet_size = "";
int sync = 3000;


bool thresholdCheck = true;
bool th_r_h = false;
bool th_r_l = false;
bool th_b_h = false;
bool th_b_l = false;
bool th_y_h = false;
bool th_y_l = false;
bool th_i_h = false;
bool th_i_l = false;
bool receive = false;

int thr_inf = 0;
int thr_red = 0;
int thr_yellow = 0;
int thr_blue = 0;

char inByte;

int inf_pin= 2;
int red_pin= 3;
int blue_pin= 7;
int yellow_pin =5;

int mode = -1;

void setup(){
Serial.begin(115200);
pinMode(inf_pin,OUTPUT);
pinMode(red_pin,OUTPUT);
randomSeed(analogRead(4));

  while(Serial.available()>0 || thresholdCheck){
    inByte = Serial.read();
    if((inByte)=='C'){
      digitalWrite(red_pin,1);
      th_r_h = true;
      Serial.println("1");
    }
    if((inByte)=='D'){
      digitalWrite(red_pin,0);
      th_r_l = true;
      Serial.println("2");
    }
    if((inByte)=='E'){
      digitalWrite(8,1);
      th_b_h = true;
      Serial.println("3");
    }
    if((inByte)=='F'){
      digitalWrite(8,0);
      th_b_l = true;
      Serial.println("4");
    }
    if((inByte)=='G'){
      digitalWrite(yellow_pin,1);
      th_y_h= true;
      Serial.println("5");
    }
    if((inByte)=='H'){
      digitalWrite(yellow_pin,0);
      th_y_l = true;
      Serial.println("6");
    }
    if((inByte)=='A'){
      digitalWrite(inf_pin, 1);
      digitalWrite(red_pin,1);
      th_i_h = true;
      Serial.println("7");
    }
    if((inByte)=='B'){
      digitalWrite(inf_pin,0);
      digitalWrite(red_pin,1);
      th_i_l = true;
      Serial.println("8");
    }

    if((th_i_l&&th_i_h)&&((th_r_l&&th_r_h)/*&&(th_y_h&&th_y_l)&&(th_b_l&&th_b_h)*/)){
      thresholdCheck = false;
      break;
    }
    delay(1000);
  }

}

void loop(){
while (Serial.available()>0){
  
  String s = Serial.readString();
   int temp = s.length();
     s = s.substring(0,temp-1);
if(s == "T"){
 Serial.println("STOP");
  receive = false;
}else if(s == "S0"){
  receive = true;
    Serial.println("0");
  digitalWrite(red_pin,1);
  mode = 0;
}else if(s == "S1"){
  receive = true;
  Serial.println("1");
  mode = 1;
}else if(s == "S2"){
  receive = true;
  Serial.println("2");
  mode = 2;
}else if(s == "S3"){
  receive = true;
  Serial.println("3");
  mode = 3;
}else if(receive){
data = s;
//Serial.println(data);

if( data!= ""){
 // Serial.println("transm");
  /*
  int temp = data.toInt();
  
  for(int i=0;i<30;i++){
    String s = "";
    for(int j=0;j<temp;j++){
      s+=String(random(2));
    }
    data = s;
  Transm();
  ResetLight();
  }*/
  Transm();
  delayMicroseconds(sync/4);
  ResetLight();
}
}
}
}
void Transm(){
    if(data.length()>0){
    digitalWrite(inf_pin,1);
    delayMicroseconds(sync/4);
    SendData();
    }
  }
  

void sendZero(int pin){
  int pre = micros();
  analogWrite(pin,0);
  while(micros()-pre<sync){

  }
  //Serial.print(0);
// digitalWrite(pin,1);
// delayMicroseconds(sync/2); 
  
}


void sendOne(int pin){
  int pre = micros();
  analogWrite(pin,1024 );
  while(micros()-pre<sync){
    
  }
 // digitalWrite(pin,0);
   //delayMicroseconds(sync/2); 
}


void ResetLight(){
  if(mode == 0){
    digitalWrite(red_pin,1);
  }
  delayMicroseconds(50);
}


void SendData()
{
  if(mode ==0){
// Red
for(int i = 0; i < data.length(); i++){
    if(data[i] == '1')
    {
      sendOne(red_pin);
      Serial.print(data[i]);
    }
    else
    {
      sendZero(red_pin);
      Serial.print(data[i]);
    }
  }
Serial.println("");
digitalWrite(inf_pin,0);
delayMicroseconds(sync);
  }else if(mode == 1){
// Blue
for(int i = 0; i < data.length(); i++){
    if(data[i] == '1')
    {
      sendOne(blue_pin);
  //    Serial.print(data[i]);
    }
    else
    {
      sendZero(blue_pin);
    //  Serial.print(data[i]);
    }
  }

  }else if(mode ==2){
// Yellow
for(int i = 0; i < data.length(); i++){
    if(data[i] == '1')
    {
      sendOne(yellow_pin);
  //    Serial.print(data[i]);
    }
    else
    {
      sendZero(yellow_pin);
    //  Serial.print(data[i]);
    }
  }
Serial.println("DONE");
digitalWrite(inf_pin,0);
delayMicroseconds(sync);
  }else if(mode==3){

// Three colors


  }
}
