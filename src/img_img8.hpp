#ifndef ___IMG_IMG8_HPP__
#define ___IMG_IMG8_HPP__

#include <vector>
#include <string>

namespace tp {
namespace img {

class Img8 : public std::vector < unsigned char > {
public:
	unsigned width, height;
	Img8( const int w, const int h );
	Img8( const std::string & fn ) {
		load( fn );
	};

	unsigned char &operator()( int x, int y );
	unsigned char operator()( int x, int y ) const;

	void save( const std::string &fname );

	void load( const std::string &fname );
};

bool operator==( const Img8 &a, const Img8 &b );
Img8 operator-( const Img8 &a, const Img8 &b );
}
}

#endif
