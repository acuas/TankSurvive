#include "LedMatrix.h"

LedMatrix::LedMatrix(int dataInPin, int clkPin, int loadPin, int intensity) {
    ledControl = new LedControl(dataInPin, clkPin, loadPin, 1);
    ledControl->shutdown(0, false);
    ledControl->setIntensity(0, intensity); // sets brightness (0~15 possible values)
    ledControl->clearDisplay(0);

    matrix = new bool*[8];
    for (int i = 0; i < 8; ++i)
        matrix[i] = new bool[8];

    clearMatrix();
}

LedMatrix::~LedMatrix() {
    delete ledControl;
    for (int i = 0; i < 8; ++i) 
        delete[] matrix[i];
    delete[] matrix;
}

int LedMatrix::getRightPosition() {
    return rightPositon;
}

int LedMatrix::getLeftPosition() {
    return leftPositon;
}

bool** LedMatrix::getMatrix() {
    return matrix;
}

void LedMatrix::setRightPosition(int x) {
    if (x >= 0 && x <= 7)
        rightPositon = x;
}

void LedMatrix::setLeftPosition(int x) {
    if (x >= 0 && x <= 7)
        leftPositon = x;
}

void LedMatrix::setLedOn(int x, int y) {
    if (x >= 0 && x <= 7 && y >= 0 && y <= 7)
        matrix[x][y] = true;
}

void LedMatrix::setLedOff(int x, int y) {
    if (x >= 0 && x <= 7 && y >= 0 && y <= 7)
        matrix[x][y] = false;
}

void LedMatrix::setMatrix(bool matrix[8][8]) {
    int i, j;
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            this->matrix[i][j] = matrix[i][j];
        }
    }
}

void LedMatrix::drawMatrix() {
    int i, j;
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j)
            ledControl->setLed(0, i, j, matrix[i][j]);
    }
}

void LedMatrix::clearMatrix() {
    int i, j;
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            matrix[i][j] = false;
        }
    }
}
