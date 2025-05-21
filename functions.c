/*
Файл functions.c содержит реализации всех функций, объявленных в library.h.
Каждая функция выполняет конкретную задачу:
вывод меню, сохранение данных, сортировка, добавление, удаление и редактирование записей.
Все функции используют локализацию на русский язык для корректного отображения текста.
*/

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "library.h"

/*
Функция print_menu
Выводит на экран меню с опциями программы на русском языке.
*/
void print_menu() {
	setlocale(LC_ALL, "Russian");
	printf("\nМеню:\n");
	printf("1. Сортировать по месяцу и подсчитать книги\n");
	printf("2. Сортировать по фамилии\n");
	printf("3. Сортировать по количеству книг\n");
	printf("4. Добавить запись\n");
	printf("5. Удалить запись\n");
	printf("6. Редактировать запись\n");
	printf("7. Вывести список\n");
	printf("0. Выход\n");
	printf("Ваш выбор: ");
}

/*
Функция save_to_file
Сохраняет массив записей (структур) в текстовый файл с указанным именем.
Параметры:
- ar: массив записей (структур).
- count: количество записей в массиве.
- filename: имя файла для сохранения.
Если файл не удалось открыть, выводит сообщение об ошибке.
*/
void save_to_file(record ar[], int count, const char* filename) {
	setlocale(LC_ALL, "Russian");
	FILE *f_out = fopen(filename, "w");
	if (f_out == NULL) {
		printf("Ошибка открытия файла %s!\n", filename);
		return;
	}
	for (int i = 0; i < count; ++i) {
		fprintf(f_out, "%d.%d.%d %s %d\n",
			ar[i].issue_date.day,
			ar[i].issue_date.month,
			ar[i].issue_date.year,
			ar[i].surname,
			ar[i].books);
	}
	fclose(f_out);
}

/*
Функция save_monthly_summary
Создает и сохраняет в файл сводку по месяцам (суммарное количество книг за каждый месяц).
Сортирует сводку по году и месяцу.
Параметры:
- ar: массив записей (структур).
- count: количество записей в массиве.
- filename: имя файла для сохранения сводки.
*/
void save_monthly_summary(record ar[], int count, const char* filename) {
	setlocale(LC_ALL, "Russian");
	FILE *f_out = fopen(filename, "w");
	if (f_out == NULL) {
		printf("Ошибка открытия файла %s!\n", filename);
		return;
	}
	fprintf(f_out, "Месяц года Количество\n");
	monthly_summary summaries[AR_SIZE];
	int summary_count = 0;
	
	//Подсчет книг по месяцам и годам.
	for (int i = 0; i < count; ++i) {
		int month = ar[i].issue_date.month;
		int year = ar[i].issue_date.year;
		int found = 0;
		for (int j = 0; j < summary_count; ++j) {
			if (summaries[j].month == month && summaries[j].year == year) {
				summaries[j].books += ar[i].books;
				found = 1;
				break;
			}
		}
		if (!found) {
			summaries[summary_count].month = month;
			summaries[summary_count].year = year;
			summaries[summary_count].books = ar[i].books;
			summary_count++;
		}
	}
	
	//Сортировка сводки по году и месяцу.
	for (int i = 0; i < summary_count - 1; ++i) {
		int imin = i;
		for (int j = i + 1; j < summary_count; ++j) {
			if (summaries[j].year < summaries[imin].year ||
				(summaries[j].year == summaries[imin].year && summaries[j].month < summaries[imin].month)) {
				imin = j;
			}
		}
		if (i != imin) {
			monthly_summary t = summaries[i];
			summaries[i] = summaries[imin];
			summaries[imin] = t;
		}
	}
	
	//Запись отсортированной сводки в файл.
	for (int i = 0; i < summary_count; ++i) {
		fprintf(f_out, "%d.%d %d\n",
			summaries[i].month,
			summaries[i].year,
			summaries[i].books);
	}
	fclose(f_out);
}

/*
Функция ar_print
Выводит на экран список всех записей в массиве.
Параметры:
- ar: массив записей (структур).
- count: количество записей в массиве.
*/
void ar_print(record ar[], int count) {
	setlocale(LC_ALL, "Russian");
	printf("\nТекущий список записей:\n");
	for (int i = 0; i < count; ++i) {
		printf("%d.%d.%d %s %d\n",
			ar[i].issue_date.day,
			ar[i].issue_date.month,
			ar[i].issue_date.year,
			ar[i].surname,
			ar[i].books);
	}
}

/*
Функция swap
Меняет местами две записи (используется в сортировках).
Параметры:
- pa, pb: указатели на записи для обмена.
*/
void swap(record *pa, record *pb) {
	record t = *pa;
	*pa = *pb;
	*pb = t;
}

/*
Функция sort_by_month
Сортирует массив записей по месяцу выдачи.
Параметры:
- ar: массив записей (структур).
- len: длина массива (количество записей).
*/
void sort_by_month(record ar[], int len) {
	for (int i = 0; i < len - 1; ++i) {
		int imin = i;
		for (int j = i + 1; j < len; ++j) {
			if (ar[j].issue_date.month < ar[imin].issue_date.month) {
				imin = j;
			}
		}
		if (i != imin) {
			swap(&ar[imin], &ar[i]);
		}
	}
}

/*
Функция sort_by_surname
Сортирует массив записей по фамилии в алфавитном порядке.
Параметры:
- ar: массив записей (структур).
- len: длина массива (количество записей).
*/
void sort_by_surname(record ar[], int len) {
	for (int i = 0; i < len - 1; ++i) {
		int imin = i;
		for (int j = i + 1; j < len; ++j) {
			if (strcmp(ar[j].surname, ar[imin].surname) < 0) {
				imin = j;
			}
		}
		if (i != imin) {
			swap(&ar[imin], &ar[i]);
		}
	}
}

/*
Функция sort_by_books
Сортирует массив записей по количеству книг (по возрастанию).
Параметры:
- ar: массив записей (структур).
- len: длина массива (количество записей).
*/
void sort_by_books(record ar[], int len) {
	for (int i = 0; i < len - 1; ++i) {
		int imin = i;
		for (int j = i + 1; j < len; ++j) {
			if (ar[j].books < ar[imin].books) {
				imin = j;
			}
		}
		if (i != imin) {
			swap(&ar[imin], &ar[i]);
		}
	}
}

/*
Функция add_record
Добавляет новую запись в массив, запрашивая данные у пользователя.
Параметры:
- ar: массив записей (структур).
- count: указатель на количество записей (увеличивается при добавлении).
*/
void add_record(record ar[], int *count) {
	setlocale(LC_ALL, "Russian");
	if (*count >= AR_SIZE) {
		printf("Массив переполнен!\n");
		return;
	}
	printf("Введите данные записи (день.месяц.год фамилия количество_книг): ");
	scanf("%d.%d.%d %s %d",
		&ar[*count].issue_date.day,
		&ar[*count].issue_date.month,
		&ar[*count].issue_date.year,
		ar[*count].surname,
		&ar[*count].books);
	(*count)++;
	printf("Запись успешно добавлена.\n");
}

/*
Функция delete_record
Удаляет запись из массива по указанной фамилии, заменяя её последней записью массива.
Параметры:
- ar: массив записей (структур).
- count: указатель на количество записей (уменьшается при удалении).
*/
void delete_record(record ar[], int *count) {
	setlocale(LC_ALL, "Russian");
	char surname[20];
	printf("Введите фамилию для удаления: ");
	scanf("%s", surname);
	int found = 0;
	for (int i = 0; i < *count; i++) {
		if (strcmp(ar[i].surname, surname) == 0) {
			found = 1;
			ar[i] = ar[*count - 1];
			(*count)--;
			printf("Запись с фамилией %s удалена.\n", surname);
			break;
		}
	}
	if (!found) {
		printf("Запись с фамилией %s не найдена.\n", surname);
	}
}

/*
Функция edit_record
Редактирует существующую запись по указанной фамилии, запрашивая новые данные.
Параметры:
- ar: массив записей (структур).
- count: количество записей в массиве.
*/
void edit_record(record ar[], int count) {
	setlocale(LC_ALL, "Russian");
	char surname[20];
	printf("Введите фамилию для редактирования: ");
	scanf("%s", surname);
	int found = 0;
	for (int i = 0; i < count; i++) {
		if (strcmp(ar[i].surname, surname) == 0) {
			found = 1;
			printf("Введите новые данные (день.месяц.год фамилия количество_книг): ");
			scanf("%d.%d.%d %s %d",
				&ar[i].issue_date.day,
				&ar[i].issue_date.month,
				&ar[i].issue_date.year,
				ar[i].surname,
				&ar[i].books);
			printf("Запись с фамилией %s обновлена.\n", surname);
			break;
		}
	}
	if (!found) {
		printf("Запись с фамилией %s не найдена.\n", surname);
	}
}
