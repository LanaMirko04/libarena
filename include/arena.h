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

#define ARENA_DEFAULT_CAPACITY 0xFFU
#define ARENA_DEFAULT_ALIGN _Alignof(size_t)

/*!
 * \brief           The arena handler.
 */
struct ArenaHandler {
    uint8_t *buffer; /*!< Pointer to the memory block */
    size_t capacity; /*!< Total capacity in bytes */
    size_t offset;   /*!< Current allocation offset */
};

/*!
 * \brief           Initialize an arena instance with a given capacity.
 *
 * \param[out]      harena: Pointer to the handler to initialize.
 * \param[in]       capacity: Size in bytes of the arena.
 * \return          0 on success, non-zero otherwise.
 */
int arena_init(struct ArenaHandler *harena, size_t capacity);

/*!
 * \brief           Allocate a block of memory from the arena.
 *
 * \param[in]       harena: Pointer to the arena handler.
 * \param[in]       size: Size in bytes of the memory block to allocate.
 * \return          Pointer to the allocated memory block, NULL otherwise.
 */
void *arena_alloc(struct ArenaHandler *harena, size_t size);

/*!
 * \brief           Allocate a block of memory from the arena with alignment.
 *
 * \param[in]       harena: Pointer to the arena handler.
 * \param[in]       size: Size in bytes of the memory block to allocate.
 * \param[in]       align: Alignment requirement for the allocated memory block.
 * \return          Pointer to the allocated memory block, NULL otherwise.
 */
void *arena_alloc_align(struct ArenaHandler *harena, size_t size, size_t align);

/*!
 * \brief           Allocate and zero-initialize a block of memory from the
 * arena.
 *
 * \param[in]       harena: Pointer to the arena handler.
 * \param[in]       size: Size in bytes of each element to allocate.
 * \param[in]       count: Number of elements to allocate.
 * \return          Pointer to the allocated memory block, NULL otherwise.
 */
void *arena_calloc(struct ArenaHandler *harena, size_t size, size_t count);

/*!
 * \brief           Free all memory allocated in the arena.
 *
 * \param[in]       harena: Pointer to the arena handler.
 * \return          None.
 */
void arena_free(struct ArenaHandler *harena);

#endif /*! ARENA_H */
