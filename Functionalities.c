#include "Functionalities.h"


/**
 * @input: Nothing.
 * @output: Loads all movie objects from the file "db" to a movie array and returns it.
 */
movie * load_movies()
{
    char *line_buffer = NULL;
    char *tok;
    size_t line_buffer_length = 0;
    int line_count = get_lines(); /*Get the number of movies in the file.
    Every line is a movie */
    ssize_t line_len;

    FILE *mvf;

    if((mvf = fopen("movie_collection.txt", "r"))==NULL)
    {
        /* If the file does not exist throw error and exit */
        printf("Error, file not found!\n");
        exit(1);
    }

    movie * movie_collection = calloc(sizeof(movie) * sizeof(line_count), 1); //Malloc vs Calloc

    /* Read all the lines from the file */
    line_len = getline(&line_buffer, &line_buffer_length, mvf);
    int i = 0;
    while (line_len >= 0)
    {

        movie film;

        film.director = calloc(sizeof(director_info), 1);
        film.release_date = calloc(sizeof(date), 1);

        /*Break the string at every # and store everything before it.
        Fill the films attributes and then the film array.*/

        tok = strtok(line_buffer, "#");
        if (tok != NULL)
        {
            film.id = atoi(tok); //argument to integer
            tok = strtok(NULL, "#");
        }
        if (tok != NULL)
        {
            film.title = calloc(strlen(tok) * sizeof(char),1);

            strcpy(film.title, tok);
            tok = strtok(NULL, "#");
        }
        if (tok != NULL)
        {
            film.director->director_name = calloc(strlen(tok) * sizeof(char),1);
            strcpy(film.director->director_name, tok);
            tok = strtok(NULL, "#");
        }
        if (tok != NULL)
        {
            film.director->director_surname = calloc(strlen(tok) * sizeof(char),1);
            strcpy(film.director->director_surname, tok);
            tok = strtok(NULL, "#");
        }
        if (tok != NULL)
        {
            film.release_date->day = atoi(tok);
            tok = strtok(NULL, "#");
        }
        if (tok != NULL)
        {
            film.release_date->month = atoi(tok); //Argument to integer
            tok = strtok(NULL, "#");
        }
        if (tok != NULL)
        {
            film.release_date->year = atoi(tok);
            tok = strtok(NULL, "#");
        }
        movie_collection[i] = film;
    
        i++;
        free(line_buffer);
        line_buffer = NULL;
        line_len = getline(&line_buffer, &line_buffer_length, mvf);
        
    }
    free(line_buffer);
    line_buffer = NULL;
    
    fflush(mvf);
    fclose(mvf);
    return movie_collection;
}

/**
 * @input: The array of movies that will be written on the file.
 * @output: Writes the array on the file "db".
 */
void save_movies(movie *movie_collection, char *operation, int arr_size)
{
    FILE *mvf;
    int i;

    if ((mvf = fopen("movie_collection.txt", operation)) == NULL)
    {
        /* If the file does not exist throw error and exit */
        fprintf(stderr, "Error writing to file!");
        exit(1);
    }

    for (i = 0; i < arr_size; i++)
    {
        if(i == 0)
        {
            fprintf(mvf, "%d#", i);
        }
        else
        {
            fprintf(mvf, "\n%d#", i);
        }
        fprintf(mvf, "%s#", movie_collection[i].title);
        fprintf(mvf, "%s#", movie_collection[i].director->director_name);
        fprintf(mvf, "%s#", movie_collection[i].director->director_surname);
        fprintf(mvf, "%d#", movie_collection[i].release_date->day);
        fprintf(mvf, "%d#", movie_collection[i].release_date->month);
        fprintf(mvf, "%d", movie_collection[i].release_date->year);
    }

    fflush(mvf);
    fclose(mvf);
}

/**
 * @input: nothing
 * @output: returns the number of lines in the "db"
 */
int get_lines()
{
    char *line_buffer = NULL;
    size_t line_buffer_length = 0;
    int line_count = 0;
    ssize_t line_len;

    FILE *mvf;

    if ((mvf = fopen("movie_collection.txt", "r")) == NULL)
    {
        /* If the file does not exist throw error and exit */
        fprintf(stderr, "File not found.\n");
        exit(1);
    }
    /* Get the line count of the file */
    line_len = getline(&line_buffer, &line_buffer_length, mvf);
    while (line_len >= 0)
    {
        line_count++;
        line_len = getline(&line_buffer, &line_buffer_length, mvf);
    }
    free(line_buffer);
    line_buffer = NULL;
    fflush(mvf);
    fclose(mvf);
    return line_count; 
}

/**
 * @input: A new movie
 * @output: saves the new array of movies on the "db"
 */
void insert_movie(movie film)
{
    int arr_size = get_lines();
    /*Allocate memory in the array for all the movies in the file + 1, which will be
    the new movie that will be added */
    movie *movie_collection = calloc((sizeof(arr_size) * sizeof(movie)) + (sizeof(arr_size) * sizeof(movie)),1);
    movie_collection = load_movies();

    movie_collection[arr_size] = film;
    save_movies(movie_collection, "w", arr_size+1);
}

/**
 * @input: the id of the movie
 * @output: saves the a new array of movies without the deleted one on the "db"
 */
void delete_movies(int id)
{
    int i;
    int flag = 0;
    int arr_size = get_lines();
    movie *movie_collection = load_movies(); //7
    movie *new_collection; //6

    for (i = 0; i < arr_size; i++)
    {
        if (id == movie_collection[i].id)
        {
           printf("Movie found and will be deleted.\n");
           new_collection = calloc(sizeof(arr_size-1) * sizeof(movie),1);
           flag = 1;
        }
    }
    if(flag == 0)
    {
        printf("Movie not found!");
        new_collection = calloc(sizeof(arr_size) * sizeof(movie),1); //7
    }

    int pos = 0;
    for (i = 0; i < arr_size; i++)
    {
        if (id != movie_collection[i].id)
        {
            new_collection[pos] = movie_collection[i];
            new_collection[pos].id = pos;
            pos++;
        }
    }
    save_movies(new_collection, "w", arr_size-1);
}

/**
 * @input: title of the movie.
 * @output: to screen if it found the movie in the "db".
 */
void search_title(char *title)
{
    int i;
    movie *movie_collection = load_movies();
    int arr_size = get_lines();
    for (i = 0; i < arr_size; i++)
    {
        if (!strcmp(title, movie_collection[i].title)) //!x is x == 0
        {
            printf("ID: %d\n", movie_collection[i].id);
            printf("Director Name: %s\n", movie_collection[i].director->director_name);
            printf("Director Surname: %s\n", movie_collection[i].director->director_surname);
            printf("%d\n", movie_collection[i].release_date->day);
            printf("%d\n", movie_collection[i].release_date->month);
            printf("%d\n", movie_collection[i].release_date->year);
            return;
        }
        
    }
    printf("Movie not found!\n");
}

/**
 * @input: surname of the director to search
 * @output: to screen if it found the director in the "db"
 */
void search_director(char *surname)
{
    int arr_size = get_lines();
    /* Sort and swap variables */
    int i = 0;
    int j = 0;
    
    movie *movie_collection = load_movies();
    movie *temp = NULL;
    movie **sort_array = calloc(arr_size, sizeof(movie *));

    /**
     * Binary search variables.
     */
    int start = 0;          //l
    int end = arr_size - 1; //r
    int middle = 0;         //m

    for (i = 0; i < arr_size; i++)
    {
        sort_array[i] = &movie_collection[i];
    }
    
    // Sort and swap.
    for (i = 0; i < arr_size - 1; i++)
    { 
        for (j = 0; j < arr_size - i - 1; j++)
        {
            if (strcmp(sort_array[j]->director->director_surname, sort_array[j + 1]->director->director_surname) > 0)
            {
                temp = sort_array[j];
                sort_array[j] = sort_array[j + 1];
                sort_array[j + 1] = temp;
                temp = NULL;
            }
        }
    }
    /**
     * Binary Search
     */
    
    while (start <= end)
    {
        middle = start + (end - start) / 2;
     
        // Check if x is present at mid
        if (!strcmp(surname, sort_array[middle]->director->director_surname))
        {
            printf("Director found!\n");
            printf("\nMovie Id: %d\n", sort_array[middle]->id);
            printf("Movie Title: %s\n", sort_array[middle]->title);
            printf("Movie Director Name: %s\n", sort_array[middle]->director->director_name);
            printf("Movie Director Surname: %s\n", sort_array[middle]->director->director_surname);
            printf("Movie Release date: \nDay:%d\n", sort_array[middle]->release_date->day);
            printf("Month:%d\n", sort_array[middle]->release_date->month);
            printf("Year:%d\n\n", sort_array[middle]->release_date->year);
            /*Find duplicates infront of the already found movie.*/
            int next = middle+1;
            if(middle < arr_size-1)
            {
                while(!strcmp(sort_array[middle]->director->director_surname,sort_array[next]->director->director_surname))
                {
                    printf("Director found!\n");
                    printf("\nMovie Id: %d\n", sort_array[next]->id);
                    printf("Movie Title: %s\n", sort_array[next]->title);
                    printf("Movie Director Name: %s\n", sort_array[next]->director->director_name);
                    printf("Movie Director Surname: %s\n", sort_array[next]->director->director_surname);
                    printf("Movie Release date: \nDay:%d\n", sort_array[next]->release_date->day);
                    printf("Month:%d\n", sort_array[next]->release_date->month);
                    printf("Year:%d\n\n", sort_array[next]->release_date->year);
                    next++;
                }
            }
            /*Find duplicates behind of the already found movie.*/
            int previous = middle-1;
            if(middle > 0)
            {
                while(!strcmp(sort_array[middle]->director->director_surname,sort_array[previous]->director->director_surname))
                {
                    printf("\nprevious\n");
                    printf("Director found!\n");
                    printf("\nMovie Id: %d\n", sort_array[previous]->id);
                    printf("Movie Title: %s\n", sort_array[previous]->title);
                    printf("Movie Director Name: %s\n", sort_array[previous]->director->director_name);
                    printf("Movie Director Surname: %s\n", sort_array[previous]->director->director_surname);
                    printf("Movie Release date: \nDay:%d\n", sort_array[previous]->release_date->day);
                    printf("Month:%d\n", sort_array[previous]->release_date->month);
                    printf("Year:%d\n\n", sort_array[previous]->release_date->year);
                    previous--;
                }
            }
            free(sort_array);
            sort_array = NULL;
            return;
        }
        // If x greater, ignore left half
        else if (strcmp(surname, sort_array[middle]->director->director_surname) > 0)
        {
            start = middle + 1;
        }// If x is smaller, ignore right half
        else
        {
            end = middle - 1;
        }
        
    }
    free(sort_array);
    sort_array = NULL;
}