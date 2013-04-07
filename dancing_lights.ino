#include <Metro.h>

// LED PWMs
const int bpin        = 2;
const int gpin        = 3;
const int rpin        = 4;

// LED Intensities
int rInt              = 255;
int gInt              = 255;
int bInt              = 255;

// RGB Inputs
int rInp              = A0;
int gInp              = A1;
int bInp              = A2;

// Mic Input
int micInp            = A5;

// Array Address Constants
//   Color:
const int red         = 0;
const int green       = 1;
const int blue        = 2;
//   State:
const int stateGlow   = 0;
const int stateBlink  = 1;
const int statePulse  = 2;
const int statePop    = 3;
const int stateListen = 4;
const int stateCycle  = 5;

// Button Variables
int  buttonPin        = 52;
bool buttonPressed    = false;

// Blink Variables
bool blinkon          = false;

// Cycle Variables
int active            = 0;
int trail             = 0;
int other             = 0;
int velDir            = 1;

// Pulse Variables
float pulseCount      = 1;
int pulseDir          = 1;

// Pop Variables
float popCount        = 0;

// State Variables
int state             = 0;
int stateCount        = 5;

// Loop Frequencies
Metro glowSpeed       = Metro(20);
Metro blinkSpeed      = Metro(500);
Metro pulseSpeed      = Metro(20);
Metro popSpeed        = Metro(10);
Metro listenSpeed     = Metro(5);
Metro cycleSpeed      = Metro(20);
Metro status          = Metro(500);

Metro stateChange     = Metro(2000);

// nobs capture a range between 383 & 639
// to represent the approximate range of the pots
// numbers are based on a 1/8 from center range
// rInp: 330 - 480
// gInp: 390 - 550 
// bInp: 210 - 360
int redNob() {
  int a = analogRead(rInp)-330;
  a = (a*0.85)*2;
  a = a < 0   ? 0   : a;
  a = a > 255 ? 255 : a;
  return 255-a;
}

int greenNob() {
  int a = analogRead(gInp)-400;
  a = (a*0.85)*2;
  a = a < 0   ? 0   : a;
  a = a > 255 ? 255 : a;
  return 255-a;
}

int blueNob() {
  int a = analogRead(bInp)-220;
  a = (a*0.85)*2;
  a = a < 0   ? 0   : a;
  a = a > 255 ? 255 : a;
  return 255-a;
}

void glow() {
  int r;
  analogWrite(bpin, blueNob());
  analogWrite(gpin, greenNob());
  analogWrite(rpin, redNob());
}

void blink() {
  blinkon = !blinkon;
  if(blinkon) {
    analogWrite(bpin, 255);
    analogWrite(gpin, 255);
    analogWrite(rpin, 255);
  } else {
    analogWrite(bpin, blueNob());
    analogWrite(gpin, greenNob());
    analogWrite(rpin, redNob());
  }
}

void pulse() {
  if (pulseCount > 0.99)
    pulseDir = -1;
  if (pulseCount < 0.01)
    pulseDir = 1;
  pulseCount += pulseDir * 0.01;
  analogWrite(bpin, 255 - ((255-blueNob())  * pulseCount));
  analogWrite(gpin, 255 - ((255-greenNob()) * pulseCount));
  analogWrite(rpin, 255 - ((255-redNob())   * pulseCount));
}

int pop() {
  popCount += 0.01;

  if(popCount > 2)
    popCount = -1;

  float c = popCount;

  if (c < 0)
    c = 0;
  else if (c > 1)
    c = 1;
  analogWrite(bpin, 255 - ((255-blueNob())  * c));
  analogWrite(gpin, 255 - ((255-greenNob()) * c));
  analogWrite(rpin, 255 - ((255-redNob())   * c));
}

void listen() {
  float l = analogRead(micInp)*0.000976525;
  Serial.println(l);

  analogWrite(bpin, 255 - ((255 - blueNob())  * l));
  analogWrite(gpin, 255 - ((255 - greenNob()) * l));
  analogWrite(rpin, 255 - ((255 - redNob())   * l));
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
      trail = 2; other = 1; break;
    case 1:
      trail = 0; other = 2; break;
    case 2:
      trail = 1; other = 0; break;
  }

  *vector[active]  += 1;
  if(*vector[trail] > 0)
    *vector[trail]   -= 1;
  if(*vector[other] > 0)
    *vector[other] -= 1;
}

void setup() {
  pinMode(rpin, OUTPUT);
  analogWrite(rpin,255);
  pinMode(gpin, OUTPUT);
  analogWrite(gpin,255);
  pinMode(bpin, OUTPUT);
  analogWrite(bpin,255);

  pinMode(rInp, INPUT);
  pinMode(gInp, INPUT);
  pinMode(bInp, INPUT);

  Serial.begin(9600);
}

void loop() {
//  if (popSpeed.check() == 1) {
//    rInt = pop();
//    analogWrite(rpin, rInt);
//  }
  if(digitalRead(buttonPin) && !buttonPressed) {
    buttonPressed = true;
    if(state >= (stateCount-1))
      state = 0;
    else
      state += 1;
  }

  if(!digitalRead(buttonPin) && buttonPressed)
    buttonPressed = false;

  if (glowSpeed.check() == 1 && state == stateGlow) {
    glow();
  }

  if (blinkSpeed.check() == 1 && state == stateBlink) {
    blink();
  }

  if (pulseSpeed.check() == 1 && state == statePulse) {
    pulse();
  }

  if (popSpeed.check() == 1 && state == statePop) {
    pop();
  }

  if (listenSpeed.check() == 1 && state == stateListen) {
    listen();
  }

//  if (cycleSpeed.check() == 1) {// && state == stateCycle) {
//    cycle(&rInt, &gInt, &bInt);
//    analogWrite(bpin,255-bInt);
//    analogWrite(gpin,255-gInt);
//    analogWrite(rpin,255-rInt);
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
//    snprintf (out, sizeof out, "r1: %i,g1: %i,b1: %i", analogRead(rInt);
//    snprintf (out, sizeof out, "r2: %i,g2: %i,b2: %i", rInt, gInt, bInt);
//    snprintf (out, sizeof out, "r3: %i,g3: %i,b3: %i", rInt, gInt, bInt);
//    snprintf (out, sizeof out, "active: %i", active);
//    snprintf (out, sizeof out, "dir: %i", dir);
//    snprintf (out, sizeof out, "velocity: %i", velocity);
//    snprintf (out, sizeof out, "intensity: %i", rInt);
//    analogWrite(rpin, pulse(rpin));
//    Serial.println(pulse(rpin, &rInt));
//    Serial.println(dir);
//    Serial.println(analogRead(blueNob()));
//    Serial.println(analogRead(greenNob()));
//    Serial.println(analogRead(rInp));
  }
}
