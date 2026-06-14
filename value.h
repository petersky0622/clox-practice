#ifndef clox_value_h
#define clox_value_h

#include "common.h"
#include "object.h"
typedef struct Obj Obj;
typedef struct ObjString ObjString;



typedef enum {
    VAL_BOOL,
    VAL_NIL,
    VAL_NUMBER,
    VAL_OBJ,
} ValueType;

typedef struct
{
    ValueType type;
    union
    {
        bool boolean;
        double number;
        Obj* obj;
    } as;

}Value;

#define IS_BOOL(value)    ((value).type == VAL_BOOL)                 //checking value type
#define IS_NIL(value)     ((value).type == VAL_NIL)
#define IS_NUMBER(value)  ((value).type == VAL_NUMBER)
#define IS_OBJ(value)     ((value).type == VAL_OBJ)

#define AS_BOOL(value)     ((value).as.boolean)                               //unpacking
#define AS_NUMBER(value)   ((value).as.number)                               //unpacking                
#define AS_OBJ(value)      ((value).as.obj)                                  //unpacking

#define BOOL_VAL(value)    ((Value){VAL_BOOL, {.boolean = value}})    //packing
#define NIL_VAL            ((Value){VAL_NIL, {.number = 0}})             //packing
#define NUMBER_VAL(value)  ((Value){VAL_NUMBER, {.number = value}})       //packing
#define OBJ_VAL(value)     ((Value){VAL_OBJ, {.obj = (Obj*)value}})       //packing

typedef struct {                                          //value array     
    int capacity;                                         //array capacity
    int count;                                            //array count
    Value* values;
} ValueArray;                                          //value array                

bool valuesEqual(Value a, Value b);
void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif
