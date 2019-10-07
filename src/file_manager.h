/*
 * **************************************************************************************************
 * Author: Martin Lang																				*
 * Description of File: Header file for the file_manager class that handles filesystem minipulation *
 * Date Created: 09/21/2019																			*
 * **************************************************************************************************
 */
#ifndef FILE_MANAGER_H_INCLUDED
#define FILE_MANAGER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>


#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

class FileManager{
	public:
		/* Constructor */
		FileManager(std::string);

		/* Destructor */
		~FileManager();
		
		/* Initialize File Attributes */
		void initFileAttr();
		
		/* Get functions */
		// Returns the Name of the File
		std::string getName(); 

		// Returns the Type of the File
		mode_t getType();

		// Returns the Size of the File
		off_t getSize();

		// Returns the Owner of the File
		char* getOwner();

		// Returns the Group of the File
		char* getGroup();

		// Returns the Permissions of the File
		mode_t getPermission();

		// Returns the Last Time of Access of the File
		time_t getAccTime();

		// Returns the Last Time of Modification of the File
		time_t getModiTime();

		// Returns the Last Time of Status Change of the File
		time_t getStatChTime();

		// Retruns the Block Size of the File
		blksize_t getBlkSize();

		// Returns the Error variable as a Number
		int getErrAsNum();

		// Returns the Error varaible as a String
		std::string getErrAsStr();
		
		// Returns the Children of the Directory
		std::vector<FileManager> getChildren();
		
		/* Set Functions */
		// Renames the File
		void setName(char*);
		
		/* Dump Function */
		int dump(std::ostream&);

		/* Rename Function */
		int changeName(char*);

		/* Remove Function */
		int remove();

		/* Compare Function */
		int compare(FileManager);

		/* Expand Function */
		int expand();

		/* Convert the permissions from unsigned long to string */
		std::string permToStr(unsigned long perm);
	
	private:
		/* The name of the file, given to the class through its constructor */
		std::string name;
 
		/* Error variable for file operations indicating if the operation was successful or not */
		int errNum;
		
		/* Vector children containing a collection of file objects */
		std::vector<FileManager> childrenVec;
		
		//-----------------------------------------------------------------------
		mode_t type; 				  // Type of the File
		off_t size;					  // Size of the File
		uid_t owner;				  // Owner of the File
		gid_t group;                  // Group of the File
		mode_t perm;                  // Permissions of the File
		time_t accessTime;   		  // Last Time of Access of the File
		time_t modiTime;     		  // Last Time of Modification of the File
		time_t statChTime;   		  // Last Time of Status Change of the File 
		blksize_t blkSize; 			  // Block Size for the file
		//-----------------------------------------------------------------------
};
#endif


