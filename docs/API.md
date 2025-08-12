# Arena - API Reference

## Macros

| Macro                  | Value            | Description                     |
|------------------------|------------------|---------------------------------|
| ARENA_DEFAULT_CAPACITY | 0xFFU            | Default handler buffer capacity |
| ARENA_DEFAULT_ALIGN    | _Alignof(size_t) | Default alignment               |

## Data Types

### `ArenaHandler_t`
```c
typedef struct ArenaHandler {
    uint8_t *buffer; /*!< Pointer to the memory block */
    size_t capacity; /*!< Total capacity in bytes */
    size_t offset;   /*!< Current allocation offset */
} ArenaHandler_t;
```

This structure represents the state of an arena instance.

## Functions

### `int arena_init(ArenaHandler_t *harena, size_t capacity)`

#### Description:
Initializes the arena instance with the given capacity. If capacity is equal to
`0U`, `ARENA_DEFAULT_CAPACITY` is used instead.

#### Parameters:

- `harena` - Pointer to an ArenaHandler_t structure to initialize.
- `capacity` - Size in bytes of the arena.

#### Returns:

- `0` on success.
- Non-zero otherwise.

#### Usage:

```c
ArenaHandler_t arena;
if (arena_init(&arena, 0U) != 0) {
    fprintf(stderr, "Failed to initialize arena\n");
    exit(EXIT_FAILURE);
}
```

### `void *arena_alloc(ArenaHandler_t *harena, size_t size)`

#### Description:
Allocates `size` bytes.

#### Parameters:

- `harena` - Pointer to an arena handler.
- `size` - Number of bytes to allocate.

#### Returns:

- Pointer to allocated memory.
- `NULL` otherwise.
s#### Usage:

```c
uint32_t *ptr = arena_alloc(&arena, sizeof(uint32_t));
if (ptr == NULL) {
    fprintf(stderr, "Failed to allocate memory\n");
    exit(EXIT_FAILURE);
}
```
### `void *arena_alloc_align(ArenaHandler_t *harena, size_t size, size_t align)`

#### Description:
Allocates `size` bytes with a specific alignment.

#### Parameters:

- `harena` - Pointer to an arena handler.
- `size` - Number of bytes to allocate.
- `align` - Alignment in bytes (must be a power of two).

#### Returns:

- Pointer to allocated memory.
- `NULL` otherwise.

#### Usage:

```c
double *ptr = arena_alloc_align(&arena, sizeof(uint32_t), 32U);
if (ptr == NULL) {
    fprintf(stderr, "Failed to allocate memory\n");
    exit(EXIT_FAILURE);
}
```

### `void *arena_calloc(ArenaHandler_t *harena, size_t size, size_t count)`

#### Description:
Allocates zero-initialized memory for an array.

#### Parameters:

- `harena` - Pointer to an arena handler.
- `size` - Size of each element.
- `count` - Number of elements.

#### Returns:

- Pointer to allocated memory.
- `NULL` otherwise.

#### Usage:

```c
int16_t *ptr = arena_calloc(&arena, sizeof(int16_t), 20U);
if (ptr == NULL) {
    fprintf(stderr, "Failed to allocate memory\n");
    exit(EXIT_FAILURE);
}
```

### `void arena_free(ArenaHandler_t *harena)`

#### Description:
Frees the arena's memory and resets its state.

#### Parameters:

- `harena` - Pointer to an arena handler.

#### Usage:

```c
arena_free(&arena);
```
