#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */

/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(*head));

    if (!head)
        return NULL;

    INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (!head)
        return;

    struct list_head *current = head->next, *next;

    while (current != head) {
        next = current->next;
        element_t *entry = list_entry(current, element_t, list);
        free(entry->value);
        free(entry);
        current = next;
    }
    free(head);
}

/* Insert an element at head of queue */

#ifndef strlcpy
#define strlcpy(dst, src, sz) snprintf((dst), (sz), "%s", (src))
#endif

bool q_insert_head(struct list_head *head, char *s)
{
    if (!head || !s)
        return false;

    element_t *first = malloc(sizeof(element_t));

    if (!first)
        return false;

    size_t len = strlen(s) + 1;
    char *newstr = malloc(len); /* Allocate memory for the string (with '\0') */

    if (!newstr) {
        free(first);
        return false;
    }

    strlcpy(newstr, s, len);
    first->value = newstr;
    list_add(&first->list, head);

    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head || !s)
        return false;

    element_t *last = malloc(sizeof(element_t));

    if (!last)
        return false;

    size_t len = strlen(s) + 1;
    char *newstr = malloc(len);

    if (!newstr) {
        free(last);
        return false;
    }

    strlcpy(newstr, s, len);
    last->value = newstr;
    list_add_tail(&last->list, head);

    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *firstnode = list_first_entry(head, element_t, list);

    list_del(&firstnode->list);
    if (sp && bufsize > 0)
        strlcpy(sp, firstnode->value, bufsize);

    return firstnode;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *lastnode = list_last_entry(head, element_t, list);

    list_del(&lastnode->list);
    if (sp && bufsize > 0)
        strlcpy(sp, lastnode->value, bufsize);

    return lastnode;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head || list_empty(head))
        return 0;

    struct list_head *node;
    int count = 0;

    list_for_each (node, head) {
        count++;
    }
    return count;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    if (!head || list_empty(head) || head->next->next == head)
        return false;

    struct list_head *node;
    int count = 1;
    element_t *temp = list_first_entry(head, element_t, list);


    list_for_each (node, head) {
        count++;
        if ((count & 1) == 0)
            temp = list_entry(temp->list.next, element_t, list);
    }
    list_del(&temp->list);
    free(temp);
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    if (!head || list_empty(head) || head->next->next == head)
        return;

    struct list_head *first = head->next, *second = first->next;

    head->next = second;
    while (first != head && second != head) {
        first->next = second->next;
        first->next->prev = first;
        second->prev = first->prev;
        second->prev->next = second;
        first->prev = second;
        second->next = first;
        first = first->next;
        second = first->next;
    }
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (!head || list_empty(head) || head->next->next == head)
        return;

    element_t *last = list_last_entry(head, element_t, list);
    head->prev = head->next;
    head->next = &last->list;

    struct list_head *node = head->next;
    struct list_head *prev = head;
    while (node != head) {
        node->next = node->prev;
        node->prev = prev;
        prev = node;
        node = node->next;
    }
}


/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
