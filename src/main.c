
#include <stdio.h>
#include <sys/stat.h>
#include <pigpio.h>

#define LED_PIN 17

int main(void) {
    int capacity = 5;
    int count = 0;
    int choice;
    FILE *file;

    if (gpioInitialise() < 0) {
        printf("GPIO initialization failed.\n");
        return 1;
    }

    gpioSetMode(LED_PIN, PI_OUTPUT);
    gpioWrite(LED_PIN, 0);

    mkdir("data", 0775);

    file = fopen("data/occupancy_log.csv", "a");

    if (file == NULL) {
        printf("Error opening log file.\n");
        gpioTerminate();
        return 1;
    }

    while (1) {
        printf("\n--- STUDY ROOM TRACKER ---\n");
        printf("Occupancy: %d/%d\n", count, capacity);

        if (count == capacity) {
            printf("Status: ROOM FULL\n");
            gpioWrite(LED_PIN, 1);
        } else {
            printf("Status: SPACE AVAILABLE\n");
            gpioWrite(LED_PIN, 0);
        }

        printf("\n1. Student enters");
        printf("\n2. Student exits");
        printf("\n3. Change room capacity");
        printf("\n4. Exit program");
        printf("\nChoose an option: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 1) {
            if (count < capacity) {
                count++;
                printf("Student entered.\n");
                fprintf(file, "ENTER,%d,%d\n",
                        count, capacity);
                fflush(file);
            } else {
                printf("WARNING: Room full! Entry denied.\n");
            }
        }
        else if (choice == 2) {
            if (count > 0) {
                count--;
                printf("Student exited.\n");
                fprintf(file, "EXIT,%d,%d\n",
                        count, capacity);
                fflush(file);
            } else {
                printf("Room empty! Exit denied.\n");
            }
        }
        else if (choice == 3) {
            int newCapacity;
            printf("Enter new capacity: ");

            if (scanf("%d", &newCapacity) != 1) {
                printf("Invalid input.\n");
                while (getchar() != '\n');
                continue;
            }

            if (newCapacity >= 1 &&
                newCapacity >= count) {
                capacity = newCapacity;
                printf("Capacity updated.\n");
                fprintf(file, "CAPACITY,%d,%d\n",
                        count, capacity);
                fflush(file);
            } else {
                printf("Invalid capacity.\n");
            }
        }
        else if (choice == 4) {
            printf("Goodbye!\n");
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
    }

    gpioWrite(LED_PIN, 0);
    fclose(file);
    gpioTerminate();

    return 0;
}
