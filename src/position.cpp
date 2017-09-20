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

#include "position.hpp"
#include <vector>

namespace tp {
namespace coord {

Position::Position():std::vector < double >( 3 ) {};
Position::Position( double x ):std::vector < double >( 3 ) {
	( *this )[0] = x;
	( *this )[1] = 0;
	( *this )[2] = 0;
};
Position::Position( double x, double y ) : std::vector < double >( 3 ) {
	( *this )[0] = x;
	( *this )[1] = y;
	( *this )[2] = 0;
};
Position::Position( double x, double y, double z ) : std::vector < double >( 3 ) {
	( *this )[0] = x;
	( *this )[1] = y;
	( *this )[2] = z;
};

Position operator+( const Position &a, const Position &b ) {
	return Position( a[0]+b[0],a[1]+b[1],a[2]+b[2] );
}
Position operator-( const Position &a, const Position &b ) {
	return Position( a[0]-b[0],a[1]-b[1],a[2]-b[2] );
}
Position operator*( const Position &a, const Position &b ) {
	return Position( a[0]*b[0],a[1]*b[1],a[2]*b[2] );
}
Position operator*( const Position &a, const double &b ) {
	return Position( a[0]*b,a[1]*b,a[2]*b );
}
Position operator/( const Position &a, const Position &b ) {
	return Position( a[0]/b[0],a[1]/b[1],a[2]/b[2] );
}
double len2( const Position &s ) {
	return s[0]*s[0]+s[1]*s[1]+s[2]*s[2];
}
double len2( const Position &s, bool x, bool y, bool z ) {
	return ( x?s[0]*s[0]:0 )+( y?s[1]*s[1]:0 )+( z?s[2]*s[2]:0 );
}

bool operator == ( const Position &l, const Position &r ) {
	return ( l[0]==r[0] ) && ( l[1]==r[1] ) && ( l[2]==r[2] );
};

std::ostream& operator << ( std::ostream& os, Position const& value ) {
	os << value[0] << ", " << value[1] << ", " << value[2] ;
	return os;
}

}
}






