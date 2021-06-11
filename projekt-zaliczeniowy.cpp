#include <iostream>
#include <time.h>
//#include <cstdlib>

using namespace std;

// Należy stworzyć listę jednostronnie wiązaną elementów posortowanych, odwrotnie posortowanych oraz przypadkowych o długości 100, 1000, 10000.
// Zaimplementować sortowanie MergeSort, CombSort, BoobleSort, InsertSort na liście jednostronnie wiązanej. 
// Pokazać wyniki w postaci czasu w milisekundach dla każdego z tych sortowań oraz każdego typu tablicy.

struct node {
	int val;
	node *next;
};

void add(node*& H, int x) {
	node* p = new node;
	p->val = x;
	p->next = H;
	H = p;
}

void show(node *H) {
	node* p = H;
	cout << "HEAD->";
	while (p != NULL) {
		cout << p->val << "->";
		p = p->next;
	}
	cout << "NULL" << endl << endl;
}

void deleteNode(node*& H) {
	if (H != NULL) {
		node *p = H;
		H = p->next;
		delete p;
	}
}

// create list of sorted numbers
void createSortedList(node*& H, int range) {
	for (int i = range; i > 0; i--) {
		add(H, i);
	}
}

// create list of reverse sorted numbers
void createReverseSortedList(node*& H, int range) {
	for (int i = 1; i <= range; i++) {
		add(H, i);
	}
}

// generate random number
int generateRandomNumber(int range) {
	int number = rand() % range + 1;
	return number;
}

// create list of random numbers
void createRandomList(node*& H, int range) {
	for (int i = 0; i < range; i++) {
		add(H, generateRandomNumber(range));
	}
}

// mergesort implementation
void divide(node*& H, node*& H1, node*& H2) {
	if (H != NULL) {
		node* p = H;
		int noOfNodes = 0;
		while (p != NULL) {
			p = p->next;
			noOfNodes++;
		}
		H1 = H;
		p = H;
		for (int i = 0; i < noOfNodes / 2 - 1; i++)
			p = p->next;
		H2 = p->next;
		p->next = NULL;
		H = NULL;
	}
}

void merge(node*& H1, node*& H2, node*& H) {
	add(H, 0);
	node* T = H;
	while (H1 && H2) {
		if (H1->val < H2->val) {
			T->next = H1;
			H1 = H1->next;
			T = T->next;
		}
		else {
			T->next = H2;
			H2 = H2->next;
			T = T->next;
		}
	}
	if (!H1) {
		T->next = H2;
		H2 = NULL;
	}
	else {
		T->next = H1;
		H1 = NULL;
	}
	deleteNode(H);
}

void mergeSort(node*& H) {
	if (H && H->next) {
		node* H1 = NULL;
		node* H2 = NULL;
		divide(H, H1, H2);
		mergeSort(H1);
		mergeSort(H2);
		merge(H1, H2, H);
	}
}

// bubblesort implementation
// changing values version
void swapVal(node *p1, node *p2) {
	int temp = p1->val;
	p1->val = p2->val;
	p2->val = temp;
}

void bubbleSortVal(node*& H) {
	if (!H || !H->next) {
		return;
	}
	else {
		bool swapped = 1;
		node *p = NULL;
		node *p1 = NULL;

		while (swapped) {
			swapped = 0;
			p = H;

			while (p->next != p1) {
				if (p->val > p->next->val) {
					swapVal(p, p->next);
					swapped = 1;
				}
				p = p->next;
			}
			p1 = p;
		}
	}
}

// changing nodes version

node* swap(node *p1, node *p2) {
	node* temp = p2->next;
	p2->next = p1;
	p1->next = temp;
	return p2;
}

void bubbleSort(node*& H) {
	if (!H || !H->next) {
		return;
	}
	else {
		add(H, 0);
		int counter = 1;
		bool swapped = 1;
		bool swappedPredecessor = 0;
		bool jumpGuard = 0;
		bool isMonotonous = 0;
		node *p = NULL;
		node *p1 = NULL;
		node *p2 = NULL;
		node *p3 = NULL;
		node *lastSwap = NULL;
		while (swapped) {
			swapped = 0;
			jumpGuard = 0;
			p = H;
			p3 = H;
			while (p->next != p1) {
				// swap
				if (p->val > p->next->val) {
					p2 = swap(p, p->next);
					p3->next = p2;
					swapped = 1;
					swappedPredecessor = 1;
					lastSwap = p;
				}
				// be 'p' one node ahead of a guard (first step)
				if (swapped == 0)
					p = p->next;
				// move p3 after swap
				if (jumpGuard == 1 && swapped == 1 && swappedPredecessor == 1)
					p3 = p2;
				// move p3 after p (second step)
				if (jumpGuard == 1 && swapped == 0)
					p3 = p3->next;
				// move both pointers if val1 < val2
				if (p->next != p1 && jumpGuard == 1 && p->val <= p->next->val) {
					p = p->next;
					p3 = p3->next;
				}
				jumpGuard = 1;
				swappedPredecessor = 0;
			}
			p1 = lastSwap;
			//cout << "lastSwap->val: " << lastSwap->val << endl;
			//cout << "p1->val: " << p1->val << endl;
		}
		deleteNode(H);
	}
}

// combsort implementation

void combSort(node*& H, int noOfElems) {
	if (!H || !H->next) {
		return;
	}
	add(H, 0);

	node* p = NULL;
	node* p1 = NULL;
	node* tmp = NULL;
	node* tmp1 = NULL;

	int gap = noOfElems;
	bool swapped = 1;
	bool jumpGap = 0;

	while (gap != 1) {
		gap /= 1.3;
		//cout << gap << endl;
		if (gap == 0) {
			gap = 1;
		}

		if (gap == 1)
			break;

		p = H;
		p1 = H;
		jumpGap = 0;
		swapped = 0;

		for (int i = 0; i < noOfElems - gap; i++) {

			if (jumpGap == false) {
				for (int i = 0; i < gap; i++) {
					p1 = p1->next;
				}
			}
			jumpGap = true;

			if (p->next->val > p1->next->val) {

				tmp1 = p1->next->next;
				tmp = p->next;

				p1->next->next = p->next->next;
				p->next->next = tmp1;
				p->next = p1->next;
				p1->next = tmp;

				tmp = NULL;
				tmp1 = NULL;
				p = p->next;
				p1 = p1->next;
				//cout << "p: " << p->val << endl;
				//cout << "p1: " << p1->val << endl;
			}
			else {
				p = p->next;
				p1 = p1->next;
				//cout << "p: " << p->val << endl;
				//cout << "p1: " << p1->val << endl;
			}
		}
	}
	//show(H);
	deleteNode(H);
	bubbleSort(H);
}

// insertsort implementation
void insert(node* p, node* guard, node* pNext) {

	node* temp = guard;
	node* temp1 = guard;
	bool jumpGuard = 0;

	while (temp->val < pNext->val) {
		temp = temp->next;
		if (jumpGuard)
			temp1 = temp1->next;
		jumpGuard = 1;
	}
	temp1->next = pNext;
	pNext->next = temp;
}

node* insertReturnNext(node *p) {
	return p->next;
}

void insertSort(node*& H) {
	if (!H || !H->next) {
		return;
	}

	add(H, 0);
	node* p = H;
	node* guard = H;
	node* pNext = NULL;

	while (p->next != NULL) { 
		if (p->val > p->next->val) {
			pNext = insertReturnNext(p);
			p->next = pNext->next;
			insert(p, guard, pNext);
		}
		else {
			p = p->next;
		}
	}	
	deleteNode(H);
}

// variables used to calculate execution time
clock_t start, stop;
double executionTime;

int main() {
	srand(time(NULL)); // random number generator (RNG)

	// initializing lists
	node* test = NULL;
	node* H_100_SortedMergeSort = NULL;
	node* H_1000_SortedMergeSort = NULL;
	node* H_10000_SortedMergeSort = NULL;
	node* H_100_ReverseSortedMergeSort = NULL;
	node* H_1000_ReverseSortedMergeSort = NULL;
	node* H_10000_ReverseSortedMergeSort = NULL;
	node* H_100_RandomMergeSort = NULL;
	node* H_1000_RandomMergeSort = NULL;
	node* H_10000_RandomMergeSort = NULL;
	// ---------------------------------------
	node* H_100_SortedCombSort = NULL;
	node* H_1000_SortedCombSort = NULL;
	node* H_10000_SortedCombSort = NULL;
	node* H_100_ReverseSortedCombSort = NULL;
	node* H_1000_ReverseSortedCombSort = NULL;
	node* H_10000_ReverseSortedCombSort = NULL;
	node* H_100_RandomCombSort = NULL;
	node* H_1000_RandomCombSort = NULL;
	node* H_10000_RandomCombSort = NULL;
	// ---------------------------------------
	node* H_100_SortedBubbleSort = NULL;
	node* H_1000_SortedBubbleSort = NULL;
	node* H_10000_SortedBubbleSort = NULL;
	node* H_100_ReverseSortedBubbleSort = NULL;
	node* H_1000_ReverseSortedBubbleSort = NULL;
	node* H_10000_ReverseSortedBubbleSort = NULL;
	node* H_100_RandomBubbleSort = NULL;
	node* H_1000_RandomBubbleSort = NULL;
	node* H_10000_RandomBubbleSort = NULL;
	// ---------------------------------------
	node* H_100_SortedInsertSort = NULL;
	node* H_1000_SortedInsertSort = NULL;
	node* H_10000_SortedInsertSort = NULL;
	node* H_100_ReverseSortedInsertSort = NULL;
	node* H_1000_ReverseSortedInsertSort = NULL;
	node* H_10000_ReverseSortedInsertSort = NULL;
	node* H_100_RandomInsertSort = NULL;
	node* H_1000_RandomInsertSort = NULL;
	node* H_10000_RandomInsertSort = NULL;

	// ** add nodes to lists **
	createSortedList(H_100_SortedMergeSort, 100);
	createSortedList(H_1000_SortedMergeSort, 1000);
	createSortedList(H_10000_SortedMergeSort, 10000);
	createReverseSortedList(H_100_ReverseSortedMergeSort, 100);
	createReverseSortedList(H_1000_ReverseSortedMergeSort, 1000);
	createReverseSortedList(H_10000_ReverseSortedMergeSort, 10000);
	createRandomList(H_100_RandomMergeSort, 100);
	createRandomList(H_1000_RandomMergeSort, 1000);
	createRandomList(H_10000_RandomMergeSort, 10000);
	// ---------------------------------------
	createSortedList(H_100_SortedCombSort, 100);
	createSortedList(H_1000_SortedCombSort, 1000);
	createSortedList(H_10000_SortedCombSort, 10000);
	createReverseSortedList(H_100_ReverseSortedCombSort, 100);
	createReverseSortedList(H_1000_ReverseSortedCombSort, 1000);
	createReverseSortedList(H_10000_ReverseSortedCombSort, 10000);
	createRandomList(H_100_RandomCombSort, 100);
	createRandomList(H_1000_RandomCombSort, 1000);
	createRandomList(H_10000_RandomCombSort, 10000);
	// ---------------------------------------
	createSortedList(H_100_SortedBubbleSort, 100);
	createSortedList(H_1000_SortedBubbleSort, 1000);
	createSortedList(H_10000_SortedBubbleSort, 10000);
	createReverseSortedList(H_100_ReverseSortedBubbleSort, 100);
	createReverseSortedList(H_1000_ReverseSortedBubbleSort, 1000);
	createReverseSortedList(H_10000_ReverseSortedBubbleSort, 10000);
	createRandomList(H_100_RandomBubbleSort, 100);
	createRandomList(H_1000_RandomBubbleSort, 1000);
	createRandomList(H_10000_RandomBubbleSort, 10000);
	// ---------------------------------------
	createSortedList(H_100_SortedInsertSort, 100);
	createSortedList(H_1000_SortedInsertSort, 1000);
	createSortedList(H_10000_SortedInsertSort, 10000);
	createReverseSortedList(H_100_ReverseSortedInsertSort, 100);
	createReverseSortedList(H_1000_ReverseSortedInsertSort, 1000);
	createReverseSortedList(H_10000_ReverseSortedInsertSort, 10000);
	createRandomList(H_100_RandomInsertSort, 100);
	createRandomList(H_1000_RandomInsertSort, 1000);
	createRandomList(H_10000_RandomInsertSort, 10000);

	// ** MergeSort ** *******************************************************************************************************************

	// ** sorted lists **
	//show(H_100_SortedMergeSort);
	start = clock();
	mergeSort(H_100_SortedMergeSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "MergeSort - sorted list of 100 elements: " << executionTime << " ms" << endl;
	//show(H_100_SortedMergeSort);
	//show(H_1000_SortedMergeSort);
	start = clock();
	mergeSort(H_1000_SortedMergeSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "MergeSort - sorted list of 1000 elements: " << executionTime << " ms" << endl;
	//show(H_1000_SortedMergeSort);
	//show(H_10000_SortedMergeSort);
	start = clock();
	mergeSort(H_10000_SortedMergeSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "MergeSort - sorted list of 10000 elements: " << executionTime << " ms" << endl;
	//show(H_10000_SortedMergeSort);

	// ** reverse sorted lists **
	//show(H_100_ReverseSortedMergeSort);
	start = clock();
	mergeSort(H_100_ReverseSortedMergeSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "MergeSort - reverse sorted list of 100 elements: " << executionTime << " ms" << endl;
	//show(H_100_ReverseSortedMergeSort);
	//show(H_1000_ReverseSortedMergeSort);
	start = clock();
	mergeSort(H_1000_ReverseSortedMergeSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "MergeSort - reverse sorted list of 1000 elements: " << executionTime << " ms" << endl;
	//show(H_1000_ReverseSortedMergeSort);
	//show(H_10000_ReverseSortedMergeSort);
	start = clock();
	mergeSort(H_10000_ReverseSortedMergeSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "MergeSort - reverse sorted list of 10000 elements: " << executionTime << " ms" << endl;
	//show(H_10000_ReverseSortedMergeSort);

	// ** random lists **
	//show(H_100_RandomMergeSort);
	start = clock();
	mergeSort(H_100_RandomMergeSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "MergeSort - random sorted list of 100 elements: " << executionTime << " ms" << endl;
	//show(H_100_RandomMergeSort);
	//show(H_1000_RandomMergeSort);
	start = clock();
	mergeSort(H_1000_RandomMergeSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "MergeSort - random sorted list of 1000 elements: " << executionTime << " ms" << endl;
	//show(H_1000_RandomMergeSort);
	//show(H_10000_RandomMergeSort);
	start = clock();
	mergeSort(H_10000_RandomMergeSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "MergeSort - random sorted list of 10000 elements: " << executionTime << " ms" << endl;
	//show(H_10000_RandomMergeSort);

	cout << "----------------------------------------------------------------------------------" << endl;
	// ** CombSort ** *******************************************************************************************************************

	// ** sorted lists **
	//show(H_100_SortedCombSort);
	start = clock();
	combSort(H_100_SortedCombSort, 100);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "CombSort - sorted list of 100 elements: " << executionTime << " ms" << endl;
	//show(H_100_SortedCombSort);
	//show(H_1000_SortedCombSort);
	start = clock();
	combSort(H_1000_SortedCombSort, 1000);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "CombSort - sorted list of 1000 elements: " << executionTime << " ms" << endl;
	//show(H_1000_SortedCombSort);
	//show(H_10000_SortedCombSort);
	start = clock();
	combSort(H_10000_SortedCombSort, 10000);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "CombSort - sorted list of 10000 elements: " << executionTime << " ms" << endl;
	//show(H_10000_SortedCombSort);

	// ** reverse sorted lists **
	//show(H_100_ReverseSortedCombSort);
	start = clock();
	combSort(H_100_ReverseSortedCombSort, 100);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "CombSort - reverse sorted list of 100 elements: " << executionTime << " ms" << endl;
	//show(H_100_ReverseSortedCombSort);
	//show(H_1000_ReverseSortedCombSort);
	start = clock();
	combSort(H_1000_ReverseSortedCombSort, 1000);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "CombSort - reverse sorted list of 1000 elements: " << executionTime << " ms" << endl;
	//show(H_1000_ReverseSortedCombSort);
	//show(H_10000_ReverseSortedCombSort);
	start = clock();
	combSort(H_10000_ReverseSortedCombSort, 10000);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "CombSort - reverse sorted list of 10000 elements: " << executionTime << " ms" << endl;
	//show(H_10000_ReverseSortedCombSort);

	// ** random lists **
	//show(H_100_RandomCombSort);
	start = clock();
	combSort(H_100_RandomCombSort, 100);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "CombSort - random sorted list of 100 elements: " << executionTime << " ms" << endl;
	//show(H_100_RandomCombSort);
	//show(H_1000_RandomCombSort);
	start = clock();
	combSort(H_1000_RandomCombSort, 1000);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "CombSort - random sorted list of 1000 elements: " << executionTime << " ms" << endl;
	//show(H_1000_RandomCombSort);
	//show(H_10000_RandomCombSort);
	start = clock();
	combSort(H_10000_RandomCombSort, 10000);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "CombSort - random sorted list of 10000 elements: " << executionTime << " ms" << endl;
	//show(H_10000_RandomCombSort);

	cout << "----------------------------------------------------------------------------------" << endl;
	// ** BubbleSort change nodes version ** ***************************************************************************************************

	//	// ** sorted lists **
	//show(H_100_SortedBubbleSort);
	start = clock();
	bubbleSort(H_100_SortedBubbleSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "BubbleSort - sorted list of 100 elements: " << executionTime << " ms" << endl;
	//show(H_100_SortedBubbleSort);
	//show(H_1000_SortedBubbleSort);
	start = clock();
	bubbleSort(H_1000_SortedBubbleSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "BubbleSort - sorted list of 1000 elements: " << executionTime << " ms" << endl;
	//show(H_1000_SortedBubbleSort);
	//show(H_10000_SortedBubbleSort);
	start = clock();
	bubbleSort(H_10000_SortedBubbleSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "BubbleSort - sorted list of 10000 elements: " << executionTime << " ms" << endl;
	//show(H_10000_SortedBubbleSort);

	// ** reverse sorted lists **
	//show(H_100_ReverseSortedBubbleSort);
	start = clock();
	bubbleSort(H_100_ReverseSortedBubbleSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "BubbleSort - reverse sorted list of 100 elements: " << executionTime << " ms" << endl;
	//show(H_100_ReverseSortedBubbleSort);
	//show(H_1000_ReverseSortedBubbleSort);
	start = clock();
	bubbleSort(H_1000_ReverseSortedBubbleSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "BubbleSort - reverse sorted list of 1000 elements: " << executionTime << " ms" << endl;
	//show(H_1000_ReverseSortedBubbleSort);
	//show(H_10000_ReverseSortedBubbleSort);
	start = clock();
	bubbleSort(H_10000_ReverseSortedBubbleSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "BubbleSort - reverse sorted list of 10000 elements: " << executionTime << " ms" << endl;
	//show(H_10000_ReverseSortedBubbleSort);

	// ** random lists **
	//show(H_100_RandomBubbleSort);
	start = clock();
	bubbleSort(H_100_RandomBubbleSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "BubbleSort - random sorted list of 100 elements: " << executionTime << " ms" << endl;
	//show(H_100_RandomBubbleSort);
	//show(H_1000_RandomBubbleSort);
	start = clock();
	bubbleSort(H_1000_RandomBubbleSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "BubbleSort - random sorted list of 1000 elements: " << executionTime << " ms" << endl;
	//show(H_1000_RandomBubbleSort);
	//show(H_10000_RandomBubbleSort);
	start = clock();
	bubbleSort(H_10000_RandomBubbleSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "BubbleSort - random sorted list of 10000 elements: " << executionTime << " ms" << endl;
	//show(H_10000_RandomBubbleSort);

	cout << "----------------------------------------------------------------------------------" << endl;
	// ** InsertSort ** *******************************************************************************************************************

	// ** sorted lists **
	//show(H_100_SortedInsertSort);
	start = clock();
	insertSort(H_100_SortedInsertSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "InsertSort - sorted list of 100 elements: " << executionTime << " ms" << endl;
	//show(H_100_SortedInsertSort);
	//show(H_1000_SortedInsertSort);
	start = clock();
	insertSort(H_1000_SortedInsertSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "InsertSort - sorted list of 1000 elements: " << executionTime << " ms" << endl;
	//show(H_1000_SortedInsertSort);
	//show(H_10000_SortedInsertSort);
	start = clock();
	insertSort(H_10000_SortedInsertSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "InsertSort - sorted list of 10000 elements: " << executionTime << " ms" << endl;
	//show(H_10000_SortedInsertSort);

	// ** reverse sorted lists **
	//show(H_100_ReverseSortedInsertSort);
	start = clock();
	insertSort(H_100_ReverseSortedInsertSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "InsertSort - reverse sorted list of 100 elements: " << executionTime << " ms" << endl;
	//show(H_100_ReverseSortedInsertSort);
	//show(H_1000_ReverseSortedInsertSort);
	start = clock();
	insertSort(H_1000_ReverseSortedInsertSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "InsertSort - reverse sorted list of 1000 elements: " << executionTime << " ms" << endl;
	//show(H_1000_ReverseSortedInsertSort);
	//show(H_10000_ReverseSortedInsertSort);
	start = clock();
	insertSort(H_10000_ReverseSortedInsertSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "InsertSort - reverse sorted list of 10000 elements: " << executionTime << " ms" << endl;
	//show(H_10000_ReverseSortedInsertSort);

	// ** random lists **
	//show(H_100_RandomInsertSort);
	start = clock();
	insertSort(H_100_RandomInsertSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "InsertSort - random sorted list of 100 elements: " << executionTime << " ms" << endl;
	//show(H_100_RandomInsertSort);
	//show(H_1000_RandomInsertSort);
	start = clock();
	insertSort(H_1000_RandomInsertSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "InsertSort - random sorted list of 1000 elements: " << executionTime << " ms" << endl;
	//show(H_1000_RandomInsertSort);
	//show(H_10000_RandomInsertSort);
	start = clock();
	insertSort(H_10000_RandomInsertSort);
	stop = clock();
	executionTime = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "InsertSort - random sorted list of 10000 elements: " << executionTime << " ms" << endl;
	//show(H_10000_RandomInsertSort);

	return 0;
	system("PAUSE");
}