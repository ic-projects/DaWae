#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <dirent.h>
#include "Instruction.h"
#include "System.h"
#include "Errors.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "Please specify a binary file to run." << endl;
        exit(ERROR_INTERNAL);
    }

    // Open specified binary and attempt to load into memory
    auto *binary = new ifstream();
    binary->open(argv[1], ios::binary);

    if (!binary->is_open()) {
        cerr << "Unable to open the specified file." << endl;
        exit(ERROR_INTERNAL);
    }

    auto *system = new System();
    system->loadInstructionsFromStream(binary);
    system->start();
    return 0;
}

