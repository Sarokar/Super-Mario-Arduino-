#include <Adafruit_GrayOLED.h>
#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
//#include <Vector2.hpp>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>


// Declare LCD object for software SPI
// Adafruit_PCD8544(CLK,DIN,D/C,CE,RST);
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

//mario position
unsigned long playerX;
unsigned long playerY;

unsigned int i;

//input
bool mvmt = 0;
unsigned int jump = 0;
bool iteration = 0;
int statusA = 0;
signed int VRx = A1;
signed int VRy = A0;
 unsigned int xPosition = 0;
 unsigned int xPosition2 = 0;
unsigned int yPosition = 0;
signed int xDir = 0;
signed int offset = 4;
int last_posX = 1;
bool inAir = 0;
int last_posY = display.height()-18;
//Vector2f player_pos(0,display.height()-18);

unsigned int yDir=0;
unsigned int start = 0;
unsigned int rBound = 80;
unsigned int moveDir = 0;
unsigned int jmpFrame = 0;
#define a2 A2

unsigned int xMax  = display.width()/2+2;
unsigned int xMin  = 0;



const unsigned char map1 [] PROGMEM = {
  0xff, 
  0x89, 
  0x89, 
  0xff, 
  0x91, 
  0x91, 
  0x91, 
  0xff};

const unsigned char map2 [] PROGMEM = {
0xff, 
0x47, 
0x47, 
0x47, 
0x47, 
0xff, 
0x26, 
0x26};

const unsigned char MarioLeft [] PROGMEM = {
0x00, 0x00, 0x07, 0xe0, 0x18, 0x10, 0x23, 0xc8, 0x1d, 0x38, 0x21, 0x64, 0x22, 0x64, 0x1f, 0x18, 
  0x08, 0x30, 0x07, 0xc8, 0x09, 0x84, 0x0f, 0xf4, 0x0d, 0x88, 0x0e, 0x48, 0x04, 0x30, 0x03, 0xe0
};

const unsigned char clearFrame [] PROGMEM = {
  0x00, 0x00, 
  0x00, 0x00 
};

const unsigned char marioJump [] PROGMEM = {
  0x07, 0xce, 
  0x08, 0x31, 
  0x11, 0xc9, 
  0x1e, 0xba, 
  0x26, 0x86, 
  0x26, 0x46, 
  0x18, 0xfc, 
  0x0c, 0x14, 
  0x3f, 0xe8, 
  0x71, 0x9e, 
  0x89, 0x69, 
  0x8b, 0xf1, 
  0x7f, 0xf2, 
  0x8f, 0xf2, 
  0x9f, 0x8c, 
  0x6e, 0x00
};

const unsigned char marioWalk [] PROGMEM = {
  0x07, 0xc0, 
  0x08, 0x38, 
  0x13, 0xc4, 
  0x1c, 0xb8, 
  0x26, 0x84, 
  0x26, 0x44, 
  0x18, 0xf8, 
  0x1c, 0x10, 
  0x63, 0xf8, 
  0x91, 0x9c, 
  0x8b, 0xfa, 
  0x4f, 0x6a, 
  0x3f, 0xf4, 
  0x4f, 0xc4, 
  0x44, 0x88, 
  0x38, 0x70
};

const unsigned char marioLeft [] PROGMEM = {
  0x00, 0x00, 
  0x07, 0xe0, 
  0x18, 0x10, 
  0x23, 0xc8, 
  0x1d, 0x38, 
  0x21, 0x64, 
  0x22, 0x64, 
  0x1f, 0x18, 
  0x08, 0x30, 
  0x07, 0xc8, 
  0x09, 0x84, 
  0x0f, 0xf4, 
  0x0d, 0x88, 
  0x0e, 0x48, 
  0x04, 0x30, 
  0x03, 0xe0  
};

const unsigned char marioWalkLeft [] PROGMEM = {
 0x03, 0xe0, 
 0x1c, 0x10, 
  0x23, 0xc8, 
  0x1d, 0x38, 
  0x21, 0x64, 
  0x22, 0x64, 
  0x1f, 0x18, 
  0x78, 0x3e, 
  0x97, 0xc9, 
  0x99, 0x89, 
  0x5f, 0xca, 
  0x36, 0xfc, 
  0x2f, 0xfc, 
  0x23, 0xf2, 
  0x11, 0x22, 
  0x0e, 0x1c
};

const unsigned char marioJumpLeft [] PROGMEM = {
  0x73, 0xe0, 
  0x8c, 0x10, 
  0x93, 0x88, 
  0x5d, 0x78, 
  0x61, 0x64, 
  0x62, 0x64, 
  0x3f, 0x18, 
  0x28, 0x30, 
  0x17, 0xfc, 
  0x79, 0x8e, 
  0x96, 0x91, 
  0x8f, 0xd1, 
  0x4f, 0xfe, 
  0x4f, 0xf1, 
  0x31, 0xf9, 
  0x00, 0x76  
};

const unsigned char marioStandLeft [] PROGMEM = {
  0x00, 0x00, 
  0x07, 0xe0, 
  0x18, 0x10, 
  0x23, 0xc8, 
  0x1d, 0x38, 
  0x21, 0x64, 
  0x22, 0x64, 
  0x1f, 0x18, 
  0x08, 0x30, 
  0x07, 0xc8, 
  0x09, 0x84, 
  0x0f, 0xf4, 
  0x0d, 0x88, 
  0x0e, 0x48, 
  0x04, 0x30, 
  0x03, 0xe0
};
  
const unsigned char Mario [] PROGMEM = {
  0x00, 0x00, 
  0x07, 0xe0, 
  0x08, 0x18, 
  0x13, 0xc4, 
  0x1c, 0xb8, 
  0x26, 0x84, 
  0x26, 0x44, 
  0x18, 0xf8, 
  0x0c, 0x10, 
  0x13, 0xe0, 
  0x21, 0x90, 
  0x2f, 0xf0, 
  0x11, 0xb0, 
  0x12, 0x70, 
  0x0c, 0x20, 
};

void drawPlayer() {
  //non jumping animations
  if (!inAir) {
    
    if (xDir == 0) {
        display.drawBitmap(last_posX, last_posY,  Mario, 16, 16, 1);  
      }
    //walking to the right
    
    else if (xDir == 1) {
      display.drawBitmap(last_posX, last_posY,  marioWalk, 16, 16, 1);
      xDir = 0;
    }
    //walking to the left
    else {
      if (!mvmt) {
        display.drawBitmap(last_posX, last_posY,  marioStandLeft, 16, 16, 1);
      }
      else {
        display.drawBitmap(last_posX, last_posY,  marioWalkLeft, 16, 16, 1);  
        mvmt = 0;
      }     
    }
  }
  else {
    if (jmpFrame <= 2) {
      Serial.println("first 2 jmp frame should display twice: ");
      Serial.println(last_posY);
      
      if (xDir == 1) {
        display.drawBitmap(last_posX, last_posY,  marioJump, 16, 16, 1);
      }
      if (xDir == -1) {
        display.drawBitmap(last_posX, last_posY,  marioJumpLeft, 16, 16, 1);
      }
      
      jmpFrame += 2;  
      }
   // }
    //jmpFrame++;
    if (jmpFrame > 2) {
      Serial.println("last 2 jmp frame should display twice: ");
      
      if (jmpFrame == 4) {
        //Serial.println("jmp=2");
        yDir = 0;
      }
       // reset y movement
      jmpFrame += 2; 
      //Serial.println(jmpFrame); 
      
      last_posY += 4;
      playerY = last_posY;
      Serial.println(last_posY);
      
      if (xDir == 1) {
        display.drawBitmap(last_posX, last_posY,  marioJump, 16, 16, 1);
      }
      if (xDir == -1) {
        display.drawBitmap(last_posX, last_posY,  marioJumpLeft, 16, 16, 1);
      }
      
      if (jmpFrame >= 8) {
        inAir = 0;
        jmpFrame = 0;
      }
    }
  }
  //Serial.println("Player Drawn");
}



typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
} task;

const unsigned short tasksNum = 1;
task tasks[tasksNum];

enum Player_States {Player_init,Player_draw,Player_movement, Player_Move,Player_yMove, Player_update};

int TickFct_Player(int state) { 
  switch(state) {
    case Player_init:
    break;

    case Player_update:
       display.clearDisplay(); 
       //TODO: drawMap

        drawPlayer();

        //mid Air
        if (yDir == 1) {
          state = Player_Move;
          Serial.println("Mid air");
          break;
        }
       
        //movement is present
        //Serial.println(xPosition);
        if (digitalRead(a2) == HIGH) {
          Serial.println("HIGH");
          delay(300);
          if (digitalRead(a2) == LOW) {
            Serial.println("LOW");
            yDir = 1; //recognize a jump is happening 
            inAir = 1;
            state = Player_Move;
            //break;
            
          }
        }
        
        if ((analogRead(VRx) > 900)) {
          Serial.println("Right Joystick Detected");
          xDir = 1;
          state = Player_Move;
          break;
        }
        
        if (analogRead(VRx) < 100) {
          xDir = -1;
          state = Player_Move;
          mvmt = 1;
          break;  
        }

       

    break;

    case Player_draw:

    break;

    case Player_movement:
       //Serial.println("Player_movement1");

      //todo: input controls
      xPosition = analogRead(VRx);
      yPosition = analogRead(VRy);
      //Serial.println(xPosition);
      //start = 0;
      
      
      //right movement
      if (xPosition > 800) {
        break;
      }

      if (xPosition < 450) {
        Serial.println("xmove1L");
        xDir = -1; // movement left
        Serial.println(xDir);
        mvmt = 1;
        mvmt = 1;
        state = Player_Move;
        break;

        
      }
      Serial.println("y dire: ");
      Serial.print(xDir);
      if (digitalRead(a2) == HIGH) {
        Serial.println("Jump Detected");
        yDir = 1;
        mvmt = 1;
        state = Player_yMove;
        break;
      }
      xDir = 0;
      moveDir = 0;
      state = Player_draw;
    break;

    case Player_yMove:
    break;

    default:
    break;
    }




    

  switch(state) {
    case Player_init:
      //default position left of the screen
      //Serial.println("Player_init2");
      Serial.println("Successful init");
      playerX = 1;
      playerY = display.height()-18;
       //int z = 10;

      state = Player_update;
    break;

    case Player_draw:
      
      state = Player_movement;
    break;

    case Player_Move:
        //Serial.println("Calculate Movement");
        //last_posX = ((playerX*0.6)/8);
        if (xDir != 0) {
          offset *= xDir;
          last_posX = playerX+offset;
  //        last_posX *= xDir;
          playerX = last_posX;
          offset *= xDir;
        }

        if (yDir == 1) {
          Serial.println("Calculate Y");
          Serial.println(last_posY);
          Serial.println(playerY);
          //offset *= yDir;
          last_posY = playerY-(offset);
          Serial.println(last_posY);
          playerY = last_posY;
          Serial.println(last_posY);
          //offset *= yDir;  
        }
        //Serial.println(last_posX);
        state = Player_update;
    break;

    default:
    break;
    }

    return state;
}
 
 

    
  


void setup() {
   xPosition = analogRead(VRx);
      yPosition = analogRead(VRy);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(a2, INPUT);
  
  i = 0;
  tasks[i].state = Player_init;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &TickFct_Player; 
  
  // Print a message to the LCD.
  //lcd.print("hello, world!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // print the number of seconds since reset:
  Serial.begin(9600);

  //Initialize Display
  display.begin();

  // you can change the contrast around to adapt the display for the best viewing!
  display.setContrast(57);

  if (statusA == 0) {
  display.clearDisplay();
    statusA++;
  }
  //Serial.println("start");
  
  for (i = 0; i < tasksNum; ++i) {
    if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
    }
  }
  delay(200);
}
