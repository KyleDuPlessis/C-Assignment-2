//==============================================================================
// Name        : Volimage.h
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 10/03/2019
// Description : A volumetric image tool, which can load a "stack" of 2D images
// 				 and manipulate them as a group - written in C++, Ansi-style
//==============================================================================

#include <string>
#include <vector>

#ifndef LIBS_VOLIMAGE_H
#define LIBS_VOLIMAGE_H

using namespace std;

namespace DPLKYL002 {

// static variables - initialized only once and then hold their value even through function calls
static int volImgSize = 0;
static int numImages = 0;

class VolImage {

private:
	// private members
	int width, height; // width and height of image stack
	std::vector<unsigned char**> slices; // data for each slice, in order

public:
	// public members
	VolImage(); // default constructor - define in .cpp
	~VolImage(); // destructor - define in .cpp file

// populate the object with images in stack and
// set member variables define in .cpp
	bool readImages(string baseName);

// compute difference map and write out; define in .cpp
	void diffmap(int sliceI, int sliceJ, string output_prefix);

// extract slice sliceId and write to output - define in .cpp
	void extract(int sliceId, string output_prefix);

// extract image along row i of volume, across all slices and write this to an output sequence
	void rowExtract(int r, string output_prefix);

// number of bytes used to store image data bytes
// and pointers (ignore vector<> container, dims etc)
	int volImageSize(void); // define in .cpp

};

// utility functions
int getNumImages(void);
void printOutputMsg(string commandLine, int imageSize);

}

#endif
