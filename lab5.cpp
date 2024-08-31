// Моделирование работы планировщика потоков в однопроцессорной ОС (приоритетное планирование)
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>


int main() {
    setlocale(LC_ALL, "Rus");
    int amount, sum = 0, wait_time = 0, min = INT_MAX, max_time = 0, index, min_time;

    int* process_time;
    int* process_time_copy;

    int* receipt_time;
    int* time_copy;

    int* priority;
    int* waiting_time;

    printf("Number of processes: ");
    scanf_s("%d", &amount);

    priority = (int*)malloc(amount * sizeof(int));
    process_time = (int*)malloc(amount * sizeof(int));
    process_time_copy = (int*)malloc(amount * sizeof(int));

    receipt_time = (int*)malloc(amount * sizeof(int));
    time_copy = (int*)malloc(amount * sizeof(int));
    waiting_time = (int*)malloc(amount * sizeof(int));

    printf("\n");

    // Введение данных для процессов
    for (int i = 0; i < amount; i++) {
        // Время поступления процесса
        printf("Time of %d receipt: ", i + 1);
        scanf_s("%d", &receipt_time[i]);
        printf("\n");

        // Время процесса
        printf("Duration of %d process: ", i + 1);
        scanf_s("%d", &process_time[i]);
        printf("\n");

        // Приоритет процесса
        printf("Priority of %d process: ", i + 1);
        scanf_s("%d", &priority[i]);
        printf("\n");

        // Выбор максимального времени поступления процесса
        if (receipt_time[i] > max_time)
            max_time = receipt_time[i];

        time_copy[i] = receipt_time[i];
        process_time_copy[i] = process_time[i];
        sum += process_time[i];
    }
    printf("\n   ");

    // Печать времени для процессов
    for (int count_time = 1; count_time <= 20; count_time++)
        printf("%d ", count_time);

    printf("\n");

    // Построение графика Ганта
    // e (execution) - исполнение, w (waiting) - ожидание
    for (int index_1 = 0; index_1 < amount; index_1++) {
        printf("%d", index_1 + 1);
        for (int index_2 = 0; index_2 < sum + max_time; index_2++) {
            min = INT_MAX;
            min_time = INT_MAX;
            index = -1;
            if (process_time[index_1] == 0) {
                break;
            }
            for (int j = 0; j < amount; j++) {
                if ((receipt_time[j] <= 0 && priority[j] < min && process_time[j]) ||
                    (receipt_time[j] <= 0 && priority[j] <= min && receipt_time[j] <= min_time && process_time[j])) {
                    min = priority[j];
                    index = j;
                    min_time = receipt_time[j];
                }
            }
            if (receipt_time[index_1] > 0) {
                printf("  ");
                if (index >= 0)
                    process_time[index]--;
            }
            else {
                if (index_1 == index) {
                    printf("e ");
                    process_time[index_1]--;
                }
                else {
                    printf("w ");
                    process_time[index]--;
                    waiting_time[index_1]++;
                }
            }
            for (int j = 0; j < amount; j++) {
                receipt_time[j]--;
            }
        }
        wait_time += waiting_time[index_1];
        printf("\n");
        for (int j = 0; j < amount; j++) {
            process_time[j] = process_time_copy[j];
            receipt_time[j] = time_copy[j];
        }
    }

    // Вывод результирующей таблицы
    printf("\nNumber of process");
    for (int i = 0; i < amount; i++)ф
        printf("%3d  ", i + 1);
    printf("\n");

    printf("Execution time   ");
    for (int i = 0; i < amount; i++)
        printf("%3d  ", process_time[i] + waiting_time[i]);
    printf("        %f  \n", (float)(sum + wait_time) / amount);

    printf("Waiting time     ");
    for (int i = 0; i < amount; i++)
        printf("%3d  ", waiting_time[i]);
    printf("        %f", (float)wait_time / amount);

    return 0;
}
