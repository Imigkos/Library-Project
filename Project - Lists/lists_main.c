#include "lists_functions.c"

void main()
{
    author_list *a_list;
    a_list = get_authors();

    book_list *b_list;
    b_list = get_books();

    writes_list *w_list;
    w_list = get_writes();

    // print_a_list(a_list);
    // sort_authors(a_list);
    // print_a_list(a_list);

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
            insert_author(a_list);
            break;
        case 2:
            puts("");
            char surname_target[MAX];
            insert_book(b_list);

            printf("\nGive the surname of the book's author: ");
            scanf("%s", surname_target);
            author *target_author = search_author(a_list, surname_target);
            if (target_author == NULL)
            {
                printf("\nAuthor was not found in the database");
                insert_author(a_list);
                insert_writes(w_list, a_list->head->writer_id, b_list->head->title);
            }
            else
            {
                insert_writes(w_list, target_author->writer_id, b_list->head->title);
            }
            update_num_of_books(a_list, w_list);
            break;
        case 3:
            printf("\nEnter the author's surname: ");
            scanf("%s", surname_target);
            target_author = search_author(a_list, surname_target);
            if (target_author == NULL)
            {
                printf("\nAuthor was not found in the database\n");
            }
            else
            {
                printf("\nThe author's full name is: ");
                print_a_node(target_author);
                search_writes_by_id(w_list, b_list, target_author->writer_id);
            }
            break;
        case 4:
            puts("");

            char title_target[MAX];
            book *target_book;
            writes *target_writes;

            printf("Enter the book's title: ");
            fgets(title_target, MAX, stdin);
            title_target[strcspn(title_target, "\n")] = 0;
            target_book = search_book(b_list, title_target);
            if (target_book == NULL)
            {
                printf("\nBook was not found in the database ");
            }
            else
            {
                target_writes = search_writes_by_title(w_list, target_book->title);
                target_author = search_author_id(a_list, target_writes->writer_id);
                print_b_node(target_book);
                printf("\nWritten By: ");
                print_a_node(target_author);
                printf("\n");
            }

            break;
        case 5:
            puts("");

            int i;
            int id_delete = -1;
            print_a_list(a_list);
            printf("Enter the id of the author you want to delete: ");
            scanf("%d", &id_delete);
            if (search_author_id(a_list, id_delete) != NULL)
            {
                target_author = search_author_id(a_list,id_delete);
                mass_book_delete(w_list,b_list,id_delete);
                print_b_list(b_list);
                for ( i = 0; i <= target_author->num_of_books; i++)
                {
                    
                    delete_writes_id(w_list,id_delete);

                }
                print_w_list(w_list);
                delete_author(a_list,id_delete);
                print_a_list(a_list);

            }
            else
            {
                printf("\nThere is no author with that id\n");
            }
            break;
        case 6:
            puts("");
            char *book_title = malloc(512 * sizeof(char));
            printf("\nEnter the title of the book you want to delete: ");
            fgets(book_title, MAX, stdin);
            book_title[strcspn(book_title, "\n")] = 0;
            int book_exists = delete_book(b_list, book_title);

            if (book_exists == 1)
            {
                print_b_list(b_list);
                delete_writes_title(w_list,book_title);
                update_num_of_books(a_list, w_list);
                print_w_list(w_list);
            }
            else
            {
                printf("\nBook was not found ");
            }

            break;
        case 7:
            exit = 1;
            exit_library(a_list,b_list,w_list);
            break;
        default:
        }
    }
}