#include "bmfgen.hpp"
#include <iostream>

using namespace std;

int main(int argc, const char *argv[]) {
    if (argc > 1) {
        FILE *opes = fopen("test.bmf", "rw");
        if (!opes){
            cout << "!opes" << endl;
            return 1;
        }
        else {
            bmf_header_t header;
            fprintf(opes, "(void*)header");
        }
    } else {
        cout << "usage: bmfgen [file ...]" << endl;
    }
    return 0;
}
