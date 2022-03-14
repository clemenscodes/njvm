#ifndef _MACROS_H
#define _MACROS_H

#define IMMEDIATE(x) ((x)&0x00FFFFFF)
#define SIGN_EXTEND(i) ((i)&0x00800000 ? (i) | 0xFF000000 : (i))
#define MSB (1 << (8 * sizeof(unsigned int) - 1))
#define BROKEN_HEART (1 << (8 * sizeof(unsigned int) - 2))
#define IS_PRIMITIVE(obj_ref) (((obj_ref)->size & MSB) == 0)
#define GET_ELEMENT_COUNT(obj_ref) ((obj_ref)->size & ~MSB)
#define GET_REFS_PTR(obj_ref) ((ObjRef *)(obj_ref)->data)
#define COPIED_MASK ((3 << 30))
#define IS_COPIED(obj_ref) (((obj_ref)->size & ~COPIED_MASK) == 0)

#endif
