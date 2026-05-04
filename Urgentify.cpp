#include <iostream>
using namespace std;

#define MAX_SIZE 20

// TASK structure
struct Task {
    string name;
    int number;
    int daysRemaining;
    int difficulty; // 1 (easy) to 5 (hardest) — used as tiebreaker
};

// ─────────────────────────────────────────
// QUEUE — History logbook (FIFO)
// First task finished = first task shown in history
// ─────────────────────────────────────────
class Queue {
private:
    Task data[MAX_SIZE];
    int front;
    int rear;

public:
    Queue() : front(0), rear(-1) {}

    void enqueue(Task t) {
        if (rear == MAX_SIZE - 1) {
            cout << "History is full!\n";
            return;
        }
        data[++rear] = t;
    }

    Task dequeue() {
        if (isEmpty()) {
            cout << "No history to remove.\n";
            Task empty;
            empty.number = -1;
            return empty;
        }
        return data[front++];
    }

    void display() {
        if (isEmpty()) {
            cout << "No history yet.\n";
            return;
        }

        cout << "Task History (oldest to newest):\n";
        for (int i = front; i <= rear; i++) {
            cout << "  Task " << data[i].number
                 << " | \"" << data[i].name << "\""
                 << " | Days remaining before finish: " << data[i].daysRemaining
                 << " | Difficulty: " << data[i].difficulty << "/5"
                 << endl;
        }
    }

    bool isEmpty() {
        return front > rear;
    }
};

// ─────────────────────────────────────────
// STACK — Raw task input (LIFO)
// Tasks are stored in the order you added them.
// The most recently added task sits on top.
// ─────────────────────────────────────────
class Stack {
private:
    Task data[MAX_SIZE];
    int top;

public:
    Stack() : top(-1) {}

    void push(Task t) {
        if (top == MAX_SIZE - 1) {
            cout << "Stack is full!\n";
            return;
        }
        data[++top] = t;
        cout << "Task pushed to stack!\n";
    }

    // Lets PriorityQueue read all tasks without removing them
    Task getAt(int index) {
        return data[index];
    }

    int getSize() {
        return top + 1;
    }

    // Remove a task by its task number (called when PriorityQueue finishes it)
    bool removeByNumber(int taskNumber) {
        for (int i = 0; i <= top; i++) {
            if (data[i].number == taskNumber) {
                for (int j = i; j < top; j++) {
                    data[j] = data[j + 1];
                }
                top--;
                return true;
            }
        }
        return false;
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack is empty.\n";
            return;
        }

        cout << "Stack (top to bottom — most recently added first):\n";
        for (int i = top; i >= 0; i--) {
            cout << "  Task " << data[i].number
                 << " | \"" << data[i].name << "\""
                 << " | Days remaining: " << data[i].daysRemaining
                 << " | Difficulty: " << data[i].difficulty << "/5"
                 << endl;
        }
    }

    bool isEmpty() {
        return top == -1;
    }
};

// ─────────────────────────────────────────
// PRIORITY QUEUE — Urgency-sorted view of the Stack
// Reads from the Stack, sorts by:
//   1. daysRemaining ascending  (fewer days = more urgent)
//   2. difficulty descending    (harder task wins the tie)
// Finishing a task removes it from BOTH the PriorityQueue and the Stack.
// ─────────────────────────────────────────
class PriorityQueue {
private:
    Task data[MAX_SIZE];
    int size;

    void sort() {
        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                bool doSwap = false;

                if (data[i].daysRemaining > data[j].daysRemaining) {
                    doSwap = true;
                } else if (data[i].daysRemaining == data[j].daysRemaining &&
                           data[i].difficulty < data[j].difficulty) {
                    doSwap = true;
                }

                if (doSwap) {
                    Task temp = data[i];
                    data[i] = data[j];
                    data[j] = temp;
                }
            }
        }
    }

public:
    PriorityQueue() : size(0) {}

    // Rebuild the priority queue from the current stack contents
    void buildFrom(Stack &s) {
        size = 0;
        for (int i = 0; i < s.getSize(); i++) {
            data[size++] = s.getAt(i);
        }
        sort();
    }

    void display() {
        if (isEmpty()) {
            cout << "No tasks in priority queue.\n";
            return;
        }

        cout << "Priority Queue (most urgent first):\n";
        for (int i = 0; i < size; i++) {
            cout << "  [" << (i + 1) << "] Task " << data[i].number
                 << " | \"" << data[i].name << "\""
                 << " | Days remaining: " << data[i].daysRemaining
                 << " | Difficulty: " << data[i].difficulty << "/5"
                 << endl;
        }
    }

    // Finish the most urgent task — removes it from the PQ, the Stack, and logs to Queue
    void finishTask(Stack &s, Queue &q) {
        if (isEmpty()) {
            cout << "No tasks to finish.\n";
            return;
        }

        Task finished = data[0];

        // Remove from priority queue
        for (int i = 0; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;

        // Remove from stack as well so they stay in sync
        s.removeByNumber(finished.number);

        // Log to history
        q.enqueue(finished);

        cout << "Finished Task " << finished.number
             << " | \"" << finished.name << "\"!\n";
    }

    bool isEmpty() {
        return size == 0;
    }
};

int main() {
    Stack s;
    PriorityQueue pq;
    Queue history;

    int choice;

    do {
        cout << "\n--- URGENTIFY: TASK ASSISTANT ---\n";
        cout << "1. Add Task\n";
        cout << "2. Show Stack (insertion order)\n";
        cout << "3. Show Priority Queue (urgency order)\n";
        cout << "4. View History\n";
        cout << "5. Finish Most Urgent Task\n";
        cout << "6. Remove Oldest History (Dequeue)\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {

        case 1: {
            Task t;

            cout << "Enter task number: ";
            cin >> t.number;

            cin.ignore();

            cout << "Enter task name: ";
            getline(cin, t.name);

            cout << "Enter days remaining: ";
            cin >> t.daysRemaining;

            cout << "Enter difficulty (1 = Easy, 5 = Hardest): ";
            cin >> t.difficulty;

            if (t.difficulty < 1) t.difficulty = 1;
            if (t.difficulty > 5) t.difficulty = 5;

            s.push(t);
            pq.buildFrom(s);
            break;
        }

        case 2:
            s.display();
            break;

        case 3:
            pq.display();
            break;

        case 4:
            history.display();
            break;

        case 5:
            pq.finishTask(s, history);
            break;

        case 6: {
            Task removed = history.dequeue();
            if (removed.number != -1) {
                cout << "Removed from history: Task "
                     << removed.number
                     << " | \"" << removed.name << "\"\n";
            }
            break;
        }
        }

    } while (choice != 0);

    return 0;
}