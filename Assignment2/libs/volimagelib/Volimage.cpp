//==============================================================================
// Name        : Volimage.cpp
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 10/03/2019
// Description : A volumetric image tool, which can load a "stack" of 2D images
// 				 and manipulate them as a group - written in C++, Ansi-style
//==============================================================================

#include "Volimage.h"

#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// default constructor
DPLKYL002::VolImage::VolImage() {

	width = 0;
	height = 0;

}

// destructor
DPLKYL002::VolImage::~VolImage() {

	for (int i = 0; i < slices.size(); i++) {

		for (int h = 0; h < height; h++) {

			delete[] (slices.at(i))[h];

		}

		delete[] slices.at(i);

	}

}

// print output message
void DPLKYL002::printOutputMsg(string commandLine, int imageSize) {

	cout << "\t---------- Volumetric Image Manipulation Tool ----------\n" << endl;
	cout << commandLine << endl;
	cout << "Number of images: " << getNumImages() << endl;
	cout << "Number of bytes required: " << imageSize << endl;
	cout << endl;

}

// return number of images
int DPLKYL002::getNumImages(void) {

	return numImages;

}

// extract image along row r of volume, across all slices and write this to an output sequence
void DPLKYL002::VolImage::rowExtract(int r, string output_prefix) {

	volImgSize = 0;

    	int rHeight = slices.size();
    	int rWidth = width;


	ofstream file(output_prefix + ".dat");

	if (file.is_open()) {

		file << rWidth << " " << rHeight << " " << 1;

		file.close();

	} else {

		cout << "Unable to open " << output_prefix << ".dat" << endl;

	}

	file.open(output_prefix + ".raw", ios::binary);

	if (file.is_open()) {

		for (int i = 0; i < numImages; i++) {

			for (int w = 0; w < width; w++) {

				file << slices.at(i)[r][w];

				volImgSize += sizeof(slices.at(i)[r][w]);

			}

		}

		file.close();

	} else {

		cout << "Unable to open " << output_prefix << ".raw" << endl;

	}

	numImages = 1;

}

// extract slice sliceId and write to output
void DPLKYL002::VolImage::extract(int sliceId, string output_prefix) {

	volImgSize = 0;
	numImages = 1;

	ofstream file(output_prefix + ".dat");

	if (file.is_open()) {

		file << width << " " << height << " " << numImages;

		file.close();

	} else {

		cout << "Unable to open " << output_prefix << ".dat" << endl;

	}

	file.open(output_prefix + ".raw", ios::binary);

	if (file.is_open()) {

		for (int h = 0; h < height; h++) {

			for (int w = 0; w < width; w++) {

				file << slices.at(sliceId)[h][w];

				volImgSize += sizeof(slices.at(sliceId)[h][w]);

			}
		}

		file.close();

	} else {

		cout << "Unable to open " << output_prefix << ".raw" << endl;

	}
}

// number of bytes used to store image data bytes and pointers (ignore vector<> container, dims etc)
int DPLKYL002::VolImage::volImageSize(void) {

	return volImgSize;

}

// compute difference map and write out
void DPLKYL002::VolImage::diffmap(int sliceI, int sliceJ, string output_prefix) {

	volImgSize = 0;
	numImages = 1;

	ofstream file(output_prefix + ".dat");

	if (file.is_open()) {

		file << width << " " << height << " " << numImages;

		file.close();

	} else {

		cout << "Unable to open " << output_prefix << ".dat" << endl;

	}

	file.open(output_prefix + ".raw", ios::binary);

	if (file.is_open()) {

		for (int h = 0; h < height; h++) {

			for (int w = 0; w < width; w++) {

				/*Every output pixel at coordinate (r,c) is computed as follows:
				(unsigned char)(abs((float)volume[i][r][c] - (float)volume[j][r][c])/2)*/

				unsigned char pixelCoordinate = (unsigned char) abs(
						((float) slices[sliceI][h][w]
								- (float) slices[sliceJ][h][w]) / 2);

				file << pixelCoordinate;

				volImgSize += sizeof(pixelCoordinate);

			}

		}

		file.close();

	} else {

		cout << "Unable to open " << output_prefix << ".raw" << endl;

	}
}

// populate the object with images in stack and set member variables
bool DPLKYL002::VolImage::readImages(string baseName) {

	ifstream file((baseName + ".data").c_str());

	if (!file) {

		cout << "Unable to open " << baseName << ".data" << endl;

		return false;

	}

	// ws discards whitespace
	file >> width >> ws;
	file >> height >> ws;
	file >> numImages >> ws;

	file.close();

	for (int i = 0; i < numImages; i++) {

		ostringstream ss;
		ss << i;

		ifstream file((baseName + ss.str() + ".raw").c_str(), ios::binary);

		if (!file) {

			cout << "Unable to open " << baseName << ".raw" << endl;

			return false;

		}

		unsigned char ** arr = new unsigned char *[height];

		volImgSize += sizeof(arr);

		for (int h = 0; h < height; h++) {

			arr[h] = new unsigned char[width];
			volImgSize += sizeof(arr[h]);

			for (int w = 0; w < width; w++) {

				if (!file.eof()) {

					char * pointer = (char *) &arr[h][w];
					file.read(pointer, 1);
					volImgSize += 1;

				}
			}
		}

		file.close();

		slices.push_back(arr);

	}

	return true;

}
