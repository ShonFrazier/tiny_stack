/*
 * @author Shon Frazier
 * @file tstack.h
 */

/**
 * Tiny stack: a minimal stack implementation. Works exclusively with pointers to tstack_ref objects and manages
 * its own memory. The value in the provided tstack_ref will change on every push and pop. Users of this API are still
 * responsible for managing memory for their objects.
 * @author: Shon Frazier
 */

#ifndef tstack_h
#define tstack_h

#include <stdlib.h>
#include <stdbool.h>


typedef void *item_ref;
typedef item_ref *pitem_ref;

struct tstack_node {
	struct tstack_node *previous;
	item_ref item;
};

typedef struct tstack_node tstack_t, *tstack_ref;

/**
 * Push an item onto the stack. Use this function to create a new stack. Refuses to operate on a NULL item or a NULL
 * tstack_ref pointer (i.e. the tstack_ref can be NULL, but the pointer to the tstack_ref cannot be)
 *
 * @param[in,out] stack A pointer to a tstack_ref variable. To create a new stack: declare a tstack_ref, set it to NULL,
 *                      and pass its address here. The new stack will be returned in this parameter.
 * @param[in] item A pointer to the item to be pushed onto the stack.
 * @return false if stack or item is NULL, true otherwise
 */
bool tstack_push(tstack_ref *stack, const item_ref item);

/**
 * Pop an item from the stack. This function will free an empty stack.
 *
 * @param[in,out] stack A pointer to a tstack_ref variable.
 * @param[out] item The item popped from the stack will be returned here.
 * @return false if stack is NULL, true otherwise;
 */
bool tstack_pop(tstack_ref *stack, item_ref *item);

/**
 * Get the current item from the stack.
 *
 * @param[in] stack A pointer to a tstack_ref variable. This value will not change on this call.
 * @param[out] item The item at the top of the stack will be returned here.
 * @return false if stack or item is NULL, true otherwise
 */
bool tstack_top(const tstack_ref *stack, item_ref *item);

/**
 * Counts the number of items in a stack.
 *
 * @param[in] stack A pointer to a tstack_ref variable. This value will not change on this call.
 * @param[out] count The number of items in the stack will be returned here.
 * @return false if stack is NULL, true otherwise
 */
bool tstack_depth(const tstack_ref *stack, size_t *count);

/**
 * Places stacked items into the provided array, top of stack at index 0.
 *
 * @param[in] stack A pointer to a tstack_ref variable. This value will not change on this call.
 * @param[out] array An array of pointers, pre-allocated, within which pointers to all stacked items will be returned.
 * @return false if stack or count is NULL, else 0 if the tstack_ref is NULL, otherwise true.
 */
bool tstack_dump(const tstack_ref *stack, void **array);

/**
 * Concatenate two stacks. Second param is pushed onto first, i.e. stack2's top will be the top of your new
 * Frankenstack. stack1 will be modified as if by tstack_push(), stack2's bottom item will be modified. This effectively
 * *destroys* your previous stack structure and gives you one new, large stack. If you need to maintain the old stacks,
 * you'll need to make copies.
 *
 * @param[in,out] stack1 The stack upon which to push stack2
 * @param[in] stack2 The stack to push upon stack1
 * @return false if stack2 is NULL, true otherwise
 */
bool tstack_concat(tstack_ref *stack1, tstack_ref *stack2);

/**
 * Copies the provided stack into new stack node objects.
 */
bool tstack_copy(const tstack_ref *src, tstack_ref *dst);


#endif
