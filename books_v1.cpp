#include<iostream>
#include <fstream>
#include<string>
//#include <stdio.h>
//#include <stdlib.h>
//#include <ctype.h>

using namespace std;
//#define NEWMAXPAGESIZE 307
#define MAXPAGESIZE 255
#define MAXPAGES 50
#define MAXLINES 14
#define MAXLINELENGTH 115 // prev 22
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

/*void printPage(ostream& os, std::string line, int start, int end) {
    os << line.substr(start, end);
}*/


/*
i  58 + 58* spacing
l  38 * 2 + 38 * spacing
li 23 + 46 + 48 * spacing = 69 + 48 * spacing 
spacing = 9/10 of a character 1st 2
spacing = 11/10 for 1st and 3rd
just 1 char, the end varies though, for it does not need a space after it

 */

int width(char let) {
    switch (let) {
        //case 1, 2, 3: return 0;
        //likely far more cases
        case 'i':
        case '.':
        case ',':
        case ';':
        case ':':
        case '\'':
        case '!':
        return 1;
        case 'l':
        case '`':
        return 2;
        case '"':
        case '*':
        case '<':
        case '>':
        case '[':
        case ']':
        case 't':
        case '{':
        case '}':
        return 3;
        case '(':
        case ')':
        case 'k':
        return 4;
        case '~': return 6;
        default: return 5;


        /*case 'i', '.', ',', ';', ':', '\'', '!' : return 1; // 1 wide: i . , ; : ' !  
        case 'l', '`' : return 2; // apostrophe
        case '"', '*', '<', '>', '[', ']', 't', '{', '}' : return 3;
        case '(', ')', 'k': return 4; // quotations
        case '~': return 6;
        default: return 5;*/
    }
}

void printWord (ofstream &out, std::string &input, int begin, int end) {
    for (; begin <= end; begin++) {
        out << input[begin];
    }
}

int main (int argc, char ** argv) {
    /* char lineNum = 0;
    char * pageStart;
    char * lineStart;
    char * wordStart; */
    //char * line;
    std::string line;
    //char line[MAXPAGES * MAXPAGESIZE];
    //char& * line_in = line;
    int i, j;
    //FILE *inFile, *outFile;
    ifstream inFile;
    ofstream outFile;

    inFile.open(argv[1]);
    inFile.open(argv[2]);

    if (argc != 3) {
        printf("error: usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    if (!inFile.is_open()) {
        printf("error: can't open file %s", argv[1]);
        perror("fopen");
        exit(1);
    } else if (!outFile.is_open()) {
        printf("error: can't open file %s", argv[2]);
        perror("fopen");
        exit(1);
    }

    /*inFile = fopen(argv[1], "r");
    if (inFile == NULL) {
        printf("error: can't open file %s", argv[1]);
        perror("fopen");
        exit(1);
    }
    outFile = fopen(argv[2], "w");
    if (outFile == NULL) {
        printf("error: can't open file %s", argv[2]);
        perror("fopen");
        exit(1);
    }*/

    // eof
    //while (fgets(line, MAXLINELENGTH, inFile) != NULL) {
    int li = 0;
    while (getline(inFile, line)) {
        // Make sure not on last line or over character lmit
        int lastWord = 0; int lineStart = 0; int pageStart = 0; int lineNum = 0; int lineLen = 0;
        int wordStart = 0;
        
        for (i = 0; i < line.length(); i++) {
            // If at the end or if at last line and max char, go to back of last character
            // Print everything between start page and last word
            //int letWidth = width(line[i]);
            /*if (i == MAXPAGESIZE || ( ((lineWidth + letWidth) > MAXLINELENGTH) && lineNum == (MAXLINES - 1) ) || lineNum == MAXLINES) {
                outFile << (line.substr(pageStart, lastWord)) << "\n\n";

            }


            if (line[i] == '\n') {
                // last word is the endline - why here?
                lineNum++; lineStart = i + 1; lastWord = i;
                // maybe do something special if this is at the end
            } else if (line[i] == ' ') {
                
                // if == 22 do something
            } else if (lineWidth + letWidth > MAXLINELENGTH) {
                lineNum++; lastWord 
            }

            // check if over the line otherwise and if at page limit, I think

            while (line[i] != ) {}*/
            int potLineLen = lineLen + width(line[i]) + 1;
            // or do maxLines = 13 and do lineNum > maxLines and lineNum == maxLines
            if (li - pageStart == 255 || lineNum == 14 || (lineNum == 13 && potLineLen > MAXLINELENGTH)) {
                pageStart = lineStart = wordStart;
                lineNum = 0;
                lineLen = wordStart - i + 1;
                outFile << "\n\n";
            
            } else if (line[i] == '\n' || (line[i] == ' ' && potLineLen > MAXLINELENGTH)) {
                wordStart = lineStart = i+1;
                lineNum++;
                lineLen = 0; // doesn't really matter but eh
                printWord(outFile, line, wordStart, i);
                // if at the end of a line and you press enter, does it just go to the next line or skip another?
                // if the latter, then check for being over the limit and ++lineNum if over
            } else if (line[i] == ' ') {
                wordStart = i+1;
                lineLen = potLineLen; // maybe have this at the end outside of if else statements depending on how ' ' works for new lines
                printWord(outFile, line, wordStart, i);
            }
            
            // if newline, or space, deal with that
            else if (potLineLen > MAXLINELENGTH && wordStart - i < MAXLINELENGTH) { // < instead of <= bc not doing +1 to account for size
                lineNum++;
                lineStart = wordStart;
                lineLen = lineStart;
            }
            else {
                lineLen = potLineLen;
            }
            ++li;

        }
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
- will this word put it over the tipping point? If so, it is going to compose the start of the next line



 */


/* 
Get line
Parse word by word
Add each word to the out file if it doesn't go over limit
If word goes onto next line, add one line and note the starting amount of chars on the next line
Note spaces

 */