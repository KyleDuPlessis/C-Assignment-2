//==============================================================================
// Name        : Driver.cpp
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 10/03/2019
// Description : A volumetric image tool, which can load a "stack" of 2D images
// 				 and manipulate them as a group - written in C++, Ansi-style
//==============================================================================

#include <iostream>
#include <sstream>

#include "Volimage.h"

using namespace std;

// main function
int main(int argc, char * argv[]) { // argc and argv values passed into main

	// argc - number of all items on command line
	// argv array - contains simple C-strings for each of these items
	// argv[0] is always the application name, and argv[1] the first argument

	string commandLine; // contains output message
	DPLKYL002::VolImage vol;

	// if number of items on command line is greater than 2
	if (argc > 2)
		vol.readImages(string(argv[2])); // pass image sequence (i.e. MRI) into readImages function

	// switch argc - order of arguments is clearly specified
	switch (argc) {

	// if 3 arguments (application name included)
	// no optional flags - build the internal representation
	case 3:

		if (string(argv[1]) != "volimage")
			return 0; // incorrect arguments
		commandLine =
				"\nCommand run: volimage <imageBase>\nCommand description: Load image base "
						+ string(argv[2])
						+ " to memory (build internal representation)";
		DPLKYL002::printOutputMsg(commandLine, vol.volImageSize()); // print output message for no requested operation

		break;

	// if 6 arguments (application name included)
	// optional flags - extract operation / extract row operation
	case 6:

		if (string(argv[1]) != "volimage"
				|| (string(argv[3]) != "-x" && string(argv[3]) != "-g"))
			return 0; // incorrect arguments
		// optional flag - extract operation
		if (string(argv[3]) == "-x") {
			istringstream ss(argv[4]); // pass image number into ss
			int i;
			ss >> i;
			vol.extract(i, string(argv[5])); // extract slice with index i given and write this to an output sequence
			commandLine =
					"\nCommand run: volimage <imageBase> [-x i output_file_name]\nCommand description: Retrieve the slice with the index given and write this to an output sequence";
			DPLKYL002::printOutputMsg(commandLine, vol.volImageSize()); // print output message for requested operation

		}
		// optional flag - extract row operation
		else if (string(argv[3]) == "-g") {
			istringstream ss(argv[4]); // pass image number into ss
			int i;
			ss >> i;
			vol.rowExtract(i, string(argv[5])); // extract image along row i of volume, across all slices and write this to an output sequence
			commandLine =
					"\nCommand run: volimage <imageBase> [-g i output_file_name]\nCommand description: Extract an image along row i of the volume, across all slices and write this to an output sequence";
			DPLKYL002::printOutputMsg(commandLine, vol.volImageSize()); // print output message for requested operation
		}

		break;

	// if 7 arguments (application name included)
	// optional flag - difference map operation
	case 7:

		if (string(argv[1]) != "volimage" || string(argv[3]) != "-d")
			return 0; // incorrect arguments
		// optional flag - difference map operation
		if (string(argv[3]) == "-d") {
			istringstream ss(argv[4]); // pass image number into ss
			int i, j;
			ss >> i;
			ss.clear(); // clear input string stream *****
			ss.str(argv[5]); // pass image number into str
			ss >> j;
			vol.diffmap(i, j, string(argv[6])); // compute the difference map between slices i and j, and write this to an output sequence
			commandLine =
					"\nCommand run: volimage <imageBase> [-d i j output_file_name]\nCommand description: Compute the difference map between slices i and j, and write this to an output sequence";
			DPLKYL002::printOutputMsg(commandLine, vol.volImageSize()); // print output message for requested operation
		}

		break;

	default:

		cout << "Incorrect arguments!" << endl;

		return 0;

	}

	return 0;

}
