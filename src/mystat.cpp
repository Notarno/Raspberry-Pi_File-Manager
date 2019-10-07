/*
 * *************************************************************
 * Author: Martin Lang										   *
 * Description of File: Source file for the unix command "stat"*
 * Date created: 09/26/2019									   *
 * *************************************************************
 */

#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string>
#include "file_manager.h"

int main(int argc, char* argv[]){
	FileManager fileM(argv[1]);
	std::string perm (fileM.permToStr(fileM.getPermission())); //Acquire permissions of the file and represent it in string format
	time_t acc = fileM.getAccTime();
	time_t mod = fileM.getModiTime();
	time_t statCh = fileM.getStatChTime();
	
	std::cout << "File name: " << fileM.getName() << std::endl;
	std::cout << "File Type: ";
	//Check the file type of the FileManager object
	switch(fileM.getType() & S_IFMT){
		case S_IFBLK: 
			printf("block device\n");
			break;
		case S_IFCHR:
			printf("character device\n");
			break;
		case S_IFDIR:
			printf("directory\n");
			break;
		case S_IFIFO:
			printf("FIFO/pipe\n");
			break;
		case S_IFLNK:
			printf("symlink\n");
			break;
		case S_IFREG:
			printf("regular file\n");
			break;
		case S_IFSOCK:
			printf("socket\n");
			break;
		default:
			printf("unknown?\n");
	}
	
	std::cout << "File Size: " << (long long)fileM.getSize() << " bytes" << std::endl;
	std::cout << "File Owner UID: " << fileM.getOwner() << std::endl;
	std::cout << "File Group GID: " << fileM.getGroup() << std::endl;
	std::cout << "File Permissions: " << perm << std::endl;
	std::cout << "File Block Size: " << fileM.getBlkSize() << " bytes" <<  std::endl; 
	std::cout << "Last File Access Time: " << ctime(&acc);
	std::cout << "Last File Modification: " << ctime(&mod);
	std::cout << "Last Status Change: " << ctime(&statCh);
	
	return 0;
}
