#pragma once
#include <iostream>
#include <string>
using namespace std;


struct queue {
	
	/*
		Атрибуты и подструктуры.
	*/
	private:
		// Один элемент очереди.
		struct queue_element {
			// Значение элемента.
			int value;

			// Ссылка на следующий элемент.
			queue_element* Next;
		};

		// Элементы очереди
		queue_element* elements = new queue_element;

		// Инициализирована ли однонаправленная очередь.
		bool isINIT = false;

		// Пустая ли очередь
		bool isEMPTY = true;

		// Длина очереди
		int LENGTH = 0;

		// Количество введённых элементов
		int INPUTS_ELEMENTS = 0;


	/*
		Методы для работы с однонаправленной очередью.
	*/
	private:
		void throw_error(string error) {
			/*
				Вызов ошибки.
			*/
			throw exception(error.c_str());
		}

		void init(queue_element* qu, int length) {
			/*
				Инициализация элементов очереди.
			*/

			// Условие выхода из рекурсии
			if (length <= 1 || length > 10) {
				return;
			}

			// Инициализируем следующий элемент очереди
			qu->Next = new queue_element;

			// Запускаем рекурсию
			this->init(qu->Next, --length);
		}

		void show_elements(queue_element* qu, int length) {
			
			// Условие выхода из рекурсии
			if (length == 0) {
				return;
			}
			
			cout << "{" << (this->LENGTH - length) << "} => [" << qu->value << "]" << endl;
			this->show_elements(qu->Next, --length);
		}

		void move_queue(queue_element* qu, int value, int length) {
			/*
				Сдвиг очереди вправо на 1 элемент.
			*/

			// Условие выхода из рекурсии.
			if (length == 0) {
				return;
			}

			if (this->INPUTS_ELEMENTS > this->LENGTH) {
				this->INPUTS_ELEMENTS--;
			}

			int temp = qu->value;
			qu->value = value;
			this->move_queue(qu->Next, temp, --length);
		}

		int front(queue_element* qu, int length) {
			/*
				Первый элемент в очереди.
			*/

			return qu->value;
		}

		int back(queue_element* qu, int input_elements) {
			/*
				Последний элемент в очереди. 
			*/
			
			// Условие выхода из рекурсии.
			if (input_elements == 1) {
				return qu->value;
			}

			return back(qu->Next, --input_elements);
		}

	public:
		queue(const int length) {
			/*
				Инициализация очереди в зависимости от количества элементов length.
			*/

			// Инициализация очереди
			this->isINIT = true;
			this->LENGTH = length;
			this->init(elements, length);
		}

		~queue() {
			delete this;
		}

		bool is_empty() {
			/*
				Пустая ли очередь на данный момент.
			*/
			return this->isEMPTY;
		}

		void push_back(const int value) {
			/*
				Вставить элемент в очередь
			*/
			if (!this->isINIT) {
				this->throw_error("Функция: push_back; Ошибка: очередь не инициализирована!");
			}

			// Сдвигаем очередь
			this->isEMPTY = false;
			this->INPUTS_ELEMENTS++;
			this->move_queue(this->elements, value, this->LENGTH);
		}

		void show_elements() {
			/*
				Просмотреть элементы однонаправленного списка.
			*/

			if (!isINIT) {
				this->throw_error("Функция: show_elements; Ошибка: очередь не инициализирована!");
			}

			if (this->is_empty()) {
				this->throw_error("Функция: show_elements; Ошибка: очередь пустая!");
			}

			this->show_elements(this->elements, this->LENGTH);
		}

		int front() {
			/*
				Получить первый элемент из очереди.
			*/

			if (!isINIT) {
				this->throw_error("Функция: front; Ошибка: очередь не инициализирована!");
			}

			if (this->is_empty()) {
				this->throw_error("Функция: front; Ошибка: очередь пустая!");
			}

			return this->front(this->elements, this->LENGTH);
		}

		int back() {
			/*
				Получить последний элемент из очереди.
			*/

			if (!isINIT) {
				this->throw_error("Функция: back; Ошибка: очередь не инициализирована!");
			}

			if (this->is_empty()) {
				this->throw_error("Функция back; Ошибка: очередь пустая!");
			}

			return this->back(this->elements, this->INPUTS_ELEMENTS);
		}
};
