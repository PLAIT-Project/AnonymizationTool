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
