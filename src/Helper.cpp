#include "Helper.h"

bool fileExists(string filename) {
	ifstream file(filename.c_str());
	return file.good();
}
