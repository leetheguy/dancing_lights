#include <Metro.h>

// LED PWMs
const int b1pin       = 2;
const int g1pin       = 3;
const int r1pin       = 4;
const int b2pin       = 5;
const int g2pin       = 6;
const int r2pin       = 7;
const int b3pin       = 8;
const int g3pin       = 9;
const int r3pin       = 10;

// RGB Analog Inputs
const int redInp      = A0;
const int greenInp    = A1;
const int blueInp     = A2;

// LED Intensities
int r1i               = 255;
int g1i               = 0;
int b1i               = 0;
int r2i               = 0;
int g2i               = 0;
int b2i               = 255;
int r3i               = 0;
int g3i               = 255;
int b3i               = 0;

// Array Address Constants
//   Color:
const int red         = 0;
const int green       = 1;
const int blue        = 2;
//   State:
const int stateBlink  = 0;
const int stateCycle  = 1;
const int statePulse  = 2;
const int statePop    = 3;
const int stateGlow   = 4;
const int stateListen = 5;

// Cycle Variables
int active            = 0;
int trail             = 0;
int other             = 0;
int velDir            = 1;

// Pulse Variables
int pulseDir          = 1;

// Pop Variables
int popCount          = 286;

// State Variables
int state             = 0;
int stateCount        = 6;

Metro cycleSpeed      = Metro(20);
Metro pulseSpeed      = Metro(5);
Metro popSpeed        = Metro(10);
Metro blinkSpeed      = Metro(500);
Metro status          = Metro(500);
Metro stateChange     = Metro(5000);

int blink(int led) {
  return !digitalRead(led);
}

int pulse(int i) {
  if (i > 254)
    pulseDir = -1;
  else if (i < 1)
    pulseDir = 1;
  i += pulseDir;
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

  if(*vector[active] > 254) {
    active += 1;
    if(active == 3)
      active = 0;
  }

  switch (active) {
    case 0:
      trail = 2;
      other = 1;
      break;
    case 1:
      trail = 0;
      other = 2;
      break;
    case 2:
      trail = 1;
      other = 0;
      break;
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

  pinMode(redInp, INPUT);
  pinMode(greenInp, INPUT);
  pinMode(blueInp, INPUT);

  Serial.begin(9600);
}

void loop() {
//  if (popSpeed.check() == 1) {
//    r1i = pop();
//    analogWrite(r1pin, r1i);
//  }
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

  if (cycleSpeed.check() == 1) {// && state == stateCycle) {
    cycle(&r1i, &g1i, &b1i);
    analogWrite(b1pin,255-b1i);
    analogWrite(g1pin,255-g1i);
    analogWrite(r1pin,255-r1i);
    cycle(&r2i, &g2i, &b2i);
    analogWrite(b2pin,255-b2i);
    analogWrite(g2pin,255-g2i);
    analogWrite(r2pin,255-r2i);
    cycle(&r3i, &g3i, &b3i);
    analogWrite(b3pin,255-b3i);
    analogWrite(g3pin,255-g3i);
    analogWrite(r3pin,255-r3i);
  }

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
//    Serial.println(dir);
    Serial.println(r1i);
  }
}
