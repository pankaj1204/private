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

void initializeFrames() {
    int n;
    cout << "Enter the number of frames to be sent: ";
    cin >> n;

    frames.resize(n + 1);

    for (int i = 1; i <= n; i++) {
        cout << "Enter data for frame " << i << ": ";
        cin >> frames[i].data;
        frames[i].ack = 'y';
    }
}

int simulateAcknowledgment() {
    srand(time(NULL));
    int r = rand() % frames.size();

    cout << "Simulating acknowledgment for frame " << r << endl;

    if (frames[r].ack == 'n') {
        frames[r].ack = 'y';
        return r;
    }

    return -1;
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

    do {
        cout << "\n1. Go-Back-N ARQ\n2. Selective Repeat ARQ\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                initializeFrames();
                int r1 = simulateAcknowledgment();
                resendFramesGoBackN(r1);
                cout << "All frames sent successfully using Go-Back-N ARQ." << endl;
                break;

            case 2:
                initializeFrames();
                int r2 = simulateAcknowledgment();
                resendFramesSelectiveRepeat(r2);
                cout << "All frames sent successfully using Selective Repeat ARQ." << endl;
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
