#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include "ifttt.h"

int main(int argc, char *argv[])
{
	int state = 0;	

  wiringPiSetup () ;
  pinMode(0, INPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  pinMode(6, OUTPUT);
  pullUpDnControl(3, PUD_UP);
		
	/*
	0: off
	1: arming
	2: armed
	3: triggered
	4: sounding
	*/
		
  /*ALARM OFF*/
  printf("ALARM_OFF\n");
	TOP:	while (state == 0) {
		digitalWrite(1, HIGH);
		digitalWrite(2, LOW);
		digitalWrite(5, LOW);
		
		delay(1000);
		
		if (digitalRead(3) == 0) {
			state = 1;
			printf("ALARM_ARMING.\n");
		}	
	}
	 
	 /*ALARM_ARMING*/
	while (state == 1) {
		int n = 10;
		int i = 0;
		for (i = 0; i < n; i++) {
			digitalWrite(1, HIGH); delay(500);
			digitalWrite(1, LOW); delay(500);
		}
		digitalWrite(2, HIGH);
		state = 2;
		printf("ALARM_ARMED.\n");
	}
	
	/*ALARM_ARMED*/
	while (state == 2) {
		digitalWrite(2, HIGH);
		delay(1000);
		
		if (digitalRead(3) == 0) {
			state = 0;
			printf("ALARM_OFF.\n");
			goto TOP;
		}
		delay(1000);
		if (digitalRead(0) == 0) {
			state = 3;
			printf("ALARM_TRIGGERED.\n");
		}
	}
	
	/*ALARM_TRIGGERED*/
	while (state == 3) {
		time_t start = time(NULL);
		time_t end = start + 10;
		
		while (time(NULL) != end) {
			digitalWrite(1, HIGH);
			digitalWrite(2, HIGH);
			delay(1000);
			digitalWrite(1, LOW);
			digitalWrite(2, LOW);
			delay(1000);
			
			if (digitalRead(3) == 0) {
				state = 0;
				printf("ALARM_OFF\n");
				goto TOP;
			}
		}
		state = 4;
		printf("ALARM_SOUNDING\n");
	}
	
	while (state == 4) {
		time_t start = time(NULL);
		time_t end = start + 5;
		
		digitalWrite(1, HIGH);
		digitalWrite(2, HIGH);
		digitalWrite(6, HIGH);
		delay(2000);
		digitalWrite(1, LOW);
		digitalWrite(2, LOW);
		digitalWrite(6, LOW);
		delay(2000);
		
		ifttt("https://maker.ifttt.com/trigger/alarm_triggered/with/key/x9XnvGbgm0kq1KFLFBCyZ", "alarm", "sounding", "hi");
		printf("Sending email via ifttt server.\n");
		
		if (digitalRead(3) == 0) {
			state = 0;
			printf("ALARM_OFF\n");
			goto TOP;
		}
		else if (time(NULL) == end) {
			continue;
		}
	}
}
