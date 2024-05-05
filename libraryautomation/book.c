#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "book.h"
#include "library.h"


void addBook(struct Library *library, struct Book newBook)
{
    if (library->bookCount >= library->bookCapacity)
    {
        PRINT_ERROR("The library is full.");
        library->changeBookCapacity(library);
    }

    if (bookExists(library, newBook.bookID))
    {
        PRINT_ERROR("Book with the same ID already exists. Book not added.");
        return;
    }
    if (library->bookCount < library->bookCapacity)
    {
        library->books[library->bookCount].title = malloc(strlen(newBook.title) + 1);
        library->books[library->bookCount].author = malloc(strlen(newBook.author) + 1);

        if (library->books[library->bookCount].title == NULL || library->books[library->bookCount].author == NULL)
        {
            PRINT_ERROR("Failed to allocate memory for title or author.");
            return;
        }

        strcpy(library->books[library->bookCount].title, newBook.title);
        strcpy(library->books[library->bookCount].author, newBook.author);

        library->books[library->bookCount].bookID = newBook.bookID;
        library->books[library->bookCount].genre = newBook.genre;
        library->books[library->bookCount].year = newBook.year;
        library->books[library->bookCount].isBorrowed = newBook.isBorrowed;

        library->bookCount++;
        printf("Book added.\n");
    }
}

void changeBookCapacity(struct Library *library)
{
    int answer;
    printf("Would you like to change book capacity?\nIf yes please write 1.\n");
    scanf(" %d", &answer);
    int increment;
    int newCapacity;
    struct Book *temp;
    switch (answer)
    {
    case 1:
        
        printf("Enter the amount of incrementation: ");
        scanf("%d", &increment);

        newCapacity = increment + library->bookCapacity;

        temp = realloc(library->books, newCapacity * sizeof(struct Book));
        if (temp == NULL)
        {
            PRINT_ERROR("Failed to allocate memory. Capacity not changed.");
            return;
        }
        library->books = temp;

        library->bookCapacity = newCapacity;

        printf("Capacity changed to %d books.\n", library->bookCapacity);
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }
}

bool bookExists(struct Library *library, int bookID)
{
    for (int i = 0; i < library->bookCount; i++)
    {
        if (library->books[i].bookID == bookID)
        {
            return true;
        }
    }
    return false;
}

void findBook(struct Library *library, int bookID)
{
    if (!bookExists(library, bookID))
    {
        PRINT_ERROR("Book not found.");
        return;
    }

    for (int i = 0; i < library->bookCount; i++)
    {
        if (library->books[i].bookID == bookID)
        {
            printf("Book found.\n");
            printBookDetails(&library->books[i]);
            return;
        }
    }
}

void updateBook(struct Library *library, int bookID)
{
    if (!bookExists(library, bookID))
    {
        PRINT_ERROR("Book not found.");
        return;
    }

    for (int i = 0; i < library->bookCount; i++)
    {
        if (library->books[i].bookID == bookID)
        {
            int choice;
            printf("Select information to update:\n");
            printf("1. Title\n");
            printf("2. Author\n");
            printf("3. Genre\n");
            printf("4. Year\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                printf("Enter new title: ");
                scanf("%s", library->books[i].title);
                break;
            case 2:
                printf("Enter new author: ");
                scanf("%s", library->books[i].author);
                break;
            case 3:
                printf("Enter new genre (0:Dystopian, 1:Science Fiction, 2:Romance, 3:Mystery, 4:Poetry, 5:Children's Book): ");
                scanf("%d", &(library->books[i].genre));
                break;
            case 4:
                printf("Enter new year: ");
                scanf("%d", &(library->books[i].year));
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
            printf("Book updated successfully.\n");
            printBookDetails(&library->books[i]);
            return;
        }
    }
}

void deleteBook(struct Library *library, int bookID)
{
    if (!bookExists(library, bookID))
    {
        PRINT_ERROR("Book not found.");
        return;
    }

    for (int i = 0; i < library->bookCount; i++)
    {
        if (library->books[i].bookID == bookID)
        {
            for (int j = i; j < library->bookCount; j++)
            {
                library->books[j] = library->books[j + 1];
            }
            --library->bookCount;
            return;
        }
    }
}

void printBookDetails(struct Book *book)
{
    printf("ID: %d\n", book->bookID);
    printf("Title: %s\n", book->title);
    printf("Author: %s\n", book->author);
    switch (book->genre) {
        case DYSTOPIAN:
            printf("Genre: DYSTOPIAN\n");
            break;
        case SCIENCE_FICTION:
            printf("Genre: SCIENCE FICTON\n");
            break;
        case ROMANCE:
            printf("Genre: ROMANCE\n");
            break;
        case MYSTERY:
            printf("Genre: MYSTERY\n");
            break;
        case POETRY:
            printf("Genre: POETRY\n");
            break;
        case CHILDRENSBOOK:
            printf("Genre: CHIDLREN'S BOOK\n");
            break;
        default:
            printf("Unknown genre\n");
    }
    printf("Year: %d\n", book->year);
    printf("\n");
}

void displayBooks(struct Library *library)
{
    for (int i = 0; i < library->bookCount; i++)
    {
        printBookDetails(&library->books[i]);
    }
}

void addBookToFile(struct Library *library, struct Book newBook)
{
    FILE *file = fopen("books_data.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "%d %s %s %d %d %d\n", newBook.bookID, newBook.title, newBook.author, newBook.genre, newBook.year, newBook.isBorrowed);
        fclose(file);
    }
}

void findBookInFile(const struct Library *library, int bookID)
{
    FILE *file = fopen("books_data.txt", "r");
    if (file != NULL)
    {
        struct Book tempBook;
        tempBook.title=malloc(sizeof(100));
        tempBook.author=malloc(sizeof(100));
        while (fscanf(file, "%d %s %s %d %d %d", &tempBook.bookID, tempBook.title, tempBook.author, &tempBook.genre, &tempBook.year, &tempBook.isBorrowed) == 6)
        {
            if (tempBook.bookID == bookID)
            {
                fclose(file);
                printf("Book found in file.\n");
                printBookDetails(&tempBook);
                return;
            }
        }
        fclose(file);
        PRINT_ERROR("Book not found in file.");
    }
}

void updateBookInFile(struct Library *library, int bookID, struct Book updatedBook)
{
    printf("ok1.\n");
    FILE *file = fopen("books_data.txt", "r");
    printf("ok2.\n");
    if (file != NULL)
    {
        printf("ok3.\n");
        FILE *tempFile = fopen("temp_books_data.txt", "w");
        printf("ok4.\n");
        if (tempFile != NULL)
        {
            printf("ok5.\n");
            struct Book tempBook;
            tempBook.title=malloc(sizeof(1000));
            tempBook.author=malloc(sizeof(1000));
            printf("ok6.\n");
            while (fscanf(file, "%d %s %s %d %d %d", &tempBook.bookID, tempBook.title, tempBook.author, &tempBook.genre, &tempBook.year, &tempBook.isBorrowed) == 6)
            {
                printf("%d", tempBook.bookID);
                if (tempBook.bookID == bookID)
                {
                    printf("ok8.\n");
                    fprintf(tempFile, "%d %s %s %d %d %d\n", updatedBook.bookID, updatedBook.title, updatedBook.author, updatedBook.genre, updatedBook.year, updatedBook.isBorrowed);
                }
                else
                {
                    fprintf(tempFile, "%d %s %s %d %d %d\n", tempBook.bookID, tempBook.title, tempBook.author, tempBook.genre, tempBook.year, tempBook.isBorrowed);
                }
            }
            printf("ok9.\n");
            fclose(file);
            fclose(tempFile);
            remove("books_data.txt");
            rename("temp_books_data.txt", "books_data.txt");
            printf("Book updated in file");
            free(tempBook.title);
            free(tempBook.author);
            printf("ok10.\n");
        }
        else
        {
            PRINT_ERROR("Failed to open temporary file for writing.");
            fclose(file);
        }
    }
    else
    {
        PRINT_ERROR("Failed to open file for reading.");
    }
}

void deleteBookFromFile(struct Library *library, int delete_bookID)
{
    FILE *file = fopen("books_data.txt", "r");
    if (file != NULL)
    {
        FILE *tempFile = fopen("temp_books_data.txt", "w");
        if (tempFile != NULL)
        {
            int bookID;
            char title[30];
            char *author[30];
            enum Genre genre;
            int year;
            bool isBorrowed;

            while (fscanf(file, "%d %s %s %d %d %d", &bookID, &title, &author, &genre, &year, &isBorrowed) == 6)
            {
                if (bookID != delete_bookID)
               
                { printf("ok");
                    fprintf(tempFile, "%d %s %s %d %d %d\n", bookID, title, author, genre, year, isBorrowed);
                }
            }
            fclose(file);
            fclose(tempFile);
            remove("books_data.txt");
            rename("temp_books_data.txt", "books_data.txt");
        }
        else
        {
            PRINT_ERROR("Failed to open temporary file for writing.");
            fclose(file);
        }
    }
    else
    {
        PRINT_ERROR("Failed to open file for reading.");
    }
}