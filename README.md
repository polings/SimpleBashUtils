# Simple Bash Utils

Development of Bash text utilities: cat, grep.

### Usage of cat

Cat is one of the most frequently used commands on Unix-like operating systems. It has three related functions with regard to text files: displaying them, combining copies of them and creating new ones.

`./s21_cat [OPTION] [FILE]...`

### cat options

| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -b (GNU: --number-nonblank) | numbers only non-empty lines |
| 2 | -e implies -v (GNU only: -E the same, but without implying -v) | but also display end-of-line characters as $  |
| 3 | -n (GNU: --number) | number all output lines |
| 4 | -s (GNU: --squeeze-blank) | squeeze multiple adjacent blank lines |
| 5 | -t implies -v (GNU: -T the same, but without implying -v) | but also display tabs as ^I  |

### Usage of grep 

`./s21_grep [options] template [file_name]`

### grep options

| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -e | pattern |
| 2 | -i | Ignore uppercase vs. lowercase.  |
| 3 | -v | Invert match. |
| 4 | -c | Output count of matching lines only. |
| 5 | -l | Output matching files only.  |
| 6 | -n | Precede each matching line with a line number. |
| 7 | -h | Output matching lines without preceding them by file names. |
| 8 | -s | Suppress error messages about nonexistent or unreadable files. |
| 9 | -f file | Take regexes from a file. |
| 10 | -o | Output the matched parts of a matching line. |

<br>

- The programs are developed in C language of C11 standard using gcc compiler.
- The program code of the cat and grep are located in the src/cat/ and src/grep/ folders, respectively  
- The programs are executable files with command line arguments
- The programs are built with Makefile with targets: s21_cat, s21_grep
- The programs are developed according to the principles of structured programming
- Cat utility supports of all flags (including GNU versions) specified above
- The source, header, and build files must be placed in the src/cat/ directory
- The resulting executable file must be placed in the directory src/cat/ and named s21_cat
- Grep utility supports of the following flags: `-e`, `-i`, `-v`, `-c`, `-l`, `-n`, `-h`, `-s`, `-f`, `-o`
- Using regex library
- The source, header and make files must be placed in the src/grep/ directory
- The resulting executable file must be placed in the directory src/grep/ and named s21_grep
- Support of all flags, including their _pair_ combinations (e.g. `-iv`, `-in`)







