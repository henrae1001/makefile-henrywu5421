#ifndef LIST_H
#define LIST_H

typedef struct Node Node;

Node* create_node(int data, Node* next);
void insert_head(Node** head, int data);
void insert_tail(Node** head, int data);
void delete_head(Node** head);
void delete_tail(Node** head);
void free_list(Node** head);
void print_list(Node* head);

#endif // LIST_H
