# ls
System function ls is recoded on this git repository.

From BSD General Commands Manual:
	
	NAME
		ls -- list directory contents

	SYNOPSIS
		ls [-ABCFGHLOPRSTUW@abcdefghiklmnopqrstuwx1] [file ...]

	DESCRIPTION
		For each operand that names a file of a type other than directory, ls displays its name as well as any requested,
		associated information.  For each operand that names a file of type directory, ls displays the names of files con-
		tained within that directory, as well as any requested, associated information.

	 	If no operands are given, the contents of the current directory are displayed.  If more than one operand is given,
	 	non-directory operands are displayed first; directory and non-directory operands are sorted separately and in lexico-
		graphical order.

for more information search in BSD General Commands Manual.

However the synopsis of my ls is:
```
./ft_ls [-CGr@aefglmnort1] [file ...]
```

**To compile a binary that will list directories** you should do **`make`**. After what you can watch through any directory (if you have such permisions of course).
**To inititalise ft_ls** you should write:
```
./ft_ls
```
That's it!
Every option (such as -l or -a) is implemented due to the option of original ls, so u can watch how it works and compare with my function!

Images of original ls and ft_ls:

<img src="https://github.com/ZeTRoY/ls/blob/master/Images/Screen%20Shot%202019-01-25%20at%206.25.20%20PM.png">

<img src="https://github.com/ZeTRoY/ls/blob/master/Images/Screen%20Shot%202019-01-25%20at%206.28.14%20PM.png">

<img src="https://github.com/ZeTRoY/ls/blob/master/Images/Screen%20Shot%202019-01-25%20at%206.29.30%20PM.png">

<img src="https://github.com/ZeTRoY/ls/blob/master/Images/Screen%20Shot%202019-01-25%20at%206.30.15%20PM.png">

<img src="https://github.com/ZeTRoY/ls/blob/master/Images/Screen%20Shot%202019-01-25%20at%206.57.23%20PM.png">

Additional info:

Makefile functions:
- `make/make all` - compiles a binary named `ft_ls`;
- `make clean` - removes every object file from `obj` directory;
- `make fclean` - the same as `make clean` + removes binary file `ft_ls`;
- `make re` - the same as `make fclean` + `make`.
