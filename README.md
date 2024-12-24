Text File Editor Documentation
Overview
This program implements a simple text file editor with features such as inserting, deleting, searching, replacing words, undoing operations, and saving/loading files. It uses an in-memory buffer to manage the file content and provides a user interface through the command line to interact with the file content.

Features
Insert Line: Add a new line at a specified position in the file.
Delete Line: Delete a line at a specified position.
Search Word: Search for a specific word in the file.
Replace Word: Replace a word with a new one throughout the file.
Delete Word at Cursor: Delete a word from a specific position in a line.
Replace Word at Cursor: Replace a word at a specific position in a line.
Undo: Undo the last operation performed (insert, delete, replace, etc.).
Save File: Save the file to the disk.
Load File: Load the file into the program's buffer.
Data Structures
Buffer: A global buffer is used to store the contents of the file, where each line is represented as a string.

char *buffer[MAX_LINES]: An array of pointers to strings, each representing a line in the file.
int line_count: Keeps track of the number of lines in the buffer.
Undo Stack: A stack is used to store the last few operations for undo functionality.

char *undo_stack[UNDO_LIMIT]: An array to store the last operations performed.
int undo_top: Keeps track of the top of the undo stack.
Functions
1. void init_buffer();
   Initializes the buffer by setting all lines to NULL and resets the line count.

2. void push_undo(const char *operation);
   Pushes the given operation onto the undo stack. If the undo stack exceeds the limit, the oldest operation is removed.

3. void undo();
   Undoes the last operation by popping the undo stack and displaying the operation that was undone.

4. void load_file(FILE *file);
   Loads the content of a file into the buffer. Each line in the file is copied into the buffer.

5. void save_file(const char *filename);
   Saves the content of the buffer into the specified file. If no filename is provided, it defaults to file.txt.

6. void insert_line(const char *line, int pos);
   Inserts a new line at the specified position in the buffer. If the position is invalid, an error is displayed. The lines after the insertion point are shifted down.

7. void delete_line(int pos);
   Deletes a line from the buffer at the specified position. The lines after the deletion point are shifted up.

8. int search_word(const char *word);
   Searches for a word in the buffer. If the word is found, its line and content are displayed; otherwise, a message indicates that the word was not found.

9. void replace_word(const char *old_word, const char *new_word);
   Replaces all occurrences of the old word in the buffer with the new word.

10. void display_buffer();
    Displays the content of the buffer on the screen, showing each line and its content.

11. void generate_unique_filename(char *filename, size_t size);
    Generates a unique filename using the current timestamp.

12. void handle_args(int argc, char *argv[]);
    Handles command-line arguments and creates or opens a file based on the arguments. It also generates a unique filename if no filename is provided.

13. void free_buffer();
    Frees the memory allocated for the buffer lines.

14. void delete_word_at_cursor(int line_num, int cursor_pos);
    Deletes a word at the specified cursor position in the given line.

15. void replace_word_at_cursor(int line_num, int cursor_pos, const char *new_word);
    Replaces a word at the specified cursor position in the given line with the new word.

Global Variables
char *buffer[MAX_LINES]: The buffer array to store lines of the text file.
int line_count: Keeps track of the number of lines in the buffer.
char *undo_stack[UNDO_LIMIT]: The undo stack to store the last few operations.
int undo_top: Tracks the top of the undo stack.
Constants
MAX_LINES: Maximum number of lines that the buffer can hold.
MAX_LINE_LENGTH: Maximum length of each line in the buffer.
UNDO_LIMIT: Maximum number of operations that can be stored in the undo stack.
Usage
1. Running the Program
   You can compile and run the program using the following commands:

bash
Copy code
gcc -o file_editor file_editor.c
./file_editor
The program will display a menu with various options:

1. Display Buffer: Show the contents of the file loaded into the buffer.
2. Insert Line: Insert a new line at a specified position.
3. Delete Line: Delete a line at a specified position.
4. Search Word: Search for a specific word in the buffer.
5. Replace Word: Replace a word in the buffer.
6. Delete Word at Cursor: Delete a word at the cursor's position in a specified line.
7. Replace Word at Cursor: Replace a word at the cursor's position in a specified line.
8. Save File: Save the current buffer to a file.
9. Undo: Undo the last operation.
10. Exit: Exit the program.
2. Command-Line Arguments
   The program accepts command-line arguments to specify the filename. For example:

bash
Copy code
./file_editor myfile.txt
If no filename is provided, a unique filename is generated using the current timestamp.

3. Memory Management
   The program dynamically allocates memory for each line in the buffer using strdup() and frees it using free() to avoid memory leaks.

Example Run
bash
Copy code
1. Display Buffer
2. Insert Line
3. Delete Line
4. Search Word
5. Replace Word
6. Delete Word at Cursor
7. Replace Word at Cursor
8. Save File
9. Undo
10. Exit
    Enter your choice: 2
    Enter line to insert: Hello, World!
    Enter line number to insert at: 1
    Line inserted at position 1.

1. Display Buffer
2. Insert Line
3. Delete Line
4. Search Word
5. Replace Word
6. Delete Word at Cursor
7. Replace Word at Cursor
8. Save File
9. Undo
10. Exit
    Enter your choice: 1
    Buffer Contents:
    [1]: Hello, World!
    Limitations
    The program can handle only a limited number of lines (defined by MAX_LINES).
    The undo functionality is limited to a fixed number of operations (defined by UNDO_LIMIT).
    File handling is simulated through memory (using local storage in some cases), and actual file reading and writing can be done via file I/O.
    Conclusion
    This text file editor provides basic editing functionality for text files. It includes file manipulation features such as loading, saving, and editing the content. The undo functionality helps revert changes, making it a simple yet useful tool for text file management.