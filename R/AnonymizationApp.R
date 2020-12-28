#' @name AnonymizationApp
#'
#' @title AnonymizationApp

#' @description Takes an .fcs or .lmd file as an input, anonymizes all the personal data in that file and save it as a new .fcs or .lmd file within a Shiny App

#' @param Btn_GetFile Input of the filepath of the file that is about to be made anonymous
#' @param newFileName the name of the new file which is a copy of the origin file
#' @param goButton Submit Button to submit the new filename
#' @param Anonymized action Button to anonymize the new file

#' @return An anonymized file which is a copy of the origin file but without the personal information and another filename

#' @export

#' @import "shiny"
#' @import "shinyjs"
#' @import "shinyFiles"
#' @import "shinyFeedback"


ui <- fluidPage(
  # disable actionButton after click on it
  tags$head(tags$script(HTML('
      Shiny.addCustomMessageHandler("jsCode",
        function(message) {
          console.log(message)
          eval(message.code);
        }
      );
    '))),

  shinyFeedback::useShinyFeedback(),
  titlePanel(
    div ("Anonymization Tool", style="text-align: center; background-color: white; font-size: 50px; width:100%; height: 100px; font-family: Georgia;
 "),
    div("PLAIT", style="text-aligh:center; font-size: 30px; margin-top:200px;font-family: Georgia;
")
  ),


  fluidRow(

    wellPanel(
      style = "width:70%; margin-left: 30px; position:center",
      div ("1.", style="text-align: left; font-size: 40px; font-family: Georgia;
 "),
      div("Choose the file you want to anonymize.", style="font-size: 14px"),
      tags$hr(),
      shinyFilesButton("Btn_GetFile", "Choose a file" ,
                       title = "Please select a file:", multiple = FALSE,
                       buttonType = "default", class = NULL),
      br(),
      br(),
      textOutput("fileName"),
      checkboxInput("checkbox", label = "I agree that this file will be irrevocably anonymized.", value = FALSE),


    )),
  fluidRow(
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


disableActionButton <- function(id,session) {
  session$sendCustomMessage(type="jsCode",
                            list(code= paste("$('#",id,"').prop('disabled',true)", sep="")))
}


server <- function(input, output, session) {

  observe({
    if(input$goButton == 1) disableActionButton("goButton",session)
  })

  volumes = getVolumes()
  observe({
    shinyFileChoose(input, "Btn_GetFile", roots = volumes, session = session)

    if(!is.null(input$Btn_GetFile)){
      # browser()
      file_selected<-parseFilePaths(volumes, input$Btn_GetFile)

      filepath <- as.character(file_selected$datapath)

      getDatapath <- reactive({
        return(filepath)
      })

      #nur Dateipfad ohne Dateiname
      getPath <- reactive({
        return(dirname(filepath))
      })

      getFileExtension <- reactive({
        substr(filepath, nchar(filepath)-4+1, nchar(filepath))
      })

      text <- eventReactive(input$Btn_GetFile, {
        paste0("You have selected the following file: ", getDatapath())
      })

      output$fileName <- renderText({
        text()
      })

      newFilename <- reactive({
        return(file.path(getPath(), input$newFileName))
      })

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
          .C("hexeditor", newFilename())

          paste0("The file was successfully anonymized. You can upload it on PLAIT. The file is: ", newFilename())
        }
      })



    }
  })

}


shinyApp(ui = ui, server = server)


