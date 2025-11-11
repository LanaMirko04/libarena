# API Reference

## Header files

- [include/arena.h](#file-includearenah)

## File include/arena.h

_A lightweight easy implementation of an arena allocator._

**Date:**

2025-08-06 



**Author:**

Mirko Lana [[lana.mirko@icloud.com](mailto:lana.mirko@icloud.com)]

## Structures and Types

| Type | Name |
| ---: | :--- |
| struct | [**ArenaHandler**](#struct-arenahandler) <br>_The arena handler._ |
| struct | [**ArenaObj**](#struct-arenaobj) <br>_The arena object._ |
| enum  | [**ArenaReturnCode**](#enum-arenareturncode)  <br>_Return codes for arena operations._ |

## Functions

| Type | Name |
| ---: | :--- |
|  enum [**ArenaReturnCode**](#enum-arenareturncode) | [**arena\_alloc**](#function-arena_alloc) (struct [**ArenaHandler**](#struct-arenahandler) \*arena, size\_t size, struct [**ArenaObj**](#struct-arenaobj) \*obj) <br>_Allocate a block of memory from the arena._ |
|  enum [**ArenaReturnCode**](#enum-arenareturncode) | [**arena\_alloc\_align**](#function-arena_alloc_align) (struct [**ArenaHandler**](#struct-arenahandler) \*arena, size\_t size, size\_t align, struct [**ArenaObj**](#struct-arenaobj) \*obj) <br>_Allocate a block of memory from the arena with alignment._ |
|  enum [**ArenaReturnCode**](#enum-arenareturncode) | [**arena\_calloc**](#function-arena_calloc) (struct [**ArenaHandler**](#struct-arenahandler) \*arena, size\_t size, size\_t count, struct [**ArenaObj**](#struct-arenaobj) \*obj) <br>_Allocate and zero-initialize a block of memory from the arena._ |
|  void | [**arena\_clear**](#function-arena_clear) (struct [**ArenaHandler**](#struct-arenahandler) \*arena) <br>_Clear the arena without freeing the allocated buffer._ |
|  void | [**arena\_free**](#function-arena_free) (struct [**ArenaHandler**](#struct-arenahandler) \*arena) <br>_Free the arena and its allocated buffer._ |
|  void \* | [**arena\_get\_ptr**](#function-arena_get_ptr) (struct [**ArenaObj**](#struct-arenaobj) \*obj) <br>_Get a pointer to the memory allocated in the arena object._ |
|  enum [**ArenaReturnCode**](#enum-arenareturncode) | [**arena\_init**](#function-arena_init) (struct [**ArenaHandler**](#struct-arenahandler) \*arena) <br>_Initialize an arena instance with a given capacity._ |

## Macros

| Type | Name |
| ---: | :--- |
| define  | [**ARENA\_DEFAULT\_ALIGN**](#define-arena_default_align)  \_Alignof(size\_t)<br> |
| define  | [**ARENA\_MAX\_SIZE**](#define-arena_max_size)  ((size\_t)-1)<br> |

## Structures and Types Documentation

### struct `ArenaHandler`

_The arena handler._

Variables:

-  uint8\_t \* buffer  <br>Pointer to the memory block

-  size\_t capacity  <br>Total capacity in bytes

-  size\_t offset  <br>Current allocation offset

### struct `ArenaObj`

_The arena object._

Variables:

-  struct [**ArenaHandler**](#struct-arenahandler) \* arena  <br>Pointer to the arena handler that allocated the memory

-  uintptr\_t ptr  <br>The offset pointer within the arena

### enum `ArenaReturnCode`

_Return codes for arena operations._
```c
enum ArenaReturnCode {
    ARENA_RC_OK = 0,
    ARENA_RC_INVALID_ARG,
    ARENA_RC_OUT_OF_MEM,
    ARENA_RC_MEM_ALLOC_FAIL
};
```


## Functions Documentation

### function `arena_alloc`

_Allocate a block of memory from the arena._
```c
enum ArenaReturnCode arena_alloc (
    struct ArenaHandler *arena,
    size_t size,
    struct ArenaObj *obj
) 
```


**Parameters:**


* `arena` Pointer to the arena handler. 
* `size` Size in bytes of the memory block to allocate. 
* `obj` Pointer to the arena object to store allocation info. 


**Returns:**

ARENA\_RC\_OK on success, error code otherwise.

* ARENA\_RC\_INVALID\_ARG: if invalid arguments are provided.
* ARENA\_RC\_OUT\_OF\_MEM: if ARENA\_MAX\_SIZE is exceeded.
### function `arena_alloc_align`

_Allocate a block of memory from the arena with alignment._
```c
enum ArenaReturnCode arena_alloc_align (
    struct ArenaHandler *arena,
    size_t size,
    size_t align,
    struct ArenaObj *obj
) 
```


**Parameters:**


* `arena` Pointer to the arena handler. 
* `size` Size in bytes of the memory block to allocate. 
* `align` Alignment requirement for the allocated memory block. 
* `obj` Pointer to the arena object to store allocation info. 


**Returns:**

ARENA\_RC\_OK on success, error code otherwise.

* ARENA\_RC\_INVALID\_ARG: if invalid arguments are provided.
* ARENA\_RC\_OUT\_OF\_MEM: if ARENA\_MAX\_SIZE is exceeded.
### function `arena_calloc`

_Allocate and zero-initialize a block of memory from the arena._
```c
enum ArenaReturnCode arena_calloc (
    struct ArenaHandler *arena,
    size_t size,
    size_t count,
    struct ArenaObj *obj
) 
```


**Parameters:**


* `arena` Pointer to the arena handler. 
* `size` Size in bytes of each element to allocate. 
* `count` Number of elements to allocate. 
* `obj` Pointer to the arena object to store allocation info. 


**Returns:**

ARENA\_RC\_OK on success, error code otherwise.

* ARENA\_RC\_INVALID\_ARG: if invalid arguments are provided.
* ARENA\_RC\_OUT\_OF\_MEM: if ARENA\_MAX\_SIZE is exceeded.
### function `arena_clear`

_Clear the arena without freeing the allocated buffer._
```c
void arena_clear (
    struct ArenaHandler *arena
) 
```


**Parameters:**


* `arena` Pointer to the arena handler. 


**Returns:**

None.
### function `arena_free`

_Free the arena and its allocated buffer._
```c
void arena_free (
    struct ArenaHandler *arena
) 
```


**Parameters:**


* `arena` Pointer to the arena handler. 


**Returns:**

None.
### function `arena_get_ptr`

_Get a pointer to the memory allocated in the arena object._
```c
void * arena_get_ptr (
    struct ArenaObj *obj
) 
```


**Parameters:**


* `obj` Pointer to the arena object. 


**Returns:**

Pointer to the allocated memory block.
### function `arena_init`

_Initialize an arena instance with a given capacity._
```c
enum ArenaReturnCode arena_init (
    struct ArenaHandler *arena
) 
```


\_\_cplusplus



**Parameters:**


* `arena` Pointer to the handler to initialize. 


**Returns:**

ARENA\_RC\_OK on success, error code otherwise.

* ARENA\_RC\_INVALID\_ARG: if the arena pointer is NULL.

## Macros Documentation

### define `ARENA_DEFAULT_ALIGN`

```c
#define ARENA_DEFAULT_ALIGN _Alignof(size_t)
```


Default alignment for allocations
### define `ARENA_MAX_SIZE`

```c
#define ARENA_MAX_SIZE ((size_t)-1)
```


Maximum size for allocations

