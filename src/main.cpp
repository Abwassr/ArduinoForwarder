#include <Arduino.h>
#include <Wire.h>

#define JOY_Y A3
#define JOY_X A1
#define JOY_SW 6

/**
 *? Resources
 *? Wire.h://! https://www.arduino.cc/en/Tutorial/LibraryExamples/MasterReader
 *? String bytes://! https://stackoverflow.com/questions/7743356/length-of-a-c-stdstring-in-bytes
 *? String.length()://! https://www.arduino.cc/reference/en/language/variables/data-types/string/functions/length/
 */

void onWireRequest();

void setup()
{
  Serial.begin(9600);
  Wire.begin(8); // Register as I2C device #8
  Wire.onRequest(onWireRequest);
  pinMode(JOY_Y, INPUT);
  pinMode(JOY_X, INPUT);
  pinMode(JOY_SW, INPUT_PULLUP);
}

// Recursive function to normalize Angles between -180 and 180
double recursiveAngle(double angle)
{
  if (angle < -180)
  {
    return recursiveAngle(angle + 360);
  }
  if (angle > 180)
  {
    return recursiveAngle(angle - 360);
  }
  return angle;
}

// Recursive function to pad a string to a desired length
String padStrLength(String str, int desiredLength)
{
  int length = str.length();
  if (length < desiredLength)
  {
    str.concat("_");
    return padStrLength(str, desiredLength);
  }
  return str;
}

void loop()
{
  /*double joy_y = ((analogRead(JOY_Y) - 519));
  double joy_x = ((analogRead(JOY_X) - 500));
  double angle = recursiveAngle((atan2(joy_x, (joy_y == 0 ? 0.01 : joy_y)) * 180 / PI) - 90);
  bool strongEnougth = abs(joy_x) > 100 || abs(joy_y) > 100;
  String message = "";
  message.concat("[");
  message.concat(strongEnougth ? "X" : " ");
  message.concat("] \t");
  message.concat(joy_y);
  message.concat(" : ");
  message.concat(joy_x);
  message.concat(" ? ");
  message.concat(angle);
  message.concat("°");
  Serial.println(message.c_str());*/

  //? ONLY FOR DEBUGGING
  //onWireRequest();

  delay(100);
}
void onWireRequest()
{
  double joy_y = ((analogRead(JOY_Y) - 519)); // JoyStick data
  double joy_x = ((analogRead(JOY_X) - 500)); // JoyStick data
  String message = "";                        // String initialisieren
  message.concat(joy_x);                      // append joy_x
  message.concat(":");                        // formatting / splitter
  message.concat(joy_y);                      // append joy_y
  message = padStrLength(message, 16);        // pad message to 16bytes //! MAYBE THERE IS A NUL CHARACTER (null terminated string) [,17bytes?]
  Wire.write(message.c_str());                // send C-String over Wire
  Serial.print(message.length());             // print to serial
  Serial.print("bytes : ");                   // print to serial
  Serial.println(message.c_str());            // print to serial
}
