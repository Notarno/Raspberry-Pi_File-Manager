/*
 * ***********************************************************
 * Author: Martin Lang										 *
 * Description of File: Source file for the unix command "ls"*
 * Date created: 09/23/2019									 *
 * ***********************************************************
 */

#include <stdio.h>
#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <time.h>
#include "file_manager.h"

int main(int argc, char* argv[]){
	std::vector<FileManager> targetDir;
	//For the option: ./myls -l [filename or dirname]
	if(argc == 3){
		//Check if users entered in the right option on the command line
		if(strcmp(argv[1], "-l") == 0){
			FileManager fileM(argv[2]);
			
			//If FileManager Object is a regular file, output the information of just that file,
			//else if FileManager Object is a directory, output the information of all elements 
			//found in that directory
			if(S_ISREG(fileM.getType())){
				std::string perm (fileM.permToStr(fileM.getPermission())); //Represents the permissions of the file in string format
				//Acquire the last modification time of the file and format it as a string
				time_t modT = fileM.getModiTime(); 
				std::string readTime = ctime(&modT);
				
				readTime.erase(24, 1);
				
				std::cout << perm << " 1 " << fileM.getOwner() << " " << fileM.getGroup() << " " << (long long)fileM.getSize() << " " << readTime << " " << fileM.getName() << std::endl;
				
			} else if(S_ISDIR(fileM.getType())){
				fileM.expand();
				targetDir = fileM.getChildren();
				
				for(int i = 0; i < (int)targetDir.size(); i++){
					std::string perm(targetDir[i].permToStr(targetDir[i].getPermission())); 
					time_t modT = targetDir[i].getModiTime();
					std::string readTime = ctime(&modT);
					
					readTime.erase(24, 1);
					
					std::cout << perm << " 1 " << targetDir[i].getOwner() << " " << targetDir[i].getGroup() << " " << (long long)targetDir[i].getSize() << " " << readTime << " " << targetDir[i].getName() << std::endl;
				}
			} else{
				std::cout  << "Invalid File Type" << std::endl;
			}
				
		} else{	
			std::cout << "Invalid option or option not supported" << std::endl;
		}
	} 
	//For the option: ./myls [filename or dirname] or ./myls -l
	else if(argc == 2){
		//Check if the user entered ./myls -l or ./myls [filename or dirname]
		if(strcmp(argv[1], "-l") == 0){
			//Make a FileManager object for the current working directory
			std::string cwd = ".";
			FileManager fileM(cwd);
			fileM.expand();
			targetDir = fileM.getChildren();
			
			for(int i = 0; i < (int)targetDir.size(); i++){
				std::string perm(targetDir[i].permToStr(targetDir[i].getPermission()));
				time_t modT = targetDir[i].getModiTime();
				std::string readTime = ctime(&modT);
				
				readTime.erase(24, 1);
				
				std::cout << perm << " 1 " << targetDir[i].getOwner() << " " << targetDir[i].getGroup() << " " << (long long)targetDir[i].getSize() << " " << readTime << " " << targetDir[i].getName() << std::endl;
			}
		} else{
			FileManager fileM(argv[1]);
			
			if(S_ISREG(fileM.getType())){
				std::cout << fileM.getName() << std::endl;
				
			} else if(S_ISDIR(fileM.getType())){			
				fileM.expand();
				targetDir = fileM.getChildren();
				
				for(int i = 0; i < (int)targetDir.size(); i++){
					std::cout << targetDir[i].getName() << std::endl;
				}
			}
		}
			
	}
	//For the option: ./myls 
	else{
		std::string cwd = ".";
		FileManager fileM(cwd);
		
		fileM.expand();
		targetDir = fileM.getChildren();
		
		for(int i = 0; i < (int)targetDir.size(); i++){
			std::cout << targetDir[i].getName() << std::endl;
		}
	}
	
	return 0;
}

