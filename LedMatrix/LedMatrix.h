/*
 * A wrapper for LedControl library that is used to
 * control easily the 8 x 8 matrix led 
 * 
 * Written by Auras Popescu
*/

#include "stdlib.h"
#include "Arduino.h"
#include "LedControl.h"

#ifndef LED_MATRIX_H
#define LED_MATRIX_H

class LedMatrix {
    private:
        LedControl *ledControl;
        bool **matrix;
        int rightPositon, leftPositon;
    public:
        LedMatrix(int, int, int, int);
        ~LedMatrix();

        int getRightPosition();
        int getLeftPosition();
        bool** getMatrix();

        void setRightPosition(int);
        void setLeftPosition(int);
        void setLedOn(int, int);
        void setLedOff(int, int);
        void setMatrix(bool matrix[8][8]);
        void drawMatrix();
        void clearMatrix();
};

#endif
