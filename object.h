#ifndef clox_object_h
#define clox_object_h

#include "common.h"
#include "value.h"
#define OBJ_TYPE(value)    (AS_OBJ(value)->type)          //get object type
#define IS_STRING(value)    isObjType(value, Obj_STRING) //check if object is a string
#define AS_STRING(value)       ((ObjString*)AS_OBJ(value)) //get string object
#define AS_CSTRING(value)      (((ObjString*)AS_OBJ(value))->chars) //get string characters

typedef enum {
    Obj_STRING,
}ObjType;

struct Obj {
    ObjType type;
};

struct ObjString {
    Obj obj;
    int length;
    char* chars;
};

ObjString* takeString(char* chars, int length);

ObjString* copyString(const char* chars, int length);

void printObject(Value value);

static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}


#endif