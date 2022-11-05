#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<sys/wait.h>
#include<fcntl.h>

void main(int argc, char* argv[])


{
	int word = 0,character = 0,new_line = 0;
	char *arr;
	if(!(open(argv[0],O_RDONLY)))
	{
	printf("Error in reading from pipe!\n");
	exit(0);	
	}
	
	arr = argv[1];
	printf("Reading the data from file => editSource.txt !\n");
	
	for(int i = 0 ; arr[i] != '\0';i++)
	{
		if(arr[i] == '\n')
		{
			new_line++;
		}
		else if(arr[i] == ' ')
		{
			word++;
		}
		else if(arr[i] != ' ' && arr[i] != '\n')
		{
			character++;
			word++;
		}
	}
	
	word--;
	character--;
	char out[3] = {new_line,character,word};
	char *buf = out;
	FILE *file;
	file = fopen("count.txt","w");
	if (file == NULL)
	{
		printf("Error in file creation!\n");
		exit(-1);
	}
	else
	{
	printf("\n_____Writing into count.txt file_____\n");
	fprintf(file,"\nNumber of New-lines = %d\n",buf[0]);
	fprintf(file,"\nNumber of words = %d\n",buf[1]);
	fprintf(file,"\nNumber of characters = %d\n",buf[2]);
	}
}
