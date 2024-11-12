# Implementing Machine Learning Algorithms

## Project Description

This project involves implementing two fundamental machine learning algorithms from scratch:

- **Gradient Descent for Linear Regression**
- **ID3 Algorithm for Decision Trees**

The purpose is to understand the inner workings of these algorithms by coding them without relying on high-level machine learning libraries.

## Running on Google Colab
You can also run this notebook on Google Colab: [Open in Google Colab](https://colab.research.google.com/drive/12lyb5BQMbr0ORm7m48F3oLEm-BcTKcCz?usp=sharing)

## Features

### Gradient Descent:
- Implements linear regression using gradient descent optimization.
- Reads training and testing data from provided .dat files.
- Plots the cost function over iterations.

### ID3 Decision Tree:
- Constructs a decision tree based on training data.
- Uses information gain to select the best features.
- Evaluates the decision tree on test data.

## Technologies Used

- **Programming Language**: Python 3
- **Libraries**:
  - `numpy`
  - `pandas`
  - `matplotlib` (for plotting)
  - Other standard Python libraries

## Setup Instructions

### Clone the Repository:
```bash
git clone https://github.com/keanupola/University_Coursework.git
```

## Navigate to the Project Directory:
```bash
cd University_Coursework/Highlights/Implementing_Machine_Learning_Algorithms
```

## Install Required Libraries:
```bash
pip install numpy pandas matplotlib
```

## Running the Programs
Open the Jupyter Notebook:
```bash
jupyter notebook CS3793_assignment3_tro893.ipynb
```

Run the notebook cells to execute the code for both algorithms.

## Program Usage
- The notebook is divided into sections for each algorithm.
- Ensure the data files (`gd-train.dat`, `gd-test.dat`, `id3-train.dat`, `id3-test.dat`) are in the same directory.
- Follow the instructions in the notebook to run the algorithms and observe the results.

## Files in the Project
- **CS3793_assignment3_tro893.ipynb** - Jupyter Notebook containing the code and explanations.
- **gd-train.dat** - Training data for gradient descent.
- **gd-test.dat** - Test data for gradient descent.
- **id3-train.dat** - Training data for ID3 algorithm.
- **id3-test.dat** - Test data for ID3 algorithm.