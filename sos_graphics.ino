/*
  Arbuboy Game SOS by John Melki-Wegner
  aka Expensive Notes
  version 3 with some Sprites
  And different levels where the Arduboy has more or less ability
  Level 1: Arduboy is silly and gives up SOSs and misses all SOSs
  Level 2: Arduboy is normal & doesn't give free SOSs - Misses half SOSs
  Level 3: Arduboy is alert & doesn't give free SOSs - Doesn't miss any SOSs

  8x8 Grid contains:
  1 - Cell is an S
  2 - Cell is an O
  10 - Free cell with no gifted SOSs
  20 - If S is placed in Cell SOS is gifted to player
  30 - If O is placed in Cell SOS is gifted to player

*/

#include <Arduboy2.h>

Arduboy2 arduboy;
Sprites sprites;
const uint8_t PROGMEM RightSide[] = {
  64, 64,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x08, 0x08, 0x10, 0x20, 0x20, 0x10, 0x08, 0x04, 0x04, 0x08, 0x10, 0x00, 0x00, 0x00, 0x46, 0x89, 0x91, 0x91, 0x62, 0x00, 0x7c, 0x82, 0x82, 0x82, 0x7c, 0x00, 0x46, 0x89, 0x91, 0x91, 0x62, 0x00, 0x00, 0x00, 0x10, 0x08, 0x04, 0x04, 0x08, 0x10, 0x20, 0x20, 0x10, 0x08, 0x08, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x01, 0x01, 0x3e, 0x01, 0x01, 0x7e, 0x00, 0x00, 0x38, 0x54, 0x54, 0x54, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x78, 0x08, 0x07, 0x00, 0x00, 0x38, 0x44, 0x44, 0x44, 0x38, 0x00, 0x00, 0x3c, 0x40, 0x40, 0x40, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x02, 0x02, 0x3f, 0x00, 0x00, 0x04, 0x04, 0x24, 0x35, 0x1f, 0x0e, 0x04, 0x00, 0x00, 0x11, 0x22, 0x24, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x22, 0x22, 0x1d, 0x00, 0x00, 0x04, 0x04, 0x24, 0x35, 0x1f, 0x0e, 0x04, 0x00, 0x00, 0x1f, 0x20, 0x20, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const uint8_t PROGMEM dot[] = {
  8, 8,
  0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00,
};

const uint8_t PROGMEM oo[] = {
  8, 8,
  0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x3c, 0x00,
};

const uint8_t PROGMEM ss[] = {
  8, 8,
  0x00, 0x08, 0x54, 0x54, 0x54, 0x54, 0x20, 0x00,
};

const uint8_t PROGMEM ooo[] = {
  8, 8,
  0x00, 0x00, 0x18, 0x24, 0x24, 0x18, 0x00, 0x00,
};

const uint8_t PROGMEM ssss[] = {
  8, 8,
  0x00, 0x00, 0x08, 0x54, 0x54, 0x20, 0x00, 0x00,
};

const uint8_t PROGMEM sel1[] = {
  8, 8,
  0x66, 0x00, 0x00, 0x81, 0x81, 0x00, 0x00, 0x66,
};

const uint8_t PROGMEM sel2[] = {
  8, 8,
  0x33, 0x00, 0x80, 0x80, 0x01, 0x01, 0x00, 0xcc,
};

const uint8_t PROGMEM sel3[] = {
  8, 8,
  0x19, 0x81, 0x80, 0x00, 0x00, 0x01, 0x81, 0x98,
};

const uint8_t PROGMEM sel4[] = {
  8, 8,
  0x8c, 0x81, 0x01, 0x00, 0x00, 0x80, 0x81, 0x31,
};

const uint8_t PROGMEM sel5[] = {
  8, 8,
  0xc6, 0x00, 0x01, 0x01, 0x80, 0x80, 0x00, 0x63,
};

byte grid[8][8];
int px = 0, py = 0;
int myx = 0, myy = 0;
long flashTimer = 0;
int scoreYou = 0, scoreMe = 0;
bool yourTurn = true;
//bool turnToggled = false;
//bool gridFilled = false;
bool choosingALevel = true;
byte level = 1;

int freeCellCount = 64;
int freeSCellCount = 0;
int freeOCellCount = 0;

void setup() {
  //Serial.begin(9600);
  arduboy.begin();
  arduboy.setFrameRate(20);
  arduboy.initRandomSeed(); // <-- seed the random number generator
  resetGrid();
}

void loop() {
  if (!arduboy.nextFrame()) {
    return;
  }
  if (choosingALevel) {
    chooseALevel();
  } else {
    analyseGrid();
    if (yourTurn) checkButtons();
    else myTurn();
  }
  displayStuff();
}

void checkButtons() {
  arduboy.pollButtons();
  if (freeCellCount == 0) {
    if (arduboy.justPressed(A_BUTTON)) {
      resetGrid();
      choosingALevel = true;
      return;
    }
  }
  if (arduboy.justPressed(UP_BUTTON)) py--;
  if (arduboy.justPressed(DOWN_BUTTON)) py++;
  if (arduboy.justPressed(LEFT_BUTTON)) px--;;
  if (arduboy.justPressed(RIGHT_BUTTON)) px++;
  if (py < 0)py = 7;
  if (py > 7) py = 0;
  if (px < 0)px = 7;
  if (px > 7)px = 0;
  if (arduboy.justPressed(A_BUTTON) && grid[px][py] > 9) {
    grid[px][py] = 1; //S placed by player on a free cell
    checkForSOSs();
  }
  if (arduboy.justPressed(B_BUTTON) && grid[px][py] > 9) {
    grid[px][py] = 2; //O placed by player
    checkForSOSo();
  }

  if (arduboy.justPressed(A_BUTTON) && arduboy.justPressed(B_BUTTON)) resetGrid();
  // bool temp = filledGrid();
}

void chooseALevel() {
  arduboy.pollButtons();
  if (arduboy.justPressed(A_BUTTON)) choosingALevel = false;
  if (arduboy.justPressed(UP_BUTTON)) level++;
  if (arduboy.justPressed(DOWN_BUTTON)) level--;
  if (level < 1) level = 1;
  if (level > 3) level = 3;
}

void resetGrid() {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      grid[x][y] = 10; //free cells are 10 or more
    }
  }
  px = 0;
  py = 0;
  scoreYou = 0;
  scoreMe = 0;
  yourTurn = true;
  //  gridFilled = false;
}

void displayStuff() {
  arduboy.clear();
  sprites.drawOverwrite(64, 0, RightSide, 0);

  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      if (myx == x && myy == y) {
        if (flashTimer < 10) {
          if (grid[x][y] > 9) sprites.drawOverwrite(x * 8, y * 8, dot, 0);
          if (grid[x][y] == 1) sprites.drawOverwrite(x * 8, y * 8, ss, 0);
          if (grid[x][y] == 2) sprites.drawOverwrite(x * 8, y * 8, ooo, 0);
        }
      } else {
        if (grid[x][y] > 9) sprites.drawOverwrite(x * 8, y * 8, dot, 0);
        if (grid[x][y] == 1) sprites.drawOverwrite(x * 8, y * 8, ss, 0);
        if (grid[x][y] == 2) sprites.drawOverwrite(x * 8, y * 8, ooo, 0);
        //       if (grid[x][y] == 30) arduboy.drawRect(x * 8, y * 8, 8, 8, WHITE);
      }
      if (px == x && py == y) {
        if (grid[x][y] == 1) sprites.drawOverwrite(x * 8, y * 8, ssss, 0);
        if (flashTimer < 2) sprites.drawSelfMasked(x * 8, y * 8, sel1, 0);
        else if (flashTimer < 5) sprites.drawSelfMasked(x * 8, y * 8, sel2, 0);
        else if (flashTimer < 8) sprites.drawSelfMasked(x * 8, y * 8, sel3, 0);
        else if (flashTimer < 11) sprites.drawSelfMasked(x * 8, y * 8, sel4, 0);
        else if (flashTimer < 14) sprites.drawSelfMasked(x * 8, y * 8, sel5, 0);
        flashTimer++;
        if (flashTimer > 13) flashTimer = 0;
        //Serial.println(flashTimer);
      }
    }
  }
  arduboy.setTextColor(WHITE);
  arduboy.setTextBackground(BLACK);
  arduboy.setCursor(100, 26);
  arduboy.print(scoreYou);
  arduboy.setCursor(70, 27);
  arduboy.print(scoreMe);

  if (freeCellCount == 0) {
    arduboy.setCursor(70, 44);
    arduboy.print("Finished!");
    arduboy.fillRect(64, 54, 64, 10, BLACK);
    arduboy.setCursor(70, 55);
    arduboy.print("A = new");
  }
  //testing
  //  arduboy.setCursor(70, 44);
  //  arduboy.print(freeCellCount);
  //  arduboy.print(" ");
  //  arduboy.print(freeSCellCount);
  //  arduboy.print(" ");
  //  arduboy.print(freeOCellCount);

  if (choosingALevel) {
    arduboy.fillRect(64, 44, 64, 20, BLACK);
    arduboy.setCursor(70, 44);
    arduboy.print("Level?");
    arduboy.setCursor(115, 44);
    arduboy.print(level);
    //arduboy.fillRect(64, 54, 64, 10, BLACK);
    arduboy.setCursor(70, 55);
    arduboy.print("Up/Down");
  }
  arduboy.display();
}

void checkForSOSs() {
  //Has the player made an SOS by placing an S
  bool found = false;
  if (px <= 5 && grid[px][py] == 1 &&  grid[px + 1][py] == 2 && + grid[px + 2][py] == 1) {
    found = true; //horizontal right
    scoreYou++;
  }
  if (px >= 2 && grid[px][py] == 1 && grid[px - 1][py] == 2 && grid[px - 2][py] == 1) {
    found = true; //horizontal left
    scoreYou++;
  }
  if (py >= 2 && grid[px][py] == 1 && grid[px][py - 1] == 2 && grid[px][py - 2] == 1) {
    found = true; //vertical up
    scoreYou++;
  }
  if (py <= 5 && grid[px][py] == 1 && grid[px][py + 1] == 2 && grid[px][py + 2] == 1) {
    found = true; //vertical down
    scoreYou++;
  }
  if (px <= 5 && py >= 2 && grid[px][py] == 1 && grid[px + 1][py - 1] == 2 && grid[px + 2][py - 2] == 1) {
    found = true; //diagonal up right
    scoreYou++;
  }
  if (px <= 5 && py <= 5 && grid[px][py] == 1 && grid[px + 1][py + 1] == 2 && grid[px + 2][py + 2] == 1) {
    found = true; //diagonal down right
    scoreYou++;
  }
  if (px >= 2 && py >= 2 && grid[px][py] == 1 && grid[px - 1][py - 1] == 2 && grid[px - 2][py - 2] == 1) {
    found = true; //diagonal up left
    scoreYou++;
  }
  if (px >= 2 && py <= 5 && grid[px][py] == 1 && grid[px - 1][py + 1] == 2 && grid[px - 2][py + 2] == 1) {
    found = true; //diagonal down left
    scoreYou++;
  }
  yourTurn = found;
  //turnToggled = true;
}

void  checkForSOSo() {
  bool found = false;
  if (px <= 6 && px >= 1 && grid[px - 1][py] == 1 && grid[px][py] == 2 && grid[px + 1][py] == 1) {
    found = true; //horizontal
    scoreYou++;
  }
  if (py <= 6 && py >= 1 && grid[px][py - 1] == 1 && grid[px][py] == 2 && grid[px][py + 1] == 1) {
    found = true; //vertical
    scoreYou++;
  }
  if (px >= 1 && px <= 6 && py >= 1 && py <= 6 &&  grid[px + 1][py - 1] == 1 && grid[px][py] == 2 && grid[px - 1][py + 1] == 1) {
    found = true; //diag up right
    scoreYou++;
  }
  if (px >= 1 && px <= 6 && py >= 1 && py <= 6 &&  grid[px - 1][py - 1] == 1 && grid[px][py] == 2 && grid[px + 1][py + 1] == 1) {
    found = true; //diag down right
    scoreYou++;
  }
  yourTurn = found;
}

void myTurn() {
  checkMySOS();
  if (yourTurn) chooseRandomSpot();
}

void checkMySOS() {
  yourTurn = true;
  //check for any wins
  //Horizontal checks
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 6; x++) {
      //s-s
      if ( grid[x][y] +  grid[x + 2][y] == 2 &&  grid[x + 1][y] > 9) {
        grid[x + 1][y] = 2;
        scoreMe++;
        yourTurn = false;
      }
      //so-
      if ( grid[x][y] == 1 &&  grid[x + 1][y] == 2 &&  grid[x + 2][y] > 9) {
        grid[x + 2][y] = 1;
        scoreMe++;
        yourTurn = false;
      }
      //-os
      if (grid[x][y] > 9 && grid[x + 1][y] == 2 && grid[x + 2][y] == 1) {
        grid[x][y] = 1;
        scoreMe++;
        yourTurn = false;
      }
    }
  }
  //Vertical checks
  for (int y = 0; y < 6; y++) {
    for (int x = 0; x < 8; x++) {
      //s-s
      if ( grid[x][y] +  grid[x][y + 2] == 2 &&  grid[x][y + 1] > 9) {
        grid[x][y + 1] = 2;
        scoreMe++;
        yourTurn = false;
      }
      //so-
      if ( grid[x][y] == 1 &&  grid[x][y + 1] == 2 &&  grid[x][y + 2] > 9) {
        grid[x][y + 2] = 1;
        scoreMe++;
        yourTurn = false;
      }
      //-os
      if (grid[x][y] > 9 && grid[x][y + 1] == 2 && grid[x][y + 2] == 1) {
        grid[x][y] = 1;
        scoreMe++;
        yourTurn = false;
      }
    }
  }
  //diagonal checks
  //down right
  for (int y = 0; y < 6; y++) {
    for (int x = 0; x < 6; x++) {
      //s-s
      if ( grid[x][y] +  grid[x + 2][y + 2] == 2 &&  grid[x + 1][y + 1] > 9) {
        grid[x + 1][y + 1] = 2;
        scoreMe++;
        yourTurn = false;
      }
      //so-
      if ( grid[x][y] == 1  &&  grid[x + 1][y + 1] == 2 && grid[x + 2][y + 2] > 9) {
        grid[x + 2][y + 2] = 1;
        scoreMe++;
        yourTurn = false;
      }
      //-os
      if ( grid[x][y] > 9  &&  grid[x + 1][y + 1] == 2 && grid[x + 2][y + 2] == 1) {
        grid[x][y] = 1;
        scoreMe++;
        yourTurn = false;
      }
    }
  }
  //up right
  for (int y = 2; y < 8; y++) {
    for (int x = 0; x < 6; x++) {
      //s-s
      if ( grid[x][y] +  grid[x + 2][y - 2] == 2 &&  grid[x + 1][y - 1] > 9) {
        grid[x + 1][y - 1] = 2;
        scoreMe++;
        yourTurn = false;
      }
      //so-
      if ( grid[x][y] == 1  &&  grid[x + 1][y - 1] == 2 && grid[x + 2][y - 2] > 9) {
        grid[x + 2][y - 2] = 1;
        scoreMe++;
        yourTurn = false;
      }
      //-os
      if ( grid[x][y] > 9  &&  grid[x + 1][y - 1] == 2 && grid[x + 2][y - 2] == 1) {
        grid[x][y] = 1;
        scoreMe++;
        yourTurn = false;
      }
    }
  }
}


//bool filledGrid() {
//  gridFilled = true;
//  for (int y = 0; y < 8; y++) {
//    for (int x = 0; x < 8; x++) {
//      if (grid[x][y] > 9) {
//        gridFilled = false;
//        return false;
//      }
//    }
//  }
//  return true;
//}


void analyseGrid() {
  //reset analysis
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      if (grid[x][y] > 9) grid[x][y] = 10;
    }
  }

  //===== Place S 2 away from another S ====

  //Horizontal to right - placing S gifts SOS
  for (int x = 2; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      if (grid[x - 2][y] == 1 && grid[x - 1][y] > 9 && grid[x][y] > 9) {
        grid[x][y] = 20;
      }
    }
  }
  //Horizontal to left - placing S gifts SOS
  for (int x = 0; x < 6; x++) {
    for (int y = 0; y < 8; y++) {
      if (grid[x + 2][y] == 1 && grid[x + 1][y] > 9 && grid[x][y] > 9) {
        grid[x][y] = 20;
      }
    }
  }

  //Vertical down - placing S gifts SOS
  for (int x = 0; x < 8; x++) {
    for (int y = 2; y < 8; y++) {
      if (grid[x][y - 2] == 1 && grid[x][y - 1] > 9 && grid[x][y] > 9) {
        grid[x][y] = 20;
      }
    }
  }
  //Vertical to up - placing S gifts SOS
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 6; y++) {
      if (grid[x][y + 2] == 1 && grid[x][y + 1] > 9 && grid[x][y] > 9) {
        grid[x][y] = 20;
      }
    }
  }
  //Diagonal left down - placing S gifts SOS
  for (int x = 0; x < 6; x++) {
    for (int y = 0; y < 6; y++) {
      if (grid[x + 2][y + 2] == 1 && grid[x + 1][y + 1] > 9 && grid[x][y] > 9) {
        grid[x][y] = 20;
      }
    }
  }
  //Diagonal Right Up - placing S gifts SOS
  for (int x = 2; x < 8; x++) {
    for (int y = 2; y < 8; y++) {
      if (grid[x - 2][y - 2] == 1 && grid[x - 1][y - 1] > 9 && grid[x][y] > 9) {
        grid[x][y] = 20;
      }
    }
  }
  //Diagonal left up - placing S gifts SOS
  for (int x = 0; x < 6; x++) {
    for (int y = 2; y < 8; y++) {
      if (grid[x + 2][y - 2] == 1 && grid[x + 1][y - 1] > 9 && grid[x][y] > 9) {
        grid[x][y] = 20;
      }
    }
  }
  //Diagonal Right down - placing S gifts SOS
  for (int x = 2; x < 8; x++) {
    for (int y = 0; y < 6; y++) {
      if (grid[x - 2][y + 2] == 1 && grid[x - 1][y + 1] > 9 && grid[x][y] > 9) {
        grid[x][y] = 20;
      }
    }
  }

  //==== Place O next to S =====

  //Diagonal
  for (int x = 1; x < 7; x++) {
    for (int y = 1; y < 7; y++) {
      if (grid[x - 1][y - 1] == 1 && grid[x + 1][y + 1] > 9 && grid[x][y] > 9) grid[x][y] = 30;
      if (grid[x - 1][y - 1] > 9 && grid[x + 1][y + 1] == 1 && grid[x][y] > 9) grid[x][y] = 30;
      if (grid[x - 1][y + 1] == 1 && grid[x + 1][y - 1] > 9 && grid[x][y] > 9) grid[x][y] = 30;
      if (grid[x - 1][y + 1] > 9 && grid[x + 1][y - 1] == 1 && grid[x][y] > 9) grid[x][y] = 30;
    }
  }
  //Horizontal
  for (int x = 1; x < 7; x++) {
    for (int y = 0; y < 8; y++) {
      if (grid[x - 1][y] == 1 && grid[x + 1][y] > 9 && grid[x][y] > 9) grid[x][y] = 30;
      if (grid[x - 1][y] > 9 && grid[x + 1][y] == 1 && grid[x][y] > 9) grid[x][y] = 30;
    }
  }

  //Vertical
  for (int x = 0; x < 8; x++) {
    for (int y = 1; y < 7; y++) {
      if (grid[x][y - 1] == 1 && grid[x][y + 1] > 9 && grid[x][y] > 9) grid[x][y] = 30;
      if (grid[x][y - 1] > 9 && grid[x][y + 1] == 1 && grid[x][y] > 9) grid[x][y] = 30;
    }
  }

  //=== Place S next to O ======

  //Horizontal to right - placing S gifts SOS
  for (int x = 2; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      if (grid[x - 2][y] > 9 && grid[x - 1][y] == 2 && grid[x][y] > 9) {
        grid[x][y] = 20;
      }
    }
  }
  //Horizontal to left - placing S gifts SOS
  for (int x = 0; x < 6; x++) {
    for (int y = 0; y < 8; y++) {
      if (grid[x + 2][y] > 9 && grid[x + 1][y] == 2 && grid[x][y] > 9) {
        grid[x][y] = 20;
      }
    }
  }

  //Vertical down - placing S gifts SOS
  for (int x = 0; x < 8; x++) {
    for (int y = 2; y < 8; y++) {
      if (grid[x][y - 2] > 9 && grid[x][y - 1] == 2 && grid[x][y] > 9) {
        grid[x][y] = 20;
      }
    }
  }
  //Vertical to up - placing S gifts SOS
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 6; y++) {
      if (grid[x][y + 2] > 9 && grid[x][y + 1] == 2 && grid[x][y] > 9) {
        grid[x][y] = 20;
      }
    }
  }
  //Diagonal left down - placing S gifts SOS
  for (int x = 0; x < 6; x++) {
    for (int y = 0; y < 6; y++) {
      if (grid[x + 2][y + 2] > 9 && grid[x + 1][y + 1] == 2 && grid[x][y] > 9) {
        grid[x][y] = 20;
      }
    }
  }
  //Diagonal Right Up - placing S gifts SOS
  for (int x = 2; x < 8; x++) {
    for (int y = 2; y < 8; y++) {
      if (grid[x - 2][y - 2] > 9 && grid[x - 1][y - 1] == 2 && grid[x][y] > 9) {
        grid[x][y] = 20;
      }
    }
  }
  //Diagonal left up - placing S gifts SOS
  for (int x = 0; x < 6; x++) {
    for (int y = 2; y < 8; y++) {
      if (grid[x + 2][y - 2] > 9 && grid[x + 1][y - 1] == 2 && grid[x][y] > 9) {
        grid[x][y] = 20;
      }
    }
  }
  //Diagonal Right down - placing S gifts SOS
  for (int x = 2; x < 8; x++) {
    for (int y = 0; y < 6; y++) {
      if (grid[x - 2][y + 2] > 9 && grid[x - 1][y + 1] == 2 && grid[x][y] > 9) {
        grid[x][y] = 20;
      }
    }
  }


  //check availabilty of free cells
  checkAvailabiltyofFreeCells();
  //  Serial.print(freeCellCount);
  //  Serial.print("\t");
  //  Serial.print(freeSCellCount);
  //  Serial.print("\t");
  //  Serial.print(freeOCellCount);
  //  Serial.println();
  //printGrid();
}

void checkAvailabiltyofFreeCells() {
  freeCellCount = 0;
  freeSCellCount = 0;
  freeOCellCount = 0;
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      if (grid[x][y] > 9 ) freeCellCount++;
      if (grid[x][y] == 20 ) freeSCellCount++;
      if (grid[x][y] == 30 ) freeOCellCount++;
    }
  }
}
//
//void printGrid() {
//  for (int y = 0; y < 8; y++) {
//    for (int x = 0; x < 8; x++) {
//      Serial.print(grid[x][y]);
//      Serial.print("\t");
//    }
//    Serial.println();
//  }
//  Serial.println();
//}


void chooseRandomSpot() {
  //are there any spaces left?
  if (freeCellCount == 0) return;
  checkAvailabiltyofFreeCells();
  //Level 1 - Dumb - Place on cells that gift an SOS if there any first
  if (level == 1) {
    //Can place a cell in a dumb spot for S or O
    if (freeSCellCount > 0 && freeOCellCount > 0) {
      if (random(2) == 0) chooseFreeSCell();
      else chooseFreeOCell();
      return;
    }
    if (freeSCellCount > 0) {
      chooseFreeSCell();
      return;
    }
    if (freeOCellCount > 0) {
      chooseFreeOCell();
      return;
    }
    //No dumb spots left
    chooseAnyFreeCell();
    return;
  }

  //Level 2
  if (level == 2) {
    chooseAnyFreeCell();
    return;
  }

  //Level 3
  //Choose a non FreeCell if available
  if (freeCellCount > freeSCellCount + freeOCellCount) {
    //There are Cells with a 10
    //Randomness
    if (random(2) == 0) choose10Cell(2);
    else choose10Cell(1);
    return;
  }
  //Last Resort. choose a free SOS Cell!
  chooseAnyFreeCell();
}

void chooseFreeSCell() {
  //Choose a cell that gifts an SOS if placing an S (Grid Cell == 20 does this)
  do {
    myx = random(8);
    myy = random(8);
  } while (grid[myx][myy] != 20);
  grid[myx][myy] = 1; //Place S
}

void chooseFreeOCell() {
  //Choose a cell that gifts an SOS if placing an O (Grid Cell == 30 does this)
  do {
    myx = random(8);
    myy = random(8);
  } while (grid[myx][myy] != 30);
  grid[myx][myy] = 2; //Place O
}

void chooseAnyFreeCell() {
  //Choose any free cell (Grid Cell > 9 does this)
  //Serial.println("--- Any - ");
  do {
    myx = random(8);
    myy = random(8);
  } while (grid[myx][myy] < 10);
  //Serial.println(grid[myx][myy]);
  if (random(2) == 0) grid[myx][myy] = 1;
  else grid[myx][myy] = 2;
}

void choose10Cell(byte gridValue) {
  //Choose any free cell that doesn't gift an SOS (Grid Cell == 10 does this)
  //Serial.print("10 --- ");
  //Serial.println(gridValue);

  if (random(2) == 0) {
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        if (grid[x][y] == 10) {
          grid[x][y] = gridValue;
          myx = x;
          myy = y;
          return;
        }
      }
    }
  } else {
    for (int x = 7; x >= 0; x--) {
      for (int y = 7; y >= 0; y--) {
        if (grid[x][y] == 10) {
          grid[x][y] = gridValue;
          myx = x;
          myy = y;
          return;
        }
      }
    }

  }
}
