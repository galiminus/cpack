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
