#include<iostream>
#include<fstream>
#include<string.h>
#include<string>
//#include <stdio.h>
//#include <stdlib.h>
//#include <ctype.h>

//using namespace std;
//#define NEWMAXPAGESIZE 307
/*
#define MAXPAGESIZE 225
#define MAXPAGES 50
#define MAXLINENUM 13
#define MAXLINELENGTH 116 // really just 115, but lobs off last space
#define NEWPAGETHRESH 220
#define BLANKLINELEN 1
*/


/*
i  58 + 58* spacing
l  38 * 2 + 38 * spacing
li 23 + 46 + 48 * spacing = 69 + 48 * spacing 
spacing = 9/10 of a character 1st 2
spacing = 11/10 for 1st and 3rd
just 1 char, the end varies though, for it does not need a space after it

 */

unsigned int width(char let) {
    switch (let) {
        //case 1, 2, 3: return 0;
        //likely far more cases
        case 'i': return 1;
        case '.': return 1;
        case ',': return 1;
        case ';': return 1;
        case ':': return 1;
        case '\'': return 1;
        case '!':
        return 1;
        case 'l': return 2;
        case '`':
        return 2;
        case '"': return 3;
        case '*': return 3;
        case '<': return 3;
        case '>': return 3;
        case '[': return 3;
        case ']': return 3;
        case 't': return 3;
        case '{': return 3;
        case '}':
        return 3;
        case '(': return 4;
        case ')': return 4;
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

void printWord (std::ofstream &out, std::string &line, int begin, int end) {
    /*for (; begin <= end; begin++) {
        out << line[begin];
    }*/
    out << line.substr(begin, end - begin + 1);
}

// Excludes commas and colons
bool lastPunctuation (unsigned int i, std::string &line) {
    i++;
    if (line.length() > i) {
        return (line[i] != '.' && line[i] != '!' && line[i] != '?' && line[i] != ';');
    }
    return true;
}

int main (int argc, char ** argv) {
		constexpr auto MAXPAGESIZE = 255;
		constexpr auto MAXPAGES = 50;
		constexpr auto MAXLINENUM = 13;
		constexpr auto MAXLINELENGTH = 116;
		constexpr auto NEWPAGETHRESH = 220;
		constexpr auto BLANKLINELEN = 1;

		std::ifstream inFile;
		std::ofstream outFile;
		std::string line;
    unsigned int i;
    //bool isPacked;

    if (argc != 4) {
        printf("error: usage: %s <input file> <output file> <packed>\ne.g. %s input.txt output.txt 1", argv[0], argv[0]);
        return 1;
    }

    inFile.open(argv[1]);
    outFile.open(argv[2]);

    if (!inFile.is_open()) {
        printf("error: can't open file %s", argv[1]);
        perror("fopen");
        return 1;
    } else if (!outFile.is_open()) {
        printf("error: can't open file %s", argv[2]);
        perror("fopen");
        return 1;
    }
    // maybe make non-const
    const bool isPacked = !strcmp(argv[3], "1");
    //cout << "PACKED? " << isPacked << "\n";


    // eof
    //while (fgets(line, MAXLINELENGTH, inFile) != NULL) {
    int li = 0;
    unsigned int pageNum = 1;
    unsigned int lineNum = 0; unsigned int inputLen = 0; unsigned int prevInputLen = 0;
    bool notWhiteSpace = false;
    outFile << "========PAGE 1========\n";
    while (getline(inFile, line) && pageNum <= MAXPAGES) {
        //cout << "LINE LENGTH: " << line.length() << "\n";
        // Make sure not on last line or over character lmit
        unsigned int lineStart = 0; unsigned int lineLen = 0;
        unsigned int wordStart = 0;
        
        prevInputLen = inputLen;
        inputLen = line.length();
        
        for (i = 0; i < inputLen; i++) {
            unsigned int potLineLen = lineLen + width(line[i]) + 1;
            
            // or do maxLines = 13 and do lineNum > maxLines and lineNum == maxLines
            // If exceeding page size, set line num to 0,
            //if (line == "") { cout << "MEOW\n"; }
            if (li > MAXPAGESIZE || lineNum > MAXLINENUM || (lineNum == MAXLINENUM && potLineLen > MAXLINELENGTH)) {
                if (line[i] == '\n' || line[i] == ' ') {
                    printWord(outFile, line, wordStart, i - 1);
                    wordStart = i + 1;
                }
                lineStart = wordStart;
                lineNum = li = 0;
                lineLen = i + 1 - wordStart;
                outFile << "\n========PAGE " << ++pageNum << "========\n";
                notWhiteSpace = false;
                //\printWord(outFile, line, wordStart, i);
            
            } else if (line[i] == '\n' || (line[i] == ' ' && potLineLen > MAXLINELENGTH)) {
                //printf("SHARK!\n");
                if (notWhiteSpace) { // can do 3 comparisons bc checking if 1
                    //printf("ATTACK!\n");
                    printWord(outFile, line, wordStart, i);
                    lineNum++;
                } else {
                    li--;
                }
                wordStart = lineStart = i + 1;
                lineLen = 0;
                
                // if at the end of a line and you press enter, does it just go to the next line or skip another?
                // if the latter, then check for being over the limit and ++lineNum if over
            } else if (line[i] == ' ') {
                if (notWhiteSpace) {
                    printWord(outFile, line, wordStart, i);
                    lineLen = potLineLen; // maybe have this at the end outside of if else statements depending on how ' ' works for new lines
                } else {
                    li--;
                    lineLen = 0;
                }
                wordStart = i+1;
            }
            
            // if newline, or space, deal with that
            // If over line size and the word isn't larger than a line, increment line 
            else if (potLineLen > MAXLINELENGTH && i - wordStart < MAXLINELENGTH) { // < instead of <= bc not doing +1 to account for size
                lineNum++;
                lineStart = wordStart;
                lineLen = i - wordStart + 1;
            } else if (lastPunctuation(i, line) && i + 1 != inputLen && 
                (line[i] == '.' || line[i] == '!' || line[i] == '?' || line[i] == ';')) {
                //cout << "Entry index: " << i << " for char " << line[i] << "\n";
                notWhiteSpace = true;
                /*if (i + 1 == line.length()) {
                    cout << "LASTCHAR\n";
                    printWord(outFile, line, wordStart, i);
                    lineNum = li = 0;
                } else */ if (!isPacked  && (lineNum + 1 >= MAXLINENUM || li > NEWPAGETHRESH)) {
                    //cout << "FORCE NEWLINE\n";
                    printWord(outFile, line, wordStart, i);
                    wordStart = lineStart = i + 1;
                    lineNum = li = lineLen = 0;
                    outFile << "\n========PAGE " << ++pageNum << "========\n";
                }

            } else if (inputLen > BLANKLINELEN) {
                //cout << "Else for " << line[i] << "\n";
                //cout << "Newline? " << (line[i] == '\n') << "\n";
                notWhiteSpace = true;
                lineLen = potLineLen;
            }
            ++li;
        }
        //cout << "NOT WHITE SPACE? " << notWhiteSpace << "\n";
        //cout << "Prev input length: " << prevInputLen << " input length: " << inputLen << "\n";
        //cout << "Double new? " << (prevInputLen == (inputLen == 1)) << " packed? " << isPacked << "\n";
        if (!isPacked && prevInputLen == BLANKLINELEN && inputLen == BLANKLINELEN && notWhiteSpace) {
            li--; //for prev \n
            //cout << "REEE\n";
            outFile << "\n========PAGE " << ++pageNum << "========\n";
            notWhiteSpace = false;

        } else if (notWhiteSpace) { // can do 3 comparisons bc checking if 1
            //printf("BABY!\n");
            printWord(outFile, line, wordStart, i);
            lineNum++;
            li++;
        }
        wordStart = lineStart = i + 1;
        lineLen = 0;
    }
    
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