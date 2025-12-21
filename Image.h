/*
* Marina Vasina
* st140082@student.spbu.ru
* LabWork1
*/


#ifndef IMAGE
#define IMAGE

#include <string>

class Image {
	public:
		//destructor
    		virtual ~Image() = default;

    		virtual int width() const = 0;
    		virtual int height() const = 0;

    		virtual void load(const std::string& filename) = 0;
    		virtual void save(const std::string& filename) = 0;

    		virtual void rotate90CW() = 0;
    		virtual void rotate90CCW() = 0;
    		virtual void GaussFilter() = 0;
};

#endif