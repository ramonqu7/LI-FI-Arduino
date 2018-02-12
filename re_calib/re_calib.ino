

const int sync = 1000;
int threshold = 0;
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
int thr_inf_h = 0;
int thr_red_h = 0;
int thr_yellow_h = 0;
int thr_blue_h = 0;
int thr_inf_l = 0;
int thr_red_l = 0;
int thr_yellow_l = 0;
int thr_blue_l = 0;

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
}

void loop()
{
  while (Serial.available() > 0||thresholdCheck)
  {
    inByte = Serial.read();
    if (inByte == 'C')
    {
      thr_red_h = analogRead(A1);
      Serial.println(thr_red_h);
      th_r_h = true;
    }
    if (inByte == 'D')
    {
      thr_red_l = analogRead(A1);
      Serial.println(thr_red_l);
      th_r_l = true;
    }
    if (inByte == 'E')
    {
      thr_blue_h = analogRead(A2);
      Serial.println(thr_blue_h);
      th_b_h = true;
    }
    if (inByte == 'F')
    {
      thr_blue_l = analogRead(A2);
      Serial.println(thr_blue_l);
      th_b_l = true;
    }
    if (inByte == 'G')
    {
      thr_yellow_h = analogRead(yellow_pin);
      th_y_h = true;
    }
    if (inByte == 'H')
    {
      thr_yellow_l = analogRead(yellow_pin);
      th_y_l = true;
    }
    if ((inByte) == 'A')
    {
      thr_inf_h = analogRead(A0);
      Serial.println(thr_inf_h);
      th_i_h = true;
    }
    if ((inByte) == 'B')
    {
      thr_inf_l = analogRead(A0);
      Serial.println(thr_inf_l);
      th_i_l = true;
    }
    if (inByte == '0')
    {
      
      double t1 = (thr_red_h + thr_red_l) / 2 * 1.3;
      double t2 = thr_inf_h - 100; //(thr_inf_h+thr_inf_l)/2*1.8;
      double t3 = (thr_blue_h + thr_blue_l) / 2 * 1.5;
      thr_red = (int)t1;
      thr_inf = (int)t2;
      thr_blue = (int)t3;

      Serial.println();
      Serial.print("Red ");
      Serial.print(thr_red);
      Serial.print(" ");
      Serial.print(thr_red_h);
      Serial.print(" ");
      Serial.print(thr_red_l);
      Serial.print("Inf ");
      Serial.print(thr_inf);
      Serial.print(" ");
      Serial.print(thr_inf_h);
      Serial.print(" ");
      Serial.print(thr_inf_l);
      Serial.print(" ");
      Serial.print(thr_blue);
      Serial.print(" ");
      Serial.print(thr_blue_h);
      Serial.print(" ");
      Serial.print(thr_blue_l);
      Serial.println("   Threshold Fixed");
    }

    delay(20);
  }
}
