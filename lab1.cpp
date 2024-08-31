#include <iostream>
using namespace std;

/*
 алгоритм:
1. упорядочить элементы множества по убыванию (можно по возрастанию).
2. если время обработки различное, то процесс поступает на выполнение на тот
процессор, где суммарное время обработки меньше. для случая равных времён, помещаем
на 1-ый процессор.
*/
int main() {
    // system("chcp 65001");  -  для отображения русского языка
    int amount;
    cout << "write amount of processes: ";
    int* arr,*num;
   
    cin >> amount;
    arr = new int[amount];
    num = new int[amount];
    for (int i = 0; i <= (amount - 1); i++) {
        cout << "write time for " << i + 1 << " process: ";
        int time_for_process;
        cin >> time_for_process;
        arr[i] = time_for_process;
        num[i] = i;
    }

    // сортировка массива пузырьком (по убыванию)
    for (int i = 1; i < amount; ++i) {
        for (int r = 0; r < amount - i; r++) {
            if (arr[r] < arr[r + 1]) {
                int temp = arr[r];
                arr[r] = arr[r + 1];
                arr[r + 1] = temp;
                int temp_1 = num[r];
               num[r] = num[r + 1];
                num[r + 1] = temp_1;
            }
        }
    }

    /* выведем отсортированный массив */
    cout << "sorted processes: ";
    for (int i = 0; i < amount; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < amount; i++) {
        cout << num[i] << " ";
    }
    cout << endl;
    int* processor_1;
    processor_1 = new int[amount];
    //int processor_1[amount];
    int* processor_2;
    processor_2= new int[amount];

    int position_1 = 0;
    int sum_1 = 0;

    int position_2 = 0;
    int sum_2 = 0;
    // если время обработки различное, то процесс поступает на выполнение на тот
    //процессор, где суммарное время обработки меньше.для случая равных времён, помещаем
       // на 1 - ый процессор.
    for (int i = 0; i < amount; i++) {
        if (sum_1 + arr[i] <= sum_2 + arr[i]) {
            processor_1[position_1] = arr[i];
            position_1++;
            sum_1 += arr[i];
        }
        else {
            processor_2[position_2] = arr[i];
            position_2++;
            sum_2 += arr[i];
        }
    }

    cout << "processor 1: ";
    for (int i = 0; i < position_1; i++) {
        cout << processor_1[i] << " ";
    }
    cout << endl;
    cout << sum_1 << endl;
    cout << "processor 2: ";
    for (int i = 0; i < position_2; i++) {
        cout << processor_2[i] << " ";
    }
    cout << endl;
    cout << sum_2 << endl;
    

    return 0;
};
//
// sample input 1
//5
//1
//2
//3
//4
//5

// sample input 2
//6
//1
//5
//39
//40
//2
//3
