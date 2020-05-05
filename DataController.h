#pragma once
#include <list>
#include <string>
#include <iterator>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <functional>

using namespace std;

template<typename T>
int distance(typename list<T>::iterator first, typename list<T>::iterator last, const list<T>& list);

template<typename T>
void fill_file(const list<T>& list, string filename); // ���������� ����� ���������� ������������

template<typename T>
void print(const list<T>& list); // ������ ��������� ������������ � �������

// ��������� ����� ��� ���������� ���������� �������
template<typename T>
class DataController
{
private:
	//��������� ��� ���������� ��� �������� ������ - ������
	list<T> _list;
public:
	void add_elem(); // ���������� ��������
	bool change_elem(function<void(T&)> change); // ��������� �������� � �������
										  // ���������� ������� 
	bool delete_elem(); // �������� ��������
	void clear(); // ������� ����������
	bool empty(); // �������� ���������� �� �������

	void fill_container(string filename); // ���� ��������� �� �����
	void fill_file_from_container(string filename); // ���������� ����� ���������� ����������
	void print_container(); // ������ ��������� ���������� � �������	

	// �������� ����� ��������� �� �������� ���������
	// check - ������� �������� (���� ������� ��������, ���������� true) 
	list<T> linear_search_elements(function<bool(const T&)> check);

	// �������� ����� ��������� �� �������� ��������
	// value - ����������� �������� (���� ����������� ������ �������� �������� ���������,
	// ���������� ��� ��������� �������� 
	// check - ������� �������� (���� ������� ��������, ���������� true) 
	// compare - ���������� ��� ���������� ���������
	list<T> binary_search_elements(const T& value, function<bool(const T&)> check, function<bool(const T&, const T&)> compare);
};

template<typename T>
void DataController<T>::add_elem()
{
	
	cout << endl << "������� �������, ������� ���������� ��������:" << endl;
	T tmp;
	cin >> tmp;
	_list.push_back(tmp);
	cout << endl << "�������� ������� ������� ��������." << endl;
}	

template<typename T>
bool DataController<T>::change_elem(function<void(T&)> change)
{
	cout << endl << "������� �������, ������� ���������� ��������:" << endl;
	T tmp;
	cin >> tmp;
	auto iter = find(_list.begin(), _list.end(), tmp);
	if (iter != _list.end())
	{
		cout << endl << "�������� ������� ������." << endl;
		change(*iter);
		cout << endl << "�������� ������� ������� ������." << endl;
		return true;
	}
	else
	{
		cout << endl << "�������� ������� �����������." << endl;
		return false;
	}	
}

template<typename T>
bool DataController<T>::delete_elem()
{
	cout << endl << "������� �������, ������� ���������� �������:" << endl;
	T tmp;
	cin >> tmp;
	auto iter = find(_list.begin(), _list.end(), tmp);
	if (iter != _list.end())
	{
		_list.erase(iter);
		cout << endl << "�������� ������� ������� �����." << endl;
		return true;
	}
	else
	{
		cout << endl << "�������� ������� �����������." << endl;
		return false;
	}
}

template<typename T>
void DataController<T>::clear()
{
	_list.clear();
	cout << endl << "��������� ������." << endl;
}

template<typename T>
bool DataController<T>::empty()
{
	return _list.empty();
}

template<typename T>
void DataController<T>::fill_container(string filename)
{
	ifstream fin(filename);
	if (!fin.is_open())
		cout << endl << "�� ������ ������� ��������� ����!" << endl;
	else
	{
		if (fin.peek() == EOF)
		{
			cout << endl << "��������� ���� - ������!" << endl;
		}
		else
		{
			copy(istream_iterator<T>(fin), istream_iterator<T>(), back_inserter(_list));
			cout << endl << "��������� �������� ���������� �� ���������� �����." << endl;
		}
		fin.close();
	}	
}

template<typename T>
void DataController<T>::fill_file_from_container(string filename)
{
	fill_file(_list, filename);
}

template<typename T>
void DataController<T>::print_container()
{
	print(_list);
}

template<typename T>
list<T> DataController<T>::linear_search_elements(function<bool(const T&)> check)
{
	list<T> result_list;
	for (T elem : _list)
	{
		if (check(elem))
		{
			result_list.push_back(elem);
		}
	}
	return result_list;
}

template<typename T>
inline list<T> DataController<T>::binary_search_elements(const T& value, function<bool(const T&)> check, function<bool(const T&, const T&)> compare)
{

	_list.sort(compare);
	auto left_border = _list.begin();
	auto right_border = _list.end();
	--right_border;
	int dist = distance(left_border, right_border, _list);

	while (dist > 0)
	{
		auto mid = left_border;
		int offset = dist / 2;
		for (int i = 0; i < offset; i++)
		{
			++mid;
		}
		if (compare(value, *mid))
		{
			right_border = mid;
			--right_border;
		}
		else
		{
			left_border = mid;
			++left_border;
		}
		dist = distance(left_border, right_border, _list);
	}

	list<T> result_list;
	for (; (right_border != _list.begin() && check(*right_border)); --right_border)
	{
		result_list.push_front(*right_border);
	}
	if (check(*right_border))
	{
		result_list.push_front(*right_border);
	}
	return result_list;
}

template<typename T>
int distance(const typename list<T>::iterator _first, const typename list<T>::iterator _last, const list<T>& _list)
{
	typename list<T>::iterator first = _first;
	typename list<T>::iterator last = _last;
	int dist = 0;
	while ((first != _list.end()) && (first != last))
	{
		++first;
		dist++;
	}
	if (first != last)
	{
		dist = -1;
	}
	return dist;
}

template<typename T>
void fill_file(const list<T>& list, string filename)
{
	ofstream fout(filename);
	if (!fout.is_open())
	{
		cout << endl << "���� � ����� ������ �� ������� �������!" << endl;
	}
	else
	{
		ostream_iterator<T> ositer(fout, "\n");
		copy(list.begin(), list.end(), ositer);
		cout << endl << "���� ������� ������ � ��������." << endl;
		fout.close();
	}
}

template<typename T>
void print(const list<T>& list)
{
	if (list.empty())
	{
		cout << endl << "������ ��������� ����!" << endl;
	}
	else
	{
		ostream_iterator<T> ositer(cout, "\n");
		cout << endl << "������ ��������� �������� ��������� ��������:" << endl;
		copy(list.begin(), list.end(), ositer);
	}
}
