/*
 * A wrapper for LiquidCrystal library that is used to
 * write vertically on LCD HD44780
 * 
 * Written by Auras Popescu
*/

#include "Arduino.h"
#include "LedControl.h"
#include "LiquidCrystal.h"

#ifndef LCD_DISPLAY_VERTICAL_H
#define LCD_DISPLAY_VERTICAL_H

class LcdDisplayVertical {
    private:
        byte **customChars;
        LiquidCrystal *lcd;
        int lives;
    public:
        LcdDisplayVertical(int rs, int en, int d4, int d5, int d6, int d7);
        ~LcdDisplayVertical();

        void createDigit(int pos, int digit);
        void setLives(int lives);
        void writeStart();
        void writeHighScores();
        void writeReadedHighScores(int numberOfHighScores, int highScores[]);
        void updateScore(int score);
        void clearFirstColumn();
};

#endif