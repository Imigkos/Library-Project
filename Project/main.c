
#include "main_functions.c"
void main()
{
    int author_arr_size = get_lines();
    author * author_arr = malloc(sizeof(author) * ((author_arr_size-1)/4)); 
    author_arr = get_authors();
    printf("%s",author_arr[1].name);

    int book_arr_size = get_lines();
    book * book_arr = malloc(sizeof(book)*((book_arr_size-1)/4));
    book_arr = get_books();
    printf("%s",book_arr[1].title);

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
            printf("add writer");
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
            break;
        default:
            printf("bale 1-7 paliomalaka");
        }
    }
}