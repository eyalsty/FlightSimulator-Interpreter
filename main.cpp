
#include "ClassMain.h"

using namespace std;

int main() {
    try {
        const char *filename = "text.txt";
        ClassMain main;
        main.parser(filename);
    } catch(std::bad_alloc& a){
        cout << a.what() << endl;
    }
    return 0;
}