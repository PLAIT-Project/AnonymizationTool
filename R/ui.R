library(shiny)
library(shinyjs)
library(shinyFiles)
library(shinyFeedback)

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
