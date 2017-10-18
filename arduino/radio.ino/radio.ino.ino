#include <LedControl.h>

/* 
 * Now we create a new LedControl. 
 * We use pins 12,11 and 10 on the Arduino for the SPI interface
 * Pin 11 is connected to the DATA IN-pin of the first MAX7221
 * Pin 13 is connected to the CLK-pin of the first MAX7221
 * Pin 10 is connected to the LOAD(/CS)-pin of the first MAX7221   
 * There will only be a single MAX7219 attached to the arduino 
 */
LedControl lc=LedControl(11,13,10,1); 

int frequency = 11800;

class Encoder {
protected:
  int pin_a;
  int pin_b;
  int step_size;
  int last_a;
  int last_b;
public:
  Encoder(int pin_a, int pin_b, int step_size) :
      pin_a(pin_a),
      pin_b(pin_b),
      step_size(step_size),
      last_a(HIGH),
      last_b(HIGH) {
      pinMode(pin_a, INPUT_PULLUP);
      pinMode(pin_b, INPUT_PULLUP);
  }

  virtual void scan() {
    int val_a = digitalRead(pin_a);
    int val_b = digitalRead(pin_b);
    int pin = -1;
    int val = HIGH;
    if (val_a != last_a) {
      pin = pin_a;
      val = val_a;
    } else if (val_b != last_b) {
      pin = pin_b;
      val = val_b;
    }
    last_a = val_a;
    last_b = val_b;

    if (pin == -1) {
      return;
    }

    if (val_a == val_b) return;
    if (pin == pin_a) {
      //Serial.println("left");
      frequency -= step_size;
    } else {
      //Serial.println("right");
      frequency += step_size;
    }
    if (frequency >= 13700) {
      frequency -= (13700 - 11800);
    } else if (frequency < 11800) {
      frequency += (13700 - 11800);
    }
  }
};

Encoder small_enc(2, 3, 5);
Encoder large_enc(4, 5, 100);

void setup() {
  Serial.begin(9600);
  lc.shutdown(0,false);
  lc.setIntensity(0,1);
  lc.setScanLimit(0, 5);
  lc.clearDisplay(0);
}

#define SERIAL_BUF_SIZE 100
char buffer[SERIAL_BUF_SIZE];
int pos = 0;
int old_frequency = 0;

void loop() {
  /*
  if (Serial.available() > 0) {
    // read the incoming byte:
    buffer[pos] = Serial.read();
    if(buffer[pos] == '\n') {
      for(int i = 0, digit = 0; i < pos; ++i) {
        int val = buffer[i] - 0x30;
        if (val >= 0 && val <= 9) {
          lc.setDigit(0, digit, val, buffer[i+1] == '.');
          ++digit;
        }
      }
      pos = 0;
    } else if (pos >= SERIAL_BUF_SIZE) {
      pos = 0;
    } else {
      ++pos;
    }
  }*/

  small_enc.scan();
  large_enc.scan();

  if (frequency != old_frequency) {
    itoa(frequency, buffer, 10);
    for(int i = 0, digit = 0; i < 5; ++i) {
      int val = buffer[i] - 0x30;
      if (val >= 0 && val <= 9) {
        lc.setDigit(0, digit, val, digit == 2);
        ++digit;
      }
    }
  }
  old_frequency = frequency;
  delay(1);
}
