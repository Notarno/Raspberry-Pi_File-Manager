/*
 * ***********************************************************
 * Author: Martin Lang										 *
 * Description of File: Source file for the unix command "mv"*
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
	char* destName = argv[2];
	FileManager file1(argv[1]);
	
	//Change file name to the acquired destination name and
	//check if the error "EXDEV" is returned
	if(file1.changeName(destName) != 0){
		std::string err = file1.getErrAsStr();
		//In the occurence of the "EXDEV" error
		//create a copy of the source file using the destination name as the 
		//new file name, then delete the original file
		if(err == "EXDEV"){
			std::ofstream dest;
			dest.open(destName);
			
			file1.dump(dest);
			file1.remove();
		}
	}
	
	return 0;
}
