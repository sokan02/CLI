# Unix-like CLI (Command Line Interface)

A simplified **Unix-like command line interface implemented in C++**.

This project simulates basic behavior of a shell by parsing commands, executing operations on files and streams, and supporting modular command implementations.

It demonstrates concepts such as **command parsing, object-oriented design, file I/O, and stream manipulation in C++**.

---

# Overview

A **Command Line Interface (CLI)** allows users to interact with a system by typing commands into a terminal instead of using a graphical interface. It enables efficient execution of tasks and automation of workflows through text-based commands. :contentReference[oaicite:0]{index=0}

This project implements a simplified CLI that supports multiple commands and demonstrates how command execution can be structured using **C++ classes and modular design**.

---

# Features

- Modular command architecture
- File input/output support
- Stream redirection
- Command parsing
- Object-oriented command implementation
- Extensible structure for adding new commands

---

# Implemented Commands

The CLI supports several Unix-like commands including:

- `echo` – prints text to the output stream
- `cat` – displays file contents
- `head` – prints the first lines of a file
- `tail` – prints the last lines of a file
- `wc` – counts lines, words, and characters
- `sort` – sorts lines of text

Commands operate on **standard input/output streams** or files.

---

# Architecture

The program is structured using an object-oriented design:

```
Program
│
├── Command (base class)
│   ├── Echo
│   ├── Cat
│   ├── Head
│   ├── Tail
│   ├── Sort
│   └── Wc
```

Each command inherits from a common **Command base class** and implements its own execution logic.

This design allows new commands to be added easily without modifying the core CLI logic.

---

# Technologies

- **C++**
- Standard Template Library (STL)
- Object-Oriented Programming
- File I/O and stream manipulation
- Linux / terminal development

---

# Project Structure

```
CLI/
├── Commands/
│   ├── Cat.cpp
│   ├── Echo.cpp
│   ├── Head.cpp
│   ├── Tail.cpp
│   ├── Sort.cpp
│   └── Wc.cpp
│
├── Program.cpp
├── Program.h
├── main.cpp
└── README.md
```

---

# Compilation

Compile the project using a C++ compiler:

```bash
g++ *.cpp Commands/*.cpp -o cli
```

---

# Running

Run the CLI:

```bash
./cli
```

Example usage:

```
echo Hello World
cat file.txt
head -5 file.txt
sort file.txt
wc file.txt
```

---

# Learning Goals

This project explores:

- building a **custom command-line interface**
- designing **modular command execution systems**
- handling **input/output streams**
- applying **object-oriented programming in C++**

---

# Possible Improvements

Future improvements could include:

- command piping (`|`)
- input/output redirection (`>`, `<`)
- command history
- interactive shell prompt
- additional Unix commands

---

# Author

**Sofija Djeric**

GitHub: https://github.com/sokan02
