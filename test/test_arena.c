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

struct ArenaHandler arena;

void setUp(void) {
    arena_init(&arena);
}
void tearDown(void) {
    arena_free(&arena);
}

/*!
 * \defgroup        arena_init Test module initialization.
 * @{
 */

void check_arena_init_with_null_handler(void) {
    int ret = arena_init(NULL);
    TEST_ASSERT_EQUAL_INT(ARENA_RC_INVALID_ARG, ret);
}

void check_arena_init(void) {
    int ret = arena_init(&arena);
    TEST_ASSERT_EQUAL_INT_MESSAGE(ARENA_RC_OK, ret, "arena_init failed");
    TEST_ASSERT_NULL_MESSAGE(arena.buffer, "arena buffer is not NULL after init");
    TEST_ASSERT_EQUAL_UINT_MESSAGE(0U, arena.capacity, "arena capacity is not zero after init");
    TEST_ASSERT_EQUAL_UINT_MESSAGE(0U, arena.offset, "arena offset is not zero after init");
}

/*!
 * @}
 */

/*!
 * \defgroup        arena_alloc Test arena_alloc behavior.
 * @{
 */

void check_arena_alloc_returns_non_null_and_zeroed(void) {
    struct ArenaObj obj;
    enum ArenaReturnCode res = arena_alloc(&arena, sizeof(uint8_t), &obj);
    TEST_ASSERT_EQUAL_INT_MESSAGE(ARENA_RC_OK, res, "arena_alloc failed");

    uint8_t *data = arena_get_ptr(&obj);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0U, *data, "allocated memory is not zeroed");
}

void check_arena_alloc_sequential_allocations_do_not_overlap(void) {
    struct ArenaObj obj1, obj2;
    enum ArenaReturnCode res1 = arena_alloc(&arena, 16, &obj1);
    enum ArenaReturnCode res2 = arena_alloc(&arena, 32, &obj2);
    TEST_ASSERT_EQUAL_INT_MESSAGE(ARENA_RC_OK, res1, "first arena_alloc failed");
    TEST_ASSERT_EQUAL_INT_MESSAGE(ARENA_RC_OK, res2, "second arena_alloc failed");

    uint8_t *ptr1 = arena_get_ptr(&obj1);
    uint8_t *ptr2 = arena_get_ptr(&obj2);
    TEST_ASSERT_TRUE_MESSAGE(ptr2 > ptr1, "second allocation overlaps first");
    TEST_ASSERT_TRUE_MESSAGE((uintptr_t)ptr2 >= (uintptr_t)(ptr1 + 16), "second allocation overlaps first");
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
    struct ArenaObj obj;
    enum ArenaReturnCode res = arena_alloc_align(&arena, 24, align, &obj);
    TEST_ASSERT_EQUAL_INT_MESSAGE(ARENA_RC_OK, res, "arena_alloc_align failed");

    void *ptr = arena_get_ptr(&obj);
    TEST_ASSERT_EQUAL_UINT(0, ((uintptr_t)ptr) % align);
}

void check_arena_alloc_align_multiple_allocations_alignment(void) {
    size_t align = 8;
    struct ArenaObj obj1, obj2;
    enum ArenaReturnCode res1 = arena_alloc_align(&arena, 10, align, &obj1);
    enum ArenaReturnCode res2 = arena_alloc_align(&arena, 20, align, &obj2);

    TEST_ASSERT_EQUAL_INT_MESSAGE(ARENA_RC_OK, res1, "first arena_alloc failed");
    TEST_ASSERT_EQUAL_INT_MESSAGE(ARENA_RC_OK, res2, "second arena_alloc failed");

    void *ptr1 = arena_get_ptr(&obj1);
    void *ptr2 = arena_get_ptr(&obj2);

    TEST_ASSERT_TRUE(ptr2 > ptr1);
    TEST_ASSERT_EQUAL_UINT(0, ((uintptr_t)ptr1) % align);
    TEST_ASSERT_EQUAL_UINT(0, ((uintptr_t)ptr2) % align);
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
    struct ArenaObj obj;

    enum ArenaReturnCode res = arena_calloc(&arena, size, count, &obj);
    TEST_ASSERT_EQUAL_INT_MESSAGE(ARENA_RC_OK, res, "arena_calloc failed");

    int *arr = (int *)arena_get_ptr(&obj);
    for (size_t i = 0; i < count; i++) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(0, arr[i], "allocated memory is not zeroed");
    }
}

/*!
 * @}
 */

/*!
 * \defgroup        arena_clear Test arena_clear behavior.
 * @{
 */

void check_arena_clear(void) {
    struct ArenaObj obj;
    enum ArenaReturnCode res = arena_alloc(&arena, 64, &obj);
    TEST_ASSERT_EQUAL_INT_MESSAGE(ARENA_RC_OK, res, "arena_alloc failed");

    arena_clear(&arena);
    TEST_ASSERT_NOT_NULL_MESSAGE(arena.buffer, "arena buffer is NULL after arena_clear");
    TEST_ASSERT_EQUAL_UINT_MESSAGE(0U, arena.offset, "arena offset not reset after arena_free");
}

/*!
 * @}
 */

/*!
  * \brief           arena_free test suite main function.
  */

void check_arena_free(void) {
    struct ArenaObj obj;
    enum ArenaReturnCode res = arena_alloc(&arena, 128, &obj);
    TEST_ASSERT_EQUAL_INT_MESSAGE(ARENA_RC_OK, res, "arena_alloc failed");

    arena_free(&arena);
    TEST_ASSERT_NULL_MESSAGE(arena.buffer, "arena buffer not NULL after arena_free");
    TEST_ASSERT_EQUAL_UINT_MESSAGE(0U, arena.offset, "arena offset not reset after arena_free");
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
     * \defgroup        arena_clear Test arena_free behavior.
     * @{
     */

    RUN_TEST(check_arena_clear);

    /*!
     * @}
     */

    /*!
     * \defgroup        arena_clear Test arena_free behavior.
     * @{
     */

    RUN_TEST(check_arena_free);

    /*!
     * @}
     */
    return UNITY_END();
}
