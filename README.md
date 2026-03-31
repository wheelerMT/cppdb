# cppdb

A relational database engine written in modern C++23, built from scratch. cppdb implements the core components of a real
database — from raw page-based storage through to a SQL-like query interface — without relying on any external database
libraries.

---

## Features

- **Page-based storage** — data is organised into fixed-size 4KB pages, aligned with OS and hardware block sizes for
  efficient I/O
- **Persistent storage** — pages are written to and read from disk, surviving process restarts
- **Buffer pool manager** — an in-memory cache of pages with LRU eviction, minimising expensive disk reads
- **B-Tree indexing** — efficient O(log n) lookups, insertions, and deletions via a B-Tree index structure
- **Relational tables** — typed columns, schema definition, and a system catalog tracking all tables
- **SQL-like query language** — supports `CREATE TABLE`, `DROP TABLE`, `INSERT`, `SELECT`, and `DELETE`
- **Interactive REPL** — a command-line shell for querying the database interactively
- **Bounds-safe I/O** — all read and write operations are bounds-checked, with errors surfaced via `std::expected`

---

## Example Usage

```sql
cppdb
>
CREATE TABLE users
(
    id   INT,
    name TEXT,
    age  INT
);
Created
table 'users'.

cppdb> INSERT INTO users VALUES (1, 'Alice', 30);
Inserted
1 row.

cppdb> INSERT INTO users VALUES (2, 'Bob', 25);
Inserted
1 row.

cppdb>
SELECT *
FROM users;
id
| name   | age
----|--------|----
1   | Alice  | 30
2   | Bob    | 25

cppdb>
SELECT *
FROM users
WHERE age > 27;
id
| name   | age
----|--------|----
1   | Alice  | 30

cppdb>
DELETE
FROM users
WHERE id = 1;
Deleted
1 row.

cppdb> .exit
Bye.
```

---

## Architecture

cppdb is built in layers, each depending only on the one below it:

```
┌─────────────────────────────┐
│         REPL / Shell        │
├─────────────────────────────┤
│       Query Executor        │
├─────────────────────────────┤
│      Parser / Analyser      │
├─────────────────────────────┤
│       Table / Schema        │
├─────────────────────────────┤
│          B-Tree             │
├─────────────────────────────┤
│       Buffer Pool           │
├─────────────────────────────┤
│        Disk Manager         │
├─────────────────────────────┤
│           Page              │
└─────────────────────────────┘
```

---

## Building

### Requirements

- CMake 3.28+
- Clang 22+ (via Homebrew on macOS: `brew install llvm`)
- Ninja (`brew install ninja`)

### Build

```bash
cmake --preset debug
cmake --build build/debug
```

### Run

```bash
./build/debug/src/cppdb
```

### Run Tests

```bash
ctest --test-dir build/debug --output-on-failure
```

---

## Development

### Presets

| Preset    | Use                                                     |
|-----------|---------------------------------------------------------|
| `debug`   | Local development — sanitizers enabled, no optimisation |
| `release` | Benchmarking — full optimisation, no debug symbols      |

### Tooling

- **clang-tidy** — static analysis, enforced on CI
- **clang-format** — automatic code formatting, enforced on CI
- **AddressSanitizer + UBSan** — enabled in debug builds to catch memory errors and undefined behaviour at runtime
- **ccache** — compiler caching for fast incremental builds

### CI

Every push and pull request runs three jobs in parallel on GitHub Actions:

| Job               | What it checks                                    |
|-------------------|---------------------------------------------------|
| `build-and-test`  | Compiles the project and runs the full test suite |
| `formatting`      | Verifies all files comply with `.clang-format`    |
| `static-analysis` | Runs `clang-tidy` across all source files         |

---

## Tech Stack

| Area         | Choice                |
|--------------|-----------------------|
| Language     | C++23                 |
| Compiler     | Clang 22              |
| Build system | CMake 3.28 with Ninja |
| Testing      | Catch2 v3             |
| CI           | GitHub Actions        |

---

## Status

Currently in active development. Completed components:

- [x] Project setup, tooling, and CI/CD pipeline
- [x] `Page` — fixed-size byte buffer with bounds-checked read/write
- [x] `DiskManager` — page-level persistence to disk
- [ ] Buffer Pool Manager
- [ ] B-Tree
- [ ] Table schema and catalog
- [ ] SQL lexer and parser
- [ ] Query executor
- [ ] REPL
