/*
 * ***********************************************************
 * Author: Martin Lang										 *
 * Description of File: Source file for the unix command "cp"*
 * Date created: 09/22/2019								     *
 * ***********************************************************
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "file_manager.h"


int main(int argc, char* argv[]){
	//Create an output stream that is connected to the cout output stream
	//in order to display file content on the terminal
	static std::ostream* fout;
	fout = &std::cout;
	
	//For each inputted file name in the command line arguments
	//Dump the contents into the cout output stream
	for(int i = 1; i < argc; i++){
		FileManager fileM(argv[i]);
		fileM.dump(*fout);
	}
	
	return 0;
}
