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

#ifndef __POSITION__HPP___
#define  __POSITION__HPP___

#include <vector>
#include <tuple>
#include <ostream>

namespace tp {
namespace coord {

class Position : public std::vector < double > {
public:
	Position();
	Position( double x );
	Position( double x, double y );
	Position( double x, double y, double z );
};

Position operator+(const Position &a, const Position &b);
Position operator-(const Position &a, const Position &b);
Position operator*(const Position &a, const Position &b);
Position operator*(const Position &a, const double &b);
Position operator/(const Position &a, const Position &b);
double len2(const Position &s);
double len2(const Position &s, bool x, bool y, bool z);
Position crossProduct( const Position &u, const Position &v);

bool operator == ( const Position &l, const Position &r );
std::ostream& operator << ( std::ostream& os, Position const& value );



Position getCrossPoint (const std::pair < Position, Position > edge1, const std::pair < Position, Position > edge2);

}
}



#endif




