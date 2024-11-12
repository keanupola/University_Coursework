# Airline Route Record System

## Project Description

The **Airline Route Record System** is a C program that manages airline routes and passenger data for different airlines over a six-month period. It allows users to:

- **Load and parse data** from CSV files containing airline route information.
- **Search** for routes based on various criteria such as route, origin airport, destination airport, or airline.
- **Display** total and average passenger numbers for matching records.
- **Interact** with a menu-driven command-line interface.

## Features

- **Data Management:**
  - Efficient handling of airline route data using dynamic memory allocation.
  - Storage of passenger counts for six months per route.

- **File I/O:**
  - Reading and parsing CSV files containing route and passenger data.
  - Dynamic creation and filling of records from file data.

- **Search Functionality:**
  - Search by route (origin and destination airports).
  - Search by origin airport.
  - Search by destination airport.
  - Search by airline.

- **Statistical Output:**
  - Total passengers for matching records.
  - Monthly passengers for each month.
  - Average passengers per month.

- **User Interface:**
  - Command-line menu for user interaction.
  - Input validation and error handling.

## Technologies Used

- **Programming Language:** C
- **Tools:**
  - GCC Compiler
  - Makefile for building the project

## Installation and Usage

### Prerequisites

- GCC compiler installed on your system (e.g., via `gcc` on Linux/Mac or MinGW on Windows).

### Build Instructions

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/keanupola/University_Coursework.git
   ```

2. **Navigate to the Project Directory:**
   ```bash
   cd University_Coursework/CS_1714_Computer_Programming_II/projects/Airline_Route_Record_System
    ```


3. **Compile the Program Using the Makefile:**
   - **On Linux/Mac:**
     ```bash
     make
     ```
   - **On Windows (using MinGW or similar):**
     ```cmd
     mingw32-make
     ```

### Run Instructions

- **Execute the Compiled Program:**
  ```bash
  ./project2 data.csv
  ```

- **Program Usage:**
  - The program will display a menu with options to search records.
  - Enter the corresponding number for the desired action.
  - Follow the prompts to input search criteria.
  - To exit the program, select the "Quit" option from the menu.

### Clean Up

- **Remove Compiled Files:**
  ```bash
  make clean
  ```

## Files in the Project

- **Source Files:**
  - `main.c` - The main driver of the program containing the main function and menu handling.
  - `route-records.c` - Implementation of functions for creating, filling, and searching route records.
  - `route-records.h` - Header file declaring structures and function prototypes.

- **Data Files:**
  - `data.csv` - Sample data file containing airline route information.
  - `passenger-data-short.csv` - A shorter sample data file for testing.

- **Build Files:**
  - `Makefile` - Contains build instructions for compiling the program.
