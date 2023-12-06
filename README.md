# <center> Spreadsheet Program Design and Implementation Report

<div style="text-align: center;"> SUN,Jiangshan </div>

<div style="text-align: center;"> Dec 06, 2023 </div>


**Statement:**
I, SUN,Jiangshan, attest that all of the materials which I am submitting for this assignment are my own and were written 
solely by me. I have cited in this report any sources, other than the class materials, which I used in creating any part 
of this assignment. Furthermore, this work adheres to the policy on generative artificial intelligence as documented in
the instructions.

---

## 1. Executive Summary

This report documents the design and implementation of a spreadsheet program, adhering to the specified functional 
requirements (FRs) and non-functional requirements (NFRs). 
The program allows users to navigate cells, modify values, and handles text, numbers, and formulas. 
The design focuses on a structured data model, efficient cell updates, and support for formulas and dependencies.

---

## 2. Design

### 1. Design Proposal

#### Approach
The design approach centers around creating a robust data structure to represent cells, incorporating a variety of data 
types and supporting formulas.

```
enum CellType {
    FORMULA,
    NUMBER,
    TEXT
};

typedef struct Cell{
    enum CellType type; // Cell type.
    char *value; // Storage value.
    char *formula;   // Storage formula itself.
    struct Cell *dependency;    // Pointer to dependent cell.
    ROW row;    // Row number.
    COL col;    // Col number.
    size_t change;  // Counts of changes.

} Cell;

Cell spreadsheet[NUM_ROWS][NUM_COLS];

```

The program utilizes a 2D array of cells, each with attributes for type, value, formula, 
dependencies, and change counts. To be specific, for each cell, I design `type` to illustrate the type
of it because `value` is always a 'string'. With this design, the programme can easily distinct
the type of cell by judging its `type`. To make the programme support 'Formula', I design another 'string'
`formula` to storage the text of the formula in case that `get_textual_value` function can get the formula itself rather than
its value. Furthermore, I design a `struct Cell *dependency` pointer to point to the cell it depends on so that
every time the dependant cell changes, it will change as well. To make the programme can read a given cell, I design
`row` and `col` to represent the Row and Col number of it. At last, I design `change` to count how many times the cell has 
changed, so that the `set_cell_value` function can skip the first modification.

#### Data Structures and Algorithms
- **Cell Structure:** A `Cell` struct includes fields for type, value, formula, dependency, row, column, and change count.
- **2D Array:** The spreadsheet is represented as a 2D array of cells.
- **Formula Evaluation:** The `evaluate_formula` function parses and evaluates formulas, updating dependent cells. 
The basic idea is divide the formula into tokens according to the delimiter and calculate the tokens separately.
- **Dependency Management:** Each cell stores a pointer to its dependent cell, facilitating efficient updates.
- **Helper function:** To implement the algorithms above, I also introduce the following helper function to make 
the programme modularized.

```
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
```

#### Design Rationale
The chosen design facilitates easy navigation, modification, and formula evaluation. Storing dependencies allows for 
automatic updates when a cell changes. The 2D array provides a straightforward representation of the spreadsheet.

#### FR Satisfaction
- **FR 1:** Navigation and modification are supported by the data structure and functions like `set_cell_value` and `clear_cell`.
- **FR 2:** Formulas are handled through the `evaluate_formula` function, distinguishing between numbers, text, and formulas.
- **FR 3:** Displayed contents are updated through `update_cell_display`, ensuring accurate representations.
- **FR 4:** Dependent cells are updated via the dependency mechanism in `set_cell_value`.

### Implementation

#### Code Overview
The implemented code follows the proposed design closely. Key aspects include the `Cell` struct, 2D array initialization 
in `model_init`, and functions for setting values, clearing cells, and evaluating formulas.
- **Initialization:** Traverse the NUM_ROWS * NUM_COLS spreadsheet, then set the default type to `TEXT`, the `formula` and `value`
    to an empty string `'/0'` and set the `dependency` pointer to `NULL`.
- **Set the cell value:** First navigate to the given `row` and `col`, then copy the `text` to the `value` of corresponding cell and then determine 
    the type and save it to `type`. Here I used helper functions `bool is_formula(const char *str)` and `bool is_number(const char *str)`
    which are used to judge the cell `type`. Then, if the `value` is a `FORMULA`, we should evaluate it and save the results to the `value`, in the meanwhile, we should copy the formula text to
    `formula`. However, if the `value` is a `NUMBER`, we should update the dependent cell. Last, I call the `update_cell_display(row, col, spreadsheet[row][col].value)` function
    to display the cell to the screen.
- **Clear the cell:** Set the corresponding cell to initial states, which is basically the same as `model_init` part.
- **Get textual value:** If the `type` is a `FORMULA` then output the `spreadsheet[row][col].formula`, otherwise(i.e. `NUMBER` or `TEXT`) output
    the `spreadsheet[row][col].value`.
- **Evaluate a formula:** Here I used a C library function `char *strtok(char *__str, const char *__sep)`to divide the 
    formula into tokens and evaluate them separately. If a token is a cell coordinates, we find the corresponding cell and 
    then get its value. I also add error handling features to indicate that `TEXT` can not be evaluated.

#### Changes Made During Implementation
- **Memory Management:** Improved memory management in functions like `set_cell_value` and `evaluate_formula`. 
    By guaranteeing `malloc()` and `free()` is pairing with each other, I can make sure that any dynamically allocated memory
    is freed once it is no longer needed.

- **Change Counts:** Introduced a change count to track modifications and trigger updates in dependent cells.

### Testing

#### Test Approach
Testing involved running the program with various inputs and checking if the displayed values matched expectations. 
Manual testing was performed to cover basic use cases, formula evaluations, and dependency updates.

#### Screenshots
1. Type '1.2' into cell 'A1', type '1.9' into cell 'B2', type '=A1+B2' into cell 'C3' and then press 'enter'.
The programme can get the value '3.1' which indicates that the programme can set the cell value and evaluate the formula
successfully.
   <img alt="Initial Spreadsheet" src="/Users/sunjiangshan/Desktop/Queen&#39;s/ELEC 278 Fnm Of Info Struc/Assignment/Test/Screenshot 2023-12-06 at 15.22.39.png"/>
*Figure 1: Initial Spreadsheet State*

2. Navigate to cell 'B2' and press 'delete-character key'. The cell 'B2' has been successfully cleared which shows that
the `clear_cell` function works.
   <img alt="Clear cell" src="/Users/sunjiangshan/Desktop/Queen&#39;s/ELEC 278 Fnm Of Info Struc/Assignment/Test/Screenshot 2023-12-06 at 15.34.14.png"/>
*Figure 2: Spreadsheet After Value cleaned*

3. Type '2.2' into cell 'B2' and press 'enter'. The cell 'C3' turned to 3.4 which means the cell can be successfully updated.
   <img alt="Updated Spreadsheet" src="/Users/sunjiangshan/Desktop/Queen&#39;s/ELEC 278 Fnm Of Info Struc/Assignment/Test/Screenshot 2023-12-06 at 15.23.55.png"/>
*Figure 3: Spreadsheet After Value Update*

---

## 3. Citations

1. [Convert double/float to string](https://stackoverflow.com/questions/7228438/convert-double-float-to-string)
2. [C Program For Double to String Conversion](https://www.geeksforgeeks.org/c-program-for-double-to-string-conversion/)
3. [C exit(), abort() and assert() Functions](https://www.geeksforgeeks.org/c-exit-abort-and-assert-functions/)
4. [strtok() and strtok_r() functions in C with examples](https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/)
5. Use [GitHub](https://github.com/jiangshan-sun/ELEC_278_Assignment) to keep my code.
---

*End of Report.*
