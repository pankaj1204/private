
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <cerrno>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

// Function to say hello to each other
void say_hello(int client_socket) {
    char hello_message[] = "Hello, I'm the server!";
    send(client_socket, hello_message, sizeof(hello_message), 0);

    char response[1024];
    recv(client_socket, response, sizeof(response), 0);
    cout << "Client says: " << response << endl;
}

// Function to send a file
void send_file(int client_socket, const char* filename) {
    ifstream file(filename, ios::binary | ios::ate);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }

    streampos fileSize = file.tellg();
    char* buffer = new char[fileSize];

    file.seekg(0, ios::beg);
    file.read(buffer, fileSize);

    file.close();

    send(client_socket, buffer, fileSize, 0);
    delete[] buffer;
    cout << "File sent successfully." << endl;
}

// Function to perform calculations
double calculate(char operation, double operand1, double operand2) {
    switch (operation) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 == 0) {
                cerr << "Division by zero is not allowed." << endl;
                return NAN;
            }
            return operand1 / operand2;
        default:
            cerr << "Invalid operator." << endl;
            return NAN;
    }
}

int main() {
    // Create a socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        cerr << "Error creating server socket: " << strerror(errno) << endl;
        return 1;
    }

    // Bind the socket to a port
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345);
    server_address.sin_addr.s_addr = INADDR_ANY;
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    // Listen for incoming connections
    listen(server_socket, 5);

    cout << "Server is listening for incoming connections..." << endl;

    // Accept a connection
    int client_socket = accept(server_socket, nullptr, nullptr);

    say_hello(client_socket);

    // File transfer
    const char* filename = "sample.txt";
    send_file(client_socket, filename);

    // Calculator
    char operation;
    double operand1, operand2, result;

    recv(client_socket, &operation, sizeof(operation), 0);
    recv(client_socket, &operand1, sizeof(operand1), 0);
    recv(client_socket, &operand2, sizeof(operand2), 0);

    result = calculate(operation, operand1, operand2);
    send(client_socket, &result, sizeof(result), 0);

    // Close the sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
