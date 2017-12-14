#include <img_img8.hpp>
#include <catch.hpp>
#include <fakeit.hpp>

#include <iostream>
#include <vector>

using namespace fakeit;
using namespace tp::img;

TEST_CASE( "Img8 tests", "[Img8]" ) {
	Img8 img( 256, 256);
	SECTION( "constructor creates correct object" ) {
		REQUIRE( img.width == 256 );
		REQUIRE( img.height == 256 );
	}

	SECTION( "drawing line on image max" ) {
		Img8 imgtest("tests/data/img8_testlines_max.png");
		img.setTo(0);
		img.drawCircleLineToMax(20, 20, 70, 80, 10, 64);
		img.drawCircleLineToMax(40, 90, 70, 80, 10, 128);
		img.drawCircleLineToMax(40, 90, 20, 20, 10, 64);
		img.drawCircleLineToMax(20, 120, 80, 120, 10, 128);
		
		img.save("build/img8_testlines_max.png");
		REQUIRE(img(0,0) == 0);
		REQUIRE(img(20,20) == 64);
		REQUIRE(img(40,90) == 128);
		REQUIRE(img(30,20+(90-20)/2) == 64);
		REQUIRE(img == imgtest);
		
	}
	SECTION( "drawing line on image min" ) {
		Img8 imgtest("tests/data/img8_testlines_min.png");
		img.setTo(255);
		img.drawCircleLineToMin(20, 20, 70, 80, 10, 64);
		img.drawCircleLineToMin(40, 90, 70, 80, 10, 128);
		img.drawCircleLineToMin(40, 90, 20, 20, 10, 64);
		img.drawCircleLineToMin(20, 120, 80, 120, 10, 128);

		img.save("build/img8_testlines_min.png");
		REQUIRE(img(0,0) == 255);
		REQUIRE(img(20,20) == 64);
		REQUIRE(img(40,90) == 64);
		REQUIRE(img(30,20+(90-20)/2) == 64);
		REQUIRE(img == imgtest);
	}
	SECTION( "dilate operation on drawed image" ) {
		Img8 imgtest("tests/data/img8_testlines_dilate_1.png");
		img.setTo(255);
		img.drawCircleLineToMin(20, 20, 70, 80, 16, 64);
		img.drawCircleLineToMin(40, 90, 70, 80, 16, 128);
		img.drawCircleLineToMin(40, 90, 20, 20, 16, 64);

		img.drawCircleLineToMin(20, 120, 80, 120, 16, 128);
		
		img = img.dilate(6);
		img.save("build/img8_testlines_dilate_1.png");
		REQUIRE(img(0,0) == 255);
		REQUIRE(img(20,20) == 64);
		REQUIRE(img(40,90) == 64);
		REQUIRE(img(30,20+(90-20)/2) == 64);
		REQUIRE(img == imgtest);
	}
	SECTION( "erode operation on drawed image" ) {
		Img8 imgtest("tests/data/img8_testlines_erode_1.png");
		img.setTo(255);
		img.drawCircleLineToMin(20, 20, 70, 80, 16, 64);
		img.drawCircleLineToMin(40, 90, 70, 80, 16, 128);
		img.drawCircleLineToMin(40, 90, 20, 20, 16, 64);
		img.drawCircleLineToMin(20, 120, 80, 120, 16, 128);
		
		img = img.erode(6);
		img.save("build/img8_testlines_erode_1.png");
		REQUIRE(img(0,0) == 255);
		REQUIRE(img(20,20) == 64);
		REQUIRE(img(40,90) == 64);
		REQUIRE(img(30,20+(90-20)/2) == 64);
		REQUIRE(img == imgtest);
	}
	SECTION( "fast dilate operation giving the same results as dilate" ) {
		img.setTo(255);
		img.drawCircleLineToMin(20, 20, 70, 80, 16, 64);
		img.drawCircleLineToMin(40, 90, 70, 80, 16, 128);
		img.drawCircleLineToMin(40, 90, 20, 20, 16, 64);

		img.drawCircleLineToMin(20, 120, 80, 120, 16, 128);
		
		Img8 imgtest = img.dilate_old(6);
		img = img.dilate(6);
		
		img.save("build/img8_testlines_dilate_1.png");
		REQUIRE(img(0,0) == 255);
		REQUIRE(img(20,20) == 64);
		REQUIRE(img(40,90) == 64);
		REQUIRE(img(30,20+(90-20)/2) == 64);
		REQUIRE(img == imgtest);
	}

}



