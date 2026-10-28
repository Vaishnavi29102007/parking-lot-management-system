#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SLOTS 5
#define MAX_QUEUE 100
#define NAME_LEN 50
#define VEHICLE_LEN 20

typedef struct {
    char owner[NAME_LEN];
    char vehicle_no[VEHICLE_LEN];
    time_t entry_time;
} Vehicle;

typedef struct {
    Vehicle items[MAX_QUEUE];
    int front;
    int rear;
    int count;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int isEmpty(Queue *q) { return q->count == 0; }
int isFull(Queue *q) { return q->count == MAX_QUEUE; }

int enqueue(Queue *q, Vehicle v) {
    if (isFull(q)) return 0;
    q->rear = (q->rear + 1) % MAX_QUEUE;
    q->items[q->rear] = v;
    q->count++;
    return 1;
}

int dequeue(Queue *q, Vehicle *v) {
    if (isEmpty(q)) return 0;
    *v = q->items[q->front];
    q->front = (q->front + 1) % MAX_QUEUE;
    q->count--;
    return 1;
}

void showStatus(int occupied, Queue *waiting) {
    printf("\\n========== PARKING STATUS ==========\\n");
    printf("Total parking slots : %d\\n", MAX_SLOTS);
    printf("Occupied slots      : %d\\n", occupied);
    printf("Available slots     : %d\\n", MAX_SLOTS - occupied);
    printf("Vehicles waiting    : %d\\n", waiting->count);
    printf("====================================\\n");
}

void listParked(Vehicle parked[], int occupied) {
    int i;
    printf("\\n------ Parked Vehicles ------\\n");
    if (occupied == 0) {
        printf("No vehicles are currently parked.\\n");
        return;
    }
    for (i = 0; i < occupied; i++) {
        char timebuf[30];
        struct tm *tm_info = localtime(&parked[i].entry_time);
        strftime(timebuf, sizeof(timebuf), "%d-%m-%Y %I:%M %p", tm_info);
        printf("%d. Vehicle: %-15s Owner: %-20s Entry: %s\\n",
               i + 1, parked[i].vehicle_no, parked[i].owner, timebuf);
    }
}

void listWaiting(Queue *q) {
    int i;
    printf("\\n------ Waiting Queue (FIFO) ------\\n");
    if (isEmpty(q)) {
        printf("No vehicles are waiting.\\n");
        return;
    }
    for (i = 0; i < q->count; i++) {
        int idx = (q->front + i) % MAX_QUEUE;
        printf("%d. Vehicle: %-15s Owner: %s\\n", i + 1,
               q->items[idx].vehicle_no, q->items[idx].owner);
    }
}

void parkOrQueue(Vehicle parked[], int *occupied, Queue *waiting) {
    Vehicle v;
    printf("Enter owner name: ");
    scanf(" %49[^\\n]", v.owner);
    printf("Enter vehicle number: ");
    scanf(" %19s", v.vehicle_no);
    v.entry_time = time(NULL);

    if (*occupied < MAX_SLOTS) {
        parked[*occupied] = v;
        (*occupied)++;
        printf("\\nVehicle %s parked successfully.\\n", v.vehicle_no);
    } else if (enqueue(waiting, v)) {
        printf("\\nParking is full. Vehicle %s added to the waiting queue.\\n", v.vehicle_no);
    } else {
        printf("\\nWaiting queue is full. Please try again later.\\n");
    }
}

void releaseVehicle(Vehicle parked[], int *occupied, Queue *waiting) {
    char number[VEHICLE_LEN];
    int i, found = -1;
    Vehicle leaving;

    if (*occupied == 0) {
        printf("\\nNo parked vehicles to release.\\n");
        return;
    }

    printf("Enter vehicle number to release: ");
    scanf(" %19s", number);

    for (i = 0; i < *occupied; i++) {
        if (strcmp(parked[i].vehicle_no, number) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\\nVehicle %s was not found in the parking lot.\\n", number);
        return;
    }

    leaving = parked[found];
    printf("\\nVehicle %s belonging to %s has left the parking lot.\\n",
           leaving.vehicle_no, leaving.owner);

    for (i = found; i < *occupied - 1; i++) parked[i] = parked[i + 1];
    (*occupied)--;

    if (!isEmpty(waiting)) {
        Vehicle next;
        dequeue(waiting, &next);
        parked[*occupied] = next;
        (*occupied)++;
        printf("Waiting vehicle %s has now been parked.\\n", next.vehicle_no);
    }
}

int main(void) {
    Vehicle parked[MAX_SLOTS];
    int occupied = 0, choice;
    Queue waiting;
    initQueue(&waiting);

    printf("====================================\\n");
    printf("      PARKING LOT MANAGEMENT        \\n");
    printf("====================================\\n");

    do {
        printf("\\n1. Park a vehicle\\n");
        printf("2. Release a vehicle\\n");
        printf("3. View parking status\\n");
        printf("4. View parked vehicles\\n");
        printf("5. View waiting queue\\n");
        printf("0. Exit\\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\\n");
            int ch;
            while ((ch = getchar()) != '\\n' && ch != EOF) {}
            continue;
        }

        switch (choice) {
            case 1: parkOrQueue(parked, &occupied, &waiting); break;
            case 2: releaseVehicle(parked, &occupied, &waiting); break;
            case 3: showStatus(occupied, &waiting); break;
            case 4: listParked(parked, occupied); break;
            case 5: listWaiting(&waiting); break;
            case 0: printf("\\nThank you for using the system!\\n"); break;
            default: printf("\\nInvalid choice. Please try again.\\n");
        }
    } while (choice != 0);

    return 0;
}
