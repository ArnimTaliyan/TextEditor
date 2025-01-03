﻿# Text File Editor

## Overview
A simple text file editor with functionality for inserting, deleting, searching, replacing words, undoing operations, and saving/loading files. It operates using an in-memory buffer to manage file content.

## Features
- **Insert Line**: Add a new line at a specified position.
- **Delete Line**: Delete a line at a specified position.
- **Search Word**: Search for a word in the file.
- **Replace Word**: Replace a word with a new one.
- **Delete Word at Cursor**: Delete word at cursor position.
- **Replace Word at Cursor**: Replace word at cursor position.
- **Undo**: Undo the last operation.
- **Save File**: Save the file to disk.
- **Load File**: Load the file into the editor.

## Usage

### Running the Program
1. Compile and run:
   ```bash
   gcc -o TextEditor TextEditor.c
   ./TextEditor
    ```
## Menu Options
- **Display Buffer**: View the contents of the file.
- **Insert Line**: Insert a line at a specified position.
- **Delete Line**: Delete a line at a specified position.
- **Search Word**: Search for a word in the file.
- **Replace Word**: Replace a word in the file.
- **Delete Word at Cursor**: Delete word at cursor position.
- **Replace Word at Cursor**: Replace word at cursor position.
- **Save File**: Save the file to disk.
- **Undo**: Undo the last operation.
- **Exit**: Exit the program.

## Example

```bash
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
Enter line number: 1
Line inserted at position 1.
```
## Limitations
- Limited number of lines (`MAX_LINES`).
- Undo stack limited by `UNDO_LIMIT`.
- Simple file handling with in-memory buffer.

## Conclusion
A basic text editor with essential text manipulation features and undo functionality. Perfect for small file editing tasks.
