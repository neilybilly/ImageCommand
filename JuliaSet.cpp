#include <iostream>
#include <vector>
#include <string>
#include "JuliaSet.h"
#include "ColorTable.h"

JuliaSet::JuliaSet()
    : mA ( -0.650492 ), mB ( -0.478235 ) {
    }

JuliaSet::~JuliaSet(){

}

double JuliaSet::getA() const {
    return mA;
}

double JuliaSet::getB() const {
    return mB;
}

void JuliaSet::setParameters( const double& a, const double& b ) {
    if ( a >= -2 && a <= 2 && b >= -2 && b <= 2 ){
        mA = a;
        mB = b;
    }
}

void JuliaSet::calculateNextPoint( const double x0, const double y0, double& x1, double &y1 ) const {
    x1 = (x0 * x0) - (y0 * y0) + mA;
    y1 = (2 * x0 * y0) + mB;
}

int JuliaSet::calculatePlaneEscapeCount( const double& x0, const double& y0 ) const {
    int counter = 0;
    double newX;
    double newY;
    double x2 = x0;
    double y2 = y0;
    double d = 0;
    while (counter < mEscape){
        calculateNextPoint( x2, y2, newX, newY );
        d = ((x2 * x2) + (y2 * y2));
        if(d > 4){
            return counter;
        }
        else {
            counter++;
            x2 = newX;
            y2 = newY;
        }
    }
    return counter;
}

int JuliaSet::calculatePixelEscapeCount( const int& row, const int& column ) const {
    double x = calculatePlaneXFromPixelColumn(column);
    double y = calculatePlaneYFromPixelRow(row);
    if (row >= 0 and row <= mHeight-1 && column >= 0 && column <= mWidth-1) {
        return calculatePlaneEscapeCount(x,y);
    }
    else {
        return -1;
    }
}
