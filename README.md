### Minishell  

## 📌 **Project Overview**  

**Minishell** is a simplified implementation of a Unix shell, written in C.
It replicates the behavior of Bash for a subset of features while complying with strict rules about memory management and authorized system calls.  

This project is part of the 42 curriculum and aims to deepen understanding of:  

- Process creation and management (`fork`, `execve`, `wait`, `pipe`, etc.)
- Input/output redirection and file descriptors
- Signal handling
- String parsing and environment variable expansion
- Implementation of built-in shell commands

## 🚀 **Features**  

- Interactive prompt waiting for user input
- Functional command history using readline
- Executes binaries found via `PATH`, or with relative/absolute paths
- Signal handling:
    - `Ctrl-C` → prints a new prompt on a new line
    - `Ctrl-D` → exits the shell
    - `Ctrl-\` → does nothing
- Proper handling of:
    - Single quotes (') to disable interpretation of metacharacters
    - Double quotes (") to disable interpretation except for `$`
- Environment variable expansion, including $? (exit status of last command)
- Redirections:
    - `<` input redirection
    - `>` output redirection (overwrite)
    - `>>` output redirection (append)
    - `<<` heredoc
- Pipes (`|`) connecting commands
- Built-in commands:  
      - `echo` (with `-n`)  
      - `cd` (relative or absolute paths)  
      - `pwd`  
      - `export`  
      - `unset`  
      - `env`  
      - `exit`  

## 🛠️ Authorized Functions  

The following functions and system calls are allowed:
`readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`, `printf`, `malloc`, `free`, `write`, `access`, `open`, `read`, `close`, `fork`, `wait`, `waitpid`, `wait3`, `wait4`, `signal`, `sigaction`, `kill`, `exit`, `getcwd`, `chdir`, `stat`, `lstat`, `fstat`, `unlink`, `execve`, `dup`, `dup2`, `pipe`, `opendir`, `readdir`, `closedir`, `strerror`, `perror`, `isatty`, `ttyname`, `ttyslot`, `ioctl`, `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`.


## 📂 Project Structure  

- `src/` → project source files organized into modules:
      - `builtins/` → implementation of shell built-ins
      - `execute/` → command execution and piping
      - `parse/` → input parsing and tokenization
      - `utils/` → helper functions
      - `lists/` → linked list management
      - `clean/` → memory cleanup
      - `minishell.c` → entry point  
- `include/` → header files
- `libft/` → personal library

## ⚙️ Makefile  

The project comes with a Makefile that compiles `minishell`.  
It supports the following rules:  

- `make / make all` → builds the program
- `make clean` → removes object files
- `make fclean` → removes object files and the executable
- `make re` → cleans and rebuilds
- `make norme` → runs norminette on the source files
- `make test` → rebuilds and runs ./minishell
- `make leaks` → runs the program with leaks for debugging memory

🔑 Note about `readline` **include paths**:  

The Makefile includes two possible `CFLAGS` setups depending on where Homebrew is installed:  

- For custom Homebrew in user directory:

  ```make
  CFLAGS = -Wall -Wextra -Werror -g $(INC) -I ~/.brew/opt/readline/include
  ```
- For standard Apple Silicon Homebrew (`M1/M2/M3`):

  ```make
  CFLAGS = -Wall -Wextra -Werror -g $(INC) -I /opt/homebrew/opt/readline/include
  ```
Adjust this depending on your environment.  

## ▶️ Usage  

```bash
make
./minishell
```
Once inside, you can run commands just like in Bash:  

```bash
minishell$ echo hello
hello
minishell$ ls -l | grep minishell > output.txt
```
To exit:  

```bash
minishell$ exit
``` 
