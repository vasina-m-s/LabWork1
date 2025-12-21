/*
* Marina Vasina
* st140082@student.spbu.ru
* LabWork1
*/

#include <gtest/gtest.h>

#include "BMPHeader.h"
#include "BMPImg.h"

#include <fstream>
#include <vector>
#include <cstdint>


static void createTestBMP(const std::string& filename)
{
	BMPHeader header;
	header.setWidth(2);
	header.setHeight(3);
	header.resize();

	std::vector<uint8_t> pixels =
	{
		0,   0, 255,   // red
		0, 255,   0,   // green

		255, 0,   0,   // blue
		255,255,255,   // white

		128,128,128,   // gray
		0,   0,   0    // black

	};

	std::ofstream out(filename, std::ios::binary);
	header.saveHeaders(out);

	uint8_t pad[2] = {0, 0};

	out.write(reinterpret_cast<char*>(pixels.data()), 6);
	out.write(reinterpret_cast<char*>(pad), 2);
	out.write(reinterpret_cast<char*>(pixels.data() + 6), 6);
	out.write(reinterpret_cast<char*>(pad), 2);
}

TEST(BMPHeaderTest, DefaultConstructor)
{
	BMPHeader header;

	EXPECT_EQ(header.getBitCount(), 24);
	EXPECT_EQ(header.getCompression(), 0);
}

TEST(BMPHeaderTest, Setters)
{
	BMPHeader header;
	header.setWidth(10);
	header.setHeight(15);

	EXPECT_EQ(header.getWidth(), 10);
	EXPECT_EQ(header.getHeight(), 15);
}

TEST(BMPHeaderTest, Load)
{	
	createTestBMP("test.bmp");
	
	BMPImg Img;

	EXPECT_NO_THROW(Img.load("test.bmp"));
	EXPECT_EQ(Img.width(), 2);
	EXPECT_EQ(Img.height(), 3);

	EXPECT_THROW(Img.load("No.bmp"), std::runtime_error);
}

TEST(BMPHeaderTest, RotateCW)
{	
	createTestBMP("test.bmp");
	
	BMPImg Img;
	Img.load("test.bmp");
	auto before = Img.getData();
	Img.rotate90CW();

	EXPECT_EQ(Img.width(), 3);
	EXPECT_EQ(Img.height(), 2);
	
	auto after = Img.getData();

	EXPECT_NE(before, after);
	
}

TEST(BMPHeaderTest, RotateCCW)
{	
	createTestBMP("test.bmp");
	
	BMPImg Img;
	Img.load("test.bmp");
	auto before = Img.getData();
	Img.rotate90CCW();
	
	EXPECT_EQ(Img.width(), 3);
	EXPECT_EQ(Img.height(), 2);
	
	auto after = Img.getData();

	EXPECT_NE(before, after);

	Img.rotate90CW();
	
	EXPECT_EQ(Img.getData(), before);
	
}


TEST(BMPImgTest, GaussFilter)
{
	createTestBMP("test.bmp");

	BMPImg Img;
	Img.load("test.bmp");
	auto before = Img.getData();

	EXPECT_NO_THROW(Img.GaussFilter());
	Img.GaussFilter();


    	auto after = Img.getData();

    	EXPECT_NE(before, after);
}



TEST(BMPImgTest, Save)
{
	createTestBMP("test.bmp");

	BMPImg Img;
	Img.load("test.bmp");

	EXPECT_NO_THROW(Img.save("out.bmp"));
	
	BMPImg Img2;
	Img2.load("out.bmp");
	EXPECT_EQ(Img.getData(), Img.getData());
}