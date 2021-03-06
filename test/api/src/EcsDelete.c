/* This is a managed file. Do not delete this comment. */

#include <include/test.h>

typedef struct Foo {
    int x;
} Foo;

void test_EcsDelete_tc_delete_1st_of_3(
    test_EcsDelete this)
{
    EcsWorld *world = ecs_init();
    ECS_COMPONENT(world, Foo);

    EcsEntity e1 = ecs_new(world, Foo_h);
    EcsEntity e2 = ecs_new(world, Foo_h);
    EcsEntity e3 = ecs_new(world, Foo_h);

    test_assert(e1 != 0);
    test_assert(e2 != 0);
    test_assert(e3 != 0);

    *(int*)ecs_get_ptr(world, e1, Foo_h) = 10;
    *(int*)ecs_get_ptr(world, e2, Foo_h) = 20;
    *(int*)ecs_get_ptr(world, e3, Foo_h) = 30;

    ecs_delete(world, e1);

    test_assert(ecs_empty(world, e1) == false);
    test_assert(ecs_empty(world, e2) == true);
    test_assert(ecs_empty(world, e3) == true);

    test_assert(ecs_get_ptr(world, e1, Foo_h) == NULL);
    test_assert(ecs_get_ptr(world, e2, Foo_h) != NULL);
    test_assert(ecs_get_ptr(world, e3, Foo_h) != NULL);

    test_assertint(*(int*)ecs_get_ptr(world, e2, Foo_h), 20);
    test_assertint(*(int*)ecs_get_ptr(world, e3, Foo_h), 30);

    ecs_fini(world);
}

void test_EcsDelete_tc_delete_2nd_of_3(
    test_EcsDelete this)
{
    EcsWorld *world = ecs_init();
    ECS_COMPONENT(world, Foo);

    EcsEntity e1 = ecs_new(world, Foo_h);
    EcsEntity e2 = ecs_new(world, Foo_h);
    EcsEntity e3 = ecs_new(world, Foo_h);

    test_assert(e1 != 0);
    test_assert(e2 != 0);
    test_assert(e3 != 0);

    *(int*)ecs_get_ptr(world, e1, Foo_h) = 10;
    *(int*)ecs_get_ptr(world, e2, Foo_h) = 20;
    *(int*)ecs_get_ptr(world, e3, Foo_h) = 30;

    ecs_delete(world, e2);

    test_assert(ecs_empty(world, e1) == true);
    test_assert(ecs_empty(world, e2) == false);
    test_assert(ecs_empty(world, e3) == true);

    test_assert(ecs_get_ptr(world, e1, Foo_h) != NULL);
    test_assert(ecs_get_ptr(world, e2, Foo_h) == NULL);
    test_assert(ecs_get_ptr(world, e3, Foo_h) != NULL);

    test_assertint(*(int*)ecs_get_ptr(world, e1, Foo_h), 10);
    test_assertint(*(int*)ecs_get_ptr(world, e3, Foo_h), 30);

    ecs_fini(world);
}

void test_EcsDelete_tc_delete_3rd_of_3(
    test_EcsDelete this)
{
    EcsWorld *world = ecs_init();
    ECS_COMPONENT(world, Foo);

    EcsEntity e1 = ecs_new(world, Foo_h);
    EcsEntity e2 = ecs_new(world, Foo_h);
    EcsEntity e3 = ecs_new(world, Foo_h);

    test_assert(e1 != 0);
    test_assert(e2 != 0);
    test_assert(e3 != 0);

    *(int*)ecs_get_ptr(world, e1, Foo_h) = 10;
    *(int*)ecs_get_ptr(world, e2, Foo_h) = 20;
    *(int*)ecs_get_ptr(world, e3, Foo_h) = 30;

    ecs_delete(world, e3);

    test_assert(ecs_empty(world, e1) == true);
    test_assert(ecs_empty(world, e2) == true);
    test_assert(ecs_empty(world, e3) == false);

    test_assert(ecs_get_ptr(world, e1, Foo_h) != NULL);
    test_assert(ecs_get_ptr(world, e2, Foo_h) != NULL);
    test_assert(ecs_get_ptr(world, e3, Foo_h) == NULL);

    test_assertint(*(int*)ecs_get_ptr(world, e1, Foo_h), 10);
    test_assertint(*(int*)ecs_get_ptr(world, e2, Foo_h), 20);

    ecs_fini(world);
}

void test_EcsDelete_tc_delete_2_of_3(
    test_EcsDelete this)
{
    EcsWorld *world = ecs_init();
    ECS_COMPONENT(world, Foo);

    EcsEntity e1 = ecs_new(world, Foo_h);
    EcsEntity e2 = ecs_new(world, Foo_h);
    EcsEntity e3 = ecs_new(world, Foo_h);

    test_assert(e1 != 0);
    test_assert(e2 != 0);
    test_assert(e3 != 0);

    *(int*)ecs_get_ptr(world, e1, Foo_h) = 10;
    *(int*)ecs_get_ptr(world, e2, Foo_h) = 20;
    *(int*)ecs_get_ptr(world, e3, Foo_h) = 30;

    ecs_delete(world, e1);
    ecs_delete(world, e2);

    test_assert(ecs_empty(world, e1) == false);
    test_assert(ecs_empty(world, e2) == false);
    test_assert(ecs_empty(world, e3) == true);

    test_assert(ecs_get_ptr(world, e1, Foo_h) == NULL);
    test_assert(ecs_get_ptr(world, e2, Foo_h) == NULL);
    test_assert(ecs_get_ptr(world, e3, Foo_h) != NULL);

    test_assertint(*(int*)ecs_get_ptr(world, e3, Foo_h), 30);

    ecs_fini(world);
}

void test_EcsDelete_tc_delete_3_of_3(
    test_EcsDelete this)
{
    EcsWorld *world = ecs_init();
    ECS_COMPONENT(world, Foo);

    EcsEntity e1 = ecs_new(world, Foo_h);
    EcsEntity e2 = ecs_new(world, Foo_h);
    EcsEntity e3 = ecs_new(world, Foo_h);

    test_assert(e1 != 0);
    test_assert(e2 != 0);
    test_assert(e3 != 0);

    *(int*)ecs_get_ptr(world, e1, Foo_h) = 10;
    *(int*)ecs_get_ptr(world, e2, Foo_h) = 20;
    *(int*)ecs_get_ptr(world, e3, Foo_h) = 30;

    ecs_delete(world, e1);
    ecs_delete(world, e2);
    ecs_delete(world, e3);

    test_assert(ecs_empty(world, e1) == false);
    test_assert(ecs_empty(world, e2) == false);
    test_assert(ecs_empty(world, e3) == false);

    test_assert(ecs_get_ptr(world, e1, Foo_h) == NULL);
    test_assert(ecs_get_ptr(world, e2, Foo_h) == NULL);
    test_assert(ecs_get_ptr(world, e3, Foo_h) == NULL);

    ecs_fini(world);
}

typedef struct Context {
    EcsEntity entity;
    uint32_t count;
} Context;

static
void DeleteNext(EcsRows *rows) {
    Context *ctx = ecs_get_context(rows->world);
    void *row;
    for (row = rows->first; row < rows->last; row = ecs_next(rows, row)) {
        (*(int*)ecs_data(rows, row, 0)) ++;
        if (ecs_entity(rows, row, ECS_ROW_ENTITY) - 1 == ctx->entity) {
            ecs_delete(rows->world, ctx->entity);
        }

        ctx->count ++;
    }
}

static
void DeletePrev(EcsRows *rows) {
    Context *ctx = ecs_get_context(rows->world);
    void *row;
    for (row = rows->first; row < rows->last; row = ecs_next(rows, row)) {
        (*(int*)ecs_data(rows, row, 0)) ++;
        if (ecs_entity(rows, row, ECS_ROW_ENTITY) + 1 == ctx->entity) {
            ecs_delete(rows->world, ctx->entity);
        }

        ctx->count ++;
    }
}

static
void DeleteCurrent(EcsRows *rows) {
    Context *ctx = ecs_get_context(rows->world);
    void *row;
    for (row = rows->first; row < rows->last; row = ecs_next(rows, row)) {
        (*(int*)ecs_data(rows, row, 0)) ++;
        if (ecs_entity(rows, row, ECS_ROW_ENTITY) == ctx->entity) {
            ecs_delete(rows->world, ctx->entity);
        }

        ctx->count ++;
    }
}

static
void DeleteAll(EcsRows *rows) {
    Context *ctx = ecs_get_context(rows->world);
    void *row;
    for (row = rows->first; row < rows->last; row = ecs_next(rows, row)) {
        ecs_delete(rows->world, ecs_entity(rows, row, ECS_ROW_ENTITY));
        (*(int*)ecs_data(rows, row, 0)) ++;
        ctx->count ++;
    }
}

void test_EcsDelete_tc_delete_cur_in_progress(
    test_EcsDelete this)
{
    EcsWorld *world = ecs_init();
    ECS_COMPONENT(world, Foo);
    ECS_SYSTEM(world, DeleteCurrent, EcsOnFrame, Foo);

    EcsEntity e1 = ecs_new(world, Foo_h);
    EcsEntity e2 = ecs_new(world, Foo_h);
    EcsEntity e3 = ecs_new(world, Foo_h);

    test_assert(e1 != 0);
    test_assert(e2 != 0);
    test_assert(e3 != 0);

    *(int*)ecs_get_ptr(world, e1, Foo_h) = 10;
    *(int*)ecs_get_ptr(world, e2, Foo_h) = 20;
    *(int*)ecs_get_ptr(world, e3, Foo_h) = 30;

    Context ctx = {.entity = e2};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 0);

    test_assertint(ctx.count, 3);

    test_assert(ecs_empty(world, e1) == true);
    test_assert(ecs_empty(world, e2) == false);
    test_assert(ecs_empty(world, e3) == true);

    test_assert(ecs_get_ptr(world, e1, Foo_h) != NULL);
    test_assert(ecs_get_ptr(world, e2, Foo_h) == NULL);
    test_assert(ecs_get_ptr(world, e3, Foo_h) != NULL);

    test_assertint(*(int*)ecs_get_ptr(world, e1, Foo_h), 11);
    test_assertint(*(int*)ecs_get_ptr(world, e3, Foo_h), 31);

    ecs_fini(world);
}

void test_EcsDelete_tc_delete_next_in_progress(
    test_EcsDelete this)
{
    EcsWorld *world = ecs_init();
    ECS_COMPONENT(world, Foo);
    ECS_SYSTEM(world, DeleteNext, EcsOnFrame, Foo);

    EcsEntity e1 = ecs_new(world, Foo_h);
    EcsEntity e2 = ecs_new(world, Foo_h);
    EcsEntity e3 = ecs_new(world, Foo_h);

    test_assert(e1 != 0);
    test_assert(e2 != 0);
    test_assert(e3 != 0);

    *(int*)ecs_get_ptr(world, e1, Foo_h) = 10;
    *(int*)ecs_get_ptr(world, e2, Foo_h) = 20;
    *(int*)ecs_get_ptr(world, e3, Foo_h) = 30;

    Context ctx = {.entity = e2};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 0);

    test_assertint(ctx.count, 3);

    test_assert(ecs_empty(world, e1) == true);
    test_assert(ecs_empty(world, e2) == false);
    test_assert(ecs_empty(world, e3) == true);

    test_assert(ecs_get_ptr(world, e1, Foo_h) != NULL);
    test_assert(ecs_get_ptr(world, e2, Foo_h) == NULL);
    test_assert(ecs_get_ptr(world, e3, Foo_h) != NULL);

    test_assertint(*(int*)ecs_get_ptr(world, e1, Foo_h), 11);
    test_assertint(*(int*)ecs_get_ptr(world, e3, Foo_h), 31);

    ecs_fini(world);
}

void test_EcsDelete_tc_delete_prev_in_progress(
    test_EcsDelete this)
{
    EcsWorld *world = ecs_init();
    ECS_COMPONENT(world, Foo);
    ECS_SYSTEM(world, DeletePrev, EcsOnFrame, Foo);

    EcsEntity e1 = ecs_new(world, Foo_h);
    EcsEntity e2 = ecs_new(world, Foo_h);
    EcsEntity e3 = ecs_new(world, Foo_h);

    test_assert(e1 != 0);
    test_assert(e2 != 0);
    test_assert(e3 != 0);

    *(int*)ecs_get_ptr(world, e1, Foo_h) = 10;
    *(int*)ecs_get_ptr(world, e2, Foo_h) = 20;
    *(int*)ecs_get_ptr(world, e3, Foo_h) = 30;

    Context ctx = {.entity = e2};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 0);

    test_assertint(ctx.count, 3);

    test_assert(ecs_empty(world, e1) == true);
    test_assert(ecs_empty(world, e2) == false);
    test_assert(ecs_empty(world, e3) == true);

    test_assert(ecs_get_ptr(world, e1, Foo_h) != NULL);
    test_assert(ecs_get_ptr(world, e2, Foo_h) == NULL);
    test_assert(ecs_get_ptr(world, e3, Foo_h) != NULL);

    test_assertint(*(int*)ecs_get_ptr(world, e1, Foo_h), 11);
    test_assertint(*(int*)ecs_get_ptr(world, e3, Foo_h), 31);

    ecs_fini(world);
}

void test_EcsDelete_tc_delete_all_in_progress(
    test_EcsDelete this)
{
    EcsWorld *world = ecs_init();
    ECS_COMPONENT(world, Foo);
    ECS_SYSTEM(world, DeleteAll, EcsOnFrame, Foo);

    EcsEntity e1 = ecs_new(world, Foo_h);
    EcsEntity e2 = ecs_new(world, Foo_h);
    EcsEntity e3 = ecs_new(world, Foo_h);

    test_assert(e1 != 0);
    test_assert(e2 != 0);
    test_assert(e3 != 0);

    *(int*)ecs_get_ptr(world, e1, Foo_h) = 10;
    *(int*)ecs_get_ptr(world, e2, Foo_h) = 20;
    *(int*)ecs_get_ptr(world, e3, Foo_h) = 30;

    Context ctx = {.count = 0};
    ecs_set_context(world, &ctx);

    ecs_progress(world, 0);

    test_assertint(ctx.count, 3);

    test_assert(ecs_empty(world, e1) == false);
    test_assert(ecs_empty(world, e2) == false);
    test_assert(ecs_empty(world, e3) == false);

    test_assert(ecs_get_ptr(world, e1, Foo_h) == NULL);
    test_assert(ecs_get_ptr(world, e2, Foo_h) == NULL);
    test_assert(ecs_get_ptr(world, e3, Foo_h) == NULL);

    ecs_fini(world);
}
