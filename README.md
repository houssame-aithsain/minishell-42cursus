<!DOCTYPE html>
<html>
<body>
  <h1>Minishell 42 Project</h1>
  
  <img src="https://img2.freepng.es/20180615/pxs/kisspng-bash-shell-script-gnu-bourne-shell-bash-5b239a62056153.0040296515290599380221.jpg" alt="Minishell 42 Project">
  
  <p>Welcome to the Minishell 42 Project! This project is part of the 42 curriculum and focuses on building a basic shell implementation.</p>

  <h2>About</h2>
  
  <p>The Minishell 42 Project challenges you to create a basic shell that can interpret and execute commands. The project involves parsing and executing commands, handling environment variables, implementing built-in shell commands, and supporting various shell functionalities. This project will enhance your understanding of process management, system calls, and command line interfaces.</p>

  <h2>Installation</h2>
  
  <ol>
    <li>Clone the repository:</li>
    <pre><code>git clone https://github.com/houssame-aithsain/minishell-42cursus.git</code></pre>
    <li>Change into the project directory:</li>
    <pre><code>cd minishell-42cursus</code></pre>
    <li>Compile the project:</li>
    <pre><code>make</code></pre>
    <li>Once the compilation is complete, you can start using the minishell executable.</li>
  </ol>

  <h2>Usage</h2>
  
  <p>To use the minishell program, simply run the executable:</p>
  
  <pre><code>./minishell</code></pre>

  <p>Once the minishell is running, you can enter commands and execute them.</p>
  
  <pre><code>$ echo "Hello, World!"
Hello, World!</code></pre>

  <h2>Documentation</h2>
  
  <p>The Minishell 42 Project involves implementing various features and functionalities of a basic shell. The project documentation provides detailed information on the supported shell commands, syntax, and usage examples. You can find the documentation in the project's repository and follow the guidelines and specifications provided.</p>
  
  <p>For detailed documentation and usage examples, refer to the <a href="https://github.com/your-username/minishell/wiki">Minishell 42 Project Wiki</a>.</p>

  <h2>Introduction</h2>
  <p>The objective of the Minishell 42 Project is to build a basic shell that can interpret and execute commands. You will learn about processes, file descriptors, and various shell functionalities. By completing this project, you will gain a deeper understanding of how shells work and improve your programming skills.</p>
  <h2>Common Instructions</h2>
  <ul>
    <li>Your project must be written in accordance with the Norm.</li>
    <li>Your functions should not quit unexpectedly (segmentation fault, bus error, double free, etc) apart from undefined behaviors.</li>
    <li>All heap allocated memory space must be properly freed when necessary. No leaks will be tolerated.</li>
    <li>If the subject requires it, you must submit a Makefile which will compile your source files with the required flags and options.</li>
    <li>If your project allows you to use your libft, you must copy its sources and associated Makefile into a libft folder.</li>
  </ul>
  <h2>Mandatory Part</h2>
  <h3>Program name</h3>
  <ul>
    <li>minishell</li>
  </ul>
  <h3>Turn in files</h3>
  <ul>
    <li>Makefile</li>
  </ul>
  <h3>Arguments</h3>
  <ul>
    <li>None</li>
  </ul>
  <h3>External Functions</h3>
  <ul>
    <li>readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs</li>
  </ul>
  <h3>Libft authorized</h3>
  <ul>
    <li>Yes</li>
  </ul>
  <h3>Description</h3>
  <p>Write a shell that meets the following requirements:</p>
  <ul>
    <li>Do not interpret unclosed quotes or unspecified special characters like \ or ;.</li>
    <li>Do not use more than one global variable.</li>
    <li>Show a prompt when waiting for a new command.</li>
    <li>Have a working history feature.</li>
    <li>Search and launch the right executable based on the PATH variable or using relative/absolute path.</li>
    <li>Implement the following built-in commands: echo with option -n, cd with only a relative or absolute path, pwd with no options, export with no options, unset with no options, env with no options or arguments, and exit with no options.</li>
    <li>Inhibit all interpretation of a sequence of characters within single quotes (').</li>
    <li>Inhibit all interpretation of a sequence of characters within double quotes (") except for $.</li>
    <li>Handle redirections: < (input redirection), > (output redirection), << (heredoc), and >> (output redirection with append mode).</li>
    <li>Implement pipes (|) to connect the output of one command to the input of the next command in a pipeline.</li>
    <li>Expand environment variables ($ followed by characters) to their values.</li>
    <li>Handle special parameters: $? (expand to the exit status of the most recently executed foreground pipeline).</li>
    <li>Handle signals: ctrl-C (print a new prompt on a newline), ctrl-D (exit the shell), and ctrl-\ (do nothing).</li>
  </ul>
  <h2>Bonus Part</h2>
  <ul>
    <li>Implement logical operators (&& and ||) with parenthesis for priorities.</li>
    <li>Make the wildcard * work for the current working directory.</li>
  </ul>
        <h2>Key Concepts</h2>
  <h3>Variables</h3>
  <p>In the Minishell project, you will work with various variables. Environment variables play an important role in storing information about the system environment. You will need to handle these variables and implement built-in commands to manipulate them, such as <code>export</code> and <code>unset</code>.</p>
  <h3>Command Line</h3>
  <p>The command line is where users can input commands to be executed by the shell. In your Minishell, you will parse and interpret the command line, handle different types of commands and arguments, and execute them accordingly.</p>
  <h3>Environment</h3>
  <p>The environment in the context of a shell refers to the collection of variables, settings, and resources available to the shell and its subprocesses. You will work with the environment variables and manage their values and interactions within your Minishell.</p>
  <h3>Parsing</h3>
  <p>Parsing is the process of analyzing and breaking down a command line into its individual components, such as command, arguments, and options. You will need to implement a parsing mechanism to extract the necessary information from the command line in order to execute the commands correctly.</p>
  <h3>Expansion</h3>
  <p>Expansion involves expanding variables or special characters to their corresponding values. You will handle the expansion of environment variables (e.g., <code>$HOME</code>) and implement the necessary logic to substitute these variables with their actual values during command execution.</p>
  <h3>Pipe</h3>
  <p>The pipe allows the output of one command to be passed as input to another command. You will implement the pipe functionality in your Minishell to enable the execution of commands in a pipeline, where the output of one command serves as the input for the next command.</p>
  <h3>Leaks and Memory</h3>
  <p>In Minishell, it is essential to manage memory properly and avoid leaks. Make sure to allocate and free memory appropriately for variables, command execution, and any dynamically allocated resources. Avoid memory leaks to ensure the stability and efficiency of your shell.</p>
  <h3>Linux</h3>
  <p>Minishell is designed to run on Linux systems. Familiarize yourself with Linux system calls, file descriptors, signals, and other relevant Linux concepts to implement the required functionality in your shell.</p>
       <h2>Contributing</h2>
  
  <p>Contributions to the Minishell 42 Project are welcome! If you find any bugs, have suggestions for improvements, or want to add new features, please open an issue or submit a pull request. Make sure to follow the project's code style and guidelines.</p>
  
  <ol>
    <li>Fork the repository</li>
    <li>Create your feature branch (<code>git checkout -b feature/your-feature</code>)</li>
    <li>Commit your changes (<code>git commit -am 'Add some feature'</code>)</li>
    <li>Push to the branch (<code>git push origin feature/your-feature</code>)</li>
    <li>Open a pull request</li>
  </ol>
</body>
</html>
</body>
</html>
