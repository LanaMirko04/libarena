/*!
 * \file            test-arena.c
 * \date            2025-08-11
 * \authors         Mirko Lana [lana.mirko@icloud.com]
 *
 * \brief           Unit tests powered by Unity.
 */

#include "arena.h"
#include "unity.h"
#include <stdint.h>

#define DEFAULT_ARENA_CAPACITY 0x400U
#define ERR -1
#define OK 0

ArenaHandler_t arena;

void setUp(void) { arena_init(&arena, DEFAULT_ARENA_CAPACITY); }
void tearDown(void) { arena_free(&arena); }

/*!
 * \defgroup        arena_init Test module initialization.
 * @{
 */

void check_arena_init_with_null_handler(void) {
    int ret = arena_init(NULL, DEFAULT_ARENA_CAPACITY);
    TEST_ASSERT_EQUAL_INT(ERR, ret);
}

void check_arena_init_with_zero_capacity(void) {
    int ret = arena_init(&arena, 0U);
    TEST_ASSERT_EQUAL_INT(OK, ret);
    TEST_ASSERT_EQUAL_UINT(ARENA_DEFAULT_CAPACITY, arena.capacity);
    TEST_ASSERT_NOT_NULL(arena.buffer);
    TEST_ASSERT_EQUAL_UINT(0, arena.offset);
}

void check_arena_init(void) {
    int ret = arena_init(&arena, DEFAULT_ARENA_CAPACITY);
    TEST_ASSERT_EQUAL_INT(OK, ret);
    TEST_ASSERT_EQUAL_UINT(DEFAULT_ARENA_CAPACITY, arena.capacity);
    TEST_ASSERT_NOT_NULL(arena.buffer);
    TEST_ASSERT_EQUAL_UINT(0, arena.offset);
}

/*!
 * @}
 */

/*!
 * \defgroup        arena_alloc Test arena_alloc behavior.
 * @{
 */

void check_arena_alloc_returns_non_null_and_zeroed(void) {
    void *ptr = arena_alloc(&arena, 16);
    TEST_ASSERT_NOT_NULL(ptr);

    uint8_t *bytes = (uint8_t *)ptr;
    for (size_t i = 0; i < 16; i++) {
        TEST_ASSERT_EQUAL_UINT8(0, bytes[i]);
    }
}

void check_arena_alloc_sequential_allocations_do_not_overlap(void) {
    void *p1 = arena_alloc(&arena, 16);
    void *p2 = arena_alloc(&arena, 32);
    TEST_ASSERT_NOT_NULL(p1);
    TEST_ASSERT_NOT_NULL(p2);
    TEST_ASSERT_TRUE(p2 > p1);
    TEST_ASSERT_TRUE(((uintptr_t)p2) >= ((uintptr_t)p1 + 16));
}

void check_arena_alloc_expands_buffer_when_needed(void) {
    void *p1 = arena_alloc(&arena, arena.capacity - 8);
    TEST_ASSERT_NOT_NULL(p1);
    void *p2 = arena_alloc(&arena, 16);
    TEST_ASSERT_NOT_NULL(p2);
    TEST_ASSERT_TRUE(arena.capacity > DEFAULT_ARENA_CAPACITY);
}

/*!
 * @}
 */

/*!
 * \defgroup        arena_alloc_align Test aligned allocations.
 * @{
 */

void check_arena_alloc_align_returns_aligned_pointer(void) {
    size_t align = 16;
    void *ptr = arena_alloc_align(&arena, 24, align);
    TEST_ASSERT_NOT_NULL(ptr);
    TEST_ASSERT_EQUAL_UINT(0, ((uintptr_t)ptr) % align);
}

void check_arena_alloc_align_multiple_allocations_alignment(void) {
    size_t align = 8;
    void *p1 = arena_alloc_align(&arena, 10, align);
    void *p2 = arena_alloc_align(&arena, 20, align);
    TEST_ASSERT_NOT_NULL(p1);
    TEST_ASSERT_NOT_NULL(p2);
    TEST_ASSERT_TRUE(p2 > p1);
    TEST_ASSERT_EQUAL_UINT(0, ((uintptr_t)p1) % align);
    TEST_ASSERT_EQUAL_UINT(0, ((uintptr_t)p2) % align);
}

/*!
 * @}
 */

/*!
 * \defgroup        arena_calloc Test arena_calloc behavior.
 * @{
 */

void check_arena_calloc_zeroes_memory(void) {
    size_t count = 10;
    size_t size = sizeof(int);
    int *arr = (int *)arena_calloc(&arena, size, count);
    TEST_ASSERT_NOT_NULL(arr);
    for (size_t i = 0; i < count; i++) {
        TEST_ASSERT_EQUAL_INT(0, arr[i]);
    }
}

/*!
 * @}
 */

/*!
 * \defgroup        arena_free Test arena_free behavior.
 * @{
 */

void check_arena_free_resets_offset(void) {
    void *p1 = arena_alloc(&arena, 16);
    arena_free(&arena);
    void *p2 = arena_alloc(&arena, 16);
    TEST_ASSERT_EQUAL_PTR(p1, p2);
}

/*!
 * @}
 */

int main(void) {
    UNITY_BEGIN();

    /*!
     * \defgroup        arena_alloc_align Test module initialization.
     * @{
     */

    RUN_TEST(check_arena_init_with_null_handler);
    RUN_TEST(check_arena_init_with_zero_capacity);
    RUN_TEST(check_arena_init);

    /*!
     * @}
     */

    /*!
     * \defgroup        arena_alloc Test aligned behavior.
     * @{
     */

    RUN_TEST(check_arena_alloc_returns_non_null_and_zeroed);
    RUN_TEST(check_arena_alloc_sequential_allocations_do_not_overlap);
    RUN_TEST(check_arena_alloc_expands_buffer_when_needed);

    /*!
     * @}
     */

    /*!
     * \defgroup        arena_alloc_align Test aligned allocations.
     * @{
     */

    RUN_TEST(check_arena_alloc_align_returns_aligned_pointer);
    RUN_TEST(check_arena_alloc_align_multiple_allocations_alignment);

    /*!
     * @}
     */

    /*!
     * \defgroup        arena_calloc Test arena_calloc behavior.
     * @{
     */

    RUN_TEST(check_arena_calloc_zeroes_memory);

    /*!
     * @}
     */

    /*!
     * \defgroup        arena_free Test arena_free behavior.
     * @{
     */

    RUN_TEST(check_arena_free_resets_offset);

    /*!
     * @}
     */

    return UNITY_END();
}
