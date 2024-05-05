#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "book.c"
#include "member.c"
#include "library.c"



int main() {
    
    struct Library l1 = createLibrary(1,1);

    struct Book b1 = {1, "The_Hunger_Games", "Suzanne_Collins", DYSTOPIAN, 2008, false};
    struct Book b2 = {2, "1984", "George_Orwell", DYSTOPIAN, 1949, false};
    struct Book b3 = {3, "Pride_and_Prejudice", "Jane_Austen", ROMANCE, 1814, false};
    addBook(&l1,b1);
    addBookToFile(&l1,b1);
    addBook(&l1,b2);
    addBookToFile(&l1,b2);
    addBook(&l1,b3);
    addBookToFile(&l1,b3);

    findBook(&l1,1);
    findBookInFile(&l1,1);

    updateBook(&l1,3);
    //updateBookInFile(&l1,3, b3);

    printf("Previous Book List\n");
    displayBooks(&l1);

    deleteBook(&l1,1);
    //deleteBookFromFile(&l1,b1.bookID);

    printf("Updated Book List\n");
    displayBooks(&l1);


    struct Member m1 = {"Eda", 1};
    struct Member m2 = {"Naz", 2};
    struct Member m3 = {"Ece", 3};
    

    addMember(&l1, m1);
    addMemberToFile(&l1, m1);
    addMember(&l1, m2);
    addMemberToFile(&l1, m2);
    addMember(&l1, m3);
    addMemberToFile(&l1, m3);

    findMember(&l1, m1.memberID);
    //findMemberInFile(&l1, m1.memberID);

    updateMember(&l1, m1.memberID);
    //updateMemberInFile(&l1, m1.memberID, m1);
    
    printf("Previous Member List\n");
    displayMembers(&l1);

    deleteMember(&l1, m3.memberID);
    //deleteMemberFromFile(&l1, m3.memberID);
    updateMember(&l1, m1.memberID);
    //updateMemberInFile(&l1, m1.memberID, m1);
    
    printf("Updated Member List\n");
    displayMembers(&l1);

    return 0;
}