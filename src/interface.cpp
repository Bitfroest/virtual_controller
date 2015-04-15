#include <virtual_controller.h>

extern "C" {
void* getInstance () {
    return new VirtualController();
}
}
