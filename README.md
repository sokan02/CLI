# C++ Unix-like CLI

A simplified **Unix-like command line interface implemented in C++**.

This project implements a modular CLI with support for command parsing, file manipulation, text processing, stream-based execution, and simple pipelines/redirections. It is designed around a custom parser and a command hierarchy, with each command implemented as a separate class.

The project demonstrates **object-oriented design, parsing, file I/O, stream handling, and terminal-style interaction in C++**.

---

## Features

- Interactive command-line prompt
- Modular command architecture
- Custom parser for commands, options, and arguments
- Support for **pipelines**
- Support for **input/output redirection**
- File and text processing commands
- Extensible structure for adding new commands

---

## Supported Commands

| Command | Description |
|--------|-------------|
| `time` | Prints the current time |
| `date` | Prints the current date |
| `touch <file>` | Creates a file |
| `echo "text"` | Prints text |
| `wc -w <file/text>` | Counts words |
| `wc -c <file/text>` | Counts characters |
| `rm <file>` | Removes a file |
| `truncate <file>` | Empties a file |
| `prompt "text"` | Changes the CLI prompt |
| `head -nN <file/text>` | Prints the first `N` lines |
| `tr <arg> -<option> <with>` | Performs character translation/transformation |
| `batch <file>` | Executes commands from a batch file |

---

## Example Usage

```bash
$ echo "Hello world"
Hello world

$ touch notes.txt

$ wc -w "hello from cli"
3

$ head -n3 file.txt

$ prompt "cli>"
cli> date
cli> time
```

### Example with redirection

```bash
$ echo "sample text" > out.txt
$ wc -c < out.txt
```

### Example with pipeline

```bash
$ echo "abcdef" | tr "abc" -d
```

---

## Project Architecture

The project is organized around three main parts:

### 1. Parser
Responsible for:
- lexical validation
- tokenization
- building command objects
- parsing pipelines and redirections

### 2. Program
Responsible for:
- storing commands
- wiring input/output streams
- executing single commands and pipelines
- handling redirected input/output

### 3. Commands
Each command is implemented as its own class derived from a common base command structure.

---

## Project Structure

```text
CLI/
├── CMakeLists.txt
├── main.cpp
├── Parser.cpp
├── Parser.h
├── Program.cpp
├── Program.h
├── Reader.cpp
├── Reader.h
├── README.md
└── Commands/
    ├── Batch.cpp
    ├── Batch.h
    ├── Command.cpp
    ├── Command.h
    ├── Date.cpp
    ├── Date.h
    ├── Echo.cpp
    ├── Echo.h
    ├── Head.cpp
    ├── Head.h
    ├── Prompt.cpp
    ├── Prompt.h
    ├── Rm.cpp
    ├── Rm.h
    ├── Time.cpp
    ├── Time.h
    ├── Touch.cpp
    ├── Touch.h
    ├── Tr.cpp
    ├── Tr.h
    ├── Truncate.cpp
    ├── Truncate.h
    ├── Wc.cpp
    ├── Wc.h
    └── streamInterfaces.h
```

---

## Build

### Using CMake

```bash
mkdir build
cd build
cmake ..
make
```

### Or compile manually

```bash
g++ *.cpp Commands/*.cpp -o cli
```

---

## Run

```bash
./cli
```

After launching, the program opens an interactive prompt where commands can be entered one by one.

---

## Technical Highlights

This project demonstrates:

- **C++ object-oriented design**
- **custom command parsing**
- **file and stream processing**
- **pipeline execution**
- **input/output redirection**
- **modular command implementation**

---

## Learning Goals

The purpose of this project was to explore how a simple shell-like environment can be implemented from scratch, including:

- command parsing
- execution flow
- stream-based communication between commands
- reusable class design
- terminal-style user interaction

---

## Possible Future Improvements

- more Unix-like commands
- better error reporting
- command history
- tab completion
- environment variables
- more advanced piping behavior

---

## Author

**Sofija Djeric**

GitHub: https://github.com/sokan02
