#include <iostream>

// 二分法查找---基于有i序数列
// 也就是说无序数列，无法二分

int half_find(int * dat, int len, int ans)
{
	if (dat == nullptr || len <= 0)
		return -1;
	int begin = 0, end = len;
	while (begin <= end)
	{
		int mid = (begin + end)/2;
		if (dat[mid] == ans)
			return mid;
		else if (dat[mid] < ans)
			begin = mid + 1;
		else
			end = mid - 1;
	}
	return -1;
}

// 二叉查找树
// -- 建立（插入），查找，删除
// --要想使用二叉查找树，前提是数据都是存放在二叉查找树中的
struct BTNode
{
	int val;
	BTNode * left, * right;
	BTNode()
	{
		left = nullptr;
		right = nullptr;
	}
};
void InsertNode(BTNode*& root, int val)
{
	if (root == nullptr)
	{
		root = new BTNode;
		root->val = val;
		return;
	}
	else if (root->val > val)
		InsertNode(root->left, val);
	else
		InsertNode(root->right, val);

}
bool searchNode(BTNode * root, int val)
{
	if (root == nullptr)
		return false;
	if (val == root->val)
		return true;
	else if (val > root->val)
		searchNode(root->right, val);
	else
		searchNode(root->left, val);
}
// 哈希查找---使用除留余数法+链地址法/开放地址法之线性探测法
// 不同的处理冲突的方法对应了不同的查找算法
// 链地址法比较复杂，此处使用开放地址法
// 开放地址法需要保证哈希表的大小大于数据的总量
#define HASHSIZE 10
#define NULLKEY -32768
int hash(int key)
{
	return key%HASHSIZE;
}
// 初始化
int* initHash (const int size)
{
	if (size <= 0)
		return nullptr;

	int * hashtable = new int[size];
	for (int i = 0; i < size; i++)
		hashtable[i] = NULLKEY;
	return hashtable;
}

// 插入
bool insertHash(int * hashtable, const int key)
{
	int addr = hash(key);
	while (hashtable[addr] != NULLKEY)
	{
		// 线性探测开放地址会以此循环整个哈希表寻找可用的地址
		// 因此必须保证哈希表大于数据总大小，要不然就死循环了
		addr = ++addr%HASHSIZE;
	}

	hashtable[addr] = key;
}

// 搜索
int searchHash(int * hashtable, const int key)
{
	int addr = hash(key);
	while(hashtable[addr] != key)
	{
		addr = ++addr%HASHSIZE;
		// 探测到空白区域或者探测了一个循环
		if (hashtable[addr] == NULLKEY || addr == hash(key))
		{
			return -1;
		}
	}
	return addr;
}



int main()
{
	int dat[]  = {1,4,6,12,10};
	const int len = 5;
	// 哈希查找
	int *hashtable = nullptr;
	hashtable = initHash(HASHSIZE);	
	for (int i = 0; i < len; i++)
		insertHash(hashtable, dat[i]);
	printf("哈希查找%d\n",searchHash(hashtable, 10));


	// 插入搜索树
	BTNode * root = nullptr;
	for (int i = 0; i < len; i++)
		InsertNode(root, dat[i]);
	if (searchNode(root, 12) == 1)
		printf("树ok\n");

	//

	int index  = half_find(dat, len, 12);
	printf("二分法%d,\n", index);
	return 0;
}
