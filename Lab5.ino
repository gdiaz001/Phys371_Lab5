/*
CCNY PHYS 37100 
Lab5
*/

// credit: Dr. Hedberg for method of getting more accurate
// readings from analogRead

// to be used in reading data from Analog Out Arduino 
  unsigned long currentTime = 0; 
  unsigned long lastTime = 0;
  const unsigned long intervalBetweenData = 1000;
  
  const int ledPin = 9; //LED connected in pin9
  const int TWOPI = 2 * 3.141529126; 

  int brightness; //brightness level of LED 

//credit David A. Mellis for method of smoothing data 
//obtained from analog Arduino input 
//Example code very similar to this one is in in the public domain.
//https://www.arduino.cc/en/Tutorial/BuiltInExamples/Smoothing
  
  //to be used in smoothing of data 
  
  // Define the number of samples to keep track of. The higher the number, the
  // more the readings will be smoothed, but the slower the output will respond to
  // the input. Using a constant rather than a normal variable lets us use this
  // value to determine the size of the readings array.
  const int numReadings = 100; 
  int readings[numReadings]; // the readings from the analog input
  int readIndex = 0; // the index of the current reading
  int total = 0;   // the average
  int average = 0;  // the average
  
  void setup() {
     
     pinMode(ledPin, OUTPUT);

     //initialize serial communication with computer
     Serial.begin(500000);

    //initialize all the readings to 0 
     for(int thisReading; thisReading < numReadings; thisReading++){
      readings[thisReading] = 0; 
     }
     
    }
   
  void loop() {
   // get the current time in microseconds
    
    currentTime =  micros(); //time since progrm began in microseconds
 
    if (currentTime - lastTime >= intervalBetweenData ) {

      //determine brightness value of LED 
      //brightness = A + B sin(omega*t) 
      brightness = 100 +5*sin(1.0*TWOPI*millis()/1000); 
      
      //change LED's brightness
      analogWrite(ledPin, brightness);

       //read voltage value Vout 
      int sensorValue = analogRead(A1); 
      lastTime += intervalBetweenData;

      //subtract the last reading
      total = total - readings[readIndex]; 
      //read from the sensor
      readings[readIndex] = sensorValue; 
      //add the reading to the total
      total = total + readings[readIndex]; 
      //advance to next position in the array 
      readIndex += 1; 

      //if we're at end of array 
      if(readIndex >= numReadings){
        //go back to the beginning
        readIndex = 0; 
      }

      //calculate the average
      average = total/numReadings; 
      
      Serial.print(currentTime/1000);
      Serial.print(',');
      Serial.println(average);
          }
          
        }
