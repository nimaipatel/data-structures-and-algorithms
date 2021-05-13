#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
	int coeff;
	int power;
	struct Node *link;
};

void
print_node(struct Node *node)
{
	printf("(%d %d)", node->coeff, node->power);
}

struct Node *
create_node(int coeff, int power)
{
	struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
	new_node->coeff = coeff;
	new_node->power = power;
	new_node->link = NULL;
	return new_node;
}

// traverse to end and insert node
void
insert_end(struct Node **head_ref, int coeff, int power)
{
	struct Node *new_node = create_node(coeff, power);
	struct Node *iter;
	if (*head_ref == NULL) {
		*head_ref = new_node;
	} else {
		iter = *head_ref;
		while (iter->link != NULL) {
			iter = iter->link;
		}
		iter->link = new_node;
	}
}

void
print_poly(struct Node *head)
{
	struct Node *iter = head;
	while (iter != NULL) {
		if (iter->power != 0) {
			if (iter->coeff < 0) {
				printf(" %dx^%d", iter->coeff, iter->power);
			} else if (iter->coeff > 0) {
				printf(" +%dx^%d", iter->coeff, iter->power);
			}
		} else {
			if (iter->coeff < 0) {
				printf(" %d", iter->coeff);
			} else if (iter->coeff > 0) {
				printf(" +%d", iter->coeff);
			}
		}
		iter = iter->link;
	}
	printf("\n");
}

struct Node *
add(struct Node **ptr_to_head1, struct Node **ptr_to_head2)
{
	struct Node *sum_head = (struct Node *)malloc(sizeof(struct Node));
	sum_head = NULL;
	struct Node *iter1 = *ptr_to_head1;
	struct Node *iter2 = *ptr_to_head2;
	while (iter1 != NULL && iter2 != NULL) {
		if (iter1->power > iter2->power) {
			insert_end(&sum_head, iter1->coeff, iter1->power);
			iter1 = iter1->link;
		} else if (iter2->power > iter1->power) {
			insert_end(&sum_head, iter2->coeff, iter2->power);
			iter2 = iter2->link;
		} else {
			insert_end(&sum_head, iter1->coeff + iter2->coeff,
				   iter2->power);
			iter1 = iter1->link;
			iter2 = iter2->link;
		}
	}
	while (iter1 != NULL && iter2 != NULL) {
		if (iter1 != NULL) {
			insert_end(&sum_head, iter1->coeff, iter1->power);
			iter1 = iter1->link;
		}
		if (iter2 != NULL) {
			insert_end(&sum_head, iter2->coeff, iter2->power);
			iter2 = iter2->link;
		}
	}
	return sum_head;
}

struct Node *
subtract(struct Node **ptr_to_head1, struct Node **ptr_to_head2)
{
	struct Node *sum_head = (struct Node *)malloc(sizeof(struct Node));
	sum_head = NULL;
	struct Node *iter1 = *ptr_to_head1;
	struct Node *iter2 = *ptr_to_head2;
	while (iter1 != NULL && iter2 != NULL) {
		if (iter1->power > iter2->power) {
			insert_end(&sum_head, iter1->coeff, iter1->power);
			iter1 = iter1->link;
		} else if (iter2->power > iter1->power) {
			insert_end(&sum_head, -iter2->coeff, iter2->power);
			iter2 = iter2->link;
		} else {
			insert_end(&sum_head, iter1->coeff - iter2->coeff,
				   iter2->power);
			iter1 = iter1->link;
			iter2 = iter2->link;
		}
	}
	while (iter1 != NULL && iter2 != NULL) {
		if (iter1 != NULL) {
			insert_end(&sum_head, iter1->coeff, iter1->power);
			iter1 = iter1->link;
		}
		if (iter2 != NULL) {
			insert_end(&sum_head, -iter2->coeff, iter2->power);
			iter2 = iter2->link;
		}
	}
	return sum_head;
}

struct Node *
multiply(struct Node **ptr_to_head1, struct Node **ptr_to_head2)
{
	struct Node *iter1 = *ptr_to_head1;
	struct Node *prod = (struct Node *)malloc(sizeof(struct Node));
	prod = NULL;
	while (iter1 != NULL) {
		struct Node *temp = NULL;
		struct Node *iter2 = *ptr_to_head2;
		while (iter2 != NULL) {
			insert_end(&temp, iter1->coeff * iter2->coeff,
				   iter1->power + iter2->power);
			iter2 = iter2->link;
		}
		if (prod == NULL) {
			prod = temp;
		} else {
			prod = add(&prod, &temp);
		}
		iter1 = iter1->link;
	}
	return prod;
}

int
main()
{
	struct Node *head1 = NULL;
	struct Node *head2 = NULL;

	int n1, n2;
	printf("Enter number of terms in first list:");
	scanf("%d", &n1);

	for (int i = 0; i < n1; i++) {
		int power, coeff;
		printf("Enter power of next term:");
		scanf("%d", &power);
		printf("Enter coefficent of next term:");
		scanf("%d", &coeff);
		insert_end(&head1, coeff, power);
	}

	printf("First polynomial is:");
	print_poly(head1);

	printf("Enter number of terms in second list:");
	scanf("%d", &n2);

	for (int i = 0; i < n2; i++) {
		int power, coeff;
		printf("Enter power of next term:");
		scanf("%d", &power);
		printf("Enter coefficent of next term:");
		scanf("%d", &coeff);
		insert_end(&head2, coeff, power);
	}

	printf("Second polynomial is:");
	print_poly(head2);

	struct Node *result;
	int oper;
	printf("Enter 1 for additons Enter 2 for subtraction Enter 3 for "
	       "multiplication:");
	scanf("%d", &oper);
	switch (oper) {
	case 1:
		result = add(&head1, &head2);
		break;
	case 2:
		result = subtract(&head1, &head2);
		break;
	case 3:
		result = multiply(&head1, &head2);
		break;
	default:
		printf("invalid operation");
	}

	printf("result is:");
	print_poly(result);
	return 0;
}
