#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_DISEASE_LENGTH 100
#define FILE_NAME "patients.dat"

// Structure for patient details
typedef struct Patient {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    char disease[MAX_DISEASE_LENGTH];
    struct Patient* next;
} Patient;

Patient* head = NULL;

// Function prototypes
void addPatient();
void viewPatients();
void searchPatient();
void deletePatient();
void updatePatient();
void saveToFile();
void loadFromFile();
void menu();
Patient* createPatientNode();
int patientExists(int id);
void displayPatient(Patient* p);
void clearScreen();
void pressAnyKeyToContinue();
void admin();
void patientface();
void callforappointment();
void finddoctor();
void neurologist();
void Orthopedics();
void Cardiologist();
void Hepatologist();
void Gynocologist();
void Endocrinologist();

// Function to clear the screen (Platform dependent)
void clearScreen() {
    system("cls"); // For Windows
}

// Function to press any key to continue
void pressAnyKeyToContinue() {
    printf("\nPress any key to continue...");
    getchar();
    getchar();
}

// Function to display the admin menu
void admin() {
    int choice1;
    printf("\n--- Hospital Management System ---\n");
    printf("1. Add Patient\n");
    printf("2. View All Patients\n");
    printf("3. Search Patient by ID\n");
    printf("4. Delete Patient\n");
    printf("5. Update Patient Information\n");
    printf("6. Save and Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice1);

    switch (choice1) {
        case 1: addPatient(); break;
        case 2: viewPatients(); break;
        case 3: searchPatient(); break;
        case 4: deletePatient(); break;
        case 5: updatePatient(); break;
        case 6: saveToFile(); exit(0);
        default: printf("Invalid choice. Try again.\n");
    }
}

// Function to display the main menu
void menu() {
    int choice;
    do {
        clearScreen();
        printf("---- WELCOME TO OUR HOSPITAL SERVICE ----\n\n");
        printf("1. ADMIN\n");
        printf("2. PATIENT\n");
        printf("3. Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1: admin(); break;
            case 2: patientface(); break;
            case 3: exit(0);
            default: printf("INVALID\n");
        }
    } while (choice != 3);
}

// Function to add a new patient
void addPatient() {
    Patient* newPatient = createPatientNode();
    if (newPatient == NULL) {
        printf("Error: Unable to allocate memory for new patient.\n");
        pressAnyKeyToContinue();
        return;
    }

    printf("Enter Patient ID: ");
    scanf("%d", &newPatient->id);
    if (patientExists(newPatient->id)) {
        printf("Error: Patient with ID %d already exists.\n", newPatient->id);
        free(newPatient);
        pressAnyKeyToContinue();
        return;
    }

    printf("Enter Patient Name: ");
    getchar(); // to clear the newline from previous input
    fgets(newPatient->name, MAX_NAME_LENGTH, stdin);
    newPatient->name[strcspn(newPatient->name, "\n")] = '\0';  // Remove newline

    printf("Enter Patient Age: ");
    scanf("%d", &newPatient->age);

    printf("Enter Disease: ");
    getchar(); // to clear the newline from previous input
    fgets(newPatient->disease, MAX_DISEASE_LENGTH, stdin);
    newPatient->disease[strcspn(newPatient->disease, "\n")] = '\0';  // Remove newline

    newPatient->next = head;
    head = newPatient;

    printf("Patient added successfully.\n");
    pressAnyKeyToContinue();
}

// Function to view all patients
void viewPatients() {
    if (head == NULL) {
        printf("No patients available.\n");
        pressAnyKeyToContinue();
        return;
    }

    Patient* temp = head;
    printf("\n--- Patient List ---\n");
    while (temp != NULL) {
        displayPatient(temp);
        temp = temp->next;
    }

    pressAnyKeyToContinue();
}

// Function to search a patient by ID
void searchPatient() {
    int searchId;
    printf("Enter Patient ID to search: ");
    scanf("%d", &searchId);

    Patient* temp = head;
    while (temp != NULL) {
        if (temp->id == searchId) {
            printf("\n--- Patient Found ---\n");
            displayPatient(temp);
            pressAnyKeyToContinue();
            return;
        }
        temp = temp->next;
    }

    printf("Patient with ID %d not found.\n", searchId);
    pressAnyKeyToContinue();
}

// Function to delete a patient
void deletePatient() {
    int deleteId;
    printf("Enter Patient ID to delete: ");
    scanf("%d", &deleteId);

    Patient* temp = head;
    Patient* prev = NULL;

    while (temp != NULL && temp->id != deleteId) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Patient with ID %d not found.\n", deleteId);
        pressAnyKeyToContinue();
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Patient with ID %d has been deleted.\n", deleteId);
    pressAnyKeyToContinue();
}

// Function to update patient information
void updatePatient() {
    int updateId;
    printf("Enter Patient ID to update: ");
    scanf("%d", &updateId);

    Patient* temp = head;
    while (temp != NULL) {
        if (temp->id == updateId) {
            int choice;
            printf("1. Update Name\n");
            printf("2. Update Age\n");
            printf("3. Update Disease\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter new Name: ");
                    getchar();
                    fgets(temp->name, MAX_NAME_LENGTH, stdin);
                    temp->name[strcspn(temp->name, "\n")] = '\0';  // Remove newline
                    break;
                case 2:
                    printf("Enter new Age: ");
                    scanf("%d", &temp->age);
                    break;
                case 3:
                    printf("Enter new Disease: ");
                    getchar();
                    fgets(temp->disease, MAX_DISEASE_LENGTH, stdin);
                    temp->disease[strcspn(temp->disease, "\n")] = '\0';  // Remove newline
                    break;
                default:
                    printf("Invalid choice.\n");
                    return;
            }

            printf("Patient information updated successfully.\n");
            pressAnyKeyToContinue();
            return;
        }
        temp = temp->next;
    }

    printf("Patient with ID %d not found.\n", updateId);
    pressAnyKeyToContinue();
}

// Function to create a new patient node
Patient* createPatientNode() {
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    if (newPatient == NULL) {
        return NULL;
    }
    newPatient->next = NULL;
    return newPatient;
}

// Function to check if a patient exists by ID
int patientExists(int id) {
    Patient* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

// Function to display patient details
void displayPatient(Patient* p) {
    printf("\nID: %d\n", p->id);
    printf("Name: %s\n", p->name);
    printf("Age: %d\n", p->age);
    printf("Disease: %s\n", p->disease);
    printf("--------------------------\n");
}

// Function to load patients from file
void loadFromFile() {
    FILE* file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("No saved data found. Starting with an empty list.\n");
        return;
    }

    while (1) {
        Patient* newPatient = createPatientNode();
        if (fread(newPatient, sizeof(Patient), 1, file) != 1) {
            free(newPatient); // Free the allocated memory if read fails
            break; // Exit the loop if no more patients are found
        }
        newPatient->next = head;
        head = newPatient;
    }
    fclose(file);
}

// Function to save patients to file
void saveToFile() {
    FILE* file = fopen(FILE_NAME, "wb");
    if (file == NULL) {
        printf("Error saving data.\n");
        return;
    }

    Patient* temp = head;

    while (temp != NULL) {
        fwrite(temp, sizeof(Patient), 1, file);
        temp = temp->next;
    }

    fclose(file);
    printf("Data saved successfully.\n");
}

// Patient face menu
void patientface() {
    int choice2;
    do {
        clearScreen();
        printf("1. Appointment\n");
        printf("2. Find Doctor\n");
        printf("3. Back\n");
        scanf("%d", &choice2);
        switch (choice2) {
            case 1: callforappointment(); break;
            case 2: finddoctor(); break;
            case 3: return;
            default: printf("INVALID CHOICE\n");
        }
    } while (choice2 != 3);
}

// Function to call for appointment
void callforappointment() {
    printf("UTTARA\n096*\n096*\n\n");
    printf("BANANI\n096*\n096*\n\n");
    printf("GULSHAN\n096*\n096*\n\n");
    printf("MYMENSINGH\n096*\n096*\n\n");
    printf("BARISHAL\n096*\n096*\n\n");
    printf("KHULNA\n096*\n096*\n\n");
    printf("CHATTAGRAM\n096*\n096*\n\n");
    printf("MANIKGANJ\n096*\n096*\n\n");
    printf("RANGPUR\n096*\n096*\n\n");
    printf("DHANMONDI\n096*\n096*\n\n");
    printf("SYLHET\n096*\n096*\n\n");
}

// Function to find a doctor
void finddoctor() {
    int choice3;
    do {
        printf("1. Neurologist\n");
        printf("2. Orthopedics\n");
        printf("3. Cardiologist\n");
        printf("4. Hepatologist\n");
        printf("5. Gynocologist\n");
        printf("6. Endocrinologist\n");
        printf("7. Back\n");
        scanf("%d", &choice3);

        switch (choice3) {
            case 1: neurologist(); break;
            case 2: Orthopedics(); break;
            case 3: Cardiologist(); break;
            case 4: Hepatologist(); break;
            case 5: Gynocologist(); break;
            case 6: Endocrinologist(); break;
            case 7: return; break;
            default: printf("INVALID CHOICE\n");
        }
    } while (choice3 != 3);
}

// Functions for different doctors
void neurologist() {
    printf("1. DR. HASIBUR RAHMAN....2pm to 6pm\n");
    printf("2. DR. MAHIBUR RAHMAN....6pm to 9pm\n");
    printf("3. DR. ASIBUR RAHMAN....8pm to 10pm\n");
    printf("4. DR. BURHAN RAHMAN....8am to 12pm\n");
}

void Orthopedics() {
    printf("1. DR. ABID HASAN MILU....2pm to 6pm\n");
    printf("2. DR. RAISUL ISLAM....6pm to 9pm\n");
    printf("3. DR. OLIVE HASAN....8pm to 10pm\n");
    printf("4. DR. NIBIR SAFHUAN....8am to 12pm\n");
}

void Cardiologist() {
    printf("1. DR. FARHANA ANAM....2pm to 6pm\n");
    printf("2. DR. FERDOUS ARA....6pm to 9pm\n");
    printf("3. DR. AKM MUSA BHUIYAN BABLU....8pm to 10pm\n");
    printf("4. DR. MAHBUB H KHAN....8am to 12pm\n");
}

void Hepatologist() {
    printf("1. DR. AKM FAZLUL HAQUE....2pm to 6pm\n");
    printf("2. DR. PRAN GOPAL DATTA....6pm to 9pm\n");
    printf("3. DR. KRISNO GOPAL SAHA....8pm to 10pm\n");
    printf("4. DR. NAIM HASAN....8am to 12pm\n");
}

void Gynocologist() {
    printf("1. DR. FARHAN SADIK....2pm to 6pm\n");
    printf("2. DR. BITHI AKTHER....6pm to 9pm\n");
    printf("3. DR. AFROJA ISLAM....8pm to 10pm\n");
    printf("4. DR. PROLOY SARKAR....8am to 12pm\n");
}

void Endocrinologist() {
    printf("1. DR. MOBIN KHAN....2pm to 6pm\n");
    printf("2. DR. AKASH CHANDRA PAUL....6pm to 9pm\n");
    printf("3. DR. DIP CHOWDHURY....8pm to 10pm\n");
    printf("4. DR. PRANTO KUMAR....8am to 12pm\n");
}

// Main function
int main() {
    loadFromFile(); // Load patient data from file on startup
    menu(); // Display main menu
    return 0;
}
