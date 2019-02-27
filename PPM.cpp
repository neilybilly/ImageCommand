#include <iostream>
#include <vector>
#include <string>
#include "PPM.h"
#include <cstdlib>

PPM::PPM()
  :  mWidth ( 0 ), mHeight ( 0 ), mMaxColorValue ( 0 ){

  }

int PPM::getWidth() const {
    return mWidth;
}

int PPM::getHeight() const {
    return mHeight;
}

int PPM::getMaxColorValue() const {
    return mMaxColorValue;
}

int PPM::getChannel( const int& row, const int& column, const int& channel ) const {
    if ( row >= 0 && row < mHeight && column >= 0 && column < mWidth && channel >= 0 && channel <= 2 ){
        size_t pixel = ((row * mWidth * 3) + (column * 3)) + channel;
        if ( pixel < mPicture.size()){
            return mPicture[pixel];
        }
    }
    return -1;
}

void PPM::setWidth( const int& width ) {
    if ( width >= 0 ){
        mWidth = width;
        mPicture.resize(mHeight * mWidth * 3);
    }
}

void PPM::setHeight( const int& height ) {
    if ( height >= 0 ) {
        mHeight = height;
        mPicture.resize( mHeight * mWidth * 3 );
    }
}

void PPM::setMaxColorValue( const int& max_color_value ){
    if ( max_color_value >= 0 && max_color_value <= 255 ){
        mMaxColorValue = max_color_value;
    }
}
void PPM::setChannel( const int& row, const int& column, const int& channel, const int& value ){
    if ( row >= 0 && row < mHeight && column >= 0 && column < mWidth && channel >= 0 && channel <= 2 && value >= 0 && value <= mMaxColorValue ){
        size_t pixel = ((row * mWidth * 3) + (column * 3)) + channel;
        if ( pixel < mPicture.size()){
            mPicture[pixel] = value;
        }
    }
}

std::istream& operator>>(std::istream& is, PPM& rhs){
    unsigned char channel;
    std::string mystring;
    int row, column, width, color, height, mcv;
    is >> mystring >> width >> height >> mcv;
    rhs.setWidth(width);
    rhs.setHeight(height);
    rhs.setMaxColorValue(mcv);
    is.read((char*)& channel, 1 );
    for( row = 0; row < rhs.getHeight(); row++ ) {
        for( column = 0; column < rhs.getWidth(); column++ ) {
            for( color = 0; color < 3; color++ ) {
                is.read((char*)&channel, 1);
                int channel2 = static_cast<int>(channel);
                rhs.setChannel(row, column, color, channel2);
            }
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const PPM& rhs){
    unsigned char channel;
    std::string p6 = "P6 ";
    int height = rhs.getHeight();
    int width = rhs.getWidth();
    int maxColor = rhs.getMaxColorValue();
    os << p6 << width << " " << height  << " " << maxColor << "\n";

    for( int row = 0; row < rhs.getHeight(); row++ ) {
        for( int column = 0; column < rhs.getWidth(); column++ ) {
            for( int color = 0; color < 3; color++ ) {
                channel = rhs.getChannel( row, column, color );
                os.write((char*) &channel, 1);
            }
        }
    }
    return os;
}

bool PPM::operator==( const PPM& rhs ) const {
    return this->mWidth * this->mHeight == rhs.getWidth() * rhs.getHeight();
}
bool PPM::operator!=( const PPM& rhs ) const {
    return this->mWidth * this->mHeight != rhs.getWidth() * rhs.getHeight();
}

bool PPM::operator<( const PPM& rhs ) const {
    return this->mWidth * this->mHeight < rhs.getWidth() * rhs.getHeight();
}

bool PPM::operator<=( const PPM& rhs ) const {
    return this->mWidth * this->mHeight <= rhs.getWidth() * rhs.getHeight();
}

bool PPM::operator>( const PPM& rhs ) const {
    return this->mWidth * this->mHeight > rhs.getWidth() * rhs.getHeight();
}

bool PPM::operator>=( const PPM& rhs ) const {
    return this->mWidth * this->mHeight >= rhs.getWidth() * rhs.getHeight();
}

PPM& PPM::operator+=( const PPM& rhs ){
    int width, height;
    width = rhs.getWidth();
    height = rhs.getHeight();
    for ( int i = 0; i < height; i++ ){
        for ( int j = 0; j < width; j++ ){
            for ( int k = 0; k < 3; k++ ) {
                int channel = this->getChannel(i,j,k) + rhs.getChannel(i,j,k);
                if( channel <= 255 ){
                    this->setChannel(i,j,k,channel);
                }
                else{
                    this->setChannel(i,j,k,255);
                }

                }
            }
        }
    return *this;
}

PPM& PPM::operator-=( const PPM& rhs ){
    int width, height;
    width = rhs.getWidth();
    height = rhs.getHeight();
    for ( int i = 0; i < height; i++ ){
        for ( int j = 0; j < width; j++ ){
            for ( int k = 0; k < 3; k++ ) {
                int channel = this->getChannel(i,j,k) - rhs.getChannel(i,j,k);
                if( channel >= 0 ){
                    this->setChannel(i,j,k,channel);
                }
                else{
                    this->setChannel(i,j,k,0);
                }

                }
            }
        }
    return *this;
}

PPM PPM::operator+( const PPM& rhs ) const {
    PPM lhs(*this);
    lhs += rhs;
    return lhs;
}

PPM PPM::operator-( const PPM& rhs ) const {
    PPM lhs(*this);
    lhs -= rhs;
    return lhs;
}

PPM& PPM::operator*=( const double& rhs ){
    int width, height;
    width = this->getWidth();
    height = this->getHeight();
    for ( int i = 0; i < height; i++ ){
        for ( int j = 0; j < width; j++ ){
            for ( int k = 0; k < 3; k++ ) {
                int channel = this->getChannel(i,j,k) * rhs;
                if( channel <= mMaxColorValue and channel >= 0 ){
                    this->setChannel(i,j,k,channel);
                }
                else if( channel > 255){
                    this->setChannel(i,j,k,255);
                } else{
                    this->setChannel(i,j,k,0);
                }

                }
            }
        }
    return *this;
}

PPM& PPM::operator/=( const double& rhs ){
    int width, height;
    width = this->getWidth();
    height = this->getHeight();
    for ( int i = 0; i < height; i++ ){
        for ( int j = 0; j < width; j++ ){
            for ( int k = 0; k < 3; k++ ) {
                int channel = this->getChannel(i,j,k) / rhs;
                if( channel >= 0 and channel <= mMaxColorValue ){
                    this->setChannel(i,j,k,channel);
                }
                else if( channel > 255){
                    this->setChannel(i,j,k,255);
                } else{
                    this->setChannel(i,j,k,0);
                }

                }
            }
        }
    return *this;
}

PPM PPM::operator*( const double& rhs ) const{
    PPM lhs(*this);
    lhs *= rhs;
    return lhs;
}

PPM PPM::operator/( const double& rhs ) const{
    PPM lhs(*this);
    lhs /= rhs;
    return lhs;
}

void PPM::setRed(){
    int i, j, k;

    for (i = 0; i < this->getHeight(); i++){
        for ( j = 0; j < this->getWidth(); j++){
            int red = this-> getChannel(i, j, 0);
            for(k=0; k<3; k++){
                this->setChannel(i, j, k, red);
            }
        }
    }
    return;
}

void PPM::setGreen(){
    int i, j, k;

    for (i = 0; i < this->getHeight(); i++){
        for ( j = 0; j < this->getWidth(); j++){
            int green = this->getChannel(i, j, 1);
            for(k=0; k<3; k++){
                this->setChannel(i, j, k, green);
            }
        }
    }
    return;
}

void PPM::setBlue(){
    int i, j, k;

    for (i = 0; i < this->getHeight(); i++){
        for (j = 0; j < this->getWidth(); j++){
            double blue = this->getChannel(i, j, 2);
            for (k=0; k<3; k++){
                this->setChannel(i, j, k, blue);
            }
        }
    }
    return;
}
