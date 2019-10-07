/*
 * ***********************************************************
 * Author: Martin Lang										 *
 * Description of File: Source file for the unix command "rm"*
 * Date created: 09/26/2019									 *
 * ***********************************************************
 */

#include <stdio.h>
#include <iostream>
#include "file_manager.h"

int main(int argc, char* argv[]){
	//Remove each file from the filesystem entered on the command line
	for(int i = 1; i < argc; i++){
		FileManager fileM(argv[i]);
		
		fileM.remove();
	}
	return 0;
}
