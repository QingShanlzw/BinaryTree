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
	int num;//用于储存节点数；
	BinaryTree() { root = NULL; }
	//使用的AVL的原理来生成树
	void creatTree(int x,int y);
	//使用定位法来生成树
	void creatTree2(string s,int pow);//pow是每个节点的degraerFromparent的数值
	//用于遍历的算法
	void preorder(BinaryTreeNode<T>* temp);
	void inorder(BinaryTreeNode<T>* temp);
	void postorder(BinaryTreeNode<T>* temp);
	void levelorder();
	void postorderForBooster(BinaryTreeNode<T>* temp);
	//用于遍历的演示
	void displaypreorder();
	void displayinorder();
	void displaypostorder();
	void displaypostorderForBooster();
	//统计叶子节点个数
	int countleaf(BinaryTreeNode<T>* temp,int& n);
	int n = 0;
	void displaycoutleaf() { int m =countleaf(root,n); cout << m << endl; }
	//计算树的高度
	int highoftree(BinaryTreeNode<T>* temp);
	void displayhighoftree() { int b = highoftree(root); cout << "树的高度为" << b << endl; }
	//放置信号放大器
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
	
	//这里输入0101..字符串的s里要保留最后一位，因为最后一位要单独看。
}
template<class T>
void BinaryTree<T>::creatTree(int x,int y) {//此方法构建的二叉树是类似于avl的左小右大树
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
	queue<string>cur;//装载信号放大器
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
	cout << "信号放大器的位置依次为：" << endl;
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
		cout << "第" << level << "层，位置为" << op << endl;
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
	
	cout << "-----------------------------------------------信号放大器-----------------------------------------------------------"<<endl;
	cout << "使用说明：树中每个节点的位置用01来表示，0表示左，1表示右。"<<endl;
	cout << "输入规则：通过输入树的每个结点的耗费值（即该节点的degradeFromparent值）和该节点的位置（用0101表示）"<<endl;
	cout << "           如：根节点的第一个左子节点耗费值为1，即输入 1，0（回车） 根节点为0，root（回车），输入“finish”表示结束"<<endl;
	cout << "--------------------------------------------------------------------------------------------------------------------"<<endl;
	cout << "请按照要求输入并创建二叉树："<<endl;
	BinaryTree<int>* d = new BinaryTree<int>();
	cout << "请输入一个容忍值：";
	int mg = 0;
	cin >> mg;
	change(mg);
	string test;
	int nub01;
	string nub02;
	cin >> test;
	while (test != "finish") {
		nub01 = test[0] - '0';
		nub02 = test.substr(2);//截取从下表2到末尾的东西
		d->creatTree2(nub02, nub01);
		cin >> test;
	}
	d->displaypostorderForBooster();
	d->levelorderTofindBooster();
	system("pause");
	return 0;
}



