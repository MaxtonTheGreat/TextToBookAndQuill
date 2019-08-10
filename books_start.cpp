#include<iostream>
#include <fstream>
//#include <stdio.h>
//#include <stdlib.h>
//#include <ctype.h>

using namespace std;
#define NEWMAXPAGESIZE 307
#define OLDMAXPAGESIZE 255
#define MAXPAGES 50
#define MAXLINES 14
#define MAXLINELENGTH 22
#define CALC 12750


/* bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}*/


/* class Book {
    // bool updated
    Book () {

    }
private:
    int pagelen;
    //char text_in[MAXPAGES * OLDMAXPAGESIZE];

};*/

void select_version() {

}


bool select_mode() {
    printf("Enter mode:\n1. Copy-paste\n2. Use .txt file\n");
}

int main () {
    char line = 0;
    char * pageStart;
    char * lineStart;
    char * wordStart;
    char * line;
    //char line[MAXPAGES * OLDMAXPAGESIZE];
    //char& * line_in = line;
    int i;
    FILE *inFile, *outFile;

    if (argc != 1) {
        printf("error: usage: %s\n", argv[0]);
        exit(1);
    }

    // eof
    //while (fgets(line, MAXLINELENGTH, inFile) != NULL) {
    while (getline())
        while (line < MAXLINES)
            for (i = 0; ) 
            strcpy(text_in, )
    }

    /*inFile = fopen(argv[1], "r");
    if (inFile == NULL) {
        printf("error: can't open file %s", argv[1]);
        perror("fopen");
        exit(1);
    }
    
    bool isValid = false; 
    std::string input;
    while(!isValid) {
        printf("Enter version:\n1. Pre-1.14\n2. 1.14+\n");
        cin >> input;
    }*/
    
}



/*
Input their version
Input copy paste vs file interface

- Option to go to the end of sentences
Go to the word closest to the page limit (future: option for sentence closest to page limit) and do new page
If reach end of lines first, then stop there - check for 13th and then either checks for a newline or 

For old ver, increment 1 char for every new line and lines by 1; for new, just increment lines bc it doesn't matter unless last line

Store:
Ptr for start of page
Ptr for current location - next newline 


Check
If no newline for 22, add line and reset



 */