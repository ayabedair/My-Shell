# My Shell

This project is a custom shell implemented in C, offering functionalities like command execution, redirection, piping, and environmental variable handling.

## Features

- **Command Execution**: Execute system commands (ls, cp, grep, etc.) and custom commands (`mycp`, `mymv`, `myecho`, etc.).
- **Redirection**: Supports `<`, `>`, `2>`, `>>` and `2>>` for input, output and error.
- **Piping**: Chain commands using pipes (`|`).
- **Environment Variables**: Handles environment variables like `PATH` and `HOME`.

## Examples on how to use myShell:

- **mycp**:
  ```bash
  mycp file1 file2

- **mycat**:
  ```bash
  mycat file1 file2 ...

- **myenv**:
  ```bash
  myenv
  myenv <variable_name>

- **piping**:
  ```bash
  ls | grep key

- **redirection**:
  ```bash
  echo aya > output.txt
  
## How to build

- **Clone the repository**:
  ```bash
  git clone https://github.com/ayabedair/My-Shell.git
  
- **Compile the project**:
  ```bash
  gcc -o myshell main.c ./myCommands/*.c ./Redirection/*.c Program/*.c Piping/*.c
