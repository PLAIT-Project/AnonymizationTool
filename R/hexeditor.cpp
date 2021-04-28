#include <Rcpp.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <cstdio>

using namespace Rcpp;

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;
// [[Rcpp::export]]

CharacterVector hexeditor(const char * filename) {
// This function overwrites the content of the following
// keywords of a .fcs or .lmd file with a string of 'XXXX':
// @SAMPLEID1, FILENAME, ORIGINALGUID, GUID, $FIL
// INPUT
// filepath to a .fcs or .lmd
// OUTPUT
// .fcs or .lmd file with 'XXXX' instead of the content
// of the above keywords

    // PROCEDURE //
    
// The function hexeditor() opens the file of the given filepath.
// Then it seeks for the keywords with a filepointer:
    // The filepointer checks, if there is a character of the separator.
    // Then it checks, if the next character is the first character
    // of the keyword. Character by character is checked, if the found keyword
    // is the one of the above. This is done by nested if-clauses for
    // each character.
    // If one of the above keywords are found, it is checked of how many
    // characters the content consists. Then a string of that length is
    // created with 'XXXX' and overwrote of the content.
// This is done for every keyword and for the different separators: '\' and '|' and ‘.‘.
    
    // VARIABLES //
    
// the tempX variables check whether a string of characters is equal to
// one of the above keywords. As ORIGINALGUID is the longest with a length of 12
// plus the separators at the beginning and ending, 14 character
// variables are necessary.
  char temp, temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9, temp10, temp11, temp12, temp13, temp14;
// the end_of_keyword variables search for the last separator of the content
// of the corresponding keyword
  char end_of_name, end_of_filename, end_of_originalguid, end_of_guid, end_of_fil;
// the count_keyword is the length of the content of the corresponding keyword.
  int count_name, count_filename, count_originalguid, count_guid, count_fil;
// the set_keyword is a boolean variable to make sure, that each keyword is
// changed only once
  bool setname = false, set_filename = false, set_originalguid = false, set_guid = false, set_fil = false;
// the anon_keyword is a string of the 'XXXX' to overwrite the content of the
// corresponding keyword
  char anon_name[100] = "";
  char anon_filename[100] = "";
  char anon_originalguid[100] = "";
  char anon_guid[100] = "";
  char anon_fil[100] = "";
// the string of which the above strings of 'XXXX' are generated
  char x[] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
  
   
    // FUNCTION //
    
// open the file and set filepointer to 0 / beginning of file
  FILE * fp;
  fp = fopen(filename,"r+");
  fseek(fp,0,SEEK_END);
  int size = ftell(fp);
  fseek(fp, 0, SEEK_SET);


// if-clause to check if the filepointer is at the end of the file
  if (fp!=NULL)
  {

      // loop through the whole file. i is always placed where our
      // filepointer fp is.
    for (int i=1; i<size; i++) {

      // Nested if-queries, whether the letters of the predetermined keywords
      // are in the correct order in the file

      //keywords:
      //@SAMPLEID1, FILENAME, ORIGINALGUID, GUID, $FIL
      

      // searching for first keyword
      //@SAMPLEID1

      fscanf(fp, "%c", &temp);
      if (temp == '\\'){      // '\\' means '\'
        i = i+1;
        fscanf(fp, "%c", &temp1);
        if (temp1 == '@'){
          i = i+1;
          fscanf(fp, "%c", &temp2);
          if (temp2 == 'S'){
            i = i+1;
            fscanf(fp, "%c", &temp3);
            if (temp3 == 'A'){
              i = i+1;
              fscanf(fp, "%c", &temp4);
              if (temp4 == 'M'){
                i = i+1;
                fscanf(fp, "%c", &temp5);
                if (temp5 == 'P'){
                  i = i+1;
                  fscanf(fp, "%c", &temp6);
                  if (temp6 == 'L'){
                    i = i+1;
                    fscanf(fp, "%c", &temp7);
                    if (temp7 == 'E'){
                      i = i+1;
                      fscanf(fp, "%c", &temp8);
                      if (temp8 == 'I'){
                        i = i+1;
                        fscanf(fp, "%c", &temp9);
                        if (temp9 == 'D'){
                          i = i+1;
                          fscanf(fp, "%c", &temp10);
                          if (temp10 == '1'){
                            i = i+1;
                            fscanf(fp, "%c", &temp11);
                            if (temp11 == '\\'){
                              i = i+1;
                              fscanf(fp, "%c", &end_of_name);
                              count_name = 0;

                              // Count the length of the content
                              // of the corresponding keyword
                              while (end_of_name != '\\'){
                                fscanf(fp, "%c", &end_of_name);
                                count_name = count_name + 1;
                              }
                              //printf("the word to be anonymous is this long:  %d\n", count_name);

                              // set anonymous name
                              // to anon_name (an empty string) is appended the string x, of length count_name
                              if (setname == false){
                                strncat(anon_name, x, count_name);
                                setname = true; // setname is set to TRUE, so that the keyword is changed only once
                              }

                              // Overwrite file at the appropriate position with anon_name
                              fseek(fp, i-1, SEEK_SET);
                              fputs(anon_name,fp);
                              i = i + count_name - 1; // set i to the next digit after the anonymized content
                              // synchronize fp and i
                              fseek(fp, i, SEEK_SET);
                            }}}}}}}}}}}

        //searching for next keyword:
        //FILENAME

        else if (temp1 == 'F'){
          i = i+1;
          fscanf(fp, "%c", &temp2);
          if (temp2 == 'I'){
            i = i+1;
            fscanf(fp, "%c", &temp3);
            if (temp3 == 'L'){
              i = i+1;
              fscanf(fp, "%c", &temp4);
              if (temp4 == 'E'){
                i = i+1;
                fscanf(fp, "%c", &temp5);
                if (temp5 == 'N'){
                  i = i+1;
                  fscanf(fp, "%c", &temp6);
                  if (temp6 == 'A'){
                    i = i+1;
                    fscanf(fp, "%c", &temp7);
                    if (temp7 == 'M'){
                      i = i+1;
                      fscanf(fp, "%c", &temp8);
                      if (temp8 == 'E'){
                        i = i+1;
                        fscanf(fp, "%c", &temp9);
                        if (temp9 == '\\'){
                          i = i+1;
                          fscanf(fp, "%c", &end_of_filename);
                          count_filename = 0;

                            // Count the length of the content
                            // of the corresponding keyword
                          while (end_of_filename != '\\'){
                            fscanf(fp, "%c", &end_of_filename);
                            count_filename = count_filename + 1;
                          }
                            //printf("the word to be anonymous is this long:  %d\n", count_filename);

                            // set anonymous name
                            // to anon_name (an empty string) is appended the string x, of length count_name
                          if (set_filename == false){
                            strncat(anon_filename, x, count_filename);
                            set_filename = true; // setname is set to TRUE, so that the keyword is changed only once
                          }

                            // Overwrite file at the appropriate position with anon_name
                          fseek(fp, i-1, SEEK_SET);
                          fputs(anon_filename,fp);
                          i = i + count_filename - 1; // set i to the next digit after the anonymized content
                            // synchronize fp and i
                          fseek(fp, i, SEEK_SET);
                        }}}}}}}}}

        //next keyword
        //ORIGINALGUID

        else if (temp1 == 'O'){
          i = i+1;
          fscanf(fp, "%c", &temp2);
          if (temp2 == 'R'){
            i = i+1;
            fscanf(fp, "%c", &temp3);
            if (temp3 == 'I'){
              i = i+1;
              fscanf(fp, "%c", &temp4);
              if (temp4 == 'G'){
                i = i+1;
                fscanf(fp, "%c", &temp5);
                if (temp5 == 'I'){
                  i = i+1;
                  fscanf(fp, "%c", &temp6);
                  if (temp6 == 'N'){
                    i = i+1;
                    fscanf(fp, "%c", &temp7);
                    if (temp7 == 'A'){
                      i = i+1;
                      fscanf(fp, "%c", &temp8);
                      if (temp8 == 'L'){
                        i = i+1;
                        fscanf(fp, "%c", &temp9);
                        if (temp9 == 'G'){
                          i = i+1;
                          fscanf(fp, "%c", &temp10);
                          if (temp10 == 'U'){
                            i = i+1;
                            fscanf(fp, "%c", &temp11);
                            if (temp11 == 'I'){
                              i = i+1;
                              fscanf(fp, "%c", &temp12);
                              if (temp12 == 'D'){
                                i = i+1;
                                fscanf(fp, "%c", &temp13);
                                if (temp13 == '\\'){
                                  i = i+1;
                                  fscanf(fp, "%c", &end_of_originalguid);
                                  count_originalguid = 0;

                                    // Count the length of the content
                                    // of the corresponding keyword
                                  while (end_of_originalguid != '\\'){
                                    fscanf(fp, "%c", &end_of_originalguid);
                                    count_originalguid = count_originalguid + 1;
                                  }
                                  //printf("so lang ist das zu anonym. Originalguid Wort:  %d\n", count_originalguid);

                                    // set anonymous name
                                    // to anon_originalguid (an empty string) is appended the string x, of length count_originalguid
                                  if (set_originalguid == false){
                                    strncat(anon_originalguid, x, count_originalguid);
                                    set_originalguid = true; // setname is set to TRUE, so that the keyword is changed only once
                                  }

                                    // Overwrite file at the appropriate position with anon_name
                                  fseek(fp, i-1, SEEK_SET);
                                  fputs(anon_originalguid,fp);
                                  i = i + count_originalguid - 1;// set i to the next digit after the anonymized content
                                    // synchronize fp and i
                                  fseek(fp, i, SEEK_SET);
                                }}}}}}}}}}}}}


        //GUID

        else if (temp1 == 'G'){
          i = i+1;
          fscanf(fp, "%c", &temp2);
          if (temp2 == 'U'){
            i = i+1;
            fscanf(fp, "%c", &temp3);
            if (temp3 == 'I'){
              i = i+1;
              fscanf(fp, "%c", &temp4);
              if (temp4 == 'D'){
                i = i+1;
                fscanf(fp, "%c", &temp5);
                if (temp5 == '\\'){
                  i = i+1;
                  fscanf(fp, "%c", &end_of_guid);
                  count_guid = 0;

                    // Count the length of the content
                    // of the corresponding keyword
                  while (end_of_guid != '\\'){
                    fscanf(fp, "%c", &end_of_guid);
                    count_guid = count_guid + 1;
                  }
                  //printf("so lang ist das zu anonym. Wort:  %d\n", count_guid);

                    // set anonymous name
                    // to anon_guid (an empty string) is appended the string x, of length count_guid
                  if (set_guid == false){
                    strncat(anon_guid, x, count_guid); //count_name
                    set_guid = true; // setname is set to TRUE, so that the keyword is changed only once
                  }

                    // Overwrite file at the appropriate position with anon_name
                  fseek(fp, i-1, SEEK_SET);
                  fputs(anon_guid,fp);
                  i = i + count_guid - 1;// set i to the next digit after the anonymized content
                    // synchronize fp and i
                  fseek(fp, i, SEEK_SET);
                }}}}}


        //$FIL

        else if (temp1 == '$'){
          i = i+1;
          fscanf(fp, "%c", &temp2);
          if (temp2 == 'F'){
            i = i+1;
            fscanf(fp, "%c", &temp3);
            if (temp3 == 'I'){
              i = i+1;
              fscanf(fp, "%c", &temp4);
              if (temp4 == 'L'){
                i = i+1;
                fscanf(fp, "%c", &temp5);
                if (temp5 == '\\'){
                  i = i+1;
                  fscanf(fp, "%c", &end_of_fil);
                  count_fil = 0;

                    // Count the length of the content
                    // of the corresponding keyword
                  while (end_of_fil != '\\'){
                    fscanf(fp, "%c", &end_of_fil);
                    count_fil = count_fil + 1;
                  }
                  //printf("FIL: so lang ist das zu anonym. FIL Wort:  %d\n", count_fil);

                    // set anonymous name
                    // to anon_fil (an empty string) is appended the string x, of length count_fil
                  if (set_fil == false){
                    strncat(anon_fil, x, count_fil); //count_name
                    set_fil = true; // setname is set to TRUE, so that the keyword is changed only once
                  }

                    // Overwrite file at the appropriate position with anon_name
                  fseek(fp, i-1, SEEK_SET);
                  fputs(anon_fil,fp);
                  i = i + count_fil - 1;// set i to the next digit after the anonymized content
                    // synchronize fp and i
                  fseek(fp, i, SEEK_SET);
                }}}}}
      }


      // next separator for FCS 3.0, which is '|'

      // |SAMPLEID1


      else if (temp == '|'){
        i = i+1;
        fscanf(fp, "%c", &temp1);
        if (temp1 == '@'){
          i = i+1;
          fscanf(fp, "%c", &temp2);
          if (temp2 == 'S'){
            i = i+1;
            fscanf(fp, "%c", &temp3);
            if (temp3 == 'A'){
              i = i+1;
              fscanf(fp, "%c", &temp4);
              if (temp4 == 'M'){
                i = i+1;
                fscanf(fp, "%c", &temp5);
                if (temp5 == 'P'){
                  i = i+1;
                  fscanf(fp, "%c", &temp6);
                  if (temp6 == 'L'){
                    i = i+1;
                    fscanf(fp, "%c", &temp7);
                    if (temp7 == 'E'){
                      i = i+1;
                      fscanf(fp, "%c", &temp8);
                      if (temp8 == 'I'){
                        i = i+1;
                        fscanf(fp, "%c", &temp9);
                        if (temp9 == 'D'){
                          i = i+1;
                          fscanf(fp, "%c", &temp10);
                          if (temp10 == '1'){
                            i = i+1;
                            fscanf(fp, "%c", &temp11);
                            if (temp11 == '|'){
                              i = i+1;
                              fscanf(fp, "%c", &end_of_name);
                              count_name = 0;

                                // Count the length of the content
                                // of the corresponding keyword
                              while (end_of_name != '|'){
                                fscanf(fp, "%c", &end_of_name);
                                count_name = count_name + 1;
                              }
                              //printf("so lang ist das zu anonym. Wort:  %d\n", count_name);

                                // set anonymous name
                                // to anon_name (an empty string) is appended the string x, of length count_name
                              if (setname == false){
                                strncat(anon_name, x, count_name); //count_name
                                setname = true; // setname is set to TRUE, so that the keyword is changed only once
                              }

                                // Overwrite file at the appropriate position with anon_name
                              fseek(fp, i-1, SEEK_SET);
                              fputs(anon_name,fp);
                              i = i + count_name - 1;// set i to the next digit after the anonymized content
                                // synchronize fp and i
                              fseek(fp, i, SEEK_SET);
                            }}}}}}}}}}}

        // |FILENAME

        else if (temp1 == 'F'){
          i = i+1;
          fscanf(fp, "%c", &temp2);
          if (temp2 == 'I'){
            i = i+1;
            fscanf(fp, "%c", &temp3);
            if (temp3 == 'L'){
              i = i+1;
              fscanf(fp, "%c", &temp4);
              if (temp4 == 'E'){
                i = i+1;
                fscanf(fp, "%c", &temp5);
                if (temp5 == 'N'){
                  i = i+1;
                  fscanf(fp, "%c", &temp6);
                  if (temp6 == 'A'){
                    i = i+1;
                    fscanf(fp, "%c", &temp7);
                    if (temp7 == 'M'){
                      i = i+1;
                      fscanf(fp, "%c", &temp8);
                      if (temp8 == 'E'){
                        i = i+1;
                        fscanf(fp, "%c", &temp9);
                        if (temp9 == '|'){
                          i = i+1;
                          fscanf(fp, "%c", &end_of_filename);
                          count_filename = 0;

                            // Count the length of the content
                            // of the corresponding keyword
                          while (end_of_filename != '|'){
                            fscanf(fp, "%c", &end_of_filename);
                            count_filename = count_filename + 1;
                          }
                          //printf("so lang ist das zu anonym. Filename-Wort:  %d\n", count_filename);

                            // set anonymous name
                            // to anon_filename (an empty string) is appended the string x, of length count_filename
                          if (set_filename == false){
                            strncat(anon_filename, x, count_filename); //count_name
                            set_filename = true; // setname is set to TRUE, so that the keyword is changed only once
                          }

                            // Overwrite file at the appropriate position with anon_name
                          fseek(fp, i-1, SEEK_SET);
                          fputs(anon_filename,fp);
                          i = i + count_filename - 1;// set i to the next digit after the anonymized content
                            // synchronize fp and i
                          fseek(fp, i, SEEK_SET);
                        }}}}}}}}}


        // |ORIGINALGUID

        else if (temp1 == 'O'){
          i = i+1;
          fscanf(fp, "%c", &temp2);
          if (temp2 == 'R'){
            i = i+1;
            fscanf(fp, "%c", &temp3);
            if (temp3 == 'I'){
              i = i+1;
              fscanf(fp, "%c", &temp4);
              if (temp4 == 'G'){
                i = i+1;
                fscanf(fp, "%c", &temp5);
                if (temp5 == 'I'){
                  i = i+1;
                  fscanf(fp, "%c", &temp6);
                  if (temp6 == 'N'){
                    i = i+1;
                    fscanf(fp, "%c", &temp7);
                    if (temp7 == 'A'){
                      i = i+1;
                      fscanf(fp, "%c", &temp8);
                      if (temp8 == 'L'){
                        i = i+1;
                        fscanf(fp, "%c", &temp9);
                        if (temp9 == 'G'){
                          i = i+1;
                          fscanf(fp, "%c", &temp10);
                          if (temp10 == 'U'){
                            i = i+1;
                            fscanf(fp, "%c", &temp11);
                            if (temp11 == 'I'){
                              i = i+1;
                              fscanf(fp, "%c", &temp12);
                              if (temp12 == 'D'){
                                i = i+1;
                                fscanf(fp, "%c", &temp13);
                                if (temp13 == '|'){
                                  i = i+1;
                                  fscanf(fp, "%c", &end_of_originalguid);
                                  count_originalguid = 0;

                                    // Count the length of the content
                                    // of the corresponding keyword
                                  while (end_of_originalguid != '|'){
                                    fscanf(fp, "%c", &end_of_originalguid);
                                    count_originalguid = count_originalguid + 1;
                                  }
                                  //printf("so lang ist das zu anonym. Originalguid Wort:  %d\n", count_originalguid);

                                    // set anonymous name
                                    // to anon_originalguid (an empty string) is appended the string x, of length count_originalguid
                                  if (set_originalguid == false){
                                    strncat(anon_originalguid, x, count_originalguid); //count_name
                                    set_originalguid = true; // setname is set to TRUE, so that the keyword is changed only once
                                  }

                                    // Overwrite file at the appropriate position with anon_name
                                  fseek(fp, i-1, SEEK_SET);
                                  fputs(anon_originalguid,fp);
                                  i = i + count_originalguid - 1;// set i to the next digit after the anonymized content
                                    // synchronize fp and i
                                  fseek(fp, i, SEEK_SET);
                                }}}}}}}}}}}}}


        // |GUID

        else if (temp1 == 'G'){
          i = i+1;
          fscanf(fp, "%c", &temp2);
          if (temp2 == 'U'){
            i = i+1;
            fscanf(fp, "%c", &temp3);
            if (temp3 == 'I'){
              i = i+1;
              fscanf(fp, "%c", &temp4);
              if (temp4 == 'D'){
                i = i+1;
                fscanf(fp, "%c", &temp5);
                if (temp5 == '|'){
                  i = i+1;
                  fscanf(fp, "%c", &end_of_guid);
                  count_guid = 0;

                    // Count the length of the content
                    // of the corresponding keyword
                  while (end_of_guid != '|'){
                    fscanf(fp, "%c", &end_of_guid);
                    count_guid = count_guid + 1;
                  }
                  //printf("so lang ist das zu anonym. Wort:  %d\n", count_guid);

                    // set anonymous name
                    // to anon_guid (an empty string) is appended the string x, of length count_guid
                  if (set_guid == false){
                    strncat(anon_guid, x, count_guid); //count_name
                    set_guid = true; // setname is set to TRUE, so that the keyword is changed only once
                  }

                    // Overwrite file at the appropriate position with anon_name
                  fseek(fp, i-1, SEEK_SET);
                  fputs(anon_guid,fp);
                  i = i + count_guid - 1;// set i to the next digit after the anonymized content
                    // synchronize fp and i
                  fseek(fp, i, SEEK_SET);
                }}}}}


        // |$FIL

        else if (temp1 == '$'){
          i = i+1;
          fscanf(fp, "%c", &temp2);
          if (temp2 == 'F'){
            i = i+1;
            fscanf(fp, "%c", &temp3);
            if (temp3 == 'I'){
              i = i+1;
              fscanf(fp, "%c", &temp4);
              if (temp4 == 'L'){
                i = i+1;
                fscanf(fp, "%c", &temp5);
                if (temp5 == '|'){
                  i = i+1;
                  fscanf(fp, "%c", &end_of_fil);
                  count_fil = 0;

                    // Count the length of the content
                    // of the corresponding keyword
                  while (end_of_fil != '|'){
                    fscanf(fp, "%c", &end_of_fil);
                    count_fil = count_fil + 1;
                  }
                  //printf("so lang ist das zu anonym. FIL Wort:  %d\n", count_fil);

                    // set anonymous name
                    // to anon_fil (an empty string) is appended the string x, of length count_fil
                  if (set_fil == false){
                    strncat(anon_fil, x, count_fil); //count_name
                    set_fil = true; // setname is set to TRUE, so that the keyword is changed only once
                  }

                    // Overwrite file at the appropriate position with anon_name
                  fseek(fp, i-1, SEEK_SET);
                  fputs(anon_fil,fp);
                  i = i + count_fil - 1;// set i to the next digit after the anonymized content
                    // synchronize fp and i
                  fseek(fp, i, SEEK_SET);
                }}}}}
      }



      // next separator for .fcs: ‘.‘


      // .SAMPLEID1


      else if (temp == '.'){
        i = i+1;
        fscanf(fp, "%c", &temp1);
        if (temp1 == '@'){
          i = i+1;
          fscanf(fp, "%c", &temp2);
          if (temp2 == 'S'){
            i = i+1;
            fscanf(fp, "%c", &temp3);
            if (temp3 == 'A'){
              i = i+1;
              fscanf(fp, "%c", &temp4);
              if (temp4 == 'M'){
                i = i+1;
                fscanf(fp, "%c", &temp5);
                if (temp5 == 'P'){
                  i = i+1;
                  fscanf(fp, "%c", &temp6);
                  if (temp6 == 'L'){
                    i = i+1;
                    fscanf(fp, "%c", &temp7);
                    if (temp7 == 'E'){
                      i = i+1;
                      fscanf(fp, "%c", &temp8);
                      if (temp8 == 'I'){
                        i = i+1;
                        fscanf(fp, "%c", &temp9);
                        if (temp9 == 'D'){
                          i = i+1;
                          fscanf(fp, "%c", &temp10);
                          if (temp10 == '1'){
                            i = i+1;
                            fscanf(fp, "%c", &temp11);
                            if (temp11 == '.'){
                              i = i+1;
                              fscanf(fp, "%c", &end_of_name);
                              count_name = 0;

                                // Count the length of the content
                                // of the corresponding keyword
                              while (end_of_name != '.'){
                                fscanf(fp, "%c", &end_of_name);
                                count_name = count_name + 1;
                              }
                              //printf("so lang ist das zu anonym. Wort:  %d\n", count_name);

                                // set anonymous name
                                // to anon_name (an empty string) is appended the string x, of length count_name
                              if (setname == false){
                                strncat(anon_name, x, count_name); //count_name
                                setname = true; // setname is set to TRUE, so that the keyword is changed only once
                              }

                                // Overwrite file at the appropriate position with anon_name
                              fseek(fp, i-1, SEEK_SET);
                              fputs(anon_name,fp);
                              i = i + count_name - 1;// set i to the next digit after the anonymized content
                                // synchronize fp and i
                              fseek(fp, i, SEEK_SET);
                            }}}}}}}}}}}

        // .FILENAME

        else if (temp1 == 'F'){
          i = i+1;
          fscanf(fp, "%c", &temp2);
          if (temp2 == 'I'){
            i = i+1;
            fscanf(fp, "%c", &temp3);
            if (temp3 == 'L'){
              i = i+1;
              fscanf(fp, "%c", &temp4);
              if (temp4 == 'E'){
                i = i+1;
                fscanf(fp, "%c", &temp5);
                if (temp5 == 'N'){
                  i = i+1;
                  fscanf(fp, "%c", &temp6);
                  if (temp6 == 'A'){
                    i = i+1;
                    fscanf(fp, "%c", &temp7);
                    if (temp7 == 'M'){
                      i = i+1;
                      fscanf(fp, "%c", &temp8);
                      if (temp8 == 'E'){
                        i = i+1;
                        fscanf(fp, "%c", &temp9);
                        if (temp9 == '.'){
                          i = i+1;
                          fscanf(fp, "%c", &end_of_filename);
                          count_filename = 0;

                            // Count the length of the content
                            // of the corresponding keyword
                          while (end_of_filename != '.'){
                            fscanf(fp, "%c", &end_of_filename);
                            count_filename = count_filename + 1;
                          }
                          //printf("so lang ist das zu anonym. Filename-Wort:  %d\n", count_filename);

                            // set anonymous name
                            // to anon_filename (an empty string) is appended the string x, of length count_filename
                          if (set_filename == false){
                            strncat(anon_filename, x, count_filename); //count_name
                            set_filename = true; // setname is set to TRUE, so that the keyword is changed only once
                          }

                            // Overwrite file at the appropriate position with anon_name
                          fseek(fp, i-1, SEEK_SET);
                          fputs(anon_filename,fp);
                          i = i + count_filename - 1;// set i to the next digit after the anonymized content
                            // synchronize fp and i
                          fseek(fp, i, SEEK_SET);
                        }}}}}}}}}


        // .ORIGINALGUID

        else if (temp1 == 'O'){
          i = i+1;
          fscanf(fp, "%c", &temp2);
          if (temp2 == 'R'){
            i = i+1;
            fscanf(fp, "%c", &temp3);
            if (temp3 == 'I'){
              i = i+1;
              fscanf(fp, "%c", &temp4);
              if (temp4 == 'G'){
                i = i+1;
                fscanf(fp, "%c", &temp5);
                if (temp5 == 'I'){
                  i = i+1;
                  fscanf(fp, "%c", &temp6);
                  if (temp6 == 'N'){
                    i = i+1;
                    fscanf(fp, "%c", &temp7);
                    if (temp7 == 'A'){
                      i = i+1;
                      fscanf(fp, "%c", &temp8);
                      if (temp8 == 'L'){
                        i = i+1;
                        fscanf(fp, "%c", &temp9);
                        if (temp9 == 'G'){
                          i = i+1;
                          fscanf(fp, "%c", &temp10);
                          if (temp10 == 'U'){
                            i = i+1;
                            fscanf(fp, "%c", &temp11);
                            if (temp11 == 'I'){
                              i = i+1;
                              fscanf(fp, "%c", &temp12);
                              if (temp12 == 'D'){
                                i = i+1;
                                fscanf(fp, "%c", &temp13);
                                if (temp13 == '.'){
                                  i = i+1;
                                  fscanf(fp, "%c", &end_of_originalguid);
                                  count_originalguid = 0;

                                    // Count the length of the content
                                    // of the corresponding keyword
                                  while (end_of_originalguid != '.'){
                                    fscanf(fp, "%c", &end_of_originalguid);
                                    count_originalguid = count_originalguid + 1;
                                  }
                                  //printf("so lang ist das zu anonym. Originalguid Wort:  %d\n", count_originalguid);

                                    // set anonymous name
                                    // to anon_originalguid (an empty string) is appended the string x, of length count_originalguid
                                  if (set_originalguid == false){
                                    strncat(anon_originalguid, x, count_originalguid); //count_name
                                    set_originalguid = true; // setname is set to TRUE, so that the keyword is changed only once
                                  }

                                    // Overwrite file at the appropriate position with anon_name
                                  fseek(fp, i-1, SEEK_SET);
                                  fputs(anon_originalguid,fp);
                                  i = i + count_originalguid - 1;// set i to the next digit after the anonymized content
                                    // synchronize fp and i
                                  fseek(fp, i, SEEK_SET);
                                }}}}}}}}}}}}}


        // .GUID

        else if (temp1 == 'G'){
          i = i+1;
          fscanf(fp, "%c", &temp2);
          if (temp2 == 'U'){
            i = i+1;
            fscanf(fp, "%c", &temp3);
            if (temp3 == 'I'){
              i = i+1;
              fscanf(fp, "%c", &temp4);
              if (temp4 == 'D'){
                i = i+1;
                fscanf(fp, "%c", &temp5);
                if (temp5 == '.'){
                  i = i+1;
                  fscanf(fp, "%c", &end_of_guid);
                  count_guid = 0;

                    // Count the length of the content
                    // of the corresponding keyword
                  while (end_of_guid != '.'){
                    fscanf(fp, "%c", &end_of_guid);
                    count_guid = count_guid + 1;
                  }
                  //printf("so lang ist das zu anonym. Wort:  %d\n", count_guid);

                    // set anonymous name
                    // to anon_guid (an empty string) is appended the string x, of length count_guid
                  if (set_guid == false){
                    strncat(anon_guid, x, count_guid); //count_name
                    set_guid = true; // setname is set to TRUE, so that the keyword is changed only once
                  }

                    // Overwrite file at the appropriate position with anon_name
                  fseek(fp, i-1, SEEK_SET);
                  fputs(anon_guid,fp);
                  i = i + count_guid - 1;// set i to the next digit after the anonymized content
                    // synchronize fp and i
                  fseek(fp, i, SEEK_SET);
                }}}}}


        // .$FIL

        else if (temp1 == '$'){
          i = i+1;
          fscanf(fp, "%c", &temp2);
          if (temp2 == 'F'){
            i = i+1;
            fscanf(fp, "%c", &temp3);
            if (temp3 == 'I'){
              i = i+1;
              fscanf(fp, "%c", &temp4);
              if (temp4 == 'L'){
                i = i+1;
                fscanf(fp, "%c", &temp5);
                if (temp5 == '.'){
                  i = i+1;
                  fscanf(fp, "%c", &end_of_fil);
                  count_fil = 0;

                    // Count the length of the content
                    // of the corresponding keyword
                  while (end_of_fil != '.'){
                    fscanf(fp, "%c", &end_of_fil);
                    count_fil = count_fil + 1;
                  }
                  //printf("so lang ist das zu anonym. FIL Wort:  %d\n", count_fil);

                    // set anonymous name
                    // to anon_fil (an empty string) is appended the string x, of length count_fil
                  if (set_fil == false){
                    strncat(anon_fil, x, count_fil); //count_name
                    set_fil = true; // setname is set to TRUE, so that the keyword is changed only once
                  }

                    // Overwrite file at the appropriate position with anon_name
                  fseek(fp, i-1, SEEK_SET);
                  fputs(anon_fil,fp);
                  i = i + count_fil - 1;// set i to the next digit after the anonymized content
                    // synchronize fp and i
                  fseek(fp, i, SEEK_SET);
                }}}}}
      }
    }

//     char buffer [3500];
//     fseek(fp, 0, SEEK_SET);
//     while ( ! feof (fp) )
//     {
//       if ( fgets (buffer , 3500 , fp) == NULL ) break;
//       fputs (buffer , stdout);
//     }
      
  }
  return 0;
  fclose(fp);
}
