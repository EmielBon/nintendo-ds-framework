#include "FileStream.h"

#include <stdlib.h>
#include <string.h>
#include <dirent.h>

namespace FileSystem
{
	using namespace std;

	//-------------------------------------------------------------------------------------------------
	void FileStream::Open(const string &path)
	{
		stream = fopen(path.c_str(), "rb");

		if (stream != NULL) 
			open = true;
		else 
			printf("could not open file: %s\n", path.c_str() );
	}

	//-------------------------------------------------------------------------------------------------
	void FileStream::Close()
	{
		open = false;
		fclose(stream);
	}

	//-------------------------------------------------------------------------------------------------
	int FileStream::Read(void* buffer, u32 bytesPerElement, u32 nrOfElements)
	{
		if (open) return fread(buffer, bytesPerElement, nrOfElements, stream);
		
		printf("could not read from file\n");
		return 0;
	}

	//-------------------------------------------------------------------------------------------------
	void FileStream::ListDirectories(const char* root)
	{
		DIR* pdir = opendir(root);
		char *dnbuf;

		if (pdir != NULL) 
		{
			while(true) 
			{
				struct dirent* pent = readdir(pdir);
				if(pent == NULL) break;
			
				if(strcmp(".", pent->d_name) != 0 && strcmp("..", pent->d_name) != 0) 
				{
					dnbuf = (char *)malloc(strlen(pent->d_name)+strlen(root)+2);
					sprintf(dnbuf, "%s/%s", (strcmp("/",root) == 0)?"":root, pent->d_name);
				
					struct stat *statbuf = (struct stat*)malloc(sizeof(statbuf));
					stat(dnbuf, statbuf);

					if(S_ISDIR(statbuf->st_mode)) 
					{
						printf("%s <DIR>\n", dnbuf);
						ListDirectories(dnbuf);
					} 
					else 
					{
						printf("%s (%d)\n", dnbuf, (int)statbuf->st_size);
					}
					free(dnbuf);
					free(statbuf);
				}
			}
		
			closedir(pdir);
		} 
		else 
		{
			printf("opendir() failure.\n");
		}
	}
}