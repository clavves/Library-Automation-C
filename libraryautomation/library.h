#ifndef LIBRARY_H
#define LIBRARY_H
#include "book.h"
#include "member.h"

struct Member;

struct Library
{
    struct Book *books;
    int bookCount;
    int bookCapacity;

    struct Member *members;
    int memberCount;
    int memberCapacity;

    void (*addBook)(struct Library *, struct Book);
    void (*changeBookCapacity)(struct Library *);
    void (*deleteBook)(struct Library *, int);
    void (*findBook)(struct Library *, int);
    void (*updateBook)(struct Library *, int);
    void (*printBookDetails)(struct Book *);
    void (*displayBooks)(struct Library *);
    
    void (*addMember)(struct Library *, struct Member);
    void (*changeMemberCapacity)(struct Library *);
    void (*deleteMember)(struct Library *, int);
    void (*findMember)(struct Library *, int);
    void (*updateMember)(struct Library *, int);
    void (*printMemberDetails)(struct Member *);
    void (*displayMembers)(struct Library *);
    void (*borrowBook)(struct Library *, int, int);
    void (*returnBook)(struct Library *, int, int);

    void (*addBookToFile)(struct Library *, struct Book);
    void (*deleteBookFromFile)(struct Library *, int);
    void (*findBookInFile)(const struct Library *, int);
    void (*updateBookInFile)(struct Library *library, int bookID, struct Book updatedBook);
    void (*addMemberToFile)(struct Library *, struct Member);
    void (*deleteMemberFromFile)(struct Library *, int);
    void (*findMemberInFile)(struct Library *, int);
    void (*updateMemberInFile)(struct Library *library, int memberID, struct Member updatedMember);
};

struct Library createLibrary(int initialBookCapacity, int initialMemberCapacity);
void freeLibrary(struct Library *library);

#endif