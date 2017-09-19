#ifndef __POSITION__HPP___
#define  __POSITION__HPP___

#include <vector>
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
bool operator == ( const Position &l, const Position &r );
std::ostream& operator << ( std::ostream& os, Position const& value );

}
}



#endif




