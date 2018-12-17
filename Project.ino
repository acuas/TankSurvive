#include "LedMatrix.h"
#include "Timer.h"
#include "LcdDisplayVertical.h"
#include <EEPROM.h>
#define dataInPin 12
#define clkPin 11
#define loadPin 10
#define deviceNumbers 1
#define swPin 8
#define xPin A0
#define yPin A1
#define V0_PIN 9 
#define RS 2
#define EN 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

// game variables
bool isHome = true;
int indexBSOS = 0;
bool isHighScore = true;
unsigned long fpsUpdate = 150;
unsigned long enemySpawnInterval = 1000;
int addr = 0;
int numberOfHighScores = 0;
int highScores[4] = {}; 
int cycle = 0;
int lives = 3;
bool blinkStart = true;
bool blinkScores = true;
bool movedBlink = false;
bool moved = false;
float score = 1.0;
unsigned long level = 0;
bool enemy[8][8];
int enemyRow[8];
unsigned long startTime = millis();

bool levelsMatrix[10][8][8] = {
    {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0, 0, 1},
        {0, 1, 0, 0, 1, 0, 0, 1},
        {0, 1, 0, 0, 0, 1, 0, 1},
        {0, 1, 1, 0, 0, 1, 1, 1},
        {0, 0, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 0, 0, 1, 0, 0, 1},
        {0, 1, 0, 0, 1, 0, 0, 1},
        {0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 1, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    }, 
    {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 1, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 1},
        {0, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0, 0, 1, 1},
        {0, 1, 1, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    }, 
    {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 1, 1, 1, 1},
        {0, 1, 0, 0, 1, 0, 0, 1},
        {0, 1, 0, 0, 1, 0, 0, 1},
        {0, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}  
    }, 
    {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 1, 1, 1},
        {0, 1, 0, 0, 0, 1, 1, 1},
        {0, 1, 1, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    }, 
    {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 0, 0, 1, 0, 0, 1},
        {0, 1, 0, 0, 1, 0, 0, 1},
        {0, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 1, 1, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    }, 
    {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 0, 0, 1, 0, 0, 1},
        {0, 1, 0, 0, 1, 0, 0, 1},
        {0, 1, 1, 1, 1, 0, 1, 1},
        {0, 0, 1, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    },
};

// Arduino Objects
LcdDisplayVertical *lcd = new LcdDisplayVertical(RS, EN, D4, D5, D6, D7);
LedMatrix *ledMatrix = new LedMatrix(dataInPin, clkPin, loadPin, deviceNumbers);
Timer *fps = new Timer(fpsUpdate);

/*
 * sortDesc is a function called repeatedly 
 * by qsort to compare two elements
*/
int sortDesc(const void * a, const void * b) {
    return ( *(int*)b - *(int*)a );
}

/*
 * initialScene is a function that is used to
 * turn off every led from the matrix
*/
void initialScene() {
    ledMatrix->setMatrix(levelsMatrix[0]);
    ledMatrix->drawMatrix();
}

/*
 * incrementLevel is used to move to the next
 * level and update the game variables
*/
void incrementLevel() {
    ++level;

    if (level == 1) { 
        lives = 3;
        score = 1.0;
        lcd->updateScore(score);
        fpsUpdate = 150;
        fps->setInterval(fpsUpdate);
        enemySpawnInterval = 1000;
    }
    else {
        if (level == 10) {
            bool succesMatrix[8][8] = {
                {0, 1, 0, 0, 0, 0, 0, 0},
                {0, 0, 1, 0, 0, 0, 0, 0}, 
                {0, 0, 0, 1, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 0, 0, 0},
                {0, 0, 0, 0, 0, 1, 0, 0},
                {0, 0, 0, 0, 0, 0, 1, 0},
                {0, 0, 0, 0, 0, 1, 0, 0},
                {0, 0, 0, 0, 1, 0, 0, 0}
            };
      
            score = 99;
            updateHighScores();
      
            ledMatrix->setMatrix(succesMatrix);
            ledMatrix->drawMatrix();

            startTime = millis();
            while (millis() - startTime < 3000);
            startTime = millis();
      
            level = 0;
            isHome = true;
            initialScene();
            for (int i = 0; i < 8; ++i) {
                enemyRow[i] = false;
                for (int j = 0; j < 8; ++j)
                    enemy[i][j] = false;
            }
      
            return ;
        }
        else if (level == 5) {
            fpsUpdate = 100;
            fps->setInterval(100);
            enemySpawnInterval = 500;
        }
        else if (level < 5) {
            enemySpawnInterval -= 200;
        }
        else {
            enemySpawnInterval -= 100;
        }  
    }
  
    bool **matrix = ledMatrix->getMatrix();
    bool deepCopyOfMatrix[8][8];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            deepCopyOfMatrix[i][j] = matrix[i][j];
            if (enemy[i][j] == 1) {
                deepCopyOfMatrix[i][j] = 0;
            }
            enemy[i][j] = 0;
        }
        enemyRow[i] = 0;
    }
  
    ledMatrix->setMatrix(levelsMatrix[level]);
    ledMatrix->drawMatrix();

    startTime = millis();
    while (millis() - startTime < 3000);
    startTime = millis();

    ledMatrix->setMatrix(deepCopyOfMatrix);
    ledMatrix->drawMatrix();
}

/*
 * moveRight is used to move the tank to the right
*/
void moveRight() {
    int tmp = ledMatrix->getRightPosition();
    if (tmp >= 1) {
        bool **matrix = ledMatrix->getMatrix();
        matrix[tmp - 1][7] = 1;
        matrix[tmp - 1][6] = 1;
        matrix[tmp][5] = 1;
        matrix[tmp + 1][5] = 0;
        matrix[tmp + 2][7] = 0;
        matrix[tmp + 2][6] = 0;
        ledMatrix->setRightPosition(tmp - 1);
        ledMatrix->setLeftPosition(tmp + 1);
    }
  
}

/*
 moveLeft is used to move the tank to the left
*/
void moveLeft() {
    int tmp = ledMatrix->getLeftPosition();
    if (tmp < 7) {
        bool **matrix = ledMatrix->getMatrix();
        matrix[tmp + 1][7] = 1;
        matrix[tmp + 1][6] = 1;
        matrix[tmp][5] = 1;
        matrix[tmp - 1][5] = 0;
        matrix[tmp - 2][7] = 0;
        matrix[tmp - 2][6] = 0;
        ledMatrix->setLeftPosition(tmp + 1);
        ledMatrix->setRightPosition(tmp - 1);
    }
}

/*
 * checkEnemyRow is used by function generateEnemy 
 * to check if the generated enemy does not block
 * the tank
*/
bool checkEnemyRow(int lin) {
    for (int i = 1; i < 7; ++i) {
        if (enemyRow[i - 1] == 0 && enemyRow[i] == 0 && enemyRow[i + 1] == 0)
            return true;
    }
    return false;
}

/*
 * generateEnemy is used to generate a random enemy
*/
void generateEnemy() {
    int lin;
    bool valid = false;
    do {
        lin = random(8);
        ++enemyRow[lin]; 
        valid = checkEnemyRow(lin);
        --enemyRow[lin];
    } while (!valid);
    
    ++enemyRow[lin];
    enemy[lin][0] = true;
    ledMatrix->setLedOn(lin, 0);
}

/*
 * moveEnemy is used to move the enemy generated 
 * by function generateEnemy and to update the score
*/
bool moveEnemy() {
    bool moved = false;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (enemy[i][j] == true) {
                enemy[i][j] = false;
                moved = true;
                ledMatrix->setLedOff(i, j);
                if (j + 1 < 8) {
                    enemy[i][j + 1] = true;
                    ledMatrix->setLedOn(i, j + 1);
                    ++j;
                }
                else {
                    --enemyRow[i];
                    score += 0.33;
                    lcd->updateScore((int)score);
                    if (((int) score) % 10 == 0) {
                        score += 1.0;
                        incrementLevel();
                    }
                }
            }
        }
    }
    return moved;
}

/*
 * checkCollision is used to check if the enemy overlaps with tank
*/
bool checkCollision() {
    int rightPosition = ledMatrix->getRightPosition();
    bool **matrix = ledMatrix->getMatrix();
    if (matrix[rightPosition][6] == enemy[rightPosition][6] 
        || matrix[rightPosition + 2][6] == enemy[rightPosition][6]
        || matrix[rightPosition + 1][5] == enemy[rightPosition + 1][5]
        || matrix[rightPosition][7] == enemy[rightPosition][7] 
        || matrix[rightPosition + 1][6] == enemy[rightPosition + 1][6]
        || matrix[rightPosition + 1][7] == enemy[rightPosition + 1][7]
        || matrix[rightPosition + 2][7] == enemy[rightPosition + 2][7])
            return true;
    
    return false;
}

/*
 * updateLives is used to decrease the number of lives
*/
void updateLives() {
    --lives;
    lcd->setLives(lives);
    lcd->updateScore(score);
    bool xMatrix[8][8] = {
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 0, 0, 0, 0, 1, 1},
        {0, 0, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 0},
        {1, 1, 0, 0, 0, 0, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1} 
    };

    int rightPosition = ledMatrix->getRightPosition();
    int leftPosition = ledMatrix->getLeftPosition();
    bool matrix[8][8];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            matrix[i][j] = 0;
            enemy[i][j] = 0;
        }
        enemyRow[i] = 0;
    }

    matrix[rightPosition][7] = 1;
    matrix[rightPosition][6] = 1;
    matrix[rightPosition + 1][7] = 1;
    matrix[rightPosition + 1][6] = 1;
    matrix[rightPosition + 1][5] = 1;
    matrix[rightPosition + 2][7] = 1;
    matrix[rightPosition + 2][6] = 1;
  
    ledMatrix->setMatrix(xMatrix);
    ledMatrix->drawMatrix();
  
    startTime = millis();
    while (millis() - startTime < 3000);
    startTime = millis();

    ledMatrix->setMatrix(matrix);
    ledMatrix->drawMatrix();
}

/*
 * updateHighScores is used to write on EEPROM 
 * the array highScores that is updated every
 * time a player loses or wins the game
*/
void updateHighScores() {
    qsort(highScores, numberOfHighScores, sizeof(int), sortDesc);
    if (score > highScores[numberOfHighScores - 1]) {
        if (numberOfHighScores == 3) {
            highScores[numberOfHighScores - 1] = (int)score;
        }
    }
    if (numberOfHighScores < 2) {
        highScores[numberOfHighScores] = (int)score;
        ++numberOfHighScores;
    }

    qsort(highScores, numberOfHighScores, sizeof(int), sortDesc);
    addr = 0;
    EEPROM.write(addr, (byte)numberOfHighScores);
    for (int i = 0; i < numberOfHighScores; ++i) {
        ++addr;
        EEPROM.write(addr, (byte)highScores[i]);    
    }
}

/*
 * gameUpdate is the main function that 
 * is used as a callback for object fps
*/
void gameUpdate() {
    if (millis() - startTime > enemySpawnInterval) {
        generateEnemy();
        startTime = millis();
    }

    if (!checkCollision()) {
        ledMatrix->drawMatrix();
        moveEnemy();
    }
    else {
        if (lives > 1) {
            updateLives();
        }
        else {
            updateHighScores();
            level = 0;
            isHome = true;
            initialScene();
            for (int i = 0; i < 8; ++i) {
                enemyRow[i] = false;
                for (int j = 0; j < 8; ++j)
                    enemy[i][j] = false;
            }
        }
    }
}

/*
 * setup is used to read the highScores array from EEPROM
 * and to establish the contrast for LcdDisplay
*/
void setup() {
    Serial.begin(9600);
    pinMode(swPin, INPUT);
    digitalWrite(swPin, HIGH);
    pinMode(V0_PIN, OUTPUT); 
    analogWrite(V0_PIN, 120);
  
    numberOfHighScores = (int)EEPROM.read(addr);
    ++addr;
    for (int i = 0; i < numberOfHighScores; ++i) {
        highScores[i] = (int)EEPROM.read(addr);
        ++addr;
    }
  
    qsort(highScores, numberOfHighScores, sizeof(int), sortDesc);
    
    // setup initial scene game
    initialScene();
    fps->setOnTimer(&gameUpdate);
    fps->Start();
}

/*
 * loop is a function that is used to read every Timer
 * the input from the joystick
*/
void loop() {
    if (isHome) {
        int direction = 0;
        int yAxis = analogRead(yPin);
        if (!moved && fps->Tick()) {
            if (yAxis < 470) {
                direction = 1;
            }
            if (yAxis > 550) {
                direction = -1;
            }
        }

        if (direction == 0) {
            moved = false;
        } else {
            moved = true;
        }

        if (!moved) {
            int selected = digitalRead(swPin);
    
            if (selected == 0 && indexBSOS == 0) {
                lcd->clearFirstColumn();
                lcd->setLives(lives);
                lcd->updateScore(score);
        
                isHome = false;
                incrementLevel();
                bool matrix[8][8] = {
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 1, 1, 1},
                    {0, 0, 0, 0, 0, 0, 1, 1}
                };

                ledMatrix->setMatrix(matrix);
                ledMatrix->setRightPosition(5);
                ledMatrix->setLeftPosition(7);
                ledMatrix->drawMatrix();
            }
            else if (selected == 0 && indexBSOS == 1) {
                lcd->writeReadedHighScores(numberOfHighScores, highScores);
                startTime = millis(); 
                while (millis() - startTime < 5000);
                startTime = millis();
            }
            else {
                //blink the start
                if (indexBSOS == 0) {
                    if (!blinkScores) {
                        blinkScores = true;
                    }
                    if (millis() - startTime >= 500) {
                        if (blinkStart) {
                            lcd->clearFirstColumn();
                            blinkStart = false;
                        }
                        else {
                            lcd->writeStart();
                            blinkStart = true;
                        }
      
                        if (cycle == 3) {
                            movedBlink = false;
                        }
                        
                        cycle += 1;
                        cycle %= 4;
                        startTime = millis();
                    }
         
                }
                else {
                    if (!blinkStart) {
                        blinkStart = true;
                    }
                    
                    if (millis() - startTime >= 500) {
                        if (blinkScores) {
                            lcd->clearFirstColumn();
                            blinkScores = false;
                        }
                        else {
                            lcd->writeHighScores();
                            blinkScores = true;
                        }
            
                        if (cycle == 3) {
                            movedBlink = false;
                        }
            
                        cycle += 1;
                        cycle %= 4;
                        startTime = millis();
                    }
                }
            }
        }
        else if (!movedBlink) {
            indexBSOS = indexBSOS + 1;
            indexBSOS %= 2;
            movedBlink = true;
            cycle = 0;
        }
    }
    else { 
        int direction = 0;
        int yAxis = analogRead(yPin);
        if (!moved && fps->Tick()) {
            if (yAxis < 470) {
                direction = 1;
                moveRight();
            }
            if (yAxis > 550) {
                direction = -1;
                moveLeft();
            }
        }
        fps->Update();

        if (direction == 0) {
            moved = false;
        } 
        else {
            moved = true;
        }
    }
}
