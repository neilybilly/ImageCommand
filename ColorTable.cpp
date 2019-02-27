#include <iostream>
#include <vector>
#include <string>
#include "ColorTable.h"
#include <cstdlib>

Color::Color()
   : mRed(0), mBlue(0), mGreen(0) {
}

Color::Color( const int& red, const int& green, const int& blue ){
    mRed = red;
    mGreen = green;
    mBlue = blue;
}

int Color::getRed() const{
    return mRed;
}

int Color::getGreen() const{
    return mGreen;
}

int Color::getBlue() const{
    return mBlue;
}

int Color::getChannel( const int& channel ) const{
    if ( channel <= 2 && channel >= 0) {
        if ( channel == 0 ){
            return mRed;
        }
        if ( channel == 1 ) {
            return mGreen;
        }else {
            return mBlue;
        }
    } else {
        return -1;
    }
}

void Color::setRed( const int& value ){
    if (value >= 0){
        mRed = value;
    }
}

void Color::setGreen( const int& value ){
    if ( value >= 0 ){
        mGreen = value;
    }
}

void Color::setBlue( const int& value ){
    if ( value >= 0 ){
        mBlue = value;
    }
}

void Color::setChannel( const int& channel, const int& value ) {
    if ( value >= 0 && channel >= 0 && channel <= 2 ){
        if ( channel == 0 ){
            mRed = value;
        }
        if ( channel == 1 ){
            mGreen = value;
        }
        if ( channel == 2 ){
            mBlue = value;
        }
    }
}

void Color::invert( const int& max_color_value ){
    if ( max_color_value >= mRed && max_color_value >= mGreen && max_color_value >= mBlue  ) {
        mRed = max_color_value - mRed;
        mGreen = max_color_value - mGreen;
        mBlue = max_color_value - mBlue;
    }
}

bool Color::operator==( const Color& rhs ) const {
    if ( this->mRed == rhs.mRed && this->mBlue == rhs.mBlue && this->mGreen == rhs.mGreen ){
        return true;
    } else {
        return false;
    }
}

ColorTable::ColorTable( const size_t& num_color )
    : mColors(num_color) {
}

size_t ColorTable::getNumberOfColors( ) const{
    return mColors.size();
}

void ColorTable::setNumberOfColors( const size_t& num_color ) {
    mColors.resize(num_color);
}

const Color& ColorTable::operator[]( const int& i ) const{
    if ( i >= 0 && i < (int) mColors.size() ){
        return mColors[i];
    } else {
        static Color ec(-1, -1, -1); static Color c(-1, -1, -1); c = ec; return c;
    }
}

Color& ColorTable::operator[]( const int& i ) {
    if ( i >= 0 && i < (int) mColors.size() ) {
        return mColors[i];
    } else {
        static Color error(-1, -1, -1);
        static Color master_error(-1, -1, -1);
        error = master_error;
        return error;
    }
}

void ColorTable::setRandomColor( const int& max_color_value, const size_t& position ) {
    if (max_color_value >= 0 && position < this->mColors.size() && max_color_value <= 255){
        int red = std::rand() % (max_color_value +1);
        int green = std::rand() % (max_color_value +1);
        int blue = std::rand() % (max_color_value +1);
        mColors[position].setChannel(0, red);
        mColors[position].setChannel(1, green);
        mColors[position].setChannel(2, blue);
    }
}

void ColorTable::insertGradient( const Color& color1, const Color& color2, const size_t& position1, const size_t& position2 ) {
    int i;
    if ( position1 < position2 && int(position1) >= 0 && position2 < mColors.size()) {
        this->mColors[position1] = color1;
        this->mColors[position2] = color2;

        double d = position2 - position1;

        int red1 = color1.getRed();
        int green1 = color1.getGreen();
        int blue1 = color1.getBlue();

        int red2 = color2.getRed();
        int green2 = color2.getGreen();
        int blue2 = color2.getBlue();

        double red_gap = ((red2 - red1) / d);
        double green_gap = ((green2 - green1) / d);
        double blue_gap = ((blue2 - blue1) / d);

        for (i = 0; i <= d; i++) {
            mColors[position1 + i].setChannel(0, (red1 + i * red_gap));
            mColors[position1 + i].setChannel(1, (green1 + i * green_gap));
            mColors[position1 + i].setChannel(2, (blue1 + i * blue_gap));
        }
    }
}
