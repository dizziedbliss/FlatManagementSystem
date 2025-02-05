#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "flats.h"

const char dataset[50] = "data/data.csv";
int current = 0;
flat flats;
flat residence[size];

int main()
{
    login();
    read_file(); // reads the file data.csv and saves all the info to the RAM (residence array)
    menufn();    // calls the main menu funtion

    return 0;
}

// ver 3.1.0 stable
