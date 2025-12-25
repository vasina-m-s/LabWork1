/*
* Marina Vasina
* st140082@student.spbu.ru
* LabWork1
*/

#ifndef BMPHEADER
#define BMPHEADER

#include <cstdint>
#include <string>
#include <fstream>

static constexpr int BMPChannels = 3;
static constexpr int BMPAlignments =4;

static constexpr uint32_t BFType = 0x4D42;
static constexpr uint32_t BISize = 40;
static constexpr uint32_t Planes = 1;
static constexpr uint32_t BITCount= 24;
static constexpr uint32_t BICompression = 0;

#pragma pack(push, 1)

struct BMPFileHeader {
	uint16_t bfType;
	uint32_t bfSize;
	uint16_t bfReserved1;
	uint16_t bfReserved2;
	uint32_t bfOffBits;
};


struct BMPInfHeader {
	uint32_t biSize;
	int32_t biWidth;
	int32_t biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	int32_t biXPelsPerMeter;
	int32_t biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
};





class BMPHeader {
	public:

		int rowPadding() const;
	

		BMPHeader();
		BMPHeader(int width, int height);

		void loadHeaders(std::ifstream& in);
		void saveHeaders(std::ofstream& out) const;

		//Getters and Setters
		int getWidth() const { return inf.biWidth; }
		int getHeight() const { return inf.biHeight; }
		uint16_t getBitCount() const { return inf.biBitCount;}

		void setWidth(int width) {
			inf.biWidth = width;
			resize();
		}

		void setHeight(int height) {
			inf.biHeight = height;
			resize();
		}
		
		int getCompression() const { return inf.biCompression; }



		void resize() {
			int padding = rowPadding();
			inf.biSizeImage = (inf.biWidth * BMPChannels + padding) * inf.biHeight;
			file.bfSize = file.bfOffBits + inf.biSizeImage;
		}

		BMPFileHeader file;
		BMPInfHeader inf;
};



#pragma pack(pop)

#endif