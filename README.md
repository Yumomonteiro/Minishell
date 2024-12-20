Minishell

Welcome to Minishell, a custom UNIX-like shell built as part of the 42 coding program. This project is a simplified version of a shell, implementing core features like command execution, piping, redirections, environment variables, and signal handling.
Table of Contents

    Overview
    Features
    Learning Objectives
    Technologies Used
    Installation
    Usage
    Key Challenges
    Acknowledgments

Overview

The Minishell project aims to deepen the understanding of how command-line shells work under the hood. It offers a functional, interactive shell that mimics some basic features of Bash while adhering to specific 42 project requirements.
Features

    Command Execution: Supports both built-in and external commands.
    Pipes and Redirection: Handles input/output redirection and multi-command pipelines.
    Environment Variables: Dynamically manages environment variables, supporting export, unset, and substitutions like $HOME.
    Robust Parsing: Processes complex command structures, including quotes, escapes, and special characters.
    Signal Handling: Gracefully manages signals like Ctrl+C and Ctrl+D.
    Error Management: Provides detailed feedback for invalid commands and syntax errors.

Learning Objectives

    Understand and utilize UNIX system calls (fork(), execve(), pipe(), etc.).
    Develop a robust command parser to handle various shell syntaxes.
    Manage processes, memory allocation, and signals effectively.
    Collaborate efficiently in a pair programming environment.

Technologies Used

    Language: C
    Libraries: Standard C library, POSIX-compliant functions
    Development Tools: Makefile, Valgrind for debugging and memory management

Installation

    Clone the repository:

git clone https://github.com/Yumomonteiro/Minishell.git  

Navigate to the project directory:

cd Minishell  

Build the project:

    make  

Usage

    Run the shell:

    ./minishell  

    Enter commands as you would in a standard shell, such as:
        ls -l | grep txt > output.txt
        export MY_VAR=42
        echo $MY_VAR
        cat file.txt | wc -l

    To exit, type exit or press Ctrl+D.

Key Challenges

    Developing a robust parser to handle complex command syntaxes.
    Managing multiple processes and ensuring proper synchronization.
    Handling edge cases for redirections and signals.

Acknowledgments

This project was completed as part of the 42 program in collaboration with my partner, Yuri Monteiro. A huge thanks to the 42 community for their support and resources throughout this journey.

Feel free to explore the code and provide feedback!
