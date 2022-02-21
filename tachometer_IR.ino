// tachometer using IR sensor and arduino
// goku-g

const int dataIN = 2; //IR sensor INPUT

int rpm; // RPM value

unsigned long prevmillis; // To store time
unsigned long duration; // To store time difference
unsigned long refresh; // To store time for refresh of reading

boolean currentstate; // Current state of IR input scan
boolean prevstate; // State of IR sensor in previous scan

int measure_rpm(int data_pin)
{
  
  int rpm_value;
  
  // RPM Measurement
  currentstate = digitalRead(data_pin); // Read IR sensor state
  if( prevstate != currentstate) // If there is change in input
   {
     if( currentstate == HIGH ) // If input only changes from LOW to HIGH
       {
         duration = ( micros() - prevmillis ); // Time difference between revolution in microsecond
         rpm_value = (60000000/duration); // rpm = (1/ time millis)*1000*1000*60;
         prevmillis = micros(); // store time for nect revolution calculation
       }
   }
  prevstate = currentstate; // store this scan (prev scan) data for next scan
  
  // LCD Display
  if( ( millis()-refresh ) >= 100 )
    {
       return rpm_value;
       //Serial.println(rpm);  
    }
}

void setup() {
  
  pinMode(dataIN,INPUT);
  prevmillis = 0;
  prevstate = LOW;  
  Serial.begin(115200); // baud rate

}

void loop() {
  
  rpm = measure_rpm(dataIN);
  Serial.print("RPM = ");
  Serial.println(rpm);

}
