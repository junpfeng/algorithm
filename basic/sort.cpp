#include <iostream>

//-------------默认使用升序--------------
// 提供一个交换swap
void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
	return;
}

// 提供一个打印prints
void prints(int *dat, int len)
{
	if (dat == nullptr || len <=0 )
		return;
	for (int i = 0; i < len; i++)
		printf("%d,", dat[i]);
	printf("\n");
}
//---------------------------------------
// 选择排序---每次确定第一个位置的元素
void sort1(int *dat, int len)
{
	if(dat == nullptr || len <= 0)
		return;
	for (int i = 0; i < len - 1; i++)
		for (int j= i + 1; j < len; j++)
		{
			if (dat[i] > dat[j])
				swap(dat[i], dat[j]);
		}
	return;
}
// 冒泡排序---每次确定最后一个位置的元素
void sort2(int *dat, int len)
{
	if (dat == nullptr || len <= 0)
		return ;

	// 有几个元素就比较几轮(不过最后一次，只有一个元素，因此不需要再比较）
	for (int j = 0; j < len - 1; j++)
		// 将每个元素和后一个元素比较，从而确定最后一个
		for (int i = 0 ; i < len - j - 1; i++)
			if (dat[i] > dat[i + 1])
				swap(dat[i], dat[i + 1]);
	return;
}


// 插入排序---每次都确定第一个位置的冒泡
void sort3(int *dat, int len)
{
	if(dat == nullptr || len <= 0)
		return ;
	// 遍历整个数组
	for (int i = 0; i < len - 1; i++)
		// 从遍历点，往前冒泡
		for (int j = i; j >= 0; j--)
			if (dat[j] > dat[j + 1])
			{
				swap(dat[j], dat[j + 1]);
			}
	return;
}

//---------------------排序进阶----------------------------------

// 希尔排序（插入排序的改进）
//void sort4( int*dat, int len)
//{
//	int gap = len;
//	do
//	{
//		gap = len/2;
//		for (int i = gap; i < len; i++)
//		{
//
//		}
//	}
//}


// 快速排序

int partition(int *dat, int begin, int end)
{
	if (begin >= end)
		return begin;

	int key = dat[end];
	int index = end;
	end--;
	while(begin < end)
	{
		while(dat[begin] < key && begin < end)
		{
			begin++;
		}
		while(dat[end] > key && begin < end)
		{
			end--;
		}
		swap(dat[begin], dat[end]);
	}
	if (dat[begin] > key)
	{
		swap(dat[begin], dat[index]);
		return begin;
	}
	else
	{
		swap(dat[begin + 1], dat[index]);
		return begin + 1;
	}
}

void sort5core(int * dat, int begin, int end)
{
	if (begin < end)
	{
		int mid = partition(dat, begin, end);
		sort5core(dat, begin, mid - 1);
		sort5core(dat, mid + 1, end);
	}
}
void sort5(int *dat, int len)
{
	if (dat == nullptr || len <=0 )
		return ;
	return sort5core(dat, 0, len - 1);
}

// 堆排序（选择排序的改进）
void heapAdjust(int * dat, int nindx, int len)
{
	int tmp = dat[nindx];
	// 调整的时候，子上到下，依次调整
	// 2*nindx 是nindx的左孩子
	for (int i = 2*nindx; i <= len; i *= 2)
	{
		// 如果左孩子更大
		if (i < len && dat[i] < dat[i + 1])
			// 那么下一拨就调整左子树
			i++;
		// 但是，如果根节点的值更大，退出调整
		// 这是因为，是先由下而上，然后再由上而下，
		// 所以一旦在由上而下的时候，根大于叶子，那么下面的肯定都满足
		// 故不u需要再往下了
		if (tmp >= dat[i])
			break;

		dat[nindx] = dat[i]; // 大的孩子的值给父亲
		nindx = i; // 父亲的位置到了大孩子这儿
	}
	dat[nindx] = tmp; // 父亲最终找到了自己新 的位置，
	// 成为了其他人的孩子
}

void sort6(int *dat, int len)
{
	// 异常处理
	// --------
	dat--;
	// 从最后一个父亲节点往前调整成大顶堆
	for (int i = len/2; i >= 1; i--)
		heapAdjust(dat, i, len);
	// 开始将堆顶元素和最后的叶子值交换
	for (int i = len; i > 1; i--)
	{
		swap(dat[1], dat[i]);
		// 每次交换完了，请你调整一下堆
		heapAdjust(dat, 1, i - 1);
	}
	dat++;
}

//归并排序 (冒泡排序的改进)

void merge(int * d1, int l1, int * d2, int l2)
{
	const int len = l1 + l2;
	int buf[len];
	int index = 0;

	int ind1 = 0,ind2 = 0;

	while(ind1 < l1 || ind2 < l2)
	{
		if (ind1 == l1)
		{
			while(ind2 < l2)
				buf[index++] = d2[ind2++];
		}
		else if (ind2 == l2)
		{
			while(ind1 < l1)
				buf[index++] = d1[ind1++];
		}
		else if (d1[ind1] < d2[ind2])
		{
			buf[index++] = d1[ind1++];
		}
		else
		{
			buf[index++] = d2[ind2++];
		}
	}
	for (int i = 0; i < len; i++)
		d1[i] = buf[i];
	return;
}

void sort7(int *dat, int len)
{
	// 异常处理
	// -------
	// 每段的长度 <=1就没必要排了
	if (len > 1)
	{
		int *d1 = dat; // d1指向了dat，可以保证d1有dat那么长的内存
		int len1 = len/2;
		int *d2 = d1 + len1;
		int len2 = len - len1;

		sort7(d1, len1);
		sort7(d2, len2);

		merge(d1, len1, d2, len2);
	}
}


int main()
{
	int dat[] = {6,5,4,3,2,1};
	const int len = 6;
	int *ans = nullptr;
	sort1(dat, len);
	prints(dat, len);
	sort2(dat, len);
	prints(dat, len);
	sort3(dat, len);
	prints(dat, len);
	sort5(dat, len);
	prints(dat, len);
	sort6(dat, len);
	prints(dat, len);
	sort7(dat, len);
	prints(dat, len);

	return 0;

}
