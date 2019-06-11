// 对于链表的操作
// 1. 建立双向链表、单向链表、
// 2. 建立带环链表并判断环的位置
// 3. 单向链表反转
#include  <iostream>
// 单向链表节点的数据结构
struct Node{
    int val;
    Node *Next;
    Node ()
    {
        Next = nullptr;
    }
};

// 建立单项链表
Node * buildList(int *dat, int len)
{
    if (dat == nullptr || len <= 0)
    return nullptr;
    Node * head = new Node;
    Node * tmp = head;
    for (int i = 0; i < len; ++i)
    {
        tmp->Next = new Node;
        tmp->Next->val = dat[i];
        tmp = tmp->Next;
    }
    tmp = head;
    head = head->Next;
    delete tmp;
    tmp = nullptr;
    return head;
}


// 打印
void prints(Node *head)
{
    if (head == nullptr)
    return;
    Node *tmp = head;
    while(tmp != nullptr)
    {
        printf("%d,",tmp->val);
        tmp = tmp->Next;
    }
    printf("\n");
}

// 反转
Node * reverse(Node *head)
{
    if (head == nullptr)
        return nullptr;
    Node * pre = nullptr;
    Node * cur = head;
    Node * Nex = head->Next;
    while(Nex != nullptr)
    {
        cur->Next = pre;
        pre = cur;
        cur = Nex;
        Nex = Nex->Next;
    }
    cur->Next = pre; // 这一步很关键
    return cur;
}
// 加环和找环

// 加环

#define INDEX 3 // 定义加环的位置

void addloop(Node *head)
{
    Node *tmp = head;
    int index= INDEX;
    while(head != nullptr&&index != 0)
    {
        index--;
        tmp = tmp->Next;
    }
    Node * end = tmp;
    while(end->Next != nullptr)
    {
        end = end->Next;
    }
    end->Next = tmp;
}



// 快慢指针只能判断是否有环，不能找到环的入口
// 要想判断环的入口，还需要先后指针，当找到环后，循环一圈
// 确定环的长度为n个节点，然后p1指针先走n个节点，
// 接下来p2和p1同时出发，当两个指针相遇时，即环入口
bool findloop(Node *head)
{
    if (head == nullptr)
        return false;
    Node * fast = head;
    Node * low = head;
    while(fast->Next != nullptr && fast != nullptr)
    {
        low = low->Next;
        fast = fast->Next->Next;
        if (low == fast)
            return true;
    }
    return false;
}



int main()
{
	int dat[] = {1,2,3,4,5,6};
	const int len = 6;
	Node * head = buildList(dat, len);
	prints(head);
	head = reverse(head);
	prints(head);
//
	addloop(head);
	bool ans = findloop(head);
	std::cout << ans << std::endl;	
	return 0;
}
