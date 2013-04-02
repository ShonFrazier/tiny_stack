Tiny Stack
==========

A small stack implementation written in pure C. Adds no memory management overhead to your code. Adds 
( 2 * ( sizeof( void * ) ) ) of additional memory overhead per item stored on the stack.

Create a new tstack_ref variable and initialize to NULL:

```
tstack_ref a_stack = NULL;
```

Push an item onto the empty stack:

```
char *some_text = "I'm stacked!";
...
tstack_push( &a_stack, some_text );
```

Keep pushing pointers to stuff to your heart's content. Keep in mind that C has no runtime type reflection so you
really should only push pointers to the same types of objects.

Pop items that you don't need on the stack:

```
some_text = NULL;
tstack_pop( &a_stack, &some_text );
printf("%s", some_text);
```

If you print the stack pointer, you'll notice A) that it changes between calls and B) it's set to NULL when it's empty.
As you push items on the array, new nodes are allocated, and as you pop, old nodes are freed.

Enjoy!

