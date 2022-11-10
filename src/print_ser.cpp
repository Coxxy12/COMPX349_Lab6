
#include "MicroBit.h"

MicroBit uBit;

void print_recv_serial() {
    while(1){
       uBit.sleep(20);
       ManagedString msg = uBit.serial.read(1024, ASYNC); // Read up until this amount if available, otherwise return what's there.
       uBit.display.scroll(msg);
    }
}

int main() {
    uBit.init();
    create_fiber(print_recv_serial); // create fiber and schedule it.
    release_fiber(); // "release the fibers!!"
}
