# Supply Chain Analysis COVID-19

## Project Description

This project is an analysis of the impact of the COVID-19 pandemic on supply chains, using data analysis and visualization techniques in R. The analysis includes:

- Data import and cleaning from an Excel file.
- Statistical analysis of supply chain metrics.
- Visualization of trends and patterns.
- Compilation of findings into an HTML report.

## Features

- **Data Processing**:
  - Reads raw data from `RawData.xlsx`.
  - Cleans and preprocesses data for analysis.

- **Statistical Analysis**:
  - Computes key metrics and statistical summaries.
  - Identifies significant changes in supply chain performance.

- **Data Visualization**:
  - Generates plots and charts using `ggplot2`.
  - Visualizes trends over time and comparisons.

- **Reporting**:
  - Uses R Markdown to create an HTML report.
  - Integrates code, analysis, and visualizations into a cohesive document.

## Technologies Used

- **Programming Language**: R
- **Libraries**:
  - tidyverse (includes ggplot2, dplyr, etc.)
  - readxl (for reading Excel files)
- **Tools**:
  - RStudio
  - R Markdown

## Installation and Usage

### Prerequisites

- R and RStudio installed on your system
- Required R packages installed

### Setup Instructions

1. Clone the Repository:
   ```bash
   git clone https://github.com/keanupola/University_Coursework.git
   ```

2. Navigate to the Project Directory:
   ```bash
   cd University_Coursework/Highlights/Supply_Chain_Analysis_COVID19
   ```

3. Install Required Packages:
   - Open R or RStudio and run:
     ```R
     install.packages(c("tidyverse", "readxl"))
     ```

### Run Instructions

1. Open the R Markdown File:
   - In RStudio, open `FinalProject_Tro893.Rmd`.

2. Ensure Data File is in Place:
   - Verify that `RawData.xlsx` is in the `data/` directory.

3. Render the Report:
   - Click the "Knit" button in RStudio to generate the HTML report.
   - The output file `FinalProject_Tro893.html` will be created.

### Files in the Project

- `FinalProject_Tro893.Rmd` - The R Markdown file containing code and analysis.
- `FinalProject_Tro893.html` - The generated HTML report.
- `FinalProject_Tro893.R` - The R script extracted from the R Markdown file.
- `data/RawData.xlsx` - The raw data file used for analysis.
