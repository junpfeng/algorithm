// 树的前序、中序、后序、层序遍历方法
// 首先使用前序建立一颗树，分别使用上述四种方法遍历输出
#include <iostream>
#include <queue>
using std::queue;
struct BTNode
{
	int val;
	BTNode * left, *right;
	BTNode()
	{
		left = nullptr;
		right = nullptr;
	}
};
// 前序

void preTravsel(BTNode * root)
{
	if (root == nullptr)
		return;
	printf("%d,", root->val);
	preTravsel(root->left);
	preTravsel(root->right);
	return;
}
//
// 中序

void midTravsel(BTNode * root)
{
	if (root == nullptr)
		return;
	midTravsel(root->left);
	printf("%d,", root->val);
	midTravsel(root->right);
	return;
}
//
// 后序

void reaTravsel(BTNode * root)
{
	if (root == nullptr)
		return;
	reaTravsel(root->left);
	reaTravsel(root->right);
	printf("%d,", root->val);

	return;

}
//
// 层序

void levelTravsel(BTNode * root)
{
	if (root == nullptr)
		return;
	queue<BTNode *> mq;
	mq.push(root);
	while(!mq.empty())
	{
		BTNode * node = mq.front();
		mq.pop();
		printf("%d,", node->val);
		if (node->left != nullptr)
			mq.push(node->left);
		if (node->right != nullptr)
			mq.push(node->right);
	}
	return;
}


// 建立一颗树
BTNode * buildTree(int *& dat)
{
	if (dat == nullptr )
		return nullptr;

	if (*dat == 94) // '^'
		return nullptr;
	BTNode * root = new BTNode;
	root->val = *dat;
	root->left =  buildTree(++dat);
	root->right = buildTree(++dat);
	return root;
}


int main()
{
	int dat[] = {1,2,3,94,94,4,94,94,5,94,94};
	int * data = dat;
	BTNode * root = buildTree(data);
	preTravsel(root);
	printf("\n");
	midTravsel(root);
	printf("\n");
	reaTravsel(root);
	printf("\n");
	levelTravsel(root);
	printf("\n");
	return 0;
}
