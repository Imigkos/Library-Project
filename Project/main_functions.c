#include "init.h"
#define MAX 35

author *get_authors()
{

    FILE *author_file;

    if ((author_file = fopen("authors.txt", "r")) == NULL)
    {
        printf("File does not exist or cannot be opened.\n");
        exit(1);
    }
    int entries = 0;
    int i = 0;
    char buffer[35];

    fgets(buffer, MAX, author_file);
    entries = atoi(buffer);
    author *author_arr = malloc(sizeof(author) * entries);
    while (fgets(buffer, MAX, author_file))
    {
        author writer;
        writer.writer_id = atoi(buffer);
        // char* buffer = malloc(100*sizeof(char));

        writer.surname = malloc(sizeof(char) * MAX);
        fgets(writer.surname, MAX, author_file);
        writer.surname[strcspn(writer.surname, "\n")] = 0;

        writer.name = malloc(sizeof(char) * MAX);
        fgets(writer.name, MAX, author_file);
        writer.name[strcspn(writer.name, "\n")] = 0;

        fgets(buffer, MAX, author_file);
        writer.num_of_books = atoi(buffer);

        author_arr[i] = writer;
        i++;
    }
    return author_arr;
}

book *get_books()
{

    FILE *book_file;

    if ((book_file = fopen("book.txt", "r")) == NULL)
    {
        printf("File does not exist or cannot be opened.\n");
        exit(1);
    }
    int entries = 0;
    int i = 0;
    char buffer[35];

    fgets(buffer, MAX, book_file);
    entries = atoi(buffer);
    book *book_arr = malloc(sizeof(book) * entries);
    while (fgets(buffer, MAX, book_file))
    {
        book book;
        book.release_date = atoi(buffer);
        // char* buffer = malloc(100*sizeof(char));

        book.title = malloc(sizeof(char) * MAX);
        fgets(book.title, MAX, book_file);
        book.title[strcspn(book.title, "\n")] = 0;

        fgets(buffer, MAX, book_file);
        book.price = atof(buffer);

        book_arr[i] = book;
        i++;
    }
    return book_arr;
}

writes *get_writes()
{

    FILE *writes_file;

    if ((writes_file = fopen("writes.txt", "r")) == NULL)
    {
        printf("File does not exist or cannot be opened.\n");
        exit(1);
    }
    int entries = 0;
    int i = 0;
    char buffer[35];

    fgets(buffer, MAX, writes_file);
    entries = atoi(buffer);
    writes *writes_arr = malloc(sizeof(writes) * entries);
    while (fgets(buffer, MAX, writes_file))
    {
        writes writes;
        writes.writer_id = atoi(buffer);
        // char* buffer = malloc(100*sizeof(char));

        writes.title = malloc(sizeof(char) * MAX);
        fgets(writes.title, MAX, writes_file);
        writes.title[strcspn(writes.title, "\n")] = 0;

        writes_arr[i] = writes;
        i++;
    }
    return writes_arr;
}

int get_arr_size(char *filename)
{
    FILE *file;
    if ((file = fopen(filename, "r")) == NULL)
    {
        /* If the file does not exist throw error and exit */
        fprintf(stderr, "file does not exist\n");
        exit(1);
    }
    char str[35];
    int array_size;
    fgets(str, MAX, file);
    array_size = atoi(str);
    return (array_size);
}

author *insert_author(int arr_size, author *author_arr)
{
    author new_writer;

    char *buffer = malloc(512 * sizeof(char));
    printf("\nEnter the author's name: ");
    scanf("%s", buffer);
    new_writer.name = malloc(strlen(buffer) * sizeof(char));
    strcpy(new_writer.name, buffer);
    free(buffer);
    buffer = NULL;

    buffer = malloc(512 * sizeof(char));
    printf("\nEnter the author's surname: ");
    scanf("%s", buffer);
    new_writer.surname = malloc(strlen(buffer) * sizeof(char));
    strcpy(new_writer.surname, buffer);
    free(buffer);
    buffer = NULL;

    new_writer.writer_id = (arr_size + 1);
    new_writer.num_of_books = 0;
    author_arr = realloc(author_arr, sizeof(author_arr) * sizeof(author) + sizeof(author_arr) * sizeof(author));
    author_arr[arr_size] = new_writer;
    return (author_arr);
}

void exit_library(author *author_arr, book *book_arr, writes *writes_arr, int author_arr_size, int book_arr_size, int writes_arr_size)
{

    FILE *author_file, *writes_file, *book_file;
    int i;

    if ((author_file = fopen("authors.txt", "w")) == NULL)
    {
        fprintf(stderr, "Error in authors.txt");
        exit(1);
    }

    for (i = 0; i < author_arr_size; i++)
    {
        if (i == 0)
        {
            fprintf(author_file, "%d\n", author_arr_size);
        }

        fprintf(author_file, "%d\n", author_arr[i].writer_id);
        fprintf(author_file, "%s\n", author_arr[i].surname);
        fprintf(author_file, "%s\n", author_arr[i].name);
        fprintf(author_file, "%d\n", author_arr[i].num_of_books);
    }

    if ((book_file = fopen("book.txt", "w")) == NULL)
    {
        fprintf(stderr, "Error in book.txt");
        exit(1);
    }

    for (i = 0; i < book_arr_size; i++)
    {
        if (i == 0)
        {
            fprintf(book_file, "%d\n", book_arr_size);
        }

        fprintf(book_file, "%d\n", book_arr[i].release_date);
        fprintf(book_file, "%s\n", book_arr[i].title);
        fprintf(book_file, "%.2f\n", book_arr[i].price);
    }

    if ((writes_file = fopen("writes.txt", "w")) == NULL)
    {
        fprintf(stderr, "Error in writes.txt");
        exit(1);
    }

    for (i = 0; i < writes_arr_size; i++)
    {
        if (i == 0)
        {
            fprintf(writes_file, "%d\n", writes_arr_size);
        }

        fprintf(writes_file, "%d\n", writes_arr[i].writer_id);
        fprintf(writes_file, "%s\n", writes_arr[i].title);
    }

    fflush(author_file);
    fclose(author_file);

    fflush(book_file);
    fclose(book_file);

    fflush(writes_file);
    fclose(writes_file);
}

int author_surname_compare(author *writer1, author *writer2)
{
    int surname_compare = strcasecmp(writer1->surname, writer2->surname);
    return surname_compare;
}

int author_id_compare(author *writer1, author *writer2)
{
    if (writer1->writer_id > writer2->writer_id)
    {
        return 1;
    }
    else if (writer1->writer_id < writer2->writer_id)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int book_title_compare(book *book1, book *book2)
{
    int title_compare = strcasecmp(book1->title, book2->title);
    return title_compare;
}

int writes_title_compare(writes *writes1, writes *writes2)
{
    int title_compare = strcasecmp(writes1->title, writes2->title);
    return title_compare;
}
int writes_id_compare(writes *writes1, writes *writes2)
{
    if (writes1->writer_id > writes2->writer_id)
    {
        return 1;
    }
    else if (writes1->writer_id < writes2->writer_id)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int search_author(author *author_arr, int array_size, char *surname)
{
    int bottom = 0;
    int mid;
    int top = array_size - 1;

    qsort(author_arr, array_size, sizeof(author), author_surname_compare);

    while (bottom <= top)
    {
        mid = (bottom + top) / 2;
        if (strcasecmp(author_arr[mid].surname, surname) == 0)
        {

            return (mid);
        }
        else if (strcasecmp(author_arr[mid].surname, surname) > 0)
        {
            top = mid - 1;
        }
        else if (strcasecmp(author_arr[mid].surname, surname) < 0)
        {
            bottom = mid + 1;
        }
    }

    return -1;
}

int search_book(book *book_arr, int array_size, char *title)
{
    int bottom = 0;
    int mid;
    int top = array_size - 1;
    char *buffer;

    qsort(book_arr, array_size, sizeof(book), book_title_compare);

    while (bottom <= top)
    {
        mid = (bottom + top) / 2;
        if (strcasecmp(book_arr[mid].title, title) == 0)
        {
            return (mid);
        }
        else if (strcasecmp(book_arr[mid].title, title) > 0)
        {
            top = mid - 1;
        }
        else if (strcasecmp(book_arr[mid].title, title) < 0)
        {
            bottom = mid + 1;
        }
    }
    return -1;
}

int search_writes_by_title(writes *writes_arr, int array_size, char *title, int index)
{
    int bottom = 0;
    int mid;
    int top = array_size - 1;
    char *buffer;

    qsort(writes_arr, array_size, sizeof(writes), writes_title_compare);

    while (bottom <= top)
    {
        mid = (bottom + top) / 2;
        if (strcasecmp(writes_arr[mid].title, title) == 0)
        {
            if (index == 0)
            {
                return (writes_arr[mid].writer_id);
            }
            else
            {
                return mid;
            }
        }
        else if (strcasecmp(writes_arr[mid].title, title) > 0)
        {
            top = mid - 1;
        }
        else if (strcasecmp(writes_arr[mid].title, title) < 0)
        {
            bottom = mid + 1;
        }
    }
    return -1;
}

int search_author_id(author *author_arr, int array_size, int id)
{
    int bottom = 0;
    int mid;
    int top = array_size - 1;
    char *buffer;

    qsort(author_arr, array_size, sizeof(author), author_id_compare);

    while (bottom <= top)
    {
        mid = (bottom + top) / 2;
        if (author_arr[mid].writer_id == id)
        {
            return (mid);
        }
        else if (author_arr[mid].writer_id > id)
        {
            top = mid - 1;
        }
        else if (author_arr[mid].writer_id < id)
        {
            bottom = mid + 1;
        }
    }

    return -1;
}

void search_writes_by_id(writes *writes_arr, book *book_arr, int writes_array_size, int book_arr_size, int id)
{
    int has_books = 0;
    qsort(writes_arr, writes_array_size, sizeof(writes), writes_id_compare);
    for (int i = 0; i < writes_array_size; i++)
    {
        if (writes_arr[i].writer_id == id)
        {
            int found_book = search_book(book_arr, book_arr_size, writes_arr[i].title);
            printf("\n-----------------");
            printf("\n%s", book_arr[found_book].title);
            printf("\n%d", book_arr[found_book].release_date);
            printf("\n%.2f€", book_arr[found_book].price);
            printf("\n-----------------");
            has_books = 1;
        }
    }
    if (has_books == 0)
    {
        printf("\nThere are no book entries regarding this author\n ");
    }
}

book *insert_book(int arr_size, book *book_arr)
{
    book new_book;

    char *buffer = malloc(512 * sizeof(char));
    printf("\nEnter the book's title: ");
    fgets(buffer, MAX, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    new_book.title = malloc(strlen(buffer) * sizeof(char));
    strcpy(new_book.title, buffer);
    free(buffer);
    buffer = NULL;

    printf("\nEnter the book's release date: ");
    scanf("%d", &new_book.release_date);

    printf("\nEnter the book's price: ");
    scanf("%f", &new_book.price);
    book_arr = realloc(book_arr, sizeof(book_arr) * sizeof(book) + sizeof(book_arr) * sizeof(book));
    book_arr[arr_size] = new_book;
    return (book_arr);
}

writes *insert_writes(int writes_arr_size, int book_arr_size, int author_arr_size, char *surname, writes *writes_arr, book *book_arr, author *author_arr)
{

    writes new_writes;

    new_writes.title = malloc(strlen(book_arr[book_arr_size - 1].title) * sizeof(char));
    strcpy(new_writes.title, book_arr[book_arr_size - 1].title);

    int index = search_author(author_arr, author_arr_size, surname);
    new_writes.writer_id = author_arr[index].writer_id;
    writes_arr = realloc(writes_arr, sizeof(writes_arr) * sizeof(writes) + sizeof(writes_arr) * sizeof(writes));
    writes_arr[writes_arr_size] = new_writes;
    return (writes_arr);
}

book *delete_book(book *book_arr, int book_arr_size, int book_index)
{

    if (book_index != -1)
    {
        book *new_book_arr;
        new_book_arr = malloc((book_arr_size - 1) * sizeof(book));
        int current_pos = 0;
        for (int i = 0; i < book_arr_size; i++)
        {
            if (i != book_index)
            {
                new_book_arr[current_pos] = book_arr[i];
                current_pos++;
            }
        }
        return (new_book_arr);
    }
    else
    {
        printf("\nBook was not found: ");
        return (book_arr);
    }
}

writes *delete_writes_title(int writes_arr_size, writes *writes_arr, char *title)
{

    int writes_index = search_writes_by_title(writes_arr, writes_arr_size, title, 1);

    if (writes_index != -1)
    {
        writes *new_writes_arr;
        new_writes_arr = malloc((writes_arr_size - 1) * sizeof(writes));
        int current_pos = 0;
        for (int i = 0; i < writes_arr_size; i++)
        {
            if (i != writes_index)
            {
                new_writes_arr[current_pos] = writes_arr[i];
                current_pos++;
            }
        }
        return (new_writes_arr);
    }
    else
    {
        printf("\nSomething has gone very wrong x<");
        return (writes_arr);
    }
}

author *update_num_of_books(int author_arr_size, int writes_arr_size, author *author_arr, writes *writes_arr)
{
    int books_written;
    for (int i = 0; i < author_arr_size; i++)
    {
        books_written = 0;
        for (int j = 0; j < writes_arr_size; j++)
        {
            if (writes_arr[j].writer_id == author_arr[i].writer_id)
            {
                books_written++;
            }
        }
        author_arr[i].num_of_books = books_written;
    }
    return (author_arr);
}

author *delete_author(int author_arr_size, author *author_arr, int author_index)
{

    author *new_author_arr;
    new_author_arr = malloc((author_arr_size - 1) * sizeof(author));
    int current_pos = 0;
    for (int i = 0; i < author_arr_size; i++)
    {
        if (i != author_index)
        {
            new_author_arr[current_pos] = author_arr[i];
            current_pos++;
        }
    }
    return (new_author_arr);
}

writes *delete_writes_id(int writes_arr_size, writes *writes_arr, int id, int book_num)
{

    writes *new_writes_arr;
    new_writes_arr = malloc((writes_arr_size - book_num) * sizeof(writes));
    int current_pos = 0;
    for (int i = 0; i < writes_arr_size; i++)
    {
        if (writes_arr[i].writer_id != id)
        {
            new_writes_arr[current_pos] = writes_arr[i];
            current_pos++;
        }
    }
    return (new_writes_arr);
}

book *mass_book_delete(writes *writes_arr, book *book_arr, int writes_array_size, int book_arr_size, int id)
{
    int has_books = 0;
    qsort(writes_arr, writes_array_size, sizeof(writes), writes_id_compare);
    for (int i = 0; i < writes_array_size; i++)
    {
        if (writes_arr[i].writer_id == id)
        {
            int found_book = search_book(book_arr, book_arr_size, writes_arr[i].title);
            book_arr = delete_book(book_arr, book_arr_size, found_book);
            book_arr_size--;
        }
    }
    return book_arr;
}

void print_arr(author *author_arr, int author_arr_size)
{
    printf("---------------");
    for (int i = 0; i < author_arr_size; i++)
    {
        printf("\n%s", author_arr[i].name);
        printf(" %s", author_arr[i].surname);
        printf("\nId: %d\n---------------", author_arr[i].writer_id);
    }
}