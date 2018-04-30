#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * client.c.
 * Reads client data in from a file and searches it.
 * @author Junior Developer and Nikolah Pearce
 */

struct client {
    char* firstName;
    char* lastName;
    int phone;
    char* emailAddress;
};

/* What is this? Static variables need comments too */
static int count;

/**
 * What does this method do?
 * @param clientArray what is the parameter?
 */
void sortFirstName(struct client** clientArray) {
    int i, j;
    for(i = 0; i < count; i++) {
        for (j = 0; j < count; j++) {
            if (clientArray[i]->firstName > clientArray[j]->firstName) {
                struct client* tmp = clientArray[i];
                clientArray[i] = clientArray[j];
                clientArray[j] = tmp;
            }
        }
    }
}

/**
 * What does this method do?
 * @param clientArray what is the parameter?
 * @return what do we return?
 */
int findFirstName(struct client** clientArray, char* str) {
    int i = 0;
    for(i = 0; i < count; i++) {
        if (strcmp(clientArray[i]->firstName, str) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * What does this method do?
 * @param clientArray what is the parameter?
 */
void sortLastName(struct client** clientArray) {
    int i, j;
    for(i = 0; i < count; i++) {
        for (j = 0; j < count; j++) {
            if (clientArray[i]->lastName > clientArray[j]->lastName) {
                struct client* tmp = clientArray[i];
                clientArray[i] = clientArray[j];
                clientArray[j] = tmp;
            }
        }
    }
}

/**
 * What does this method do?
 * @param clientArray what is the parameter?
 * @return what do we return?
 */
int findLastName(struct client** clientArray, char* str) {
    int i = 0;
    for(i = 0; i < count; i++) {
        if (strcmp(clientArray[i]->lastName, str) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * What does this method do?
 * @param clientArray what is the parameter?
 */
void sortPhone(struct client** clientArray){
    int i, j;
    for(i = 0; i < count; i++) {
        for (j = 0; j < count; j++) {
            if (clientArray[i]->phone > clientArray[j]->phone) {
                struct client* tmp = clientArray[i];
                clientArray[i] = clientArray[j];
                clientArray[j] = tmp;
            }
        }
    }
}


/**
 * What does this method do?
 * @param clientArray what is the parameter?
 * @return what do we return?
 */
int findPhone(struct client** clientArray, int ph) {
    int i = 0;
    for(i = 0; i < count; i++) {
        // OK to use primitive comparison here as only comparing numbers
        if(clientArray[i]->phone == ph)
            return 1;
    }
    return 0;
}

/**
 * What does this method do?
 * @param clientArray what is the parameter?
 */
void sortEmail(struct client** clientArray) {
    int i, j;
    for(i = 0; i < count; i++) {
        for (j = 0; j < count; j++) {
            if (clientArray[i]->emailAddress > clientArray[j]->emailAddress) {
                struct client* tmp = clientArray[i];
                clientArray[j] = clientArray[i];
                clientArray[j] = tmp;
            }
        }
    }
}

/**
 * What does this method do?
 * @param clientArray what is the parameter?
 * @return what do we return?
 */
int findEmail(struct client** clientArray, char* str) {
    int i = 0;
    for(i = 0; i < count; i++) {
        if (strcmp(clientArray[i]->emailAddress, str) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * Free all allocated memory used in the program.
 * @param clientArray the array of client structs to free.
 */
void free_all(struct client** clientArray) {
    int i;
    for(i = 0; i < count; i++) {
        free(clientArray[i]->firstName);
        free(clientArray[i]->lastName);
        free(clientArray[i]->emailAddress);
        free(clientArray[i]);
    }
    free(clientArray);
}

/**
 * Main method.
 * What does main do?
 * Reads in a file of client data, stores it and parses based on stdin input.
 * @param argc command line arguments
 * @param argv command line arguments
 * @return exit success of failure.
 */
int main(int argc, char ** argv) {
    count = 0;

    struct client** clientArray = (struct client**) malloc(100 * sizeof(struct client));

    FILE* f = fopen(argv[1], "r");

    if (f != NULL) {

        while (!feof(f)) {
            
            struct client* tmp = (struct client*) malloc(sizeof(struct client));
            
            tmp->firstName = (char *) malloc(80 * sizeof(char));
            tmp->lastName = (char *) malloc(80 * sizeof(char));
            tmp->emailAddress = (char *) malloc(80 * sizeof(char));
            
            fscanf(f, "%s %s %d %s", tmp->firstName, tmp->lastName, &tmp->phone, tmp->emailAddress);            
            
            clientArray[count] = tmp;
            
            count++;

        }
        fclose(f);

    } else {

        printf("Error, could not open file.\n");
        return EXIT_FAILURE;

    }

    int command = -1;
    printf("USAGE: 0=exit, 1=email, 2=firstname, 3=lastname, 4=phone.\n");

    // Keep asking the user for input until they enter 0
    while(command != 0) {
        int isFound = -1;
        char* val = (char *) malloc(80 * sizeof(char));
        
        printf("Enter the integer that corresponds to what you want to search for: ");
        scanf("%d", &command);
        
        if (command == 0) {
            printf("\nExiting program.. You pressed 0.\n");
            break;
        }

        printf("You entered: %d\n", command);
        printf("\nEnter the value to search for: ");
        scanf("%s", val);

        switch(command) {
            case 1:
                printf("Looking for email address: %s\n", val);
                //sortEmail(clientArray);
                isFound = findEmail(clientArray, val);
                //printf("Found: %d\n", isFound);
                break;
            case 2:
                printf("Looking for first name:  %s\n", val);
                //sortFirstName(clientArray);
                isFound = findFirstName(clientArray, val);
                //printf("Found: %d\n", isFound);
                break;
            case 3:
                printf("Looking for last name: %s\n", val);
                //sortLastName(clientArray);
                isFound = findLastName(clientArray, val);
                //printf("Found: %d\n", isFound);
                break;
            case 4:
                printf("Looking for phone number: %s\n", val);
                //sortPhone(clientArray);
                isFound =  findPhone(clientArray, atoi(val));
                //printf("Found: %d\n", isFound);
            default:
                break;
        }

        if (isFound == 1) {
            printf("SUCCESS. Found value: %s\n", val);
        } else {
            printf("FAILURE. Did not find:: %s\n", val);    
        }

        free(val);       
    }

    // free all remaining memory allocated
    free_all(clientArray);

    return EXIT_SUCCESS;

}