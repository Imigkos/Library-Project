
#include "main_functions.c"
int main()
{
	printf("\nIteration using dynamic arrays");
    int author_arr_size = get_arr_size("authors.txt");
    author *author_arr = malloc(sizeof(author) * author_arr_size);
    author_arr = get_authors();

    int book_arr_size = get_arr_size("book.txt");
    book *book_arr = malloc(sizeof(book) * book_arr_size);
    book_arr = get_books();

    int writes_arr_size = get_arr_size("writes.txt");
    writes *writes_arr = malloc(sizeof(writes) * writes_arr_size);
    writes_arr = get_writes();
    author_arr = update_num_of_books(author_arr_size, writes_arr_size, author_arr, writes_arr);

    int exit = 0;
    while (exit == 0)
    {
        int menu_choice;
        printf("\n1)Insert new writer record\n2)Insert new book record\n3)Search a writer record\n4)Search a book record\n5)Delete a writer record\n6)Delete a book record\n7)Exit\n");
        scanf("%d", &menu_choice);
        getchar();

        switch (menu_choice)
        {
        case 1:

            author_arr = insert_author(author_arr_size, author_arr);
            author_arr_size++;

            break;
        case 2:
            puts("");
            char surname_target[MAX];

            book_arr = insert_book(book_arr_size, book_arr);
            book_arr_size++;

            printf("\nGive the surname of the book's author: ");
            scanf("%s", surname_target);
            int target_author = search_author(author_arr, author_arr_size, surname_target);
            if (target_author == -1)
            {
                printf("\nAuthor was not found in the database\n");
                author_arr = insert_author(author_arr_size, author_arr);
                author_arr_size++;
                writes_arr = insert_writes(writes_arr_size, book_arr_size, author_arr_size, surname_target, writes_arr, book_arr, author_arr);
                writes_arr_size++;
            }
            else
            {

                writes_arr = insert_writes(writes_arr_size, book_arr_size, author_arr_size, surname_target, writes_arr, book_arr, author_arr);
                writes_arr_size++;
            }
            author_arr = update_num_of_books(author_arr_size, writes_arr_size, author_arr, writes_arr);

            break;
        case 3:
            target_author = 0;
            printf("\nEnter the author's surname: ");
            scanf("%s", surname_target);
            target_author = search_author(author_arr, author_arr_size, surname_target);
            if (target_author == -1)
            {
                printf("\nAuthor was not found in the database\n");
            }
            else
            {
                printf("\nThe author's full name is: %s %s", author_arr[target_author].name, author_arr[target_author].surname);
                search_writes_by_id(writes_arr, book_arr, writes_arr_size, book_arr_size, author_arr[target_author].writer_id);
            }
            break;
        case 4:
            puts("");
            char title_target[MAX];
            int target_book;
            printf("Enter the book's title: ");
            fgets(title_target, MAX, stdin);
            title_target[strcspn(title_target, "\n")] = 0;
            target_book = search_book(book_arr, book_arr_size, title_target);
            if (target_book == -1)
            {
                printf("\nBook was not found in the database ");
            }
            else
            {
                int target_writes = search_writes_by_title(writes_arr, writes_arr_size, title_target, 0);
                int current_book_author = search_author_id(author_arr, author_arr_size, target_writes);
                printf("\n-----------------");
                printf("\n%s", book_arr[target_book].title);
                printf("\n%d", book_arr[target_book].release_date);
                printf("\n%.2f", book_arr[target_book].price);
                printf("\n-----------------");
                printf("\nWritten By: ");
                printf("\n-----------------");
                printf("\n%s", author_arr[current_book_author].name);
                printf("\n%s", author_arr[current_book_author].surname);
                printf("\n-----------------\n");
            }
            break;
        case 5:
        	puts("");
            int id_delete = -1;
            print_arr(author_arr,author_arr_size);
            printf("\nEnter the id of the author you want to delete: ");
            scanf("%d", &id_delete);
            if (search_author_id(author_arr,author_arr_size,id_delete) != -1){
        
                int author_index = search_author_id(author_arr, author_arr_size, id_delete);
                book_arr = mass_book_delete(writes_arr,book_arr,writes_arr_size,book_arr_size,id_delete);
                book_arr_size = book_arr_size - author_arr[author_index].num_of_books;
                writes_arr = delete_writes_id(writes_arr_size,writes_arr,id_delete,author_arr[author_index].num_of_books);
                writes_arr_size = writes_arr_size - author_arr[author_index].num_of_books;
                author_arr = delete_author(author_arr_size, author_arr, author_index);
                author_arr_size--;
            }
            else
            {
                printf("\nThere is no author with that id \n");
            }
            break;
        case 6:
            puts("");
            char *book_title = malloc(512 * sizeof(char));
            print_b_arr (book_arr,book_arr_size);
            printf("\nEnter the title of the book you want to delete: ");
            fgets(book_title, MAX, stdin);
            book_title[strcspn(book_title, "\n")] = 0;
            int book_index = search_book(book_arr, book_arr_size, book_title);

            if (book_index != -1)
            {
                book_arr = delete_book(book_arr, book_arr_size, book_index);
                book_arr_size--;
                writes_arr = delete_writes_title(writes_arr_size, writes_arr, book_title);
                writes_arr_size--;
            }
            else
            {
                printf("\nBook was not found ");
            }
            author_arr = update_num_of_books(author_arr_size, writes_arr_size, author_arr, writes_arr);

            break;

        case 7:
            exit = 1;
            qsort(author_arr, author_arr_size, sizeof(author), author_id_compare);
            exit_library(author_arr, book_arr, writes_arr, author_arr_size, book_arr_size, writes_arr_size);
            free(author_arr);
            free(book_arr);
            free(writes_arr);
            break;
        default:
            printf("\nEnter a valid choice!! ");
        }
    }
    return 1;
}
