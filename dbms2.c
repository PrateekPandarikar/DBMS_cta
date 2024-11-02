#include <stdio.h>

#define MAX_SIZE 100 // Maximum size of the array

// Function declarations
void insert(int arr[], int *size, int element, int position);
void delete(int arr[], int *size, int position);
int search(int arr[], int size, int element);
void update(int arr[], int position, int new_element);
void display(int arr[], int size);

int main() {
    int arr[MAX_SIZE], size = 0, choice, element, position, search_result, new_element;

    printf("Enter initial size of array (max %d): ", MAX_SIZE);
    scanf("%d", &size);

    if (size > MAX_SIZE) {
        printf("Error: Size exceeds the maximum limit!\n");
        return 1;
    }

    // Taking initial array input
    printf("Enter %d elements: \n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    while (1) {
        printf("\n--- Array Operations Menu ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Update\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Insert element
                printf("Enter element to insert: ");
                scanf("%d", &element);
                printf("Enter position (1 to %d): ", size + 1);
                scanf("%d", &position);
                insert(arr, &size, element, position);
                break;

            case 2: // Delete element
                printf("Enter position (1 to %d) to delete: ", size);
                scanf("%d", &position);
                delete(arr, &size, position);
                break;

            case 3: // Search element
                printf("Enter element to search: ");
                scanf("%d", &element);
                search_result = search(arr, size, element);
                if (search_result == -1) {
                    printf("Element not found!\n");
                } else {
                    printf("Element found at position: %d\n", search_result + 1);
                }
                break;

            case 4: // Update element
                printf("Enter position (1 to %d) to update: ", size);
                scanf("%d", &position);
                printf("Enter new element: ");
                scanf("%d", &new_element);
                update(arr, position - 1, new_element);
                break;

            case 5: // Display array
                display(arr, size);
                break;

            case 6: // Exit
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function to insert an element at a specified position
void insert(int arr[], int *size, int element, int position) {
    if (*size >= MAX_SIZE) {
        printf("Error: Array is full, cannot insert new element!\n");
        return;
    }
    if (position < 1 || position > *size + 1) {
        printf("Error: Invalid position!\n");
        return;
    }

    // Shift elements to the right to make space
    for (int i = *size; i >= position; i--) {
        arr[i] = arr[i - 1];
    }
    arr[position - 1] = element;
    (*size)++;
    printf("Element inserted successfully!\n");
}

// Function to delete an element at a specified position
void delete(int arr[], int *size, int position) {
    if (*size == 0) {
        printf("Error: Array is empty, cannot delete element!\n");
        return;
    }
    if (position < 1 || position > *size) {
        printf("Error: Invalid position!\n");
        return;
    }

    // Shift elements to the left to fill the gap
    for (int i = position - 1; i < *size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*size)--;
    printf("Element deleted successfully!\n");
}

// Function to search for an element in the array
int search(int arr[], int size, int element) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == element) {
            return i;
        }
    }
    return -1; // Element not found
}

// Function to update an element at a specified position
void update(int arr[], int position, int new_element) {
    arr[position] = new_element;
    printf("Element updated successfully!\n");
}

// Function to display the array elements
void display(int arr[], int size) {
    if (size == 0) {
        printf("Array is empty!\n");
        return;
    }
    printf("Array elements: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
