# Implementing Machine Learning Algorithms

## Project Description

This project involves implementing two fundamental machine learning algorithms from scratch:

1. Gradient Descent for Linear Regression
2. ID3 Algorithm for Decision Trees

The purpose is to understand the inner workings of these algorithms by coding them without relying on high-level machine learning libraries.

## Running on Google Colab
You can also run this notebook on Google Colab: [Open in Google Colab](https://colab.research.google.com/drive/13p44_GLFyvbDXDPBxJVpHuh38qDoUL16?usp=sharing)

## Features

- **Gradient Descent**:
  - Implements linear regression using gradient descent optimization.
  - Reads training and testing data from provided .dat files.
  - Plots the cost function over iterations.

- **ID3 Decision Tree**:
  - Constructs a decision tree based on training data.
  - Uses information gain to select the best features.
  - Evaluates the decision tree on test data.

## Technologies Used

- **Programming Language**: Python 3
- **Libraries**:
  - numpy
  - pandas
  - matplotlib (for plotting)

## Installation and Usage

### Prerequisites

- Python 3.x installed
- Required Python libraries installed

### Setup Instructions

1. Clone the Repository:
   ```bash
   git clone https://github.com/keanupola/University_Coursework.git
   ```

2. Navigate to the Project Directory:
   ```bash
   cd University_Coursework/Highlights/Implementing_Machine_Learning_Algorithms
   ```

3. Install Required Libraries:
   ```bash
   pip install numpy pandas matplotlib
   ```

### Run Instructions

- Open the Jupyter Notebook:
  ```bash
  jupyter notebook CS3793_assignment3_tro893.ipynb
  ```

- Run the notebook cells to execute the code for both algorithms.

### Files in the Project

- CS3793_assignment3_tro893.ipynb - Jupyter Notebook containing the code and explanations.
- gd-train.dat - Training data for gradient descent.
- gd-test.dat - Test data for gradient descent.
- id3-train.dat - Training data for ID3 algorithm.
- id3-test.dat - Test data for ID3 algorithm.
