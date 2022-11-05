#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<sys/wait.h>
#include<errno.h>



int main(int argc, char* argv[])
{	
	int num1;
	char arr[1024];
	char arr1[1024];
	int num;
	int file_dis[2];
	pid_t process_id;
	
	pipe(file_dis);
	
	FILE* file_obj = fopen("editSource.txt", "r");
	if (file_obj == NULL)
	{
		printf("Error in opening File!\n");
	}
	fseek(file_obj, 0L, SEEK_END);	//Changing file position
	num = ftell(file_obj);	//Storing the current file position
	fseek(file_obj, 0L, SEEK_SET);	//Changing file position
	
	if (arr == NULL)	//checking if array is empty
	{
		printf("File is Empty!\n");
	}
	
	fread(arr, sizeof(char), num, file_obj); //reading from file and storing into arr
	
	fclose(file_obj); // closing file object

	char* arg[] = { "./cp",arr,(char)0 }; //Copying all the data in arg[] , extension and data
	
	process_id = fork(); //Process creation using fork

	if (process_id < 0) //error checking
	{
		printf("Fork creation failed!\n");
	}
	else if (process_id == 0) // child
	{
		printf("Writing into file => consumerproducer.c ,through pipe!\n\n");
		execv(arg[0], arg); //Executing a file
		perror("Execution failed!\n"); //Execution error checking
		return 1;
	}
	else// parent
	{
		wait(NULL); // waiting for child completion
		FILE *new = fopen("count.txt","r");
		if(new == NULL)
		{
			printf("Error in file opening!\n");
		}
		else
		{
	
		fseek(new, 0L, SEEK_END);	//Changing file position
		num1 = ftell(new);	//Storing the current file position
		fseek(new, 0L, SEEK_SET);	//Changing file position
		
		if (arr1 == NULL)	//checking if array is empty
		{
			printf("File is Empty!\n");
		}
		fread(arr1, sizeof(char), num1, new); //reading from file and storing into arr
	
		fclose(file_obj); // closing file object
		
			printf("%s",arr1);
		
		}
		
	}
}
