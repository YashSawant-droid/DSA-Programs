#include <iostream>  // Include the standard input-output library
using namespace std;

class CircularQueue {
private:
    int front, rear, size;  // Variables to track the front, rear, and size of the queue
    char *queue;            // Pointer to dynamically allocate memory for the queue
    int capacity;           // Capacity of the queue (fixed size)

public:
    // Constructor to initialize the queue with a given capacity
    CircularQueue(int capacity) {
        front = rear = -1;          // Initially, both front and rear are set to -1 indicating an empty queue
        this->capacity = capacity;  // Set the capacity of the queue
        queue = new char[capacity]; // Dynamically allocate memory for the queue array
        size = 0;                   // Initially, the size of the queue is 0
    }

    // Destructor to deallocate the memory when the object is destroyed
    ~CircularQueue() {
        delete[] queue;  // Deallocate the memory for the queue array
    }

    // Function to check if the queue is full
    bool isFull() {
        return (size == capacity);  // Queue is full if the current size equals the capacity
    }

    // Function to check if the queue is empty
    bool isEmpty() {
        return (size == 0);  // Queue is empty if the current size is 0
    }

    // Function to insert an element into the queue
    void enqueue(char element) {
        if (isFull()) {  // Check if the queue is full
            cout << "Queue is full! Cannot insert more elements.\n";
            return;
        }
        if (isEmpty()) {  // If the queue is empty, set front and rear to 0
            front = rear = 0;
        } else {
            rear = (rear + 1) % capacity;  // Move the rear pointer to the next position circularly
        }
        queue[rear] = element;  // Insert the element at the rear position
        size++;  // Increase the size of the queue
    }

    // Function to remove an element from the queue
    void dequeue() {
        if (isEmpty()) {  // Check if the queue is empty
            cout << "Queue is empty! Cannot remove elements.\n";
            return;
        }
        if (front == rear) {  // If the queue has only one element, reset front and rear to -1
            front = rear = -1;
        } else {
            front = (front + 1) % capacity;  // Move the front pointer to the next position circularly
        }
        size--;  // Decrease the size of the queue
    }

    // Function to display the queue elements from the front to the rear
    void displayFromFront() {
        if (isEmpty()) {  // Check if the queue is empty
            cout << "Queue is empty\n";
            return;
        }
        int i = front;  // Start from the front of the queue
        do {
            cout << queue[i] << " ";  // Print the element at position i
            i = (i + 1) % capacity;   // Move to the next position circularly
        } while (i != (rear + 1) % capacity);  // Continue until the rear is reached
        cout << endl;
    }

    // Function to display the queue elements from the rear to the front
    void displayFromRear() {
        if (isEmpty()) {  // Check if the queue is empty
            cout << "Queue is empty\n";
            return;
        }
        int i = rear;  // Start from the rear of the queue
        do {
            cout << queue[i] << " ";  // Print the element at position i
            i = (i - 1 + capacity) % capacity;  // Move to the previous position circularly
        } while (i != (front - 1 + capacity) % capacity);  // Continue until the front is reached
        cout << endl;
    }

    // Function to display the current status of the queue
    void displayStatus() {
        if (isEmpty()) {  // Check if the queue is empty
            cout << "Queue is empty\n";
        } else {
            cout << "At front : " << front << " " << size << " " << queue[front] << endl;
            cout << "At rear : " << rear << " " << size << " " << queue[rear] << endl;
            cout << "All from front : " << front << " " << size << " ";
            displayFromFront();  // Display elements from the front
            cout << "All from rear : " << rear << " " << size << " ";
            displayFromRear();  // Display elements from the rear
        }
    }
};

int main() {
    int capacity = 5;  // Set the capacity of the queue to 5
    CircularQueue cq(capacity);  // Create a CircularQueue object with the specified capacity

    // Initial display showing the queue status after creation
    cout << "Display of elements in Queue:\n";
    cout << "After creation front rear elements\n";
    cq.displayStatus();  // Display the current status of the queue

    char token;  // Variable to store the token (element) to be inserted
    char insertMore;  // Variable to check if the user wants to insert more elements

    // Loop to add elements to the queue based on user input
    cout << "\nAddition of elements in : Token Insert More?\n";
    do {
        cout << "Token: ";  // Prompt for the token
        cin >> token;  // Read the token from user input
        cq.enqueue(token);  // Insert the token into the queue
        cout << "Insert More? (Y/N): ";  // Ask if the user wants to insert more elements
        cin >> insertMore;  // Read the response from user input
    } while (insertMore == 'Y' || insertMore == 'y');  // Continue until the user says no

    // Final display showing the queue status after additions
    cout << "\nAfter Additions front rear elements\n";
    cq.displayStatus();  // Display the current status of the queue

    return 0;  // End of the program
}

