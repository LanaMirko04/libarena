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

#define ERR -1
#define OK 0

typedef struct Point {
    float x, y;
} Point_t;

int main(void) {
    struct ArenaHandler arena;

    int ret = arena_init(&arena, 0x400U);
    if (ret == ERR)
        return ERR;

    Point_t *point_ptr = arena_alloc(&arena, sizeof(Point_t));
    if (point_ptr == NULL)
        return ERR;

    *point_ptr = (Point_t){.x = 0.5, .y = 1.2};

    printf("Point(x=%.2f,y=%.2f)\tAddress=%p\n",
                point_ptr->x,
                point_ptr->y,
                point_ptr);

    arena_free(&arena);
    return OK;
}
```

## API Reference
Full API reference and docs are in the [API.md](docs/API.md) file.

## License
[MIT](LICENSE) License.
