/*
  Arbuboy Game SOS by John Melki-Wegner
  aka Expensive Notes
*/

#include <Arduboy2.h>

Arduboy2 arduboy;
byte grid[8][8];
int px = 0, py = 0;
int myx = 0, myy = 0;
long flashTimer = 0;
int scoreYou = 0, scoreMe = 0;
bool yourTurn = true;
bool gridFilled = false;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(20);
  arduboy.initRandomSeed(); // <-- seed the random number generator
}

void loop() {
  if (!arduboy.nextFrame()) {
    return;
  }
  if (yourTurn) checkButtons();
  else myTurn();
  displayStuff();
}

void checkButtons() {
  arduboy.pollButtons();
  if (arduboy.justPressed(UP_BUTTON)) py--;
  if (arduboy.justPressed(DOWN_BUTTON)) py++;
  if (arduboy.justPressed(LEFT_BUTTON)) px--;;
  if (arduboy.justPressed(RIGHT_BUTTON)) px++;
  if (py < 0)py = 7;
  if (py > 7) py = 0;
  if (px < 0)px = 7;
  if (px > 7)px = 0;
  if (arduboy.justPressed(A_BUTTON) && grid[px][py] == 0) {
    grid[px][py] = 1;
    checkForSOSs();
  }
  if (arduboy.justPressed(B_BUTTON) && grid[px][py] == 0) {
    grid[px][py] = 10;
    checkForSOSo();
  }

  if (arduboy.justPressed(A_BUTTON) && arduboy.justPressed(B_BUTTON)) resetGrid();
  bool temp = filledGrid();
}

void resetGrid() {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      grid[x][y] = 0;
    }
  }
  px = 0;
  py = 0;
  scoreYou = 0;
  scoreMe = 0;
  yourTurn = true;
  gridFilled = false;
}

void displayStuff() {
  arduboy.clear();
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      arduboy.setCursor(x * 8, y * 8);
      if (px == x && py == y) {
        arduboy.setTextColor(BLACK);
        arduboy.setTextBackground(WHITE);
      } else {
        arduboy.setTextColor(WHITE);
        arduboy.setTextBackground(BLACK);
      }
      //flashing my last choice
      if (myx == x && myy == y) {
        flashTimer++;
        if (flashTimer > 10) {
          arduboy.setTextColor(BLACK);
          arduboy.setTextBackground(BLACK);
          flashTimer = 0;
        }
      }
      if (grid[x][y] == 0) {
        arduboy.print(".");
      } else {
        if (grid[x][y] == 1) arduboy.print("s");
        if (grid[x][y] == 10) arduboy.print("o");
        if (grid[x][y] == 0) arduboy.print(".");
      }
    }
  }

  arduboy.setTextColor(WHITE);
  arduboy.setTextBackground(BLACK);
  arduboy.setCursor(70, 0);
  arduboy.print("-= SOS =-");
  arduboy.setCursor(70, 10);
  arduboy.print("You: ");
  arduboy.print(scoreYou);
  arduboy.setCursor(76, 20);
  arduboy.print("Me: ");
  arduboy.print(scoreMe);
  arduboy.setCursor(76, 30);
  arduboy.print(px);
  arduboy.print(" : ");
  arduboy.print(py);
  if (gridFilled) {
    arduboy.setCursor(70, 40);
    arduboy.print("Finished!");
    arduboy.setCursor(70, 50);
    arduboy.print("A+B = new");
  } else {
    arduboy.setCursor(70, 40);
    arduboy.print("Buttons:");
    arduboy.setCursor(70, 50);
    arduboy.print("A= S B= O");
  }
  arduboy.display();
}

void checkForSOSs() {
  bool found = false;
  if (px <= 5 && grid[px][py] == 1 &&  grid[px + 1][py] == 10 && + grid[px + 2][py] == 1) {
    found = true; //horizontal right
    scoreYou++;
  }
  if (px >= 2 && grid[px][py] == 1 && grid[px - 1][py] == 10 && grid[px - 2][py] == 1) {
    found = true; //horizontal left
    scoreYou++;
  }
  if (py >= 2 && grid[px][py] == 1 && grid[px][py - 1] == 10 && grid[px][py - 2] == 1) {
    found = true; //vertical up
    scoreYou++;
  }
  if (py <= 5 && grid[px][py] == 1 && grid[px][py + 1] == 10 && grid[px][py + 2] == 1) {
    found = true; //vertical down
    scoreYou++;
  }
  if (px <= 5 && py >= 2 && grid[px][py] == 1 && grid[px + 1][py - 1] == 10 && grid[px + 2][py - 2] == 1) {
    found = true; //diagonal up right
    scoreYou++;
  }
  if (px <= 5 && py <= 5 && grid[px][py] == 1 && grid[px + 1][py + 1] == 10 && grid[px + 2][py + 2] == 1) {
    found = true; //diagonal down right
    scoreYou++;
  }
  if (px >= 2 && py >= 2 && grid[px][py] == 1 && grid[px - 1][py - 1] == 10 && grid[px - 2][py - 2] == 1) {
    found = true; //diagonal up left
    scoreYou++;
  }
  if (px >= 2 && py <= 5 && grid[px][py] == 1 && grid[px - 1][py + 1] == 10 && grid[px - 2][py + 2] == 1) {
    found = true; //diagonal down left
    scoreYou++;
  }
  yourTurn = found;
}

void  checkForSOSo() {
  bool found = false;
  if (px <= 6 && px >= 1 && grid[px - 1][py] == 1 && grid[px][py] == 10 && grid[px + 1][py] == 1) {
    found = true; //horizontal
    scoreYou++;
  }
  if (py <= 6 && py >= 1 && grid[px][py - 1] == 1 && grid[px][py] == 10 && grid[px][py + 1] == 1) {
    found = true; //vertical
    scoreYou++;
  }
  if (px >= 1 && px <= 6 && py >= 1 && py <= 6 &&  grid[px + 1][py - 1] == 1 && grid[px][py] == 10 && grid[px - 1][py + 1] == 1) {
    found = true; //diag up right
    scoreYou++;
  }
  if (px >= 1 && px <= 6 && py >= 1 && py <= 6 &&  grid[px - 1][py - 1] == 1 && grid[px][py] == 10 && grid[px + 1][py + 1] == 1) {
    found = true; //diag down right
    scoreYou++;
  }
  yourTurn = found;
}

void myTurn() {
  checkMySOS();
  if (yourTurn) chooseRandomSpot();
}

bool checkMySOS() {
  yourTurn = true;
  //check for any wins
  //Horizontal checks
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 6; x++) {
      //s-s
      if ( grid[x][y] +  grid[x + 2][y] == 2 &&  grid[x + 1][y] == 0) {
        grid[x + 1][y] = 10;
        scoreMe++;
        yourTurn = false;
      }
      //so-
      if ( grid[x][y] == 1 &&  grid[x + 1][y] == 10 &&  grid[x + 2][y] == 0) {
        grid[x + 2][y] = 1;
        scoreMe++;
        yourTurn = false;
      }
      //-os
      if (grid[x][y] == 0 && grid[x + 1][y] == 10 && grid[x + 2][y] == 1) {
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
      if ( grid[x][y] +  grid[x][y + 2] == 2 &&  grid[x][y + 1] == 0) {
        grid[x][y + 1] = 10;
        scoreMe++;
        yourTurn = false;
      }
      //so-
      if ( grid[x][y] == 1 &&  grid[x][y + 1] == 10 &&  grid[x][y + 2] == 0) {
        grid[x][y + 2] = 1;
        scoreMe++;
        yourTurn = false;
      }
      //-os
      if (grid[x][y] == 0 && grid[x][y + 1] == 10 && grid[x][y + 2] == 1) {
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
      if ( grid[x][y] +  grid[x + 2][y + 2] == 2 &&  grid[x + 1][y + 1] == 0) {
        grid[x + 1][y + 1] = 10;
        scoreMe++;
        yourTurn = false;
      }
      //so-
      if ( grid[x][y] == 1  &&  grid[x + 1][y + 1] == 10 && grid[x + 2][y + 2] == 0) {
        grid[x + 2][y + 2] = 1;
        scoreMe++;
        yourTurn = false;
      }
      //-os
      if ( grid[x][y] == 0  &&  grid[x + 1][y + 1] == 10 && grid[x + 2][y + 2] == 1) {
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
      if ( grid[x][y] +  grid[x + 2][y - 2] == 2 &&  grid[x + 1][y - 1] == 0) {
        grid[x + 1][y - 1] = 10;
        scoreMe++;
        yourTurn = false;
      }
      //so-
      if ( grid[x][y] == 1  &&  grid[x + 1][y - 1] == 10 && grid[x + 2][y - 2] == 0) {
        grid[x + 2][y - 2] = 1;
        scoreMe++;
        yourTurn = false;
      }
      //-os
      if ( grid[x][y] == 0  &&  grid[x + 1][y - 1] == 10 && grid[x + 2][y - 2] == 1) {
        grid[x][y] = 1;
        scoreMe++;
        yourTurn = false;
      }
    }
  }
}

void chooseRandomSpot() {
  //are there any spaces left?
  if (filledGrid()) return;
  do {
    myx = random(8);
    myy = random(8);
  } while (grid[myx][myy] != 0);
  if (random(2) == 0) grid[myx][myy] = 1;
  else grid[myx][myy] = 10;
}

bool filledGrid() {
  gridFilled = true;
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      if (grid[x][y] == 0) {
        gridFilled = false;
        return false;
      }
    }
  }
  return true;
}
