
#include "main_functions.c"
void main()
{

    int author_arr_size = get_arr_size("authors.txt");
    author * author_arr = malloc(sizeof(author) * author_arr_size); 
    author_arr = get_authors();
    printf("%s",author_arr[1].name);

    int book_arr_size = get_arr_size("book.txt");
    book * book_arr = malloc(sizeof(book)*book_arr_size);
    book_arr = get_books();
    printf("%s",book_arr[1].title);

    int writes_arr_size = get_arr_size("writes.txt");
    writes * writes_arr = malloc(sizeof(writes)*writes_arr_size);
    writes_arr = get_writes();
    printf("%s",writes_arr[1].title);
    

    int exit = 0;
    while (exit == 0)
    {
        int menu_choice;
        printf("\n1)Insert new writer record\n2)Insert new book record\n3)Search a writer record\n4)Search a book record\n5)Delete a writer record\n6)Delete a book record\n7)Exit\n");
        scanf("%d", &menu_choice);
        printf("%d", menu_choice);

        switch (menu_choice)
        {
        case 1:
            author new_writer;

            char *buffer = malloc(512*sizeof(char));
            printf("\nEnter the author's name: ");
            scanf("%s",buffer);
            new_writer.name = malloc(strlen(buffer)*sizeof(char));
            strcpy(new_writer.name,buffer);
            free(buffer);
            buffer = NULL;

            buffer = malloc(512*sizeof(char));
            printf("\nEnter the author's surname: ");
            scanf("%s",buffer);
            new_writer.surname = malloc(strlen(buffer)*sizeof(char));
            strcpy(new_writer.surname,buffer);
            free(buffer);
            buffer = NULL;

            new_writer.writer_id = (author_arr_size+1);
            new_writer.num_of_books = 0;
            author_arr = insert_author(new_writer,author_arr_size);
            printf("\n%s\n%s\n%d\n%d",author_arr[author_arr_size].name,author_arr[author_arr_size].surname,author_arr[author_arr_size].writer_id,author_arr[author_arr_size].num_of_books);
            author_arr_size++;
            free(new_writer.name);
            free(new_writer.surname);
        
            break;
        case 2:
            printf("add book");
            break;
        case 3:
            printf("search writer");
            break;
        case 4:
            printf("search book");
            break;
        case 5:
            printf("delete writer");
            break;
        case 6:
            printf("delete book");
            break;
        case 7:
            exit = 1;
            exit_library(author_arr,book_arr,writes_arr,author_arr_size,book_arr_size,writes_arr_size);
            break;
        default:
            printf("bale 1-7 paliomalaka");
        }
    }
}