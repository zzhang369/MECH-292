int enableA = 5;          // initializing pin D1 as PWN signal receiver for motor A
int input1A = 1, input2A = 2; // the two logic pins on the WEMOS for motor A

int enableB = 7;           // same for motor B
int input1B = 3, input2B = 4; 

void setup() 
{
  // Setting Motor control pins as outputs
  // Motor A
  pinMode (enableA, OUTPUT);  // it is clear that the signal is an output from the WEMOS
  pinMode (input1A, OUTPUT);   // the two logical pins are also set as outputs
  pinMode (input2A, OUTPUT); 

  // Motor B
  pinMode (enableB, OUTPUT); 
  pinMode (input1B, OUTPUT);   
  pinMode (input2B, OUTPUT); 
}

void ConstantSpeed()
{
  // This function will run the car in a straight line
  // hopefully :(
  // Note that the enable variables are pwn signals, hence they are analog signals
  digitalWrite (input1A, HIGH);
  digitalWrite (input2A, LOW);  // Turning on motorA
  analogWrite (enableA, 250); // Setting max speed at 250, where range is from 0-255
  
  digitalWrite (input1B, HIGH);
  digitalWrite (input2B, LOW);
  analogWrite (enableB, 250); // Doing the same for motorB
  delay(2000);
  // Now we have to run he motors inversely, and have them going backwards (or front
  // if the upper lines were running the motors backwards)
  digitalWrite (input1A, LOW);
  digitalWrite (input1B, HIGH); // For motorA
  digitalWrite (input2A, LOW);
  digitalWrite (input2B, HIGH); // For motorB
  delay(2000);

  // Finish by turning off the motors
  digitalWrite (input1A, LOW);
  digitalWrite (input2A, LOW);
  digitalWrite (input1B, LOW);
  digitalWrite (input2B, LOW);
}

void ChangeOfPace()
{
  // This function allows the motors to run across their range of speed 
  // determine by the WEMOS. Here, range is chosen to be from 0-255 as
  // restricted by the WEMOS :D

  // Turn on the motors; direction don't matter.
  digitalWrite (input1A, LOW);
  digitalWrite (input1B, HIGH); // For motorA
  digitalWrite (input2A, LOW);
  digitalWrite (input2B, HIGH); // For motorB

  // Accelerating to max speed allowed by the Wemos (0-255)
  // Note: We could always go higher on speed by inputting
  // more voltage into the motors.
  for (int i = 0; i <= 255; i++)
  {
    analogWrite (enableA, i);
    analogWrite (enableB, i);
    delay(15);
  }
  // Decelerating the motors
  for (int i = 255; i >= 0; --i)
  {
    analogWrite (enableA, i);
    analogWrite (enableB, i);
    delay(15);
  }
  // Once again, we have to turn off the motors
  digitalWrite (input1A, LOW);
  digitalWrite (input2A, LOW);
  digitalWrite (input1B, LOW);
  digitalWrite (input2B, LOW);
}

void loop() 
{
 ConstantSpeed();
 delay(1500);
 ChangeOfPace();
 delay(1500);
}
