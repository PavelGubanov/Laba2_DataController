#include "MainMenu.h"
#include "DataController.h"
#include "BookRecord.h"
#include <Windows.h>
#include <cstdio>
#include <string>
#include <list>
#include <iostream>

using namespace std;

// ������ ������� ����� ������ �� �������
void get_eoln()
{
	do
	{

	} while (getchar() != '\n');
}

//���� ����� � ����������� ��������� ��� �� �������������� ������� [min, max]
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

//���� ������ �� �������
string get_string(string text)
{
	cout << text;
	string result_string;
	getline(cin, result_string);
	return result_string;
}

void print_record_structure() 
{
	cout << endl << "_-_��������� �������������� ������ � �����_-_" << endl;
	cout << "����� ������������� ������" << endl;
	cout << "������� ��������" << endl;
	cout << "���� ������ ����� (��.��.����)" << endl;
	cout << "���� �������� �����" << endl;
	cout << "����� �����" << endl;
	cout << "�������� �����" << endl;
	cout << "��� �������" << endl;
	cout << "������������" << endl;
}

// ������ ������� ���� ��� ��������� ������ � �����
void print_change_menu() 
{
	cout << endl 
		<< "�������� ���� �� ������� ������, ������� ���������� ��������:" << "\n"
		<< "0 - ������ �� ����� ��������" << "\n"
		<< "1 - ����� ������������� ������" << "\n"
		<< "2 - ������� ��������" << "\n"
		<< "3 - ���� ������ �����" << "\n"
		<< "4 - ���� �������� �����" << "\n"
		<< "5 - ����� �����" << "\n"
		<< "6 - �������� �����" << "\n"
		<< "7 - ��� �������" << "\n"
		<< "8 - ������������" << "\n"
		<< endl;
}

//������ ������� �������� ���� � ����������� �� ������� ��������� � ������
int print_main_menu(bool ContainerIsEmpty = false) {
	int stop_item = 2;
	cout << endl;
	cout << "�������� ���� �� ������� ����:" << "\n"
		<< "0 - ����� �� ���������" << "\n"
		<< "1 - �������� ������" << "\n"
		<< "2 - ������� ������ �� �����" << "\n";
	if (!ContainerIsEmpty) {
		cout << "3 - �������� ������" << "\n"
			<< "4 - ������� ������" << "\n"
			<< "5 - �������� ���������" << "\n"
			<< "6 - ������� ������ � �������" << "\n"
			<< "7 - ���������� ������ � ����" << "\n"
			<< "8 - ������� ��������� �� ������� �� ��������� ��������" << "\n";
		stop_item = 8;
	}
	cout << endl;
	return stop_item;
}

//������� ���� ��� ���������
void main_menu()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "������ ��������� ������������� ������ ���������� �����a ��� ���������� �������," << endl
		<< "�� ������� �������������� ������� � ���������� � ������." << endl;
	int stop_item, cur_item = 1;
	DataController<BookRecord> controller;
	while (cur_item != 0)
	{
		stop_item = print_main_menu(controller.empty());
		cur_item = get_num("��� ����� - ", "������! ����� ����� ����������� � ����. ��������� ����!", 0, stop_item);
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
				string name = get_string("������� ��� ���������� �����: ");
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
							cur_change_item = get_num("��� ����� - ", "������! ����� ����� ����������� � ����. ��������� ����!", 0, 8);
							if (cur_change_item != 0)
							{
								cout << endl << "������� ����� �������� ��� ���������� ������: ";
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
				string name = get_string("������� ��� ���������� �����: ");
				controller.fill_file_from_container(name);
				break;
			}
			case 8:
			{
				list<BookRecord> result;
				BookRecord tmp;
				int search_element = get_num("\n�� ������ �������� ����� �������������� �����?\n1 - ����� ������������� ������\n2 - ����� �����\n3 - ������������\n4 - ���� ��������\n��� ����� - ", "\n������, ��������� ����!\n", 1, 4);
				switch (search_element)
				{
					case 1:
					{
						int number_of_library_card;
						cout << "������� ����� ������������� ������: ";
						cin >> number_of_library_card;
						auto check = [number_of_library_card](const BookRecord& br) -> bool
						{
							return br.get_number_of_library_card() == number_of_library_card;
						};
						if (get_num("����� �������� ������ ����� ������������: 1 - ��������, 2 - ��������?\n��� ����� - ", "\n������, ��������� ����!\n", 1, 2) == 1)
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
						cout << "������� ������: ";
						getline(cin, author);
						auto check = [author](const BookRecord& br)
						{
							return br.get_author_of_book() == author;
						};
						if (get_num("����� �������� ������ ����� ������������: 1 - ��������, 2 - ��������?\n��� ����� - ", "\n������, ��������� ����!\n", 1, 2) == 1)
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
						cout << "������� ������������: ";
						getline(cin, publishing_house);
						auto check = [publishing_house](const BookRecord& br)
						{
							return br.get_publishing_house() == publishing_house;
						};
						if (get_num("����� �������� ������ ����� ������������: 1 - ��������, 2 - ��������?\n��� ����� - ", "\n������, ��������� ����!\n", 1, 2) == 1)
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
						cout << "������� ���� �������� (����� ����� ������������ ������): ";
						cin >> return_date;
						auto check = [return_date](const BookRecord& br)
						{
							return br.get_return_date() < return_date;
						};
						if (get_num("����� �������� ������ ����� ������������: 1 - ��������, 2 - ��������?\n��� ����� - ", "\n������, ��������� ����!\n", 1, 2) == 1)
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
					cout << endl << "������ � �������� ��������� �����������!" << endl;
				}
				else {
					cout << endl << "�� ��������� �������� ����������� ��������� �� " << result.size() << " ������(-��)." << endl;
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
