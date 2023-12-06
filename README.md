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

#### Changes Made During Implementation
- **Memory Management:** Improved memory management in functions like `set_cell_value` and `evaluate_formula`.
- **Change Counts:** Introduced a change count to track modifications and trigger updates in dependent cells.

### Testing

#### Test Approach
Testing involved running the program with various inputs and checking if the displayed values matched expectations. 
Manual testing was performed to cover basic use cases, formula evaluations, and dependency updates.

#### Screenshots
![Initial Spreadsheet](screenshots/initial_spreadsheet.png)
*Figure 1: Initial Spreadsheet State*

![Updated Spreadsheet](screenshots/updated_spreadsheet.png)
*Figure 2: Spreadsheet After Value Update*

### Citations

No external resources were used in creating this solution. All code and design decisions are original.

---

*Note: Include screenshots in the provided path `screenshots/` for better clarity.*

*End of Report.*
