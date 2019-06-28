#include<iostream>
#include<stdlib.h>
#include<omp.h>
#include<time.h>

using namespace std;

void mergeSort(int a[], int i, int j);
void merge(int a[], int i1, int j1,  int i2, int j2);


void mergeSort(int a[], int i, int j)
{
	int mid;
	if(i < j)
	{
		mid = (i + j) / 2;

		#pragma omp parallel sections
		{
			#pragma omp section
			{
				mergeSort(a, i, mid);
			}

			#pragma omp section
			{
				mergeSort(a, mid + 1, j);
			}

		}

		mergeSort(a, i, mid);
	}
}

void merge(int a[], int i1, int j1, int i2, int j2)
{
	int temp[1000], i, j, k;
	i = i1;
	j = i2;
	k = 0;

	while(i <= j1 && j <= j2)
	{
		if(a[i] < a[j])
		{
			temp[k++] = a[i++];
		}
		else
		{
			temp[k++] = a[j++];
		}
	}

	while(i <= j1)
	{
		temp[k++] = a[i++];
	}

	while(j <= j2)
	{
		temp[k++] = a[j++];
	}

	for(i=i1, j=0; i <= j2; i++, j++)
	{
		a[i] = temp[j];
	}
}


int main()
{
	clock_t start = clock();
	int *a, n, i;
	cout << "\nEnter total number of elements:";
	cin >> n;
	a = new int[n];
	cout << "\nEnter elements:\n";
	for(i = 0; i < n; ++i)
		cin >> a[i];

	mergeSort(a, 0, n - 1);

	cout << "\nSorted array :";
		cout << " " << a[i] << endl;

	clock_t end = clock();
	cout << "\nTotal running time:" << double(end - start) << endl;

return 0;
}		


















































