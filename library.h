#ifndef LIBRARY_H
#define LIBRARY_H

#define AR_SIZE 100

typedef struct {
	int day, month, year;
} date;

typedef struct {
	date issue_date;
	char surname[20];
	int books;
} record;

typedef struct {
	int month, year;
	int books;
} monthly_summary;

void print_menu();
void save_to_file(record ar[], int count, const char* filename);
void save_monthly_summary(record ar[], int count, const char* filename);
void ar_print(record ar[], int count);
void swap(record *pa, record *pb);
void sort_by_month(record ar[], int len);
void sort_by_surname(record ar[], int len);
void sort_by_books(record ar[], int len);
void add_record(record ar[], int *count);
void delete_record(record ar[], int *count);
void edit_record(record ar[], int count);

#endif
