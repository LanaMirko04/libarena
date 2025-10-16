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

## Functions

| Type | Name |
| ---: | :--- |
|  void \* | [**arena\_alloc**](#function-arena_alloc) (struct [**ArenaHandler**](#struct-arenahandler) \*harena, size\_t size) <br>_Allocate a block of memory from the arena._ |
|  void \* | [**arena\_alloc\_align**](#function-arena_alloc_align) (struct [**ArenaHandler**](#struct-arenahandler) \*harena, size\_t size, size\_t align) <br>_Allocate a block of memory from the arena with alignment._ |
|  void \* | [**arena\_calloc**](#function-arena_calloc) (struct [**ArenaHandler**](#struct-arenahandler) \*harena, size\_t size, size\_t count) <br>_Allocate and zero-initialize a block of memory from the arena._ |
|  void | [**arena\_free**](#function-arena_free) (struct [**ArenaHandler**](#struct-arenahandler) \*harena) <br>_Free all memory allocated in the arena._ |
|  int | [**arena\_init**](#function-arena_init) (struct [**ArenaHandler**](#struct-arenahandler) \*harena, size\_t capacity) <br>_Initialize an arena instance with a given capacity._ |

## Macros

| Type | Name |
| ---: | :--- |
| define  | [**ARENA\_DEFAULT\_ALIGN**](#define-arena_default_align)  \_Alignof(size\_t)<br> |
| define  | [**ARENA\_DEFAULT\_CAPACITY**](#define-arena_default_capacity)  0xFFU<br> |

## Structures and Types Documentation

### struct `ArenaHandler`

_The arena handler._

Variables:

-  uint8\_t \* buffer  <br>Pointer to the memory block

-  size\_t capacity  <br>Total capacity in bytes

-  size\_t offset  <br>Current allocation offset


## Functions Documentation

### function `arena_alloc`

_Allocate a block of memory from the arena._
```c
void * arena_alloc (
    struct ArenaHandler *harena,
    size_t size
) 
```


**Parameters:**


* `harena` Pointer to the arena handler. 
* `size` Size in bytes of the memory block to allocate. 


**Returns:**

Pointer to the allocated memory block, NULL otherwise.
### function `arena_alloc_align`

_Allocate a block of memory from the arena with alignment._
```c
void * arena_alloc_align (
    struct ArenaHandler *harena,
    size_t size,
    size_t align
) 
```


**Parameters:**


* `harena` Pointer to the arena handler. 
* `size` Size in bytes of the memory block to allocate. 
* `align` Alignment requirement for the allocated memory block. 


**Returns:**

Pointer to the allocated memory block, NULL otherwise.
### function `arena_calloc`

_Allocate and zero-initialize a block of memory from the arena._
```c
void * arena_calloc (
    struct ArenaHandler *harena,
    size_t size,
    size_t count
) 
```


**Parameters:**


* `harena` Pointer to the arena handler. 
* `size` Size in bytes of each element to allocate. 
* `count` Number of elements to allocate. 


**Returns:**

Pointer to the allocated memory block, NULL otherwise.
### function `arena_free`

_Free all memory allocated in the arena._
```c
void arena_free (
    struct ArenaHandler *harena
) 
```


**Parameters:**


* `harena` Pointer to the arena handler. 


**Returns:**

None.
### function `arena_init`

_Initialize an arena instance with a given capacity._
```c
int arena_init (
    struct ArenaHandler *harena,
    size_t capacity
) 
```


**Parameters:**


* `harena` Pointer to the handler to initialize. 
* `capacity` Size in bytes of the arena. 


**Returns:**

0 on success, non-zero otherwise.

## Macros Documentation

### define `ARENA_DEFAULT_ALIGN`

```c
#define ARENA_DEFAULT_ALIGN _Alignof(size_t)
```

### define `ARENA_DEFAULT_CAPACITY`

```c
#define ARENA_DEFAULT_CAPACITY 0xFFU
```


