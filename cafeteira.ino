#include <Rtc_rodri.h>



#include <iostream>
#include <math.h>

#include <Wire.h>
//#include <Rtc_Pcf8563.h>//

#define RELAY 14 

#define OFF_M 00
#define OFF_H 18

#define ON_M 45
#define ON_H 07

#define BZR 02

//init the real time clock
Rtc_rodri rtc;
//const char *day[]={"sabado","domingo","segunda","terca","quarta","quinta","sexta"};

void banzer();
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
  rtc.setDate(8, 0, 7, 2, 22);
  //hr, min, sec
 // rtc.setTime(14, 00, 0);//
  Serial.begin(9600);
}
using namespace std; 

void loop()
{  const char *day[]={"sabado","domingo","segunda","terca","quarta","quinta","sexta"};

 Serial.println(day[weekday(rtc.getDay(),rtc.getMonth(),rtc.getYear())]);
 //  int day_int = weekday( rtc.getDay(),rtc.getMonth(),rtc.getYear());
  // Serial.println(day[day_int]);

  //both format functions call the internal getTime() so that the 
  //formatted strings are at the current time/date.
  Serial.print(rtc.formatTime());
  Serial.print("\r\n");
  Serial.println(rtc.formatDate());
  Serial.print("\r\n");
  delay(1000);
  
  if (rtc.getMinute()==ON_M && rtc.getHour()==ON_H)
  {
    digitalWrite(RELAY,LOW);
    
  }
  if(rtc.getMinute()==OFF_M && rtc.getHour()==OFF_H)
  {
    digitalWrite(RELAY,HIGH);
  }
  
}
/*=============função do bazer============*/

void bazer()
{
  digitalWrite(BZR,HIGH);
  delay(100);
  digitalWrite(BZR,LOW);
  delay(500);
  
  
  }
