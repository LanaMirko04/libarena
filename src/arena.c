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
static inline size_t prv_arena_aligned_offset(size_t offset, size_t align) {
    return (offset + (align - 1)) & ~(align - 1);
}

/*!
 * \brief           Expand the buffer of the arena to accommodate more memory.
 *
 * \param[in]       arena: Pointer to the arena handler.
 * \return          ARENA_RC_OK on success, error code otherwise.
 *                   - ARENA_RC_INVALID_ARG: if the arena pointer is NULL.
 *                   - ARENA_RC_OUT_OF_MEM: if the new capacity exceeds maximum size.
 *                   - ARENA_RC_MEM_ALLOC_FAIL: if memory allocation fails.
 */
static enum ArenaReturnCode prv_arena_expand_buffer(struct ArenaHandler *arena) {
    if (!arena)
        return ARENA_RC_INVALID_ARG;

    size_t new_capacity = arena->capacity * 2U;
    if (new_capacity >= ARENA_MAX_SIZE)
        return ARENA_RC_OUT_OF_MEM;

    uint8_t *buffer = realloc(arena->buffer, new_capacity);
    if (!buffer)
        return ARENA_RC_MEM_ALLOC_FAIL;

    arena->buffer = buffer;
    arena->capacity = new_capacity;
    return ARENA_RC_OK;
}

enum ArenaReturnCode arena_init(struct ArenaHandler *arena) {
    if (!arena)
        return ARENA_RC_INVALID_ARG;

    arena->buffer = NULL;
    arena->capacity = 0U;
    arena->offset = 0U;

    return ARENA_RC_OK;
}

enum ArenaReturnCode arena_alloc(struct ArenaHandler *arena, size_t size, struct ArenaObj *obj) {
    return arena_alloc_align(arena, size, ARENA_DEFAULT_ALIGN, obj);
}

enum ArenaReturnCode arena_alloc_align(struct ArenaHandler *arena, size_t size, size_t align, struct ArenaObj *obj) {
    if (!arena || !obj || size == 0U)
        return ARENA_RC_INVALID_ARG;

    if (!arena->buffer) {
        arena->buffer = malloc(size);
        if (!arena->buffer)
            return ARENA_RC_MEM_ALLOC_FAIL;

        arena->capacity = size;
        arena->offset = 0U;
    }

    size_t offset = prv_arena_aligned_offset(arena->offset, align);
    if (offset + size > arena->capacity) {
        enum ArenaReturnCode res = prv_arena_expand_buffer(arena);
        if (res != ARENA_RC_OK)
            return res;
    }

    obj->arena = arena;
    obj->ptr = offset;
    arena->offset = offset + size;

    memset(arena->buffer + obj->ptr, 0U, size);
    return ARENA_RC_OK;
}

enum ArenaReturnCode arena_calloc(struct ArenaHandler *arena, size_t size, size_t count, struct ArenaObj *obj) {
    return arena_alloc(arena, size * count, obj);
}

void arena_clear(struct ArenaHandler *arena) {
    arena->offset = 0U;
}

void arena_free(struct ArenaHandler *arena) {
    if (arena->buffer) {
        free(arena->buffer);
        arena->buffer = NULL;
    }
    arena->capacity = 0U;
    arena->offset = 0U;
}

void *arena_get_ptr(const struct ArenaObj *obj) {
    assert(obj);
    assert(obj->arena);
    return (void *)(obj->arena->buffer + obj->ptr);
}
