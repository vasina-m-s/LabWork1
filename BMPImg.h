/*
* Marina Vasina
* st140082@student.spbu.ru
* LabWork1
*/


#ifndef BMP_IMAGE
#define BMP_IMAGE

#include "Image.h"
#include "BMPHeader.h"

#include <cstdint>
#include <string>
#include <vector>

class BMPImg: public Image {
	public:
		//constructor and destructor
		BMPImg() = default;
		~BMPImg() override = default;

		void load(const std::string& filename) override;
		void save(const std::string& filename) override;

		void rotate90CW() override;
		void rotate90CCW() override;

		void GaussFilter() override;

		int width() const override { return header.inf.biWidth; }
		int height() const override { return header.inf.biHeight; }

		const std::vector<uint8_t>& getData() const { return data; }

	private:
		BMPHeader header;

		std::vector<uint8_t> data;

		int pixel(int x, int y) const;
};

#endif