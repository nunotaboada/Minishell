# Minishell 💻

**A 42 School project developed in collaboration with [Nuno Valadão](https://github.com/nunovaladao)**

## Introduction

Minishell is a simplified shell implementation created as part of the 42 School curriculum. This project aims to replicate core functionalities of a Unix shell, such as `bash`, by executing basic command-line operations, handling input/output redirection, and managing processes. The goal is to deepen understanding of Unix systems, process management, and system programming in C.

By completing Minishell, we honed essential programming skills, including:

- **Understanding of Unix systems**: I gain a deeper understanding of how Unix-based operating systems function, including processes, file systems, and command execution.
- **Process management**: I learn how to create and manage processes within the shell, including forking, executing commands, and handling process termination.
- **Command parsing**: I be able to understand to parse user input and interpret command structures, including handling arguments, options, and redirection.
- **Input/output handling**: I learn how to manage input/output streams, including reading from and writing to files, implementing pipes, and handling standard input/output redirection.
- **Signal handling**: I gain experience in handling signals and implementing signal handlers for various events, such as process termination or interruption.

## Grade

**101/125** ✅\
This score reflects the project's successful implementation of mandatory features and some bonus functionalities, as evaluated by 42's Moulinette.

## Features

Minishell supports the following features:

- **Basic Commands**: Execute built-in commands (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`) and external programs.
- **Pipes (**`|`**)**: Chain multiple commands, redirecting output from one to the input of another.
- **Redirections (**`<`**,** `>`**,** `>>`**)**: Support for input/output redirection and appending to files.
- **Environment Variables**: Handle variable expansion (e.g., `$HOME`, `$PATH`) and manage the environment.
- **Signal Handling**: Properly manage `Ctrl+C`, `Ctrl+D`, and `Ctrl+\` signals for smooth user interaction.
- **Heredoc (**`<<`**)**: Support for heredoc-style input redirection.
- **Exit Status**: Correctly handle and display the exit status of commands (`$?`).


## Installation

To set up and run Minishell, follow these steps:

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/nunovaladao/42_Minishell_lev3.git
   ```
2. **Navigate to the Directory**:

   ```bash
   cd 42_Minishell_lev3
   ```
3. **Build the Project**:

   ```bash
   make
   ```
4. **Run Minishell**:

   ```bash
   ./minishell
   ```

## Testing the Project

Once Minishell is running, you can test its functionality with various commands, such as:

- `ls`: List files and directories.
- `cd <path>`: Change the current working directory.
- `echo <text>`: Display text or environment variables (e.g., `echo $PATH`).
- `pwd`: Print the current working directory.
- `cat <file>`: Display file contents.
- `mkdir <dir>`: Create a new directory.
- `rm <file>`: Remove files or directories.
- `exit`: Exit the shell.
- **Pipes**: Combine commands, e.g., `ls | grep .txt`.
- **Redirections**: Redirect input/output, e.g., `echo "Hello" > file.txt` or `cat < file.txt`.
- **Heredoc**: Use `<< EOF` to input multi-line text.

Experiment with these commands, combine them with pipes (`|`) or redirections (`<`, `>`), and test edge cases to explore the shell's capabilities.

## Skills and Competencies Acquired

The Minishell project provided valuable learning opportunities, including:

- **C Programming**: Strengthened proficiency in C, leveraging data structures (e.g., linked lists for command parsing), pointers, and memory management.
- **Unix System Calls**: Mastered system calls like `fork()`, `execve()`, `wait()`, `pipe()`, and `dup2()` for process and I/O management.
- **Operating Systems**: Deepened understanding of Unix process creation, file descriptors, and shell mechanics.
- **Debugging**: Developed strong problem-solving skills by debugging complex issues, such as memory leaks or signal handling errors.
- **Collaboration**: Practiced teamwork through pair programming, code reviews, and version control using Git.
- **Norminette Compliance**: Adhered to 42's strict coding standards (Norminette), ensuring clean and readable code.

## Known Limitations

- Minishell is a simplified shell and does not support all features of full-fledged shells like `bash` or `zsh`.
- The project is designed for 42's Linux-based environment and may exhibit unexpected behavior on other systems.

## Conclusion

Minishell is a challenging yet rewarding project that offers a deep dive into Unix systems and shell programming. By building a functional shell, we developed critical skills in C programming, process management, and system-level operations. These skills form a strong foundation for future projects in software development, system administration, and operating system design.

This project not only enhanced our technical expertise but also fostered collaboration, problem-solving, and attention to detail. We hope Minishell serves as a valuable learning resource for others exploring Unix systems and shell programming.

## Useful Resources

- [**Writing Your Own Shell**](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- [**42 Docs: Minishell**](https://harm-smits.github.io/42docs/projects/minishell.html)
- [**Building a Simple Shell in C**](https://blog.ehoneahobed.com/building-a-simple-shell-in-c-part-1#heading-printing-a-prompt)
- [**Subject**](https://github.com/nunovaladao42_Minishell_lev3/blob/main/extras/en.subject.pdf) 

## Notes

- [**Coding Norm**](): Minishell adheres to 42's Norminette coding standards, ensuring clean and consistent code.

## Authors
- **Names**: [Nuno Taboada](https://github.com/nunotaboada), [Nuno Valadão](https://github.com/nunovaladao),
- **Emails**: nunotaboada@gmail.com

This project was completed as part of the 42 school curriculum

<a href="https://www.42porto.com/pt/">
 	<img alt="Static Badge" src="https://img.shields.io/badge/_-Porto-_?style=for-the-badge&logo=42&labelColor=black&color=gray&link=https%3A%2F%2Fwww.42porto.com%2Fpt%2F">	
</a>
