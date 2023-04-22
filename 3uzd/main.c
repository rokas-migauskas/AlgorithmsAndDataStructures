#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "queue.h"
#include "priority_queue.h"


#define EMPLOYEE_COUNT 5

int random_factor(int min, int max) {
    return min + rand() % (max - min + 1);
}

int read_input_data(const char *filename, int *cash_register_cost, int **customer_times) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open input file: %s\n", filename);
        return -1;
    }

    fscanf(file, "%d", cash_register_cost);

    int n;
    fscanf(file, "%d", &n);

    *customer_times = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &(*customer_times)[i]);
    }

    fclose(file);
    return n;
}

void process1(Queue* customers, int service_time[], int n) {
    int total_time = 0;
    for (int i = 0; i < n; i++) {
        int customer_time = dequeue(customers);
        total_time += customer_time;
        service_time[i] = total_time;
    }
}

void process2(Queue* customers, int service_time[], int n) {
    int selection_time = 0;
    int payment_time = 0;

    PriorityQueue* paymentQueue = createPriorityQueue();

    for (int i = 0; i < n; i++) {
        int customer_time = dequeue(customers);
        int current_selection_time = customer_time / 2 + random_factor(-1, 1);
        int current_payment_time = customer_time - current_selection_time + random_factor(-1, 1);

        selection_time += current_selection_time;
        enqueuePriority(paymentQueue, current_payment_time, current_payment_time);

        // Add a random waiting time between the two steps.
        int waiting_time = random_factor(1, 3);

        // Dequeue the customer with the highest priority (lowest payment time).
        int dequeued_payment_time = dequeuePriority(paymentQueue);
        payment_time += dequeued_payment_time;

        // The customer's total service time is the sum of the time spent in both processes and the waiting time.
        service_time[i] = selection_time + dequeued_payment_time + waiting_time;
    }

    freePriorityQueue(paymentQueue);
}


void run_simulation(int n, int cash_register_cost, int customer_times[], int num_simulations, int time_units) {
    int min_time1, min_time2, max_time1, max_time2;
    float avg_time1, avg_time2;
    int total_cost1, total_cost2;

    total_cost1 = total_cost2 = 0;
    min_time1 = min_time2 = INT_MAX;
    max_time1 = max_time2 = INT_MIN;
    avg_time1 = avg_time2 = 0;

    for (int sim = 0; sim < num_simulations; sim++) {
        Queue* customers = createQueue();
        for (int i = 0; i < n; i++) {
            enqueue(customers, customer_times[i] * time_units);
        }

        int service_time1[n];
        int service_time2[n];

        process1(customers, service_time1, n);

        // Reset the queue for process2
        freeQueue(customers);
        customers = createQueue();
        for (int i = 0; i < n; i++) {
            enqueue(customers, customer_times[i] * time_units);
        }

        process2(customers, service_time2, n);

        int economic_cost1 = cash_register_cost * EMPLOYEE_COUNT;
        int economic_cost2 = cash_register_cost * (EMPLOYEE_COUNT / 2) + cash_register_cost;

        total_cost1 += economic_cost1;
        total_cost2 += economic_cost2;

        for (int i = 0; i < n; i++) {
            if (service_time1[i] < min_time1) min_time1 = service_time1[i];
            if (service_time1[i] > max_time1) max_time1 = service_time1[i];
            avg_time1 += service_time1[i];

            if (service_time2[i] < min_time2) min_time2 = service_time2[i];
            if (service_time2[i] > max_time2) max_time2 = service_time2[i];
            avg_time2 += service_time2[i];
        }

        freeQueue(customers);
    }

    avg_time1 /= (n * num_simulations);
    avg_time2 /= (n * num_simulations);

    printf("Time for Process 1: Min: %d, Avg: %.2f, Max: %d\n", min_time1, avg_time1, max_time1);
    printf("Time for Process 2: Min: %d, Avg: %.2f, Max: %d\n", min_time2, avg_time2, max_time2);

    printf("Economic cost for Process 1: %d\n", total_cost1 / num_simulations);
    printf("Economic cost for Process 2: %d\n", total_cost2 / num_simulations);
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s num_simulations time_units\n", argv[0]);
        return 1;
    }

    srand(time(NULL));

    int cash_register_cost;
    int *customer_times = NULL;
    int n = read_input_data("input.txt", &cash_register_cost, &customer_times);
    if (n == -1) {
        printf("Error: Could not read data from input.txt.\n");
        return 1;
    }

    int num_simulations = atoi(argv[1]);    // number of simulations
    int time_units = atoi(argv[2]);         // time units per simulation

    run_simulation(n, cash_register_cost, customer_times, num_simulations, time_units);

    free(customer_times);
    return 0;
}
