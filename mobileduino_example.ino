/*
 Mobileduino V2.0
 
 Example code for Mobileduino - RC car to Robot conversion kit by Techjango
 http://techjango.com/
 
 Project Group
 http://techjango.com/group/mobileduino
 
 Eagle Design files
 https://github.com/TechJango/Mobileduino
 
 Created 20 April 2013
 by Daniyal Ahmed
 Modified 4 May 2013
 by Azam Shahani
 
 This example code is in the public domain.

*/

#include "Ultrasonic.h"
#include <Ultrasonic.h>

Ultrasonic ultrasonic(1,7);

//==========================================================
// RC and Proximity Variables
//==========================================================

long duration, inches, cm_back, cm_front, cm_right, cm_left;
int test, number, turn;
int speed_control = A0;
float speed_value = 0;
int speed_value1 = 0;
int distance_control = A1;
float distance_value = 0;
int distance_value1 = 0;
double value = 1000;
int trig_1 = 1;
int trig_2 = trig_1;
int trig_3 = trig_2;
int trig_4 = trig_3;

int echo_back = 0;
int echo_front = 7;

int backward = 3;
int forward = 5;
int left = 2;
int right = 4;

int pin_1 = 11;
int pin_2 = 10;

int dip1 = 8;
int dip2 = 12;
int dip1_state;
int dip2_state;

int rc_mode = 0;
int in_rc_mode = 0;
int sensor_mode = 0;
int in_sensor_mode = 0;
int heat_mode = 0;
int in_heat_mode = 0;
int light_mode = 0;
int in_light_mode = 0;

unsigned long duration_1;
unsigned long duration_2;
unsigned long duration_1_c = 0;
unsigned long duration_2_c = 0;

//====================================================
//============Heat Variables==========================
//====================================================

float difference_heat;
int therm1;
int therm2;
float temp1 = 0;
float temp2 = 0; 
int one_big_t = 0;
int two_big_t = 0;
#define THERM_PIN1   2  
#define THERM_PIN2   3
int avg_temp = 100;
const int temps[] PROGMEM = { 0, 1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 143, 144, 145, 146, 147, 148, 149, 150, 151, 151, 152, 153, 154, 155, 156, 157, 158, 159, 159, 160, 161, 162, 163, 164, 165, 166, 167, 167, 168, 169, 170, 171, 172, 173, 174, 175, 175, 176, 177, 178, 179, 180, 181, 182, 182, 183, 184, 185, 186, 187, 188, 189, 190, 190, 191, 192, 193, 194, 195, 196, 197, 197, 198, 199, 200, 201, 202, 203, 204, 205, 205, 206, 207, 208, 209, 210, 211, 212, 212, 213, 214, 215, 216, 217, 218, 219, 220, 220, 221, 222, 223, 224, 225, 226, 227, 228, 228, 229, 230, 231, 232, 233, 234, 235, 235, 236, 237, 238, 239, 240, 241, 242, 243, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 252, 253, 254, 255, 256, 257, 258, 259, 260, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 332, 333, 334, 335, 335, 336, 337, 338, 339, 340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382, 383, 384, 385, 386, 387, 388, 389, 390, 392, 393, 394, 395, 396, 397, 398, 399, 400, 401, 402, 403, 404, 405, 406, 407, 408, 410, 411, 412, 413, 414, 415, 416, 417, 418, 419, 420, 422, 423, 424, 425, 426, 427, 428, 429, 430, 432, 433, 434, 435, 436, 437, 438, 439, 441, 442, 443, 444, 445, 446, 448, 449, 450, 451, 452, 453, 455, 456, 457, 458, 459, 460, 462, 463, 464, 465, 466, 468, 469, 470, 471, 472, 474, 475, 476, 477, 479, 480, 481, 482, 484, 485, 486, 487, 489, 490, 491, 492, 494, 495, 496, 498, 499, 500, 501, 503, 504, 505, 507, 508, 509, 511, 512, 513, 515, 516, 517, 519, 520, 521, 523, 524, 525, 527, 528, 530, 531, 532, 534, 535, 537, 538, 539, 541, 542, 544, 545, 547, 548, 550, 551, 552, 554, 555, 557, 558, 560, 561, 563, 564, 566, 567, 569, 570, 572, 574, 575, 577, 578, 580, 581, 583, 585, 586, 588, 589, 591, 593, 594, 596, 598, 599, 601, 603, 604, 606, 608, 609, 611, 613, 614, 616, 618, 620, 621, 623, 625, 627, 628, 630, 632, 634, 636, 638, 639, 641, 643, 645, 647, 649, 651, 653, 654, 656, 658, 660, 662, 664, 666, 668, 670, 672, 674, 676, 678, 680, 683, 685, 687, 689, 691, 693, 695, 697, 700, 702, 704, 706, 708, 711, 713, 715, 718, 720, 722, 725, 727, 729, 732, 734, 737, 739, 741, 744, 746, 749, 752, 754, 757, 759, 762, 764, 767, 770, 773, 775, 778, 781, 784, 786, 789, 792, 795, 798, 801, 804, 807, 810, 813, 816, 819, 822, 825, 829, 832, 835, 838, 842, 845, 848, 852, 855, 859, 862, 866, 869, 873, 877, 881, 884, 888, 892, 896, 900, 904, 908, 912, 916, 920, 925, 929, 933, 938, 942, 947, 952, 956, 961, 966, 971, 976, 981, 986, 991, 997, 1002, 1007, 1013, 1019, 1024, 1030, 1036, 1042, 1049, 1055, 1061, 1068, 1075, 1082, 1088, 1096, 1103, 1110, 1118, 1126, 1134, 1142, 1150, 1159, 1168, 1177, 1186, 1196, 1206, 1216, 1226, 1237, 1248, 1260, 1272, 1284, 1297, 1310, 1324, 1338, 1353, 1369, 1385, 1402, 1420, 1439, 1459, 1480, 1502 };

//====================================================
//============Light Variables=========================
//====================================================

float difference_light;
int light1;
int light2;
float light_reading_1 = 0;
float light_reading_2 = 0; 
int one_big_l = 0;
int two_big_l = 0;
#define light_pin1   4 
#define light_pin2   5
int avg_light = 100;

//====================================================

void setup()
{
  
  pinMode (pin_1, INPUT);
  pinMode (pin_2, INPUT);
  
  pinMode (dip1, INPUT);
  pinMode (dip2, INPUT);
  
  pinMode (backward, OUTPUT);
  pinMode (forward, OUTPUT);
  pinMode (left, OUTPUT);
  pinMode (right, OUTPUT);
  
  delay(100);
  
  //Serial.begin(57600);
  digitalWrite(backward, LOW);
  digitalWrite(forward, LOW);
  digitalWrite(left, LOW);
  digitalWrite(right, LOW);
  

  dip1_state = digitalRead(dip1);
  dip2_state = digitalRead(dip2);
  
  calib();
  
  if (dip2_state == LOW && dip1_state == LOW)
    {     
      rc_mode = 1;
      calibrate();
    }
  if (dip2_state == LOW && dip1_state == HIGH)
    {     
      sensor_mode = 1;
    }
  if (dip2_state == HIGH && dip1_state == LOW)
    {
      heat_mode = 1;
    }
  if (dip2_state == HIGH && dip1_state == HIGH)
    {
      light_mode = 1;
    }
  
  if (heat_mode)
  {
    for (int a=0; a<avg_temp; a++)
        {
          therm1=analogRead(THERM_PIN1)-238;
          therm1=pgm_read_word(&temps[therm1]);
          temp1 = temp1 + therm1;
          therm2=analogRead(THERM_PIN2)-238;
          therm2=pgm_read_word(&temps[therm2]);
          temp2 = temp2 + therm2;
        }
    temp1 = temp1 / avg_temp;
    temp2 = temp2 / avg_temp;
    if (temp1 >= temp2)
    {
      difference_heat = temp1 - temp2;
      one_big_t = 1;
    }
    else
    {
      difference_heat = temp2 - temp1;
      two_big_t = 1;
    }
  }  
    
}

void loop()
{
    
  if (rc_mode)
  {
    calib();      
    drive_car();
    steer_car();       
  }
  
  if (heat_mode)
  {
    heat();
  }
  
  if (light_mode)
  {
    light();
  }
  
  if (sensor_mode)
  {
    sensor();                   
  }
}

void calib()
{
  speed_value = analogRead (speed_control);
  speed_value1 = map(speed_value, 0, 1023, 0, 255);
  
  distance_value = analogRead (distance_control);
  distance_value1 = map(distance_value, 0, 1023, 0, 20);
}

//====================================================================
//=================== RC - Functions =================================
//====================================================================

void calibrate()
{
    delay(1000);
    
    for(int a=0; a<10; a++)
    {      
      duration_1_c = duration_1_c + pulseIn (pin_1, HIGH);
      duration_2_c = duration_2_c + pulseIn (pin_2, HIGH);
    }
    
    duration_1_c = map (floor(duration_1_c/10), 1000, 2000, 1, 20);
    duration_2_c = map (floor(duration_2_c/10), 1000, 2000, 1, 20);
}

//====================================================================
void read_receiver()
{
    duration_1 = pulseIn (pin_1, HIGH);
    duration_2 = pulseIn (pin_2, HIGH);
    duration_1 = map (duration_1, 1000, 2000, 1, 20);
    duration_2 = map (duration_2, 1000, 2000, 1, 20);
}

//====================================================================
void drive_car()
{
  read_receiver();
  if (duration_2 >= (duration_2_c+2))
  {
    digitalWrite(forward, LOW); 
    digitalWrite(backward, LOW); 
    
    analogWrite(forward, speed_value1);
  }
  else if (duration_2 <= (duration_2_c-2))
  {
    digitalWrite(forward, LOW); 
    digitalWrite(backward, LOW); 
    
    analogWrite(backward, speed_value1);
  }
  else if ((duration_2 < (duration_2_c+2)) && (duration_2 > (duration_2_c-2)))
  {
    digitalWrite(forward, LOW);
    digitalWrite(backward, LOW);
  }
  else{}
}

//====================================================================
void steer_car()
{
  
  if ((duration_1 < (duration_1_c+3)) && (duration_1 > (duration_1_c-3)))
  {
    digitalWrite(right, LOW);
    digitalWrite(left, LOW);
  }
  else if (duration_1 >= (duration_1_c+3))
  {
    digitalWrite(right, HIGH);
    digitalWrite(left, LOW);
  }
  else if (duration_1 <= (duration_1_c-3))
  {
    digitalWrite(right, LOW);
    digitalWrite(left, HIGH);
  }
  else{}
}


//====================================================================
//=================== Sensor - Functions =============================
//====================================================================

//==================Range Finder 1==================//
/*
void rf_back()
{
  pinMode(trig_1, OUTPUT);
  digitalWrite(trig_1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_1, LOW);
 
  pinMode(echo_back, INPUT);
  duration = pulseIn(echo_back, HIGH);

  cm_back = microsecondsToCentimeters(duration);
}

*/

//==================Range Finder 2==================//

/*
void rf_front()
{
  pinMode(trig_3, OUTPUT);
  digitalWrite(trig_3, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_3, LOW);

  pinMode(echo_front, INPUT);
  duration = pulseIn(echo_front, HIGH);
 
  cm_front = microsecondsToCentimeters(duration);
}


long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

*/

//==================  Sensor Function ==================//
void sensor()
{
      while (ultrasonic.Ranging(CM) <= (50+distance_value1))
      {
      stopp();
      moveBackward();
      turning(0);
      delay(1000);
      stopp();
      moveForward();
      turning(1);
      delay(1000);
      }
      while ((ultrasonic.Ranging(CM) > (50+distance_value1)) && (ultrasonic.Ranging(CM) <= (80+distance_value1)))
      {
      //stopp();
      moveForward();
      turning(1);
      //delay(1000);
      //straight();
      
      }
      stopp();
      while (ultrasonic.Ranging(CM) > (80+distance_value1))
  {
    stopp();
    moveForward();
  }
      
}
//====================================================================
//=================== Heat - Functions ===============================
//====================================================================
void heat()    
  { 
    
    calib();
    analogWrite(forward, speed_value1);
    
    temp1 = 0;
    temp2 = 0; 
    
      for (int a=0; a<avg_temp; a++)
        {
          therm1=analogRead(THERM_PIN1)-238;
          therm1=pgm_read_word(&temps[therm1]);
          temp1 = temp1 + therm1;
          therm2=analogRead(THERM_PIN2)-238;
          therm2=pgm_read_word(&temps[therm2]);
          temp2 = temp2 + therm2;
        }
      
      temp1 = temp1 / avg_temp;  // LEFT
      temp2 = temp2 / avg_temp;  // RIGHT
      if (one_big_t)
        {
          temp2 = temp2 + difference_heat;
        }
      else if (two_big_t)
        {
          temp1 = temp1 + difference_heat;
        }
      temp1 = floor(temp1);
      temp2 = floor(temp2);
      
      if (temp1 > (temp2 + 10))
        {
          digitalWrite(left, HIGH);
          digitalWrite(right, LOW);
        }
      else if (temp2 > (temp1 + 10)) 
        {
          digitalWrite(left, LOW);
          digitalWrite(right, HIGH);
        }
      else
        {
          digitalWrite(left, LOW);
          digitalWrite(right, LOW);
        }
      // Serial.println(temp1);
      // Serial.println(temp2);
    
}

void light()
{
    calib();
    analogWrite(backward, speed_value1);
    
    light_reading_1 = 0;
    light_reading_2 = 0; 
    
    for (int a=0; a<avg_light; a++)
      {
        light1=analogRead(light_pin1);
        light_reading_1 = light1 + light_reading_1;
        light1=analogRead(light_pin2);
        light_reading_2 = light1 + light_reading_2;
      }
    
    light_reading_1 = light_reading_1 / avg_light;
    light_reading_2 = light_reading_2 / avg_light;

    light_reading_1 = floor(light_reading_1);
    light_reading_2 = floor(light_reading_2);
    
     if (light_reading_1 > (light_reading_2 + 50))
        {
          digitalWrite(left, HIGH);
          digitalWrite(right, LOW);
        }
      else if (light_reading_2 > (light_reading_1 + 50)) 
        {
          digitalWrite(left, LOW);
          digitalWrite(right, HIGH);
        }
      else
        {
          digitalWrite(left, LOW);
          digitalWrite(right, LOW);
        }
    
}
  
void moveBackward()
{
  digitalWrite(left, LOW);
  digitalWrite(right, LOW);
  analogWrite(backward, speed_value1);
  digitalWrite(forward, LOW);
}

void turning(int direction)
{
  //int turn=0;
  //number=random (255);
  
  if (direction == 0)
  {
    
    digitalWrite(left, HIGH);
    digitalWrite(right, LOW);
    
  }
  else 
  {
    digitalWrite(left,LOW);
    digitalWrite(right,HIGH);
  }
}

void stopp()
{
  digitalWrite(left, LOW);
  digitalWrite(right, LOW);
  digitalWrite(backward, LOW);
  digitalWrite(forward, LOW);
}

void moveForward()
{
  analogWrite(left, LOW);
  digitalWrite(right, LOW);
  digitalWrite(backward, LOW);
  analogWrite(forward, speed_value1);
}
