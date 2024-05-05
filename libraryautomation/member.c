#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "member.h"
#include "library.h"

#define MAX_BORROWED_BOOKS 5

void addMember(struct Library *library, struct Member newMember)
{
    if (library->memberCount >= library->memberCapacity)
    {
        PRINT_ERROR("The member list is full.");
        library->changeMemberCapacity(library);
    }

    if (memberExists(library, newMember.memberID))
    {
        PRINT_ERROR("Member with the same ID already exists. Member not added.");
        return;
    }

    if (library->memberCount < library->memberCapacity)
    {
        library->members[library->memberCount].name = malloc(strlen(newMember.name) + 1);

        if (library->members[library->memberCount].name == NULL)
        {
            PRINT_ERROR("Failed to allocate memory for member name.");
            return;
        }

        strcpy(library->members[library->memberCount].name, newMember.name);

        library->members[library->memberCount].memberID = newMember.memberID;
        library->members[library->memberCount].borrowedBookCount = 0;

        library->members[library->memberCount].borrowedBooks = malloc(MAX_BORROWED_BOOKS * sizeof(struct Book));

        if (library->members[library->memberCount].borrowedBooks == NULL)
        {
            PRINT_ERROR("Failed to allocate memory for borrowedBooks.");
            free(library->members[library->memberCount].name);
            return;
        }

        library->memberCount++;
        printf("Member added.\n");
    }
}

void changeMemberCapacity(struct Library *library)
{
    int answer;
    printf("Would you like to change member capacity?\nIf yes please write 1.\n");
    scanf(" %d", &answer);
    int increment;
    int newCapacity;
    switch (answer)
    {
    case 1:
        
        printf("Enter the amount of incrementation: ");
        scanf("%d", &increment);

        newCapacity = increment + library->memberCapacity;

        library->members = realloc(library->members, newCapacity * sizeof(struct Member));
        if (library->members == NULL)
        {
            PRINT_ERROR("Failed to allocate memory. Capacity not changed.");
            return;
        }
        library->memberCapacity = newCapacity;

        printf("Capacity changed to %d members.\n", library->memberCapacity);
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }
}

bool memberExists(struct Library *library, int memberID)
{
    for (int i = 0; i < library->memberCount; i++)
    {
        if (library->members[i].memberID == memberID)
        {
            return true;
        }
    }
    return false;
}

void findMember(struct Library *library, int memberID)
{
    if (!memberExists(library, memberID))
    {
        PRINT_ERROR("Member not found.");
        return;
    }

    for (int i = 0; i < library->memberCount; i++)
    {
        if (library->members[i].memberID == memberID)
        {
            printf("Member found.\n");
            printMemberDetails(&library->members[i]);
            return;
        }
    }
}

void updateMember(struct Library *library, int memberID)
{
    if (!memberExists(library, memberID))
    {
        PRINT_ERROR("Member not found.");
        return;
    }

    for (int i = 0; i < library->memberCount; i++)
    {
        if (library->members[i].memberID == memberID)
        {
            int choice;
            printf("Select information to update:\n");
            printf("1. Name\n");
            printf("2. Borrow book\n");
            printf("3. Return book\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                printf("Enter new name: ");
                scanf("%s", library->members[i].name);
                break;
            case 2:
                printf("Enter book ID that will be borrowed:  ");
                int bookID1;
                scanf("%d", &bookID1);
                borrowBook(library, memberID, bookID1);
                break;
            case 3:
                printf("Enter book ID that will be returned:  ");
                int bookID2;
                scanf("%d", &bookID2);
                returnBook(library, memberID, bookID2);
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
            printf("Member is updated.\n");
            printMemberDetails(&library->members[i]);
            return;
        }
    }
}

void deleteMember(struct Library *library, int memberID)
{
    if (!memberExists(library, memberID))
    {
        PRINT_ERROR("Member not found.");
        return;
    }

    for (int i = 0; i < library->memberCount; i++)
    {
        if (library->members[i].memberID == memberID)
        {
            for (int j = i; j < library->memberCount; j++)
            {
                library->members[j] = library->members[j + 1];
            }
            --library->memberCount;
            return;
        }
    }
}

void printMemberDetails(struct Member *member)
{
    printf("ID: %d\n", member->memberID);
    printf("Name: %s\n", member->name);
    printf("Borrowed Books\n");
    for (int i = 0; i < member->borrowedBookCount; i++)
    {
        printf("%s by %s\n", member->borrowedBooks[i].title, member->borrowedBooks[i].author);
    }
    printf("\n");
}

void displayMembers(struct Library *library)
{
    for (int i = 0; i < library->memberCount; i++)
    {
        printMemberDetails(&library->members[i]);
    }
}

void borrowBook(struct Library *library, int memberID, int bookID)
{
    if (!memberExists(library, memberID))
    {
        PRINT_ERROR("Member not found.");
        return;
    }

    if (!bookExists(library, bookID))
    {
        PRINT_ERROR("Book not found.");
        return;
    }

    struct Member *member = NULL;
    for (int i = 0; i < library->memberCount; i++)
    {
        if (library->members[i].memberID == memberID)
        {
            member = &library->members[i];
            break;
        }
    }

    struct Book *book = NULL;
    for (int i = 0; i < library->bookCount; i++)
    {
        if (library->books[i].bookID == bookID)
        {
            book = &library->books[i];
            break;
        }
    }

    if (book->isBorrowed)
    {
        PRINT_ERROR("The book is already borrowed.");
        return;
    }

    book->isBorrowed = true;
    member->borrowedBooks[member->borrowedBookCount++] = *book;

    printf("Book (%s by %s) successfully borrowed by %s.\n", book->title, book->author, member->name);
}

void returnBook(struct Library *library, int memberID, int bookID)
{
    if (!memberExists(library, memberID))
    {
        PRINT_ERROR("Member not found.");
        return;
    }

    if (!bookExists(library, bookID))
    {
        PRINT_ERROR("Book not found.");
        return;
    }

    struct Member *member = NULL;
    for (int i = 0; i < library->memberCount; i++)
    {
        if (library->members[i].memberID == memberID)
        {
            member = &library->members[i];
            break;
        }
    }

    struct Book *book = NULL;
    for (int i = 0; i < library->bookCount; i++)
    {
        if (library->books[i].bookID == bookID)
        {
            book = &library->books[i];
            break;
        }
    }

    if (!book->isBorrowed)
    {
        PRINT_ERROR("The book is not currently borrowed.");
        return;
    }

    book->isBorrowed = false;

    for (int i = 0; i < member->borrowedBookCount; i++)
    {
        if (member->borrowedBooks[i].bookID == bookID)
        {
            for (int j = i; j < member->borrowedBookCount; j++)
            {
                member->borrowedBooks[j] = member->borrowedBooks[j + 1];
            }
            --member->borrowedBookCount;
            printf("Book (%s by %s) returned by %s.\n", book->title, book->author, member->name);
            return;
        }
    }
}

void addMemberToFile(struct Library *library, struct Member newMember)
{
    FILE *file = fopen("members_data.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "%s %d\n", newMember.name, newMember.memberID);
        fclose(file);
    }
}

void findMemberInFile(struct Library *library, int memberID)
{
    FILE *file = fopen("members_data.txt", "r");
    if (file != NULL)
    {
        struct Member tempMember;
        tempMember.name = malloc(sizeof(100));
        while (fscanf(file, "%s %d", tempMember.name, &tempMember.memberID) == 2)
        {
            if (tempMember.memberID == memberID)
            {
                fclose(file);
                printf("Member found in file.\n");
                printMemberDetails(&tempMember);
                return;
            }
        }
        fclose(file);
        PRINT_ERROR("Member not found in file.");
    }
}

void updateMemberInFile(struct Library *library, int updated_memberID, struct Member updatedMember)
{
    FILE *file = fopen("members_data.txt", "r");
    if (file != NULL)
    {
        FILE *tempFile = fopen("temp_members_data.txt", "w");
        if (tempFile != NULL)
        {
            char name[50];
            int memberID;
            while (fscanf(file, "%s %d", &name, &memberID) == 2)
            {
                if (memberID == updated_memberID)
                {
                    fprintf(tempFile, "%s %d\n", name, memberID);
                    printf("Member updated in file.\n");
                }
                else
                {
                    fprintf(tempFile, "%s %d\n", name, memberID);
                }
            }
            fclose(file);
            fclose(tempFile);
            remove("members_data.txt");
            rename("temp_members_data.txt", "members_data.txt");
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

void deleteMemberFromFile(struct Library *library, int delete_memberID)
{
    FILE *file = fopen("members_data.txt", "r");
    if (file != NULL)
    {
        FILE *tempFile = fopen("temp_members_data.txt", "w");
        if (tempFile != NULL)
        {
            char name[50];
            int memberID;
            while (fscanf(file, "%s %d", &name, &memberID) == 2)
            {
                if (memberID != delete_memberID)
                {
                    fprintf(tempFile, "%s %d\n", name, memberID);
                }
            }
            fclose(file);
            fclose(tempFile);
            remove("members_data.txt");
            rename("temp_members_data.txt", "members_data.txt");
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