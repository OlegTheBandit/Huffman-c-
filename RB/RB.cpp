	#pragma once

	#include <iostream> 
	#include "Node.h"
	#include <fstream>
	#include <windows.h>
	#include <malloc.h>
	

	void SetColor(int text, int background)
	{
		HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleHandle, (WORD)((background << 4) | text));
	}

	using namespace std;

	class NodeOfTree
	{
	public:
		int a;
		char c;
		NodeOfTree* left, * right;

		NodeOfTree() { left = right = NULL; }

		NodeOfTree(NodeOfTree* L, NodeOfTree* R)
		{
			left = L;
			right = R;
			a = L->a + R->a;
		}
	};

	template<typename T>
	class NodeOfList
	{
	private:

		NodeOfList* next, * prev;
	public:
		T data;
		NodeOfList() : next(NULL), prev(NULL) {};
		NodeOfList(T data) {
			this->data = data;
			next = NULL;
			prev = NULL;
		}
		~NodeOfList() {
			next = NULL;
			prev = NULL;
		}
		void set_data(T data) {
			this->data = data;
		}
		T get_data() {
			return data;
		}
		NodeOfList* get_next() {

			return next;
		}
		NodeOfList* get_prev() {
			return prev;
		}
		void set_next(NodeOfList* pointer) {
			next = pointer;
		}
		void set_prev(NodeOfList* pointer) {
			prev = pointer;
		}
	};

	template<typename T>
	class List
	{
	private:


	public:


	
		NodeOfList<T>* head, * tail;
		NodeOfList<T>* get_pointer(size_t index)
		{
			if (isEmpty() || (index > get_size() - 1))
			{
				throw out_of_range("Invalid argument");
			}
			else if (index == get_size() - 1)
				return tail;
			else if (index == 0)
				return head;
			else
			{
				NodeOfList<T>* temp = head;
				while ((temp) && (index--))
				{
					temp = temp->get_next();
				}
				return temp;
			}
		}




		List() : head(NULL), tail(NULL) {}
		List(const List<T>& list) {
			clear();
			NodeOfList<T>* temp = list.head;
			while (temp) {
				push_back(temp->get_data());
				temp = temp->get_next();
			}
		}
		~List()
		{
			if (head == NULL)
			{
				head = NULL;
			}
			else
			{
				while (head)
				{
					tail = head->get_next();
					delete head;
					head = tail;
				}
			}
		}
		void push_back(T data)
		{
			NodeOfList<T>* temp = new NodeOfList<T>;
			temp->set_data(data);
			if (head)
			{
				temp->set_prev(tail);
				tail->set_next(temp);
				tail = temp;
			}
			else
			{
				head = temp;
				tail = head;
			}
		}
		void push_front(T data)
		{
			NodeOfList<T>* temp = new NodeOfList<T>;
			temp->set_data(data);
			if (head)
			{
				temp->set_next(head);
				head->set_prev(temp);
				head = temp;
			}
			else
			{
				head = temp;
				tail = head;
			}
		}
		void push_front(List& ls2)
		{
			NodeOfList<T>* temp = ls2.tail;
			size_t n = ls2.get_size();
			while ((temp) && (n--))
			{
				push_front(temp->get_data());
				temp = temp->get_prev();
			}
		}
		void pop_back()
		{
			if (head != tail)
			{
				NodeOfList<T>* temp = tail;
				tail = tail->get_prev();
				tail->set_next(NULL);
				delete temp;
			}
			else if (!isEmpty())
			{
				NodeOfList<T>* temp = tail;
				tail = head = NULL;
				delete temp;
			}
			else
				throw out_of_range("The list is empty");
		}
		void pop_front()
		{
			if (head != tail)
			{
				NodeOfList<T>* temp = head;
				head = head->get_next();
				head->set_prev(NULL);
				delete temp;
			}
			else if (!isEmpty())
			{
				NodeOfList<T>* temp = head;
				head = tail = NULL;
				delete temp;
			}
			else
				throw out_of_range("The list is empty");
		}
		void insert(size_t index, T data)
		{
			NodeOfList<T>* temp;
			temp = get_pointer(index);
			if (temp == head)
				push_front(data);
			else
			{
				NodeOfList<T>* newElem = new NodeOfList;
				newElem->set_data(data);
				temp->get_prev()->set_next(newElem);
				newElem->set_prev(temp->get_prev());
				newElem->set_next(temp);
				temp->set_prev(newElem);
			}
		}
		T at(size_t index)
		{
			NodeOfList<T>* temp;
			temp = get_pointer(index);
			return temp->get_data();
		}
		void remove(size_t index)
		{
			NodeOfList<T>* temp;
			temp = get_pointer(index);
			if (temp == head)
				pop_front();
			else if (temp == tail)
				pop_back();
			else
			{
				temp->get_prev()->set_next(temp->get_next());
				temp->get_next()->set_prev(temp->get_prev());
				delete temp;
			}
		}
		void remove(T data) {
			NodeOfList<T>* temp = head;
			while (temp && temp->get_data() != data)
				temp = temp->get_next();
			if (!temp)
				throw out_of_range("Invalid argument");
			if (temp == head)
				pop_front();
			else if (temp == tail)
				pop_back();
			else
			{
				temp->get_prev()->set_next(temp->get_next());
				temp->get_next()->set_prev(temp->get_prev());
				delete temp;
			}
		}
		size_t get_size()
		{
			NodeOfList<T>* temp = head;
			size_t length = 0;
			while (temp)
			{
				length++;
				temp = temp->get_next();
			}
			return length;
		}
		void print_to_console()
		{
			NodeOfList<T>* temp = head;
			while (temp)
			{
				cout << temp->get_data() << ' ';
				temp = temp->get_next();
			}
			cout << endl;
		}
		void clear()
		{
			if (this->isEmpty())
				return;
			while (head)
			{
				tail = head->get_next();
				delete head;
				head = tail;
			}
		}
		void set(size_t index, T data)
		{
			NodeOfList<T>* temp;
			temp = get_pointer(index);
			temp->set_data(data);
		}
		bool isEmpty()
		{
			if (!head)
				return true;
			else
				return false;
		}

	};



	template<typename T1, typename T2>
	class Map {

		Node<T1, T2>* root;

		void leftRotate(Node<T1, T2>* x) {
			Node<T1, T2>* nParent = x->right;
			if (x == root)
				root = nParent;
			x->moveDown(nParent);
			x->right = nParent->left;
			if (nParent->left != NULL)
				nParent->left->parent = x;
			nParent->left = x;

		}

		void rightRotate(Node<T1, T2>* x) {

			Node<T1, T2>* nParent = x->left;
			if (x == root)
				root = nParent;

			x->moveDown(nParent);
			x->left = nParent->right;
			if (nParent->right != NULL)
				nParent->right->parent = x;
			nParent->right = x;

		}



		void swapColors(Node<T1, T2>* x1, Node<T1, T2>* x2) {

			COLOR temp;

			temp = x1->color;

			x1->color = x2->color;

			x2->color = temp;

		}


		void swapkeyues(Node<T1, T2>* u, Node<T1, T2>* v) {

			int temp;

			temp = u->key;

			u->key = v->key;

			v->key = temp;

		}


		void fixRedRed(Node<T1, T2>* newElement) {


			if (newElement == root) {

				newElement->color = BLACK;

				return;

			}

			Node<T1, T2>* parent = newElement->parent, * grandparent = parent->parent,

				* uncle = newElement->uncle();



			if (parent->color != 1) {

				if (uncle != NULL && uncle->color == 0) {


					parent->color = BLACK;

					uncle->color = BLACK;

					grandparent->color = RED;

					fixRedRed(grandparent);

				}
				else {

					// Else perform LR, LL, RL, RR 

					if (parent->isOnLeft()) {

						if (newElement->isOnLeft()) {

							// for left right 

							swapColors(parent, grandparent);

						}
						else {

							leftRotate(parent);

							swapColors(newElement, grandparent);

						}

						// for left left and left right 

						rightRotate(grandparent);

					}
					else {

						if (newElement->isOnLeft()) {

							// for right left 

							rightRotate(parent);

							swapColors(newElement, grandparent);

						}
						else {

							swapColors(parent, grandparent);

						}



						// for right right and right left 

						leftRotate(grandparent);

					}

				}

			}

		}


		Node<T1, T2>* successor(Node<T1, T2>* x) {

			Node<T1, T2>* temp = x;



			while (temp->left != NULL)

				temp = temp->left;



			return temp;

		}



		Node<T1, T2>* BSTreplace(Node<T1, T2>* x) {
			if (x->left != NULL && x->right != NULL)
				return successor(x->right);
			if (x->left == NULL && x->right == NULL)
				return NULL;

			if (x->left != NULL)
				return x->left;
			else
				return x->right;

		}



		void deleteNode(Node<T1, T2>* v) {

			Node<T1, T2>* u = BSTreplace(v);



			// True when u and v are both 1 

			bool uv1 = ((u == NULL || u->color == 1) && (v->color == 1));

			Node<T1, T2>* parent = v->parent;



			if (u == NULL) {

				// u is NULL therefore v is leaf 

				if (v == root) {

					// v is root, making root null 

					root = NULL;

				}
				else {

					if (uv1) {

						// u and v both black 

						// v is leaf, fix double black at v 

						fixDoubleBlack(v);

					}
					else {

						// u or v is 0 

						if (v->sibling() != NULL)

							// sibling is not null, make it 0" 

							v->sibling()->color = RED;

					}



					// delete v from the tree 

					if (v->isOnLeft()) {

						parent->left = NULL;

					}
					else {

						parent->right = NULL;

					}

				}

				delete v;

				return;

			}



			if (v->left == NULL || v->right == NULL) {

				// v has 1 child 

				if (v == root) {

					// v is root, assign the keyue of u to v, and delete u 

					v->key = u->key;

					v->left = v->right = NULL;

					delete u;

				}
				else {

					// Detach v from tree and move u up 

					if (v->isOnLeft()) {

						parent->left = u;

					}
					else {

						parent->right = u;

					}

					delete v;

					u->parent = parent;

					if (uv1) {

						// u and v both 1, fix double 1 at u 

						fixDoubleBlack(u);

					}
					else {

						// u or v 0, color u 1 

						u->color = BLACK;

					}

				}

				return;

			}



			// v has 2 children, swap keyues with successor and recurse 

			swapkeyues(u, v);

			deleteNode(u);

		}



		void fixDoubleBlack(Node<T1, T2>* x) {

			if (x == root)

				// Reached root 

				return;



			Node<T1, T2>* sibling = x->sibling(), * parent = x->parent;

			if (sibling == NULL) {

				// No sibiling, double black pushed up 

				fixDoubleBlack(parent);

			}
			else {

				if (sibling->color == 0) {

					// Sibling red

					parent->color = RED;

					sibling->color = BLACK;

					if (sibling->isOnLeft()) {

						// left case 

						rightRotate(parent);

					}
					else {

						// right case 

						leftRotate(parent);

					}

					fixDoubleBlack(x);

				}
				else {

					// Sibling 1 

					if (sibling->has0Child()) {

						// at least 1 0 children 

						if (sibling->left != NULL && sibling->left->color == 0) {

							if (sibling->isOnLeft()) {

								// left left 

								sibling->left->color = sibling->color;

								sibling->color = parent->color;

								rightRotate(parent);

							}
							else {

								// right left 

								sibling->left->color = parent->color;

								rightRotate(sibling);

								leftRotate(parent);

							}

						}
						else {

							if (sibling->isOnLeft()) {

								// left right 

								sibling->right->color = parent->color;

								leftRotate(sibling);

								rightRotate(parent);

							}
							else {

								// right right 

								sibling->right->color = sibling->color;

								sibling->color = parent->color;

								leftRotate(parent);

							}

						}

						parent->color = BLACK;

					}
					else {

						// 2 1 children 

						sibling->color = RED;

						if (parent->color == 1)

							fixDoubleBlack(parent);

						else

							parent->color = BLACK;

					}

				}

			}

		}


	public:


		Map() { root = NULL; }

		~Map() { clear(root); 
		root = NULL;
		};

		Node<T1, T2>* getRoot() { return root; }
 

		Node<T1, T2>* find(T1 n) {

			Node<T1, T2>* temp = root;

			while (temp != NULL) {

				if (n < temp->key) {

					if (temp->left == NULL)

						break;

					else

						temp = temp->left;

				}
				else if (n == temp->key) {

					break;

				}
				else {

					if (temp->right == NULL)

						break;

					else

						temp = temp->right;

				}

			}



			return temp;

		}


		void insert(T1 key, T2 data) {

			Node<T1, T2>* newNode = new Node<T1, T2>(key, data);

			if (root == NULL) {

 

				newNode->color = BLACK;

				root = newNode;

			}
			else {

				Node<T1, T2>* temp = find(key);



				if (temp->key == key) {

					temp->data+=1;
					return;

				}



				newNode->parent = temp;



				if (key < temp->key)

					temp->left = newNode;

				else

					temp->right = newNode;

 

				fixRedRed(newNode);

			}

		}


		void remove(T1 n) {

			if (root == NULL)

				// Tree is empty 

				return;



			Node<T1, T2>* v = find(n), * u;



			if (v->key != n) {

				cout << "No Node<T1, T2> found to delete with keyue:" << n << endl;

				return;

			}



			deleteNode(v);

		}


		void printKey(Node<T1, T2>* root, int lvl)
		{
			if (root != NULL)
			{

				printKey(root->right, lvl + 2);

				for (int i = 0; i < lvl; i++)
				{

					cout << "  ";
				}
				if (root->parent != NULL && root->parent->key >= root->key)
				{
					if (root->color == 0)
						SetColor(12, 0);
					else
						SetColor(9, 0);
					cout << "\\" << root->key;

					cout << endl;
				}
				else if (root->parent != NULL && root->parent->key < root->key)
				{
					if (root->color == 0)
						SetColor(12, 0);
					else
						SetColor(9, 0);
					cout << "/" << root->key;

					cout << endl;
				}
				else
				{

					SetColor(9, 0);
					cout << root->key;
				}

				cout << endl;


				printKey(root->left, lvl + 2);
			}
		}

		void print(Node<T1, T2>* root, int lvl)
		{
			if (root != NULL)
			{

				print(root->right, lvl + 2);

				for (int i = 0; i < lvl; i++)
				{

					cout << "  ";
				}
				if (root->parent != NULL && root->parent->key >= root->key)
				{
					if (root->color == 0)
						SetColor(12, 0);
					else
						SetColor(9, 0);
					cout << "\\" << root->data;
				
					cout << endl;
				}
				else if (root->parent != NULL && root->parent->key < root->key)
				{
					if (root->color == 0)
						SetColor(12, 0);
					else
						SetColor(9, 0);
					cout << "/" << root->data;
				
					cout << endl;
				}
				else
				{
				
						SetColor(9, 0);
					cout << root->data;
				}

				cout << endl;


				print(root->left, lvl + 2);
			}
		}

		void getListAll(Node<T1, T2>* root, List<Node<T1, T2>*> &A)
		{
			if (root)
			{
				getListAll(root->left, A);
				getListAll(root->right, A);
				A.push_back(root);

			}
		
		}

		void getListTree(Node<T1, T2>* root, List<NodeOfTree*>& A)
		{
			if (root)
			{
				getListTree(root->left, A);
				getListTree(root->right, A);
				NodeOfTree* p = new NodeOfTree;
				p->c = root->key;
				p->a = root->data;
				A.push_back(p);
			}
		}

		List<T1>* getListKey(Node<T1, T2>* root, List<T1>* A)
		{
			if (root)
			{
				getListKey(root->left, A);
				getListKey(root->right, A);
				A->push_back(root->key);

			}
		
		
	
		
			return A;
		}

		List<T2>* getListData(Node<T1, T2>* root, List<T2>* A)
		{
			if (root)
			{
				getListData(root->left, A);
				getListData(root->right, A);
				A->push_back(root->data);

			}




			return A;
		}
	
		void printListKey(List<T1>* list)
		{
			while (!list->isEmpty())
			{
				cout << list->at(0);
				cout << endl;
				list->pop_front();
			}
		}

		void printListData(List<T2>* list)
		{
			while (!list->isEmpty())
			{
				cout << list->at(0);
				cout << endl;
				list->pop_front();
			}
		}

		void clear(Node<T1,T2>* root)
		{
			if (root)
			{
				clear(root->left);
				clear(root->right);
				 delete root;
			}
		}

	



	};

	void sortList(List<NodeOfTree*>& list)
	{
		NodeOfList<NodeOfTree*>* left = list.head;                 //Первый элемент — это пусть будет голова
		NodeOfList<NodeOfTree*>* right = list.head->get_next();          //Второй элемент — это пусть будет следующий за головой элемент

		NodeOfList<NodeOfTree*>* temp = new NodeOfList<NodeOfTree*>;              //Временное звено для хранения переставляемого всех значений переставляемого звена

		while (left->get_next()) {                 //Обходим по всем звеньям, за исключением крайнего правого
			while (right) {              //Обходим по всем звеньям, включая крайний правый (по всем относительно первого левого на текущий момент)
				if ((left->data->a) >= (right->data->a)) {        //Проверяем необходимость перестановки
					temp->data = left->data;              //И переставляем все внутренние элементы, за исключением указателей связи, местами
					left->data = right->data;             //Сейчас у нас имеется только x, поэтому только его
					right->data = temp->data;             //иначе бы  нужно было это проделывать для каждого несвязующего элемента
				}
				right = right->get_next();                    //не забываем направлять указатель на следующий элемент (по подобию инкремента), иначе цикл зависнет
			}
			left = left->get_next();                              //не забываем направлять указатель на следующий элемент (по подобию инкремента), иначе цикл зависнет
			right = left->get_next();                             //Поскольку второй указатель убежал немного вперёд, обязательно возвращаем его назад, это следующий элемент относительно текущего первого
		}
	}

	void BuildTree(List<NodeOfTree*>& tree)
	{
		while (tree.get_size() != 1)
		{
			sortList(tree);

			NodeOfTree* SonLeft = tree.head->data;
			tree.pop_front();
			NodeOfTree* SonRight = tree.head->data;
			tree.pop_front();
			NodeOfTree* parent = new NodeOfTree(SonLeft, SonRight);
			tree.push_back(parent);
		}
	}

	void BuildTable(NodeOfTree* root, Map<char, bool*>& table, List<bool> &listCode)
	{
	
		if (root->left != NULL)
		{
			listCode.push_back(false);
			BuildTable(root->left, table, listCode);
		}

		if (root->right != NULL)
		{
			listCode.push_back(true);
			BuildTable(root->right, table, listCode);
		}

		if (root->left == NULL && root->right == NULL)
		{
		
			table.find(root->c)->data=new bool[listCode.get_size()];
			for (int i = 0; i < listCode.get_size(); i++)
			{
				table.find(root->c)->data[i] = listCode.get_pointer(i)->data;
			}
	
		}
	
		if (listCode.isEmpty())
			return;
		listCode.pop_back();
	}

	void PrintTable(Node<char, bool*>* root)
	{
		int arrSize;
		if (root != NULL)
		{

			PrintTable(root->right);

		
				cout << root->key << " - simbol | code: ";
				arrSize = _msize(root->data) / sizeof(root->data[0]);
				for (int i = 0; i < arrSize; i++)
				{
					cout << root->data[i];
				}
				cout << endl;
	


			PrintTable(root->left);
		}
	}



	int main() {

		Map<char, int> map;
		//reading the string
		ifstream input;
		input.open("input.txt");

		char ch;

		Map<char, bool*> table;
		int MemoryCounter = 0;
		cout << "Entered string:" << endl;
		while (input.get(ch))
		{
			map.insert(ch, 1);
			cout << ch;
			MemoryCounter++;
			table.insert(ch, nullptr);
		}
		cout << endl;
		cout <<"Takes up memory:"<< MemoryCounter*8<<" bit."<<endl;
		input.close();
		float AspectRatio = (float)1/MemoryCounter;
		MemoryCounter = 0;

		List<NodeOfTree*> tree;

	
		map.getListTree(map.getRoot(), tree);
	

		BuildTree(tree);
	
			NodeOfTree* root = tree.head->data;
		
			List<bool> listCode;

			BuildTable(root, table, listCode);
			input.open("input.txt");
			int arrSize;
			cout << "Coded string: " << endl;
			while (input.get(ch))
			{
				arrSize = _msize(table.find(ch)->data) / sizeof(table.find(ch)->data[0]);
				MemoryCounter = MemoryCounter + arrSize;
				for (int i = 0; i < arrSize; i++)
					cout << table.find(ch)->data[i];
				cout << " ";
			}
			cout << endl;
			cout << "The encoded string takes up memory: " << MemoryCounter << " bit."<<endl;
			AspectRatio = AspectRatio * MemoryCounter * 100;
			cout << "AspectRatio = " <<(int)AspectRatio<<"%"<< endl << endl;
			PrintTable(table.getRoot());
	 

	

		return 0;
	}