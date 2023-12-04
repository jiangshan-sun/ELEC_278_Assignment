#include "model.h"
#include "interface.h"

#include <stddef.h>
#include <stdlib.h>

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
        spreadsheet[row][col].value = evaluate_formula(spreadsheet[row][col].value);
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
    bool out = true;
    for (int i = 0; i < strlen(str); ++i) {
        if ( !(isdigit(str[i]) || str[i] == '.') )
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
    char *result = (char *) malloc(sizeof (char ) * (CELL_DISPLAY_WIDTH + 1));
    size_t num_token = 0;   // Count of token.
    double formula_value = 0.0;
    char **tokens = (char **) malloc(sizeof (char *) * (strlen(formula) + 1));
    char **iterator = tokens;
    char* token = strtok((char*)formula + 1, delims);
    while (token != NULL) {
        *iterator = strdup(token);
        iterator ++;
        num_token ++;
        token = strtok(NULL, "+");
    }
    for (int i = 0; i < num_token; ++i) {
        // printf("token: %s \n",tokens[i]);
        if(is_number(tokens[i])) {
            // Parse the number to 'double'.
            formula_value += strtod(tokens[i],NULL);
        } else{
            int Row_Col_num[2];
            find_cell(tokens[i],Row_Col_num);
            // printf("%s ",spreadsheet[Row_Col_num[0]][Row_Col_num[1]].value);
            formula_value += strtod(spreadsheet[Row_Col_num[0]][Row_Col_num[1]].value,NULL);
        }
    }
    snprintf(result,CELL_DISPLAY_WIDTH + 1,"%g",formula_value);
    // used for debug.
    printf("formula value: %s",result);
    free(tokens);
    return result;
}

bool find_cell(const char *cell, int *out) {
    // Row and Col number.
    char col = cell[0];
    char row = cell[1];
    int col_num = col - 'A';
    int row_num = row - '1';
    out[0] = row_num;   // Row number.
    out[1] = col_num;   // Col number.

    return true;
}


