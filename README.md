# PLAIT AnonymizationTool

PLAIT: Phenotyping Lymphoma with an Artificial Intelligence Toolbox <br>

The anonymization app deletes personal data from .fcs/.lmd files. In the anonymization process, the entered file is overwritten in the affected areas, which means field contents are deleted. This enables the further use of the anonymized file for physicians and doctors on services such as ours. 

Requirements: R > 3.6 and various shiny-related packages (see below) <br>
Recommended: R 4.0.3 and R-Studio 1.33

PLAIT-Website: [htts://plait.uni-marburg.de](137.248.121.81:9798/plait/) <br>
PLAIT-Webservice: [https://plait-ai.uni-marburg.de](137.248.121.81:9797)

## Installation

Install the required packages for the execution (see [here](http://137.248.121.81:9798/plait/anonymisierungsapp/); link is only accessible from eduroam):
```{r}
requiredPackages <- c("shiny", "shinyjs", "shinyFiles", "shinyFeedback", "Rcpp") 
new.packages <- requiredPackages[!(requiredPackages %in% installed.packages()[,"Package"])]
if(length(new.packages)) install.packages(new.packages, quiet=TRUE)
invisible(lapply(requiredPackages, library, character.only = TRUE)) 
```
Run the AnonymizationTool in R with following Command:
```{r}
shiny::runGitHub("AnonymizationTool", "PLAIT-project", subdir = "R")
```

Or install the package by using Github:
```{r}
remotes::install_github("PLAIT-project/AnonymizationTool")
```

More detailed instructions can be found in the Manual. 

## Manual
The full manual for physicians, doctors and scientists who have .fcs/.lmds files for anonymization, is available (here)[http://137.248.121.81:9798/plait/anonymisierungsapp/]; link is only accessible from eduroam)

After this, a new window should pop-up: <br>

![New Window](https://raw.githubusercontent.com/Wandergarten/PLAIT-AnonApp/main/howto/1a.png)

Click on the Button "Choose File", this will prompt your file explorer. Choose the file you would like to anonymize by marking and selecting it. If you'd like to try it out, this package comes with three sample .LMD files in the folder [/Sample/](https://github.com/Wandergarten/PLAIT-AnonApp/tree/main/sample).

![Choose File](https://raw.githubusercontent.com/Wandergarten/PLAIT-AnonApp/main/howto/1b.png)

After you have selected your lymphoma dataset (.LMD/.FCS), confirm your wish to irreversibly anonymize this file. It may be recommended, creating a backup of you file in another location of your computer's directory. To avoid this, give your file another name with the same file type extension.

![New File Name](https://raw.githubusercontent.com/Wandergarten/PLAIT-AnonApp/main/howto/2.png)

Now, you are all set to let the Anonymization tool do its work: Click on the button "Anonymize"

![Anonymize](https://raw.githubusercontent.com/Wandergarten/PLAIT-AnonApp/main/howto/3.png)


Note that this is a student project!

For inquiries and feedback, contact: databionics@informatik.uni-marburg.de <br>
Project lead: Prof. Ultsch, Dr. rer. nat. MC Thrun, Dr. med. Brendel <br>
Authors and contributors: F. Lerch, J. Schulz-Marner, AC Rathert, C. Kujath 
