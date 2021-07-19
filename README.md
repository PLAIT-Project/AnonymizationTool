# PLAIT AnonymizationTool

PLAIT: Phenotyping Lymphoma with an Artificial Intelligence Toolbox <br>

The anonymization app deletes personal data from .fcs/.lmd files. In the anonymization process, the entered file is overwritten in the affected areas, which means field contents are deleted. This enables the further use of the anonymized file for physicians and doctors on services such as ours. 

Requirements: R > 3.5, various shiny-related packages (see below) and RTools <br>
Recommended: R 4.0.3, R-Studio 1.33 and RTools40

PLAIT-Website: [https://plait.uni-marburg.de](http://137.248.121.81:9798/plait/) ([eduroam VPN](https://www.uni-marburg.de/de/hrz/dienste/vpn) necessary) <br>
PLAIT-Webservice: [https://plait-ai.uni-marburg.de](http://137.248.121.81:9797) ([eduroam VPN](https://www.uni-marburg.de/de/hrz/dienste/vpn) necessary)

## Quick-Installation
Note: For detailed installation instructions go to [https://plait.uni-marburg.de/anonymisierungsapp](http://137.248.121.81:9798/plait/anonymisierungsapp/) <br>
Install the required packages for the execution (see [here](http://137.248.121.81:9798/plait/anonymisierungsapp/); link is accessible from eduroam only - use [VPN](https://www.uni-marburg.de/de/hrz/dienste/vpn)):
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
For permanent installation, download this repository as [ZIP-folder](https://github.com/PLAIT-Project/AnonymizationTool/archive/refs/heads/master.zip) (upper right, green button) and install it locally (make sure that the package is unpacked). 

```{r}
shiny::runApp('R')
```

More detailed instructions can be found in the [Manual](http://137.248.121.81:9798/plait/handbuch/). 

## Manual
The full manual for physicians, doctors and scientists who have .fcs/.lmds files for anonymization, is available [here](http://137.248.121.81:9798/plait/handbuch/); link is accessible from eduroam only - use [VPN](https://www.uni-marburg.de/de/hrz/dienste/vpn))

After download, installation and execution, a new window should pop-up: <br>

![New Window](https://raw.githubusercontent.com/Wandergarten/PLAIT-AnonApp/main/howto/1a.png)

Click on the Button "Choose File", this will prompt your file explorer. Choose the file you would like to anonymize by marking and selecting it. If you'd like to try it out, this package comes with three sample .LMD files in the folder [/Sample/](https://github.com/Wandergarten/PLAIT-AnonApp/tree/main/sample).

![Choose File](https://raw.githubusercontent.com/Wandergarten/PLAIT-AnonApp/main/howto/1b.png)

After you have selected your lymphoma dataset (.LMD/.FCS), confirm your wish to irreversibly anonymize this file. It may be recommended, creating a backup of you file in another location of your computer's directory. To avoid this, give your file another name with the same file type extension.

![New File Name](https://raw.githubusercontent.com/Wandergarten/PLAIT-AnonApp/main/howto/2.png)

Now, you are all set to let the Anonymization tool do its work: Click on the button "Anonymize"

![Anonymize](https://raw.githubusercontent.com/Wandergarten/PLAIT-AnonApp/main/howto/3.png)

Note that this is a student project!

For inquiries and feedback, contact: databionics@informatik.uni-marburg.de <br>
Project lead: [Prof. Ultsch](https://www.uni-marburg.de/fb12/arbeitsgruppen/datenbionik), [Dr. rer. nat. MC Thrun](https://mthrun.github.io/index), [Dr. med. Brendel](https://www.uni-marburg.de/de/fb20/bereiche/zim/haematoonkol/forschung/internetauftritt-der-ag-brendel) <br>
Authors and contributors: [Dr. F. Lerch](https://www.uni-marburg.de/fb12/arbeitsgruppen/datenbionik/mitarbeiter), [J. Schulz-Marner](https://github.com/JonasSchulz-Marner), AC. Rathert, [C. Kujath](https://github.com/Wandergarten), S. Nguyen 
