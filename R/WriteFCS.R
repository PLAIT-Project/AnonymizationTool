WriteFCS <- function(FileName, Data, DeviceName="", SpilloverMatrix=NULL,
                     VarIdentifiers=NULL, VarNames=NULL, Cls=NULL,
                     OutDirectory=NULL){
  # V = WriteFCS(FileName, Data, VarIdentifiers,
  #                    VarNames, Cls, OutDirectory)
  # Writes data to FCS format
  # 
  # INPUT
  # FileName              name of the file.
  # Data[1:n, 1:d]        matrix  with n observations and d features 
  #                       carrying flowcytometry data values.
  # DeviceName            String name of the flowcytometer device.
  #                       options are DeviceName = "Navios", "CytoFlex",
  #                       "LSRII", "CytoFLEX LX", "NovoCyte Quanteon", "YETI"
  # 
  # OPTIONAL
  # SpilloverMatrix[1:d2, 1:d2]  Numerical matrix with spillover matrix.
  #                              The values in the SpilloverMatrix (Sij) are
  #                              floating point numbers that indicate the ratio
  #                              of the amount of signal in the “j” channel to
  #                              the amount of signal in the “i” channel for
  #                              particles carrying only the “i” parameter dye.
  #                              Only parameters associated with fluorescence
  #                              detectors are present in this matrix.
  # VarIdentifiers[1:d]          detector names used by the machine to adress
  #                              the variable) (e.g. "FS-H", "FS-A", "SS-H",
  #                              "SS-A","FL1-A", "FL1-H", "FL2-A", "FL2-H",...,
  #                              "TIME")
  # VarNames[1:d]                variable names (e.g. "FS_PEAK_LIN", "FS",
  #                              "SS_PEAK_LIN", "SS", "TCRgd-FITC", "CD45-KrO")
  # Cls[1:n]                     Integer vector with classes for each datapoint.
  # OutDirectory                 name of the file's directory
  # 
  # OUTPUT
  #
  # Author: QS 2021
  
  if(is.null(OutDirectory)){
    OutDirectory = getwd()
  }
  if(is.null(VarIdentifiers)){
    VarIdentifiers = colnames(Data)
    #VarIdentifiers = gsub("-H", " PEAK", gsub("-A", " INT", colnames(Data)))
  }
  if(is.null(VarNames)){
    VarNames = VarIdentifiers
  }
  if(length(VarIdentifiers) != length(VarNames)){
    message("Length of VarIdentifiers and VarNames does not match!")
    return()
  }
  # Modify the VarIdentifiers and VarNames if Cls is given
  if(!is.null(Cls)){
    if(length(Cls) != dim(Data)[1]){
      message("Length of classes does not match the number of observations in 
              Data")
      return()
    }
    VarIdentifiers = c(VarIdentifiers, "Cls")
    VarNames       = c(VarNames, "Cls")
    adf_parameters = get_AnnotatedDataFrame(Data, VarIdentifiers, VarNames, Cls)
    Data = as.matrix(cbind(Data, Cls))
  }else{
    adf_parameters = get_AnnotatedDataFrame(Data, VarIdentifiers, VarNames, Cls = NULL)
  }
  colnames(Data) = VarIdentifiers

  # Adapt description
  list_description = list()
  if(is.null(Cls)){
    if(!is.null(SpilloverMatrix)){
      list_description[["$SPILLOVER"]] = SpilloverMatrix
    }else{
      message("Note: A spillover matrix can be provided if there is no Cls.")
      #message("Please provide a compensation matrix if there is no Cls.")
      #return()
    }
  }
  list_description[["$FCSversion"]] = "3"
  list_description[["$CYT"]]        = DeviceName
  
  for(p in 1:length(colnames(Data))){
    list_description[[paste0("$P", p, "N")]]             = colnames(Data)[p]
    list_description[[paste0("$P", p, "S")]]             = colnames(Data)[p]
    list_description[[paste0("@P", p, "ADDRESS")]]       = p
    list_description[[paste0("$P", p, "B")]]             = 32
    list_description[[paste0("$P", p, "E")]]             = "0,0"
    list_description[[paste0("$P", p, "R")]]             = 1048576       # Set to high value to enable enough space
    #list_description[[paste0("flowCore_$P", p, "Rmax")]] = lmd$FCSDatasetTwo@description[[paste0("flowCore_$P", p, "Rmax")]]
    #list_description[[paste0("flowCore_$P", p, "Rmin")]] = lmd$FCSDatasetTwo@description[[paste0("flowCore_$P", p, "Rmin")]]
  }
  
  if(!is.null(SpilloverMatrix)){
    compensation = round(SpilloverMatrix,4)*100
    diag(compensation) = rep(0, length(diag(compensation)))
    vec_compensation = as.vector(t(compensation))
    counter = 1
    list_description = list()
    for(i in 1:10){
      for(j in 1:10){
        list_description[[paste("$DFC", i, "TO", j, sep="")]] = as.character(vec_compensation[counter])
        counter = counter + 1
      }
    }
  }
  
  #if(!is.null(Cls)){
  #  list_description[["$Cls"]] = Cls
  #}
  if (!requireNamespace('flowCore', quietly = TRUE)) {
    message(
      "Package flowCore is missing in function WriteFCSNavios
      No computations are performed.
      Please install the packages which are defined in 'Suggests'"
    )
    return()
  }
  # Create flowCore::flowFrame
  flowFrame = methods::new("flowFrame",
                           exprs       = Data,
                           parameters  = adf_parameters,
                           description = list_description
  )
  if(!is.null(OutDirectory)){                                 # Check directory name
    if(nchar(OutDirectory) > 0){
      if(substr(OutDirectory, nchar(OutDirectory), nchar(OutDirectory)) != '/')
        OutDirectory = paste0(OutDirectory, '/')
    }
    FileName = paste(OutDirectory, FileName, sep = "")
  }else{
    FileName = FileName
  }
  flowCore::write.FCS(x = flowFrame, filename = FileName)     # Write flowFrame
}

get_AnnotatedDataFrame = function(CompensatedData, VarIdentifiers, VarNames, Cls = NULL){
  # FCSData@parameters@data
  vec_rowNames = c()
  vec_range    = c()
  vec_minRange = c()
  vec_maxRange = c()
  for(i in 1:length(colnames(CompensatedData))){
    vec_rowNames = c(vec_rowNames, paste0("$P", i, "N"))
    vec_minRange = c(vec_minRange, 0)
    vec_range    = c(vec_range, 1048576)                                        # Set to high value to enable enough space
    vec_maxRange = c(vec_maxRange, vec_range[i]-1)
  }
  if(!is.null(Cls)){
    vec_rowNames   = c(vec_rowNames, paste0("$P", length(colnames(CompensatedData))+1, "N"))
    vec_minRange   = c(vec_minRange, 1)
    num_labels     = length(unique(Cls))
    vec_range      = c(vec_range, num_labels)
    vec_maxRange   = c(vec_maxRange, vec_range[length(colnames(CompensatedData))+1]-1)
  }
  list_data = list("name" = VarIdentifiers,
                   "desc" = VarNames,
                   "range" = vec_range,
                   "minRange" = vec_minRange,
                   "maxRange" = vec_maxRange)
  df_data = data.frame(list_data, row.names = vec_rowNames)
  
  # FCSData@parameters@varMetadata
  labelDescription = c("Name of Parameter",
                       "Description of Parameter",
                       "Range of Parameter",
                       "Minimum Parameter Value after Transforamtion",
                       "Maximum Parameter Value after Transformation")
  vec_rowNames_Desc = c("name", "desc", "range", "minRange", "maxRange")
  df_varMetadata = data.frame(labelDescription, row.names = vec_rowNames_Desc)
  
  if (!requireNamespace('Biobase', quietly = TRUE)) {
    message(
      "Package Biobase is missing in function get_AnnotatedDataFrame
      No computations are performed.
      Please install the packages which are defined in 'Suggests'"
    )
    return()
  }
  # AnnotatedDataFrame
  adf_data = Biobase::AnnotatedDataFrame(data        = df_data,
                                         varMetadata = df_varMetadata,
                                         dimLabels   = c("rowNames", "columnNames"))
  return(adf_data)
}
