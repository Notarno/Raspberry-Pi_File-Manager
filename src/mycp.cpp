/*
 * ***********************************************************
 * Author: Martin Lang										 *
 * Description of File: Source file for the unix command "cp"*
 * Date created: 09/22/2019									 *
 * ***********************************************************	
 */

#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include "file_manager.h"

int main(int argc, char* argv[]){
	FileManager fileM(argv[1]);	//FileManager object for the source file to allow use of the copying method
	std::ofstream dest;			//Output stream for the destination file where the contents of the source fille will be stored

	//Open destinaton file stream and pass into the dump method to allow for copying to start
	//Close destination file stream when done
	dest.open(argv[2]);
	fileM.dump(dest);
	dest.close();
	return 0;
}
