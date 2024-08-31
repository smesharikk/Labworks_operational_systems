/* ������������� ������ ������������ ������� ������� � ���������������� ��
(����� - �� ����������� ������������) fcfs, sjf*/
//���������� �����, ����������� ��� ��������� ���� ���������. ���������� ������� �����
//���������� � ������� ����� �������� ���������.��������� ������ �����.
#define _crt_secure_no_warnings
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;


void print_result(int algorithm, int all_time, float work_time, float wait_time) {
    printf("����� ��������� ���� ���������: %d\n", all_time);
    printf("������� ����� ����������: %0.1f\n", work_time);
    printf("������� ����� ��������: %0.1f\n\n", wait_time);
}


int main() {
    setlocale(LC_ALL, "russian");
    int amount_of_process;

    printf("������� ���������� ���������: ");
    scanf("%d", &amount_of_process);

    // ���������� ���������
    int* mas = (int*)malloc(amount_of_process * sizeof(int));
    for (int i = 0; i < amount_of_process; i++) {
        printf("������� ����� �������� %d: ", i + 1);
        scanf("%d", &mas[i]);
    }

    // 1. �������� fcfs
    printf("\n1. �������� fcfs\n");

    int all_time_fcfs = 0;
    int time = 0;
    int wait_time_fcfs = 0;

    for (int i = 0; i < amount_of_process; i++) {
        all_time_fcfs += mas[i];
    }
    printf("   ");

    for (int i = 0; i < all_time_fcfs; i++) {
        printf("%02d ", i + 1);
        }
    printf("\n");

    for (int i = 0; i < amount_of_process; i++) {
        printf("%02d ", i + 1);

        for (int j = 0; j < time; j++) {
            printf("�  ");
            wait_time_fcfs++;
        }

        for (int j = 0; j < mas[i]; j++) {
            printf("�  ");
            time++;
        }
        printf("\n");
    }

    int work_time_fcfs = 0;
    for (int i = 0; i < amount_of_process; i++) work_time_fcfs += mas[i] * (amount_of_process - i);

    print_result(1, all_time_fcfs, ((float)work_time_fcfs) / amount_of_process, ((float)wait_time_fcfs) / amount_of_process);

    // 2. �������� sjf
    printf("\n2. �������� sjf\n");

    int all_time_sjf = 0;
    for (int i = 0; i < amount_of_process; i++) all_time_sjf += mas[i];

    printf("   ");
    for (int i = 0; i < all_time_sjf; i++) printf("%02d ", i + 1);
    printf("\n");

    int* order = (int*)malloc(amount_of_process * sizeof(int));

    for (int i = 0; i < amount_of_process; i++) {
        order[i] = i;
    }

    for (int i = 0; i < amount_of_process; i++) {
        for (int j = 0; j < amount_of_process; j++) {
            if (mas[i] < mas[j]) {
                int t = mas[i];
                mas[i] = mas[j];
                mas[j] = t;

                t = order[i];
                order[i] = order[j];
                order[j] = t;
            }
        }
    }

    int wait_time_sgf=0;
    int work_time_sgf=0;

    for (int i = 0; i < amount_of_process; i++) {
        int j = 0;

        printf("%02d ", i + 1);
        while (order[j] != i) {
            for (int k = 0; k < mas[j]; k++) printf("�  ");
            work_time_sgf += mas[j];
            wait_time_sgf += mas[j];
            j++;
        }
        for (int k = 0; k < mas[j]; k++) printf("�  ");
        work_time_sgf += mas[j];
        printf("\n");
    }

    print_result(2, all_time_sjf, ((float)work_time_sgf) / amount_of_process, ((float)wait_time_sgf) / amount_of_process);
}