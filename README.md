# pipex

This project is part of the 42 school curriculum. The goal is to understand how UNIX pipes and process management work by reproducing the shell behavior for piping commands using `fork`, `execve`, `pipe`, and `dup2`.

## Description

`pipex` takes input from a file, passes it through two commands via a pipe, and writes the output to a second file. The behavior mimics the shell instruction:

```bash
< infile cmd1 | cmd2 > outfile
```

You will need to handle process creation, file descriptors, and environment paths manually.

## Allowed Functions

- `open`, `close`, `read`, `write`, `malloc`, `free`, `perror`, `strerror`, `access`, `dup`, `dup2`, `execve`, `exit`, `fork`, `pipe`, `wait`, `waitpid`

You are not allowed to use `system()` or any other function that launches the shell.

## Compilation

**Note:** You must have your `libft` (including `ft_printf`) available in a directory named `libft/`.

To compile the program:

```bash
gcc -Wall -Wextra -Werror pipex.c utils.c libft/libft.a -Ilibft -o pipex
```

Make sure to compile `libft` first:

```bash
cd libft && make && cd ..
```

## Usage

```bash
./pipex infile "cmd1" "cmd2" outfile
```

Example:

```bash
./pipex infile "grep hello" "wc -l" outfile
```

This is equivalent to:

```bash
< infile grep hello | wc -l > outfile
```

## Author

Developed by Elena as part of the 42 School curriculum.
