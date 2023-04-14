#ifndef MINLIB_STDBOOL_H
#define MINLIB_STDBOOL_h

#ifndef bool
    #define bool _Bool
// TODO check doesnt break _Bool
#ifndef _Bool
    #define bool unsigned char
#endif
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#endif