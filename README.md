cpack
=====

C library to ease the passing of multiple arguments to callback functions.

# Usage

## Packing and unpacking
```C
char * packed_string;

packed_string = pack ("ddp", 42, 0, "Hello World!");

```

```C
char * my_string;
int a, b;

unpack (packed_string, "ddp", &a, &b, &my_string);
printf ("%d %d %s\n", a, b, my_string); // will output "42 0 Hello World!"
```

## Map packed data into structures
```C
struct my_struct {
  char * my_string;
  int    a;
  int    b;
};

struct my_struct test = *(struct my_struct *)(packed_string);
```

You can use the MAPPACK macro to do it in one single line:
```C
MAPPACK(my_struct, {char * my_string; int a; int b;}, pack);
printf("%s %d %d\n", my_struct.my_string, my_struct.a, my_struct.b);
```
