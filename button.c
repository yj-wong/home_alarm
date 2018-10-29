#include <wiringPi.h>
#include <stdio.h>
int main (int argc, char *argv[])
{
  wiringPiSetup () ;
  pinMode (3, INPUT) ;
  pullUpDnControl(3, PUD_UP) ;
  for (;;)
  {
    int x = digitalRead(3);
    printf("Got a %d\n",x);
  }
  return 0 ;
}
