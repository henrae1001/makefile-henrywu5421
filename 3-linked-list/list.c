#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct Node {
    int data;
    struct Node* next;
};

Node* create_node(int data, Node* next) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = next;
    return new_node;
}

void insert_head(Node** head, int data) {
    Node* new_node = create_node(data, *head);
    if (new_node) {
        *head = new_node;
    }
}

void insert_tail(Node** head, int data) {
    if (!head) return;

    Node* new_node = create_node(data, NULL);
    if (!new_node) return;

    if (!*head) {
        *head = new_node;
    } else {
        Node* temp = *head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void delete_head(Node** head) {
    if (!head || !*head) return;

    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

void delete_tail(Node** head) {
    if (!head || !*head) return;

    if (!(*head)->next) {
        free(*head);
        *head = NULL;
    } else {
        Node* temp = *head;
        while (temp->next && temp->next->next) {
            temp = temp->next;
        }
        free(temp->next);
        temp->next = NULL;
    }
}

void free_list(Node** head) {
    while (*head) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *head = NULL;
}

void print_list(Node* head) {
    if (!head) {
        printf("List is empty.\n");
        return;
    }
    Node* current = head;
    while (current) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
