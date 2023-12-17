#include <stdio.h>
#include <stdlib.h>

struct Movie {
    char title[50];
    int availableSeats;
    float ticketPrice;
};

struct Theatre {
    char name[50];
    char location[50];
};

struct CanteenItem {
    char itemName[50];
    float price;
};

int isEqual(char str1[], char str2[]) {
    int i = 0;
    while (str1[i] != '\0' || str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 0;  
        }
        i++;
    }
    return 1;  
}

void displayTheatresInLocation(struct Theatre theatres[], int numTheatres, char location[]) {
    printf("\nAvailable Theatres in %s:\n", location);
    for (int i = 0; i < numTheatres; i++) {
        if (isEqual(theatres[i].location, location)) {
            printf("%d. %s\n", i + 1, theatres[i].name);
        }
    }
}

void displayMovies(struct Movie movies[], int numMovies, int theatreIndex) {
    printf("\nAvailable Movies at %s:\n", movies[theatreIndex].title);
    for (int i = 0; i < numMovies; i++) {
        printf("%d. %s (Seats: %d, Price: %.2f)\n", i + 1, movies[i].title, movies[i].availableSeats, movies[i].ticketPrice);
    }
}

void displayCanteenMenu(struct CanteenItem canteenMenu[], int numItems) {
    printf("\nCanteen Menu:\n");
    for (int i = 0; i < numItems; i++) {
        printf("%d. %s (Price: %.2f)\n", i + 1, canteenMenu[i].itemName, canteenMenu[i].price);
    }
}

void bookTickets(struct Movie *selectedMovie) {
    int numTickets;
    printf("\nEnter the number of tickets to book: ");
    scanf("%d", &numTickets);

    if (numTickets > 0 && numTickets <= selectedMovie->availableSeats) {
        printf("Total cost: %.2f\n", numTickets * selectedMovie->ticketPrice);
        selectedMovie->availableSeats -= numTickets;
        printf("Tickets booked successfully!\n");
    } else {
        printf("Invalid number of tickets or not enough seats available.\n");
    }
}

void orderFood(struct Movie *selectedMovie, struct CanteenItem canteenMenu[], int numItems) {
    int choices[50];  
    int quantities[50]; 
    int totalItems = 0;
    float totalPrice = 0.0;

    printf("\nEnter the item numbers and quantities to order (0 to finish): ");

    int choice;
    while (totalItems < 50) {
        scanf("%d", &choice);

        if (choice == 0) {
            break;  
        }

        if (choice > 0 && choice <= numItems) {
            printf("Enter the quantity for %s: ", canteenMenu[choice - 1].itemName);
            int quantity;
            scanf("%d", &quantity);

            if (quantity > 0) {
                choices[totalItems] = choice;
                quantities[totalItems] = quantity;
                totalItems++;
            } else {
                printf("Invalid quantity. Try again.\n");
            }
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    
    printf("\nItems ordered for %s:\n", selectedMovie->title);
    for (int i = 0; i < totalItems; i++) {
        printf("%d. %s (Quantity: %d)\n", i + 1, canteenMenu[choices[i] - 1].itemName, quantities[i]);
        totalPrice += canteenMenu[choices[i] - 1].price * quantities[i];
    }

    printf("\nTotal cost: %.2f\n", totalPrice);
    printf("Food ordered successfully!\n");
}

int main() {
    struct Theatre theatres[] = {
        {"Mega Star Cinemas", "Trichy"},
        {"L.A.Cinemas", "Trichy"},
        {"CityPlex", "Chennai"},
    
    };

    struct Movie movies[][9] = {
        {
            {"Leo", 300, 190.0},
            {"Salaar", 250, 220.5},
            {"K.G.F 2", 300, 250.0},
            {"Parking", 100, 170.0},
            {"Fast  X", 180, 200.0},
            {"Avengers Endgame", 300, 200.0},
            {"Avatar", 250, 220.0},
            {"animal", 200, 190.0},
            {"jailer", 200, 220.0},
        },
        
    };

    struct CanteenItem canteenMenu[] = {
        {"Popcorn", 40.0},
        {"big popcorn", 150.0},
        {"small popcorn", 90.0},
        {"Coco cola", 30.0},
        {"Burger", 70.0},
        {"Egg puffs", 40.0},
        {"Ice cream", 80.0},
        {"Finger chips", 50.0},
        {"panni puri", 50.0},
        {"pael puri", 50.0},
        {"masal puri", 50.0},
        {"coffe", 60.0},
        {"cold coffe", 100.0},
        {"chocolate coffe", 150.0},
        {"donut", 70.0},
        {"tea", 50.0},
        {"juice", 60.0},
        {"water bottle", 30.0},
        {"cool drinkes", 60.0}
    };

    int numTheatres = sizeof(theatres) / sizeof(theatres[0]);
    int numItems = sizeof(canteenMenu) / sizeof(canteenMenu[0]);

    char location[50];
    int theatreChoice, movieChoice;

    printf("Welcome to the Movie Ticket Booking System!\n");

    printf("Enter your location: ");
    scanf("%s", location);

    do {
        displayTheatresInLocation(theatres, numTheatres, location);

        printf("\nEnter the theatre number to view movies (0 to exit): ");
        scanf("%d", &theatreChoice);

        if (theatreChoice > 0 && theatreChoice <= numTheatres) {
            int selectedTheatreIndex = theatreChoice - 1;
            struct Movie *selectedMovies = movies[selectedTheatreIndex];

            do {
                displayMovies(selectedMovies, 9, selectedTheatreIndex);

                printf("\nEnter the movie number to book tickets (0 to go back): ");
                scanf("%d", &movieChoice);

                if (movieChoice > 0 && movieChoice <= 9) {
                    struct Movie *selectedMovie = &selectedMovies[movieChoice - 1];
                    displayCanteenMenu(canteenMenu, numItems);

                    int option;
                    printf("\nSelect an option:\n1. Book Tickets\n2. Order Food\n3. Exit\n");
                    scanf("%d", &option);

                    switch (option) {
                        case 1:
                            bookTickets(selectedMovie);
                            break;
                        case 2:
                            orderFood(selectedMovie, canteenMenu, numItems);
                            break;
                        case 3:
                            printf("Exiting...\n");
                            break;
                        default:
                            printf("Invalid option.\n");
                    }
                } else if (movieChoice != 0) {
                    printf("Invalid movie choice.\n");
                }

            } while (movieChoice != 0);
        } else if (theatreChoice != 0) {
            printf("Invalid theatre choice.\n");
        }

    } while (theatreChoice != 0);

    return 0;
}
