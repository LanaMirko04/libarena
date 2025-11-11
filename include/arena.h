/*!
 * \file            arena.h
 * \date            2025-08-06
 * \author          Mirko Lana [lana.mirko@icloud.com]
 *
 * \brief           A lightweight easy implementation of an arena allocator.
 */

#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>
#include <stdint.h>

#define ARENA_DEFAULT_ALIGN _Alignof(size_t) /*!< Default alignment for allocations */
#define ARENA_MAX_SIZE ((size_t)-1)          /*!< Maximum size for allocations */

/*!
 * \brief           Return codes for arena operations.
 */
enum ArenaReturnCode {
    ARENA_RC_OK = 0,        /*!< Operation successful */
    ARENA_RC_INVALID_ARG,   /*!< Invalid argument provided */
    ARENA_RC_OUT_OF_MEM,    /*!< Out of memory */
    ARENA_RC_MEM_ALLOC_FAIL /*!< Memory allocation failed */
};

/*!
 * \brief           The arena handler.
 */
struct ArenaHandler {
    uint8_t *buffer; /*!< Pointer to the memory block */
    size_t capacity; /*!< Total capacity in bytes */
    size_t offset;   /*!< Current allocation offset */
};

/*!
 * \brief           The arena object.
 */
struct ArenaObj {
    struct ArenaHandler *arena; /*!< Pointer to the arena handler that allocated the memory */
    uintptr_t ptr;              /*!< The offset pointer within the arena */
};

#ifdef __cplusplus
extern "C" {
#endif /*! __cplusplus */

/*!
 * \brief           Initialize an arena instance with a given capacity.
 *
 * \param[out]      arena: Pointer to the handler to initialize.
 * \return          ARENA_RC_OK on success, error code otherwise.
 *                   - ARENA_RC_INVALID_ARG: if the arena pointer is NULL.
 */
enum ArenaReturnCode arena_init(struct ArenaHandler *arena);

/*!
 * \brief           Allocate a block of memory from the arena.
 *
 * \param[in]       arena: Pointer to the arena handler.
 * \param[in]       size: Size in bytes of the memory block to allocate.
 * \param[out]      obj: Pointer to the arena object to store allocation info.
 * \return          ARENA_RC_OK on success, error code otherwise.
 *                   - ARENA_RC_INVALID_ARG: if invalid arguments are provided.
 *                   - ARENA_RC_OUT_OF_MEM: if ARENA_MAX_SIZE is exceeded.
 *                   - ARENA_RC_MEM_ALLOC_FAIL: if memory allocation fails.
 */
enum ArenaReturnCode arena_alloc(struct ArenaHandler *arena, size_t size, struct ArenaObj *obj);

/*!
 * \brief           Allocate a block of memory from the arena with alignment.
 *
 * \param[in]       arena: Pointer to the arena handler.
 * \param[in]       size: Size in bytes of the memory block to allocate.
 * \param[in]       align: Alignment requirement for the allocated memory block.
 * \param[out]      obj: Pointer to the arena object to store allocation info.
 * \return          ARENA_RC_OK on success, error code otherwise.
 *                   - ARENA_RC_INVALID_ARG: if invalid arguments are provided.
 *                   - ARENA_RC_OUT_OF_MEM: if ARENA_MAX_SIZE is exceeded.
 *                   - ARENA_RC_MEM_ALLOC_FAIL: if memory allocation fails.
 */
enum ArenaReturnCode arena_alloc_align(struct ArenaHandler *arena, size_t size, size_t align, struct ArenaObj *obj);

/*!
 * \brief           Allocate and zero-initialize a block of memory from the
 * arena.
 *
 * \param[in]       arena: Pointer to the arena handler.
 * \param[in]       size: Size in bytes of each element to allocate.
 * \param[in]       count: Number of elements to allocate.
 * \param[out]      obj: Pointer to the arena object to store allocation info.
 * \return          ARENA_RC_OK on success, error code otherwise.
 *                   - ARENA_RC_INVALID_ARG: if invalid arguments are provided.
 *                   - ARENA_RC_OUT_OF_MEM: if ARENA_MAX_SIZE is exceeded.
 *                   - ARENA_RC_MEM_ALLOC_FAIL: if memory allocation fails.
 */
enum ArenaReturnCode arena_calloc(struct ArenaHandler *arena, size_t size, size_t count, struct ArenaObj *obj);

/*!
 * \brief           Clear the arena without freeing the allocated buffer.
 *
 * \param[out]      arena: Pointer to the arena handler.
 * \return          None.
 */
void arena_clear(struct ArenaHandler *arena);

/*!
 * \brief           Free the arena and its allocated buffer.
 *
 * \param[out]      arena: Pointer to the arena handler.
 * \return          None.
 */
void arena_free(struct ArenaHandler *arena);

/*!
 * \brief           Get a pointer to the memory allocated in the arena object.
 *
 * \param[in]       obj: Pointer to the arena object.
 * \return          Pointer to the allocated memory block.
 */
void *arena_get_ptr(struct ArenaObj *obj);

#ifdef __cplusplus
}
#endif /*! __cplusplus */

#endif /*! ARENA_H */
