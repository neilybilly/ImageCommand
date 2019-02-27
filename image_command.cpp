#include "ColorTable.h"
#include "ComplexFractal.h"
#include "MandelbrotSet.h"
#include "PPM.h"
#include "JuliaSet.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sstream>

void set_size( ColorTable &ct, const char *arg) {
    std::stringstream ss;
    size_t size;
    ss.str(arg);
    ss >> size;
    if (ss) {
        ct.setNumberOfColors(size);
    }
}

void assign_color_position(ColorTable &ct, const char *arg){
    std::stringstream ss;
    int pos, r, g, b;
    char c, c1, c2;
    ss.str(arg);
    ss >> pos >> c >> r >> c1 >> g >> c2 >> b;
    if ( ss and c == ':' and c1 == ',' and c2 == ','){
        Color color(r, g, b);
        ct[pos] = color;
    }
}

void assign_random_color_max(ColorTable &ct, const char *arg){
    std::stringstream ss;
    size_t pos;
    int max;
    char c;
    ss.str(arg);
    ss >> pos >> c >> max;
    if (ss and c == ':'){
        ct.setRandomColor(max, pos);
    }
}

void assign_color_gradient(ColorTable &ct, const char *arg){
    std::stringstream ss;
    size_t pos1, pos2;
    int r1, g1, b1, r2, g2, b2;
    char c1, c2, c3, c4, c5, c6, c7;
    ss.str(arg);
    ss >> pos1 >> c1 >> r1 >> c2 >> g1 >> c3 >> b1 >> c4 >> pos2 >> c5 >> r2 >> c6 >> g2 >> c7 >> b2;
    if ( ss and c1 == ':' and c2 == ',' and c3 == ',' and c4 == ':' and c5 == ':' and c6 == ',' and c7 == ',') {
        Color color1(r1, g1, b1);
        Color color2(r2, g2, b2);
        ct.insertGradient(color1, color2, pos1, pos2);
    }
}
    
void assign_plane_size(ComplexFractal *fractal, const char *arg){
    std::stringstream ss;
    int minx, maxx, miny, maxy;
    char c1, c2, c3;
    ss.str(arg);
    ss >> minx >> c1 >> maxx >> c2 >> miny >> c3 >> maxy;
    if( ss and c1 == ':' and c2 == ',' and c3 == ':') {
        fractal->setPlaneSize(minx, maxx, miny, maxy);
    }
}

void assign_pixel_size(ComplexFractal *fractal, const char *arg){
    std::stringstream ss;
    int width, height;
    char c1;
    ss.str(arg);
    ss >> width >> c1 >> height;
    if (ss and c1 == ',') {
        fractal->setPixelSize(width,height);
    }
}

void assign_max_escapevalue(ComplexFractal *fractal, const char *arg){
    std::stringstream ss;
    int max;
    ss.str(arg);
    ss >> max;
    if(ss){
        fractal->setMaxEscapeCount(max);
    }
}

void assign_juliaset_parameters(ComplexFractal *fractal, const char *arg){
    std::stringstream ss;
    double a, b;
    char c1;
    ss.str(arg);
    ss >> a >> c1 >> b;
    if (ss and c1 == ','){
        JuliaSet *juliaset = dynamic_cast < JuliaSet* >(fractal);
        if (juliaset != 0){
            juliaset->setParameters(a,b);
        }
    }
}

void calculate_setPPM(ComplexFractal *fractal, ColorTable &ct, const char *arg){
    std::stringstream ss;
    std::string filename;
    PPM ppm;
    ss.str(arg);
    ss >> filename;
    if ( ss ){
        fractal->calculateAllEscapeCounts();
        fractal->setPPM(ppm, ct);
        std::ofstream fout(filename, std::ios::binary);
        if(fout){
            fout << ppm;
            fout.close();
        }
    }
}

int main( int argc, char **argv) {
    ComplexFractal *fractal  = new JuliaSet();
    ColorTable ct(16);
    ct.insertGradient( Color(0,255,0), Color(255,0,255), 0, 15 );

    int c;
    while((c = getopt ( argc, argv, "T:A:R:g:MJr:p:m:a:f:h?")) != -1 ){
        switch(c) {
        case 'T':
            set_size( ct, optarg );
            break;
        case 'A':
            assign_color_position(ct, optarg);
            break;
        case 'R':
            assign_random_color_max(ct,optarg);
            break;
        case 'g':
            assign_color_gradient(ct, optarg);
            break;
        case 'M':
            delete fractal;
            fractal = new MandelbrotSet();
            break;
        case 'J':
            delete fractal;
            fractal = new JuliaSet();
            break;
        case 'r':
            assign_plane_size(fractal, optarg);
            break;
        case 'p':
            assign_pixel_size(fractal,optarg);
            break;
        case 'm':
            assign_max_escapevalue(fractal, optarg);
            break;
        case 'a':
            assign_juliaset_parameters(fractal, optarg);
            break;
        case 'f':
            calculate_setPPM(fractal, ct, optarg);
            break;
        case 'h':
        case '?':
        default:
            std::cout << "usage: " << argv[0] << " " << std::endl 
                      << "-z int:float,int:float=string  //gives vital parameters" << std::endl 
                      << "-h|-?                          // displays this help message" << std::endl    
                      << std::endl;
            return 1;
            break;
        }
    }
    return 0;
}
