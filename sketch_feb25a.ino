#include <LSM303AGR_ACC_Sensor.h>

/*
 * To use this, hold the microbit horizontally with the pads facing up.
 * Then wave it holding the usb cable.
 */

// Arduino pin values, not actual nrf5 gpio values
#define COL3 3   
#define ROW1 21    
#define ROW2 22
#define ROW3 23
#define ROW4 24
#define ROW5 25

#define MESSAGE_LEN 5

int blank[5] = {0,0,0,0,0}; // need this to clear with output_cols()

int letter_S[5][5] = {
  {0,1,0,0,1},
  {1,0,1,0,1},
  {1,0,1,0,1},
  {1,0,1,0,1},
  {1,0,0,1,0}
};

int letter_M[5][5] = {
  {1,1,1,1,1},
  {0,1,0,0,0},
  {0,0,1,0,0},
  {0,1,0,0,0},
  {1,1,1,1,1}
};

int letter_R[5][5] = {
  {1,1,1,1,1},
  {1,0,1,0,0},  
  {1,0,1,0,0},
  {1,0,1,1,0},
  {0,1,0,0,1}
};

int letter_F[5][5] = {
  {1,1,1,1,1},
  {1,0,1,0,0},
  {1,0,1,0,0},
  {1,0,0,0,0},
  {1,0,0,0,0},
};

int (*message[])[5] = {letter_S, letter_M, letter_R, letter_R, letter_F}; // I hope i never have to deal with C types ever again

void output_cols(int output[]) {
  digitalWrite(ROW5, output[0]);
  digitalWrite(ROW4, output[1]); 
  digitalWrite(ROW3, output[2]); 
  digitalWrite(ROW2, output[3]); 
  digitalWrite(ROW1, output[4]); 
}

LSM303AGR_ACC_Sensor Acc(&Wire1);

int prev_accel = 0;
int current_letter = 0;

void setup() {  
  pinMode(COL3, OUTPUT);
  digitalWrite(COL3, LOW); // since this is a matrix, column needs to be grounded
   
  pinMode(ROW1, OUTPUT);
  pinMode(ROW2, OUTPUT);
  pinMode(ROW3, OUTPUT);  
  pinMode(ROW4, OUTPUT);  
  pinMode(ROW5, OUTPUT);        

  Wire1.begin(); // i2c is on Wire1

  Acc.begin();
  Acc.Enable();
  
}

void loop(){
  int32_t accelerometer[3];
  Acc.GetAxes(accelerometer);

  // show only when acceleration is decreasing
  if (accelerometer[0] < prev_accel) {
    for (int i=0; i<5; i++) {
      output_cols(message[current_letter][i]);
      delay(1);
    }
    current_letter = (current_letter + 1) % MESSAGE_LEN;
    
    output_cols(blank);
    delay(2);
    
  } else {
    current_letter = 0; // reset the count for the next cycle  
  }
  prev_accel = accelerometer[0];
  
}
