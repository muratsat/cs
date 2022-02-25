#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum type{
    RM,
    RR,
    RI,
    J
};

class compiler{

    // table of codes and their numbers
    map<string, int> code;

    // table of code and their types
    map<string, int> codeType;

    // table of register name and their number
    map<string, int> registerInt;

    public:
    compiler();
    ~compiler();
    
    // read and return vector of lines
    // from FILENAME
    vector<string> readfile(const char* filename);

    // split string into 
    // separate words
    vector<string> split_words(string line);

    // operation code
    // returns -1 if doesn't exist
    int opcode(string word);

    // operation type(RM, RR, RI, J)
    // returns -1 if doesn't exist
    int optype(string word);
};