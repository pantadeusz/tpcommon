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

	SECTION( "drawing line on image max" ) {
		img.setTo(0);
		img.drawCircleLineToMax(20, 20, 70, 80, 5, 64);
		img.drawCircleLineToMax(40, 90, 70, 80, 5, 128);
		img.drawCircleLineToMax(40, 90, 20, 20, 5, 64);
		
		img.save("build/img8_testlines_max.png");
		REQUIRE(img(0,0) == 0);
		REQUIRE(img(20,20) == 64);
		REQUIRE(img(40,90) == 128);
		REQUIRE(img(30,20+(90-20)/2) == 64);
		
	}
	SECTION( "drawing line on image min" ) {
		img.setTo(255);
		img.drawCircleLineToMin(20, 20, 70, 80, 5, 64);
		img.drawCircleLineToMin(40, 90, 70, 80, 5, 128);
		img.drawCircleLineToMin(40, 90, 20, 20, 5, 64);
		
		img.save("build/img8_testlines_min.png");
		REQUIRE(img(0,0) == 255);
		REQUIRE(img(20,20) == 64);
		REQUIRE(img(40,90) == 64);
		REQUIRE(img(30,20+(90-20)/2) == 64);
		
	}

}



