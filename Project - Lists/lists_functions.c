#include "init.h"

author_list* get_authors(){

    author_list *a_list = malloc(sizeof(author_list));
    FILE *author_file;

    int entries = 0;
    int i = 0;
    char buffer[MAX];

    
    if ((author_file = fopen("authors.txt", "r")) == NULL)
    {
        printf("File does not exist or cannot be opened.\n");
        exit(1);
    }
    fgets(buffer, MAX, author_file);
    a_list->entries = atoi(buffer);
    while (fgets(buffer, MAX, author_file))
    {
       author *new_author;
       new_author = malloc(sizeof(author));
       new_author->writer_id = atoi(buffer);

       new_author->surname = malloc(sizeof(char)*MAX);
       fgets(new_author->surname,MAX,author_file);
       new_author->surname[strcspn(new_author->surname,"\n")] = 0;

       new_author->name = malloc(sizeof(char)*MAX);
       fgets(new_author->name,MAX,author_file);
       new_author->name[strcspn(new_author->name,"\n")] = 0;

       fgets(buffer,MAX,author_file);
       new_author->num_of_books = atoi(buffer);

       new_author->next = a_list->head;
       a_list->head = new_author;

    }
    
    return(a_list);
    
}

void print_a_list(const author_list *list){
    author *cur;
    cur = list->head;
     while (cur)
    {
        printf("------------\n");
        printf("%s\n", cur->surname);
        printf("%s\n", cur->name);
        printf("%d\n", cur->writer_id);
        printf("%d\n", cur->num_of_books);
        printf("------------\n");
        cur = cur->next;
    }
}
