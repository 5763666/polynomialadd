#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct ListNode {
	int coef;
	int expon;
	struct ListNode* link;
} ListNode;

typedef struct ListType {
	int size;
	ListNode* head;
	ListNode* tail;
} ListType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

ListType* create() {
	ListType* plist = (ListType*)malloc(sizeof(ListType));
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}

void insert_last(ListType* plist, int coef, int expon) {
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
	if (temp == NULL)
		error;
	temp->coef = coef;
	temp->expon = expon;
	temp->link = NULL;
	if (plist->tail == NULL) {
		plist->head = plist->tail = temp;
	}
	else {
		plist->tail->link = temp;
		plist->tail = temp;
	}
	plist->size++;
}

void poly_add(ListType* plist1, ListType* plist2, ListType* plist3) {
	ListNode* a = plist1->head;
	ListNode* b = plist2->head;
	int sum;
	while (a && b) {
		if (a->expon == b->expon) {
			sum = a->coef + b->coef;
			if (sum != 0) insert_last(plist3, sum, a->expon);
			a = a->link; b = b->link;
		}
		else if (a->expon > b->expon) {
			insert_last(plist3, a->coef, a->expon);
			a = a->link;
		}
		else {
			insert_last(plist3, b->coef, b->expon);
			b = b->link;
		}
	}

	for (; a != NULL; a = a->link)
		insert_last(plist3, a->coef, a->expon);
	for (; b != NULL; b = b->link)
		insert_last(plist3, b->coef, b->expon);
}

void poly_print(ListType* plist) {
	ListNode* p = plist->head;
	printf("polynomial = ");
	for (; p; p = p->link) {
		printf("%d^%d + ", p->coef, p->expon);
	}
	printf("\n");
}

int main() {
	ListType* list1, * list2, * list3;

	list1 = create();
	list2 = create();
	list3 = create();

	int coef, expon, i;
	int num;

	printf("Enter the number of terms for the first polynomial: ");
	scanf_s("%d", &num);

	printf("Enter the coefficients and exponents for each term of the first polynomial:\n");
	for (i = 0; i < num; i++) {
		scanf_s("%d %d", &coef, &expon);
		insert_last(list1, coef, expon);
	}

	printf("Enter the number of terms for the second polynomial: ");
	scanf_s("%d", &num);

	printf("Enter the coefficients and exponents for each term of the second polynomial:\n");
	for (i = 0; i < num; i++) {
		scanf_s("%d %d", &coef, &expon);
		insert_last(list2, coef, expon);
	}

	printf("First polynomial: ");
	poly_print(list1);

	printf("Second polynomial: ");
	poly_print(list2);

	poly_add(list1, list2, list3);

	printf("Sum of the polynomials: ");
	poly_print(list3);

	free(list1);
	free(list2);
	free(list3);

	return 0;
}
