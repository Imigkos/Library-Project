#include "init.h"

author_list *get_authors()
{

    author_list *a_list = malloc(sizeof(author_list));
    FILE *author_file;

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

        new_author->surname = malloc(sizeof(char) * MAX);
        fgets(new_author->surname, MAX, author_file);
        new_author->surname[strcspn(new_author->surname, "\n")] = 0;

        new_author->name = malloc(sizeof(char) * MAX);
        fgets(new_author->name, MAX, author_file);
        new_author->name[strcspn(new_author->name, "\n")] = 0;

        fgets(buffer, MAX, author_file);
        new_author->num_of_books = atoi(buffer);

        new_author->next = a_list->head;
        a_list->head = new_author;
    }

    return (a_list);
}

book_list *get_books()
{

    book_list *b_list = malloc(sizeof(book_list));
    FILE *book_file;

    char buffer[MAX];

    if ((book_file = fopen("book.txt", "r")) == NULL)
    {
        printf("File does not exist or cannot be opened.\n");
        exit(1);
    }
    fgets(buffer, MAX, book_file);
    b_list->entries = atoi(buffer);
    while (fgets(buffer, MAX, book_file))
    {
        book *new_book;
        new_book = malloc(sizeof(book));
        new_book->release_date = atoi(buffer);

        new_book->title = malloc(sizeof(char) * MAX);
        fgets(new_book->title, MAX, book_file);
        new_book->title[strcspn(new_book->title, "\n")] = 0;

        fgets(buffer, MAX, book_file);
        new_book->price = atof(buffer);

        new_book->next = b_list->head;
        b_list->head = new_book;
    }

    return (b_list);
}

writes_list *get_writes()
{

    writes_list *w_list = malloc(sizeof(writes_list));
    FILE *writes_file;

    char buffer[MAX];

    if ((writes_file = fopen("writes.txt", "r")) == NULL)
    {
        printf("File does not exist or cannot be opened.\n");
        exit(1);
    }
    fgets(buffer, MAX, writes_file);
    w_list->entries = atoi(buffer);
    while (fgets(buffer, MAX, writes_file))
    {
        writes *new_writes;
        new_writes = malloc(sizeof(writes));
        new_writes->writer_id = atoi(buffer);

        new_writes->title = malloc(sizeof(char) * MAX);
        fgets(new_writes->title, MAX, writes_file);
        new_writes->title[strcspn(new_writes->title, "\n")] = 0;

        new_writes->next = w_list->head;
        w_list->head = new_writes;
    }

    return (w_list);
}

void print_a_list(const author_list *list)
{
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

void print_a_node(author *a)
{
    printf("%s %s", a->surname,a->name);
}

void print_b_node(book *b)
{
    printf("\n------------\n");
    printf("%s\n", b->title);
    printf("%d\n", b->release_date);
    printf("%.2f\n", b->price);
    printf("------------");
}

void print_b_list(const book_list *list)
{
    book *cur;
    cur = list->head;
    while (cur)
    {
        printf("------------\n");
        printf("%s\n", cur->title);
        printf("%.2f\n", cur->price);
        printf("%d\n", cur->release_date);
        printf("------------\n");
        cur = cur->next;
    }
}

void print_w_list(const writes_list *list)
{
    writes *cur;
    cur = list->head;
    while (cur)
    {
        printf("------------\n");
        printf("%s\n", cur->title);
        printf("%d\n", cur->writer_id);
        printf("------------\n");
        cur = cur->next;
    }
}

void insert_author(author_list *a_list)
{
    author *new_author;
    new_author = malloc(sizeof(author));

    char *buffer = malloc(512 * sizeof(char));
    printf("\nEnter the author's name: ");
    scanf("%s", buffer);
    new_author->name = malloc(strlen(buffer) * sizeof(char));
    strcpy(new_author->name, buffer);
    free(buffer);
    buffer = NULL;

    buffer = malloc(512 * sizeof(char));
    printf("\nEnter the author's surname: ");
    scanf("%s", buffer);
    new_author->surname = malloc(strlen(buffer) * sizeof(char));
    strcpy(new_author->surname, buffer);
    free(buffer);
    buffer = NULL;

    new_author->writer_id = (++a_list->entries);
    new_author->num_of_books = 0;

    new_author->next = a_list->head;
    a_list->head = new_author;
}

void insert_book(book_list *b_list)
{
    book *new_book;
    new_book = malloc(sizeof(book));

    char *buffer = malloc(512 * sizeof(char));
    printf("\nEnter the book's title: ");
    fgets(buffer, MAX, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    new_book->title = malloc(strlen(buffer) * sizeof(char));
    strcpy(new_book->title, buffer);
    free(buffer);
    buffer = NULL;

    printf("\nEnter the book's release date: ");
    scanf("%d", &new_book->release_date);

    printf("\nEnter the book's price: ");
    scanf("%f", &new_book->price);

    b_list->entries++;
    new_book->next = b_list->head;
    b_list->head = new_book;
}

void insert_writes(writes_list *w_list, int id, char *title)
{
    writes *new_writes;
    new_writes = malloc(sizeof(writes));

    new_writes->title = malloc(strlen(title) * sizeof(char));
    strcpy(new_writes->title, title);

    new_writes->writer_id = id;

    w_list->entries++;
    new_writes->next = w_list->head;
    w_list->head = new_writes;
}

author *search_author(author_list *a_list, char *surname)
{
    author *cur = a_list->head;
    while (cur != NULL)
    {
        if (strcasecmp(cur->surname, surname) == 0)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

book *search_book(book_list *b_list, char *title)
{
    book *cur = b_list->head;
    while (cur != NULL)
    {
        if (strcasecmp(cur->title, title) == 0)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void search_writes_by_id(writes_list *w_list, book_list *b_list, int id)
{
    int has_books = 0;
    writes *cur = w_list->head;
    while (cur != NULL)
    {
        if (cur->writer_id == id)
        {
            book *found_book = search_book(b_list, cur->title);
            print_b_node(found_book);
            has_books = 1;
        }
        cur = cur->next;
    }
    if (has_books == 0)
    {
        printf("\nThere are no book entries regarding this author\n ");
    }
}

void update_num_of_books(author_list *a_list, writes_list *w_list)
{

    author *a_cur;
    writes *w_cur;
    int books_written;

    a_cur = a_list->head;

    while (a_cur != NULL)
    {
        w_cur = w_list->head;
        books_written = 0;
        while (w_cur != NULL)
        {
            if (w_cur->writer_id == a_cur->writer_id)
            {
                books_written++;
                w_cur = w_cur->next;
            }
            else
            {
                w_cur = w_cur->next;
            }
        }
        a_cur->num_of_books = books_written;
        if (a_cur != NULL)
        {
            a_cur = a_cur->next;
        }
    }
}

writes *search_writes_by_title(writes_list *w_list, char *title)
{
    writes *cur = w_list->head;
    while (cur != NULL)
    {
        if (strcasecmp(cur->title, title) == 0)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

author *search_author_id(author_list *a_list, int id)
{
    author *cur = a_list->head;
    while (cur != NULL)
    {
        if (cur->writer_id == id)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}


