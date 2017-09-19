
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

unsigned char &Img8::operator()( int x, int y ) {
	if ( x<0 ) x = 0;
	if ( x>= ( int )width ) x = width-1;
	if ( y<0 ) y = 0;
	if ( y>= ( int )width ) y = width-1;
	return operator[]( y*width+x );
}
unsigned char Img8::operator()( int x, int y ) const {
	if ( x<0 ) x = 0;
	if ( x>= ( int )width ) x = width-1;
	if ( y<0 ) y = 0;
	if ( y>= ( int )width ) y = width-1;
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
