#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_FLIGHTS 100
#define MAX_STRING 50

// Arrays to store flight details
int flight_ids[MAX_FLIGHTS];
char flight_carriers[MAX_FLIGHTS][50];
char flight_numbers[MAX_FLIGHTS][10];
char flight_origins[MAX_FLIGHTS][50];
char flight_destinations[MAX_FLIGHTS][50];
int flight_distances[MAX_FLIGHTS];
char flight_departures[MAX_FLIGHTS][20];
char flight_names[MAX_FLIGHTS][50];
int flight_count = 0; // Counter for the number of flights

// Function prototypes
void displayMenu();
void viewFlights();
void addFlight();
void editFlight();
void deleteFlight();
void viewDetails();
void loadFlightsFromCSV();
int is_valid_time_format(char* time);
void clearInputBuffer();
int getValidInt(const char *prompt, int min, int max);
void getValidString(const char *prompt, char *buffer, size_t size);

int main() {
    int choice = -1; // Initialize choice to an invalid value
    loadFlightsFromCSV(); // Load flights from the CSV file at the start
    while (choice != 0) {
        displayMenu();
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        getchar(); // Consume the newline character
        switch (choice) {
            case 1: viewFlights(); break;
            case 2: addFlight(); break;
            case 3: editFlight(); break;
            case 4: deleteFlight(); break;
            case 5: viewDetails(); break;
            case 0: printf("\nExiting the system. Goodbye!\n"); break;
            default: printf("\nInvalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Function to display the main menu
void displayMenu() {
    printf("\nFlight Management System\n");
    printf("1. View Flights\n"); // Option to view all flights
    printf("2. Add Flight\n"); // Option to add a new flight
    printf("3. Edit Flight\n"); // Option to edit an existing flight
    printf("4. Delete Flight\n"); // Option to delete a flight
    printf("5. View Flight Details\n");
    printf("0. Exit\n"); // Option to exit the program
}

// Function to view all flights
void viewFlights() {
    if (flight_count == 0) {
        printf("\nNo flights available.\n"); // Inform user if no flights are available
        return;
    }

    printf("\nList of Flights:\n");
    printf("%-5s %-10s %-10s %-14s %-10s\n", "ID", "Number", "Origin", "Destination", "Departure");
    for (int i = 0; i < 60; i++) {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < flight_count; i++) {
        // Display flight details
        printf("%-5d %-10s %-10s %-14s %-10s\n",
               flight_ids[i], flight_numbers[i], flight_origins[i],
               flight_destinations[i], flight_departures[i]);
    }
}

// Function to add a new flight
void addFlight() {
    if (flight_count >= MAX_FLIGHTS) {
        printf("\nFlight list is full. Cannot add more flights.\n");
        return;
    }
    getValidString("\nEnter carrier: ", flight_carriers[flight_count], 50);
    getValidString("\nEnter flight number: ", flight_numbers[flight_count], 10);
    getValidString("\nEnter origin: ", flight_origins[flight_count], 50);
    getValidString("\nEnter destination: ", flight_destinations[flight_count], 50);
    do {
        printf("\nEnter distance: ");
        while (scanf("%d", &flight_distances[flight_count]) != 1 || flight_distances[flight_count] <= 0) {
            printf("Invalid input. Enter a valid distance greater than zero: ");
            while (getchar() != '\n'); // Clear the input buffer
        }
        getchar(); // Consume the newline character left in the buffer
    } while (flight_distances[flight_count] <= 0);
    do {
        getValidString("\nEnter departure time (hh:mm): ", flight_departures[flight_count], 20);
        if (!is_valid_time_format(flight_departures[flight_count])) {
            printf("Invalid format. Please enter time in hh:mm format with valid values for hours and minutes.\n");
        }
    } while (!is_valid_time_format(flight_departures[flight_count]));
    getValidString("\nEnter flight name: ", flight_names[flight_count], 50);

    flight_ids[flight_count] = flight_count + 1;
    flight_count++;
    printf("\nFlight added successfully.\n");
}

void editFlight() {
    if (flight_count <= 0) {
        printf("No flights available to edit.\n");
        return;
    }

    int id = getValidInt("Enter flight ID to edit: ", 1, flight_count);
    int index = id - 1;

    printf("\nWhat do you want to edit?\n");
    printf("1. Carrier\n");
    printf("2. Flight Number\n");
    printf("3. Origin\n");
    printf("4. Destination\n");
    printf("5. Distance\n");
    printf("6. Departure Time\n");
    printf("7. Flight Name\n");
    printf("8. All\n");
    printf("0. Exit\n");

    int choice = getValidInt("\nEnter your choice: ", 0, 8);

    switch (choice) {
        case 1:
            getValidString("\nEnter new carrier: ", flight_carriers[index], MAX_STRING);
            break;
        case 2:
            getValidString("\nEnter new flight number: ", flight_numbers[index], 10);
            break;
        case 3:
            getValidString("\nEnter new origin: ", flight_origins[index], MAX_STRING);
            break;
        case 4:
            getValidString("\nEnter new destination: ", flight_destinations[index], MAX_STRING);
            break;
        case 5:
            flight_distances[index] = getValidInt("\nEnter new distance: ", 1, 100000);
            break;
        case 6:
            do {
                getValidString("\nEnter new departure time (hh:mm): ", flight_departures[index], 20);
                if (!is_valid_time_format(flight_departures[index])) {
                    printf("Invalid format. Please enter time in hh:mm format.\n");
                }
            } while (!is_valid_time_format(flight_departures[index]));
            break;
        case 7:
            getValidString("\nEnter new flight name: ", flight_names[index], MAX_STRING);
            break;
        case 8:
            getValidString("\nEnter new carrier: ", flight_carriers[index], MAX_STRING);
            getValidString("\nEnter new flight number: ", flight_numbers[index], 10);
            getValidString("\nEnter new origin: ", flight_origins[index], MAX_STRING);
            getValidString("\nEnter new destination: ", flight_destinations[index], MAX_STRING);
            flight_distances[index] = getValidInt("\nEnter new distance: ", 1, 100000);
            do {
                getValidString("\nEnter new departure time (hh:mm): ", flight_departures[index], 20);
                if (!is_valid_time_format(flight_departures[index])) {
                    printf("Invalid format. Please enter time in hh:mm format.\n");
                }
            } while (!is_valid_time_format(flight_departures[index]));
            getValidString("\nEnter new flight name: ", flight_names[index], MAX_STRING);
            break;
        case 0:
            return;
        default:
            printf("\nInvalid choice.\n");
            break;
    }

    printf("\nFlight updated successfully.\n");
}

// Function to delete a flight
void deleteFlight() {
    int id;
    printf("\nEnter flight ID to delete: ");
    scanf("%d", &id);
    getchar(); // Consume newline character

    if (id <= 0 || id > flight_count) {
        printf("Invalid flight ID.\n"); // Handle invalid ID
        return;
    }

    int index = id - 1; // Find the index of the flight

    // Shift all flights after the deleted one
    for (int i = index; i < flight_count - 1; i++) {
        strcpy(flight_carriers[i], flight_carriers[i + 1]);
        strcpy(flight_numbers[i], flight_numbers[i + 1]);
        strcpy(flight_origins[i], flight_origins[i + 1]);
        strcpy(flight_destinations[i], flight_destinations[i + 1]);
        flight_distances[i] = flight_distances[i + 1];
        strcpy(flight_departures[i], flight_departures[i + 1]);
        strcpy(flight_names[i], flight_names[i + 1]);
    }

    flight_count--; // Decrement the flight count
    printf("Flight deleted successfully.\n");
}

void viewDetails() {
    printf("Enter flight ID to view details: ");
    int id;
    scanf("%d", &id);
    getchar(); // Consume newline character

    if (id <= 0 || id > flight_count) {
        printf("\nInvalid flight ID.\n"); // Handle invalid ID
        return;
    }

    int index = id - 1; // Find the index of the flight
    printf("\nFlight %d Details:\n", id);
    for (int i = 0; i < 60; i++) {
        printf("-");
    }
    printf("\n%-15s:   %-15s\n", "Carrier", flight_carriers[index]);
    printf("%-15s:   %-15s\n", "Flight Number", flight_numbers[index]);
    printf("%-15s:   %-15s\n", "Origin", flight_origins[index]);
    printf("%-15s:   %-15s\n", "Destination", flight_destinations[index]);
    printf("%-15s:   %-15d\n", "Distance", flight_distances[index]);
    printf("%-15s:   %-15s\n", "Departure Time", flight_departures[index]);
    printf("%-15s:   %-15s\n", "Flight Name", flight_names[index]);
}
    
void loadFlightsFromCSV() {
    FILE *file = fopen("flight.csv", "r");
    if (!file) {
        printf("\nCould not open/find CSV file.\n");
        return;
    }

    char line[256];
    // Skip header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        if (flight_count >= MAX_FLIGHTS) {
            printf("\nMaximum flight capacity reached.\n");
            break;
        }

        int id, distance, hour, minute;
        char carrier[50], number[10], origin[50], dest[50], name[50], departure[20];

        // Parse line with all fields
        if (sscanf(line, "%d,%49[^,],%9[^,],%49[^,],%49[^,],%d,%d,%d,%49[^\n]",
                   &id, carrier, number, origin, dest, &distance, &hour, &minute, name) == 9) {
            snprintf(departure, sizeof(departure), "%02d:%02d", hour, minute);

            // Store data in arrays
            flight_ids[flight_count] = id;
            strcpy(flight_carriers[flight_count], carrier);
            strcpy(flight_numbers[flight_count], number);
            strcpy(flight_origins[flight_count], origin);
            strcpy(flight_destinations[flight_count], dest);
            flight_distances[flight_count] = distance;
            strcpy(flight_departures[flight_count], departure);
            strcpy(flight_names[flight_count], name);
            flight_count++;
        } else {
            printf("Invalid line format, skipping: %s", line);
        }
    }
    fclose(file);
    printf("\nSucessfully loaded %d flights from CSV file.\n", flight_count);
}

int is_valid_time_format(char* time) {
    if (strlen(time) != 5) return 0; // Length should be 5 (hh:mm)
    // Check the first two characters for digits
    for (int i = 0; i < 2; i++) {
        if (!isdigit(time[i])) return 0;
    }
    // Check the colon separator
    if (time[2] != ':') return 0;
    // Check the last two characters for digits
    for (int i = 3; i < 5; i++) {
        if (!isdigit(time[i])) return 0;
    }
    // Convert the hour and minute parts to integers and check their ranges
    int hour = atoi(time);
    int minute = atoi(&time[3]);
    if (hour < 0 || hour > 24) return 0;
    if (minute < 0 || minute > 59) return 0;
    if (hour == 24 && minute != 0) return 0;
    return 1;
}

void clearInputBuffer() {
    while (getchar() != '\n');
}

// Helper function to get a valid integer input
int getValidInt(const char *prompt, int min, int max) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1 && value >= min && value <= max) {
            clearInputBuffer();
            return value;
        }
        printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
        clearInputBuffer();
    }
}

// Helper function to get a valid string input
void getValidString(const char *prompt, char *buffer, size_t size) {
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, size, stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline
            if (strlen(buffer) > 0) { // Check if input is not empty
                break; // Valid input
            } else {
                printf("Input cannot be empty. Please try again.\n");
            }
        } else {
            printf("Error reading input. Please try again.\n");
            clearInputBuffer(); // Clear buffer to avoid infinite loop
        }
    }
}