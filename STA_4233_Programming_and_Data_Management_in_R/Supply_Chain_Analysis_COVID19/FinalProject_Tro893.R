#### STA4233
#### Addressing Supply Chain Challenges: Data Preparation and Exploration for 
#### ODM Site and Shipping Mode Analysis during the COVID-19 Pandemic
#### Keanu Anderson-Pola
#
#
#
# Load packages
library(tidyr)
library(dplyr)
library(ggplot2)
library(lubridate)
library(readxl)


### Read in Raw-Data and Calendar worksheets of RawData.xlsx 
##
#-------------------------------------------------------------------------------
rawData <- read_excel("RawData.xlsx", sheet = 1)
calendar <- read_excel("RawData.xlsx", sheet = 2)

#-------------------------------------------------------------------------------
#### Add Quarter and Year columns to the Raw-Data sheet
###
##
# Convert columns to date type for future calculation
#-------------------------------------------------------------------------------
rawData$`PO Download Date` <- as.Date(rawData$`PO Download Date`, format = "%m/%d/%Y")
rawData$`Ship Date` <- as.Date(rawData$`Ship Date`, format = "%m/%d/%Y")
rawData$`Receipt Date` <- as.Date(rawData$`Receipt Date`, format = "%m/%d/%Y")
calendar$`Start_Date` <- as.Date(calendar$`Start_Date`, format = "%m/%d/%Y")
calendar$`End_date` <- as.Date(calendar$`End_date`, format = "%m/%d/%Y")

#-------------------------------------------------------------------------------
# Create function add_quarter_year() to add quarter and year columns
#-------------------------------------------------------------------------------
# add_quarter_year() finds Quarter and Year that is appropriate for the Receipt 
# Date, creates said columns, and then populates them.
add_quarter_year <- function(rawData, calendar) {
  
  # Function to find the quarter and year for receipt date
  find_quarter_year <- function(receiptDate, calendar) {
    if (is.na(receiptDate)) {
      return(c(NA, NA))
    }
    for (i in 1:nrow(calendar)) {
      if (receiptDate >= calendar$`Start_Date`[i] & receiptDate <= calendar$`End_date`[i]) {
        return(c(calendar$Quarter[i], calendar$Year[i]))
      }
    }
    return(c(NA, NA))
  }
  
  # Initialize Quarter and Year columns in rawData
  rawData$Quarter <- NA
  rawData$Year <- NA
  
  # Loop through rawData and populate Quarter and Year columns
  for (i in 1:nrow(rawData)) {
    receiptDate <- rawData$`Receipt Date`[i]
    quarterYear <- find_quarter_year(receiptDate, calendar) # store matches
    rawData$Quarter[i] <- quarterYear[1]
    rawData$Year[i] <- quarterYear[2]
  }
  
  return(rawData)
}

#-------------------------------------------------------------------------------
# Apply add_quarter_year() to rawData
#-------------------------------------------------------------------------------
rawData <- add_quarter_year(rawData, calendar)

#-------------------------------------------------------------------------------
### Calculate and add Lead Time columns to rawData
##
#-------------------------------------------------------------------------------
rawData <- rawData %>%
  mutate(
    `Manufacturing Lead Time` = as.numeric(`Ship Date` - `PO Download Date`),
    `In-transit Lead Time` = as.numeric(`Receipt Date` - `Ship Date`)
  )

#-------------------------------------------------------------------------------
#### Explore ways to clean/impute data
###
##
# -------------------- Visual analysis on the rawData table --------------------
# There are no N/A values for LOB, Origin, and Ship Mode
# Negative lead time values must be removed
# In manufacturing lead time there is a big jump from 51 to 105, the lower 
# non-negative lead times had reasonable in-transit lead times
# 0 <= manufacturing lead time <= 51
# For In-Transit lead times I found that all days past 55 as well as 0 days had 
# questionable manufacturing lead times, 0 < In-Transit Lead Time <= 55
# ------------------------------------------------------------------------------
#
### Visualize Lead times for outliers
##
# Convert rawData to long format for combined box plot
#-------------------------------------------------------------------------------
rawData_long <- rawData %>% 
  select(`Manufacturing Lead Time`, `In-transit Lead Time`) %>% 
  pivot_longer(cols = everything(), names_to = "Lead Time Type", values_to = "Lead Time")

#-------------------------------------------------------------------------------
# Combined box plot for Manufacturing and In-transit Lead Times
#-------------------------------------------------------------------------------
box_leadTimes <- ggplot(rawData_long, aes(x = `Lead Time Type`, y = `Lead Time`)) +
  geom_boxplot() +
  labs(title = "In-transit & Manufacturing Lead Times",
       x = "Lead Time Type",
       y = "Lead Time (days)")
box_leadTimes
# *There are extreme outliers in both directions*

#-------------------------------------------------------------------------------
### Clean Manufacturing Lead Time and In-Transit Lead times based on my criteria
## Gather descriptive statistics
#-------------------------------------------------------------------------------
rawData <- rawData %>%
  mutate(`Manufacturing Lead Time` = ifelse(`Manufacturing Lead Time` >= 0 & `Manufacturing Lead Time` <= 51, `Manufacturing Lead Time`, NA),
         `In-transit Lead Time` = ifelse(`In-transit Lead Time` > 0 & `In-transit Lead Time` <= 55, `In-transit Lead Time`, NA))

#-------------------------------------------------------------------------------
# Check LOB, Origin and Ship mode tables for inconsistencies
#-------------------------------------------------------------------------------
table(rawData$LOB)
table(rawData$Origin)
table(rawData$`Ship Mode`)
# Product C and Fastboat are relatively low (262 and 530, respectively), however
# there are no glaring inconsistencies.

#-------------------------------------------------------------------------------
# Calculate rounded mean lead times grouped by LOB, Origin, and Ship Mode
#-------------------------------------------------------------------------------
avg_leadTimes <- rawData %>%
  group_by(LOB, Origin, `Ship Mode`) %>%
  summarise(`Avg MLT` = round(mean(`Manufacturing Lead Time`, na.rm = TRUE)),
            `Avg ITLT` = round(mean(`In-transit Lead Time`, na.rm = TRUE)))

#-------------------------------------------------------------------------------
# Save original dataset as copy for future analysis
#-------------------------------------------------------------------------------
rawData_noImpute <- rawData

#-------------------------------------------------------------------------------
# Impute mean lead times for NA's in rawData, add cols to count imputations
#-------------------------------------------------------------------------------
rawData <- rawData %>%
  left_join(avg_leadTimes, by = c("LOB", "Origin", "Ship Mode")) %>%
  mutate(`MLT Imputed` = is.na(`Manufacturing Lead Time`),
         `ITLT imputed` = is.na(`In-transit Lead Time`),
         `Manufacturing Lead Time` = ifelse(is.na(`Manufacturing Lead Time`), `Avg MLT`, `Manufacturing Lead Time`),
         `In-transit Lead Time` = ifelse(is.na(`In-transit Lead Time`), `Avg ITLT`, `In-transit Lead Time`),
         `Any Lead Time Imputed` = `MLT Imputed` | `ITLT imputed`) %>%
  select(-`Avg MLT`, -`Avg ITLT`)

#-------------------------------------------------------------------------------
# Count the number of rows imputed for each new column
#-------------------------------------------------------------------------------
imputed_total <- sum(rawData$`Any Lead Time Imputed`, na.rm = TRUE) # 520
imputed_mlt <- sum(rawData$`MLT Imputed`, na.rm = TRUE) # 477
imputed_itlt <- sum(rawData$`ITLT imputed`, na.rm = TRUE) # 291

#-------------------------------------------------------------------------------
# Save partially imputed dataset as copy for future analysis and also remove
# rows where Ship and Receipt Date are empty, this may dilute the sample
#-------------------------------------------------------------------------------
sum(is.na(rawData$`Ship Date`)) # 145
sum(is.na(rawData$`Receipt Date`)) # 145
# Losing 145 rows, they all correspond on the table
rawData_someImpute <- rawData %>%
  filter(!is.na(rawData$`Ship Date`)) # only need one since they are equal

#-------------------------------------------------------------------------------
### Impute missing Ship Date values and overwrite original column
##
#-------------------------------------------------------------------------------
rawData <- rawData %>%
  mutate(`Ship Date` = ifelse(is.na(`Ship Date`),
                              `PO Download Date` + days(`Manufacturing Lead Time`),
                              `Ship Date`)) %>%
  mutate(`Ship Date` = as.Date(`Ship Date`, origin = "1970-01-01"))

#-------------------------------------------------------------------------------
### Impute missing Receipt Date values and overwrite original column
##
#-------------------------------------------------------------------------------
rawData <- rawData %>%
  mutate(`Receipt Date` = ifelse(is.na(`Receipt Date`),
                                 `Ship Date` + days(`In-transit Lead Time`),
                                 `Receipt Date`)) %>%
  mutate(`Receipt Date` = as.Date(`Receipt Date`, origin = "1970-01-01"))

#-------------------------------------------------------------------------------
### Update Quarter and Year columns 
##
#-------------------------------------------------------------------------------
add_quarter_year(rawData, calendar)

#------------------------------------------------------------------------------
# Store clean data set
#-------------------------------------------------------------------------------
rawData_clean <- rawData %>%
  select(-c(11:13))

#-------------------------------------------------------------------------------
### Exploratory Analysis
##
#-------------------------------------------------------------------------------
# I will be using three versions of rawData to see if there is any significant 
# loss of information. A fully cleaned/imputed version 'rawData' that has 645 
# imputations, the partially imputed version that has 520 imputations and 145 
# removed rows 'rawData_someImpute', and finally the unimputed but cleaned 
# version 'rawData_noImpute'.
#-------------------------------------------------------------------------------
#
# Remove unecessary columns and NA's from rawData's for analysis, combine year 
# and quarter columns
#-------------------------------------------------------------------------------
rawData_noImpute <- rawData_noImpute %>%
  filter(!is.na(`Ship Date`)) %>%
  mutate(Year_Quarter = paste0(Year, "-", Quarter)) %>%
  select(-c(4:8))

rawData_someImpute <- rawData_someImpute %>%
  mutate(Year_Quarter = paste0(Year, "-", Quarter)) %>%
  select(-c(4:8), -c(11:13))

rawData <- rawData %>%
  mutate(Year_Quarter = paste0(Year, "-", Quarter)) %>%
  select(-c(4:8), -c(11:13))

#-------------------------------------------------------------------------------
# See if there is a relation between NA's and year/quarter
#-------------------------------------------------------------------------------
missing_leadTimes <- rawData_noImpute %>%
  mutate(missing_MLT = is.na(`Manufacturing Lead Time`),
         missing_ITLT = is.na(`In-transit Lead Time`))

# Count the occurrences of missing values for each Year_Quarter
missing_by_year_quarter <- missing_leadTimes %>%
  group_by(Year_Quarter) %>%
  summarise(n_missing_MLT = sum(missing_MLT),
            n_missing_ITLT = sum(missing_ITLT),
            n_total_missing = n_missing_MLT + n_missing_ITLT)
# Table
missing_by_year_quarter

# Plot for total
bar_missing_by_year_quarter <- ggplot(missing_by_year_quarter, aes(x = Year_Quarter, y = n_total_missing)) +
  geom_bar(stat = "identity") +
  labs(title = "Missing Lead Times by Year and Quarter",
       x = "Year and Quarter",
       y = "Total Missing Count") +
  theme(axis.text.x = element_text(angle = 45, hjust = 1))
bar_missing_by_year_quarter
# Most NA's occured in 2020 - Q2

#-------------------------------------------------------------------------------
### Explore relation b/w lead times and LOB, Origin, and Ship Mode
##
# Relation between In-Transit Lead Time and Ship Mode
#-------------------------------------------------------------------------------
# summary statistic version test 
shipMode_summary1 <-  rawData %>% 
  group_by(`Ship Mode`) %>%
  summarize(`In-Transit Lead Time Avg.` = mean(`In-transit Lead Time`, na.rm = TRUE))
shipMode_summary2 <-  rawData_someImpute %>% 
  group_by(`Ship Mode`) %>%
  summarize(`In-Transit Lead Time Avg.` = mean(`In-transit Lead Time`, na.rm = TRUE))
shipMode_summary3 <-  rawData_noImpute %>% 
  group_by(`Ship Mode`) %>%
  summarize(`In-Transit Lead Time Avg.` = mean(`In-transit Lead Time`, na.rm = TRUE))
# No significant difference

bar_avgITLT_by_shipMode <- ggplot(shipMode_summary1, aes(x = `Ship Mode`, y = `In-Transit Lead Time Avg.`, fill = `Ship Mode`)) +
  geom_bar(stat = "identity") +
  labs(title = "In-Transit Lead Time by Ship Mode",
       x = "Ship Mode",
       y = "Avg. In-Transit Lead Time (days)")

bar_avgITLT_by_shipMode

# In-Transit Lead times are much higher than average when Ship mode is Ocean 
# and Fastboat

#-------------------------------------------------------------------------------
# Relation between In-Transit Lead Time and Ship Mode/LOB
#-------------------------------------------------------------------------------
# summary statistic version test 
shipMode_LOB_summary1 <- rawData %>%
  group_by(`Ship Mode`, LOB) %>%
  summarize(`In-Transit Lead Time Avg.` = mean(`In-transit Lead Time`, na.rm = TRUE))
shipMode_LOB_summary2 <- rawData_someImpute %>%
  group_by(`Ship Mode`, LOB) %>%
  summarize(`In-Transit Lead Time Avg.` = mean(`In-transit Lead Time`, na.rm = TRUE))
shipMode_LOB_summary3 <- rawData %>%
  group_by(`Ship Mode`, LOB) %>%
  summarize(`In-Transit Lead Time Avg.` = mean(`In-transit Lead Time`, na.rm = TRUE))
# No significant difference

# Create a bar chart
bar_avgITLT_by_shipMode_LOB <- ggplot(shipMode_LOB_summary1, aes(x = `Ship Mode`, y = `In-Transit Lead Time Avg.`, fill = LOB)) +
  geom_bar(stat = "identity", position = "dodge") +
  labs(title = "In-Transit Lead Time by Ship Mode and LOB",
       x = "Ship Mode",
       y = "Avg. In-Transit Lead Time (days)")

bar_avgITLT_by_shipMode_LOB
# Ocean has very high avg. In-Transit Lead Times

#-------------------------------------------------------------------------------
# Relation between Manufacturing Lead Time and LOB
#-------------------------------------------------------------------------------
# summary statistic version test 
lob_summary1 <- rawData %>%
  group_by(LOB) %>%
  summarise(`Manufacturing Lead Time Avg.` = mean(`Manufacturing Lead Time`, na.rm = TRUE))
lob_summary2 <- rawData_someImpute %>%
  group_by(LOB) %>%
  summarise(`Manufacturing Lead Time Avg.` = mean(`Manufacturing Lead Time`, na.rm = TRUE))
lob_summary3 <- rawData_noImpute %>%
  group_by(LOB) %>%
  summarise(`Manufacturing Lead Time Avg.` = mean(`Manufacturing Lead Time`, na.rm = TRUE))
# No significant differences

bar_avgMLT_by_lob <- ggplot(lob_summary1, aes(x = LOB, y = `Manufacturing Lead Time Avg.`, fill = LOB)) +
  geom_bar(stat = "identity") +
  labs(title = "Avg. Manufacturing Lead Time by LOB",
       x = "LOB",
       y = "Manufacturing Lead Time (days)")

bar_avgMLT_by_lob
# Manufacturing Lead Time is significantly higher for product C

#-------------------------------------------------------------------------------
# Relation between Manufacturing Lead Time and Origin
#-------------------------------------------------------------------------------
# summary statistic version test 
origin_summary1 <- rawData %>%
  group_by(Origin) %>%
  summarise(`Manufacturing Lead Time Avg.` = mean(`Manufacturing Lead Time`, na.rm = TRUE))
origin_summary2 <- rawData_someImpute %>%
  group_by(Origin) %>%
  summarise(`Manufacturing Lead Time Avg.` = mean(`Manufacturing Lead Time`, na.rm = TRUE))
origin_summary3 <- rawData_noImpute %>%
  group_by(Origin) %>%
  summarise(`Manufacturing Lead Time Avg.` = mean(`Manufacturing Lead Time`, na.rm = TRUE))
# no significant differences

bar_avgMLT_by_origin <- ggplot(origin_summary1, aes(x = Origin, y = `Manufacturing Lead Time Avg.`, fill = Origin)) +
  geom_bar(stat = "identity") +
  labs(title = "Avg. Manufacturing Lead Time by Origin",
       x = "Origin",
       y = "Manufacturing Lead Time (days)")

bar_avgMLT_by_origin
# Manufacturing Lead Time is significantly higher for Site B

#-------------------------------------------------------------------------------
# Relation between Manufacturing Lead Time and both LOB & Origin
#-------------------------------------------------------------------------------
# summary statistic version test 
lob_origin_summary1 <- rawData %>%
  group_by(LOB, Origin) %>%
  summarise(`Manufacturing Lead Time Avg.` = mean(`Manufacturing Lead Time`, na.rm = TRUE))
lob_origin_summary2 <- rawData_someImpute %>%
  group_by(LOB, Origin) %>%
  summarise(`Manufacturing Lead Time Avg.` = mean(`Manufacturing Lead Time`, na.rm = TRUE))
lob_origin_summary3 <- rawData_noImpute %>%
  group_by(LOB, Origin) %>%
  summarise(`Manufacturing Lead Time Avg.` = mean(`Manufacturing Lead Time`, na.rm = TRUE))
# No significant difference

bar_avgMLT_by_lob_origin <- ggplot(lob_origin_summary1, aes(x = LOB, y = `Manufacturing Lead Time Avg.`, fill = Origin)) +
  geom_bar(stat = "identity", position = "dodge") +
  labs(title = "Avg. Manufacturing Lead Time by LOB and Origin",
       x = "LOB",
       y = "Manufacturing Lead Time (days)") +
  theme(axis.text.x = element_text(angle = 45, hjust = 1))

bar_avgMLT_by_lob_origin
# Product B at site B and Product C at site A average much higher Manufacturing
# Lead times than other combinations, B is the only product handled at all
# sites

#-------------------------------------------------------------------------------
# ***After calculating various summary statistics I have noticed that there is 
# no significant difference between the three versions so there would be no 
# significant loss of information by evaluating the fully imputed version.***
#-------------------------------------------------------------------------------
#### Calculate and report correlations between all categorical variables and
### In-Transit Lead Time
##
# Define the group combinations for future calculation
#-------------------------------------------------------------------------------
group_combinations <- list(
  c("LOB"),
  c("Origin"),
  c("Ship Mode"),
  c("LOB", "Origin"),
  c("LOB", "Ship Mode"),
  c("Origin", "Ship Mode"),
  c("LOB", "Origin", "Ship Mode")
)

#-------------------------------------------------------------------------------
# Generate box plots for each group combination by In-Transit Lead Time
#-------------------------------------------------------------------------------
plots_list <- list() # Create an empty list to store the generated plots

for (i in seq_along(group_combinations)) {
  # Get the current combination of categorical variables
  current_combination <- group_combinations[[i]]
  
  # Define the plot title based on the current combination
  plot_title <- paste("In-Transit Lead Time by", paste(current_combination, collapse = ", "))
  
  # Generate the box plot for the current combination
  plot_data <- rawData[, c(current_combination, "In-transit Lead Time")]
  # use `interaction()` to create a single factor variable 
  # representing the unique combinations of group combination. 
  # The `!!!rlang::syms(current_combination)` code 
  # is used to unquote the symbols in the 'current_combination' list so that 
  # they can be treated as separate arguments within the `interaction()` 
  # function.
  plot_aes <- aes(x = interaction(!!!rlang::syms(current_combination)), y = `In-transit Lead Time`, fill = interaction(!!!rlang::syms(current_combination)))
  current_plot <- ggplot(plot_data, plot_aes) +
    geom_boxplot() +
    labs(title = plot_title,
         x = paste(current_combination, collapse = ", "),
         y = "In-Transit Lead Time (days)") +
    scale_fill_discrete(name = paste(current_combination, collapse = ", "))
  
  # Add the current plot to the plots_list
  plots_list[[i]] <- current_plot
}
# Store plots
box_ITLT_by_lob <-  plots_list[[1]]
box_ITLT_by_origin <-  plots_list[[2]]
box_ITLT_by_shipMode <-  plots_list[[3]]
box_ITLT_by_lob_origin <- plots_list[[4]]
box_ITLT_by_lob_shipMode <-  plots_list[[5]]
box_ITLT_by_origin_shipMode <-  plots_list[[6]]
box_ITLT_by_all <- plots_list[[7]]
#-------------------------------------------------------------------------------
# Fix x axis labels for box_ITLT_by_lob_shipMode & box_ITLT_by_all (too long)
#-------------------------------------------------------------------------------
# Modify box_ITLT_by_lob_shipMode
# Function to generate labels for x-axis and legend
generate_labels <- function(current_combination, n) {
  original_labels <- sort(unique(interaction(rawData[, current_combination])))
  letters_subset <- letters[1:n]
  new_labels <- setNames(paste0(original_labels, " - ", letters_subset), original_labels)
  return(new_labels)
}

# Modify box_ITLT_by_lob_origin
box_ITLT_by_lob_origin <- box_ITLT_by_lob_origin +
  scale_x_discrete(labels = letters[1:9]) +
  scale_fill_discrete(name = paste(group_combinations[[3]], collapse = ", "), labels = generate_labels(group_combinations[[3]], 8)) +
  labs(x = "")

# Modify box_ITLT_by_origin_shipMode
box_ITLT_by_origin_shipMode <- box_ITLT_by_origin_shipMode +
  scale_x_discrete(labels = letters[1:9]) +
  scale_fill_discrete(name = paste(group_combinations[[6]], collapse = ", "), labels = generate_labels(group_combinations[[6]], 8)) +
  labs(x = "")


# Modify box_ITLT_by_lob_shipMode
box_ITLT_by_lob_shipMode <- box_ITLT_by_lob_shipMode +
  scale_x_discrete(labels = letters[1:10]) +
  scale_fill_discrete(name = paste(group_combinations[[5]], collapse = ", "), labels = generate_labels(group_combinations[[5]], 9)) +
  labs(x = "")

# Modify box_ITLT_by_all
box_ITLT_by_all <- box_ITLT_by_all +
  scale_x_discrete(labels = letters[1:11]) +
  scale_fill_discrete(name = paste(group_combinations[[7]], collapse = ", "), labels = generate_labels(group_combinations[[7]], 11)) +
  labs(x = "")


#-------------------------------------------------------------------------------
# Display all boxplot combinations of groups by In-Transit Lead Time
#-------------------------------------------------------------------------------
box_ITLT_by_lob
# Product A has the most outliers, Product C has the highest avg.
box_ITLT_by_origin
# Sites B, C, and D have high variability, site A's IQR is the larget, site B 
# has the highest median
box_ITLT_by_shipMode
# All modes have very high variability
box_ITLT_by_lob_origin
# Product B site A has highest median, also high variability
box_ITLT_by_lob_shipMode
# Highest variability of all plots, highest median is Product C, OCEAN
box_ITLT_by_origin_shipMode
# Site A ocean has highest median, high amount of outliers
box_ITLT_by_all
# some combinations have high variability

# *** Because there were many outliers, start testing for significance *** 

#-------------------------------------------------------------------------------
# Function to calculate outlier summary for given grouping columns
#-------------------------------------------------------------------------------
calculate_outlier_summary <- function(data, grouping_columns) {
  IQR_summary <- data %>%
    group_by(across(all_of(grouping_columns))) %>%
    summarise(Q1 = quantile(`In-transit Lead Time`, 0.25, na.rm = TRUE),
              Q3 = quantile(`In-transit Lead Time`, 0.75, na.rm = TRUE)) %>%
    mutate(IQR = Q3 - Q1,
           lowerBound = Q1 - 1.5 * IQR,
           upperBound = Q3 + 1.5 * IQR)
  
  rawData_bounded <- data %>%
    left_join(IQR_summary, by = grouping_columns) %>%
    mutate(isOutlier = (`In-transit Lead Time` < lowerBound) | (`In-transit Lead Time` > upperBound))
  
  outlier_summary <- rawData_bounded %>%
    group_by(across(all_of(grouping_columns))) %>%
    summarise(Total = n(),
              outliers = sum(isOutlier),
              OutlierPercentage = (outliers / Total) * 100)
  
  return(outlier_summary)
}

#-------------------------------------------------------------------------------
# Apply to group combinations
#-------------------------------------------------------------------------------
outlier_summaries <- lapply(group_combinations, function(grouping_columns) {
  calculate_outlier_summary(rawData, grouping_columns)
})

#-------------------------------------------------------------------------------
# Calculate total outliers
#-------------------------------------------------------------------------------
# Calculate total outliers for each summary
total_outliers <- lapply(outlier_summaries, function(outlier_summary) {
  sum(outlier_summary$outliers)
})

# Extract total outliers for each group combination
total_outliers_LOB <- total_outliers[[1]]
total_outliers_Origin <- total_outliers[[2]]
total_outliers_ShipMode <- total_outliers[[3]]
total_outliers_LOB_Origin <- total_outliers[[4]]
total_outliers_LOB_ShipMode <- total_outliers[[5]]
total_outliers_Origin_ShipMode <- total_outliers[[6]]
total_outliers_all <- total_outliers[[7]]

#-------------------------------------------------------------------------------
# Outlier summaries in order of group_combinations +total outliers
#-------------------------------
outlier_summaries[1] # "LOB"
# Product A has the most outliers at 55 but only 1.87%, low variability
total_outliers_LOB # 77

#-------------------------------
outlier_summaries[2] # "Origin"
# Site D has the most outliers at 125 but percentages are close b/w each other,
# moderate variability
total_outliers_Origin # 277

#-------------------------------
outlier_summaries[3] # "Ship Mode"
# Air has the most outliers at 303 with 7.94%, ship mode has more outliers than
# other categories, high variability
total_outliers_ShipMode # 611

#-------------------------------
outlier_summaries[4] # "LOB", "Origin"
# Product B Site D has the most outliers at 125 with 5%, moderate variability
total_outliers_LOB_Origin # 355

#-------------------------------
outlier_summaries[5] # "LOB", "Ship Mode"
# Product B OCEAN has 315 outliers with 17.4%, very high variability
total_outliers_LOB_ShipMode # 713

#-------------------------------
outlier_summaries[6] # "Origin", "Ship Mode"
# Moderate variability accross, SITE B AIR too small of a sample, 
total_outliers_Origin_ShipMode # 433

#-------------------------------
outlier_summaries[7] # "LOB", "Origin", "Ship Mode"
# combinations to note: 
# Product A Site A FASTBOAT - 15.7%, 305 observations
# Product B Site B AIR - 38.9%, 18 observations
# Product C Site A AIR - 14.3%, 21 observations
total_outliers_all # 454

# Unsurprisingly, Ship mode had the single most variability when comparing 
# categories by themselves. However, it is worth noting that the combination
# of LOB and Ship mode had the highest variability than any other combination.
# It would be worth investigating this further.

