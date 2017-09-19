#include <img_img8.hpp>
#include <catch.hpp>
#include <fakeit.hpp>

#include <iostream>
#include <vector>

using namespace fakeit;
using namespace tp::img;

TEST_CASE( "Img8 tests", "[Img8]" ) {
	Img8 img( 1024,1024 );
	SECTION( "constructor creates correct object" ) {
		REQUIRE( img.width == 1024 );
		REQUIRE( img.height == 1024 );
	}
}



