#ifndef MOVIE_COLLECTION_H_INCLUDED
#define MOVIE_COLLECTION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct date
{
    int day, month, year;
} date;

typedef struct director_info
{
    char* director_surname; 
    char* director_name;
} director_info;

typedef struct movie
{
    int id;
    char* title;
    director_info* director;
    date* release_date;
} movie;

movie *load_movies();
int get_lines();
void delete_movies(int id);
void insert_movie(movie film);
void search_title(char *title);
void search_director(char* surname);
void save_movies(movie *movie_collection, char* operation, int arr_size);
#endif