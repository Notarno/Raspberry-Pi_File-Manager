/*
 * ***********************************************************
 * Author: Martin Lang										 *	
 * Description of File: Source file for the unix command "rm"*
 * Date created: 09/26/2019									 *
 * ***********************************************************
 */

#include <stdio.h>
#include <iostream>
#include <vector>
#include "file_manager.h"

int main(int argc, char* argv[]){
	std::vector<FileManager> fileList;
	
	//Create FileManager object instances for each file name given in the command arguments
	for(int i = 1; i < argc; i++){
		FileManager fileM(argv[i]);
		fileList.push_back(fileM);
	}
	
	//Compare the two FileManager objects to see if they are the same or not
	fileList[0].compare(fileList[1]);
	return 0;
}
