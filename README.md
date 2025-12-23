# GeoQuery CabeAí: Geospatial Query System

This project implements a **Geospatial Query System** designed to process large volumes of urban addressing data for the logistics context of "CabeAí". [cite_start]The system is capable of disambiguating partial text inputs and ranking the best geographic matches in real-time[cite: 9, 10].

## About the Project

[cite_start]The core objective is to receive a GPS origin and a search string (partial terms) and return the top $R$ closest addresses that contain all the searched terms[cite: 12].

[cite_start]To handle the **Zipfian distribution** of words in street names (where few terms are massive and many are rare), the solution utilizes an **Inverted Index** implemented over an **AVL Tree**[cite: 14, 15]. [cite_start]The project is developed in **C++ (C++11)** with **manual memory management**, strictly avoiding the use of STL containers to ensure optimized resource control[cite: 21].

## Key Features

* [cite_start]**Inverted Index with AVL:** Robust structure for fast retrieval of occurrence lists, ensuring balanced height $O(\log P)$[cite: 27, 76].
* [cite_start]**Stream Processing:** File reading, database population, and index construction occur simultaneously to maximize temporal locality[cite: 23].
* [cite_start]**Geospatial Ranking:** Calculates the "center of gravity" (centroid) of streets and sorts results by Euclidean distance[cite: 16, 59].
* [cite_start]**Manual Memory Management:** rigorous allocation and deallocation of dynamic arrays and tree nodes to prevent memory leaks[cite: 109].

## Method and Architecture

The system operates based on distinct Abstract Data Types (ADTs):

### 1. Data Structures (ADTs)
* **`WordIndex` (AVL):** Manages the inverted index. [cite_start]Each node stores a textual key and a linked list of associated IDs[cite: 27].
* **`StreetManager`:** Manages a manual dynamic vector of streets. [cite_start]Uses a direct mapping array (`idMap`) for $O(1)$ access[cite: 38, 39].
* [cite_start]**`QueryProcessor`:** Service engine that handles parsing, AVL search, and list filtering[cite: 44, 46].

### 2. Algorithmic Logic
* **Matching (Intersection):** For queries with multiple terms $T = \{t_1, t_2, ..., t_n\}$, the system intersects the candidate lists ($L_{res} = L_{res} \cap L_i$). [cite_start]This acts as an aggressive filter, reducing the search space[cite: 53, 203].
* [cite_start]**Distance Calculation:** Applies the Euclidean formula between the query origin $(x_0, y_0)$ and the street's midpoint $(\bar{x}, \bar{y})$[cite: 59].
* [cite_start]**Sorting:** Uses **Bubble Sort** for the final ranking, chosen due to the small cardinality of the result set ($R \le 20$)[cite: 63].

## Complexity Analysis

The system performance is analyzed in two phases: Load (Pre-processing) and Query (Online).

| Component | Time Complexity | Description |
| :--- | :--- | :--- |
| **Load Phase** | $O(N \log P)$ | [cite_start]Insertion of $N$ addresses, where $P$ is the number of unique words[cite: 77]. |
| **Query Processing** | $O(L_{max}^2)$ | [cite_start]Dominated by the intersection of occurrence lists (where $L_{max}$ is the largest list)[cite: 84]. |
| **Space (Memory)** | $O(N)$ | [cite_start]Linear growth for storing street data and tree nodes[cite: 97]. |

> [cite_start]**Note:** Empirical experiments confirmed a robust linear correlation ($R^2 \approx 1$) for the loading time, ensuring scalability for massive databases[cite: 159].

## Robustness Strategies

* [cite_start]**Bounds Checking:** The `addEntry` method strictly verifies ID limits to prevent buffer overflows[cite: 102].
* [cite_start]**Error Handling:** Global `try-catch` blocks capture `std::bad_alloc` to handle memory exhaustion gracefully[cite: 107].
* [cite_start]**Input Validation:** Internal protection against conversion exceptions (like `std::invalid_argument`) allows the system to skip corrupted lines without crashing[cite: 105].
