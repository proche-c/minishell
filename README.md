### Minishell  

## 📌 **Project Overview**  

**Minishell** is a simplified implementation of a Unix shell, written in C.
It replicates the behavior of Bash for a subset of features while complying with strict rules about memory management and authorized system calls.  

This project is part of the 42 curriculum and aims to deepen understanding of:  

- Process creation and management (fork, execve, wait, pipe, etc.)
- Input/output redirection and file descriptors
- Signal handling
- String parsing and environment variable expansion
- Implementation of built-in shell commands

## 🚀 **Features**  

- Interactive prompt waiting for user input
- Functional command history using readline
- Executes binaries found via PATH, or with relative/absolute paths
- Signal handling:
    - Ctrl-C → prints a new prompt on a new line
    - Ctrl-D → exits the shell
    - Ctrl-\ → does nothing
- Proper handling of:
    - Single quotes (') to disable interpretation of metacharacters
    - Double quotes (") to disable interpretation except for $
- Environment variable expansion, including $? (exit status of last command)
- Redirections:
    - `<` input redirection
    - `>` output redirection (overwrite)
    - `>>` output redirection (append)
    - `<<` heredoc
- Pipes (|) connecting commands  
