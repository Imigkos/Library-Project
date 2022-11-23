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


int get_arr_size(char *filename){
    FILE *file;
    if ((file = fopen(filename, "r")) == NULL)
    {
        /* If the file does not exist throw error and exit */
        fprintf(stderr, "file does not exist\n");
        exit(1);
    }
    char str[35];
    int array_size;
    fgets(str,MAX,file);
    array_size = atoi(str);
    return(array_size);
}

author * insert_author(author writer,int arr_size)
{
    author *author_arr = malloc(arr_size*sizeof(author)+sizeof(author));
    author_arr = get_authors();
    author_arr[arr_size] = writer;
    return(author_arr);
}

void exit_library(author *author_arr,book *book_arr,writes *writes_arr,int author_arr_size,int book_arr_size,int writes_arr_size){

    FILE *author_file,*writes_file,*book_file;
    int i;

    if ((author_file= fopen("authors.txt", "w")) == NULL)
    {
        fprintf(stderr, "Error in authors.txt");
        exit(1);
    }

for (i = 0; i < author_arr_size; i++)
    {
        if (i==0)
        {
           fprintf(author_file,"%d",author_arr_size);
        }
        
        fprintf(author_file, "%d", author_arr[i].writer_id);
        fprintf(author_file, "%s", author_arr[i].surname);
        fprintf(author_file, "%s", author_arr[i].name);
        fprintf(author_file, "%d", author_arr[i].num_of_books);
    }

if ((book_file= fopen("book.txt", "w")) == NULL)
    {
        fprintf(stderr, "Error in book.txt");
        exit(1);
    }

for (i = 0; i < book_arr_size; i++)
    {
        if (i==0)
        {
           fprintf(book_file,"%d",book_arr_size);
        }
        
        fprintf(book_file, "%d", book_arr[i].release_date);
        fprintf(book_file, "%s", book_arr[i].title);
        fprintf(book_file, "%f", book_arr[i].price);
        
    }

if ((writes_file= fopen("writes.txt", "w")) == NULL)
    {
        fprintf(stderr, "Error in writes.txt");
        exit(1);
    }

for (i = 0; i < writes_arr_size; i++)
    {
        if (i==0)
        {
           fprintf(writes_file,"%d",writes_arr_size);
        }
        
        fprintf(writes_file, "%d", writes_arr[i].writer_id);
        fprintf(writes_file, "%s", writes_arr[i].title);
           
    }

    fflush(author_file);
    fclose(author_file);

    fflush(book_file);
    fclose(book_file);

    fflush(writes_file);
    fclose(writes_file);

}