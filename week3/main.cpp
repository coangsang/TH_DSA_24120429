#include <stdio.h>
#include <string.h>
#include "sort_algor.h"
int main(int argc, char const *argv[])
{
	char* type_sort = new char[50];
	char* input_path = new char[100];
	char* output_path = new char[100];

	for(int i = 1;i<argc;i+=2){
		if(!strcmp(argv[i],"-a")){
			strcpy(type_sort,argv[i+1]); 
		}
		else if(!strcmp(argv[i],"-i")){
			strcpy(input_path,argv[i+1]);
		}
		else if(!strcmp(argv[i],"-o")){
			strcpy(output_path,argv[i+1]);
		}
	}
	FILE* input_file = fopen(input_path,"r");
	FILE* output_file = fopen(output_path,"w");
	int n;
	fscanf(input_file,"%d",&n);
	int *nums = new int[n];
	for(int i =0;i<n;i++){
		fscanf(input_file,"%d",&nums[i]);
	}
	delete[]input_path;
	delete[]type_sort;
	delete[]output_path;
	fclose(input_file);
	fclose(output_file);
	return 0;
}