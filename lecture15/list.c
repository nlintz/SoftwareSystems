/* Example code for Software Systems at Olin College.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node * next;
} Node;

Node *make_node(int val, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    return node;
}

void print_list(Node *head) {
    Node *current = head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}

int pop(Node **head) {
    int retval;
    Node *next_node;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}

// Add a new element to the beginning of the list. - FILL IN
void push(Node **head, int val) {
    Node *node = make_node(val, *head);
    *head = node;
}

// Remove the first element with the given value; return the number - FILL IN
// of nodes removed.
int remove_by_value(Node **head, int val) {
    Node *current = *head;
    if (current == NULL)
        return 0;

    if (current->val == val) {
        pop(head);
        return 1;
    }

    for(; current->next != NULL; current = current->next)
    {
        if (current->next->val == val)
        {
            Node *toFree = current->next;
            current->next = current->next->next;
            free(toFree);
            return 1;
        }
    }
    return 0;
}

// Reverse the elements of the list without allocating new nodes. - FILL IN
void reverse(Node **head) {
    Node *current = *head;
    Node *next, *next_next;

    if (current == NULL || next == NULL)
    {
        return;
    }

    next = current->next;
    current->next = NULL;

    while (next != NULL)
    {
        next_next = next->next;
        next->next = current;
        current = next;
        next = next_next;
    }

    *head = current;
}

int main() {
    Node *test_list = make_node(1, NULL);
    test_list->next = make_node(2, NULL);
    test_list->next->next = make_node(3, NULL);
    test_list->next->next->next = make_node(4, NULL);

    int retval = pop(&test_list);

    push(&test_list, retval+10);

    remove_by_value(&test_list, 3);
    remove_by_value(&test_list, 7);

    reverse(&test_list);

    print_list(test_list);
}
