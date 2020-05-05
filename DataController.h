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
void fill_file(const list<T>& list, string filename); // заполнение файла элементами подмножества

template<typename T>
void print(const list<T>& list); // печать элементов подмножества в консоль

// Шаблонный класс для управления различными данными
template<typename T>
class DataController
{
private:
	//Выбранный тип контейнера для хранения данных - список
	list<T> _list;
public:
	void add_elem(); // добавление элемента
	bool change_elem(function<void(T&)> change); // изменение элемента с помощью
										  // переданной функции 
	bool delete_elem(); // удаление элемента
	void clear(); // очистка контейнера
	bool empty(); // проверка контейнера на пустоту

	void fill_container(string filename); // ввод элементов из файла
	void fill_file_from_container(string filename); // заполнение файла элементами контейнера
	void print_container(); // печать элементов контейнера в консоль	

	// линейный поиск элементов по заданным критериям
	// check - унарный предикат (если элемент подходит, возвращает true) 
	list<T> linear_search_elements(function<bool(const T&)> check);

	// двоичный поиск элементов по заданным критерим
	// value - минимальное значение (если результатом поиска является диапозон элементов,
	// подходящих под указанные критерии 
	// check - унарный предикат (если элемент подходит, возвращает true) 
	// compare - компаратор для сортировки элементов
	list<T> binary_search_elements(const T& value, function<bool(const T&)> check, function<bool(const T&, const T&)> compare);
};

template<typename T>
void DataController<T>::add_elem()
{
	
	cout << endl << "Введите элемент, который необходимо добавить:" << endl;
	T tmp;
	cin >> tmp;
	_list.push_back(tmp);
	cout << endl << "Заданный элемент успешно добавлен." << endl;
}	

template<typename T>
bool DataController<T>::change_elem(function<void(T&)> change)
{
	cout << endl << "Введите элемент, который необходимо изменить:" << endl;
	T tmp;
	cin >> tmp;
	auto iter = find(_list.begin(), _list.end(), tmp);
	if (iter != _list.end())
	{
		cout << endl << "Заданный элемент найден." << endl;
		change(*iter);
		cout << endl << "Заданный элемент успешно изменён." << endl;
		return true;
	}
	else
	{
		cout << endl << "Заданный элемент отсутствует." << endl;
		return false;
	}	
}

template<typename T>
bool DataController<T>::delete_elem()
{
	cout << endl << "Введите элемент, который необходимо удалить:" << endl;
	T tmp;
	cin >> tmp;
	auto iter = find(_list.begin(), _list.end(), tmp);
	if (iter != _list.end())
	{
		_list.erase(iter);
		cout << endl << "Заданный элемент успешно удалён." << endl;
		return true;
	}
	else
	{
		cout << endl << "Заданный элемент отсутствует." << endl;
		return false;
	}
}

template<typename T>
void DataController<T>::clear()
{
	_list.clear();
	cout << endl << "Контейнер очищен." << endl;
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
		cout << endl << "Не удаётся открыть указанный файл!" << endl;
	else
	{
		if (fin.peek() == EOF)
		{
			cout << endl << "Указанный файл - пустой!" << endl;
		}
		else
		{
			copy(istream_iterator<T>(fin), istream_iterator<T>(), back_inserter(_list));
			cout << endl << "Контейнер заполнен элементами из указанного файла." << endl;
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
		cout << endl << "Файл с таким именем не удалось открыть!" << endl;
	}
	else
	{
		ostream_iterator<T> ositer(fout, "\n");
		copy(list.begin(), list.end(), ositer);
		cout << endl << "Файл успешно создан и заполнен." << endl;
		fout.close();
	}
}

template<typename T>
void print(const list<T>& list)
{
	if (list.empty())
	{
		cout << endl << "Данный контейнер пуст!" << endl;
	}
	else
	{
		ostream_iterator<T> ositer(cout, "\n");
		cout << endl << "Данный контейнер содержит следующие элементы:" << endl;
		copy(list.begin(), list.end(), ositer);
	}
}
