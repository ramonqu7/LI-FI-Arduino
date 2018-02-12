/*
MIT License
Copyright (c) 2017 Yiren Qu
*/
const int sync = 1000;
int threshold = 0;
bool thresholdCheck = true;

bool receive = false;

int thr_inf = 850;
int thr_red = 360;
int thr_yellow = 0;
int thr_blue =100;

int detRed = 30;

int cu = 0;
int mode = -1;

int previous;
int current;

int inf_pin = A0;
int red_pin = A1;
int blue_pin = A2;
int yellow_pin = A3;

String data_raw = "";
String data_final = "";

char inByte;

void setup()
{
  Serial.begin(115200);
  /*
  Serial.println();
  Serial.print("Red ");
  Serial.print(thr_red);
  Serial.print(" ");
  Serial.print("Inf ");
  Serial.print(thr_inf);
  Serial.print(" ");
  
  Serial.print(" ");
  Serial.print(thr_blue);
  Serial.print(" ");
  
  while (Serial.available() > 0 || thresholdCheck)
  {
    inByte = Serial.read();
    
    if (inByte == '0')
    {
      receive = true;
      //Serial.println("0");
      mode = 0;
    }
    if (inByte == '1')
    {
      receive = true;
      Serial.println("1");
      mode = 1;
    }
    if (inByte == '2')
    {
      receive = true;
      Serial.println("2");
      mode = 2;
    }
    if (inByte == '3')
    {
      receive = true;
      Serial.println("3");
      mode = 3;
    }

    if ( (mode != -1)) /*||(th_y_h&&th_y_l)||(th_b_l&&th_b_h)))
    {
      thresholdCheck = false;
      
      double t1 = (thr_red_h + thr_red_l) / 2 * 1.3;
      double t2 = thr_inf_h - 100; //(thr_inf_h+thr_inf_l)/2*1.8;
      double t3 = (thr_blue_h + thr_blue_l) / 2 * 1.5;
      
      thr_red = (int)t1;
      thr_inf = (int)t2;
      thr_blue = (int)t3;
      
      break;
    }
    delay(20);
  }


  delay(1000);
  */
  receive = true;

      mode = 0;
}

void loop()
{

  if (receive)
  {
    while(analogRead(A0)<thr_inf){

    }

      //  Serial.print(cu);
      //  Serial.print(" ");
      //    Serial.println("Start");
      
     delayMicroseconds(sync / 2);
      //Serial.println(analogRead(red_pin));

      GetData();
    
  }
}
void GetData()
{
  int pre = -1;
  if (mode == 0)
  {
    String datastring = "";
    while (true)
    {
      int pre = micros();
      String ss = "";
      if (analogRead(A0) < thr_inf)
      {
        if (datastring != "")
        {
          Serial.println(datastring);
       // Serial.println();
        }
        break;
      }
   //   Serial.print(analogRead(A1));
     // Serial.print(" ");
/*      if(pre==-1){
        pre = analogRead(A1);
        if (pre>thr_red){
          datastring += "1";
          ss="1";
        }else{
          datastring += "0";
          ss="0";
        }
      }else{
        int cu = analogRead(A1);
        if(abs(cu-pre)<detRed){
          datastring+=ss;
        }else{
          if(ss=="1"){
            ss="0";
            datastring+=ss;
          }else{
            ss="1";
            datastring+=ss;
          }
          
        }
      }*/
      
      if (analogRead(A1) > thr_red)
      {
        datastring += "1";
      }
      else
      {
        datastring += "0";
      }
      while (micros() - pre < sync)
      {
      }
    }
  }
  else if (mode == 1)
  {
    Serial.println("SS");
    int preRead = 0;
    String datastring = "";
    while (true)
    {
      if (analogRead(A0) < thr_inf)
      {

        if (datastring != "")
        {
      //    Serial.println(datastring);
       Serial.println();
        }
        break;
      }
      int pre = micros();
      
      Serial.print(analogRead(A1));
      Serial.print(" ");
      Serial.print(analogRead(A2));
      Serial.print(" ");
      
      if (analogRead(A1) > thr_red)
      {
        datastring += "1";
      }
      else
      {
        datastring += "0";
      }
      if (analogRead(A2) > thr_blue)
      {
        datastring += "1";
      }
      else
      {
        datastring += "0";
      }
      while (micros() - pre < sync)
      {
      }
    }
  }
  else if(mode==2){
      String datastring = "";
    while (true)
    {
      int pre = micros();
      if (analogRead(A0) < thr_inf)
      {
        if (datastring != "")
        {
          Serial.println(datastring);
        }
        break;
      }

      if (analogRead(A1) > thr_red)
      {
        datastring += "1";
      }
      else
      {
        datastring += "0";
      }
      while (micros() - pre < sync)
      {
      }
    }
  }
}
