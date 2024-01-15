#include <Braccio.h>
#include <Servo.h>


Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

int m1 = 90;
int m2 = 90;
int m3 = 90;
int m4 = 90;
int m5 = 90;
int m6 = 73;

void setup() {  
  //Initialization functions and set up the initial position for Braccio
  //All the servo motors will be positioned in the "safety" position:
  //Base (M1):90 degrees
  //Shoulder (M2): 45 degrees
  //Elbow (M3): 180 degrees
  //Wrist vertical (M4): 180 degrees
  //Wrist rotation (M5): 90 degrees
  //gripper (M6): 10 degrees
  Serial.begin(9600); // Initialize serial communication
  Braccio.begin();
  Braccio.ServoMovement(20, m1, m2, m3, m4, m5,  m6);  
}

void loop() {
  /*
   Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
   M1=base degrees. Allowed values from 0 to 180 degrees
   M2=shoulder degrees. Allowed values from 15 to 165 degrees
   M3=elbow degrees. Allowed values from 0 to 180 degrees
   M4=wrist vertical degrees. Allowed values from 0 to 180 degrees
   M5=wrist rotation degrees. Allowed values from 0 to 180 degrees
   M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.
  */
  
  // the arm is aligned upwards  and the gripper is closed
                     //(step delay, M1, M2, M3, M4, M5, M6);
  
 if (Serial.available() > 0) { // Sprawdzenie, czy są dostępne dane do odczytu
    char receivedChar = Serial.read(); // Odczyt pojedynczego znaku
    if (receivedChar == '\0' || receivedChar == ' ') {
      Serial.println("Received character is null.");
    } else {
      Serial.print("Received character: ");
      Serial.println(receivedChar);// Wyświetlenie odebranego znaku
      parseCommand(receivedChar);
    }
    
  }
}
void parseCommand(char command) {
    
  if ( command == 'G') {
    toggleGripper();
  } else if (command == 'H') {
    closeGripper();
  } else if(command == 'Z'){
    rotateLeft();
  } else if(command == 'X'){
    rotateRight();
  }else if(command == 'J'){
    toggleWrist_ver();
  }else if(command == 'K'){
    closeWrist_ver();
  }else if(command == 'Q'){
    toggleWrist_rot();
  }else if(command == 'W'){
    closeWrist_rot();
  }else if(command == 'R'){
    toggleElbow();
  }else if(command == 'T'){
    closeElbow();
  }else if(command == 'O'){
    toggleShoulder();
  }else if(command == 'P'){
    closeShoulder();
  }
  else{
  Serial.print("ERROR");
  }
}
void toggleGripper() {
  // Your gripper control logic here
  // Example: gripper.write(90); // Move gripper to a specific angle
  // Adjust the angle based on your gripper configuration
  delay(1000); // Adjust delay as needed
  gripper.write(10);  // Move gripper to another angle
  // Adjust the angle based on your gripper configuration
  delay(1000); // Adjust delay as needed
}
void closeGripper() {
  // Your gripper control logic here to close the gripper
  gripper.write(73);  // Move gripper to a closed position
  // Adjust the angle based on your gripper configuration
  delay(1000); // Adjust delay as needed
}
void toggleWrist_ver(){
  wrist_ver.write(0);
  delay(1000);
}
void closeWrist_ver(){
  wrist_ver.write(180);
  delay(1000);
}
void rotateLeft(){
  if(m1>=0){
    m1=m1-10;
    base.write(m1);
    //Braccio.ServoMovement(10, m1, m2, m3, m4, m5,  m6);
    delay(1000); // Adjust delay as needed
  }
}
void rotateRight(){
  if(m1>=0){
    m1=m1+10;
    base.write(m1);
    //Braccio.ServoMovement(10, m1, m2, m3, m4, m5,  m6);
    delay(1000); // Adjust delay as needed
  }
}
void toggleWrist_rot(){
  m5=m5+10;
  wrist_rot.write(m5);
}
void closeWrist_rot(){
  m5=m5-10;
  wrist_rot.write(m5);
}
void toggleElbow(){
  m4=m4+10;
  elbow.write(m4);
}
void closeElbow(){
  m4=m4-10;
  elbow.write(m4);
}
void toggleShoulder(){
  m2=m2+10;
  shoulder.write(m2);
}
void closeShoulder(){
  m2=m2-10;
  shoulder.write(m2);
}