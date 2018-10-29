#include <wiringPi.h>
#include <stdio.h>
int main (int argc, char *argv[])
{
  int i;
  wiringPiSetup () ;
  pinMode (1, OUTPUT) ;
  pinMode (2, OUTPUT) ;
  pinMode (4, OUTPUT) ;
  for (i=0;i<10;i++) {
    digitalWrite (1, HIGH) ; delay (500) ;
    digitalWrite (1,  LOW) ; delay (500) ;
  }
  for (i=0;i<10;i++) {
    digitalWrite (2, HIGH) ; delay (500) ;
    digitalWrite (2,  LOW) ; delay (500) ;
  }
  for (i=0;i<10;i++) {
    digitalWrite (4, HIGH) ; delay (500) ;
    digitalWrite (4,  LOW) ; delay (500) ;
  }
  return 0 ;
}
