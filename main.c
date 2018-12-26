#include <I2CLiquidCrystal.h>
#include <mglcd.h>



int trig = 8; // 出力ピン
int echo = 9; // 入力ピン

void melody();

#define NOTE_A 440
#define NOTE_B 493
#define NOTE_Cis 554
#define NOTE_D 587
#define NOTE_E 659
#define NOTE_Fis 739
#define NOTE_Gis 830
#define NOTE_A2 880

#define WHOLE 1
#define HALF 0.5
#define QUARTER 0.25
#define EIGHTH 0.125
#define SIXTEENTH 0.625

int tune[] =
{
    NOTE_Fis, NOTE_D, NOTE_A, NOTE_D, NOTE_E, NOTE_A2,
    NOTE_E, NOTE_Fis, NOTE_E, NOTE_A, NOTE_D
};  
float duration[]=
{1,1,1,1,1,3,
 1,1,1,1,4};
int length;   
int tonePin=11; 

void setup() {
  Serial.begin(9600);

  pinMode(tonePin,OUTPUT);   //  initialize the digital pin as an output
  length = sizeof(tune)/sizeof(tune[0]);
    
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  }

void loop() {
  // 超音波の出力終了
  digitalWrite(trig,LOW);
  delayMicroseconds(1);
  // 超音波を出力
  digitalWrite(trig,HIGH);
  delayMicroseconds(11);
  // 超音波を出力終了
  digitalWrite(trig,LOW);
  // 出力した超音波が返って来る時間を計測
  int t = pulseIn(echo,HIGH);
  // 計測した時間と音速から反射物までの距離を計算
  float distance = t*0.017;
  // 計算結果をシリアル通信で出力
  if(distance < 50)melody();
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
}


void melody(){
    for(int x=0;x<length;x++)
    {tone(tonePin,tune[x]);
        delay(300*duration[(x%100)]);    // to distinguish the notes, set a minimum time between them.

        noTone(tonePin); // stop the tone playing:
    }
}
