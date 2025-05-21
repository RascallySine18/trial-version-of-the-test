/*
Заголовочный файл определяет основные структуры данных (date, record, monthly_summary)
и объявляет функции для работы с массивом записей.
Макрос AR_SIZE задает максимальный размер массива (100 записей).
Все функции предназначены для управления данными библиотеки,
включая сортировку, вывод, сохранение и модификацию записей.
*/

#ifndef LIBRARY_H
#define LIBRARY_H
#define AR_SIZE 100

//Структура для хранения даты (день, месяц, год).
typedef struct {
	int day, month, year;
} date;

//Структура для хранения записи о выдаче книг: дата, фамилия читателя, количество книг.
typedef struct {
	date issue_date;
	char surname[20];
	int books;
} record;

//Структура для хранения сводки по месяцам: месяц, год, общее количество книг.
typedef struct {
	int month, year;
	int books;
} monthly_summary;

//Функция для вывода меню программы на экран.
void print_menu();

//Функция для сохранения массива записей (структур) в текстовый файл.
void save_to_file(record ar[], int count, const char* filename);

//Функция для подсчета и сохранения сводки по месяцам в текстовый файл.
void save_monthly_summary(record ar[], int count, const char* filename);

//Функция для вывода списка записей на экран.
void ar_print(record ar[], int count);

//Функция для обмена двух записей местами (используется в сортировках).
void swap(record *pa, record *pb);

//Функция для сортировки массива записей (структур) по месяцу выдачи.
void sort_by_month(record ar[], int len);

//Функция для сортировки массива записей (структур) по фамилии читателя.
void sort_by_surname(record ar[], int len);

//Функция для сортировки массива записей (структур) по количеству выданных книг.
void sort_by_books(record ar[], int len);

//Функция для добавления новой записи в массив.
void add_record(record ar[], int *count);

//Функция для удаления записи из массива по фамилии.
void delete_record(record ar[], int *count);

//Функция для редактирования существующей записи по фамилии.
void edit_record(record ar[], int count);

#endif
