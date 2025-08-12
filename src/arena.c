/*!
 * \file            arena.c
 * \date            2025-08-06
 * \author          Mirko Lana [lana.mirko@icloud.com]
 *
 * \brief           A lightweight easy implementation of an arena allocator.
 */

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "arena.h"

/*!
 * \brief           Calculate the aligned offset for a given offset.
 *
 * \param[in]       offset: The original offset to align.
 * \param[in]       align: The alignment requirement.
 * \return          The aligned offset that meets the specified alignment.
 */
static size_t prv_arena_aligned_offset(size_t offset, size_t align) {
    return (offset + (align - 1)) & ~(align - 1);
}

/*!
 * \brief           Expand the buffer of the arena to accommodate more memory.
 *
 * \param[in]       harena: Pointer to the arena handler.
 * \return          None. The function will assert if the reallocation fails.
 */
static void prv_arena_expand_buffer(ArenaHandler_t *harena) {
    assert(harena != NULL);

    uint8_t *buffer = realloc(harena->buffer, harena->capacity * 2U);
    assert(buffer != NULL);

    harena->buffer = buffer;
    harena->capacity *= 2U;
}

int arena_init(ArenaHandler_t *harena, size_t capacity) {
    if (harena == NULL)
        return -1;

    harena->offset = 0U;
    harena->capacity = capacity != 0U ? capacity : ARENA_DEFAULT_CAPACITY;
    harena->buffer = (uint8_t *)malloc(capacity);
    if (harena->buffer == NULL)
        return -1;

    return 0;
}

void *arena_alloc(ArenaHandler_t *harena, size_t size) {
    return arena_alloc_align(harena, size, ARENA_DEFAULT_ALIGN);
}

void *arena_alloc_align(ArenaHandler_t *harena, size_t size, size_t align) {
    if (harena == NULL || size == 0U)
        return NULL;

    size_t offset = prv_arena_aligned_offset(harena->offset, align);

    if (offset + size >= harena->capacity)
        prv_arena_expand_buffer(harena);

    harena->offset = offset + size;

    memset(&harena->buffer[offset], 0, size);

    return (void *)&harena->buffer[offset];
}

void *arena_calloc(ArenaHandler_t *harena, size_t size, size_t count) {
    return arena_alloc(harena, size * count);
}

void arena_free(ArenaHandler_t *harena) { harena->offset = 0U; }
