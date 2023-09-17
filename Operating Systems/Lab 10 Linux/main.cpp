#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main (int argc, char ** argv) {
    int i;

    for( i=1; i<argc-1; i++)
    {   //0 - stdin, 1 - stdout
        int pd[2]; // pd[0] - end of read, pd[1] - end of write
        pipe(pd);
        cout << "launched " << argv[i] << "\n";
        if (!fork()) {
            dup2(pd[1], 1);
            execlp(argv[i], argv[i], NULL);
            perror("exec");
            abort();
        }


        dup2(pd[0], 0); // 0 - stdin
        close(pd[1]);
    }

    execlp(argv[i], argv[i], NULL);
    perror("exec");
    abort();
}
