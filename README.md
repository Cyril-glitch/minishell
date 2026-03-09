# 🐚 Minishell - As beautiful as a shell

## 📝 Description
[cite_start]**Minishell** is a 42 school project that consists of creating a simple shell[cite: 6]. [cite_start]This "little Bash" was developed to gain extensive knowledge about processes, file descriptors, and system calls[cite: 7, 8].



## 🚀 Features
[cite_start]This implementation covers the mandatory requirements of the subject[cite: 96, 98]:

* [cite_start]**Interactive Prompt**: Displays a prompt when waiting for a new command[cite: 99].
* [cite_start]**Command Execution**: Searches and launches the right executable based on the `PATH` variable or using relative/absolute paths[cite: 101].
* [cite_start]**History**: Includes a working command history (via `readline`)[cite: 100].
* **Quoting Management**: 
    * [cite_start]**Single quotes (`'`)**: Prevents the shell from interpreting meta-characters[cite: 112].
    * [cite_start]**Double quotes (`"`)**: Prevents interpretation except for the dollar sign (`$`)[cite: 113].
* **Redirections**:
    * [cite_start]`<`: Redirects input[cite: 115].
    * [cite_start]`>`: Redirects output (truncate mode)[cite: 116].
    * [cite_start]`>>`: Redirects output (append mode)[cite: 119].
    * [cite_start]`<<` (Heredoc): Reads input until a specific delimiter is seen[cite: 117].
* [cite_start]**Pipes (`|`)**: Connects the output of one command to the input of the next in a pipeline[cite: 120].
* [cite_start]**Environment Variables**: Expands `$VAR` to its environment value[cite: 121].
* [cite_start]**Exit Status**: Expands `$?` to the exit status of the last executed foreground pipeline[cite: 122].
* [cite_start]**Signals**: Handles `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` as in Bash[cite: 123]:
    * [cite_start]**Ctrl-C**: Displays a new prompt on a new line[cite: 125].
    * [cite_start]**Ctrl-D**: Exits the shell[cite: 126].
    * [cite_start]**Ctrl-\**: Does nothing[cite: 127].

## 🛠️ Built-in Commands
[cite_start]The following built-ins are implemented natively[cite: 128]:
* [cite_start]`echo` (with option `-n`) [cite: 129]
* [cite_start]`cd` (relative or absolute path only) [cite: 130]
* [cite_start]`pwd` (no options) [cite: 131]
* [cite_start]`export` (no options) [cite: 132]
* [cite_start]`unset` (no options) [cite: 133]
* [cite_start]`env` (no options or arguments) [cite: 134]
* [cite_start]`exit` (no options) [cite: 135]

## 🏗️ Technical Details
* [cite_start]**Language**: C[cite: 22].
* [cite_start]**Signal Handling**: Uses at most one global variable to store the signal number, ensuring no access to main data structures from the handler[cite: 102, 105].
* [cite_start]**Memory Management**: All heap-allocated memory is properly freed[cite: 27]. [cite_start]Note: `readline()` leaks are acknowledged and tolerated by the subject[cite: 139, 140].
* [cite_start]**No Relinking**: The Makefile is optimized to avoid unnecessary relinking[cite: 29].

## 📦 Installation & Usage
1. **Clone the repository**:
   ```bash
   git clone <your-repo-link>
   cd minishell
