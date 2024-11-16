#include <iostream>
using namespace std;


template<typename T>
class subforwardlist {

struct Node {
    T data;
    Node* next;
};

Node * begin;
Node * end;

public:

	//конструктор
    subforwardlist() {
        begin = nullptr;
        end = nullptr;
		cout << "List created" << endl;
    }

	//деструктор
	~subforwardlist() {
		while (begin) {
			Node * i = begin;
			if (begin == end) {
				begin = nullptr;
				end = nullptr;
				delete i;
			} else {
				while (i->next != end) {
					i = i->next;
				}
				Node * temp = end;
				end = i;
				i->next = nullptr;
				delete temp;
			}
		}
		cout << "List deleted" << endl;
	}
    
	//конструктор копирования
	subforwardlist(const subforwardlist<T> &rhs) {
		begin = nullptr;
		end = nullptr;
		unsigned int size = rhs.size();
		for (int i = 0; i < size; i++) {
			push_back(rhs.get_where_data(i+1));
		}
		Node *curr = begin;
		int counter = 1;
		while (counter != size) {
			curr = curr->next;
			counter++;
		}
		end = curr;
		cout << "List created via copy" << endl;
	}

	//оператор присваивания копированием
	subforwardlist& operator= (const subforwardlist<T> &rhs) {
		if (this != &rhs) {
			while (begin) {
				Node * i = begin;
				if (begin == end) {
					begin = nullptr;
					end = nullptr;
					delete i;
				} else {
					while (i->next != end) {
						i = i->next;
					}
					Node * temp = end;
					end = i;
					i->next = nullptr;
					delete temp;	
				}			
			}	
			// this->~subforwardlist<T>();
			
			unsigned int size = rhs.size();
			for (int j = 0; j < size; j++) {
				push_back(rhs.get_where_data(j+1));
			}
			Node *curr = begin;
			int counter = 1;
			while (counter != size) {
				curr = curr->next;
				counter++;
			}
			end = curr;
			cout << "List copied" << endl;
		}
		return *this;
	}

	//конструктор перемещенея 
	subforwardlist (subforwardlist<T>&& rhs) {
		begin = rhs.begin;
		end = rhs.end;
		rhs.begin = nullptr;
		rhs.end = nullptr;
		cout << "List created via movement" << endl;
	}

	//оператор присваивания перемещением
	subforwardlist& operator= (subforwardlist<T>&& rhs) {
		if (this != &rhs) {
			while (begin) {
				Node * i = begin;
				if (begin == end) {
					begin = nullptr;
					end = nullptr;
					delete i;
				} else {
					while (i->next != end) {
						i = i->next;
					}
					Node * temp = end;
					end = i;
					i->next = nullptr;
					delete temp;	
				}	
			}
			// this->~subforwardlist<T>();
			begin = rhs.begin;
			end = rhs.end;
			rhs.begin = nullptr;
			rhs.end = nullptr;
			cout << "List movemed" << endl;
		}
		return *this;
	}    

	T get_begin_data() const {
		if (!begin) {
			return T();
		} else {
			return begin->data;
		}
	}

	T get_end_data() const {
		if (!begin) {
			return T();
		} else {
			return end->data;
		}
	}

	T get_where_data (unsigned int where) const {
		if (!begin) {
			return T();
		} else {
			int counter = 1;
			Node * i = begin;
			while (counter != where and i != end) {
				counter++;
				i = i->next;
			}
			if (counter == where) {
				return i->data;
			} else {
				return T();
			}
		}
	}

	void print_list(){
		if (begin) {
			Node * i = begin;
			while (i != end) {
				cout << i->data << ' ';
				i = i->next;
			}
			cout << end->data << endl;
		}
	}

	void push_back(const T& data) {
	    if (!begin) {
			Node* new_node = new Node;
			new_node->data = data;
			new_node->next = nullptr;
			begin = new_node;
			end = new_node;
		} else {
			Node* new_node = new Node;
			new_node->data = data;
			new_node->next = nullptr;
			end->next = new_node;
			end = new_node;
		}
	}
	 // добавление элемента в конец
	T pop_back() {
		if (!begin) {
			return T();
		} else if (begin == end) {
			T res = begin->data;
			Node * temp = begin;
			begin = nullptr;
			end = nullptr;
			delete temp;
			return res;
		} else {
			Node * i = begin;
			while (i->next != end) {
				i = i->next;
			}
			Node * temp = end;
			end = i;
			i->next = nullptr;
			T res = temp->data;
			delete temp;
			return res;
		}
	}
	  // удаление элемента с конца
	void push_forward(const T& data) {
		if (!begin) {
			Node* new_node = new Node;
			begin = new_node;
			end = new_node;
		} else {
			Node* prev_first = begin;
			Node* new_node = new Node;
			new_node->data = data;
			new_node->next = prev_first;
			begin = new_node;
		}
	}//добавление элемента в начало недосписка
	T pop_forward(){
		if (!begin) {
			return T();
		} else if(begin == end) {
			T res = begin->data;
			Node * temp = begin;
			begin = nullptr;
			end = nullptr;
			delete temp;
			return res;
		} else {
			Node * temp = begin;
			T res = begin->data;
			begin = begin->next;
			delete temp;
			return res;
		}
	} 	//удаление элемента из начала недосписка
	void push_where(unsigned int where, const T& data) {
		if (where == 1) {
			push_forward(data);
		} else {
			Node * prev;
			Node * i = begin;
			int number = 1;
			while (number != where && i != end) {
				prev = i;
				i = i->next;
				number++;
			}
			if (number + 1 == where) {
				push_back(data);
			} else if (number == where) {
					Node* new_node = new Node;
					new_node->data = data;
					new_node->next = i;
					prev->next = new_node;
			}
		}
	} //добавление элемента с порядковым номером where
	T erase_where(unsigned int where) {
		T res;
		if (where == 1) {
			res = pop_forward();
		} else {
			Node * prev;
			Node * i = begin;
			int number = 1;
			while (number != where && i != end) {
				prev = i;
				i = i->next;
				number++;
			}
			if (number == where) {
				res = pop_back();
			} else if (number == where) {
				Node * temp = i;
				prev->next = i->next;
				res = temp->data;
				delete temp;
			}
		}
		return res;
	}	//удаление элемента с порядковым номером where

	unsigned int size() const {
		if (!begin) {
			return 0;
		} else {
			Node * i = begin;
			unsigned int res = 1;
			while (i != end) {
				i = i->next;
				res++;
			}
			return res;
		}
	} //определить размер недосписка
	
};

template<typename T>
subforwardlist<T> create_subforwardlist_with_one_node(T data) {
	subforwardlist<T> new_list;
	new_list.push_back(data);
	return new_list;
}

int main() {
    subforwardlist<int> x;
	x.push_back(5);
	x.push_back(4);
	x.push_forward(8);
	// cout << x.subforwardlist<int>::pop_back() << endl;
	// cout << x.subforwardlist<int>::pop_forward() << endl;
	// cout << x.subforwardlist<int>::get_begin() << endl;
	// x.subforwardlist<int>::print_list();
	// x.subforwardlist<int>::push_where(4, 10);
	// cout << x.subforwardlist<int>::erase_where(4) << endl;	
	// x.subforwardlist<int>::print_list();
	subforwardlist<int> a;
	a = move(x);
	// a = create_subforwardlist_with_one_node(7);
	a.subforwardlist<int>::print_list();
	// cout << a.subforwardlist<int>::get_where_data(1) << endl;
}