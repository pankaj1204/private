#include <iostream>
#include <vector>

using namespace std;

struct MemoryBlock {
    int size;
    int process_id;
};

void allocateMemory(vector<MemoryBlock>& memory, int process_id, int process_size, const string& strategy) {
    int index = -1;

    if (strategy == "Best") {
        int min_size = INT_MAX;
        for (int i = 0; i < memory.size(); i++) {
            if (memory[i].process_id == -1 && memory[i].size >= process_size && memory[i].size < min_size) {
                min_size = memory[i].size;
                index = i;
            }
        }
    } else if (strategy == "First") {
        for (int i = 0; i < memory.size(); i++) {
            if (memory[i].process_id == -1 && memory[i].size >= process_size) {
                index = i;
                break;
            }
        }
    } else if (strategy == "Next") {
        static int last_index = 0;
        for (int i = last_index; i < memory.size(); i++) {
            if (memory[i].process_id == -1 && memory[i].size >= process_size) {
                index = i;
                last_index = (i + 1) % memory.size();
                break;
            }
        }
        if (index == -1) {
            for (int i = 0; i < last_index; i++) {
                if (memory[i].process_id == -1 && memory[i].size >= process_size) {
                    index = i;
                    last_index = (i + 1) % memory.size();
                    break;
                }
            }
        }
    } else if (strategy == "Worst") {
        int max_size = -1;
        for (int i = 0; i < memory.size(); i++) {
            if (memory[i].process_id == -1 && memory[i].size >= process_size && memory[i].size > max_size) {
                max_size = memory[i].size;
                index = i;
            }
        }
    }

    if (index != -1) {
        memory[index].process_id = process_id;
        cout << "Process " << process_id << " of size " << process_size << " placed in block " << index << " using " << strategy << " Fit.\n";
    } else {
        cout << "Process " << process_id << " of size " << process_size << " cannot be placed using " << strategy << " Fit.\n";
    }
}

int main() {
    int memory_size, num_blocks;
    cout << "Enter the memory size: ";
    cin >> memory_size;

    cout << "Enter the number of memory blocks: ";
    cin >> num_blocks;

    vector<MemoryBlock> memory(num_blocks);

    for (int i = 0; i < num_blocks; i++) {
        cout << "Enter the size of memory block " << i << ": ";
        cin >> memory[i].size;
        memory[i].process_id = -1;
    }

    int choice, process_id, process_size;
    string strategies[] = {"Best", "First", "Next", "Worst"};

    do {
        cout << "\nMemory Placement Strategies:\n";
        for (int i = 0; i < 4; i++) {
            cout << i + 1 << ". " << strategies[i] << " Fit\n";
        }
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 4) {
            cout << "Enter process ID and size: ";
            cin >> process_id >> process_size;
            allocateMemory(memory, process_id, process_size, strategies[choice - 1]);
        } else if (choice != 5) {
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
