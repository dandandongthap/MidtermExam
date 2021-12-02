#include <iostream>
#include <vector>

struct Node
{
	int key;
	Node* left;
	Node* right;
};

class BST
{
public:
	BST();
	~BST();

	void printPreorder();
	void printInorder();
	void deleteBST();
	bool isBST();

private:
	Node* root;

	void printPreorder(Node*);
	void printInorder(Node*);
	void deleteBST(Node*);
	bool isBST(Node*, Node*, Node*);
	friend BST& toBalancedBST(std::vector<int>);
};

BST& toBalancedBST(std::vector<int> vec);

Node* createNode(int key);

Node* createBST(const std::vector<int>& vec, int left, int right);

void fillVector(std::vector<int>& vec);

void heapSort(std::vector<int>& vec);

void heapify(std::vector<int>& vec, int num, int index);

int main()
{
	int n = 0;

	std::cin >> n;

	std::vector<int> vec(n);

	fillVector(vec);

	BST& tree = toBalancedBST(vec);

	tree.printPreorder();
	std::cout << "\n";
	tree.printInorder();

	return 0;
}

BST& toBalancedBST(std::vector<int> vec)
{
	static BST tree;

	heapSort(vec);
	tree.root = createBST(vec, 0, static_cast<int>(vec.size()) - 1);
	return tree;
}

Node* createBST(const std::vector<int>& vec, int left, int right)
{
	if (right < left) return nullptr;

	int mid = left + (right - left) / 2;
	Node* root = createNode(vec.at(mid));

	root->left = createBST(vec, left, mid - 1);
	root->right = createBST(vec, mid + 1, right);
	return root;
}

Node* createNode(int key)
{
	Node* newNode = new Node{ key,nullptr,nullptr };

	return newNode;
}

BST::BST()
{
	root = nullptr;
}

BST::~BST()
{
	deleteBST();
}

void BST::printPreorder()
{
	printPreorder(root);
}

void BST::printInorder()
{
	printInorder(root);
}

void BST::deleteBST()
{
	deleteBST(root);
}

bool BST::isBST()
{
	return isBST(root, nullptr, nullptr);
}

void BST::printPreorder(Node* root)
{
	if (!root) return;

	std::cout << root->key << " ";
	printPreorder(root->left);
	printPreorder(root->right);
}

void BST::printInorder(Node* root)
{
	if (!root) return;

	printInorder(root->left);
	std::cout << root->key << " ";
	printInorder(root->right);
}

void BST::deleteBST(Node* root)
{
	if (!root) return;

	Node* currentNode = root;
	Node* leftNode = root->left;
	Node* rightNode = root->right;

	delete currentNode;
	currentNode = nullptr;

	deleteBST(leftNode);
	deleteBST(rightNode);
}

bool BST::isBST(Node* root, Node* min, Node* max)
{
	if (!root) return true;

	if (min && root->key <= min->key) return false;
	if (max && root->key >= max->key) return false;
	return isBST(root->left, min, root) && isBST(root->right, root, max);
}

void fillVector(std::vector<int>& vec)
{
	for (auto& input : vec)
	{
		std::cin >> input;
	}
}

void heapSort(std::vector<int>& vec)
{
	int size = static_cast<int>(vec.size());

	for (int i = size / 2 - 1; i >= 0; i--)
	{
		heapify(vec, size, i);
	}

	for (int i = size - 1; i > 0; i--)
	{
		std::swap(vec.at(0), vec.at(i));
		heapify(vec, i, 0);
	}
}

void heapify(std::vector<int>& vec, int num, int index)
{
	int largest = index;
	int left = 2 * index + 1;
	int right = left + 1;

	if (left < num && vec.at(left) > vec.at(largest))
	{
		largest = left;
	}
	if (right < num && vec.at(right) > vec.at(largest))
	{
		largest = right;
	}
	if (largest != index)
	{
		std::swap(vec.at(largest), vec.at(index));
		heapify(vec, num, largest);
	}
}