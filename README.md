An implementation of the shell's pipe operator, using the pipe() system call and file descriptors to pass data between processes.

---

## Compiling: 

1. `make` creates the executable named "pipex" 

2. `make clean` removes object files
   
3. `make fclean` removes object files and the executable
   
4. `make re` calls `fclean` followed by `all`

---

## Usage:
```
./pipex [infile] [command1] [command2] [outfile]
```

## Example:

`./pipex infile "ls -l" "wc -l" outfile` should behave like `< infile ls -l | wc -l > outfile`

### Parameters:

infile: file that is redirected to STDIN (input of the program)

outfile: file that is redirected to STDOUT (output of the program)

command1/ command2: bash commands
