#include "init.h"
#define MAX 35

author * get_authors(){

    FILE *author_file;

    if((author_file= fopen("authors.txt", "r"))==NULL)
    {
        printf("File does not exist or cannot be opened.\n");
        exit(1);
    }
    int entries = 0;
    char buffer[35];

    fgets (entries, MAX ,author_file);    
    author * author_arr = malloc(sizeof(author) * entries); 
    while (fgets(buffer,MAX,author_file)){
        author writer;
        writer.writer_id = atoi(buffer);
        //char* buffer = malloc(100*sizeof(char));

        writer.surname = malloc(sizeof(char)*MAX);
        fgets(writer.surname,MAX,author_file);
        
        writer.name = malloc (sizeof(char)*MAX);
        fgets(writer.name,MAX,author_file);

        fgets.
        writer.num_of_books

    }
}


