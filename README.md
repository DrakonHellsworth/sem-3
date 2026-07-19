<h1 align="center">⚡ Semester 3 Academic Repository</h1>

<p align="center">
  <code>🔧 C (DAA)</code>&nbsp;&nbsp;<code>🛢️ SQL</code>&nbsp;&nbsp;<code>🍃 MongoDB</code>&nbsp;&nbsp;<code>🐍 Python (AI/ML)</code>&nbsp;&nbsp;<code>📅 Sem 3</code>
</p>

---

## About This Repository

This directory contains academic coursework, experiments, and assignments completed during **Semester 3**, spanning three key domains:
1. **Design and Analysis of Algorithms (DAA)** (implemented in **C**) — analyzing algorithmic efficiency, divide-and-conquer, greedy designs, dynamic programming, and string matching.
2. **Database Management Systems (DBMS)** (using **SQL** & **MongoDB**) — structured queries, relational calculus, PL/SQL blocks, transactions, and NoSQL databases.
3. **Artificial Intelligence and Machine Learning (AI/ML)** (using **Python**) — data cleaning, regression analysis, clustering (K-Means), and Principal Component Analysis (PCA) using spreadsheets.

---

## Progress

```
 ██████████████████████████████████████████  100% Coursework Completed
```

**Core concepts covered:** BST Insertion Efficiency · Merge Sort · Strassen's Matrix Multiplication · Activity Selection · Fractional Knapsack & Job Sequencing · Kruskal's MST · Dijkstra & Floyd-Warshall shortest paths · 0/1 Knapsack (DP) · Rabin-Karp String Search · SQL Join & PL/SQL cursors · MongoDB collections · Linear Regression & K-Means clustering

---

## Core Coursework Log

> Every file is linked directly — click any filename to view the source code.

<details open>
<summary><h3>Phase 1 — Design and Analysis of Algorithms (DAA) <code>DAA/</code></h3></summary>

Focuses on computational complexity and sorting, greedy decision heuristics, single-source/all-pairs shortest paths, and dynamic programming formulations.

| Lab / File | Concept | Algorithmic Design | Solution Link |
|:---|:---|:---|:---:|
| **exp1.c** | BST Search Efficiency | BST Iterative vs Recursive Insertion comparison | [exp1.c](DAA/exp1.c) |
| **exp2.c** | Merge Sort | Divide and conquer sorting | [exp2.c](DAA/exp2.c) |
| **exp3.c** | Matrix Multiplication | Strassen's matrix algorithm | [exp3.c](DAA/exp3.c) |
| **exp4.1.c** | Activity Selection | Greedy scheduling optimization | [exp4.1.c](DAA/exp4.1.c) |
| **exp4.2.c** | Fractional Knapsack | Greedy value/weight partitioning | [exp4.2.c](DAA/exp4.2.c) |
| **exp5.c** | Job Sequencing | Greedy deadline scheduling | [exp5.c](DAA/exp5.c) |
| **exp6.c** | Kruskal's MST | Disjoint sets graph optimization | [exp6.c](DAA/exp6.c) |
| **exp7.c** | Dijkstra's SSSP | Single-source shortest path ($O(V^2)$) | [exp7.c](DAA/exp7.c) |
| **exp8.c** | Floyd-Warshall | All-pairs shortest path matrix ($O(V^3)$) | [exp8.c](DAA/exp8.c) |
| **exp9.c** | 0/1 Knapsack | Dynamic programming state table | [exp9.c](DAA/exp9.c) |
| **exp10.c** | Rabin-Karp Search | String-matching algorithm via rolling hashes | [exp10.c](DAA/exp10.c) |

</details>

<details open>
<summary><h3>Phase 2 — Database Management Systems (DBMS) <code>DBMS/</code></h3></summary>

Features relational databases, advanced SQL syntax (joins, groups, subqueries), PL/SQL programming (variables, loops, exception handling, triggers, cursors), and NoSQL JSON databases.

| File | Language | Topic | Purpose |
|:---|:---:|:---|:---|
| `1st.sql` | SQL | Schema definition | Table creation, Primary/Foreign keys, and base constraints |
| `2ND4.sql` | SQL | DML Commands | Insert, Update, and Delete operations |
| `3rd.sql` | SQL | Query Expressions | Group By, Order By, Having, and Subquery structures |
| `5th.sql` | SQL | Relational Algebra | Nested conditions, union operations, and intersections |
| `EXP10.sql` to `EXP12.sql` | PL/SQL | Dynamic scripting | PL/SQL loops, parameters, and logical blocks |
| `exp13.sql` to `exp15.sql` | PL/SQL | Cursors | Implicit and Explicit cursors handling multi-row results |
| `exp16.sql` to `exp17.sql` | PL/SQL | Triggers | Database level constraints triggered on INSERT/UPDATE |
| `mongo1.mongodb.js` | JS (MongoDB) | NoSQL Queries | Collection inserts, updates, and aggregate queries |

</details>

<details open>
<summary><h3>Phase 3 — Artificial Intelligence and Machine Learning (AI/ML) <code>aiml lab/</code></h3></summary>

Features Python-based data operations, spreadsheet data manipulation, regression, clustering, PCA, and classification models.

| Lab / File | Topic | Key Techniques | Solution Link |
|:---|:---|:---|:---:|
| **Lab 1 & 2** | Data Pre-processing | Handling missing data, Null mapping, Excel integration | [Lab1.py](aiml%20lab/Lab1.py) / [Lab2.py](aiml%20lab/Lab2.py) |
| **Lab 3** | Data Scaling | Z-score normalization and Min-Max scaling | [Lab3.py](aiml%20lab/Lab3.py) |
| **Lab 4 & 5** | Linear Regression | Plotting line of best fit, gradient descent steps | [lab4.py](aiml%20lab/lab4.py) / [lab5.py](aiml%20lab/lab5.py) |
| **Lab 6** | Multiple Regression | Multi-variable linear equations fitting | [lab6.py](aiml%20lab/lab6.py) |
| **Lab 8 & 9** | PCA (Manual & Library) | Dimensionality reduction via eigenvectors, Excel export | [lab8.py](aiml%20lab/lab8.py) / [lab9.1.py](aiml%20lab/lab9.1.py) |
| **Lab 10 & 11** | K-Means Clustering | Silhouette coefficient optimization and cluster plotting | [lab10.py](aiml%20lab/lab10.py) / [lab11.1.py](aiml%20lab/lab11.1.py) |
| **Lab 12** | Credit Card Clustering | Processing balanced datasets with clusters | [lab12.py](aiml%20lab/lab12.py) |

</details>

---

## Repository Structure

```
sem3/
│
├── DAA/                                 ← Design & Analysis of Algorithms C files
│   ├── exp1.c to exp10.c
│   └── Anmol_590011794_DAA.pdf          ← Compiled DAA lab document
│
├── DBMS/                                ← Database Management SQL scripts & PDF guides
│   ├── EXP3.sql to exp17.sql
│   ├── mongo1.mongodb.js                ← MongoDB script
│   └── Database Management Systems.pdf  ← Textbook references
│
├── ai/
│   └── 1.py                             ← AI model scripts
│
├── aiml lab/                            ← Python files and datasets for ML lab
│   ├── Lab1.py to lab12.py
│   ├── Students Data.xlsx               ← Student dataset
│   └── creditcard.csv                   ← Credit Card Fraud dataset
│
└── README.md
```

---

## How to Run

<details>
<summary><b>⚡ Compile and Run DAA (C) Code</b></summary>

```bash
cd DAA
gcc exp2.c -o mergesort
./mergesort
```

</details>

<details>
<summary><b>🛢️ Execute DBMS (SQL/MongoDB) Scripts</b></summary>

For Oracle SQL CLI:
```sql
@DBMS/EXP3.sql
```

For MongoDB:
```bash
mongosh < DBMS/mongo1.mongodb.js
```

</details>

<details>
<summary><b>🐍 Run AI/ML (Python) Scripts</b></summary>

Install pandas, openpyxl, scikit-learn, and run:
```bash
cd "aiml lab"
pip install pandas openpyxl scikit-learn
python lab10.py
```

</details>

---

<p align="center">
  <i>"Algorithms are the heart of computer science, and databases are its memory."</i>
</p>
