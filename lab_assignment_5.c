#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char letter;
    struct node* next;
} node;

// Returns number of nodes in the linked list.
int length(node* head) {
    int len = 0;
    
    // stop counting when current node points to NULL
    while (head != NULL) {
        len++;
        head = head->next;
    }
    return len;
}

// Parses the string in the linked list
char* toCString(node* head) {
    // use length() to determine the size of the string
    int len = length(head);

    // allocate memory for the string +1 char for the null terminator
    char* str = (char*)malloc(sizeof(char) * (len + 1));

    // copy the characters from the linked list to the string incrementally
    int i = 0;
    while (head != NULL) {
        str[i++] = head->letter;
        head = head->next;
    }

    // add the null terminator to the end of the string
    str[i] = '\0'; 
    return str;
}

// Inserts character to the linked list
void insertChar(node** pHead, char c) {
    // allocate memory for a new node
    node* newNode = (node*)malloc(sizeof(node));

    // set the letter and next pointer of the new node
    newNode->letter = c;
    newNode->next = NULL;

    // if the linked list is empty, set the head to the new node
    if (*pHead == NULL) {
        *pHead = newNode;
    }

    // otherwise, traverse the linked list to the end and add the new node
    else {
        node* current = *pHead;

        // stop when current node points to NULL
        while (current->next != NULL) {
            current = current->next;
        }
        
        //point the last node to the new created node
        current->next = newNode;
    }
}

// Deletes all nodes in the linked list.
void deleteList(node** pHead) {
    // curremt and next node pointers
    node* current = *pHead;
    node* next;

    // free each node in the linked list
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    // set the head to NULL to reflect the empty linked list
    *pHead = NULL;
}

int main(void) {
    int i, strLen, numInputs;
    node* head = NULL;
    char* str;
    char c;
    FILE* inFile = fopen("input.txt", "r");

    if (inFile == NULL) {
        printf("Could not open file input.txt\n");
        return 1;
    }
    
    fscanf(inFile, " %d\n", &numInputs);
    while (numInputs-- > 0) {
        fscanf(inFile, " %d\n", &strLen);

        for (i = 0; i < strLen; i++) {
            fscanf(inFile, " %c", &c);
            insertChar(&head, c);
        }

        str = toCString(head);
        printf("String is : %s\n", str);

        free(str);
        deleteList(&head);

        if (head != NULL) {
            printf("deleteList is not correct!\n");
            break;
        }
    }
    fclose(inFile);
    return 0;
}
