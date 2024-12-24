#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINES 25
#define MAX_LINE_LENGTH 256
#define UNDO_LIMIT 3

char *buffer[MAX_LINES];
int line_count = 0;
char *undo_stack[UNDO_LIMIT];
int undo_top = -1;

// Initialize buffer
void init_buffer();

// Push operation to undo stack
void push_undo(const char *operation);

// Undo last operation
void undo();

// Load file into buffer
void load_file(FILE *file);

// Save buffer to file
void save_file(const char *filename);

// Insert line at specified position
void insert_line(const char *line, int pos);

// Delete line at specified position
void delete_line(int pos);

// Search for a word in the buffer
int search_word(const char *word);

// Replace word in buffer
void replace_word(const char *old_word, const char *new_word);

// Display buffer content
void display_buffer();

// Generate unique filename using timestamp
void generate_unique_filename(char *filename, size_t size);

// Handle command line arguments and create new files on each run
void handle_args(int argc, char *argv[]);

// Free memory allocated to buffer
void free_buffer();

// Delete word at a cursor
void delete_word_at_cursor(int line_num, int cursor_pos);

// Replace word at a cursor
void replace_word_at_cursor(int line_num, int cursor_pos, const char *new_word);

int main(int argc, char *argv[]) {
    init_buffer();
    handle_args(argc, argv);

    int choice;
    char temp[MAX_LINE_LENGTH];
    char word[MAX_LINE_LENGTH];
    int line_num, cursor_pos;

    do {
        printf("\n1. Display Buffer\n2. Insert Line\n3. Delete Line\n4. Search Word\n5. Replace Word\n6. Delete Word at Cursor\n7. Replace Word at Cursor\n8. Save File\n9. Undo\n10. Exit\n");
        printf("Enter your choice:");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid choice.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                display_buffer();
                break;
            case 2:
                printf("Enter line to insert:");
                if (fgets(temp, sizeof(temp), stdin) == NULL) {
                    printf("Error reading input.\n");
                    continue;
                }
                printf("Enter line number to insert at:");
                if (scanf("%d", &line_num) != 1 || line_num < 1 || line_num > MAX_LINES) {
                    printf("Invalid line number.\n");
                    continue;
                }
                insert_line(temp, line_num - 1);  // Adjust for 0-indexing
                break;
            case 3:
                printf("Enter line number to delete:");
                if (scanf("%d", &line_num) != 1 || line_num < 1 || line_num > line_count) {
                    printf("Invalid line number.\n");
                    continue;
                }
                delete_line(line_num - 1);
                break;
            case 4:
                printf("Enter word to search:");
                if (scanf("%s", word) != 1) {
                    printf("Invalid input.\n");
                    continue;
                }
                search_word(word);
                break;
            case 5:
                printf("Enter word to replace:");
                if (scanf("%s", word) != 1) {
                    printf("Invalid input.\n");
                    continue;
                }
                printf("Enter new word: ");
                if (scanf("%s", temp) != 1) {
                    printf("Invalid input.\n");
                    continue;
                }
                replace_word(word, temp);
                break;
            case 6:
                printf("Enter line number to delete word from:");
                if (scanf("%d", &line_num) != 1 || line_num < 1 || line_num > line_count) {
                    printf("Invalid line number.\n");
                    continue;
                }
                printf("Enter cursor position (start of word to delete):");
                if (scanf("%d", &cursor_pos) != 1 || cursor_pos < 0 || cursor_pos >= MAX_LINE_LENGTH) {
                    printf("Invalid cursor position.\n");
                    continue;
                }
                delete_word_at_cursor(line_num - 1, cursor_pos);
                break;
            case 7:
                printf("Enter line number to replace word in:");
                if (scanf("%d", &line_num) != 1 || line_num < 1 || line_num > line_count) {
                    printf("Invalid line number.\n");
                    continue;
                }
                printf("Enter cursor position (start of word to replace):");
                if (scanf("%d", &cursor_pos) != 1 || cursor_pos < 0 || cursor_pos >= MAX_LINE_LENGTH) {
                    printf("Invalid cursor position.\n");
                    continue;
                }
                printf("Enter new word:");
                if (scanf("%s", temp) != 1) {
                    printf("Invalid input.\n");
                    continue;
                }
                replace_word_at_cursor(line_num - 1, cursor_pos, temp);
                break;
            case 8:
                save_file(argv[1]);
                printf("File saved.\n");
                break;
            case 9:
                undo();
                break;
            case 10:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 10);

    free_buffer();
    return 0;
}


// Initialize buffer
void init_buffer() {
    for (int i = 0; i < MAX_LINES; i++) {
        buffer[i] = NULL;
    }
}

// Push operation to undo stack
void push_undo(const char *operation) {
    if (undo_top == UNDO_LIMIT - 1) {
        free(undo_stack[0]);
        for (int i = 0; i < UNDO_LIMIT - 1; i++) {
            undo_stack[i] = undo_stack[i + 1];
        }
        undo_top--;
    }
    undo_stack[++undo_top] = strdup(operation);
}

// Undo last operation
void undo() {
    if (undo_top == -1) {
        printf("Nothing to undo.\n");
        return;
    }
    printf("Undo:%s\n", undo_stack[undo_top]);
    free(undo_stack[undo_top--]);
}

// Load file into buffer
void load_file(FILE *file) {
    char temp[MAX_LINE_LENGTH];
    int i = 0;

    while (fgets(temp, sizeof(temp), file) && i < MAX_LINES) {
        buffer[i] = strdup(temp);
        i++;
    }
    line_count = i;
}

// Save buffer to file
void save_file(const char *filename) {
    if (filename == NULL) {
        filename = "file.txt";  // Default to "file.txt" if no file is specified
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < line_count; i++) {
        fprintf(file, "%s", buffer[i]);
    }
    fclose(file);
    printf("File saved successfully to %s.\n", filename);
}

// Insert line at specified position
void insert_line(const char *line, int pos) {
    if (pos < 0 || pos >= MAX_LINES) {
        printf("Invalid position.\n");
        return;
    }

    // Pad with empty lines if needed
    while (line_count <= pos) {
        buffer[line_count] = strdup("\n");
        line_count++;
    }

    // Shift lines downwards to make space
    for (int i = line_count; i > pos; i--) {
        buffer[i] = buffer[i - 1];
    }

    // Insert new line
    buffer[pos] = strdup(line);
    line_count++;
    push_undo("Inserted Line");
    printf("Line inserted at position %d.\n", pos + 1);
}

// Delete line at specified position
void delete_line(int pos) {
    if (pos < 0 || pos >= line_count) return;

    free(buffer[pos]);
    for (int i = pos; i < line_count - 1; i++) {
        buffer[i] = buffer[i + 1];
    }
    buffer[line_count - 1] = NULL;
    line_count--;
    push_undo("Deleted Line");
}

// Search for a word in the buffer
int search_word(const char *word) {
    for (int i = 0; i < line_count; i++) {
        char *pos = strstr(buffer[i], word);
        if (pos) {
            printf("Found at line %d:%s", i + 1, buffer[i]);
            return i;
        }
    }
    printf("Word not found.\n");
    return -1;
}

// Replace word in buffer
void replace_word(const char *old_word, const char *new_word) {
    for (int i = 0; i < line_count; i++) {
        char *pos = strstr(buffer[i], old_word);
        if (pos) {
            char temp[MAX_LINE_LENGTH];
            strncpy(temp, buffer[i], pos - buffer[i]);
            temp[pos - buffer[i]] = '\0';
            strcat(temp, new_word);
            strcat(temp, pos + strlen(old_word));

            free(buffer[i]);
            buffer[i] = strdup(temp);
            push_undo("Replaced Word");
        }
    }
}

// Display buffer content
void display_buffer() {
    printf("\nBuffer Contents:\n");
    for (int i = 0; i < line_count; i++) {
        printf("[%d]: %s", i + 1, buffer[i]);
    }
}

// Handle command line arguments and open/create files
// Generate unique filename using timestamp
void generate_unique_filename(char *filename, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(filename, size, "file_%Y%m%d_%H%M%S.txt", t);
}

// Handle command line arguments and create new files on each run
void handle_args(int argc, char *argv[]) {
    FILE *file;
    char path[256];

    if (argc == 1) {
        generate_unique_filename(path, sizeof(path));
    } else if (argc == 2) {
        snprintf(path, sizeof(path), "%s", argv[1]);
    } else if (argc == 3) {
        snprintf(path, sizeof(path), "%s/%s", argv[2], argv[1]);
    } else {
        fprintf(stderr, "Error: Too many arguments.\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(path, "w+");
    if (file == NULL) {
        perror("Error opening/creating file");
        exit(EXIT_FAILURE);
    }

    printf("New file created: %s\n", path);
    load_file(file);
    fclose(file);

    // Save the filename for later use in saving
    argv[1] = strdup(path);
}

// Free memory allocated to buffer
void free_buffer() {
    for (int i = 0; i < line_count; i++) {
        free(buffer[i]);
    }
}

// Delete word at a cursor in the specified line
void delete_word_at_cursor(int line_num, int cursor_pos) {
    if (line_num < 0 || line_num >= line_count) return;

    char *line = buffer[line_num];
    int i = cursor_pos;

    // Find the word to delete
    while (i < strlen(line) && (line[i] != ' ' && line[i] != '\n')) {
        i++;
    }

    // Remove the word
    memmove(line + cursor_pos, line + i, strlen(line) - i + 1);
    push_undo("Deleted Word");
    printf("Word deleted at cursor position %d in line %d.\n", cursor_pos, line_num + 1);
}

// Replace word at a cursor in the specified line
void replace_word_at_cursor(int line_num, int cursor_pos, const char *new_word) {
    if (line_num < 0 || line_num >= line_count) return;

    char *line = buffer[line_num];
    int i = cursor_pos;

    // Find the word to replace
    while (i < strlen(line) && (line[i] != ' ' && line[i] != '\n')) {
        i++;
    }

    // Replace with the new word
    memmove(line + cursor_pos + strlen(new_word), line + i, strlen(line) - i + 1);
    memcpy(line + cursor_pos, new_word, strlen(new_word));

    push_undo("Replaced Word");
    printf("Word replaced at cursor position %d in line %d.\n", cursor_pos, line_num + 1);
}
