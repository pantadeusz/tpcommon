#include <position.hpp>
#include <catch.hpp>
#include <fakeit.hpp>

#include <iostream>
#include <vector>

using namespace fakeit;
using namespace tp::coord;

TEST_CASE( "Position tests", "[Position]" ) {

	Position P(1,1,0), b(2,1,0), c(1,2,0);
	Position P2(1,1,0), b2(1,1,1), c2(1,2,0);
	
	SECTION( "pointSegmentDistance2D" ) {
		REQUIRE( pointSegmentDistance2D( P, b, c ) == Approx(::sqrt(2)/2).epsilon(0.01) );
	}
	SECTION( "pointSegmentDistance3D" ) {
		REQUIRE( pointSegmentDistance3D( P, b, c ) == Approx(::sqrt(2)/2).epsilon(0.01) );
		REQUIRE( pointSegmentDistance3D( P2, b2, c2 ) == Approx(::sqrt(2)/2).epsilon(0.01) );
	}
}



