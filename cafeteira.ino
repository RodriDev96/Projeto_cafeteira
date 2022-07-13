#include <Rtc_rodri.h>



//#include <iostream>
#include <math.h>

#include <Wire.h>


#define RELAY 14 

#define OFF_M 00
#define OFF_H 18
#define MINUTOS_DESLIGAR (OFF_H*60+OFF_M)

#define ON_M 40
#define ON_H 7
#define MINUTOS_LIGAR (ON_H*60+ON_M)

#define ON_M8 00
#define ON_H8 8

#define ON_M12 00
#define ON_H12 12

#define ON_M13 00
#define ON_H13 13

#define ON_M18 00
#define ON_H18 18

#define BZR 15

//init the real time clock
Rtc_rodri rtc;
//const char *day[]={"sabado:","domingo:","segunda:","terca:","quarta:","quinta:","sexta:"};

void banzer();
void rele();
int DOOMS_ZERO = 3; //doomsday do ano zero  
int doomsday( int year){
  int century, doomsCentury, centCentury, dooms, centYear;
  century = (int)(year/100);
  doomsCentury = (((century%4)*5) + DOOMS_ZERO )%7;
  centYear = year-century*100;
  dooms = (centYear%28%4) + ((int)(centYear/4)*5);
  dooms = (dooms + doomsCentury)%7;
  
  return dooms;
} 


int weekday(int day,int month, int year){
    int dooms,ref=0;
    dooms = doomsday(year);
    if((year%4 == 0) && (year%100!=0)){ //is a leap year
      int doomsdays[]={32,29,0,4,9,6,11,8,5,10,7,12};
      ref = doomsdays[month-1];
    }
    else
     {
      int doomsdays[]={31,28,0,4,9,6,11,8,5,10,7,12};
      ref = doomsdays[month-1];
    }
    if((ref-day)>0)
    {
      return ((7-(abs(ref-day)%7))+ dooms)%7;
    }
    else
    { 
    return (abs(ref-day) + dooms)%7;
    }
} 

void setup()
{
  pinMode(RELAY,OUTPUT);
  pinMode(BZR,OUTPUT);
   digitalWrite(RELAY,HIGH);
  //clear out the registers
  rtc.initClock();
  //set a time to start with.
  //day, weekday, month, century(1=1900, 0=2000), year(0-99)
  //rtc.setDate (11, 2, 7, 2, 22);
  //hr, min, sec
  //rtc.setTime(17, 15, 0);//
  Serial.begin(9600);
}
using namespace std; 

void loop()
{  const char *day[]={"sabado:","domingo:","segunda:","terca:","quarta:","quinta:","sexta:"};

 Serial.println(day[weekday(rtc.getDay(),rtc.getMonth(),rtc.getYear())]);
 

  //both format functions call the internal getTime() so that the 
  //formatted strings are at the current time/date.
  Serial.print(rtc.formatTime());
  Serial.print("\r\n");
  Serial.println(rtc.formatDate());
  Serial.print("\r\n");
  delay(1000);
  
   int MINUTOS_ATUAL=(rtc.getHour()*60+rtc.getMinute());
  Serial.println(MINUTOS_ATUAL);

  Serial.println(weekday(rtc.getDay(),rtc.getMonth(),rtc.getYear()));
   
  if(weekday(rtc.getDay(),rtc.getMonth(),rtc.getYear())>=2 && weekday(rtc.getDay(),rtc.getMonth(),rtc.getYear())<=6)
  {
 
  if (rtc.getHour()==ON_H8&&rtc.getMinute()==ON_M8)
  {
    
    bazer();
  }
  if(rtc.getHour()==ON_H12&&rtc.getMinute()==ON_M12)
  {
    bazer();
  }
  if (rtc.getHour()==ON_H13&&rtc.getMinute()==ON_M13){
    bazer();
  }
  if (rtc.getHour()==ON_H18&&rtc.getMinute()==ON_M18){
    bazer();
  }

  
  if(MINUTOS_ATUAL>=MINUTOS_LIGAR && MINUTOS_ATUAL<=MINUTOS_DESLIGAR){
      
          digitalWrite(RELAY,LOW);
          Serial.print("ligado!!!!\n");
     
  }}
  else{
    digitalWrite(RELAY,HIGH);
    Serial.print("desligado!!!!\n");
    }
}
/*=============função do bazer============*/

void bazer()
{//static int i;
//for (i=1000;i<2000;i++){
  tone(BZR,1000,500);
  delay(550);
   tone(BZR,1100,500);
  delay(550);
   tone(BZR,1200,500);
  delay(550);
   tone(BZR,1300,500);
  delay(550);
   tone(BZR,1400,500);
  delay(550);
   tone(BZR,1500,500);
  delay(1600);
 /* digitalWrite(BZR,HIGH);
  delay(500);
  digitalWrite(BZR,LOW);
  delay(100);*/
  
  
  }
 
