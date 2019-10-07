/*
 * *************************************************************************************************
 * Author: Martin Lang																			   *
 * Description of File: Source file for the file_manager class that handles filesystem minipulation*
 * Date Created: 09/21/2019																		   *
 * 	************************************************************************************************					
 */
 
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include "file_manager.h"

/**
 * Function Declaration: FileManager(std::string)
 * 
 * Function Description:
 * Constructor method for the FileManager class, invokes
 * the initializing function.
 * 
 * @param String variable n, representing the name of the file
 * @return The initialized FileManger object
 */
FileManager::FileManager(std::string n){
	name = n;
	errNum = 0;
	//Call initializing function
	initFileAttr();
}

/**
 * Function Declaration: ~FileManager()
 * 
 * Function Description:
 * Destructor method for the FileManager class
 * 
 * @param N/A
 * @return N/A
 */
FileManager::~FileManager(){
}

/**
 * Function Declaration: void initFileAttr()
 * 
 * Function Description:
 * initializes the data members of the class with the values
 * aqcuired from the stat() function. If a file does not exist
 * initializes data members to zero and set errNum respected error.
 * 
 * @param N/A
 * @return N/A
 */

void FileManager::initFileAttr(){
	struct stat myStat;
	//Check to see if File exists or not
	if((stat(name.c_str(), &myStat)) == 0){
		type = myStat.st_mode;
		size = myStat.st_size;
		owner = myStat.st_uid;
		group = myStat.st_gid;
		perm = myStat.st_mode;
		accessTime = myStat.st_atime;
		modiTime = myStat.st_mtime;
		statChTime = myStat.st_ctime;
		blkSize = myStat.st_blksize;
	} else{
		std::cout << name << ": no such file or directory exists" << std::endl;
		errNum = errno;
		type = 0;
		size = 0;
		owner = 0;
		group = 0;
		perm = 0;
		accessTime = 0;
		modiTime = 0;
		statChTime = 0;
		blkSize = 0;
	}
}

/**
 * Function Declaration: getName()
 * 
 * Function Description:
 * returns the name of the FileManager object.
 * 
 * @param N/A
 * @return The name of the FileManager object
 */
std::string FileManager::getName(){
	return name;
}

/**
 * Function Declaration: mode_t getType()
 * 
 * Function Description:
 * returns the type of the FileManager object.
 * 
 * @param N/A
 * @return The type of the FileManager object
 */
mode_t FileManager::getType(){
	return type;
}

/**
 * Function Declaration: off_t getSize()
 * 
 * Function Description:
 * returns the size of the FileManager object.
 * 
 * @param N/A
 * @return The size of the FileManager object
 */
off_t FileManager::getSize(){
	return size;
}

/**
 * Function Declaration: char* getOwner()
 * 
 * Function Description:
 * returns the owner of the FileManager object
 * in string format.
 * 
 * @param N/A
 * @return The owner of the FileManager object
 */
char* FileManager::getOwner(){
	struct passwd *pw = getpwuid(owner);
	return pw->pw_name;
}

/**
 * Function Declaration: char* getGroup()
 * 
 * Function Description:
 * returns the group of the FileManager object
 * in string format.
 * 
 * @param N/A
 * @return The group of the FileManager object
 */
char* FileManager::getGroup(){
	struct group *grp = getgrgid(group);
	return grp->gr_name;
}

/**
 * Function Declaration: mode_t getPermission()
 * 
 * Function Description:
 * returns the permissions of the FileManager object
 * which are the 9 least significant bits of the
 * st_mode variable.
 * 
 * @param N/A
 * @return The permissions of the FileManager object
 */
mode_t FileManager::getPermission(){
	return perm & 0x1FF;
}

/**
 * Function Declaration: time_t getAccTime()
 * 
 * Function Description:
 * returns the last time of access of the FileManager object
 * 
 * @param N/A
 * @return The last time of access of the FileManager object
 */
time_t FileManager::getAccTime(){
	return accessTime;
}

/**
 * Function Declaration: time_t getModiTime()
 * 
 * Function Description:
 * returns the last time of modification of the FileManager object
 * 
 * @param N/A
 * @return The last time of modification of the FileManager object
 */
time_t FileManager::getModiTime(){
	return modiTime;
}

/**
 * Function Declaration: time_t getStatChTime()
 * 
 * Function Description:
 * returns the last time of status change of the FileManager object
 * 
 * @param N/A
 * @return The last time of status change of the FileManager object
 */
time_t FileManager::getStatChTime(){
	return statChTime;
}

/**
 * Function Declaration: blksize_t getBlkSize()
 * 
 * Function Description:
 * returns the block size of the FileManager object
 * 
 * @param N/A
 * @return The block size of the FileManager object
 */
blksize_t FileManager::getBlkSize(){
	return blkSize;
}

/**
 * Function Declaration: int getErrAsNum()
 * 
 * Function Description:
 * returns the error variable as an integer
 * 
 * @param N/A
 * @return The error variable of the FileManager object
 */
int FileManager::getErrAsNum(){
	return errNum;
}

/**
 * Function Declaration: std::string getErrAsStr()
 * 
 * Function Description:
 * returns the error varible as a string
 * 
 * @param N/A
 * @return The error variable of the FileManager object
 */
std::string FileManager::getErrAsStr(){
	std::string errStr(strerror(errNum));
	return errStr;
}

/**
 * Function Declaration: std::vector<FileManager> getChildren()
 * 
 * Function Description:
 * returns a vector of FileManager object that hold the different files
 * and directories found in the target directory
 * 
 * @param N/A
 * @return A vector of FileManager objects
 */
std::vector<FileManager> FileManager::getChildren(){
	return childrenVec;
}

/**
 * Function Declaration: void setName()
 * 
 * Function Description:
 * Sets the name of the FileManager object
 * 
 * @param a char pointer variable that represents the new name
 * @return N/A
 */
void FileManager::setName(char* n){
	changeName(n);
}

/**
 * Function Declaration: int dump(std::ostream&)
 * 
 * Function Description:
 * Dumps the content of the current FileManager object into 
 * a target file stream.
 * 
 * @param An output destination file stream
 * @return The error code
 */
int FileManager::dump(std::ostream& dest){
	char buffer[blkSize];
	std::ifstream src;
	
	//Check to see if the object is a regular file or not
	if(S_ISREG(type)){
		//Open source stream and check for errors
		src.open(name);
		if(!src){
			errNum = ECANCELED;
		} else{
			//Extract lines from source and place into destination until end of file
			while(!src.eof()){
				src.getline(buffer, blkSize);
				dest << buffer << std::endl;
			}
			
			src.close();
			errNum = 0;
		}
	} else{
		errNum = ENOTSUP;
	}
	
	return errNum;
}

/**
 * Function Declaration: int changeName(char*)
 * 
 * Function Description:
 * Changes the name associated with the FileManager object with 
 * a new specificied name.
 * 
 * @param A char pointer variable that represents the new name
 * @return The error code
 */
int FileManager::changeName(char* n){
	if(rename(name.c_str(), n) == 0){
		FileManager child();
		name = n;
		errNum = 0;
	} else{
		errNum = errno;
	}
	
	return errNum;
}

/**
 * Function Declaration: int remove(std::ostream&)
 * 
 * Function Description:
 * Removes the file by unlinking it and deleting its FileManager object.
 * 
 * @param N/A
 * @return The error code
 */
int FileManager::remove(){
	if(unlink(name.c_str()) == 0){
		errNum = 0;
		type = 0;
		size = 0;
		owner = 0;
		group = 0;
		perm = 0;
		accessTime = 0;
		modiTime = 0;
		statChTime = 0;
		blkSize = 0;
	} else{
		errNum = errno;
	}
	
	return errNum;
}

/**
 * Function Declaration: int compare(FileManager)
 * 
 * Function Description:
 * Compares the current FileManager object with a
 * specified second object, to see if they are the same or 
 * not.
 * 
 * @param A FileManager object
 * @return The error code
 */
int FileManager::compare(FileManager p){
	char buffer1[blkSize];
	char buffer2[p.getBlkSize()];
	int numOfLine1 = 0;
	int numOfLine2 = 0;
	std::ifstream stream1, stream2;
	
	//Check if both objects are regular files
	if (S_ISREG(type) && S_ISREG(p.getType())){
		//Open stream for both files
		stream1.open(name);
		stream2.open(p.getName());
		
		if(!stream1 || !stream2){
			errNum = ECANCELED;
		} else{
			errNum = 0;
			//Acquire and compare each line of each file to each other to find any differences 
			while(!stream1.eof() && !stream2.eof()){
				//Count number of lines each file has
				++numOfLine1;
				++numOfLine2;
				
				stream1.getline(buffer1, blkSize);
				stream2.getline(buffer2, p.getBlkSize());
				
				//If a difference is found, files are not the same
				if(strcmp(buffer1, buffer2) != 0){
					std::cout << "The Files are not the same! (Difference in characters)" << std::endl;
					return errNum;
				}
			}
			
			//If files have the same number of lines, they are the same
			//otherwise they are different
			if(numOfLine1 == numOfLine2){
				std::cout << "The Files are the same!" << std::endl;
			} else{
				std::cout << "The Files are not the same! (Difference in number of lines)" << std::endl;
				return errNum;
			}
		}
	} else{
		errNum = ENOTSUP;
	}
		
	return errNum;
}

/**
 * Function Declaration: int expand()
 * 
 * Function Description:
 * If the FileManager object is a directory, this function expands the 
 * contents of it and creates a new object for each element in the directory
 * and stores it in a vector.
 * 
 * @param N/A
 * @return The error code
 */
int FileManager::expand(){
	struct dirent* rDir;
	DIR* oDir;
	
	//Check if object is a direcotry
	if(S_ISDIR(type)){
		//Open directory stream
		oDir = opendir(name.c_str());
		while(oDir){
			errNum = 0;
			errno = 0;
			//Read element from directory stream
			if((rDir = readdir(oDir)) != NULL){
				if(rDir->d_type == DT_REG){
					//Add element to vector
					FileManager child(name + "/" + rDir->d_name);
					childrenVec.push_back(child);
				}
			} else{
				if (errno == 0){
					closedir(oDir);
					return errNum;
				}
				closedir(oDir);
				errNum = errno;
				return errNum;
			}
		}
		errNum = errno;
		return errNum;
	} else{
		errNum = ENOTSUP;
	}
	
	return errNum;
}

/**
 * Function Declaration: std::string permToStr(unsigned long)
 * 
 * Function Description:
 * Converts the permission of the FileManager object from unsigned long
 * to string format
 * 
 * @param The permission variable in unsigned long format
 * @return The permission variable in string format
 */
std::string FileManager::permToStr(unsigned long perm){
	std::string permStr ("-");
	//Checks each of the 9 bits to see whether
	//or not if it has been set to 1;
	if(CHECK_BIT(perm, 8) == 256)
		permStr += "r";
	else
		permStr += "-";
		
	if(CHECK_BIT(perm, 7) == 128)
		permStr += "w";
	else
		permStr += "-";
		
	if(CHECK_BIT(perm, 6) == 64)
		permStr += "x";
	else
		permStr += "-";	
		
	if(CHECK_BIT(perm, 5) == 32)
		permStr += "r";
	else
		permStr += "-";
		
	if(CHECK_BIT(perm, 4) == 16)
		permStr += "w";
	else
		permStr += "-";
		
	if(CHECK_BIT(perm, 3) == 8)
		permStr += "x";
	else
		permStr += "-";

	if(CHECK_BIT(perm, 2) == 4)
		permStr += "r";
	else
		permStr += "-";

	if(CHECK_BIT(perm, 1) == 2)
		permStr += "w";
	else
		permStr += "-";

	if(CHECK_BIT(perm, 0) == 1)
		permStr += "x";
	else
		permStr += "-";
		
	return permStr;
}
