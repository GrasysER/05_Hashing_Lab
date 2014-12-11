05_Hashing_Lab
==============

Implement a hash table in C++

Requirements
------------

1. `keyExists`, `find`, `remove`, and `size` should all be O(1)
2. `add` should be reasonably fast. Use linear probing to find an open slot in the hash table. This will be O(1), on average, except when `grow` is called.
3. `grow` should be O(n)
4. Do not leak memory


Reading
=======
"Open Data Structures," Chapter 5, except for 5.2.3. http://opendatastructures.org/ods-cpp/5_Hash_Tables.html

Questions
=========

#### 1. Which of the above requirements work, and which do not? For each requirement, write a brief response.

1. All 4 are constant time
2. I believe add is reasonably fast when grow is not called
3. Grow is 0(n)
4. Both the constructor, destructor, and grow allocate and deallocate memory correctly

#### 2. I decided to use two function (`keyExists` and `find`) to enable lookup of keys. Another option would have been to have `find` return a `T*`, which would be `NULL` if an item with matching key is not found. Which design do you think would be better? Explain your reasoning. You may notice that the designers of C++ made the same decision I did when they designed http://www.cplusplus.com/reference/unordered_map/unordered_map/

I believe the design you used is better because it seperates the workload and makes each seperate method faster. Also returning null if no matching key is found poses other problems (I can't remember a better reason, but I know it's bad) such as potentially confusing the user that the index has never been used.

#### 3. What is one question that confused you about this exercise, or one piece of advice you would share with students next semester?

I was very confused about how . and -> are to be used and I think it should be one of the first things to be explained. 

