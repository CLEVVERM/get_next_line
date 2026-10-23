*This project has been created as part of the 42 curriculum by msotnych.*

# Get Next Line

## Description

Get Next Line is a project of the 42 curriculum. The goal is to write a function,
`get_next_line()`, that returns **one line** from a file descriptor every time it
is called. When it is called in a loop, it reads a whole text file (or the
standard input) line by line, without loading the whole file into memory.

```c
char *get_next_line(int fd);
```

- The returned line includes the ending `'\n'`, except for the last line of a file
  that does not end with `'\n'`.
- It returns `NULL` when there is nothing left to read, or when an error occurs.
- The caller must `free` every returned line.
- Only `read`, `malloc` and `free` are allowed. `libft`, `lseek` and global
  variables are forbidden.

The project teaches two things: **static variables** (a value that survives between
function calls) and careful **dynamic memory management**.

### Files

| File | Content |
|---|---|
| `get_next_line.c` | `get_next_line()` and its `static` helpers |
| `get_next_line_utils.c` | small string helpers |
| `get_next_line.h` | prototypes and the default `BUFFER_SIZE` |
| `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, `get_next_line_bonus.h` | bonus version: several file descriptors at the same time |

## Instructions

There is no Makefile in this project. The files are compiled together with your
own `main` file. `BUFFER_SIZE` is the number of bytes that `read()` asks for each
time. It is given with the `-D` flag. If the flag is not used, the header sets a
default value of 1024.

### Compilation

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
./a.out file.txt
```

Bonus:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=10 get_next_line_bonus.c get_next_line_utils_bonus.c main.c
```

### Usage

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

## Functions

A few basics used in the descriptions below:

- A **file descriptor** is a number that identifies an open file. `0` is the standard input (the keyboard), `1` is the screen, `2` is the error output, and every file opened with `open` gets its own number.
- `read(fd, buffer, n)` asks for up to `n` bytes from a file descriptor and puts them in `buffer`. It returns how many bytes it really read: a number bigger than 0 means data was read, `0` means the end of the file, and `-1` means an error. It does not know anything about lines, so a chunk can contain several lines or only a piece of one.
- `read` does **not** add a `'\0'` at the end of the data. The code has to add it, because C strings need it.
- `'\n'` (newline) ends a line in a text file. `'\0'` is different: it ends a C string in memory.
- A **`static` variable** inside a function is created once and keeps its value between calls, unlike a normal variable that disappears when the function returns. In this project it keeps the text that was read but not yet returned.
- "Allocates" means the function reserves new memory with `malloc`. Somebody must `free` it later.

### Part 1 - The main function (`get_next_line.c`)

- **`get_next_line`**: returns the next line of the file descriptor. It keeps one `static` pointer, called the *stash*, with the text that was read from the file but not returned yet. First it returns `NULL` right away if `fd` is negative or `BUFFER_SIZE` is 0 or less. Then it does four steps: reads more text into the stash if needed (`read_str`), cuts the first line out of it (`put_str`), keeps the rest as the new stash (`str_rest`), and returns the line.

### Part 2 - Helpers inside `get_next_line.c`

These are `static`, so they are visible only inside this file. The Norm allows only 25 lines per function, so the work is split into small helpers.

- **`join_str`**: glues the stash and a newly read piece into a new string (using `ft_strjoin`), then frees the old stash. It returns the new string, or `NULL` if the allocation failed. The result must always be saved back into the variable, because the old address is not valid anymore.
- **`read_str`**: fills the stash. It allocates a buffer of `BUFFER_SIZE + 1` bytes (one extra byte for the `'\0'`) and repeats: while the stash has no `'\n'` and the last `read` did not return `0`, it reads a chunk, puts a `'\0'` after the bytes that were read, and appends the chunk to the stash with `join_str`. If the stash already has a `'\n'` from a previous call, it reads nothing at all. If `read` returns `-1` or an allocation fails, it frees the stash and the buffer and returns `NULL`. At the end it frees the buffer.
- **`put_str`**: makes the line to return. It returns a new copy of the stash from its start up to and including the first `'\n'`, or the whole stash if there is no `'\n'` (the last line of the file). If the stash is `NULL` or empty, there is nothing left, so it returns `NULL`.
- **`str_rest`**: makes the new stash. It returns a new copy of everything that comes after the first `'\n'` and frees the old stash. If there is no `'\n'`, nothing remains, so it frees the stash and returns `NULL`. This must be called **after** `put_str`, because it frees the text that `put_str` copies from.

### Part 3 - Utility functions (`get_next_line_utils.c`)

`libft` is not allowed in this project, so the helper functions were written again here.

- **`ft_strlen`**: counts the characters of a string before the `'\0'`. For a `NULL` pointer it returns `0`, so it is safe to call on an empty stash.
- **`find_n`**: looks for the first `'\n'` in a string and returns its index. If there is none (or the string is `NULL`) it returns `-1`. The value `-1` is used because `0` is a valid index: `'\n'` can be the very first character of the string.
- **`ft_strjoin`**: glues two strings into a new string. A `NULL` string is treated as an empty one, so the first join (when the stash is still `NULL`) works without a special case. The original strings are not changed.
- **`ft_substr`**: makes a new string from a piece of another one: it starts at index `start` and takes up to `len` characters (fewer if the string ends earlier). If `start` is beyond the end of the string, the result is an empty string. A `NULL` input returns `NULL`.
- **`free_str`**: takes the **address** of a pointer (`char **`), frees the memory and sets the pointer to `NULL`. This way the pointer is never used again after it was freed, and calling `free_str` on a pointer that is already `NULL` does nothing.

### Part 4 - Bonus (`*_bonus.*`)

The bonus files have the same functions. The only difference is in `get_next_line`: instead of one stash it has an array of stashes, `static char *buff[1024]`, and the file descriptor is the index. So `buff[3]` is the stash of file descriptor 3, `buff[4]` of file descriptor 4, and so on. This allows reading from several files in turns (`fd 3`, `fd 4`, `fd 3`, ...) without mixing them up. An array is still **one** static variable, as the bonus requires. A file descriptor outside of the array (`fd < 0` or `fd >= 1024`) returns `NULL`.

## How it works

`read()` gives a fixed number of bytes and does not care where a line ends. So the function reads chunks, keeps what it does not need yet, and returns only one line at a time.

Each call of `get_next_line` does this:

1. **Read** (`read_str`): if the stash has no `'\n'` yet, read chunks of `BUFFER_SIZE` bytes and add them to the stash, until a `'\n'` appears or the file ends.
2. **Cut the line** (`put_str`): copy everything up to and including the first `'\n'`.
3. **Keep the rest** (`str_rest`): the text after the `'\n'` becomes the new stash, for the next call.
4. **Return** the line.

### Example

File content: `ab\ncd\nef` (no `'\n'` at the end), `BUFFER_SIZE = 4`.

| Call | Read | Stash after reading | Returned | Stash after the call |
|---|---|---|---|---|
| 1 | `ab\nc` | `ab\nc` | `ab\n` | `c` |
| 2 | `d\nef` | `cd\nef` | `cd\n` | `ef` |
| 3 | nothing (`read` returns 0) | `ef` | `ef` | `NULL` |
| 4 | nothing (`read` returns 0) | empty | `NULL` | `NULL` |

In call 2 the stash `c` has no `'\n'`, so one more chunk is read and joined to it. In call 3 there is no `'\n'` anymore, so the rest of the file is returned as the last line, without a `'\n'`.

### Special cases

- **Empty file**: the first call returns `NULL`.
- **File without `'\n'` at the end**: the last line is returned without it.
- **Empty lines**: a line that has only `'\n'` is returned as `"\n"` (not as `NULL`), so it can be told apart from the end of the file.
- **After the end of the file**: every next call returns `NULL`.
- **Invalid or closed file descriptor**: `read` returns `-1`, so the function returns `NULL`.
- **`read` error or failed `malloc`**: everything that is held is freed and `NULL` is returned. Nothing leaks.
- **`BUFFER_SIZE`**: works with any positive value (tested with 1, 2, 3, 42, 9999 and 10000000).

### Why this approach

- It reads as little as needed: it stops reading as soon as a `'\n'` is found and never loads the whole file.
- One `static` pointer is enough to keep the state between calls, so no global variable is needed.
- It works on any file descriptor, including the standard input.
- Every allocated pointer is freed on every exit path. `free_str` also sets pointers to `NULL`, so a freed pointer is never used again.

**Known trade-off.** For a line of length `L` and a buffer of size `B`, the loop runs about `L / B` times. Each time it searches the stash from the start and copies the whole stash into a new string, so the work grows roughly as `L² / B`. For normal files this is fast. The slow case is a very long line with a very small `BUFFER_SIZE`. A possible improvement is to remember where the search for `'\n'` stopped, instead of starting from the beginning each time.

## Logic and techniques used

This section explains the main ideas used in the code and where they appear.

### Static variable

A `static` variable keeps its value between calls. It is used in **`get_next_line`** to keep the stash: the text that `read` already took from the file but that belongs to the next lines. Without it, this text would be lost when the function returns. In the bonus, the same idea is used with an array, so each file descriptor has its own stash.

### Reading in a loop

`read` can return less than asked, and a line can be longer than the buffer. So **`read_str`** reads in a loop and stops only for two reasons: a `'\n'` is in the stash, or `read` returned `0` (end of the file). The value `-1` (error) stops it too, with cleanup.

### Memory management

Every allocation has an owner who must free it:

- the read buffer is allocated and freed inside `read_str`;
- the old stash is freed by `join_str` and `str_rest`, right after the new one is made;
- the returned line belongs to the caller.

Every function that allocates checks the result of `malloc`, and the error paths free everything that is still held, so there are no leaks even when `read` or `malloc` fails.

### Static helper functions

When a function is too long for the Norm, the work is split into helpers declared `static`, so they are visible only in their file: `join_str`, `read_str`, `put_str` and `str_rest` in `get_next_line.c`.

### Reusing my own functions

- `join_str` uses `ft_strjoin` and `free_str`.
- `read_str` uses `find_n`, `join_str` and `free_str`.
- `put_str` uses `find_n`, `ft_strlen` and `ft_substr`.
- `str_rest` uses `find_n`, `ft_strlen`, `ft_substr` and `free_str`.
- `ft_strjoin` and `ft_substr` use `ft_strlen`.

Recursion is not used in this project: a loop is enough to read chunk after chunk.

## Resources

- [Linux man pages (`man 2 read`, `man 2 open`, `man 3 malloc`, `man 3 free`)](https://linux.die.net/man/)
- The Get Next Line subject (`en_subject_get_next_line.pdf`, version 14.3)
- [Wikipedia](https://www.wikipedia.org/), ["Static variable"](https://en.wikipedia.org/wiki/Static_variable), and web searches about `static` variables and about `read()` in C.
- [Peer discussions with other 42 students](https://www.42network.org/)

### Use of AI

AI ([Claude](https://claude.com/)) was used:

- **Explanations:** to clarify concepts: what `read()` returns, how a `static` variable behaves, how `-D BUFFER_SIZE` works, and how pointers to pointers and `free` work.
- **Plan and review:** to check my paper plan of the algorithm.
- **Testing:** to write a throw-away `main` for tests (not part of the submission) and to help read the tester output.
- **README:** a draft of this file was generated with AI and then reviewed and edited by me.