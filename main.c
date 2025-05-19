/*
Пробный вариант к зачету по дисциплине МДК.01.04 Системное программирование
Вариант №6
В базе данных хранятся сведения о работе библиотеки:
дата текущего года, фамилия читателя, количество книг
Структура входного файла in.txt
23.10.2022 Винни-Пух 5
12.11.2022 Пятачок 3
15.10.2022 Винни-Пух 7
...
Определить количество книг, взятых за каждый месяц, упорядочив по номеру месяца
Структура выходного файла out.txt
Месяц года Количество
10.2022 12
11.2022 3
*Дополнительно реализовано:
1. Меню
2. Запись в разные текстовые файлы для разных сортировок
3. Добавление, удаление, редактирование в массив
Выполнил Базан Игорь 303ИС-22
*/

#include <stdio.h>
#include <locale.h>
#include "library.h"

int main() {
	setlocale(LC_ALL, "Russian");
	FILE *f_in = fopen("in.txt", "r");
	if (f_in == NULL) {
		printf("Ошибка открытия файла in.txt!\n");
		return 1;
	}
	record ar[AR_SIZE];
	int count = 0;
	while (fscanf(f_in, "%d.%d.%d %s %d",
		&ar[count].issue_date.day,
		&ar[count].issue_date.month,
		&ar[count].issue_date.year,
		ar[count].surname,
		&ar[count].books) == 5) {
		++count;
	}
	fclose(f_in);
	int choice;
	do {
		print_menu();
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			sort_by_month(ar, count);
			save_to_file(ar, count, "sorted_by_month.txt");
			save_monthly_summary(ar, count, "out.txt");
			printf("Отсортировано по месяцу и сохранено в sorted_by_month.txt\n");
			printf("Итоги по месяцам сохранены в out.txt\n");
			ar_print(ar, count);
			break;
		case 2:
			sort_by_surname(ar, count);
			save_to_file(ar, count, "sorted_by_surname.txt");
			printf("Отсортировано по фамилии и сохранено в sorted_by_surname.txt\n");
			ar_print(ar, count);
			break;
		case 3:
			sort_by_books(ar, count);
			save_to_file(ar, count, "sorted_by_books.txt");
			printf("Отсортировано по количеству книг и сохранено в sorted_by_books.txt\n");
			ar_print(ar, count);
			break;
		case 4:
			add_record(ar, &count);
			ar_print(ar, count);
			break;
		case 5:
			delete_record(ar, &count);
			ar_print(ar, count);
			break;
		case 6:
			edit_record(ar, count);
			ar_print(ar, count);
			break;
		case 7:
			ar_print(ar, count);
			break;
		case 0:
			printf("Выход...\n");
			break;
		default:
			printf("Неверный выбор!\n");
		}
	} while (choice != 0);
	return 0;
}
