#include <iostream>

struct Node
{
	int key;
	Node* pNext;
};

typedef struct SinglyLinkedList
{
	Node* pHead;
	Node* pTail;
}List;

Node* initNode(int key);

void appendNode(List& L, int key);

void deleteHead(List& L);

void deleteList(List& L);

void printList(List& L);

Node* getMidNode(List& L);

Node* reverse(Node* head);

void updateTail(List& L);

void createList(List& L, int n);

void reorderList(List& L, int n);

int main()
{
	List L{ nullptr,nullptr };
	int n;

	std::cin >> n;
	createList(L, n);

	reorderList(L, n);
	printList(L);

	deleteList(L);

	return 0;
}

Node* initNode(int key)
{
	Node* newNode = new Node{ key,nullptr };

	return newNode;
}

void appendNode(List& L, int key)
{
	Node* newNode = initNode(key);

	if (!L.pHead)
	{
		L.pHead = L.pTail = newNode;
		return;
	}

	L.pTail->pNext = newNode;
	L.pTail = newNode;
}

void deleteHead(List& L)
{
	if (!L.pHead) return;

	Node* del = L.pHead;

	L.pHead = L.pHead->pNext;
	delete del;
	del = nullptr;
}

void deleteList(List& L)
{
	while (!L.pHead)
	{
		deleteHead(L);
	}
}

void printList(List& L)
{
	Node* current = L.pHead;

	while (current)
	{
		std::cout << current->key << " ";
		current = current->pNext;
	}
}

Node* getMidNode(List& L)
{
	if (!L.pHead) return nullptr;

	Node* slow = L.pHead;
	Node* fast = L.pHead;

	while (fast && fast->pNext)
	{
		slow = slow->pNext;
		fast = fast->pNext->pNext;
	}

	return slow;
}

Node* reverse(Node* head)
{
	Node* current = head;
	Node* previous = nullptr;
	Node* next = nullptr;

	while (current)
	{
		next = current->pNext;
		current->pNext = previous;
		previous = current;
		current = next;
	}
	return previous;
}

void updateTail(List& L)
{
	if (!L.pHead)
	{
		L.pTail = nullptr;
		return;
	}

	Node* current = L.pHead;

	while (current->pNext)
	{
		current = current->pNext;
	}
	L.pTail = current;
}

void createList(List& L, int n)
{
	int input = 0;

	for (int i = 0; i < n; i++)
	{
		std::cin >> input;
		appendNode(L, input);
	}
}

void reorderList(List& L, int n)
{
	Node* mid = getMidNode(L);

	mid = reverse(mid);

	Node* left = L.pHead;
	Node* right = mid;
	Node* temp = nullptr;

	for (int i = 0; i < n / 2; i++)
	{
		temp = left->pNext;
		left->pNext = right;
		right = right->pNext;
		left->pNext->pNext = temp;
		left = temp;
	}
	left->pNext = nullptr;

	updateTail(L);
}
