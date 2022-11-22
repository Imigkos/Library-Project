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
    int i = 0;
    char buffer[35];

    fgets (buffer, MAX ,author_file); 
    entries = atoi(buffer);
    author * author_arr = malloc(sizeof(author) * entries); 
    while (fgets(buffer,MAX,author_file)){
        author writer;
        writer.writer_id = atoi(buffer);
        //char* buffer = malloc(100*sizeof(char));

        writer.surname = malloc(sizeof(char)*MAX);
        fgets(writer.surname,MAX,author_file);
        
        writer.name = malloc (sizeof(char)*MAX);
        fgets(writer.name,MAX,author_file);

        fgets(buffer,MAX,author_file);
        writer.num_of_books = atoi(buffer);

        author_arr[i] = writer;
        i++;

    }
    return author_arr;
}

book * get_books(){

    FILE *book_file;

    if((book_file= fopen("book.txt", "r"))==NULL)
    {
        printf("File does not exist or cannot be opened.\n");
        exit(1);
    }
    int entries = 0;
    int i = 0;
    char buffer[35];

    fgets (buffer, MAX ,book_file); 
    entries = atoi(buffer);
    book * book_arr = malloc(sizeof(book) * entries); 
    while (fgets(buffer,MAX,book_file)){
        book book;
        book.release_date = atoi(buffer);
        //char* buffer = malloc(100*sizeof(char));

        book.title= malloc(sizeof(char)*MAX);
        fgets(book.title,MAX,book_file);
        

        fgets(buffer,MAX,book_file);
        book.price = atof(buffer);

        book_arr[i] = book;
        i++;

    }
    return book_arr;
}

writes * get_writes(){

    FILE *writes_file;

    if((writes_file= fopen("writes.txt", "r"))==NULL)
    {
        printf("File does not exist or cannot be opened.\n");
        exit(1);
    }
    int entries = 0;
    int i = 0;
    char buffer[35];

    fgets (buffer, MAX ,writes_file); 
    entries = atoi(buffer);
    writes * writes_arr = malloc(sizeof(writes) * entries); 
    while (fgets(buffer,MAX,writes_file)){
        writes writes;
        writes.writer_id = atoi(buffer);
        //char* buffer = malloc(100*sizeof(char));

        writes.title= malloc(sizeof(char)*MAX);
        fgets(writes.title,MAX,writes_file);

        writes_arr[i] = writes;
        i++;

    }
    return writes_arr;
}


int get_lines(char *filename)
{
    char *line_buffer = NULL;
    size_t line_buffer_length = 0;
    int line_count = 0;
    ssize_t line_len;

    FILE *file;

    if ((file = fopen(filename, "r")) == NULL)
    {
        /* If the file does not exist throw error and exit */
        fprintf(stderr, "file does not exist\n");
        exit(1);
    }
    /* Get the line count of the file */
    line_len = getline(&line_buffer, &line_buffer_length, file);
    while (line_len >= 0)
    {
        line_count++;
        line_len = getline(&line_buffer, &line_buffer_length, file);
    }
    free(line_buffer);
    line_buffer = NULL;
    fflush(file);
    fclose(file);
    return line_count; 
}


