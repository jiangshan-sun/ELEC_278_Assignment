#ifndef ASSIGNMENT_MODEL_H
#define ASSIGNMENT_MODEL_H

#include "defs.h"

#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include <stdio.h>

// Initializes the data structure.
//
// This is called once, at program start.
void model_init();

// Sets the value of a cell based on user input.
//
// The string referred to by 'text' is now owned by this function and/or the
// cell contents data structure; it is its responsibility to ensure it is freed
// once it is no longer needed.
void set_cell_value(ROW row, COL col, char *text);

// Clears the value of a cell.
void clear_cell(ROW row, COL col);

// Gets a textual representation of the value of a cell, for editing.
//
// The returned string must have been allocated using 'malloc' and is now owned
// by the interface. The cell contents data structure must not modify it or
// retain any reference to it after the function returns.
char *get_textual_value(ROW row, COL col);

// Check whether 'str' starts with 'prefix'.
bool starts_with(const char *str, const char *prefix);

// Check whether 'str' is a number.
bool is_number(const char *str);

// Check whether 'str' is a formula.
bool is_formula(const char *str);

// Function to evaluate a formula and return the computed value.
char *evaluate_formula(const char* formula,ROW row,COL col);

// Get the Row and Col number of corresponding cell.
bool find_cell(const char *cell, int *out);

#endif //ASSIGNMENT_MODEL_H
