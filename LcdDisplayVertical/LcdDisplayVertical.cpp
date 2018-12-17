#include "LcdDisplayVertical.h"
#define CGRAMDIM 8

byte S[8] = {
	0b00000,
	0b10010,
	0b10111,
	0b10101,
	0b11101,
	0b11001,
	0b01010,
	0b00000
};

byte T[8] = {
	0b00000,
	0b00011,
	0b10001,
	0b11111,
	0b11111,
	0b10001,
	0b00011,
	0b00000
};

byte A[8] = {
	0b00000,
	0b11100,
	0b11110,
	0b01011,
	0b01011,
	0b11110,
	0b11100,
	0b00000
};

byte R[8] = {
	0b00000,
	0b10001,
	0b11111,
	0b11111,
	0b00101,
	0b01101,
	0b11111,
	0b10010
};

byte H[8] = {
	0b00000,
	0b11111,
	0b11111,
	0b00100,
	0b00100,
	0b11111,
	0b11111,
	0b00000
};

byte I[8] = {
	0b00000,
	0b00000,
	0b10001,
	0b11111,
	0b11111,
	0b10001,
	0b00000,
	0b00000
};

byte G[8] = {
	0b00000,
	0b01110,
	0b11111,
	0b10001,
	0b10101,
	0b11101,
	0b11101,
	0b00000
};

byte C[8] = {
	0b00000,
	0b01110,
	0b11111,
	0b10001,
	0b10001,
	0b11011,
	0b11010,
	0b00000
};

byte O[8] = {
	0b00000,
	0b01110,
	0b11111,
	0b10001,
	0b10001,
	0b11111,
	0b01110,
	0b00000
};

byte E[8] = {
	0b00000,
	0b10001,
	0b11111,
	0b11111,
	0b10101,
	0b10101,
	0b10101,
	0b00000
};

byte ZERO[8] = {
	0b00000,
	0b00000,
	0b01110,
	0b10001,
	0b10001,
	0b01110,
	0b00000,
	0b00000
};

byte ONE[8] = {
	0b00000,
	0b10000,
	0b10010,
	0b11111,
	0b11111,
	0b10000,
	0b10000,
	0b00000
};

byte TWO[8] = {
	0b00000,
	0b00000,
	0b11101,
	0b10101,
	0b10101,
	0b10111,
	0b00000,
	0b00000
};

byte THREE[8] = {
	0b00000,
	0b01010,
	0b11011,
	0b10001,
	0b10101,
	0b11111,
	0b01110,
	0b00000
};

byte FOUR[8] = {
	0b00000,
	0b00000,
	0b01100,
	0b01010,
	0b01001,
	0b11111,
	0b00000,
	0b00000
};

byte FIVE[8] = {
	0b00000,
	0b00000,
	0b10111,
	0b10101,
	0b10101,
	0b01001,
	0b00000,
	0b00000
};

byte SIX[8] = {
	0b00000,
	0b00000,
	0b11111,
	0b10101,
	0b10101,
	0b11101,
	0b00000,
	0b00000
};

byte SEVEN[8] = {
	0b00000,
	0b00000,
	0b00001,
	0b11001,
	0b00101,
	0b00011,
	0b00000,
	0b00000
};


byte EIGHT[8] = {
	0b00000,
	0b00000,
	0b01010,
	0b10101,
	0b10101,
	0b01010,
	0b00000,
	0b00000
};

byte NINE[8] = {
	0b00000,
	0b00000,
	0b10111,
	0b10101,
	0b10101,
	0b11111,
	0b00000,
	0b00000
};

byte HEART[8] = {
	0b00010,
	0b00111,
	0b01111,
	0b11110,
	0b11110,
	0b01111,
	0b00111,
	0b00010
};

LcdDisplayVertical::LcdDisplayVertical(int rs, int en, int d4, int d5, int d6, int d7) {
    lcd = new LiquidCrystal(rs, en, d4, d5, d6, d7);
}

LcdDisplayVertical::~LcdDisplayVertical() {
    delete lcd;
}

void LcdDisplayVertical::setLives(int lives) {
    this->lives = lives;
}

void LcdDisplayVertical::writeStart() {
    int col = 10;

    lcd->createChar(0, S);
    lcd->createChar(1, T);
    lcd->createChar(2, A);
    lcd->createChar(3, R);
    lcd->begin(16, 2);
    lcd->clear();
    
    lcd->setCursor(1, 0);
    lcd->print("-----");
    lcd->setCursor(11, 0);
    lcd->print("-----");

    lcd->setCursor(col, 0);
    lcd->write(byte(0));
    --col;
    lcd->setCursor(col, 0);
    lcd->write(byte(1));
    --col;
    lcd->setCursor(col, 0);
    lcd->write(byte(2));
    --col;
    lcd->setCursor(col, 0);
    lcd->write(byte(3));
    --col;
    lcd->setCursor(col, 0);
    lcd->write(byte(1));
    --col;
}

void LcdDisplayVertical::writeHighScores() {
    int col = 13;
    lcd->createChar(0, H);
    lcd->createChar(1, I);
    lcd->createChar(2, G);
    lcd->createChar(3, S);
    lcd->createChar(4, C);
    lcd->createChar(5, O);
    lcd->createChar(6, R);
    lcd->createChar(7, E);

    lcd->begin(16, 2);
    lcd->clear();
    lcd->setCursor(1, 0);
    lcd->print("--");
    lcd->setCursor(14, 0);
    lcd->print("--");

    lcd->setCursor(col, 0);
    lcd->write(byte(0));
    --col;
    lcd->setCursor(col, 0);
    lcd->write(byte(1));
    --col;
    lcd->setCursor(col, 0);
    lcd->write(byte(2));
    --col;
    lcd->setCursor(col, 0);
    lcd->write(byte(0));
    --col;
    lcd->setCursor(col, 0);
    lcd->print(" ");
    --col;
    lcd->setCursor(col, 0);
    lcd->write(byte(3));
    --col;
    lcd->setCursor(col, 0);
    lcd->write(byte(4));
    --col;
    lcd->setCursor(col, 0);
    lcd->write(byte(5));
    --col;
    lcd->setCursor(col, 0);
    lcd->write(byte(6));
    --col;
    lcd->setCursor(col, 0);
    lcd->write(byte(7));
    --col;
    lcd->setCursor(col, 0);
    lcd->write(byte(3));
    --col;
}

void LcdDisplayVertical::writeReadedHighScores(int numberOfHighScores, int highScores[]) {
    int pos = 0;
    for (int i = 0; i < numberOfHighScores; ++i) {
        createDigit(pos, (highScores[i]/10) % 10);
        ++pos;
        createDigit(pos, highScores[i] % 10);
        ++pos;
    }

    lcd->begin(16, 2);
    lcd->clear();
    lcd->setCursor(1, 0);
    lcd->print("---");
    int col = 4;
    lcd->setCursor(col, 0);
    lcd->write(byte(5));
    ++col;
    lcd->setCursor(col, 0);
    lcd->write(byte(4));
    ++col;
    lcd->setCursor(col, 0);
    lcd->print("---");
    col += 3;
    lcd->setCursor(col, 0);
    lcd->write(byte(3));
    ++col;
    lcd->setCursor(col, 0);
    lcd->write(byte(2));
    ++col;
    lcd->setCursor(col, 0);
    lcd->print("---");
    col += 3;
    lcd->setCursor(col, 0);
    lcd->write(byte(1));
    ++col;
    lcd->setCursor(col, 0);
    lcd->write(byte(0));
}

void LcdDisplayVertical::createDigit(int pos, int digit) {
    switch (digit) {
        case 0:
            lcd->createChar(pos, ZERO);
            break;
        case 1:
            lcd->createChar(pos, ONE);
            break;
        case 2:
            lcd->createChar(pos, TWO);
            break;
        case 3:
            lcd->createChar(pos, THREE);
            break;
        case 4:
            lcd->createChar(pos, FOUR);
            break;
        case 5:
            lcd->createChar(pos, FIVE);
            break;
        case 6:
            lcd->createChar(pos, SIX);
            break;
        case 7:
            lcd->createChar(pos, SEVEN);
            break;
        case 8:
            lcd->createChar(pos, EIGHT);
            break;
        case 9:
            lcd->createChar(pos, NINE);
            break;
    }
}

void LcdDisplayVertical::updateScore(int score) {
    lcd->createChar(0, S);
    lcd->createChar(1, C);
    lcd->createChar(2, O);
    lcd->createChar(3, R);

    int lastDigit = score % 10;
    int firstDigit = (score / 10) % 10;
    createDigit(4, firstDigit);
    createDigit(5, lastDigit);
    createDigit(6, lives);
    lcd->createChar(7, HEART);
    

    lcd->begin(16, 2);
    lcd->clear();
    lcd->setCursor(1, 0);
    lcd->print("----");
    lcd->setCursor(12, 0);
    lcd->print("----");
    lcd->setCursor(1, 1);
    lcd->print("------------");
    int col = 11;

    lcd->setCursor(col, 0);
    lcd->write(byte(0));
    --col;
    lcd->setCursor(col, 0);
    lcd->write(byte(1));
    --col;
    lcd->setCursor(col, 0);
    lcd->write(byte(2));
    --col;
    lcd->setCursor(col, 0);
    lcd->write(byte(3));
    --col;
    lcd->setCursor(col, 0);
    lcd->print(" ");
    --col;
    lcd->setCursor(col, 0);
    lcd->write(byte(4));
    --col;
    lcd->setCursor(col, 0);
    lcd->write(byte(5));
    --col;

    col = 15;
    lcd->setCursor(col, 1);
    lcd->write(byte(6));
    --col;
    lcd->setCursor(col, 1);
    lcd->write(byte(7));
    --col;
}

void LcdDisplayVertical::clearFirstColumn() {
    lcd->begin(16, 2);
    lcd->clear();
    lcd->setCursor(1, 0);
    lcd->print("               ");
}