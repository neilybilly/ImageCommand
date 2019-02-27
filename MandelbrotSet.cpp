#include "MandelbrotSet.h"
#include "ComplexFractal.h"

MandelbrotSet::MandelbrotSet( ){

}

MandelbrotSet::~MandelbrotSet( ) {

}

void MandelbrotSet::calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const {
    x1 = (x0 * x0) - (y0 * y0) + a;
    y1 = (2 * x0 * y0) + b;
}

int MandelbrotSet::calculatePlaneEscapeCount( const double& a, const double& b ) const {
    int counter = 0;
    double newX;
    double newY;
    double x2 = a;
    double y2 = b;
    double d = 0;
    while (counter < mEscape){
        calculateNextPoint( x2, y2, a, b, newX, newY );
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

int MandelbrotSet::calculatePixelEscapeCount( const int& row, const int& column ) const {
    double x = calculatePlaneXFromPixelColumn(column);
    double y = calculatePlaneYFromPixelRow(row);
    if (row >= 0 and row <= mHeight-1 && column >= 0 && column <= mWidth-1) {
        return calculatePlaneEscapeCount(x,y);
    }
    else {
        return -1;
    }
}
