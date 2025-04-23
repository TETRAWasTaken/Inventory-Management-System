//
// Created by Anshumaan soni on 4/17/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Environment Variable
#define MAX_SHELVES 5
#define MAX_ROWS 12
#define MAX_COLUMNS 12
#define MAX_ENTRY 10
char COLUMN[] = {'A','B','C','D','E','F','G','H','I','J','K','L'};
int ROW[] = {1,2,3,4,5,6,7,8,9,10,11,12};
int SHELFS[] = {1,2,3,4,5};

// Structure Definitions
typedef struct {
    char COL;
    int ROW;
    int SHELF;
}location;

typedef struct {
    int ID;
    char name[100];
    int amount;
    location *location;
}Item;

typedef union {
    Item* item;
    int bool;
}Data;

Data dataarray[MAX_ENTRY];


// Structure Initiators
Item* Initiator(int ID, char *name, int amount, location *location) {
    Item* item = (Item*)malloc(sizeof(Item));
    if (item == NULL) {
        perror("Error allocating memory for item");
        exit(EXIT_FAILURE);
    }

    item->ID = ID;
    strcpy(item->name, name);
    item->amount = amount;
    item->location = location;
    return item;
}

location* allocator(char col, int row, int shelf) {
    location* loca = (location*)malloc(sizeof(location));
    if (loca == NULL) {
        perror("Error allocating memory for item");
        exit(EXIT_FAILURE);
    }
    loca->COL = col;
    loca->ROW = row;
    loca->SHELF = shelf;
    return loca;
}

void datainitiator() {
    for (int i = 0; i < MAX_ENTRY; i++) {
        dataarray[i].bool = 1;
    }
}

// Location Displayer
void displayLocationMatrix(location *location) {
    printf("\n--- Shelf %d ---\n", location->SHELF);
    printf("   ");
    for (char col = 'A'; col <= 'L'; col++) {
        printf("%c  ", col);
    }
    printf("\n");
    for (int i = 1; i <= MAX_ROWS; i++) {
        printf("%2d  ", i);
        for (char col = 'A'; col <= 'L'; col++) {
            if (col == location->COL && i == location->ROW) {
                printf("X  ");
            } else {
                printf(".  ");
            }
        }
        printf("\n");
    }
    printf("Legend: '.' = Empty, 'X' = Item Location\n");
    printf("\n\n");
}

void locator() {
    int ID;
    printf("Enter ID: ");
    scanf("%d", &ID);

    for (int i = 0; i < MAX_ENTRY; i++) {
        if (dataarray[i].bool == 1) {
            continue;
        }
        else {
            if (dataarray[i].item->ID == ID) {
                displayLocationMatrix(dataarray[i].item->location);
            }
            else {
                printf("Invalid ID.\n");
            }
        }
    }
    printf("\n\n");
}

// Item Display
void listdisplay() {

    printf("%-10s%-30s%-10s%-10s%-10s%-10s\n","ID", "Name", "Amount", "Columns", "Rows", "Shelf");
    printf("-------------------------------------------------------------------------------\n");
    for (int i = 0; i < MAX_ENTRY; i++) {
        if (dataarray[i].bool == 1) {
            continue;
        }
        else {
            printf("%-10d%-30s%-10d%-10c%-10d%-10d", dataarray[i].item->ID, dataarray[i].item->name,
                   dataarray[i].item->amount, dataarray[i].item->location->COL,
                   dataarray[i].item->location->ROW, dataarray[i].item->location->SHELF);
            printf("\n");
        }
    }
    printf("\n\n");
}

// Item Data Input
void Instance(int N) {
    int ID ;
    char name[30];
    int amount;
    char col; // Stays as char
    int row;
    int shelf;
    int conflict_found = 0;

    printf("Enter ID : ");
    scanf("%d", &ID);
    getchar();

    printf("Enter name : ");
    fgets(name, 30, stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter amount : ");
    scanf("%d", &amount);
    getchar();

    printf("Enter location COL (single character A-L): ");
    scanf(" %c", &col);
    getchar();

    printf("Enter location ROW (1-12): ");
    scanf("%d", &row);
    getchar();

    printf("Enter location SHELF (1-5): ");
    scanf("%d", &shelf);
    getchar();

    for (int j = 0; j < MAX_ENTRY; j++) {
        if (N == j || dataarray[j].bool == 1) {
            continue;
        }

        if (dataarray[j].item->location->COL == col &&
            dataarray[j].item->location->ROW == row &&
            dataarray[j].item->location->SHELF == shelf) {
            printf("\nError: Invalid Location. Item '%s' (ID: %d) already occupies %c%d on shelf %d.\n",
                   dataarray[j].item->name, dataarray[j].item->ID, col, row, shelf);
            printf("Please try again with a different location.\n");
            conflict_found = 1;
            break;
            }
    }

    if (!conflict_found) {
        location* location = allocator(col, row, shelf);
        Item* item = Initiator(ID, &name, amount, location);

        Data data;
        data.item = item;
        dataarray[N] = data;
        printf("\n\n");
        listdisplay();

        printf("Item Added Succesfully\n");
    }
    printf("\n\n");
}

// Update Item

void updateamm(int i) {
    int newamm;
    printf("Enter new amm : ");
    scanf("%d", &newamm);
    dataarray[i].item->amount = newamm;
    printf("\nChanged ammount to %d\n", dataarray[i].item->amount);
    printf("\n\n");
}

void updatelocation(int i) {
    location* old_location = dataarray[i].item->location;
    char new_col;
    int new_row;
    int new_shelf;
    int conflict_found = 0;

    getchar();
    printf("Enter new location COL (A-L): ");
    scanf(" %c", &new_col);
    printf("Enter new location ROW (1-12): ");
    scanf("%d", &new_row);
    printf("Enter new location SHELF (1-5): ");
    scanf("%d", &new_shelf);
    getchar();

    for (int j = 0; j < MAX_ENTRY; j++) {
        if (i == j || dataarray[j].bool == 1) {
            continue;
        }

        if (dataarray[j].item->location->COL == new_col &&
            dataarray[j].item->location->ROW == new_row &&
            dataarray[j].item->location->SHELF == new_shelf) {
            printf("\nError: Invalid Location. Item '%s' (ID: %d) already occupies %c%d on shelf %d.\n",
                   dataarray[j].item->name, dataarray[j].item->ID, new_col, new_row, new_shelf);
            printf("Please try again with a different location.\n");
            conflict_found = 1;
            break;
        }
    }

    if (!conflict_found) {
        location* new_location = allocator(new_col, new_row, new_shelf);
        dataarray[i].item->location = new_location;
        free(old_location);

        printf("\nLocation changed successfully to %c%d on shelf %d.\n", new_col, new_row, new_shelf);
    }
    printf("\n\n");
}

void deleteitem(int i) {
    dataarray[i].bool = 1;
    printf("Deleted Succesfully\n");
    printf("\n\n");
}

void updateitem() {
    int id;
    int func;
    printf("Enter ID : ");
    scanf("%d", &id);

    for (int i = 0; i < MAX_ENTRY; i++) {
        if (dataarray[i].bool == 1) {
            continue;
        }
        if (dataarray[i].item->ID == id) {
            printf("What needs to be changed ? \n");
            printf("1. Amount\n");
            printf("2. Location\n");
            printf("3. Delete Item\n");

            scanf("%d", &func);

            switch (func) {
                case 1:
                    updateamm(i);
                    break;
                case 2:
                    updatelocation(i);
                    break;
                case 3:
                    deleteitem(i);
                    break;
                default:
                    printf("Invalid Selection.\n");
            }
        }
        else {
            printf("Invalid ID.\n");
        }
    }
    printf("\n\n");
}

// Program Initiator
void main() {
    int func;
    int N=0;

    // Welcome message
    printf("Welcome to the Inventory Management System!\n");
    printf("--------------------------------------------\n");
    printf("Maximum shelves available: %d\n", MAX_SHELVES);
    printf("Maximum rows per shelf: %d\n", MAX_ROWS);
    printf("Maximum columns per row: %d\n", MAX_COLUMNS);
    printf("Maximum item entries allowed: %d\n", MAX_ENTRY);
    printf("--------------------------------------------\n\n");

    datainitiator();

    for (int i = 0; i < 10; i++) {
        printf("What would you like to do : \n");
        printf("1. Enter Item Data \n");
        printf("2. Locate an Item \n");
        printf("3. Check Items list \n");
        printf("4. Update Items list \n");

        scanf("%d",&func);
        printf("\n\n");


        switch (func) {
            case 1:
                Instance(N);
                N++;
                break;
            case 2:
                locator();
                break;
            case 3:
                listdisplay();
                break;
            case 4:
                updateitem();
                break;
            default:
                printf("Invalid input.\n");
        }
    }
}