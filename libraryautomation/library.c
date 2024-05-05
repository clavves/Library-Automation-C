#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "book.h"
#include "member.h"
#include "library.h"


struct Library createLibrary(int initialBookCapacity, int initialMemberCapacity)
{
    struct Library newLibrary;

    newLibrary.bookCount = 0;
    newLibrary.bookCapacity = initialBookCapacity;
    newLibrary.books = NULL;
    newLibrary.books = calloc(initialBookCapacity, sizeof(struct Book));
    if (newLibrary.books == NULL)
    {
        PRINT_ERROR("Failed to allocate memory for books.");
        exit(EXIT_FAILURE);
    }
    

    FILE *bookFile = fopen("books_data.txt", "w");
    if (bookFile == NULL)
    {
        fprintf(stderr, "Error opening books_data.txt for reading.\n");
        exit(EXIT_FAILURE);
    }
    else if (bookFile != NULL)
    {
        while (fscanf(bookFile, "%d %s %s %d %d %d",
                      &newLibrary.books[newLibrary.bookCount].bookID,
                      newLibrary.books[newLibrary.bookCount].title,
                      newLibrary.books[newLibrary.bookCount].author,
                      &newLibrary.books[newLibrary.bookCount].genre,
                      &newLibrary.books[newLibrary.bookCount].year,
                      &newLibrary.books[newLibrary.bookCount].isBorrowed) == 6)
        {
            newLibrary.bookCount++;

            if (newLibrary.bookCount >= newLibrary.bookCapacity)
            {
                newLibrary.changeBookCapacity(&newLibrary);
            }
        }

        fclose(bookFile);
    }

    newLibrary.memberCount = 0;
    newLibrary.memberCapacity = initialMemberCapacity;
    newLibrary.members = NULL;
    newLibrary.members = calloc(initialMemberCapacity, sizeof(struct Member));
    if (newLibrary.members == NULL)
    {
        PRINT_ERROR("Failed to allocate memory for members.");
        exit(EXIT_FAILURE);
    }

    FILE *memberFile = fopen("members_data.txt", "w");
    if (memberFile == NULL)
    {
        fprintf(stderr, "Error opening members_data.txt for reading.\n");
        exit(EXIT_FAILURE);
    }
    else if (memberFile != NULL)
    {
        while (fscanf(memberFile, "%s %d",
                      newLibrary.members[newLibrary.memberCount].name,
                      &newLibrary.members[newLibrary.memberCount].memberID) == 2)
        {
            newLibrary.memberCount++;

            if (newLibrary.memberCount >= newLibrary.memberCapacity)
            {
                newLibrary.changeMemberCapacity(&newLibrary);
            }
        }

        fclose(memberFile);
    }

    newLibrary.addBook = addBook;
    newLibrary.changeBookCapacity = changeBookCapacity;
    newLibrary.deleteBook = deleteBook;
    newLibrary.findBook = findBook;
    newLibrary.updateBook = updateBook;
    newLibrary.printBookDetails = printBookDetails;
    newLibrary.displayBooks = displayBooks;

    newLibrary.addMember = addMember;
    newLibrary.changeMemberCapacity = changeMemberCapacity;
    newLibrary.deleteMember = deleteMember;
    newLibrary.findMember = findMember;
    newLibrary.updateMember = updateMember;
    newLibrary.printMemberDetails = printMemberDetails;
    newLibrary.displayMembers = displayMembers;
    newLibrary.borrowBook = borrowBook;
    newLibrary.returnBook = returnBook;

    newLibrary.addBookToFile = addBookToFile;
    newLibrary.deleteBookFromFile = deleteBookFromFile;
    newLibrary.findBookInFile = findBookInFile;
    newLibrary.updateBookInFile = updateBookInFile;
    newLibrary.addMemberToFile = addMemberToFile;
    newLibrary.deleteMemberFromFile = deleteMemberFromFile;
    newLibrary.findMemberInFile = findMemberInFile;
    newLibrary.updateMemberInFile = updateMemberInFile;

    printf("Library created.\n");
    return newLibrary;
}

void freeLibrary(struct Library *library)
{
    for (int i = 0; i < library->bookCount; i++)
    {
        free(library->books[i].title);
        free(library->books[i].author);
    }
    free(library->books);

    for (int i = 0; i < library->memberCount; i++)
    {
        free(library->members[i].name);
        free(library->members[i].borrowedBooks);
    }
    free(library->members);
}