#include "model.h"
#include "interface.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

enum CellType {
    FORMULA,
    NUMBER,
    TEXT
};

typedef struct Cell{
    enum CellType type;
    char *value; // Value that cell storages.
} Cell;

Cell spreadsheet[NUM_ROWS][NUM_COLS];

// Represents an error that occurred in the input.
struct error {
    // The position in the input string where the error occurred.
    const char *pos;
    // A description of the error; this must be a string literal, not a dynamically allocated string.
    const char *desc;
};

void model_init() {
    // TODO: implement this.
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS; ++j) {
            // Initialize all cells to be empty.
            spreadsheet[i][j].type = TEXT;  // Initialize the type to TEXT.
            spreadsheet[i][j].value = strdup("");   // Allocate memories.
        }
    }
}

void set_cell_value(ROW row, COL col, char *text) {
    // TODO: implement this.
    // Copy the value.
    spreadsheet[row][col].value = strdup(text);

    // Determine the type.
    // Determine if it is a formula.
    if (is_formula(spreadsheet[row][col].value)) {
        // Evaluate the validity.
        spreadsheet[row][col].type = FORMULA;
    } else if (is_number(spreadsheet[row][col].value))
        spreadsheet[row][col].type = NUMBER;
    else
        spreadsheet[row][col].type = TEXT;

    // This just displays the text without saving it in any data structure. You will need to change this.
    update_cell_display(row, col, spreadsheet[row][col].value);
    free(text);
}

void clear_cell(ROW row, COL col) {
    // TODO: implement this.
    spreadsheet[row][col].value = strdup("");
    spreadsheet[row][col].type = TEXT;
    // This just clears the display without updating any data structure. You will need to change this.
    update_cell_display(row, col, spreadsheet[row][col].value);
}

char *get_textual_value(ROW row, COL col) {
    // TODO: implement this.
    char *out = NULL;
    out = strdup(spreadsheet[row][col].value);
    return out;
}

bool starts_with(const char *str, const char *prefix) {
    return *prefix == '\0' || *str == *prefix && starts_with(str + 1, prefix + 1);
}

bool is_number(const char *str) {
    bool out;
    for (int i = 0; i < strlen(str); ++i) {
        if (isdigit(str[i]) || str[i] == '.' )
            out = true;
        else
            out = false;
    }
    return out;
}

bool is_formula(const char *str) {
    bool out;   // The output.
    // TODO: Need to check cell validity.
    if (starts_with(str,"="))
        out = true;
    else
        out = false;
    return out;
}
char *evaluate_formula(const char* formula) {
    // For simplicity, this example assumes a basic formula with addition only
    // You need to implement a more comprehensive formula evaluation based on your requirements
    char delims[] = "+";  // Can be modified to support more formula evaluation.
    char *result = NULL;
    size_t num_token = 0;   // Count of token.
    char **tokens = (char **) malloc(sizeof (char **) * (strlen(formula) + 1));
    char **iterator = tokens;
    char* token = strtok((char*)formula + 1, delims);
    while (token != NULL) {
        *iterator = strdup(token);
        iterator ++;
        num_token ++;
        token = strtok(NULL, "+");
    }
    for (int i = 0; i < num_token; ++i) {
        printf("token: %s \n",tokens[i]);
    }
    return result;
}