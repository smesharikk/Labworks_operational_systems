// «моделирование работы планировщика ос в однопроцессорной ос». рандомная генерация времени для процессов.
#define _crt_secure_no_warnings
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>


int main() {
    int amount_of_processes;
    int counts = 0;

    printf("write amount of processes: ");
    scanf("%d", &amount_of_processes);

    int iteration = amount_of_processes;
    int* a = (int*)malloc(amount_of_processes * sizeof(int));
    int* b = (int*)malloc(amount_of_processes * sizeof(int));

    for (int i = 0; i < amount_of_processes; i++) {
        counts = counts + 1;
        a[i] = counts;
    }

    printf("make random generation\n");

    srand(time(Null));
    for (int i = 0; i < amount_of_processes; i++) {
        b[i] = rand() % 40 + 1;
    }

    printf("number of process: ");
    for (int i = 0; i < amount_of_processes; i++) {
        if (b[i] <= 9) {
            printf("%d     ", a[i]);
        }
        else {
            printf("%d    ", a[i]);
        }
    }

    printf("\ntime  of  process: ");
    for (int i = 0; i < amount_of_processes; i++) {
        if (b[i] <= 9) {
            printf("%d     ", b[i]);
        }
        else if (b[i] >= 100) {
            printf("%d  ", b[i]);
        }
        else {
            printf("%d   ", b[i]);
        }
    }

    printf("\n\niteration num    | cpu time quantum            | total cpu time           | n of selected process          | time of selected process    | remaining cpu time\n");
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");

    srand(time(Null));

    int counter = 0;
    int cpu_time = 0;
    int last_cpu_time = 0;

    int c = 0;
    int d = 0;
    int e = 0;
    int* order_of_execution = (int*)malloc(amount_of_processes * sizeof(int));

    while (iteration > 0) {
        if (last_cpu_time == 0) {
            int max1 = 0;
            int bcc = -1;
            int quant_cp = rand() % 49 + 1;
            cpu_time = quant_cp + last_cpu_time + d;

            for (int i = 0; i < amount_of_processes; i++) {
                if (cpu_time >= b[i]) {
                    if (max1 < b[i]) {
                        max1 = b[i];
                        counter = i + 1;
                        bcc = bcc + 1;
                    }
                }
            }

            last_cpu_time = cpu_time - max1;

            if (bcc < 0) {
                last_cpu_time = cpu_time;
                if (c + 1 <= 9) {
                    printf("%d                |", c + 1);
                }
                else {
                    printf("%d               |", c + 1);
                }
                if (quant_cp < 10) {
                    printf("%d                            |", quant_cp);
                }
                else {
                    printf("%d                           |", quant_cp);
                }

                if (cpu_time < 10) {
                    printf("%d                         |-                               |-                             |", cpu_time);
                }

                else {
                    printf("%d                        |-                               |-                             |", cpu_time);
                }
                printf("%d\n", last_cpu_time);

                last_cpu_time = 0;
                d = cpu_time;
            }
            else {
                iteration = iteration - 1;
                if (c + 1 <= 9) {
                    printf("%d                |", c + 1);
                }
                else {
                    printf("%d               |", c + 1);
                }
                if (quant_cp < 10) {
                    printf("%d                            |", quant_cp);
                }
                else {
                    printf("%d                           |", quant_cp);
                }

                if (cpu_time < 10) {
                    printf("%d                         |", cpu_time);
                }
                else {
                    printf("%d                        |", cpu_time);
                }

                if (counter < 10) {
                    printf("%d                               |", counter);
                }
                else {
                    printf("%d                              |", counter);
                }

                if (max1 < 10) {
                    printf("%d                             |", max1);
                }
                else {
                    printf("%d                            |", max1);
                }

                printf("%d\n", last_cpu_time);

                    cpu_time = last_cpu_time;
                d = 0;
                b[counter - 1] = -1;
                order_of_execution[e] = counter;
                e++;
            }
            c++;
        }
        else if (last_cpu_time != 0) {
            int maxlast = 0;
            int f = -1;

            for (int i = 0; i < amount_of_processes; i++) {
                if (cpu_time >= b[i]) {
                    if (maxlast < b[i] && b[i] > 0) {
                        maxlast = b[i];
                        counter = i + 1;
                        f++;
                    }
                }
            }
            last_cpu_time = cpu_time - maxlast;
            if (f < 0) {
                last_cpu_time = cpu_time;
                printf("                 |                             |");

                if (cpu_time < 10) {
                    printf("%d                         |-                               |-                             |", cpu_time);
                }
                else {
                    printf("%d                        |-                               |-                             |", cpu_time);
                }

                printf("%d", last_cpu_time);
                printf("\n");
                last_cpu_time = 0;
                d = cpu_time;
            }
            else {
                iteration--;
                printf("                 |                             |");
                if (cpu_time < 10) {
                    printf("%d                         |", cpu_time);
                }
                else {
                    printf("%d                        |", cpu_time);
                }

                if (counter < 10) {
                    printf("%d                               |", counter);
                }
                else {
                    printf("%d                              |", counter);
                }

                if (maxlast < 10) {
                    printf("%d                             |", maxlast);
                }
                else {
                    printf("%d                            |", maxlast);
                }

                printf("%d\n", last_cpu_time);

                d = 0;
                b[counter - 1] = -1;
                order_of_execution[e] = counter;
                e++;
            }
        }
    }
    printf("\norder of execution: ");
    for (int i = 0; i < e; i++) {
        printf("%d ", order_of_execution[i]);
    }
}