/*
HC-SR04 Ping distance sensor]
VCC to arduino 5v GND to arduino GND
Echo to Arduino pin 13 Trig to Arduino pin 12
Red POS to Arduino pin 11
Green POS to Arduino pin 10
560 ohm resistor to both LED NEG and GRD power rail
*/
int delayAlpha = 0.5;
int delay_prev = 0;
long overall_c = 1;
long trueAvg = 0;
const int MAX_BUFFERSIZE = 30 ;
int buffer[MAX_BUFFERSIZE];
int trig = 13; // attach pin 3 to Trig
int echo = 12; //attach pin 4 to Echo
int speakerOut = 9;
long counter = 0;

void setup() {
// initialize serial communication:
Serial.begin(112500);
pinMode(echo,INPUT);
pinMode(speakerOut, OUTPUT);
Serial.print("Doing average tests on ");
Serial.print(MAX_BUFFERSIZE);
Serial.println(" readings");
}

void loop()
{
// establish variables for duration of the ping,
// and the distance result in inches and centimeters:
long duration, inches, cm;

// The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
pinMode(trig, OUTPUT);
digitalWrite(trig, LOW);
delayMicroseconds(2);
digitalWrite(trig, HIGH);
delayMicroseconds(5);
digitalWrite(trig, LOW);

// The same pin is used to read the signal from the PING))): a HIGH
// pulse whose duration is the time (in microseconds) from the sending
// of the ping to the reception of its echo off of an object.
duration = pulseIn(echo, HIGH);
int save = duration;
duration = delayAlpha*duration + (1-delayAlpha)*delay_prev;
delay_prev = save;


// convert the time into a distance
inches = microsecondsToInches(duration);
cm = microsecondsToCentimeters(duration);


if(counter == MAX_BUFFERSIZE)
{
  counter = 0;
  int lcounter = 0;
  long sum = 0;
  boolean doLoop = true;
  while(doLoop == true)
  {
    sum = sum + buffer[lcounter];
    lcounter++;
    if(lcounter == MAX_BUFFERSIZE)
    {
      doLoop = false;
    }
  }
  long average = sum/MAX_BUFFERSIZE;
  //Serial.print("Average for the batch: ");
  //Serial.print(average);
  
  trueAvg = ((trueAvg * (overall_c-1)) + average)/(overall_c);
  overall_c++;

  //Serial.print("   Total current average: ");
  //Serial.println(trueAvg);
   
  //tone generator:
  if(average < 446)
{
  noTone(9);
}
else if(563 <= average && average < 1114) // C
{
  tone(9, 261.63);
}
else if(1114 <= average && average < 1575) // D
{
  tone(9, 293.66);
}
else if(1675 <= average && average < 2127) // E
{
  tone(9, 329.63);
}
else if(2227 <= average && average < 2682) // F
{
  tone(9, 349.23);
}
else if(2782 <= average && average < 3253) // G
{
  tone(9, 392.00);
}
else if(3353 <= average && average < 3830) // A
{
  tone(9, 440.00);
}
else if(average  < 3830 && average > 563)
{
  noTone(9);
}
else
{
  //do nothing
}
}
else
{
  Serial.print("Packet:  ");
  Serial.print(counter);
  Serial.print("  ");
  Serial.print(duration);
  Serial.print(" microsecods read...");
  buffer[counter] = duration;
  Serial.print("  buffer with index of ");
  Serial.print(counter);
  Serial.print(" Has been set to:  ");
  Serial.println(buffer[counter]);
  counter++;
  delay(100);
}
}

long microsecondsToInches(long microseconds)
{
// According to Parallax's datasheet for the PING))), there are
// 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
// second). This gives the distance travelled by the ping, outbound
// and return, so we divide by 2 to get the distance of the obstacle.
// See: http://www.parallax.com/dl/docs/prod/acc/28015-PI...
return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return microseconds / 29 / 2;
}

