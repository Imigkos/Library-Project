#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct book
{
   char *title;
   int release_date;
   float price;
} book;

   typedef struct author
{
   int writer_id;
   char *surname;
   char *name;
   int num_of_books;
   struct author *next;
} author;

typedef struct writes
{
   char *title;
   int writer_id;
} writes;

typedef struct author_list
{
   author *head;
   int entries;
}author_list;

typedef struct book_list
{
   book *head;
   int entries;
}book_list;

typedef struct writes_list
{
   writes *head;
   int entries;
}writes_list;

//author * get_authors();