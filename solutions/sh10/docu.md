### Unrolled Linked List

LinkedBlock: block in the unrolled linked list, like a container that holds multiple elements, there is a head within the block
Node: a single element within a block, a block stores multiple Nodes

Pros: faster search, reduced memory overhead, better for cache
Cons: more complex, less flexible when inserting and deleting, wasted space

#### Init

````init_unrolled_linked_list```` creates a linked list with a specified number of blocks, elements per block, and element size, calls ````init_block```` which creates an array to represent it

#### Operations

````read```` traverses the list and block to get the specified element, copies it to a variable and returns it

````write```` same as read but copies the value from the input to the specified node

````insert```` essentially does the same as write but with additional checks for out of bounds accesses, more in results.md

````delete```` replaces the value at the specified node with 0


### Tiered Array

An array of pointers that reference smaller sub-arrays containing the actual data elements

#### Init

````init_tiered_array```` allocates memory for the tier-zero array with the pointers and then calls ````init_array```` that inits the sub arrays with the specified sizes and assigns the pointers to the tier-zero array to store them

#### Operations

````read```` retrieves the element by accessing the chunk and then the index inside that chunk

````write```` similiar to read it takes the chunk but then copies the provided value to the index

````insert```` checks if the chunk is within the valid range, then the first if checks if the insertion is beyond the current chunk size and if there is room at the end of the subarray, if so then insert there

the second if checks if it is within or equal the current chunk size and if there is room at the end, if so then insert at the provided index

if none of these cases are hit we need to resize the chunk for the element to fit

````delete```` removes an element at a specific chunk and index , uses read to to retrieve the element, checks if it is not empty to decrease element counter, then uses memmove to shift the elements from index + 1 forward