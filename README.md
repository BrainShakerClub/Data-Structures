<h1>
    <p align="center">
    <strong>
    Brain Shaker's Data Structures C library
    </strong>
    </p>
</h1>



 <p align="center">
 <img src="assets/BrainShaker.jpg" alt="BrainShaker" width="200" />
 <br>
 <br>
 <a href="LICENSE">Copyright (c)
    </a>
    2022
    <a href="https://github.com/BrainShakerClub">
        <b>Brain Shaker Computer Club</b>
        <br>
    </a> 
</p>
<br>

> [**Antonis Kalantzis**](https://github.com/tonykalantzis)

> [**Giorgos Sofronas**](https://github.com/giorgossofronas)

> [**Mixalis Kostagiannis**](https://github.com/MikeRaphK)
 

## **Purpose**
The **purpose** of this repository is to:

 Provide a **library** writen in **C** with **all** the **popular** **data structures** that there are. We opted for a binary functionality:

1. Easy to **use**. We wanted to provide **ready-to-use** **data structs** just **like** in **high-level languages**.

2. Easy to **understand code**(style, variable names, types e.t.c). Providing solid **algorithimic and theoretical foundations** of the **implementation** of the structures. Also **food for thought** on the **technical part** and over all an opportunity of **deepening C understanding**.


## **How to use**
### - **The library**
* ```bash 
  ~Data-Structures/library$ make
  ```

* There will be produced a file named BSdatastructs.a

* #include any .h file you want to use and compile your main program with:

* ```bash 
  ~Data-Structures$ gcc -o foo foo.o -L. path/BSdatastructs.a -flags
  ```

### - **Specific Function**
* All functions have the format:
* ```c
  data_struct_function()
  ```
* All structures use **types** of **integers**

* **Specific usage** can be found in the **documentation** of each structure

## **Directories**

<dl>
  <dt><strong>assets/</strong></dt>
    <dt>└─── The files that are to be used as a path</dd>
  <dt><strong>headers/</strong></dt>
    <dt>└───The <strong>prototypes</strong> of the structs</dd>
  <dt><strong>library/</strong></dt>
    <dt>└───The final <strong>product</strong> with the makefile and the <b>.a</b> file</dd>
  <dt><strong>source/</strong></dt>
    <dt>└───The <strong>source code</strong> ( .c files)</dd>
  <dt><strong>README.md</strong></dt>
    <dt>└───*Sighs* Tony this is not a time for a <a href="https://en.wikipedia.org/wiki/Mise_en_abyme">mise en abyme</a>...</dd>
</dl>

## **The Data Structures:**
- [x] [**Arrays**](source/Arrays/Arrays.c)

- [x] [**Lists**](source/Lists/Lists.c)

- [x] [**Stacks**](source/Stacks/Stacks.c)

- [x] [**Queues**](source/Queues/Queues.c)

- [x] [**Priority Queues**](source/PriorityQueues/PriorityQueues.c)

- [x] [**Hash Tables**](source/HashTables/HashTable.c)

- [x] [**Binary Trees**](source/BinaryTrees/BinaryTrees.c)

- [x] [**Red-Black Trees**](source/RedBlackTrees/RedBlackTrees.c)

- [x] [**Directed Graphs**](source/DirectedGraphs/DirectedGraphs.c)

- [x] [**Undirected Graphs**](source/UndirectedGraphs/UndirectedGraphs.c)
