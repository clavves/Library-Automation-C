#ifndef MEMBER_H
#define MEMBER_H
#include "library.h"


struct Library; 
struct Book;

struct Member
{
    char *name;
    int memberID;
    struct Book *borrowedBooks;
    int borrowedBookCount;
};

void addMember(struct Library *library, struct Member newMember);
void changeMemberCapacity(struct Library *library);
bool memberExists(struct Library *library, int memberID);
void findMember(struct Library *library, int memberID);
void updateMember(struct Library *library, int memberID);
void deleteMember(struct Library *library, int memberID);
void printMemberDetails(struct Member *member);
void displayMembers(struct Library *library);
void borrowBook(struct Library *library, int memberID, int bookID);
void returnBook(struct Library *library, int memberID, int bookID);
void addMemberToFile(struct Library *library, struct Member newMember);
void findMemberInFile(struct Library *library, int memberID);
void updateMemberInFile(struct Library *library, int memberID, struct Member updatedMember);
void deleteMemberFromFile(struct Library *library, int memberID);

#endif