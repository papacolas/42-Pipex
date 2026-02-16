# Pipex

This project mimics the behavior of the shell pipe command in C. It allows you to explore UNIX mechanisms in detail, specifically handling pipes, forks, and file descriptors.

## 📝 Description

The program `pipex` works like this shell command:
```bash
< file1 cmd1 | cmd2 > file2
```

It takes a file as input, sends it through a first command, pipes the output to a second command, and saves the result to an output file.

## ⚙️ Implementation Details

The project is implemented using standard UNIX system calls to manage processes and file descriptors. Here is a high-level overview of the workflow:

1.  **Pipe Creation**: The `pipe()` system call is used to create a unidirectional data channel that can be used for interprocess communication. It creates two file descriptors: one for reading and one for writing.

2.  **Forking**: The `fork()` system call is used to create child processes.
    - **Child Process 1**:
        - Duplicates `infile` to `STDIN`.
        - Duplicates the *write end* of the pipe to `STDOUT`.
        - Closes unused file descriptors.
        - Executes `cmd1` using `execve()`.
    - **Child Process 2**:
        - Duplicates the *read end* of the pipe to `STDIN`.
        - Duplicates `outfile` to `STDOUT`.
        - Closes unused file descriptors.
        - Executes `cmd2` using `execve()`.

3.  **Redirection**: `dup2()` is the key function here. It swaps the file descriptors so that the commands read from files/pipes instead of the standard keyboard input/screen output.

4.  **Execution**: `execve()` replaces the current process image with a new process image (the command to run). If successful, it never returns.

5.  **Parent Process**: The parent process waits for the children to finish using `waitpid()` to ensure proper synchronization and handling of exit statuses.

## 🛠️ Compilation

To compile the program, simply run:

```bash
make
```

To compile with bonus features:

```bash
make bonus
```

To clean object files:
```bash
make clean
```

To clean everything (objects and executable):
```bash
make fclean
```

## 🚀 Usage

### Mandatory Part

The program is executed as follows:

```bash
./pipex file1 cmd1 cmd2 file2
```

- `file1`: Input file
- `cmd1`: First shell command (with parameters)
- `cmd2`: Second shell command (with parameters)
- `file2`: Output file

#### Examples:

```bash
./pipex infile "ls -l" "wc -l" outfile
# Behaves like: < infile ls -l | wc -l > outfile
```

```bash
./pipex infile "grep a1" "wc -w" outfile
# Behaves like: < infile grep a1 | wc -w > outfile
```

### Bonus Part

The bonus version supports multiple pipes and `here_doc`.

#### Multiple Pipes
Handle an indefinite number of commands:

```bash
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```

Behaves like:
```bash
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
```

#### Here_doc
Support for `<<` and `>>` when the first parameter is "here_doc":

```bash
./pipex here_doc LIMITER cmd1 cmd2 file
```

Behaves like:
```bash
cmd1 << LIMITER | cmd2 >> file
```

## 📂 Project Structure

- `src/`: Source files for the mandatory part.
- `src_bonus/`: Source files for the bonus part.
- `includes/`: Header files.
- `utils/`: Utility functions.
- `Makefile`: Compilation rules.

## ⚠️ Requirements

- The project is written in C.
- It complies with the 42 Norm.
- No memory leaks.
- Handles errors similar to the shell.
