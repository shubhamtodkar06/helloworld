#include <stdio.h>
#include <string.h>

#define MAX_RECORDS 100

typedef struct {
    int id;
    char name[50];
    int age;
    float salary;
} Record;

Record records[MAX_RECORDS];
int numRecords = 0;

void createRecord() {
    if (numRecords >= MAX_RECORDS) {
        printf("Database is full.\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &records[numRecords].id);

    printf("Enter Name: ");
    scanf(" %[^\n]s", records[numRecords].name);

    printf("Enter Age: ");
    scanf("%d", &records[numRecords].age);

    printf("Enter Salary: ");
    scanf("%f", &records[numRecords].salary);

    numRecords++;
    printf("Record created successfully.\n");
}

void modifyRecord(int id) {
    int i;
    for (i = 0; i < numRecords; i++) {
        if (records[i].id == id) {
            printf("Enter new Name: ");
            scanf(" %[^\n]s", records[i].name);

            printf("Enter new Age: ");
            scanf("%d", &records[i].age);

            printf("Enter new Salary: ");
            scanf("%f", &records[i].salary);

            printf("Record modified successfully.\n");
            return;
        }
    }
    printf("Record with ID %d not found.\n", id);
}

void appendRecord() {
    if (numRecords >= MAX_RECORDS) {
        printf("Database is full.\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &records[numRecords].id);

    printf("Enter Name: ");
    scanf(" %[^\n]s", records[numRecords].name);  

    printf("Enter Age: ");
    scanf("%d", &records[numRecords].age);

    printf("Enter Salary: ");
    scanf("%f", &records[numRecords].salary);

    numRecords++;
    printf("Record appended successfully.\n");
}

void searchRecord(int id) {
    int i;
    for (i = 0; i < numRecords; i++) {
        if (records[i].id == id) {
            printf("ID: %d\n", records[i].id);
            printf("Name: %s\n", records[i].name);
            printf("Age: %d\n", records[i].age);
            printf("Salary: %.2f\n", records[i].salary);
            return;
        }
    }
    printf("Record with ID %d not found.\n", id);
}

void sortRecords(int field) {
    int i, j;
    Record temp;

    switch (field) {
        case 1:  // Sort by ID
            for (i = 0; i < numRecords - 1; i++) {
                for (j = i + 1; j < numRecords; j++) {
                    if (records[i].id > records[j].id) {
                        temp = records[i];
                        records[i] = records[j];
                        records[j] = temp;
                    }
                }
            }
            break;

        case 2:  // Sort by Name
            for (i = 0; i < numRecords - 1; i++) {
                for (j = i + 1; j < numRecords; j++) {
                    if (strcmp(records[i].name, records[j].name) > 0) {
                        temp = records[i];
                        records[i] = records[j];
                        records[j] = temp;
                    }
                }
            }
            break;

        case 3:  // Sort by Age
            for (i = 0; i < numRecords - 1; i++) {
                for (j = i + 1; j < numRecords; j++) {
                    if (records[i].age > records[j].age) {
                        temp = records[i];
                        records[i] = records[j];
                        records[j] = temp;
                    }
                }
            }
            break;

        case 4:  // Sort by Salary
            for (i = 0; i < numRecords - 1; i++) {
                for (j = i + 1; j < numRecords; j++) {
                    if (records[i].salary > records[j].salary) {
                        temp = records[i];
                        records[i] = records[j];
                        records[j] = temp;
                    }
                }
            }
            break;

        default:
            printf("Invalid field for sorting.\n");
            return;
    }

    printf("Records sorted successfully.\n");
}

int main() {
    int choice, id, field;

    while (1) {
        printf("\nDatabase Management System\n");
        printf("1. Create Record\n");
        printf("2. Modify Record\n");
        printf("3. Append Record\n");
        printf("4. Search Record\n");
        printf("5. Sort Records\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {  // Check if input is valid
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');  // Clear invalid input
            continue;
        }

        switch (choice) {
            case 1:
                createRecord();
                break;

            case 2:
                printf("Enter ID to modify: ");
                scanf("%d", &id);
                modifyRecord(id);
                break;

            case 3:
                appendRecord();
                break;

            case 4:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                searchRecord(id);
                break;

            case 5:
                printf("Sort by:\n");
                printf("1. ID\n");
                printf("2. Name\n");
                printf("3. Age\n");
                printf("4. Salary\n");
                printf("Enter your choice: ");
                scanf("%d", &field);
                sortRecords(field);
                break;

            case 6:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}
