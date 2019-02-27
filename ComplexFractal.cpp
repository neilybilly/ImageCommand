#include "ComplexFractal.h"

ComplexFractal::ComplexFractal()
: mWidth(400), mHeight(300), mEscape(255), mMinX(-2), mMaxX(2), mMinY(-1.5), mMaxY(1.5), mDeltaX(0.01), mDeltaY(0.01), mEscCount(120000) {}

ComplexFractal::~ComplexFractal( ){

}

int ComplexFractal::getWidth() const {
    return mWidth;
}

int ComplexFractal::getHeight( ) const {
    return mHeight;
}

double ComplexFractal::getMinX() const {
    return mMinX;
}

double ComplexFractal::getMaxX( ) const {
    return mMaxX;
}

double ComplexFractal::getMinY( ) const {
    return mMinY;
}

double ComplexFractal::getMaxY( ) const {
    return mMaxY;
}

int ComplexFractal::getMaxEscapeCount() const {
    return mEscape;
}

void ComplexFractal::setPixelSize( const int& width, const int& height ) {
    if ( width >= 2 && height >= 2 ){
        mWidth = width;
        mHeight = height;
    }
    if ( calculateDeltaX() != mDeltaX ) {
        mDeltaX = calculateDeltaX();
    }
    if ( calculateDeltaY() != mDeltaY ) {
        mDeltaY = calculateDeltaY();
    }
    mEscCount.resize(mWidth * mHeight);
}

void ComplexFractal::setPlaneSize( const double& min_x, const double& max_x, const double& min_y, const double& max_y ) {
    if ( min_x >= -2 && min_x <= 2  && min_y >= -2 && min_y <= 2 && max_x <= 2 && max_x >= -2 && max_y >= -2&& max_y <= 2 && min_x != max_x && min_y != max_y ) {
            mMinX = min_x;
            mMinY = min_y;
            mMaxX = max_x;
            mMaxY = max_y;
    if (mMinX > mMaxX) {
        double a = 0;
        a = mMinX;
        mMinX = mMaxX;
        mMaxX = a;
    }
    if (mMinY > mMaxY) {
        double b = 0;
        b = mMinY;
        mMinY = mMaxY;
        mMaxY = b;
    }
    }
    if ( calculateDeltaX() != mDeltaX ) {
        mDeltaX = calculateDeltaX();
    }
    if ( calculateDeltaY() != mDeltaY ) {
        mDeltaY = calculateDeltaY();
    }

}

void ComplexFractal::setMaxEscapeCount( const int& count ) {
    if ( count >= 0 ){
        mEscape = count;
    }
}

double ComplexFractal::getDeltaX() const {
    return mDeltaX;
}

double ComplexFractal::getDeltaY() const {
    return mDeltaY;
}

void ComplexFractal::setDeltas( const double& delta_x, const double& delta_y ) {
    if ( delta_x > 0 && delta_y > 0 ){
    mDeltaX = delta_x;
    mDeltaY = delta_y;
    }
}

double ComplexFractal::calculateDeltaX() const {
    double gap = (mMaxX - mMinX) / (mWidth -1);
    return gap;
}

double ComplexFractal::calculateDeltaY() const {
    double gap = (mMaxY - mMinY) / (mHeight -1);
    return gap;
}

double ComplexFractal::calculatePlaneXFromPixelColumn( const int& column ) const {
    if ( column >= 0 && column <= mWidth -1 ) {
        double plane = mMinX + column * mDeltaX;
        return plane;
    }else{
        return 0;
    }
}

double ComplexFractal::calculatePlaneYFromPixelRow( const int& row ) const {
    if ( row >= 0 && row <= mHeight -1 ) {
        double plane = mMaxY - row * mDeltaY;
        return plane;
    }else{
        return 0;
    }
}

void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates( const int& row, const int& column, double& x, double& y ) const {
    if ( row >= 0 && row <= mHeight -1 && column >= 0 && column <= mWidth -1) {
       x = calculatePlaneXFromPixelColumn( column );
       y = calculatePlaneYFromPixelRow( row );
    } else {
        x = 0;
        y = 0;
    }
}

const std::vector< int >& ComplexFractal::getEscapeCounts( ) const {
    return this->mEscCount;
}

int ComplexFractal::getEscapeCount( const int& row, const int& column ) const {
    if ( row >= 0 && row <= mHeight -1 && column >= 0 && column <= mWidth -1) {
        return mEscCount[row * mWidth + column];
} else {
    return -1;
}
}

void ComplexFractal::setEscapeCount( const int& row, const int& column, const int& count ) {
    if ( row >= 0 && row <= mHeight -1 && column >= 0 && column <= mWidth -1 && count >= 0 && count <= mEscape ) {
        mEscCount[row *mWidth + column] = count;
    }
}

// int ComplexFractal::calculatePixelEscapeCount( const int& row, const int& column ) const {
//     double x = calculatePlaneXFromPixelColumn(column);
//     double y = calculatePlaneYFromPixelRow(row);
//     if (row >= 0 and row <= mHeight-1 && column >= 0 && column <= mWidth-1) {
//         return calculatePlaneEscapeCount(x,y);
//     }
//     else {
//         return -1;
//     }
// }

void ComplexFractal::calculateAllEscapeCounts( ) {
    for (int i = 0; i <= mHeight -1; i++){
        for (int j = 0; j<= mWidth -1; j++){
            int count = calculatePixelEscapeCount(i,j);
            setEscapeCount(i,j, count);
        }
    }
}

void ComplexFractal::setPPM(PPM& ppm) const {

    ppm.setWidth(mWidth);
    ppm.setHeight(mHeight);
    ppm.setMaxColorValue(63);
    for (int i = 0; i < mHeight; i++){
        for (int j = 0; j < mWidth; j++){
            int count = getEscapeCount(i,j);
            if (count == 0) {
                // for(int k=0; k<3; k++){
                //     ppm.setChannel(i,j,k,0);
                // }
                ppm.setChannel(i,j,0,0);
                ppm.setChannel(i,j,1,0);
                ppm.setChannel(i,j,2,0);
            } else
            if (count == mEscape) {
                ppm.setChannel(i,j,0,63);
                ppm.setChannel(i,j,1,31);
                ppm.setChannel(i,j,2,31);
                }else
            if (count % 8 == 0){
                for(int k=0; k<3; k++){
                    ppm.setChannel(i,j,k,63);
                }
            }else
            if (count % 8 == 1){
                ppm.setChannel(i,j,0,63);
                ppm.setChannel(i,j,1,31);
                ppm.setChannel(i,j,2,31);
                }else
            if (count % 8 == 2){
                ppm.setChannel(i,j,0,63);
                ppm.setChannel(i,j,1,63);
                ppm.setChannel(i,j,2,31);
                }else
            if (count % 8 == 3){
                ppm.setChannel(i,j,0,31);
                ppm.setChannel(i,j,1,63);
                ppm.setChannel(i,j,2,31);
                }else
            if (count % 8 == 4){
                ppm.setChannel(i,j,0,0);
                ppm.setChannel(i,j,1,0);
                ppm.setChannel(i,j,2,0);
                }else
            if (count % 8 == 5){
                ppm.setChannel(i,j,0,31);
                ppm.setChannel(i,j,1,63);
                ppm.setChannel(i,j,2,63);
                }else
            if (count % 8 == 6){
                ppm.setChannel(i,j,0,31);
                ppm.setChannel(i,j,1,31);
                ppm.setChannel(i,j,2,63);
                }else{
            // if (count % 8 == 7){
                ppm.setChannel(i,j,0,63);
                ppm.setChannel(i,j,1,31);
                ppm.setChannel(i,j,2,63);
                }
            }
        }

    }

void ComplexFractal::setPPM( PPM& ppm, const ColorTable& colors ) const {
    ppm.setWidth(mWidth);
    ppm.setHeight(mHeight);
    int max = 0;
    int red, green, blue;
    for (int i=0; i < int(colors.getNumberOfColors()); i++){
        for ( int k = 0; k <3; k++){
            if(colors[i].getChannel(k)>max){
                max = colors[i].getChannel(k);
            }
        }
    }
    ppm.setMaxColorValue(max);
    if ((int)colors.getNumberOfColors() >= 3) {
        for ( int i = 0; i<ppm.getHeight(); i ++){
            for( int j = 0; j < ppm.getWidth(); j++){
                if (getEscapeCount(i, j) == mEscape) {
                    red = colors[colors.getNumberOfColors() -1].getRed();
                    green = colors[colors.getNumberOfColors() -1].getGreen();
                    blue = colors[colors.getNumberOfColors() -1].getBlue();
                }
                else if ( getEscapeCount(i,j) == 0){
                    red = colors[colors.getNumberOfColors() -2].getRed();
                    green = colors[colors.getNumberOfColors() -2].getGreen();
                    blue = colors[colors.getNumberOfColors() -2].getBlue();
                }
                else {
                    int index = getEscapeCount(i, j) % (colors.getNumberOfColors() -2);
                    red = colors[index].getRed();
                    green = colors[index].getGreen();
                    blue = colors[index].getBlue();
                }
                ppm.setChannel(i, j, 0, red);
                ppm.setChannel(i, j, 1, green);
                ppm.setChannel(i, j, 2, blue);
            }
        }
    }
}
