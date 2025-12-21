/*
* Marina Vasina
* st140082@student.spbu.ru
* LabWork1
*/

#include "BMPImg.h"

#include <fstream>
#include <stdexcept>
#include <algorithm>


void BMPImg::load(const std::string& filename) {
	std::ifstream in(filename, std::ios::binary);
	if (!in)
	{
        	throw std::runtime_error("Cannot open file");
	}
	header.loadHeaders(in);
	if (header.file.bfType != 0x4D42)
	{
		throw std::runtime_error("Not a BMP file");
	}

	if (header.inf.biBitCount != 24 || header.inf.biCompression != 0)
	{
		throw std::runtime_error("Only 24-bit BMP");
	}

	int w = header.inf.biWidth;
	int h = header.inf.biHeight;
	int padding = header.rowPadding();

	data.resize(w * h * 3);

	in.seekg(header.file.bfOffBits, std::ios::beg);

	for (int y = 0; y < h; ++y)
	{
		in.read(reinterpret_cast<char*>(&data[y * w * 3]), w * 3);
		in.ignore(padding);
	}
}

void BMPImg::save(const std::string& filename) {
	std::ofstream out(filename, std::ios::binary);
	if (!out)
	{
		throw std::runtime_error("Cannot create BMP");
	}
	BMPHeader outHeader(width(), height());
	outHeader.saveHeaders(out);

	int padding = outHeader.rowPadding();
	std::vector<uint8_t> pad(padding, 0);

	for (int y = 0; y < height(); ++y)
	{
		out.write(reinterpret_cast<const char*>(&data[y * width() * 3]), width() * 3);
		out.write(reinterpret_cast<const char*>(pad.data()), padding);
	}
}




void BMPImg::rotate90CW() {
	int w = width();
	int h = height();
	std::vector<uint8_t> result(w * h * 3);

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			for (int c = 0; c < 3; ++c)
			{
				 result[((w - x - 1) * h + y) * 3 + c] = data[(y * w + x) * 3 + c];
			}
		}
	}

	std::swap(header.inf.biWidth, header.inf.biHeight);
	data.swap(result);
}

void BMPImg::rotate90CCW() {
	int w = width();
	int h = height();
	std::vector<uint8_t> result(w * h * 3);

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			for (int c = 0; c < 3; ++c)
			{
				result[(x * h + (h - y - 1)) * 3 + c] = data[(y * w + x) * 3 + c];
			}
		}
	}

	std::swap(header.inf.biWidth, header.inf.biHeight);
	data.swap(result);
}





void BMPImg::GaussFilter() {
	int w = width();
	int h = height();
	std::vector<unsigned char> result(data.size());

	int kernelSize = 3;
	int half = kernelSize / 2;

	float kernel[3][3] = {
	{1/9.0f, 1/9.0f, 1/9.0f},
	{1/9.0f, 1/9.0f, 1/9.0f},
	{1/9.0f, 1/9.0f, 1/9.0f}
	};
	
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			float r = 0, g = 0, b = 0;

			for (int ky = -half; ky <= half; ++ky) {
				int yy = y + ky;
				if (yy < 0) yy = 0;
				if (yy >= h) yy = h - 1;

				for (int kx = -half; kx <= half; ++kx) {
					int xx = x + kx;
					if (xx < 0) xx = 0;
					if (xx >= w) xx = w - 1;

					int idx = pixel(xx, yy);
					float weight = kernel[ky + half][kx + half];

					b += data[idx] * weight;
					g += data[idx + 1] * weight;
					r += data[idx + 2] * weight;
				}
			}

			int outIdx = pixel(x, y);
			result[outIdx] = static_cast<unsigned char>(b);
			result[outIdx + 1] = static_cast<unsigned char>(g);
			result[outIdx + 2] = static_cast<unsigned char>(r);
		}
	}

	data.swap(result);
}




int BMPImg::pixel(int x, int y) const
{
    return (y * width() + x) * 3;
}