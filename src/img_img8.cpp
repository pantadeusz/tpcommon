/*

MIT License

Copyright (c) 2017 Tadeusz Puźniakowski

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include "img_img8.hpp"
#include <lodepng.h>
#include <vector>
#include <stdexcept>
#include <iostream>

namespace tp {
namespace img {

Img8::Img8( const int w, const int h ) : std::vector < unsigned char >( w*h ) {
	width = w;
	height = h;
	for ( int i = w*h; i--; ) {
		operator[]( i ) = 255;
	}
}

void Img8::setTo(unsigned char v) {
	#pragma omp parallel for
	for (unsigned y = 0; y < height*width; y++) {
		this->operator[](y) = v;
	}
}

unsigned char &Img8::operator()( int x, int y ) {
	if ( x<0 ) x = 0;
	if ( x>= ( int )width ) x = width-1;
	if ( y<0 ) y = 0;
	if ( y>= ( int )height ) y = height-1;
	return operator[]( y*width+x );
}
unsigned char Img8::operator()( int x, int y ) const {
	if ( x<0 ) x = 0;
	if ( x>= ( int )width ) x = width-1;
	if ( y<0 ) y = 0;
	if ( y>= ( int )height ) y = height-1;
	return operator[]( y*width+x );
}

void Img8::save( const std::string &fname ) {
	unsigned error = lodepng::encode( fname, ( unsigned char * )data(), width, height, LodePNGColorType::LCT_GREY, 8 );
	if( error ) throw std::runtime_error( lodepng_error_text( error ) );
}

void Img8::load( const std::string &fname ) {
	this->clear();
	unsigned error = lodepng::decode( *( std::vector<unsigned char > * )this, width, height, fname, LodePNGColorType::LCT_GREY, 8 );

	if( error ) throw std::runtime_error( lodepng_error_text( error ) );
}


double Img8::similarTo(const Img8 &dst) {
	auto &a = *this;
	auto &b = dst;

	if ( a.width != b.width ) throw std::runtime_error( "Different image sizes!" );
	if ( a.height != b.height ) throw std::runtime_error( "Different image sizes!" );
	

	double difference = 0;
	#pragma omp parallel for
	for ( int x = 0; x < ( int )a.width; x++ ) {
		for ( int y = 0; y < ( int )a.height; y++ ) {
			double dist = 0;
			if (a( x,y ) != b( x,y )) {
				dist = 1;
				if (a( x,y ) == b( x+1,y )) {
					dist = 0.5;
				} else if (a( x,y ) == b( x-1,y )) {
					dist = 0.5;
				} else if (a( x,y ) == b( x,y+1 )) {
					dist = 0.5;
				} else if (a( x,y ) == b( x,y-1 )) {
					dist = 0.5;
				} else if (a( x,y ) == b( x-1,y-1)) {
					dist = 0.75;
				} else if (a( x,y ) == b( x-1,y+1)) {
					dist = 0.75;
				} else if (a( x,y ) == b( x+1,y+1)) {
					dist = 0.75;
				} else if (a( x,y ) == b( x+1,y-1)) {
					dist = 0.75;
				}
			}
			if (dist != 0) {
				#pragma omp critical
				difference += dist;
			}
			
		}
	}
	return difference;
}

bool operator==( const Img8 &a, const Img8 &b ) {
	if ( a.width != b.width ) return false;
	if ( a.height != b.height ) return false;
	for ( unsigned i = 0; i < a.width*a.height; i++ ) {
		if ( a[i] != b[i] ) {
			//std::cout << "E: " << i << " : " << ( int )a[i] << " != " << ( int )b[i] << std::endl;
			return false;
		}
	}
	return true;
}

Img8 operator-( const Img8 &a, const Img8 &b )  {
	Img8 ret = a;
	for ( int x = 0; x < ( int )a.width; x++ ) {
		for ( int y = 0; y < ( int )a.height; y++ ) {
			ret( x,y ) = a( x,y ) - b( x,y );
		}
	}
	return ret;
}


}
}
