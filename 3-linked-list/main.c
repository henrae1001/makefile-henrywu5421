#include <stdio.h>

#include "list.h"


int main() {
    Node* tail = NULL;
    Node* head = NULL;

    printf("\ninsert 1 at head\n");
    insert_head(&head, 1);
    print_list(head);

    printf("\ninsert 2 at tail\n");
    insert_tail(&head, 2);
    print_list(head);
    printf("\ninsert 3 at tail\n");
    insert_tail(&head, 3);
    print_list(head);

    printf("\ndelete head\n");
    delete_head(&head);
    print_list(head);

    printf("\ndelete tail\n");
    delete_tail(&head);
    print_list(head);

    printf("\nfreeing list\n");
    free_list(&head);
    print_list(head);

    return 0;
}
