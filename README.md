# Skiplist
Goals: Working with dynamic arrays, pointers, doubly linked lists

This assignment is a SkipList structure. This SkipList only takes in ints for data. 

When searching a Skip List, items can be found in O(log n) time. 
No duplicates are allowed.A SkipList can have multiple levels. 
SkipList of depth 1 is similar to a doubly linked list. All elements are inserted into a single doubly linked list.

When a SkipList has multiple levels, all elements are inserted at level = 0. 50% of those inserted at level = 0, 
are also inserted at level = 1. 50% of those inserted at level = 1 are also inserted at level = 2, and so on.
 
In addition, there should be no memory leaks in this SkipList. The Heap should be empty.
Each node has pointers to up, down, next, prev
##Included Files
- `CMakeLists.txt`: For complex projects, `cmake CMakeLists.txt` will
  generate a `Makefile`. We can then use `make` to compile the
  project. Optional for a small project like this, but included as an
  example.
  
- `skiplist.h` and `skiplist.cpp`
###Functions:
```
    // overloads << operator to display list as desired 
    friend ostream& operator<<(ostream& out, const SkipList& skipList);

    // default SkipList has Depth of 1, just one doubly-linked list
    explicit SkipList(int depth = 1);

    // destructor
    virtual ~SkipList();

    // return true if successfully added, no duplicates
    bool add(int data);

    // return true if successfully removed
    bool remove(int data);

    // return true if found in SkipList
    bool contains(int data);

    // SNode
    explicit SNode(int data);
    //Snode data
    int data;
    // link to Next SNode
    SNode* next;
    // link to Prev SNode
    SNode* prev;
    // link to up one level
    SNode* upLevel;
    // link to down one level
    SNode* downLevel;

    // Depth of SkipList
    int depth;

    // array of Depth SNode* objects as FrontGuards linking levels
    SNode** frontGuards;

    // array of Depth SNode* objects as RearGuards linking levels
    SNode** rearGuards;

    // given a SNode, place it before the given NextNode
    void addBefore(SNode* newNode, SNode* nextNode);

    // return true 50% of time,
    // each node has a 50% chance of being at higher level
    bool alsoHigher() const;

    //clears nodes inside skipList at each level
    void clear();
```

- `main.cpp`: Runs all tests

- `output.txt`: Output from `./simple.compile.sh > output.txt 2>&1`
showing how the program is compiled and run.

- `simplecompile.sh`: Unix bash script file to compile, run 
and then delete the executable. Can be used to create an output.txt file
## Compile and Run

```
./simplecompile.sh
```

### Style Explanation
These options are defined in `.clang-tidy` file.

Perform all check except the following:

- fuchsia-* do not need specific checks for "fuchsia" a modular, capability-based operating system
- cppcoreguidelines-pro-bounds-array-to-pointer-decay: do not give warnings on assert
- google-build-using-namespace: for simplicity allow `using namespace std;`
- google-readability-braces-around-statements: allow compact code without `{`
- readability-braces-around-statements: allow compact code without `{`
This option is not available in CSS Linux lab under LLVM 3.8.1, but is needed on my PC when using 9.0.0
- hicpp-no-array-decay need to use assert
- modernize-use-trailing-return-type: not ready yet for `auto func() -> int` format
- hicpp-braces-around-statements: allow compact code without `{` (this option
- cppcoreguidelines-pro-bounds-pointer-arithmetic,
- llvm-header-guard: not using full directory name
- google-global-names-in-headers: for simplicity allow `using namespace std;`
- cppcoreguidelines-special-member-functions: not defining move operator
- hicpp-special-member-functions: not defining move operator
- cppcoreguidelines-owning-memory: not using gsl

## Misc

This file is part of a repository located at
https://github.com/jdelliot/skiplist

