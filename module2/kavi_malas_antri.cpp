#include <iostream>

// Use the standard namespace as requested.
using namespace std;

//---------------------------------------------------------------------------//
// Node Class (Represents a Person)
// This class is the basic building block of our linked list.
// Each Node object represents one person in the queue.
//---------------------------------------------------------------------------//
class Node {
public:
    int id;      // The unique ID of the person
    Node* next;  // Pointer to the next person in the queue
    Node* prev;  // Pointer to the previous person in the queue

    // Constructor to initialize a new person with an ID.
    // By default, a new node is not connected to any other node.
    Node(int personId) {
        id = personId;
        next = nullptr;
        prev = nullptr;
    }
};

//---------------------------------------------------------------------------//
// WakandaQueue Class (Manages the entire queue)
// This class encapsulates all the logic for the queue simulation.
// It uses a doubly linked list to manage the people.
//---------------------------------------------------------------------------//
class WakandaQueue {
private:
    Node* head;  // Pointer to the very first person in the line
    Node* tail;  // Pointer to the very last person in the line
    Node* stand; // Special pointer to the 'stand' node (ID 0)

    // Helper function to find a node by its ID.
    // Traverses the list from the head until it finds the ID.
    // Returns nullptr if the ID is not found.
    Node* findNodeById(int targetId) {
        Node* current = head;
        while (current != nullptr) {
            if (current->id == targetId) {
                return current;
            }
            current = current->next;
        }
        return nullptr; // Not found
    }

public:
    // Constructor: Initializes the queue.
    // The stand (ID 0) is created and is initially the only element.
    WakandaQueue() {
        stand = new Node(0);
        head = stand;
        tail = stand;
    }

    // Destructor: Cleans up memory.
    // It's crucial to delete all dynamically allocated nodes to prevent memory leaks.
    ~WakandaQueue() {
        Node* current = head;
        while (current != nullptr) {
            Node* nodeToDelete = current;
            current = current->next;
            delete nodeToDelete;
        }
    }

    // Main function to process a new person entering the queue.
    bool addNewPerson(int newPersonId, char position, int referenceId) {
        // Find the person they want to queue relative to.
        Node* referenceNode = findNodeById(referenceId);

        // Rule: If the reference person doesn't exist, the input is invalid.
        if (referenceNode == nullptr) {
            return false; // Indicate failure
        }

        Node* newPersonNode = new Node(newPersonId);

        if (position == 'A') { // After
            newPersonNode->prev = referenceNode;
            newPersonNode->next = referenceNode->next;

            if (referenceNode->next != nullptr) {
                referenceNode->next->prev = newPersonNode;
            } else {
                tail = newPersonNode;
            }
            referenceNode->next = newPersonNode;

        } else if (position == 'B') { // Before
            if (referenceNode->id == 0) {
                delete newPersonNode;
                return false; // Indicate failure
            }
            newPersonNode->next = referenceNode;
            newPersonNode->prev = referenceNode->prev;

            if (referenceNode->prev != nullptr) {
                referenceNode->prev->next = newPersonNode;
            } else {
                head = newPersonNode;
            }
            referenceNode->prev = newPersonNode;
        }

        return true; // Indicate success
    }

    // Function to print the queue in the required spiral format.
    void printSpiral(int totalPeople) {
        // 1. Calculate the size of the square matrix.
        int matrixSize = 1;
        while (matrixSize * matrixSize < totalPeople) {
            matrixSize += 2;
        }

        // 2. Create and initialize the 2D matrix with a placeholder.
        int** matrix = new int*[matrixSize];
        for (int i = 0; i < matrixSize; ++i) {
            matrix[i] = new int[matrixSize];
            for (int j = 0; j < matrixSize; ++j) {
                matrix[i][j] = -1; // -1 means an empty spot
            }
        }

        // 3. Create a temporary 1D array to hold IDs in the correct spiral order.
        // The order is: people before the stand, then people after the stand.
        int* orderedIds = new int[totalPeople - 1];
        int count = 0;
        
        // Add people from the 'before' side (from stand->prev backwards).
        // This naturally gets them in the order: person closest to 0, next closest, etc.
        Node* current = stand->prev;
        while (current != nullptr) {
            orderedIds[count++] = current->id;
            current = current->prev;
        }

        // Add people from the 'after' side (from stand->next forwards).
        current = stand->next;
        while (current != nullptr) {
            orderedIds[count++] = current->id;
            current = current->next;
        }

        // 4. Fill the matrix in a counter-clockwise spiral using the ordered IDs.
        int centerX = matrixSize / 2;
        int centerY = matrixSize / 2;
        matrix[centerY][centerX] = 0; // Place the stand at the center.

        int x = centerX;
        int y = centerY;
        int dx = -1, dy = 0; // Start by moving Left
        int steps = 1;
        int turnCount = 0;
        int peoplePlaced = 0;
        
        while (peoplePlaced < totalPeople - 1) {
            // Move 'steps' times in the current direction
            for (int i = 0; i < steps; ++i) {
                if (peoplePlaced >= totalPeople - 1) break;
                
                x += dx;
                y += dy;
                
                matrix[y][x] = orderedIds[peoplePlaced];
                peoplePlaced++;
            }
            if (peoplePlaced >= totalPeople - 1) break;

            // Turn counter-clockwise (Left -> Down -> Right -> Up)
            int temp = dx;
            dx = dy;
            dy = -temp;
            
            turnCount++;
            if (turnCount % 2 == 0) {
                steps++; // Increase steps after every two turns
            }
        }
        
        // 5. Print the final matrix.
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                if (matrix[i][j] == -1) {
                    cout << "-";
                } else {
                    cout << matrix[i][j];
                }
                if (j < matrixSize - 1) {
                    cout << " ";
                }
            }
            cout << endl;
        }

        // 6. Clean up all dynamically allocated memory.
        delete[] orderedIds;
        for (int i = 0; i < matrixSize; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
};

//---------------------------------------------------------------------------//
// Main Function
//---------------------------------------------------------------------------//
int main() {
    // To speed up input/output operations.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n; // Read the number of people who will enter the queue

    WakandaQueue queue;

    for (int i = 0; i < n; ++i) {
        int id, refId;
        char pos;
        cin >> id >> pos >> refId;

        // Add the person to the queue. If it fails (invalid input), stop the program.
        if (!queue.addNewPerson(id, pos, refId)) {
            return 1;
        }
    }

    // If all inputs were valid, print the final queue in spiral format.
    // Total entities = n people + 1 stand.
    queue.printSpiral(n + 1);

    return 0; // Successful execution
}
