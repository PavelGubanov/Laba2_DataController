#include "BookRecord.h"

int BookRecord::get_number_of_library_card() const { return number_of_library_card; }
string BookRecord::get_surname_of_reader() const { return surname_of_reader; }
Date BookRecord::get_date_of_issue() const { return date_of_issue; }
int BookRecord::get_repayment_period() const { return repayment_period; }
Date BookRecord::get_return_date() const { return return_date; }
string BookRecord::get_author_of_book() const { return author_of_book; }
string BookRecord::get_name_of_book() const { return name_of_book; }
int BookRecord::get_year_of_publication() const { return year_of_publication; }
string BookRecord::get_publishing_house() const { return publishing_house; }

void BookRecord::set_number_of_library_card(const int number)
{
	this->number_of_library_card = number;
}
void BookRecord::set_surname_of_reader(const string& surname)
{
	this->surname_of_reader = surname;
}
void BookRecord::set_date_of_issue(const Date& date)
{
	this->date_of_issue = date;
	(this->return_date = Date(date_of_issue)).addDays(repayment_period);
}
void BookRecord::set_repayment_period(const int period)
{
	this->repayment_period = period;
	(this->return_date = Date(date_of_issue)).addDays(repayment_period);
}
void BookRecord::set_author_of_book(const string& author)
{
	this->author_of_book = author;
}
void BookRecord::set_name_of_book(const string& name)
{
	this->name_of_book = name;
}
void BookRecord::set_year_of_publication(const int year)
{
	this->year_of_publication = year;
}
void BookRecord::set_publishing_house(const string& house)
{
	this->publishing_house = house;
}

void BookRecord::update_return_date()
{
	this->return_date = Date(date_of_issue);
	this->return_date.addDays(repayment_period);
}

bool compare(const BookRecord& r1, const BookRecord& r2)
{
	if (r1.number_of_library_card < r2.number_of_library_card)
		return true;
	if (r1.number_of_library_card > r2.number_of_library_card)
		return false;
	if (r1.author_of_book < r2.author_of_book)
		return true;
	if (r1.author_of_book > r2.author_of_book)
		return false;
	if (r1.publishing_house < r2.publishing_house)
		return true;
	if (r1.publishing_house > r2.publishing_house)
		return false;
	
	return (r1.return_date < r2.return_date);
}

BookRecord::BookRecord(int number_card, string surname_reader, Date date_of_issue,
					   int period, string author_of_book, string name_of_book,
					   int year_of_publication, string publishing_house) :
	number_of_library_card(number_card),
	surname_of_reader(surname_reader),
	date_of_issue(date_of_issue),
	repayment_period(period),
	author_of_book(author_of_book),
	name_of_book(name_of_book),
	year_of_publication(year_of_publication),
	publishing_house(publishing_house)
{
	this->return_date = Date(date_of_issue);
	this->return_date.addDays(period);
}

BookRecord::BookRecord():
	number_of_library_card(0),
	surname_of_reader(""),
	date_of_issue(Date()),
	repayment_period(0),
	author_of_book(""),
	name_of_book(""),
	year_of_publication(1000),
	publishing_house("")
{
	(this->return_date = Date()).addDays(repayment_period);
}

ostream& operator<<(ostream& out, const BookRecord& record)
{
	out << record.number_of_library_card << endl
		<< record.surname_of_reader << endl
		<< record.date_of_issue
		<< record.repayment_period << endl
		<< record.author_of_book << endl
		<< record.name_of_book << endl
		<< record.year_of_publication << endl
		<< record.publishing_house << endl;
	return out;
}

istream& operator>>(istream& in, BookRecord& record)
{
	string s;
	in >> record.number_of_library_card;
	getline(in, s);
	getline(in, record.surname_of_reader);
	in >> record.date_of_issue;
	in >> record.repayment_period;
	getline(in, s);
	getline(in, record.author_of_book);
	getline(in, record.name_of_book);
	in >> record.year_of_publication;
	getline(in, s);
	getline(in, record.publishing_house);
	record.update_return_date();
	return in;
}

bool operator==(const BookRecord& rec1, const BookRecord& rec2)
{
	return ((rec1.number_of_library_card == rec2.number_of_library_card) &&
		(rec1.surname_of_reader == rec2.surname_of_reader) &&
		(rec1.date_of_issue == rec2.date_of_issue) &&
		(rec1.repayment_period == rec2.repayment_period) &&
		(rec1.author_of_book == rec2.author_of_book) &&
		(rec1.name_of_book == rec2.name_of_book) &&
		(rec1.year_of_publication == rec2.year_of_publication) &&
		(rec1.publishing_house == rec2.publishing_house));
}

bool operator!=(const BookRecord& rec1, const BookRecord& rec2)
{
	return !(rec1 == rec2);
}
