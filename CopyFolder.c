/**********************************************************************
* CopyFolder
* version: 1.0
* September, 6th, 2015
*
* This lib was written by thangdn
* Contact:thangdn.tlu@outlook.com
*
* Every comment would be appreciated.
*
* If you want to use parts of any code of mine:
* let me know and
* use it!
**********************************************************************/
/*
	Guide: ./Copy ~/Desktop ~/Desktop/file
*/
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAX 1000


void nums(char *directory,int i,char *directoryto);
int main(int argc, char const *argv[])
{

		char path[400];
		char path_to_save[400];
		char cach[10];
		int i=0;
		sprintf(path,"%s",argv[1]);
		sprintf(path_to_save,"%s",argv[2]);
		nums(path,i,path_to_save);
		return 0;
}

void copy(char *file,char *filecopy)
{
	int file1 = open(file,O_RDONLY);
	if (file1<0)	
	{
		write(1,"ERRO FILE1",10);
		return;
	}
	int file2 = open(filecopy,O_RDWR|O_CREAT,0666);
	if(file2==-1){puts("ERRO OPEN FOLDER");return;}
	char buffer[MAX]; int numberofbytes;
	do
	{
		numberofbytes=read(file1,buffer,MAX);
		write(file2,buffer,numberofbytes);
	}while(numberofbytes>0);
	close(file2);
}

void nums(char *directory,int i,char *directoryto)
{
	int status;
	struct stat st_buf;
	DIR *d;
	char path[400];
	char path_to_save[400];
	d=opendir (directory);
	if (d==0)
	{
		printf("Could not to read directory!");
		return;
	}
	struct dirent *entry =readdir(d);
	while(entry!=0)
	{
		if(entry->d_name[0]!='.'){
			sprintf(path,"%s/%s",directory,entry->d_name);
			sprintf(path_to_save,"%s/%s",directoryto,entry->d_name);
			status = stat (path, &st_buf);
			int j=0;
	    	for(;j<i*2;j++)
	    		printf("__");
			if (entry->d_type==DT_DIR)
	        {
	        	
	        	puts(entry->d_name);
	        	i++;
	        	{
	        		mkdir(path_to_save, 0777);
	        	}
	        	nums(path,i,path_to_save);
	        	i--;
	        }else{
	        	puts(entry->d_name);
	        	copy(path,path_to_save);
	        }
    	}
        entry =readdir(d);
    }
	closedir(d);
}
