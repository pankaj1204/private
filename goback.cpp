#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Frame {
    char ack;
    int data;
};

int n;
vector<Frame> frames;

// Function to initialize sender frames
void initializeSenderFrames() {
    cout << "Enter the number of frames to be sent: ";
    cin >> n;

    frames.resize(n + 1); // Resize the vector to accommodate frames from 1 to n

    for (int i = 1; i <= n; i++) {
        cout << "Enter data for frame " << i << ": ";
        cin >> frames[i].data;
        frames[i].ack = 'y';
    }
}

// Function to simulate acknowledgment reception
int simulateAcknowledgment() {
    srand(time(NULL));
    int r = rand() % n + 1; // Random frame number between 1 and n

    cout << "Simulating acknowledgment for frame " << r << endl;

    if (frames[r].ack == 'n') {
        frames[r].ack = 'y';
        return r;
    }

    return -1;
}

// Function to resend frames using Selective Repeat ARQ
void resendFramesSelectiveRepeat(int r) {
    if (r == -1) {
        cout << "No frame to resend." << endl;
        return;
    }

    cout << "Resending frame " << r << endl;
    cout << "Received data of frame " << r << " is " << frames[r].data << endl;
}

// Function to resend frames using Go-Back-N ARQ
void resendFramesGoBackN(int r) {
    if (r == -1) {
        cout << "No frame to resend." << endl;
        return;
    }

    cout << "Resending frames from frame " << r << endl;

    for (int i = r; i <= n; i++) {
        frames[i].ack = 'y';
        cout << "Received data of frame " << i << " is " << frames[i].data << endl;
    }
}

// Function to implement Go-Back-N ARQ
void goBackN() {
    initializeSenderFrames();
    int r = simulateAcknowledgment();
    resendFramesGoBackN(r);
    cout << "All frames sent successfully." << endl;
}

// Function to implement Selective Repeat ARQ
void selectiveRepeat() {
    initializeSenderFrames();
    int r = simulateAcknowledgment();
    resendFramesSelectiveRepeat(r);
    cout << "All frames sent successfully." << endl;
}

int main() {
    int choice;
    do {
        cout << "\n\n1. Selective Repeat ARQ\n2. Go-Back-N ARQ\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                selectiveRepeat();
                break;
            case 2:
                goBackN();
                break;
            case 3:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
