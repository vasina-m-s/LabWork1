/*
* Marina Vasina
* st140082@student.spbu.ru
* LabWork1
*/

#include "Image.h"
#include "BMPHeader.h"
#include "BMPImg.h"

#include <iostream>
#include <exception>
#include <string>

int main() {
	std::string filename;
	std::getline(std::cin, filename);

	try
	{
		BMPImg img;
		img.load(filename);

		BMPImg rotatedCW = img;
 		rotatedCW.rotate90CW();
		rotatedCW.save("rotated_cw.bmp");

		BMPImg rotatedCCW = img;
		rotatedCCW.rotate90CCW();
		rotatedCCW.save("rotated_ccw.bmp");

		BMPImg filtr = rotatedCW;
		filtr.GaussFilter();
		filtr.save("filtr.bmp");

		std::cout << "Completed.\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}

	return 0;
}