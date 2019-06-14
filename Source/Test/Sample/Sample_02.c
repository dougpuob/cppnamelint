#include <stdint.h>
typedef _FILE_ENTRY { void *pPtr; }
FILE_ENTRY;

#define IN
int MyFunc5ABC(char cValue) { return 0; }
int _GetNewAddress(IN uint8_t *const pu8Addr) { return 0; }

void _RemapToNewSpace(IN void *const pOld, IN FILE_ENTRY *const pNew) {
    return 0;
}