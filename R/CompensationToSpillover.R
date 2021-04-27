CompensationToSpillover <- function(CompensationMatrix){
  # V = CompensationToSpillover(CompensationMatrix)
  # 
  # INPUT
  #
  # Compensation    [1:d, 1:d] Numerical matrix with compensation matrix for
  #                 given variables.
  # 
  # OUTPUT
  # 
  # SpilloverMatrix [1:d, 1:d] Numerical matrix with spillover matrix for given
  #                            variables.
  # 
  # This function inverts/solves the compensation matrix in order to retrieve
  # the spillover matrix.
  # Author: QS 2021
  nrow = dim(CompensationMatrix)[1]
  inverseCompensationMatrix =solve(CompensationMatrix)
  SpilloverMatrix = matrix(inverseCompensationMatrix, nrow = nrow)
  colnames(SpilloverMatrix) = 1:dim(CompensationMatrix)[1]
  return(list("SpilloverMatrix"=SpilloverMatrix))
}
