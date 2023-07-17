<!DOCTYPE html>
<html>
<head>
  <title>Minishell 42 Project</title>
</head>
<body>
  <h1>Minishell 42 Project</h1>
  <h2>About</h2>
  <p>
    Welcome to the Minishell 42 project! This project is a part of the curriculum at 42, a renowned coding school. Minishell is a simplified Unix shell implementation that aims to provide a basic command-line interface for users to interact with the operating system. It allows users to execute commands, manage environment variables, and handle essential shell functionalities.
  </p>
  <h2>Project Goals</h2>
  <p>
    The main goals of the Minishell 42 project are as follows:
  </p>
  <ul>
    <li><strong>Understanding Unix processes and system calls:</strong> Gain a deep understanding of how Unix processes work, including process creation, execution, and management. Learn about system calls and their role in interacting with the underlying operating system.</li>
    <li><strong>Implementing a basic command-line interface:</strong> Develop a user-friendly command-line interface that accepts and processes user input. The shell should display a prompt, read commands from the user, and execute them.</li>
    <li><strong>Building a parser:</strong> Create a parser to analyze and interpret user commands. This involves tokenizing input, identifying command structure, and handling arguments and options. The parser should handle complex command structures, such as pipelines and command redirections.</li>
    <li><strong>Handling environment variables:</strong> Manage environment variables within the shell. Environment variables are used to store information such as user preferences, system configurations, and paths. The shell should allow users to set, modify, and retrieve variable values.</li>
    <li><strong>Supporting common shell functionalities:</strong> Implement essential shell functionalities such as pipes, redirections, and signals. Pipes allow users to connect the output of one command to the input of another, enabling command chaining. Redirections allow users to redirect command input or output to files. Signals enable the shell to respond to various events, such as user interrupts or termination signals.</li>
  </ul>
  <h2>Getting Started</h2>
  <p>
    To get started with the Minishell project, follow these steps:
  </p>
  <ol>
    <li>Clone the project repository from the 42 GitLab server using the provided URL.</li>
    <li>Navigate to the project directory on your local machine.</li>
    <li>Review the project's requirements and specifications in the subject file provided in the repository. It will explain the expected behavior, supported features, and additional guidelines for implementing your Minishell.</li>
    <li>Implement your Minishell according to the project guidelines and requirements specified in the subject file. Begin by creating a basic shell structure, implementing the command prompt, and progressively adding support for commands, variables, and shell functionalities.</li>
    <li>Thoroughly test your shell to ensure it handles various commands and scenarios correctly. Consider edge cases, error handling, and performance optimization.</li>
  </ol>
  <h2>Project Structure</h2>
  <p>
    The project repository contains the following files and directories:
  </p>
  <ul>
    <li><strong>src/</strong>: This directory contains the source code for the Minishell project. You will find the implementation of various components, including the main shell loop, command execution, parsing logic, environment variable management, and supporting functions.</li>
    <li><strong>includes/</strong>: This directory includes the header files necessary for the Minishell project. It provides the function prototypes and definitions required for proper compilation and linking of the source code.</li>
    <li><strong>Makefile</strong>: The Makefile is provided to automate the compilation and building of the Minishell executable. It includes commands for compiling source files, managing dependencies, and generating the final executable file.</li>
    <li><strong>README.md</strong>: The README file you are currently reading, which provides essential information and instructions about the project.</li>
  </ul>
  <h2>Commands and Variables</h2>
  <p>
    In Minishell, users can execute various commands and manage environment variables. Here's an overview of the command and variable handling within the shell:
  </p>
  <h3>Commands</h3>
  <p>
    Minishell supports executing both built-in commands and external programs. Built-in commands are implemented within the shell itself, while external programs are executed using the underlying operating system's facilities.
  </p>
  <ul>
    <li><strong>Built-in Commands:</strong> Minishell typically provides a set of built-in commands, such as <code>cd</code> (change directory), <code>echo</code> (display text), <code>exit</code> (terminate the shell), and <code>export</code> (set environment variables). These commands are implemented directly within the shell and have specific behavior defined by the project requirements.</li>
    <li><strong>External Programs:</strong> Minishell can execute external programs by launching new processes. Users can enter the name of an external program, and the shell will attempt to locate and execute it. The shell should handle searching for programs in the system's PATH variable and execute them with the appropriate command-line arguments.</li>
  </ul>
  <h3>Environment Variables</h3>
  <p>
    Minishell provides functionality to manage environment variables. Environment variables are used to store information that can be accessed by programs and scripts running within the shell. Users can set, modify, and retrieve variable values using built-in commands or shell syntax.
  </p>
  <ul>
    <li><strong>Setting Variables:</strong> Users can set environment variables using the <code>export</code> command or shell syntax. For example, <code>export VAR=value</code> sets the variable <code>VAR</code> to the value <code>value</code>. The shell should maintain a table of environment variables and their corresponding values.</li>
    <li><strong>Retrieving Variables:</strong> Users can access the values of environment variables using the <code>$VAR</code> syntax. For example, if <code>VAR</code> is an environment variable, then <code>$VAR</code> will be replaced with its corresponding value when executing a command or expanding a shell expression.</li>
    <li><strong>Modifying Variables:</strong> Users can modify the values of existing environment variables using the <code>export</code> command or shell syntax. For example, <code>export VAR=new_value</code> changes the value of the variable <code>VAR</code> to <code>new_value</code>. The shell should update the variable's value in its environment variable table.</li>
  </ul>
  <h2>Dependencies</h2>
  <p>
    The Minishell project has the following dependencies:
  </p>
  <ul>
    <li><strong>Standard C library (libc):</strong> The project relies on various standard C library functions for string manipulation, memory management, input/output operations, and other fundamental operations.</li>
    <li><strong>Unix system calls and libraries:</strong> As Minishell interacts with the underlying operating system, it depends on Unix system calls and libraries to perform various operations, such as executing commands, managing processes, and handling input/output streams.</li>
  </ul>
  <h2>Contributing</h2>
  <p>
    This project is part of the curriculum at 42, and contributions are generally not accepted from external sources. However, if you are a student at 42, you can contribute to the project by improving its functionality, fixing bugs, or adding additional features. Collaborate with your peers and mentors to enhance the overall Minishell experience.
  </p>
  <h2>License</h2>
  <p>
    The Minishell project is licensed under the MIT License. You can find the license details in the LICENSE file included in the project repository.
  </p>
</body>
</html>
