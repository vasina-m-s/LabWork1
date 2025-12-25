/*
* Marina Vasina
* st140082@student.spbu.ru
* LabWork1
*/

#include "BMPHeader.h"
#include <fstream>
#include <stdexcept>

BMPHeader::BMPHeader() {
	file.bfType = BFType;
	file.bfReserved1 = 0;
	file.bfReserved2 = 0;
	file.bfOffBits = sizeof(BMPFileHeader) + sizeof(BMPInfHeader);
	file.bfSize = file.bfOffBits;

	inf.biSize = BISize;
	inf.biWidth = 0;
	inf.biHeight = 0;
	inf.biPlanes = Planes;
	inf.biBitCount = BITCount;
	inf.biCompression = BICompression;
	inf.biSizeImage = 0;
	inf.biXPelsPerMeter = 0;
	inf.biYPelsPerMeter = 0;
	inf.biClrUsed = 0;
	inf.biClrImportant = 0;
}


BMPHeader::BMPHeader(int width, int height) {
	file.bfType = BFType;
	file.bfReserved1 = 0;
	file.bfReserved2 = 0;
	file.bfOffBits = sizeof(BMPFileHeader) + sizeof(BMPInfHeader);

	inf.biSize = BISize;


	inf.biWidth = width;
	inf.biHeight = height;

	int padding = rowPadding();

	inf.biSizeImage = (width * BMPChannels + padding) * height;
	file.bfSize = file.bfOffBits + inf.biSizeImage;;


	inf.biPlanes = Planes;
	inf.biBitCount = BITCount;
	inf.biCompression = BICompression;
	inf.biXPelsPerMeter = 0;
	inf.biYPelsPerMeter = 0;
	inf.biClrUsed = 0;
	inf.biClrImportant = 0;
}



int BMPHeader::rowPadding() const {
	int rowSize = inf.biWidth * BMPChannels;
	return (BMPAlignments - (rowSize % BMPAlignments)) % BMPAlignments;
}

void BMPHeader::loadHeaders(std::ifstream& in) {
	in.read(reinterpret_cast<char*>(&file), sizeof(file));
	in.read(reinterpret_cast<char*>(&inf), sizeof(inf));
}



void BMPHeader::saveHeaders(std::ofstream& out) const {
	out.write(reinterpret_cast<const char*>(&file), sizeof(file));
	out.write(reinterpret_cast<const char*>(&inf), sizeof(inf));
}
