#include <LSM303AGR_ACC_Sensor.h>


/*
 * To use this, hold the microbit vertically with the usb port on the left
 * Then wave it holding the bottom side.
 */

// Arduino pin values, not actual nrf5 gpio values
#define ROW3 23   
#define COL1 4    
#define COL2 7
#define COL3 3
#define COL4 6
#define COL5 10

#define MESSAGE_LEN 5

int blank[5] = {1,1,1,1,1}; // need this to clear with output_cols()

int letter_S[5][5] = {
  {1,0,1,1,0},
  {0,1,0,1,0},
  {0,1,0,1,0},
  {0,1,0,1,0},
  {0,1,1,0,1}
};

int letter_M[5][5] = {
  {0,0,0,0,0},
  {1,0,1,1,1},
  {1,1,0,1,1},
  {1,0,1,1,1},
  {0,0,0,0,0}
};

int letter_R[5][5] = {
  {0,0,0,0,0},
  {0,1,0,1,1},  
  {0,1,0,1,1},
  {0,1,0,0,1},
  {1,0,1,1,0}
};

int letter_F[5][5] = {
  {0,0,0,0,0},
  {0,1,0,1,1},
  {0,1,0,1,1},
  {0,1,1,1,1},
  {0,1,1,1,1},
};

int (*message[])[5] = {letter_S, letter_M, letter_R, letter_R, letter_F}; // I hope i never have to deal with C types ever again

void output_cols(int output[]) {
  digitalWrite(COL5, output[0]);
  digitalWrite(COL4, output[1]); 
  digitalWrite(COL3, output[2]); 
  digitalWrite(COL2, output[3]); 
  digitalWrite(COL1, output[4]); 
}

LSM303AGR_ACC_Sensor Acc(&Wire1);

int prev_accel = 0;
int current_letter = 0;

void setup() {  
  pinMode(ROW3, OUTPUT);
  digitalWrite(ROW3, HIGH); 
   
  pinMode(COL1, OUTPUT);
  pinMode(COL2, OUTPUT);
  pinMode(COL3, OUTPUT);  
  pinMode(COL4, OUTPUT);  
  pinMode(COL5, OUTPUT);       

  Wire1.begin(); // i2c is on Wire1

  Acc.begin();
  Acc.Enable();
  
}

void loop(){
  int32_t accelerometer[3];
  Acc.GetAxes(accelerometer);

  // show only when acceleration is decreasing
  if (accelerometer[1] < prev_accel) {
    for (int i=0; i<5; i++) {
      output_cols(message[current_letter][i]);
      delay(1);
    }
    current_letter = (current_letter + 1) % MESSAGE_LEN;
    
    output_cols(blank);
    delay(1);
    
  } else {
    current_letter = 0; // reset the count for the next cycle  
  }
  prev_accel = accelerometer[1];
  
}
