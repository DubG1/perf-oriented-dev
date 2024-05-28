### Sheet 09

I created function for each read, write, insert and delete, first for every one we need to calculate the address of the element with ````void* element = (char*)array + index * elem_size; ```` then i had to find out how write and insert differ and the difference is

- write overwrites an element and insert adds a new element so write only uses memcpy to copy the value into the array
- insert creates space and shifts existing elements using memmove
- deletion shifts elements backwards to overwrite the element and the current index

then for the benchmark i initialized the array with N+1 elements, caculate the number of iterations per operatiopn given by the ratios and then 

performed the operations in a loop based on the given rations and used clock() to measure the time taken