#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Frame {
    char ack;
    int data;
};

vector<Frame> frames;

void initializeFrames(int n) {
    frames.resize(n + 1);

    for (int i = 1; i <= n; i++) {
        frames[i].data = i;  // Assign frame number as data
        frames[i].ack = 'y'; // Initialize all frames as acknowledged
    }
}

int simulateAcknowledgment() {
    srand(time(NULL));

    for (int i = 1; i < frames.size(); i++) {
        int isAcknowledged = rand() % 2;
        if (!isAcknowledged) {
            cout << "Frame " << i << " was not acknowledged." << endl;
            frames[i].ack = 'n'; // Simulate acknowledgment failure
        }
    }

    // Check if any frame was not acknowledged
    for (int i = 1; i < frames.size(); i++) {
        if (frames[i].ack == 'n') {
            return i; // Return the frame number that was not acknowledged
        }
    }

    return -1; // All frames acknowledged successfully
}

void resendFramesGoBackN(int r) {
    if (r == -1) {
        cout << "No frame to resend." << endl;
        return;
    }

    cout << "Resending frames from frame " << r << endl;

    for (int i = r + 1; i < frames.size(); i++) {
        frames[i].ack = 'y';
        cout << "Received data of frame " << i << " is " << frames[i].data << endl;
    }
}

void resendFramesSelectiveRepeat(int r) {
    if (r == -1) {
        cout << "No frame to resend." << endl;
        return;
    }

    cout << "Resending frame " << r << endl;
    cout << "Received data of frame " << r << " is " << frames[r].data << endl;
}

int main() {
    int choice;
    int n; // Number of frames
    int r; // Declare r here

    do {
        cout << "\n1. Go-Back-N ARQ\n2. Selective Repeat ARQ\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
            case 2:
                cout << "Enter the number of frames to be sent: ";
                cin >> n;
                initializeFrames(n);
                r = simulateAcknowledgment();
                if (choice == 1)
                    resendFramesGoBackN(r);
                else
                    resendFramesSelectiveRepeat(r);
                cout << "All frames sent successfully using " << (choice == 1 ? "Go-Back-N" : "Selective Repeat") << " ARQ." << endl;
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
