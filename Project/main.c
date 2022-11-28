
#include "main_functions.c"
void main()
{

    int author_arr_size = get_arr_size("authors.txt");
    author * author_arr = malloc(sizeof(author) * author_arr_size); 
    author_arr = get_authors();
   

    int book_arr_size = get_arr_size("book.txt");
    book * book_arr = malloc(sizeof(book)*book_arr_size);
    book_arr = get_books();
    

    int writes_arr_size = get_arr_size("writes.txt");
    writes * writes_arr = malloc(sizeof(writes)*writes_arr_size);
    writes_arr = get_writes();
    
    

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
            
            author_arr = insert_author(author_arr_size,author_arr);
            author_arr_size++;
        
            break;
        case 2:
            char surname_target[MAX];

            book_arr = insert_book(book_arr_size,book_arr);
            book_arr_size++; 

            printf("\nGive the surname of the book's author: ");
            scanf("%s",&surname_target);
            int target_author = search_author(author_arr,author_arr_size,surname_target);
            if (target_author == -1){
                printf("\nAuthor was not found in the database: \n");
                author_arr = insert_author(author_arr_size,author_arr);
                author_arr_size++;
                writes_arr = insert_writes(writes_arr_size,book_arr_size,author_arr_size,surname_target,writes_arr,book_arr,author_arr);
                writes_arr_size ++;
            }
            else{
                
                writes_arr = insert_writes(writes_arr_size,book_arr_size,author_arr_size,surname_target,writes_arr,book_arr,author_arr);
                writes_arr_size ++;

            }

            break;
        case 3:
            target_author = 0;
            printf("\nEnter the author's surname: ");
            scanf("%s", &surname_target);
            target_author=search_author(author_arr,author_arr_size,surname_target);
            if (target_author == -1){
                printf("\nAuthor was not found in the database\n");
            }
            else{
                printf("\nThe author's full name is: %s %s",author_arr[target_author].name,author_arr[target_author].surname);
                search_writes_by_id(writes_arr,book_arr,writes_arr_size,book_arr_size,author_arr[target_author].writer_id);
            }
            break;
        case 4:
            char title_target[MAX];
            int target_book;
            printf("Enter the book's title: ");
            fgets(title_target,MAX,stdin);
            title_target[strcspn(title_target, "\n")] = 0;
            target_book = search_book(book_arr,book_arr_size,title_target);
            if (target_book == -1){
                printf("\nBook was not found in the database");
            }
            else{
                int target_writes = search_writes_by_title(writes_arr,writes_arr_size,title_target);
                int current_book_author = search_author_id(author_arr,author_arr_size,target_writes);
                printf("\n-----------------");
                printf("\n%s",book_arr[target_book].title);
                printf("\n%d",book_arr[target_book].release_date);
                printf("\n%.2f€",book_arr[target_book].price);
                printf("\n-----------------");
                printf("\nWritten By: ");
                printf("\n-----------------");
                printf("\n%s",author_arr[current_book_author].name);
                printf("\n%s",author_arr[current_book_author].surname);
                printf("\n-----------------\n");
            }
            break;
        case 5:
            printf("delete writer");
            break;
        case 6:
            printf("delete book");
            break;
        case 7:
              for (int i = 0; i < author_arr_size; i++)
    {
           printf("\n%s\n%s\n%d\n%d\n",author_arr[i].name,author_arr[i].surname,author_arr[i].writer_id,author_arr[i].num_of_books);
    }
            exit = 1;
            qsort(author_arr,author_arr_size,sizeof(author),author_id_compare);
            exit_library(author_arr,book_arr,writes_arr,author_arr_size,book_arr_size,writes_arr_size);
            free(author_arr);
            free(book_arr);
            free(writes_arr);
            break;
        default:
            printf("bale 1-7 ");
        }
    }
}