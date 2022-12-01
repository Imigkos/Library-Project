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
            scanf("%s",surname_target);
            author *target_author = search_author(a_list,surname_target);
            if (target_author == NULL){
                printf("\nAuthor was not found in the database");
                insert_author(a_list);
                insert_writes(w_list,a_list->head->writer_id,b_list->head->title);
            }
            else{
                insert_writes(w_list,target_author->writer_id,b_list->head->title);
            }
            update_num_of_books(a_list,w_list);
            
            break;
        case 3:
            printf("\nEnter the author's surname: ");
            scanf("%s", surname_target);
            target_author = search_author(a_list,surname_target);
            if (target_author == NULL){
                printf("\nAuthor was not found in the database\n");
            }
            else
            {
                printf("\nThe author's full name is: %s %s", target_author->name,target_author->surname);
                search_writes_by_id(w_list,b_list,target_author->writer_id);
            }
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        default:
        }
    }
}