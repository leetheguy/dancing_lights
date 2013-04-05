#include <Metro.h>


const int b1pin     = 2;      // the number of the LED pin
const int g1pin     = 3;      // the number of the LED pin
const int r1pin     = 4;      // the number of the LED pin
const int b2pin     = 5;      // the number of the LED pin
const int g2pin     = 6;      // the number of the LED pin
const int r2pin     = 7;      // the number of the LED pin
const int b3pin     = 8;      // the number of the LED pin
const int g3pin     = 9;      // the number of the LED pin
const int r3pin     = 10;     // the number of the LED pin

const int sw1    = 52;
const int sw2    = 50;
const int sw3    = 48;

const int red    = 0;
const int green  = 1;
const int blue   = 2;
const int velInp = A0;

const int stateBlink = 0;
const int stateCycle = 1;

int active   = 0;
int trail    = 0;
int other    = 0;
int dir      = 1;
int r1i      = 255;
int g1i      = 0;
int b1i      = 0;
int r2i      = 0;
int g2i      = 0;
int b2i      = 255;
int r3i      = 0;
int g3i      = 255;
int b3i      = 0;
int velocity = 0;
int popCount = 286;

int state        = 1;
int stateCount   = 2;

Metro cycleSpeed  = Metro(5);
Metro pulseSpeed  = Metro(5);
Metro popSpeed    = Metro(10);
Metro blinkSpeed  = Metro(500);
Metro status      = Metro(500);
Metro stateChange = Metro(5000);

void setVelocity() {
//  int v = 128; //analogRead(velInp);
//  if(v > 511) {
//    dir = 1;
//    velocity = (v-512)/2;
//  } else {
//    dir = -1;
//    velocity = (511-v)/2;
//  }
//  velocity = 255-velocity;

//  char out[256];
//  snprintf (out, sizeof out, "pace: %i", pace);
//  Serial.println(out);
//  cycleSpeed.interval(5+velocity/10);
//  blinkSpeed.interval(300+(velocity*2));
}

int blink(int led) {
  return !digitalRead(led);
//  if (digitalRead(led))
//    return LOW;
//  else
//    return HIGH;
}

int pulse(int i) {
  if (i > 254)
    dir = -1;
  else if (i < 1)
    dir = 1;
  i += dir;
  return i;
}

int pop() {
  popCount -= 1;

  if(popCount < -31)
    popCount = 350;

    if (popCount < 1)
      return 0;
    else if (popCount > 254)
      return 255;
    else
      return popCount;
}

void cycle(int *r, int *g, int *b) {
  int *vector[3] = {r,g,b};
  int trail;
  int other;

  if(*vector[active] > 254) {// || *vector[trail] < 1) {
    active += dir;
    if(active == 3)
      active = 0;
    if(active == -1)
      active = 2;
  }

  if(active == 0) {
    if(dir == 1) {
      trail = 2;
      other = 1;
    } else {
      trail = 1;
      other = 2;
    }
  } else if(active == 1) {
    if(dir == 1) {
      trail = 0;
      other = 2;
    } else {
      trail = 2;
      other = 0;
    }
  } else {
    if(dir == 1) {
      trail = 1;
      other = 0;
    } else {
      trail = 0;
      other = 1;
    }
  }

  *vector[active]  += 1;
  if(*vector[trail] > 0)
    *vector[trail]   -= 1;
  if(*vector[other] > 0)
    *vector[other] -= 1;
}

void setup() {
  pinMode(b1pin, OUTPUT);
  analogWrite(b1pin,255);
  pinMode(g1pin, OUTPUT);
  analogWrite(g1pin,255);
  pinMode(r1pin, OUTPUT);
  analogWrite(r1pin,255);
  pinMode(b2pin, OUTPUT);
  analogWrite(b2pin,255);
  pinMode(g2pin, OUTPUT);
  analogWrite(g2pin,255);
  pinMode(r2pin, OUTPUT);
  analogWrite(r2pin,255);
  pinMode(b3pin, OUTPUT);
  analogWrite(b3pin,255);
  pinMode(g3pin, OUTPUT);
  analogWrite(g3pin,255);
  pinMode(r3pin, OUTPUT);
  analogWrite(r3pin,255);

  pinMode(velInp, INPUT);

  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(sw3, INPUT);

  Serial.begin(9600);
}

void loop() {
//  setVelocity();
  if (popSpeed.check() == 1) {
    r1i = pop();
    analogWrite(r1pin, r1i);
  }
//  if (stateChange.check() == 1) {
//    if(state >= (stateCount-1))
//      state = 0;
//    else
//      state += 1;
//    analogWrite(r1pin,255);
//    analogWrite(g1pin,0);
//    analogWrite(b1pin,0);
//    analogWrite(r2pin,0);
//    analogWrite(g2pin,0);
//    analogWrite(b2pin,255);
//    analogWrite(r3pin,0);
//    analogWrite(g3pin,255);
//    analogWrite(b3pin,0);
//  }

//  if (blinkSpeed.check() == 1 && state == stateBlink) {
//    digitalWrite(b1pin, blink(b1pin));
//  }

//  if (cycleSpeed.check() == 1 && state == stateCycle) {
//    cycle(&r1i, &g1i, &b1i);
//    analogWrite(b1pin,255-b1i);
//    analogWrite(g1pin,255-g1i);
//    analogWrite(r1pin,255-r1i);
//    cycle(&r2i, &g2i, &b2i);
//    analogWrite(b2pin,255-b2i);
//    analogWrite(g2pin,255-g2i);
//    analogWrite(r2pin,255-r2i);
//    cycle(&r3i, &g3i, &b3i);
//    analogWrite(b3pin,255-b3i);
//    analogWrite(g3pin,255-g3i);
//    analogWrite(r3pin,255-r3i);
//  }

  if (status.check() == 1) {
    char out[256];
//    snprintf (out, sizeof out, "high: %i, low: %i", HIGH, LOW);
//    snprintf (out, sizeof out, "active: %i", active);
//    snprintf (out, sizeof out, "r1: %i,g1: %i,b1: %i", analogRead(r1i);
//    snprintf (out, sizeof out, "r2: %i,g2: %i,b2: %i", r1i, g1i, b1i);
//    snprintf (out, sizeof out, "r3: %i,g3: %i,b3: %i", r1i, g1i, b1i);
//    snprintf (out, sizeof out, "active: %i", active);
//    snprintf (out, sizeof out, "dir: %i", dir);
//    snprintf (out, sizeof out, "velocity: %i", velocity);
//    snprintf (out, sizeof out, "intensity: %i", r1i);
//    analogWrite(r1pin, pulse(r1pin));
//    Serial.println(pulse(r1pin, &r1i));
    Serial.println(dir);
    Serial.println(r1i);
  }
}
