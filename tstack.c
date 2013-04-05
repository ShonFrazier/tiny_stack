/*
 * @author Shon Frazier
 * @file tstack.c
 */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tstack.h"


bool tstack_push(tstack_ref *s, const item_ref item) {
	
	if ( (!s) || (!item) ) {
		return false;
	}
	
	tstack_ref t = (*s);
	
	*s = malloc(sizeof(tstack_t)); if ( !(*s) ) return false;
	(*s)->item = item;
	(*s)->previous = t;
	
	return true;
}

// make this item the new bottom - not really a 'proper' operation and thus not public
bool tstack_shove(tstack_ref *s, const item_ref item) {
	
	tstack_ref bottom = (*s);
	tstack_ref new_bottom = NULL;
	
	while (bottom->previous) {
		bottom = bottom->previous;
	}
	
	new_bottom = malloc(sizeof(tstack_t)); if (!new_bottom) return false;
	new_bottom->previous = NULL;
	new_bottom->item = item;
	
	bottom->previous = new_bottom;
	
	return true;
}

// put 'wedge' between these two stack nodes - not proper and error prone, therefore not trusting it to others
bool tstack_wedge(tstack_ref *previous, tstack_ref *next, const item_ref wedge) {
	
	tstack_ref wedge_node = malloc(sizeof(tstack_t)); if (!wedge_node) return false;
	wedge_node->item = wedge;
	wedge_node->previous = *previous;
	
	(*next)->previous = wedge_node;
	
	return true;
}

bool tstack_pop(tstack_ref *s, item_ref *item) {
	
	if ( !s ) {
		return false;
	}
	
	tstack_ref t = *s;
	*s = t->previous;
	*item = t->item;
	
	free(t);
	
	return true;
}

bool tstack_top(const tstack_ref *s, item_ref *item) {
	
	if ( !s || !item ) {
		return false;
	}
	
	*item = (*s)->item;
	
	return true;
}

bool tstack_depth(const tstack_ref *s, size_t *count) {
	
	if ( (!s) || (!count) ) {
		return false;
	}
	
	if ( !(*s) ) {
		*count = 0;
	}
	else {
		*count = 0;
		tstack_ref t = (*s);
		
		while (t) {
			(*count)++;
			t = t->previous;
		}
	}
	
	return true;
}

bool tstack_dump(const tstack_ref *s, item_ref *array) {
	
	if ( !s || !array ) {
		return false;
	}
	
	tstack_ref t = (*s);
	size_t count = 0;
	
	while (t) {
		array[count++] = t->item;
		
		t = t->previous;
	}
	
	return true;
}

// Convenience for other operations. Not public.
bool tstack_bottom(const tstack_ref *s, tstack_ref *a) {
	
	if ( (!s) || (!a) ) {
		return false;
	}
	
	(*a) = (*s)->previous;
	
	while ((*a)->previous) {
		(*a) = (*a)->previous;
	}
	
	return true;
}

bool tstack_concat(tstack_ref *stack1, tstack_ref *stack2) {
	
	if ( !stack2 ) {
		return false;
	}
	
	tstack_ref bottom = NULL;
	
	if (!tstack_bottom(stack2, &bottom)) {
		return false;
	}
	
	bottom->previous = *stack1;
	stack1 = stack2;
	
	return true;
}

bool tstack_copy(const tstack_ref *src, tstack_ref *dst) {
	
	if ( (!src) || (!dst) ) {
		return false;
	}
	
	return false;
}
