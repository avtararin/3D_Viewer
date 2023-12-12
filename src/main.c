#include <stdio.h>
#include "3d_viewer.h"

int main() { 
    Data data3d;
    char filename [9] = "skull.obj";
    parse_file(filename, &data3d);
    return 0;
    }