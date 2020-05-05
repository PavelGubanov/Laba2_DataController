#pragma once
#include <string>
#include "Date.h"

using namespace std;

class BookRecord //�������������� ������ � �����, �������� �� ���� ��������
{
private:
	int number_of_library_card; // ����� ������������� ������
	string surname_of_reader; // ������� ��������
	Date date_of_issue; // ���� ������
	int repayment_period; // ���� ��������
	Date return_date; // ���� ��������
	string author_of_book; // ����� �����
	string name_of_book; // ��������
	int year_of_publication; // ��� ������������
	string publishing_house; // ������������

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

