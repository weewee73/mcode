#include <stdio.h>

#define N 10
#define MAX 0x7FFFFFFF

void swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void print(int a[], int n)
{
	int i;

	for (i=0; i<n-1; i++)
	{
		printf("%d, ", a[i]);
	}
	printf("%d\n", a[i]);
}

void select_sort(int a[], int n)
{
	int i, j, min;

	for (i=0; i<n; i++)
	{
		min = i;
		
		for (j=i+1; j<n; j++)
		{
			if (a[j] < a[min])
				min = j;
		}

		swap(&a[i], &a[min]);
	}
}

void insert_sort(int a[], int n)
{
	int i, j, curr;

	for (i=1; i<n; i++)
	{
		curr = a[i];

		for (j=i-1; a[j]>curr && j>=0; j--)
		{
			a[j+1] = a[j];
		}

		a[j+1] = curr;
	}
}

void bubble_sort(int a[], int n)
{
	int i, j;

	for (i=n-1; i>=0; i--)
	{
		for (j=0; j<i; j++)
		{
			if (a[j] > a[j+1])
				swap(&a[j], &a[j+1]);
		}
	}
}

int partition_2(int a[], int low, int high)
{
	int x = a[low];

	while (low < high)
	{
		while (a[high] >= x && low < high) high--;
		swap(&a[low], &a[high]);

		while (a[low] < x && low < high) low++;
		swap(&a[low], &a[high]);
	}

	return low;
}
int partition_1(int a[], int low, int high)
{
	int x = a[low];

	while (low < high)
	{
		//a[high]<x move to low
		while (a[high] >= x && low < high) high--;
		a[low] = a[high];

		//a[low]>x move to high
		while (a[low] <= x && low < high) low++;
		a[high] = a[low];
	}

	a[low] = x;	

	return low;
}
int partition(int a[], int low, int high)
{
	//low..j-1(<x), j(=x), j+1..high(>x)
	int x = a[low];
	int i, j = low;

	for (i=low+1; i<=high; i++)
	{
		if (a[i] < x)
		{
			swap(&a[++j], &a[i]);
		}
	}
	swap(&a[j], &a[low]);

	return j;
}

void qsort(int a[], int low, int high)
{
	int k;

	if (low < high)
	{
		k = partition_1(a, low, high);
		//k = partition(a, low, high);
		
		qsort(a, low, k-1);
		qsort(a, k+1, high);
	}
}

void quick_sort(int a[], int n)
{
	qsort(a, 0, n-1);
}

merge(int a[], int s1, int s2, int end)
{
	int i, *p, *p1, *p2, a1[N], a2[N];

	for (p1=a1, p=a+s1; p<a+s2; p1++,p++)
		*p1 = *p;
	*p1 = MAX; 
	for (p2=a2, p=a+s2; p<=a+end; p2++,p++)
		*p2 = *p;
	*p2 = MAX; 

	p = a+s1, p1 = a1, p2 = a2;
	while (p<=a+end)
	{
		if(*p1 < *p2)
			*p++ = *p1++;
		else
			*p++ = *p2++;
	}

}

void msort(int a[], int low, int high)
{
	int mid;
	if (low >= high) return;

	mid = (low + high) / 2;

	msort(a, low, mid);
	msort(a, mid+1, high);

	merge(a, low, mid+1, high);
}

void merge_sort(int a[], int n)
{
	msort(a, 0, n-1);
}

void shell_sort(int a[], int n)
{
}


void test()
{
	int a[][N] = {{5,2,4,6,1,3,23,13,10,100},
                  {6,6,4,6,1,3,23,6,6,10},
                  {52,32,4,68,21,3,32,13,10,40},
                  {19,89,4,60,1,8,23,13,10,13},
                  {35,12,4,46,1,3,2,13,100,18}
	           };
		 
	int i;

	for (i=0; i<5; i++)
	{
		printf("Before sort:  ");
		print(a[i], N);

		//insert_sort(a[i], N);
		//select_sort(a[i], N);
		//bubble_sort(a[i], N);
		//quick_sort(a[i], N);
		merge_sort(a[i], N);

		printf("After  sort:  ");
		print(a[i], N);
	}
}

int main()
{
	test();
	return 0;
}
