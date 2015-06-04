#include "Helper.h"

bool fileExists(string filename) {
	ifstream file(filename.c_str());
	printf("file good: %d\n", file.good());
	return file.good();
}
