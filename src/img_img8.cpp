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
#include <map>
#include <tuple>

namespace tp {
namespace img {

Img8::Img8( const int w, const int h ) : std::vector < unsigned char >( w*h ) {
	width = w;
	height = h;
	for ( int i = w*h; i--; ) {
		operator[]( i ) = 255;
	}
}

void Img8::setTo( unsigned char v ) {
	#pragma omp parallel for
	for ( unsigned y = 0; y < height*width; y++ ) {
		this->operator[]( y ) = v;
	}
}

void Img8::drawCircleMax( const int x_, const int y_, const int r_, unsigned char color ) {
	int r2 = r_*r_;
	int rr;
	int lx=x_-r_, ly=y_-r_,
	    rx=x_+r_, ry=y_+r_;
	int x0, y0;
	if ( lx < 0 ) lx = 0;
	if ( ly < 0 ) ly = 0;
	if ( rx >= ( int )width ) rx = width;
	if ( ry >= ( int )height ) ry = height;
	for ( int y = ly; y <= ry; y++ ) {
		for ( int x = lx; x <= rx; x++ ) {
			x0 = x-x_;
			y0 = y-y_;
			rr = x0*x0+y0*y0;
			if ( rr <= r2 ) {
				auto &c = operator[]( y*width+x );
				if ( c < color ) c = color;
			}
		}
	}
}
void Img8::drawCircleMin( const int x_, const int y_, const int r_, unsigned char color ) {
	int r2 = r_*r_;
	int rr;
	int lx=x_-r_, ly=y_-r_,
	    rx=x_+r_, ry=y_+r_;
	int x0, y0;
	if ( lx < 0 ) lx = 0;
	if ( ly < 0 ) ly = 0;
	if ( rx < ( int )width ) rx = width;
	if ( ry < ( int )height ) ry = height;

	for ( int y = ly; y <= ry; y++ ) {
		for ( int x = lx; x <= rx; x++ ) {
			x0 = x-x_;
			y0 = y-y_;
			rr = x0*x0+y0*y0;
			if ( rr <= r2 ) {
				auto &c = data()[y*width+x];
				if ( c > color ) c = color;
			}
		}
	}
}

void Img8::drawCircleLineToMax( const int x_0, const int y_0, const int x_1, const int y_1,const int r_, unsigned char color ) {
	drawCircleMax( x_0, y_0, r_, color );
	drawCircleMax( x_1, y_1, r_, color );

	int dx = x_1-x_0, dy=y_1-y_0;
	double x0,y0,x1,y1;
	auto swp = [&]() {
		x0 = x_1;
		x1 = x_0;
		y0 = y_1;
		y1 = y_0;
	};
	auto ccp = [&]() {
		x0 = x_0;
		x1 = x_1;
		y0 = y_0;
		y1 = y_1;
	};

	if ( dx*dx > dy*dy ) {
		if ( x_0 > x_1 ) {
			swp();
		} else {
			ccp();
		}
		double a = ( y1-y0 )/( x1-x0 );
		double b = y0-a*x0;
		for ( double x = x0+1; x < x1; x++ ) {
			double y = a*x+b;
			drawCircleMax( x, y, r_, color );
		}
	} else {
		if ( y_0 > y_1 ) {
			swp();
		} else {
			ccp();
		}
		double a = ( x1-x0 )/( y1-y0 );
		double b = x0-a*y0;
		for ( double y = y0+1; y < y1; y++ ) {
			double x = a*y+b;
			drawCircleMax( x, y, r_, color );
		}

	}
}

void Img8::drawCircleLineToMin( const int x_0, const int y_0, const int x_1, const int y_1,const int r_, unsigned char color ) {
	drawCircleMin( x_0, y_0, r_, color );
	drawCircleMin( x_1, y_1, r_, color );

	int dx = x_1-x_0, dy=y_1-y_0;
	double x0,y0,x1,y1;
	auto swp = [&]() {
		x0 = x_1;
		x1 = x_0;
		y0 = y_1;
		y1 = y_0;
	};
	auto ccp = [&]() {
		x0 = x_0;
		x1 = x_1;
		y0 = y_0;
		y1 = y_1;
	};

	if ( dx*dx > dy*dy ) {
		if ( x_0 > x_1 ) {
			swp();
		} else {
			ccp();
		}
		double a = ( y1-y0 )/( x1-x0 );
		double b = y0-a*x0;
		for ( double x = x0+1; x < x1; x++ ) {
			double y = a*x+b;
			drawCircleMin( x, y, r_, color );
		}
	} else {
		if ( y_0 > y_1 ) {
			swp();
		} else {
			ccp();
		}
		double a = ( x1-x0 )/( y1-y0 );
		double b = x0-a*y0;
		for ( double y = y0+1; y < y1; y++ ) {
			double x = a*y+b;
			drawCircleMin( x, y, r_, color );
		}

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


double Img8::similarTo( const Img8 &dst ) {
	auto &a = *this;
	auto &b = dst;

	if ( a.width != b.width ) throw std::runtime_error( "Different image sizes!" );
	if ( a.height != b.height ) throw std::runtime_error( "Different image sizes!" );


	double difference = 0;
	#pragma omp parallel for
	for ( int x = 0; x < ( int )a.width; x++ ) {
		for ( int y = 0; y < ( int )a.height; y++ ) {
			double dist = 0;
			if ( a( x,y ) != b( x,y ) ) {
				dist = 1;
				if ( a( x,y ) == b( x+1,y ) ) {
					dist = 0.5;
				} else if ( a( x,y ) == b( x-1,y ) ) {
					dist = 0.5;
				} else if ( a( x,y ) == b( x,y+1 ) ) {
					dist = 0.5;
				} else if ( a( x,y ) == b( x,y-1 ) ) {
					dist = 0.5;
				} else if ( a( x,y ) == b( x-1,y-1 ) ) {
					dist = 0.75;
				} else if ( a( x,y ) == b( x-1,y+1 ) ) {
					dist = 0.75;
				} else if ( a( x,y ) == b( x+1,y+1 ) ) {
					dist = 0.75;
				} else if ( a( x,y ) == b( x+1,y-1 ) ) {
					dist = 0.75;
				}
			}
			if ( dist != 0 ) {
				#pragma omp critical
				difference += dist;
			}

		}
	}
	return difference;
}

Img8 Img8::dilate(double r_0) {
	auto r2 = r_0*r_0;
	std::vector < std::pair < int, int > > ballPositions;
	for (double x = -r_0-0.5; x < r_0+1; x++) {
		for (double y = -r_0-0.5; y < r_0+1; y++) {
			auto d = x*x + y*y;
			if (d < r2) {
				ballPositions.push_back({x, y});
			}
		}
	}

	Img8 ret = *this;

	#pragma omp parallel for
	for (int y = 0; y < (int)height; y++) {
		for (int x = 0; x < (int)width; x++) {
			unsigned char c = 0;
			for (auto &p : ballPositions) {
				auto a = c;
				auto b = (*this)(x+p.first,y+p.second); 
				c = (a>b)?a:b;
			}
			ret(x,y) = c;
		}
	}
	return ret;
}
Img8 Img8::erode(double r_0) {
	auto r2 = r_0*r_0;
	std::vector < std::pair < int, int > > ballPositions;
	for (double x = -r_0-1; x < r_0+1; x++) {
		for (double y = -r_0-1; y < r_0+1; y++) {
			auto d = x*x + y*y;
			if (d < r2) {
				ballPositions.push_back({x, y});
			}
		}
	}

	Img8 ret = *this;

	#pragma omp parallel for
	for (int y = 0; y < (int)height; y++) {
		for (int x = 0; x < (int)width; x++) {
			unsigned char c = 255;
			for (auto &p : ballPositions) {
				auto a = c;
				auto b = (*this)(x+p.first,y+p.second); 
				c = (a<b)?a:b;
			}
			ret(x,y) = c;
		}
	}
	return ret;
}



bool operator==( const Img8 &a, const Img8 &b ) {
	if ( a.width != b.width ) return false;
	if ( a.height != b.height ) return false;
	for ( unsigned i = 0; i < a.width*a.height; i++ ) {
		if ( a[i] != b[i] ) {
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
