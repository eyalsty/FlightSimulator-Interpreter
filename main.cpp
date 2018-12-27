
#include "ClassMain.h"

using namespace std;

int main() {

    try {
        const char *filename = "text.txt";
        ClassMain main;
        main.parser(filename);
    } catch (std::bad_alloc &a) {
        cout << a.what() << endl;
    }
    return 0;
//    queue<string> q;
//    pthread_mutex_t mutex;
//    pthread_mutex_init(&mutex, nullptr);
//    ConnectCommand connect = ConnectCommand(q, mutex);
//    connect.setMembers(true, "set /controls/engines/current-engine/throttle 1.0\r\n");
//    connect.openClient("10.0.2.2" , 5402);
//    while(true){
//
//    }

}
