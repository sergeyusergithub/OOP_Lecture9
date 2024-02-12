#include <iostream>
#include <vector>

#include <chrono> // библиотека работы со временем
// создание шаблонного связного списка


template<typename Type>
class LinkedList {
public:
	// default constructor
	LinkedList():start_(nullptr),end_(nullptr),size_(0) {}


	// n - количество элементов в списке // лист с уже созданными n элементами
	LinkedList(int n) :LinkedList() {
		if (n < 0) {
			throw - 1;
		}
		if (n == 0)
			return;


		Node* tmp{};
		// -----
		// другой вариант создание списка на n элементов
		/*size_ = n;
		do {
			tmp = new Node;
			if (start_ == nullptr) {
				start_ = tmp;

			}
			n -= 1;
		} while (n > 0);*/

		//-----------

		int count{ 0 }; // счетчик добавленных Node addedNodes {} -   при такой инициализации 
						// компилятор позволяет производить сравнение типов
						// и отсекать часть ошибок

		tmp = new Node{};

		start_ = tmp;
		end_ = tmp;

		count += 1;

		while (count < n) {
			
			tmp = new Node{}; // создаем новую точку
			end_->Next(tmp); // старому концу списка говорим что новый конечный элемент существует
			end_ = tmp; // запоминаем в списке какой элемент сейчас последний
			count += 1;
		}

		size_ = n;

	}

	// констрвуктор копирования
	LinkedList(const LinkedList& other):LinkedList() {
		if (other.size() == 0) {
			return;
		}

		start_ = new Node(other.start_->Data());
		end_ = start_;
		// for(int i = 1; i < other.size(); i++)

		for (Node* current = other.start_->Next(); current != nullptr; current = current->Next())
		{
			// Node* tmp = new Node(other[i]); //
			Node* tmp = new Node(current->Data());
			end_->Next(tmp);
			end_ = tmp;

		}

		size_ = other.size_;
	}
	
	// конструкторв переноса
	// можно не делать, но для оптимизаации скорости работы программы полезно
	LinkedList(LinkedList&& other):LinkedList() {
		std::swap(start_,other.start_);
		std::swap(end_, other.end_);
		std::swap(size_, other.size_);
	}
	
	// тут не будет реализации конструктора от списка инициализации,
	// внесем позже

	~LinkedList() {

		Node* current = start_; 
		while (current != nullptr) {

			Node* tmp = current->Next();
			delete current;

			current = tmp;
		}
	}
	
	void clear() {
		Node* current = start_;
		while (current != nullptr) {

			Node* tmp = current->Next();
			delete current;

			current = tmp;
		}
		//LinkedList();
		start_ = nullptr;
		end_ = nullptr;
		size_ = 0;
	}

	/// оператор присваивания копированием
	LinkedList& operator = (const LinkedList& other) {
		clear();
		if (other.size() == 0) {
			return *this;
		}

		start_ = new Node(other.start_->Data());
		end_ = start_;
		// for(int i = 1; i < other.size(); i++)

		for (Node* current = other.start_->Next(); current != nullptr; current = current->Next())
		{
			// Node* tmp = new Node(other[i]); //
			Node* tmp = new Node(current->Data());
			end_->Next(tmp);
			end_ = tmp;

		}

		size_ = other.size_;

		return *this;
	}

	// оператор присваивания переносом
	LinkedList& operator = (LinkedList&& other) {
		clear();
		std::swap(start_, other.start_);
		std::swap(end_, other.end_);
		std::swap(size_, other.size_);

		return *this;
	}


	Type& operator[](int i) {
		int count{};
		Node* tmp = start_;
		while (count < i) {
			tmp = tmp->Next();
			count += 1;

		}
		return tmp->Data();
	}

	const Type & operator[](int i) const {
		int count{};
		Node* tmp = start_;
		while (count < i) {
			tmp = tmp->Next();
			count += 1;

		}
		return tmp->Data();
	}

	//=======================================
	Type& at(int i) {
		// проверка если вышли за диапазон значений
		if (i < 0 || i >= size_) {
			throw - 1;
		}
		int count{};
		Node* tmp = start_;
		while (count < i) {
			tmp = tmp->Next();
			count += 1;

		}
		return tmp->Data();
	}



	const Type & at(int i) const
	{
		// проверка если вышли за диапазон значений
		if (i < 0 || i >= size_) {
			throw - 1;
		}
		int count{};
		Node* tmp = start_;
		while (count < i) {
			tmp = tmp->Next();
			count += 1;

		}
		return tmp->Data();
	}



	// добавить данные в конец и в начало списка
	void push_back(const Type& obj) {
		// Node* tmp = new Node(obj); // сразу вызываем нужный контсруктор
		Node* tmp = new Node{ obj }; // сразу вызываем нужный контсруктор
		if (size_ = 0) {
			start_ = tmp;
			end_ = tmp;
		}
		else {
			end_->Next(tmp);
			end_ = tmp;
		}

		size_ += 1;
	}

	void push_front(const Type& obj){
		// Node* tmp = new Node(obj); // сразу вызываем нужный контсруктор
		Node* tmp = new Node{ obj }; // сразу вызываем нужный контсруктор
	if (size_ = 0) {
		start_ = tmp;
		end_ = tmp;
	}
	else {
		tmp->Next(start_);
		start_ = tmp;
	}

	size_ += 1;
	}
	
	// удалить (уничтожить) данные в конце и в начале списка
	void pop_back() {
		if (end_) { // end_ != 0
			auto tmp = start_;
			
			// цикл поиска предпоследнего элемента
			while (tmp->Next() != end_) {
				tmp = tmp->Next();
			}

			// осовбождение и замена последнего элемента

			delete end_;
			end_ = tmp;

			size_--;
		}

		if (!size_) { // size_ == 0
			end_ = start_;
			// end_ = start_ = nullptr;
		}
	}


	void pop_front() {
		if (start_) { // start_ != 0
			auto tmp = start_;
			start_ = start_->Next();
			delete tmp;
			size_--;
		}

		if (!size_) { // size_ == 0
			end_ = start_;
			// end_ = start_ = nullptr;
		}
	}

	/*
	emplace/insert - методы добавления новых данных в произвольное место коллекции
	erise - метод для уничтожения данных в произвольной точке коллекции
	
	*/

	// получение размера коллекции
	int size() const {
		return size_;
	}

	/*
	* методы для прохода по коллекции умными
	* указателями мы пока сознательно опустим
	*/

private:

	class Node {
	public:
		Node():Node(Type()){} // Type() - конструктор по умолчанию типа Type()
							// при делегации вызываем конструктор по умолчанию хранимого\
							// типа данных. Данный синтаксис корректно отработает даже если прямой вызов
							// такого метода (например конструктора встроенных типов) недоступен.

		Node(const Type& data, Node* place = nullptr) :data_(data), next_(place) {}

		Type& Data() {
			return data_;
		}
		const Type& Data() const {
			return data_;
		}

		// возврат местоположения следующей точи
		Node* Next()const {
			return next_;
		}

		// устанавливаем новое значение о следующей точке
		void Next(Node* next) {
			next_ = next;
		}

	private:
		Type data_;
		Node* next_;
	};


	Node* start_;
	Node* end_;
	int size_;

};

int main() {
	
	int arr[10]{};

	std::vector<int> vec;
	
	LinkedList<int> list;
	arr;
	for (int i = 0; i < 10000; i++) {
		vec.push_back(i + 1);
	}
	arr;
	for (int i = 0; i < 10000; i++) {
		list.push_back(i + 1);
	}


	arr;

	for (int i = 0; i < vec.size(); i++) {
		vec[i];
	}
	arr;

	for (int i = 0; i < list.size(); i++) {
		list[i];
	}
	arr;

	
	//arr[5] = 5;
	//vec[5] = 33;

	//list[5] = 12;


	//std::size(vec);
	//std::size(list);

	//// for(/*переменная для хранения элементов*/ : /*коллекция элементы которой нужно перебрать*/){
	//// }
	//// 
	//
	//for (auto & e : vec) {
	//	std::cout << e << ' ';
	//}

	//for (int& e : arr) {
	//	std::cout << e << ' ';
	//}

	//std::chrono::duration<float> time_lenght; // std::chrono::duration<float> - тип данных, если использовать такой тип
	//											// данных в векторе vector, то в range base for его можно заменить auto

	return 0;
}