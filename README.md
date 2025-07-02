
# ⚡ hotrace

**hotrace** is a fast key-value dictionary program built as part of the **RUSH** project in the 42 School curriculum.
It reads a list of key-value pairs and allows ultra-fast retrievals using a custom hashtable implementation.

---

## 📄 Description

The program reads input from `stdin` in two phases:

1. **Definition phase**: Alternating lines of keys and values (e.g. `key\nvalue\n...`)
2. **Query phase**: A single empty line (`\n`) signals the end of definitions.
   Then, every subsequent line is treated as a **key lookup**.

If the key exists, the program prints its value. If not, it prints:

```bash
Not found: <key>
```

---

## 🧪 Example

**Input:**

```
name
youssef
city
casablanca

name
city
age
```

**Output:**

```
youssef
casablanca
Not found: age
```

---

## 🚀 Build & Run

### 1. Compile

```bash
make
```

This compiles the project using the provided `Makefile`.

### 2. Run

```bash
./hotrace
```

Then enter keys/values as described above.

---

## 📁 Project Files

* `hotrace.c / hotrace.h` — main logic and hash map functions
* `add_back.c` — list utilities
* `get_next_line.c/.h` — line-by-line input reader
* `test.c` — optional test file
* `Makefile` — builds the project
* `en.subject.pdf` — official project instructions

---

## 🧠 Notes

* The program is **optimized for speed** — no dynamic memory waste
* Lookup performance is near **O(1)** thanks to hash table usage
* Input is read via a custom `get_next_line` implementation
