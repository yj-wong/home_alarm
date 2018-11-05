#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include "ifttt.h"

int off() {
	time_t start = time(NULL);
	time_t end = start + 1;
	digitalWrite(6, LOW);

	while(time(NULL) < end) {}

	digitalWrite(1, HIGH);
	digitalWrite(2, LOW);
	digitalWrite(5, LOW);

	while (1) {
		if (digitalRead(3) == 0) {
		printf("ALARM_ARMING\n");
		return arming();
		}
	}
}

int arming() {
	time_t start = time(NULL);
	time_t end = start + 10;

	while (time(NULL) < end) {
		if (time(NULL) % 2 == 0) {
			digitalWrite(1, HIGH);
		} else {
			digitalWrite(1, LOW);
		}
	}
	printf("ALARM_ARMED\n");
	return armed();
}

int armed() {
	digitalWrite(1, LOW);
	digitalWrite(2, HIGH);

	while (1) {
		if (digitalRead(3) == 0) {
			printf("ALARM_OFF\n");
			return off();
		} else if (digitalRead(0) == 1) {
			printf("ALARM_TRIGGERED\n");
			return triggered();
		}
	}
}

int triggered() {
	time_t start = time(NULL);
	time_t end = start + 10;

	while (time(NULL) < end) {
		if (digitalRead(3) == 0) {
			printf("ALARM_OFF\n");
			return off();
		}
		if (time(NULL) % 2 == 0) {
			digitalWrite(1, HIGH);
			digitalWrite(2, HIGH);
		}	else {
			digitalWrite(1, LOW);
			digitalWrite(2, LOW);
		}
	}
	printf("ALARM_SOUNDING\n");
	return sounding();
}

int sounding() {
	ifttt("https://maker.ifttt.com/trigger/alarm_triggered/with/key/x9XnvGbgm0kq1KFLFBCyZ", "alarm", "sounding", "hi");
	printf("Sending email via ifttt server.\n");
	while (1) {
		if (digitalRead(3) == 0) {
			printf("ALARM_OFF\n");
			return off();
		}
		if (time(NULL) % 3 == 0) {
			digitalWrite(1, HIGH);
			digitalWrite(2, HIGH);
			digitalWrite(6, HIGH);
		} else if (time(NULL) % 3 != 0) {
			digitalWrite(1, LOW);
			digitalWrite(2, LOW);
			digitalWrite(6, LOW);
		}
	}
}

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

	printf("START\n");
	off();

	return 0;
}
