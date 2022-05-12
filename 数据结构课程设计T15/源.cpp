#include<iostream>
using namespace std;
#include<queue>
#include<string>
int tolerance = 3;
struct booster
{
	int degradeToLeaf;
	int degradeFromParent;
	bool boosterHere;
	string pos;
};
template<class T>
class BinaryTreeNode {
public:
	booster element;
	int data;
	BinaryTreeNode* Lchild;
	BinaryTreeNode* Rchild;
public:
	BinaryTreeNode();
	BinaryTreeNode(int data,BinaryTreeNode* a,BinaryTreeNode* b);
	BinaryTreeNode(int data);
};
template<class T>
BinaryTreeNode<T>::BinaryTreeNode() {
	data = 0;
	Lchild = Rchild = NULL;
	element.boosterHere = false;
	element.degradeFromParent = 0;
	element.degradeToLeaf = 0;
	element.pos = "0";
}
template<class T>
BinaryTreeNode<T>::BinaryTreeNode(int data,BinaryTreeNode* a, BinaryTreeNode* b) {
	this->data = data;
	Lchild = a;
	Rchild = b;
	element.boosterHere = false;
	element.degradeFromParent = 0;
	element.degradeToLeaf = 0;
	element.pos = "0";
}
template<class T>
BinaryTreeNode<T>::BinaryTreeNode(int data) {
	this->data = data;
	Lchild = Rchild = NULL;
	element.boosterHere = false;
	element.degradeFromParent = 0;
	element.degradeToLeaf = 0;
	element.pos = "0";
}
template<class T>
class BinaryTree {
public:
	BinaryTreeNode<T>* root;
	int num;//���ڴ���ڵ�����
	BinaryTree() { root = NULL; }
	//ʹ�õ�AVL��ԭ����������
	void creatTree(int x,int y);
	//ʹ�ö�λ����������
	void creatTree2(string s,int pow);//pow��ÿ���ڵ��degraerFromparent����ֵ
	//���ڱ������㷨
	void preorder(BinaryTreeNode<T>* temp);
	void inorder(BinaryTreeNode<T>* temp);
	void postorder(BinaryTreeNode<T>* temp);
	void levelorder();
	void postorderForBooster(BinaryTreeNode<T>* temp);
	//���ڱ�������ʾ
	void displaypreorder();
	void displayinorder();
	void displaypostorder();
	void displaypostorderForBooster();
	//ͳ��Ҷ�ӽڵ����
	int countleaf(BinaryTreeNode<T>* temp,int& n);
	int n = 0;
	void displaycoutleaf() { int m =countleaf(root,n); cout << m << endl; }
	//�������ĸ߶�
	int highoftree(BinaryTreeNode<T>* temp);
	void displayhighoftree() { int b = highoftree(root); cout << "���ĸ߶�Ϊ" << b << endl; }
	//�����źŷŴ���
	void placeBooster(BinaryTreeNode<T>* temp);
	void levelorderTofindBooster();

};
template<class T>
void BinaryTree<T>::creatTree2(string s, int pow) {
	queue<int>cur;
	if (root == NULL) {
		BinaryTreeNode<T>* tee = new BinaryTreeNode<T>();
		tee->element.pos = s;
		tee->element.degradeFromParent = pow;
		root=tee;
	}
	else {
		BinaryTreeNode<T>* x = root;
		for (int i = 0; i < s.length() - 1; i++) {
			cur.push(s[i] - '0');
		}
		while (!cur.empty()) {
			int p = cur.front();
			cur.pop();
			if (p == 0) {
				x = x->Lchild;
			}
			else if (p == 1) {
				x = x->Rchild;
			}
		}
		BinaryTreeNode<T>* x1 = new BinaryTreeNode<T>();
		x1->element.degradeFromParent = pow;
		x1->element.pos = s;

		if ((s[s.length() - 1] - '0') == 0) {
			x->Lchild = x1;
		}
		else if ((s[s.length() - 1] - '0') == 1) {
			x->Rchild = x1;
		}
	}
	
	//��������0101..�ַ�����s��Ҫ�������һλ����Ϊ���һλҪ��������
}
template<class T>
void BinaryTree<T>::creatTree(int x,int y) {//�˷��������Ķ�������������avl����С�Ҵ���
	num += 1;
	BinaryTreeNode<T>* numb = new BinaryTreeNode<T>(x);
	numb->element.degradeFromParent = y;
	
	if (root == NULL) {
		root = numb;
	}
	else {
		BinaryTreeNode<T>* curr = root;
		//curr->element.degradeFromParent = y;
		BinaryTreeNode<T>* backtree = NULL;
		while (curr != NULL) {
			backtree = curr;
			if (x < curr->data) {
				curr = curr->Lchild;
			}
			else {
				curr = curr->Rchild;
			}
		}
		if (backtree->data > x) {
			backtree->Lchild = numb;
		}
		else {
			backtree->Rchild = numb;
		}
	}
}
template<class T>
void BinaryTree<T>::preorder(BinaryTreeNode<T>* temp) {
	if (temp != NULL) {
		cout << temp->data << " ";
		preorder(temp->Lchild);
		preorder(temp->Rchild);
	}
}
template<class T>
void BinaryTree<T>::inorder(BinaryTreeNode<T>* temp) {
	if (temp != NULL) {		
		inorder(temp->Lchild);
		cout << temp->data << " ";
		inorder(temp->Rchild);
	}
}
template<class T>
void BinaryTree<T>::postorder(BinaryTreeNode<T>* temp) {
	if (temp != NULL) {		
		postorder(temp->Lchild);
		postorder(temp->Rchild);
		cout << temp->data << " ";
	}
}
template<class T>
void BinaryTree<T>::placeBooster(BinaryTreeNode<T>* temp)
{
	temp->element.degradeToLeaf = 0;
	BinaryTreeNode<T>* y = temp->Lchild;
	if (y != NULL) {
		int degradation = y->element.degradeFromParent + y->element.degradeToLeaf;
		if (degradation > tolerance) {
			y->element.boosterHere = true;
			temp->element.degradeToLeaf = y->element.degradeFromParent;
		}
		else {
			temp->element.degradeToLeaf = degradation;
		}
	}
	y = temp->Rchild;
	if (y != NULL) {
		int degradation = y->element.degradeFromParent + y->element.degradeToLeaf;
		if (degradation > tolerance) {
			y->element.boosterHere = true;
			degradation = y->element.degradeFromParent;
		}
		if (temp->element.degradeToLeaf < degradation) {
			temp->element.degradeToLeaf = degradation;
		}
	}

}
template<class T>
void BinaryTree<T>::postorderForBooster(BinaryTreeNode<T>* temp)
{
	if (temp != NULL) {
		postorderForBooster(temp->Lchild);
		postorderForBooster(temp->Rchild);
		placeBooster(temp);

	}
}
template<class T>
void BinaryTree<T>::displaypostorderForBooster() {
	postorderForBooster(root);
	
}
template<class T>
void BinaryTree<T>::displaypreorder() {
	preorder(root);
	cout << endl;
}
template<class T>
void BinaryTree<T>::displayinorder() {
	inorder(root);
	cout << endl;
}
template<class T>
void BinaryTree<T>::displaypostorder() {
	postorder(root);
	cout << endl;
}
template<class T>
int BinaryTree<T>::countleaf(BinaryTreeNode<T>* temp,int& n) {
	if (temp == NULL)
		return 0;
	else {
		if (temp->Lchild == NULL && temp->Rchild == NULL)
			return n += 1;
		else {
			countleaf(temp->Lchild,n);
			countleaf(temp->Rchild,n);
		}
		return n;
	}
}
template<class T>
void BinaryTree<T>::levelorder() {
	BinaryTreeNode<T>* temp = root;
	if (temp == NULL) {
		return;
	}
	queue<BinaryTreeNode<T>*>que;
	que.push(temp);
	while (!que.empty()) {
		temp = que.front();
		que.pop();
		cout << temp->data << " ";
		if (temp->Lchild != NULL) {
			que.push(temp->Lchild);
		}
		if (temp->Rchild != NULL) {
			que.push(temp->Rchild);
		}
	}cout << endl;

}
template<class T>
void BinaryTree<T>::levelorderTofindBooster()
{
	BinaryTreeNode<T>* temp = root;
	if (temp == NULL) {
		return;
	}
	queue<BinaryTreeNode<T>*>que;
	queue<string>cur;//װ���źŷŴ���
	que.push(temp);
	while (!que.empty()) {
		temp = que.front();
		que.pop();
		if (temp->element.boosterHere == true) {
			cur.push(temp->element.pos);
		}
		
		if (temp->Lchild != NULL) {
			que.push(temp->Lchild);
		}
		if (temp->Rchild != NULL) {
			que.push(temp->Rchild);
		}
	}
	cout << "�źŷŴ�����λ������Ϊ��" << endl;
	while (!cur.empty()) {
		string op = cur.front();
		int level = 0;
		cur.pop();
		if (op.length() == 1) { level = 1; }
		if (op.length() == 2) { level = 2; }
		if (op.length() == 3) { level = 3; }
		if (op.length() == 4) { level = 4; }
		if (op.length() == 5) { level = 5; }
		if (op.length() == 6) { level = 6; }
		cout << "��" << level << "�㣬λ��Ϊ" << op << endl;
	}
}
template<class T>
int BinaryTree<T>::highoftree(BinaryTreeNode<T>* temp) {
	if (temp == NULL) {
		return 0;
	}
	else {
		int hl = highoftree(temp->Lchild);
		int hr = highoftree(temp->Rchild);
		return hl > hr ? hl + 1 : hr + 1;
	}
}
void change(int a) {
	tolerance = a;
}


int main()
{
	
	cout << "-----------------------------------------------�źŷŴ���-----------------------------------------------------------"<<endl;
	cout << "ʹ��˵��������ÿ���ڵ��λ����01����ʾ��0��ʾ��1��ʾ�ҡ�"<<endl;
	cout << "�������ͨ����������ÿ�����ĺķ�ֵ�����ýڵ��degradeFromparentֵ���͸ýڵ��λ�ã���0101��ʾ��"<<endl;
	cout << "           �磺���ڵ�ĵ�һ�����ӽڵ�ķ�ֵΪ1�������� 1��0���س��� ���ڵ�Ϊ0��root���س��������롰finish����ʾ����"<<endl;
	cout << "--------------------------------------------------------------------------------------------------------------------"<<endl;
	cout << "�밴��Ҫ�����벢������������"<<endl;
	BinaryTree<int>* d = new BinaryTree<int>();
	cout << "������һ������ֵ��";
	int mg = 0;
	cin >> mg;
	change(mg);
	string test;
	int nub01;
	string nub02;
	cin >> test;
	while (test != "finish") {
		nub01 = test[0] - '0';
		nub02 = test.substr(2);//��ȡ���±�2��ĩβ�Ķ���
		d->creatTree2(nub02, nub01);
		cin >> test;
	}
	d->displaypostorderForBooster();
	d->levelorderTofindBooster();
	system("pause");
	return 0;
}



