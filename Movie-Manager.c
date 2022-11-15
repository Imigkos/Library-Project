#include "Functionalities.h"
#include "Functionalities.c"

void main(int argc, char *argv[])
{
    int exit = 0;
    while (exit == 0) 
    {
        int menu_choice;

        printf("Specify an option by entering a number below:\n");
        printf("1. Insert a new movie\n 2. Delete a movie based on movie's id\n 3. Search a movie based on movie's title\n");
        printf("4. Search a movie based on movies director\n 5. Exit \n");
        scanf("%d", &menu_choice);

        if (menu_choice == 1)
        {
            /*Create a new film, fill-in it's variables and pass it to the
            insert method which will store it in an array */
            movie film; 
            int day;
            int month;
            int year;

            film.director = calloc(sizeof(director_info), 1);
            film.release_date = calloc(sizeof(date), 1);

            char *buffer = calloc(512 * sizeof(char), 1);
            printf("Enter the movie's title:\n");
            scanf("%s", buffer);
            film.title = calloc(strlen(buffer) * sizeof(char), 1);
            strcpy(film.title, buffer);
            free(buffer);
            buffer = NULL;

            buffer = calloc(512 * sizeof(char), 1);
            printf("Enter the director's name:\n");
            scanf("%s", buffer);
            film.director->director_name = calloc(strlen(buffer) * sizeof(char), 1);
            strcpy(film.director->director_name, buffer);
            free(buffer);
            buffer = NULL;

            buffer = calloc(512 * sizeof(char), 1);
            printf("Enter the director's surname:\n");
            scanf("%s", buffer);
            film.director->director_surname = calloc(strlen(buffer) * sizeof(char), 1);
            strcpy(film.director->director_surname, buffer);
            free(buffer);
            buffer = NULL;

            printf("Enter the movie's release date {day} {month} {year}:\n");
            scanf("%d", &film.release_date->day);
            scanf("%d", &film.release_date->month);
            scanf("%d", &film.release_date->year);

            /*Call the insert_movie function and pass it the film we just created */
            insert_movie(film);
        }

        else if(menu_choice == 2)
        {
            /*Call the delete_movie function and give it the id */
            int id;
            printf("Enter the id of the movie:\n");
            scanf("%d",&id);

            delete_movies(id);
        }
        else if (menu_choice == 3)
        {
            /*Call the search_title function and give it the title */
            char *title = calloc(512 * sizeof(char), 1);
            printf("Enter the title of the movie:\n");
            scanf("%s", title);

            search_title(title);
        }

        else if (menu_choice == 4)
        {
            /*Call the search_director function and give it the 
            director's surname */
            char *surname = calloc(512 * sizeof(char), 1);
            printf("Enter the surname of the movie's director:\n");
            scanf("%s", surname);
            search_director(surname);
        }
        else if(menu_choice == 5)
        {
            /*Exit the application, the save is not done here
            since each function called saves on it's own. */
            return;
        }
        else
        {
            /*If the input is invalid, show a message. */
            printf("\nEnter a valid number!\n");
        }
    }
}