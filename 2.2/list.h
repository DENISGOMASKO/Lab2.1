#pragma once
using namespace std;
/*class list
{
public:
	element *head;

	void push_back(int num) {
		element* p = head;
		for (; p != nullptr;) p = p->next;
		p->next = new element;
		p->next->next = nullptr;
		p->next->number = num;
	}

	void print_list() {
		
		element* p = head;
		for (; p != nullptr;) cout << p->number << ' ';
		cout << endl;
	}

};*/




class list
{
	public:
		int number;
		list* next{nullptr};
		bool head;
		list* head_ptr;

		list() {
			this->next = nullptr;
			this->head = true;
			this->head_ptr = this;
		}

		list(int num, list* nxt, list* head_ptr) {
			this->number = num;
			this->next = nullptr;
			this->head = false;
			this->head_ptr = head_ptr;
		}

		void push_back(int num) {

			list* p = head_ptr->next;
			if (p != nullptr) {
				while (p->next) p = p->next;
			}
			else {
				p = this;
			}
			
			p->next = new list(num, nullptr, head_ptr->head_ptr);

		}

		int len() {
			list* p = head_ptr->next;
			int len{0};
			while (p) {
				len++;
				p = p->next;
			}
			return len;
		}

		int element(int j) {
			list* p = head_ptr->next;
			int i{ 0 };
			while (p && i != j) {
				i++;
				p = p->next;
			}
			return p->number;
		}

};