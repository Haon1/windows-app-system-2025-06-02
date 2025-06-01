#pragma once

typedef  char               INT8;
typedef  unsigned char      INT8U;
typedef  unsigned char      UINT8;

typedef  short int          INT16;
typedef  unsigned short int INT16U;
typedef  unsigned short int UINT16;

typedef  int                INT32;
typedef  unsigned  int      INT32U;
typedef  unsigned  int      UINT32;

typedef  float              FLOAT;
typedef  bool               BOOL;

typedef  void               VOID;

#define TRUE  1
#define FALSE 0

#define RELEASEIF(p)    do\
                        {\
                            if(p)\
                            {\
                                delete (p);\
                                (p) = nullptr;\
                            }\
                        }while(0);


#define ARRAYSIZE(arr) (sizeof(arr)/sizeof(arr[0]))
