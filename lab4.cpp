#include <iostream>

char** strings;  //массив из строк для вывода
int* sizes;    //размеры строк
int count, iteration, quant;
int* processTime;  //время процесса
int* timeLeft;
int* executionTime;  //время выполнения
int* prior;    //приоритет вполнения
int* timeReceipt;  //время поступления

void input() {    //метод ввода данных и выделение памяти
	printf("Введите квант: ");
	scanf_s("%d", &quant);
	printf("Введите кол-во процессов: ");
	scanf_s("%d", &count);
	processTime = (int*)malloc(count * sizeof(int));
	printf("Введите времена процессов: ");
	for (int i = 0; i < count; i++) {
		scanf_s("%d", &processTime[i]);
	}
	strings = (char**)malloc((count + 1) * sizeof(char*));   //выделили память для ссылок на массивы
	for (int i = 0; i <= count; i++) {
		strings[i] = (char*)malloc(256 * sizeof(char));
	}
	sizes = (int*)malloc((count + 1) * sizeof(int));    //память для каждой строки
	timeLeft = (int*)malloc(count * sizeof(int));
	executionTime = (int*)malloc(count * sizeof(int));
	prior = (int*)malloc(count * sizeof(int));
	timeReceipt = (int*)malloc(count * sizeof(int));
}

void init() {    //инициализация
	for (int i = 0; i <= count; i++) {  //очищаем все строки
		for (int j = 0; j < 256; j++) {
			strings[i][j] = '\0';
		}
	}
	strings[0][0] = '|';
	strings[0][1] = ' ';
	strings[0][2] = ' ';
	strings[0][3] = '|';
	for (int i = 1; i <= count; i++) {   //первый столбец
		strings[i][0] = '|';
		if (i <= 9) {
			strings[i][1] = (char)('0' + i);  //переводим число в строку
			strings[i][2] = ' ';
		}
		else {
			strings[i][1] = (char)('0' + i / 10);
			strings[i][2] = (char)('0' + i % 10);
		}
		strings[i][3] = '|';
	}
	for (int i = 0; i <= count; i++) {
		sizes[i] = 4;
	}
	iteration = 1;
	for (int i = 0; i < count; i++) {  //изначально оставшееся время равно времени процесса
		timeLeft[i] = processTime[i];
	}
	for (int i = 0; i < count; i++) {
		executionTime[i] = 0;
	}
	for (int i = 0; i < count; i++) {
		prior[i] = 0;
	}
	for (int i = 0; i < count; i++) {  //время поступления
		timeReceipt[i] = 0;
	}
}

void addToLine(int index) {   //добавление всех новых ячеек у столбца
	if (iteration <= 9) {     //заполнение ячейки для нулевой строки
		strings[0][sizes[0]] = (char)('0' + iteration);
		strings[0][sizes[0] + 1] = ' ';
	}
	else {
		strings[0][sizes[0]] = (char)('0' + iteration / 10);
		strings[0][sizes[0] + 1] = (char)('0' + iteration % 10);
	}
	strings[0][sizes[0] + 2] = '|';
	sizes[0] += 3;
	for (int i = 1; i <= count; i++) {
		if (timeLeft[i - 1] <= 0 || timeReceipt[i - 1] >= iteration) {
			strings[i][sizes[i]] = ' ';
		}
		else {
			if (i == index) strings[i][sizes[i]] = 'и';
			else strings[i][sizes[i]] = 'г';
			executionTime[i - 1]++;   //увеличиваем время выполнения
		}
		strings[i][sizes[i] + 1] = ' ';
		strings[i][sizes[i] + 2] = '|';
		sizes[i] += 3;
	}
	iteration++;
}

void printTable() {    //выводим таблицу
	char* str = (char*)malloc((sizes[0] + 1) * sizeof(char));  //создаем разделительную строку
	for (int i = 0; i < sizes[0]; i++) {
		str[i] = '-';
	}
	str[sizes[0]] = '\0';
	printf("%s\n", str);
	for (int i = 0; i <= count; i++) {    //выводим строки и разделительные строки
		printf("%s\n", strings[i]);
		printf("%s\n", str);
	}
}

void printAddTable() { //вывод второй таблицы
	int sumExTime = 0, sumWaitTime = 0;    //сумма времени выполнения и сумма времени ожидания
	int size = 18 + 3 * count + 8;   //размер разделительной строки
	char* str = (char*)malloc((size + 1) * sizeof(char));
	for (int i = 0; i < size; i++) {
		str[i] = '-';
	}
	str[size] = '\0';
	printf("%s\n", str);
	printf("|      № процесса|");    //вывод первой строки
	for (int i = 0; i < count; i++) {
		if (i <= 9) {
			printf("%d |", i + 1);
		}
		else {
			printf("%d|", i + 1);
		}
	}
	printf("       |\n");
	printf("%s\n", str);
	printf("|Время выполнения|");    //вывод строки с временем выполнения
	for (int i = 0; i < count; i++) {
		if (executionTime[i] <= 9) {
			printf("%d |", executionTime[i]);
		}
		else {
			printf("%d|", executionTime[i]);
		}
		sumExTime += executionTime[i];
	}
	if (sumExTime <= 9) {  //вывод суммарного времени выполнения
		printf("S = %d  |\n", sumExTime);
	}
	else if (sumExTime > 9 && sumExTime <= 99) {
		printf("S = %d |\n", sumExTime);
	}
	else {
		printf("S = %d|\n", sumExTime);
	}
	printf("%s\n", str);
	printf("|Время ожидания  |");   //вывод строки с временем ожидания
	for (int i = 0; i < count; i++) {
		if (executionTime[i] - processTime[i] <= 9) {
			printf("%d |", executionTime[i] - processTime[i]);
		}
		else {
			printf("%d|", executionTime[i] - processTime[i]);
		}
		sumWaitTime += executionTime[i] - processTime[i];
	}
	if (sumWaitTime <= 9) {  //вывод суммарного времени ожидания
		printf("S = %d  |\n", sumWaitTime);
	}
	else if (sumWaitTime > 9 && sumWaitTime <= 99) {
		printf("S = %d |\n", sumWaitTime);
	}
	else {
		printf("S = %d|\n", sumWaitTime);
	}
	printf("%s\n", str);
	printf("Среднее время выполнения %d/%d = %0.1f\n", sumExTime, count, (float)sumExTime / count);
	printf("Среднее время ожидания   %d/%d = %0.1f\n", sumWaitTime, count, (float)sumWaitTime / count);
}

void FCFS2() {
	printf("\nАлгоритм FCFS (c прерыванием процесса)\n");
	int rTime = quant;  //оставшееся время
	bool flag = true;
	while (flag) {
		for (int i = 0; i < count; i++) {
			while (timeLeft[i] > 0 && rTime > 0) { //выполняем процессы
				addToLine(i + 1);
				timeLeft[i]--;
				rTime--;
			}
			rTime = quant;
		}
		flag = false;
		for (int i = 0; i < count; i++) {  //проверяем, все ли процессы выполнены
			if (timeLeft[i] > 0) flag = true;
		}
	}
}

void SJF2() {
	printf("\nАлгоритм SJF (c прерыванием процесса)\n");
	int rTime = quant;
	bool flag = true;
	while (flag) {
		int min = 0, index = 0;  //индекс-номер процесса
		while (index < count && timeLeft[index] <= 0 || prior[index] == 1) {  //если prior 1, только что выполнили
			index++;
		}
		if (index != count) {
			min = timeLeft[index];
		}
		for (int j = index; j < count; j++) {   //поиск минимального времени
			if (timeLeft[j] < min && timeLeft[j] > 0 && prior[j] == 0) {
				min = timeLeft[j];
				index = j;
			}
		}
		while (timeLeft[index] > 0 && rTime > 0) {
			addToLine(index + 1);
			timeLeft[index]--;
			rTime--;
		}
		for (int i = 0; i < count; i++) {
			prior[i] = 0;
		}
		prior[index] = 1;
		rTime = quant;
		flag = false;
		for (int i = 0; i < count; i++) {  //проверяем, все ли процессы сделаны
			if (timeLeft[i] > 0) flag = true;
		}
	}
}

void SJF2_1() {
	printf("\nВведите времена поступления процессов: ");
	for (int i = 0; i < count; i++) {
		scanf_s("%d", &timeReceipt[i]);
	}
	printf("\nАлгоритм SJF (c прерыванием процесса и учетом времени поступления)\n");
	bool flag = true;
	while (flag) {
		int min = 0, index = 0;
		while (index < count && timeLeft[index] <= 0 || timeReceipt[index] >= iteration) {  //проверка
			index++;
		}
		if (index != count) min = timeLeft[index];
		for (int j = index; j < count; j++) {  //ищем минимум
			if ((timeLeft[j] < min || (timeLeft[j] <= min && prior[j] > prior[index])) && timeLeft[j] > 0 && timeReceipt[j] < iteration) {
				min = timeLeft[j];
				index = j;
			}
		}
		if (timeLeft[index] > 0 && timeReceipt[index] < iteration) {
			addToLine(index + 1);
			timeLeft[index]--;
			prior[index]++;
		}
		flag = false;
		for (int i = 0; i < count; i++) {  //проверка
			if (timeLeft[i] > 0) flag = true;
		}
	}
}

int main() {
	setlocale(LC_ALL, "Rus");
	input();
	init();
	FCFS2();
	printTable();
	printAddTable();
	init();
	SJF2();
	printTable();
	printAddTable();
	init();
	SJF2_1();
	printTable();
	printAddTable();
}