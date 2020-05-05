#pragma once
#include <string>
#include "Date.h"

using namespace std;

class BookRecord //Информационная запись о книге, выданной на руки абоненту
{
private:
	int number_of_library_card; // номер читательского билета
	string surname_of_reader; // фамилия абонента
	Date date_of_issue; // дата выдачи
	int repayment_period; // срок возврата
	Date return_date; // дата возврата
	string author_of_book; // автор книги
	string name_of_book; // название
	int year_of_publication; // год издательства
	string publishing_house; // издательство

public:
	int get_number_of_library_card() const;
	string get_surname_of_reader() const;
	Date get_date_of_issue() const;
	int get_repayment_period() const;
	Date get_return_date() const;
	string get_author_of_book() const;
	string get_name_of_book() const;
	int get_year_of_publication() const;
	string get_publishing_house() const;

	void set_number_of_library_card(const int number);
	void set_surname_of_reader(const string& surname);
	void set_date_of_issue(const Date& date);
	void set_repayment_period(const int period);
	void set_author_of_book(const string& author);
	void set_name_of_book(const string& name);
	void set_year_of_publication(const int year);
	void set_publishing_house(const string& house);
	void update_return_date();

	friend ostream& operator<< (ostream& out, const BookRecord& record);
	friend istream& operator>> (istream& in, BookRecord& record);

	friend bool operator== (const BookRecord& rec1, const BookRecord& rec2);
    friend bool operator!= (const BookRecord& rec1, const BookRecord& rec2);
	friend bool compare(const BookRecord& r1, const BookRecord& r2);

	BookRecord(int number_card,
		string surname_reader,
		Date date_of_issue,
		int period,
		string author_of_book,
		string name_of_book,
		int year_of_publication,
		string publishing_house);

	BookRecord();
};

