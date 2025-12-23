# GeoQuery CabeAí: Geospatial Query System

This project implements a **Geospatial Query System** designed to process large volumes of urban addressing data for the logistics context of "CabeAí". The system is capable of disambiguating partial text inputs and ranking the best geographic matches in real-time.

## About the Project

The core objective is to receive a GPS origin and a search string (partial terms) and return the top $R$ closest addresses that contain all the searched terms.

To handle the **Zipfian distribution** of words in street names (where few terms are massive and many are rare), the solution utilizes an **Inverted Index** implemented over an **AVL Tree**. The project is developed in **C++ (C++11)** with **manual memory management**, strictly avoiding the use of STL containers to ensure optimized resource control.

## Key Features

* **Inverted Index with AVL:** Robust structure for fast retrieval of occurrence lists, ensuring balanced height $O(\log P)$.
* **Stream Processing:** File reading, database population, and index construction occur simultaneously to maximize temporal locality.
* **Geospatial Ranking:** Calculates the "center of gravity" (centroid) of streets and sorts results by Euclidean distance.
* **Manual Memory Management:** Rigorous allocation and deallocation of dynamic arrays and tree nodes to prevent memory leaks.

## Method and Architecture

The system operates based on distinct Abstract Data Types (ADTs):

### 1. Data Structures (ADTs)
* **WordIndex (AVL):** Manages the inverted index. Each node stores a textual key and a linked list of associated IDs.
* **StreetManager:** Manages a manual dynamic vector of streets. Uses a direct mapping array (`idMap`) for $O(1)$ access.
* **QueryProcessor:** Service engine that handles parsing, AVL search, and list filtering.

### 2. Algorithmic Logic
* **Matching (Intersection):** For queries with multiple terms $T=\{t_1, t_2, ..., t_n\}$, the system intersects the candidate lists ($L_{res}=L_{res} \cap L_i$). This acts as an aggressive filter, reducing the search space.
* **Distance Calculation:** Applies the Euclidean formula between the query origin $(x_0, y_0)$ and the street's midpoint $(\bar{x}, \bar{y})$.
* **Sorting:** Uses **Bubble Sort** for the final ranking, chosen due to the small cardinality of the result set ($R \le 20$).

## Complexity Analysis

The system performance is analyzed in two phases: Load (Pre-processing) and Query (Online).

| Component | Time Complexity | Description |
| :--- | :--- | :--- |
| **Load Phase** | $O(N \log P)$ | Insertion of $N$ addresses, where $P$ is the number of unique words. |
| **Query Processing** | $O(L_{max}^2)$ | Dominated by the intersection of occurrence lists (where $L_{max}$ is the largest list). |
| **Space (Memory)** | $O(N)$ | Linear growth for storing street data and tree nodes. |

> **Note:** Empirical experiments confirmed a robust linear correlation ($R^2 \approx 1$) for the loading time, ensuring scalability for massive databases.

## Robustness Strategies

* **Bounds Checking:** The `addEntry` method strictly verifies ID limits to prevent buffer overflows.
* **Error Handling:** Global `try-catch` blocks capture `std::bad_alloc` to handle memory exhaustion gracefully.
* **Input Validation:** Internal protection against conversion exceptions (like `std::invalid_argument`) allows the system to skip corrupted lines without crashing.
