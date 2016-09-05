#include <iostream>
#include <string>
#include <vector>
#include <math.h>

#include <csim/model.h>
#include <csim/error_codes.h>
#include <csim/executable_functions.h>

#include "version.h"

void usage(int argc, char* argv[])
{
    std::cout << "This is CellML-2-BeatBox version: " << versionString() << std::endl;
}

int main(int argc, char* argv[])
{
    // check command line arguments
    usage(argc, argv);

    return 0;
}
