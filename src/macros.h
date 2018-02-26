#ifndef _MACROS_H_
#define _MACROS_H_
#define IRAM0 __attribute__((section(".irom0.text")))
#define RODATA_ATTR  __attribute__((section(".irom.text"))) __attribute__((aligned(4)))
#define ROMSTR_ATTR  __attribute__((section(".irom.text.romstr"))) __attribute__((aligned(4)))
#define ROMSTR(s) (__extension__({static const char __c[] ROMSTR_ATTR = (s); &__c[0];}))

#define __asize(x) (sizeof(x) / sizeof(x[0]))

#endif /* _MACROS_H_ */
