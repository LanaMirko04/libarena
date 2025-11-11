# Arena
**Arena** is a lightweight C static library for fast, linear memory allocation.

## Installation

```sh
$ git clone https://github.com/LanaMirko04/libarena.git && cd libarena
$ make                  # Build the library
$ make test             # Build and run unit tests
$ sudo make install     # Install library and headers to /usr/local
```

Alternatively, you can simply copy `src` and `include` files directly into your project.

To clean build artifacts:

```sh
$ make clean
```

To uninstall:

```sh
$ sudo make uninstall
```

## Usage
Quick example to get started:

```c
#include <arena/arena.h>
#include <stdio.h>
#include <stdlib.h>

struct Point {
    float x, y;
};

int main(void) {
    struct ArenaHandler arena;
    struct ArenaObj obj;

    arena_init(&arena);
    enum ArenaReturnCode res = arena_alloc(&arena, sizeof(struct Point), &obj);
    if (res != ARENA_RC_OK)
        return EXIT_FAILURE;

    struct Point *point_ptr = (struct Point *)arena_get_ptr(&obj);
    *point_ptr = (struct Point){.x = 0.5, .y = 1.2};

    printf("Point(x=%.2f,y=%.2f)\tAddress=%p\n",
                point_ptr->x,
                point_ptr->y,
                point_ptr);

    arena_free(&arena);
    return EXIT_SUCCESS;
}
```

## API Reference
Full API reference and docs are in the [api.md](api.md) file.

## License
[MIT](LICENSE) License.
