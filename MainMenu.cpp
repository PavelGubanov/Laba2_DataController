#include "MainMenu.h"
#include "DataController.h"
#include "BookRecord.h"
#include <Windows.h>
#include <cstdio>
#include <string>
#include <list>
#include <iostream>

using namespace std;

// чтение символа конца строки из консоли
void get_eoln()
{
	do
	{

	} while (getchar() != '\n');
}

//ввод числа с последующей проверкой его на принадлежность отрезку [min, max]
int get_num(string str, string err, int min, int max)
{
	int num;
	cout << str;
	cin >> num;
	get_eoln();
	while (num < min || num > max) {
		cout << str;
		cin >> num;
		get_eoln();
	}
	return num;
}

//ввод строки из консоли
string get_string(string text)
{
	cout << text;
	string result_string;
	getline(cin, result_string);
	return result_string;
}

void print_record_structure() 
{
	cout << endl << "_-_Структура информационной записи о книге_-_" << endl;
	cout << "Номер читательского билета" << endl;
	cout << "Фамилия читателя" << endl;
	cout << "Дата взятия книги (ДД.ММ.ГГГГ)" << endl;
	cout << "Срок возврата книги" << endl;
	cout << "Автор книги" << endl;
	cout << "Название книги" << endl;
	cout << "Год издания" << endl;
	cout << "Издательство" << endl;
}

// печать пунктов меню для изменения записи о книге
void print_change_menu() 
{
	cout << endl 
		<< "Выберите один из пунктов записи, который необходимо изменить:" << "\n"
		<< "0 - ничего не нужно изменять" << "\n"
		<< "1 - номер читательского билета" << "\n"
		<< "2 - фамилия читателя" << "\n"
		<< "3 - дата взятия книги" << "\n"
		<< "4 - срок возврата книги" << "\n"
		<< "5 - автор книги" << "\n"
		<< "6 - название книги" << "\n"
		<< "7 - год издания" << "\n"
		<< "8 - издательство" << "\n"
		<< endl;
}

//печать пунктов главного меню в зависимости от наличия элементов в списке
int print_main_menu(bool ContainerIsEmpty = false) {
	int stop_item = 2;
	cout << endl;
	cout << "Выберите один из пунктов меню:" << "\n"
		<< "0 - выйти из программы" << "\n"
		<< "1 - добавить запись" << "\n"
		<< "2 - считать записи из файла" << "\n";
	if (!ContainerIsEmpty) {
		cout << "3 - изменить запись" << "\n"
			<< "4 - удалить запись" << "\n"
			<< "5 - очистить контейнер" << "\n"
			<< "6 - вывести записи в консоль" << "\n"
			<< "7 - напечатать записи в файл" << "\n"
			<< "8 - создать контейнер из записей по заданному критерию" << "\n";
		stop_item = 8;
	}
	cout << endl;
	return stop_item;
}

//главное меню для программы
void main_menu()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Данная программа демонстрирует работу шаблонного классa для управления данными," << endl
		<< "на примере информационных записей в библиотеке о книгах." << endl;
	int stop_item, cur_item = 1;
	DataController<BookRecord> controller;
	while (cur_item != 0)
	{
		stop_item = print_main_menu(controller.empty());
		cur_item = get_num("Ваш выбор - ", "Ошибка! Такой пункт отсутствует в меню. Повторите ввод!", 0, stop_item);
		switch (cur_item)
		{
			case 1:
			{
				print_record_structure();
				controller.add_elem();
				break;
			}
			case 2:
			{
				string name = get_string("Введите имя текстового файла: ");
				controller.fill_container(name);
				break;
			}
			case 3:
			{
				print_record_structure();
				controller.change_elem([](BookRecord& br) -> void
					{
						int cur_change_item = 1;
						while (cur_change_item != 0)
						{
							int tmp_int;
							string tmp_str;
							Date tmp_date;
							print_change_menu();
							cur_change_item = get_num("Ваш выбор - ", "Ошибка! Такой пункт отсутствует в меню. Повторите ввод!", 0, 8);
							if (cur_change_item != 0)
							{
								cout << endl << "Введите новое значение для выбранного пункта: ";
								switch (cur_change_item)
								{
									case 1:
									{
										cin >> tmp_int;
										br.set_number_of_library_card(tmp_int);
										break;
									}
									case 2:
									{
										getline(cin, tmp_str);
										br.set_surname_of_reader(tmp_str);
										break;
									}
									case 3:
									{
										cin >> tmp_date;
										br.set_date_of_issue(tmp_date);
										break;
									}
									case 4:
									{
										cin >> tmp_int;
										br.set_repayment_period(tmp_int);
										break;
									}
									case 5:
									{
										getline(cin, tmp_str);
										br.set_author_of_book(tmp_str);
										break;
									}
									case 6:
									{
										getline(cin, tmp_str);
										br.set_name_of_book(tmp_str);
										break;
									}
									case 7:
									{
										cin >> tmp_int;
										br.set_year_of_publication(tmp_int);
										break;
									}
									case 8:
									{
										getline(cin, tmp_str);
										br.set_publishing_house(tmp_str);
										break;
									}
								}
							}
						}
					}
				);
				break;
			}
			case 4:
			{
				print_record_structure();
				controller.delete_elem();
				break;
			}
			case 5:
			{
				controller.clear();
				break;
			}
			case 6:
			{
				controller.print_container();
				break;
			}
			case 7:
			{
				string name = get_string("Введите имя текстового файла: ");
				controller.fill_file_from_container(name);
				break;
			}
			case 8:
			{
				list<BookRecord> result;
				BookRecord tmp;
				int search_element = get_num("\nПо какому элементу будет осуществляться поиск?\n1 - номер читательского билета\n2 - автор книги\n3 - издательство\n4 - дата возврата\nВаш выбор - ", "\nОшибка, повторите ввод!\n", 1, 4);
				switch (search_element)
				{
					case 1:
					{
						int number_of_library_card;
						cout << "Введите номер читательского билета: ";
						cin >> number_of_library_card;
						auto check = [number_of_library_card](const BookRecord& br) -> bool
						{
							return br.get_number_of_library_card() == number_of_library_card;
						};
						if (get_num("Какой алгоритм поиска нужно использовать: 1 - линейный, 2 - двоичный?\nВаш выбор - ", "\nОшибка, повторите ввод!\n", 1, 2) == 1)
						{
							result = controller.linear_search_elements(check);
						}
						else
						{
							tmp.set_number_of_library_card(number_of_library_card);
							result = controller.binary_search_elements(tmp, check, [](const BookRecord& rec1, const BookRecord& rec2) -> bool
							{
								return rec1.get_number_of_library_card() < rec2.get_number_of_library_card();
							});
						}
						break;
					}
					case 2:
					{
						string author;
						cout << "Введите автора: ";
						getline(cin, author);
						auto check = [author](const BookRecord& br)
						{
							return br.get_author_of_book() == author;
						};
						if (get_num("Какой алгоритм поиска нужно использовать: 1 - линейный, 2 - двоичный?\nВаш выбор - ", "\nОшибка, повторите ввод!\n", 1, 2) == 1)
						{
							result = controller.linear_search_elements(check);
						}
						else
						{
							tmp.set_author_of_book(author);
							result = controller.binary_search_elements(tmp, check, [](const BookRecord& rec1, const BookRecord& rec2) -> bool
								{
									return rec1.get_author_of_book() < rec2.get_author_of_book();
								});
						}
						break;
					}
					case 3:
					{
						string publishing_house;
						cout << "Введите издательство: ";
						getline(cin, publishing_house);
						auto check = [publishing_house](const BookRecord& br)
						{
							return br.get_publishing_house() == publishing_house;
						};
						if (get_num("Какой алгоритм поиска нужно использовать: 1 - линейный, 2 - двоичный?\nВаш выбор - ", "\nОшибка, повторите ввод!\n", 1, 2) == 1)
						{
							result = controller.linear_search_elements(check);
						}
						else
						{
							tmp.set_publishing_house(publishing_house);
							result = controller.binary_search_elements(tmp, check, [](const BookRecord& rec1, const BookRecord& rec2) -> bool
								{
									return rec1.get_publishing_house() < rec2.get_publishing_house();
								});
						}
						break;
					}
					case 4:
					{
						Date return_date;
						cout << "Введите дату возврата (чтобы найти просроченные записи): ";
						cin >> return_date;
						auto check = [return_date](const BookRecord& br)
						{
							return br.get_return_date() < return_date;
						};
						if (get_num("Какой алгоритм поиска нужно использовать: 1 - линейный, 2 - двоичный?\nВаш выбор - ", "\nОшибка, повторите ввод!\n", 1, 2) == 1)
						{
							result = controller.linear_search_elements(check);
						}
						else
						{
							tmp.set_date_of_issue(return_date);
							result = controller.binary_search_elements(tmp, check, [](const BookRecord& rec1, const BookRecord& rec2) -> bool
								{
									return rec1.get_return_date() < rec2.get_return_date();
								});
						}
						break;
					}
				}
				if (result.empty()) {
					cout << endl << "Записи с заданным критерием отсутствуют!" << endl;
				}
				else {
					cout << endl << "По заданному критерию сформирован контейнер из " << result.size() << " записи(-ей)." << endl;
					print(result);
				}
				break;
			}
			case 0:
			{
				break;
			}
		}
	}
}
