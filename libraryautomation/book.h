#ifndef BOOK_H
#define BOOK_H
#define PRINT_ERROR(message) printf("Error: %s\n", message)
#include "library.h"

struct Library;

enum Genre
{
    DYSTOPIAN,
    SCIENCE_FICTION,
    ROMANCE,
    MYSTERY,
    POETRY,
    CHILDRENSBOOK
};

struct Book
{
    int bookID;
    char *title;
    char *author;
    enum Genre genre;
    int year;
    bool isBorrowed;
};

void addBook(struct Library *library, struct Book newBook);
void changeBookCapacity(struct Library *library);
bool bookExists(struct Library *library, int bookID);
void findBook(struct Library *library, int bookID);
void updateBook(struct Library *library, int bookID);
void deleteBook(struct Library *library, int bookID);
void printBookDetails(struct Book *book);
void displayBooks(struct Library *library);
void addBookToFile(struct Library *library, struct Book newBook);
void findBookInFile(const struct Library *library, int bookID);
void updateBookInFile(struct Library *library, int bookID, struct Book updatedBook);
void deleteBookFromFile(struct Library *library, int bookID);

#endif