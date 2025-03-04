# CM_Shell: A Custom Command-Line Shell

## Overview

CM_Shell is a lightweight custom command-line shell implementation in C, providing basic shell functionality with support for built-in commands and external program execution.

## Built-in Commands

CM_Shell supports the following built-in commands:

### 1. `help`
- **Usage**: `help`
- **Description**: Displays information about the shell and lists available built-in commands
- **Example**:
  ```
  CM_shell > help
  welcome to chrinovic's shell
  type program names and arguments, and hit enter
  builtin in functions : 
   help
   cd
   crdir
   exit
  ```

### 2. `cd` (Change Directory)
- **Usage**: `cd <directory_path>`
- **Description**: Changes the current working directory
- **Examples**:
  ```
  CM_shell > cd /home/user
  CM_shell > cd ..        # Move to parent directory
  CM_shell > cd /tmp      # Change to /tmp directory
  ```
- **Notes**:
  - Provides error message if no directory is specified
  - Displays an error if directory change fails

### 3. `crdir` (Create Directory)
- **Usage**: `crdir <directory_path>`
- **Description**: Creates a new directory
- **Features**:
  - Creates nested directories automatically
  - Prevents creating directories that already exist
- **Examples**:
  ```
  CM_shell > crdir myproject
  myproject directory created
  
  CM_shell > crdir /path/to/nested/directory
  /path/to/nested/directory directory created
  ```
- **Notes**:
  - Creates directories with 0755 permissions
  - Handles both relative and absolute paths
  - Prevents overwriting existing directories

### 4. `exit`
- **Usage**: `exit`
- **Description**: Exits the shell
- **Example**:
  ```
  CM_shell > exit
  ```

## Error Handling

- Provides informative error messages
- Handles various scenarios like:
  - Missing arguments
  - Permission issues
  - Directory creation failures

## Prerequisites

- GCC or compatible C compiler
- POSIX-compliant operating system (Linux, macOS)
- Standard C libraries (`<sys/stat.h>`, `<errno.h>`)

## Compilation

Compile the shell with:

```bash
gcc -o cm_shell main.c shell_builtins.c
```

## Advanced Features of Built-in Commands

### Directory Creation Mechanism
The `crdir` command has a sophisticated directory creation mechanism:
- Supports creating nested directories
- Automatically creates parent directories if they don't exist
- Uses `mkdir()` with 0755 permissions
- Prevents duplicate directory creation

### Change Directory Flexibility
The `cd` command provides:
- Support for absolute paths
- Support for relative paths
- Error handling for invalid directories

## Common Scenarios

```bash
# Get help
CM_shell > help

# Create a new directory
CM_shell > crdir project/src/main

# Change to a new directory
CM_shell > cd project/src/main

# Exit the shell
CM_shell > exit
```

## Limitations

- Basic shell functionality
- No advanced features like piping or redirection
- Limited complex command support

## Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Create a pull request

## License

[Specify your license here, e.g., MIT, GPL]

## Author

Chrinovic

## Acknowledgments

- Inspired by traditional Unix shells
- Developed as a learning project in C programming
