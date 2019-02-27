#ifndef _COMPLEXFRACTAL_H_
#define _COMPLEXFRACTAL_H_
#include <vector>
#include <iostream>
#include "ColorTable.h"

class ComplexFractal {

    public:
        ComplexFractal( );
        virtual ~ComplexFractal( );
        int getWidth( ) const;
        int getHeight( ) const;
        double getMinX( ) const;
        double getMaxX( ) const;
        double getMinY( ) const;
        double getMaxY( ) const;
        int getMaxEscapeCount( ) const;
        void setPixelSize( const int& width, const int& height );
        void setPlaneSize( const double& min_x, const double& max_x, const double& min_y, const double& max_y );
        void setMaxEscapeCount( const int& count );
        double getDeltaX( ) const;
        double getDeltaY( ) const;
        void setDeltas( const double& delta_x, const double& delta_y );
        double calculateDeltaX( ) const;
        double calculateDeltaY( ) const;
        double calculatePlaneXFromPixelColumn( const int& column ) const;
        double calculatePlaneYFromPixelRow( const int& row ) const;
        void calculatePlaneCoordinatesFromPixelCoordinates( const int& row, const int& column, double& x, double& y ) const;
        const std::vector< int >& getEscapeCounts( ) const;
        int getEscapeCount( const int& row, const int& column ) const;
        void setEscapeCount( const int& row, const int& column, const int& count );
        virtual int calculatePixelEscapeCount( const int& row, const int& column ) const = 0;
        void calculateAllEscapeCounts( );
        void setPPM( PPM& ppm ) const;
        void setPPM( PPM& ppm, const ColorTable& colors ) const;

    protected:

        int mWidth;
        int mHeight;
        int mEscape;
        double mMinX;
        double mMaxX;
        double mMinY;
        double mMaxY;
        double mDeltaX;
        double mDeltaY;
        std::vector<int> mEscCount;
};


#endif
