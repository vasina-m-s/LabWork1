/*
* Marina Vasina
* st140082@student.spbu.ru
* LabWork1
*/

#include "BMPHeader.h"
#include <fstream>
#include <stdexcept>

BMPHeader::BMPHeader() {
	file.bfType = 0x4D42;
	file.bfReserved1 = 0;
	file.bfReserved2 = 0;
	file.bfOffBits = sizeof(BMPFileHeader) + sizeof(BMPInfHeader);
	file.bfSize = file.bfOffBits;

	inf.biSize = 40;
	inf.biWidth = 0;
	inf.biHeight = 0;
	inf.biPlanes = 1;
	inf.biBitCount = 24;
	inf.biCompression = 0;
	inf.biSizeImage = 0;
	inf.biXPelsPerMeter = 0;
	inf.biYPelsPerMeter = 0;
	inf.biClrUsed = 0;
	inf.biClrImportant = 0;
}


BMPHeader::BMPHeader(int width, int height) {
	file.bfType = 0x4D42;
	file.bfReserved1 = 0;
	file.bfReserved2 = 0;
	file.bfOffBits = sizeof(BMPFileHeader) + sizeof(BMPInfHeader);

	inf.biSize = 40;


	inf.biWidth = width;
	inf.biHeight = height;

	int padding = rowPadding();

	inf.biSizeImage = (width * 3 + padding) * height;
	file.bfSize = file.bfOffBits + inf.biSizeImage;;


	inf.biPlanes = 1;
	inf.biBitCount = 24;
	inf.biCompression = 0;
	inf.biXPelsPerMeter = 0;
	inf.biYPelsPerMeter = 0;
	inf.biClrUsed = 0;
	inf.biClrImportant = 0;
}



int BMPHeader::rowPadding() const {
	int rowSize = inf.biWidth * 3;
	return (4 - (rowSize % 4)) % 4;
}

void BMPHeader::loadHeaders(std::ifstream& in) {
	in.read(reinterpret_cast<char*>(&file), sizeof(file));
	in.read(reinterpret_cast<char*>(&inf), sizeof(inf));
}



void BMPHeader::saveHeaders(std::ofstream& out) const {
	out.write(reinterpret_cast<const char*>(&file), sizeof(file));
	out.write(reinterpret_cast<const char*>(&inf), sizeof(inf));
}
