#' @name AnonymizationApp
#'
#' @title AnonymizationApp

#' @description Takes an .fcs or .lmd file as an input, anonymizes all the personal data in that file and save it as a new .fcs or .lmd file within a Shiny App

#' @return An anonymized file which is a copy of the origin file but without the personal information and another filename

#' @useDynLib AnonymizationToolCpp, .registration = TRUE
#' @importFrom Rcpp sourceCpp

#' @export shinyApp

#' @import "shiny"
#' @import "shinyjs"
#' @import "shinyFiles"
#' @import "shinyFeedback"

library(shiny)
library(shinyjs)
library(shinyFiles)
library(shinyFeedback)
library(Rcpp)

#sourceCpp('hexeditor.cpp')




### Concept of the Shiny-App ###
# As an Input, a .fcs or .lmd-file is selected. This file is copied then under a
# new filename which is the users choice. This copied file is then anonymized,
# meaning that the new file does not consist any personal information.

### Comment to the Shiny-App ###
# The UI consists of three panels, two of them are conditional.
# The first panel consists of a file input and a checkbox.
# The second panel consists of a text input and a submit button.
# The third panel consists of a action button.
# INPUT
# Btn_GetFile         shinyFilesButton: The selected input file. (.fcs or .lmd)
# checkbox            checkboxInput:    The checkbox of the first panel.
# newFileName         textInput:        The name of the new file.
# goButton            actionButton:     Submit Button in the second panel
# Anonymized          actionButton:     Clicking on this Button makes the anonymization happen.
#
# OUTPUT
# fileName            textOutput:       The local filepath of the selected input file.
# newFilename         textOutput:       The name of the new file.
# success             textOutput:       Success info that the anonymization is done.



ui = fluidPage(
  # disable actionButton after click on it
  tags$head(tags$script(HTML('
      Shiny.addCustomMessageHandler("jsCode",
        function(message) {
          console.log(message)
          eval(message.code);
        }
      );
    '))),

  # HTML graphics
  shinyFeedback::useShinyFeedback(),
  titlePanel(
    div ("Anonymization Tool", style="text-align: center; background-color: white; font-size: 50px; width:100%; height: 100px; font-family: Georgia;
 "),
    div("PLAIT", style="text-aligh:center; font-size: 30px; margin-top:200px;font-family: Georgia;
")
  ),

  ## Start of the page ##
  fluidRow(

    wellPanel(
      style = "width:70%; margin-left: 30px; position:center",
      div ("1.", style="text-align: left; font-size: 40px; font-family: Georgia;
 "),
      div("Choose the file you want to anonymize.", style="font-size: 14px"),
      tags$hr(),

      # input of the filepath of the input file
      shinyFilesButton("Btn_GetFile", "Choose a file" ,
                       title = "Please select a file:", multiple = FALSE,
                       buttonType = "default", class = NULL),
      br(),
      br(),
      textOutput("fileName"),
      checkboxInput("checkbox", label = "I agree that this file will be irrevocably anonymized.", value = FALSE),


    )),
  fluidRow(
    # under the condition of a tick at the checkbox
    conditionalPanel(condition = "input.checkbox == 1",
                     wellPanel(
                       style = "width:70%; margin-left: 30px; position:center",

                       div ("2.", style="text-align: left; font-size: 40px; font-family: Georgia;"),
                       div("Enter the new filename you want the anonymized file to be saved as. Make sure to keep the file extension (.LMD / .fcs).", style="font-size: 14px"),
                       tags$hr(),
                       textInput("newFileName", "New Filename", width = "300px"),
                       actionButton("goButton", "Submit", class = "btn-primary"),
                       br(),
                       br(),
                       textOutput("newFilename")
                     ))),
  fluidRow(
    # under the condition of a click at "Submit"
    conditionalPanel(condition = "input.goButton == 1",
                     wellPanel(
                       style = "width:70%; margin-left: 30px; position:center",

                       div ("3.", style="text-align: left; font-size: 40px; font-family: Georgia;"),
                       div("Click on Anonymize. Since the Anonymization is successful, you will be informed below. This process can take up to minutes.", style="font-size: 14px"),
                       tags$hr(),
                       actionButton("Anonymized", "Anonymize",class = "btn-primary"),
                       br(),
                       br(),
                       textOutput("success")

                     ))),

)

# function to disable the action button in order to change the file input
disableActionButton <- function(id,session) {
  session$sendCustomMessage(type="jsCode",
                            list(code= paste("$('#",id,"').prop('disabled',true)", sep="")))
}


server = function(input, output, session) {

  observe({
    if(input$goButton == 1) disableActionButton("goButton",session)
  })

  volumes = getVolumes()
  observe({
    shinyFileChoose(input, "Btn_GetFile", roots = volumes, session = session)

    if(!is.null(input$Btn_GetFile)){
      # save the selected file and the filepath
      file_selected<-parseFilePaths(volumes, input$Btn_GetFile)

      filepath <- as.character(file_selected$datapath)

      getDatapath <- reactive({
        return(filepath)
      })

      #OUTPUT: only filepath without the file
      getPath <- reactive({
        return(dirname(filepath))
      })

      # OUTPUT: file extension
      getFileExtension <- reactive({
        substr(filepath, nchar(filepath)-4+1, nchar(filepath))
      })

      # generate the text right after selecting the file
      # OUTPUT: text of the datapath
      text <- eventReactive(input$Btn_GetFile, {
        paste0("You have selected the following file: ", getDatapath())
      })

      output$fileName <- renderText({
        text()
      })

      # generate the new filename with the path of the original file
      # OUTPUT: text of the datapath of the new file
      newFilename <- reactive({
        return(file.path(getPath(), input$newFileName))
      })

      # the extension of the filename of the original file
      # OUTPUT: text of the file extension
      newFilenameEnding <- reactive({
        extension = substr(input$newFileName, nchar(input$newFileName)-4+1, nchar(input$newFileName))
        testing = (extension == getFileExtension())
        shinyFeedback::feedbackWarning("newFileName", !testing, "Choose the same file extension as in the original file. Then continue with 3.")
        req(testing)
        return (extension)
      })


      output$newFilename <- renderText({
        if (input$goButton == 1){
          shinyjs::hide("goButton")
          if (newFilenameEnding() == '.fcs' || newFilenameEnding() == '.FCS' || newFilenameEnding() == '.LMD') {
            file.copy(getDatapath(), newFilename())
            paste0("Your new file will be: ", newFilename())
          }
        }
      })



      output$success <- renderText({
        if (input$Anonymized == 1){
          hexeditor(newFilename())
          # .C("hexeditor", newFilename())

          paste0("The file was successfully anonymized. You can upload it on PLAIT. The file is: ", newFilename())
        }
      })



    }
  })

}

# Create Shiny app

shinyApp(ui, server)







