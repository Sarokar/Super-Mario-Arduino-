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
bool iteration = 0;
int statusA = 0;
int VRx = A0;
int VRy = A1;
int xPosition = 0;
int yPosition = 0;
int xDir;
int start = 0;
int rBound = 80;
int moveDir = 0;

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
  0x07, 0xc0 
};



void drawMap() {
  Serial.println(moveDir);
  if (moveDir != 2 ) { 
    if (iteration) {
            display.clearDisplay();
            display.drawBitmap(playerX, playerY-6,  Mario, 16, 16, 1);
            //display.print("move");
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map2, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map2, 8, 8, BLACK);
            start += 8;
             display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map2, 8, 8, BLACK);
            start += 8;
            start = 0;
    }
    if (!iteration) {
            display.clearDisplay();
            display.drawBitmap(playerX, playerY-6,  Mario, 16, 16, 1);
            display.drawBitmap(start, display.height()-8,  map2, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map2, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
             display.drawBitmap(start, display.height()-8,  map2, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            start = 0;
    }
  }
  if (moveDir == 2) {
    if (iteration) {
            
            //display.print("moveLeft");
//            display.clearDisplay();
//        display.drawBitmap(playerX, playerY-6,  MarioLeft, 16, 16, 1);
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map2, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map2, 8, 8, BLACK);
            start += 8;
             display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map2, 8, 8, BLACK);
            start += 8;
            start = 0;
    }
    if (!iteration) {
//            display.clearDisplay();
//            display.drawBitmap(playerX, playerY-6,  MarioLeft, 16, 16, 1);
            display.clearDisplay();
              display.drawBitmap(playerX, playerY-6,  MarioLeft, 16, 16, 1);
            display.drawBitmap(start, display.height()-8,  map2, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map2, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
             display.drawBitmap(start, display.height()-8,  map2, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            display.drawBitmap(start, display.height()-8,  map1, 8, 8, BLACK);
            start += 8;
            start = 0;
    }
    
  }
}


typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
} task;

const unsigned short tasksNum = 1;
task tasks[tasksNum];

enum Player_States {Player_init,Player_draw,Player_movement, Player_xMove};

int TickFct_Player(int state) { 
  switch(state) {
    case Player_init:
    Serial.println("ETET");
    //state = Player_init;
    break;

    case Player_draw:
      Serial.println("Player_draw1");
       //state = Player_xMove;
      break;
    break;

    case Player_movement:
            Serial.println("Player_movement1");

      //todo: input controls
      xPosition = analogRead(VRx);
      yPosition = analogRead(VRy);
      Serial.println(xPosition);
      start = 0;
      
      
      //right movement
      if (xPosition > 800) {
        Serial.println("xmove1R");
        xDir = 1; // movement right
       // start -=2;
        state = Player_xMove;
        break;
      }

      if (xPosition < 500) {
        Serial.println("xmove1L");
        xDir = 2; // movement left
        Serial.println(xDir);
        state = Player_xMove;
        break;

        
      }
      xDir = 0;
      moveDir = 0;
      state = Player_draw;
    break;

    default:
    break;
    }

  switch(state) {
    case Player_init:
      //default position left of the screen
      Serial.println("Player_init2");
      playerX = 0;
      playerY = display.height()-18;
       //int z = 10;

      state = Player_draw;
    break;

    case Player_draw:
      Serial.println("Player_draw2");
      //Serial.println(xPosition);
     start = 0;

     Serial.println(xDir);
     Serial.println(moveDir);

      //int j =0;
      //display.clearDisplay();
      //display.drawBitmap(playerX, playerY-6,  Mario, 16, 16, 1);
      //0 - netural
      //1 - right
      //-1 = left

      if (moveDir == 0) {
          Serial.println("mov");
          drawMap();
      }

      if (moveDir == 1) {
        iteration = !iteration;
        drawMap();
//        if (iteration == 1) {
//          rBound = 72;
//          Serial.println("it1");
//          display.clearDisplay();
//          display.drawBitmap(rBound, display.height()-8,  map2, 8, 8, BLACK);
//          rBound -= 8;
//          display.drawBitmap(rBound, display.height()-8,  map1, 8, 8, BLACK);
//          rBound -= 8;
//          display.drawBitmap(rBound, display.height()-8,  map1, 8, 8, BLACK);
//          rBound -= 8;
//          display.drawBitmap(rBound, display.height()-8,  map2, 8, 8, BLACK);
//          rBound -= 8;
//          display.drawBitmap(rBound, display.height()-8,  map1, 8, 8, BLACK);
//          rBound -= 8;
//          display.drawBitmap(rBound, display.height()-8,  map1, 8, 8, BLACK);
//          rBound -= 8;
//           display.drawBitmap(rBound, display.height()-8,  map2, 8, 8, BLACK);
//         rBound -= 8;
//          display.drawBitmap(rBound, display.height()-8,  map1, 8, 8, BLACK);
//          rBound -= 8;
//          display.drawBitmap(rBound, display.height()-8,  map1, 8, 8, BLACK);
//          rBound -= 8;
//          display.drawBitmap(rBound, display.height()-8,  map2, 8, 8, BLACK);
//          display.drawBitmap(playerX, playerY-6,  Mario, 16, 16, 1);
//          iteration++;
//        }
//        if (iteration == 2) {
//          rBound = 72;
//          Serial.println("it1");
//          display.clearDisplay();
//          display.drawBitmap(rBound, display.height()-8,  map1, 8, 8, BLACK);
//         rBound -= 8;
//          display.drawBitmap(rBound, display.height()-8,  map1, 8, 8, BLACK);
//          rBound -= 8;
//          display.drawBitmap(rBound, display.height()-8,  map2, 8, 8, BLACK);
//         rBound -= 8;
//          display.drawBitmap(rBound, display.height()-8,  map1, 8, 8, BLACK);
//          rBound -= 8;
//          display.drawBitmap(rBound, display.height()-8,  map1, 8, 8, BLACK);
//          rBound -= 8;
//          display.drawBitmap(rBound, display.height()-8,  map2, 8, 8, BLACK);
//          rBound -= 8;
//           display.drawBitmap(rBound, display.height()-8,  map1, 8, 8, BLACK);
//          rBound -= 8;
//          display.drawBitmap(rBound, display.height()-8,  map1, 8, 8, BLACK);
//         rBound -= 8;
////          display.drawBitmap(rBound, display.height()-8,  map2, 8, 8, BLACK);
//          rBound -= 8;
//          display.drawBitmap(rBound, display.height()-8,  map1, 8, 8, BLACK);
//          display.drawBitmap(playerX, playerY-6,  Mario, 16, 16, 1);
//          iteration = 1;
//        }   
      }

      if (moveDir == 2) {
        //display.println("??");
        iteration = !iteration;
        display.clearDisplay();
        display.drawBitmap(playerX, playerY-6,  MarioLeft, 16, 16, 1);
        drawMap();
      }

      //display.display();
      state = Player_movement;
    break;

    case Player_xMove:
      Serial.println("xmove2");
      //1 = right
      //0 = left
      if (xDir == 1) {
        Serial.println("+x");
        Serial.println(xPosition);
        if (playerX < xMax) {
          playerX  += 4;
        }
        moveDir = 1;
        state = Player_draw;
        break;
      }

      if (xDir == 2) {
        Serial.println("-x");
        Serial.println(xPosition);
        if (playerX > xMin) {
          playerX  -= 4;
        }
        moveDir = 2;
        state = Player_draw;
      }

      state = Player_draw;
    break;

    default:
    break;
    }

    return state;
}
 
 

    
  


void setup() {
  
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  
  i = 0;
  tasks[i].state = Player_init;
  tasks[i].period = 200;
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
