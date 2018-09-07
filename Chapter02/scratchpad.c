//
// Copyright (C) 2018 Rian Quinn <rianquinn@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// -----------------------------------------------------------------------------
// Section: Stream Based IO
// -----------------------------------------------------------------------------

#if SNIPPET01

#include <stdio.h>

int main(void)
{
    printf("Hello World\n");
}

// > gcc scratchpad.c; ./a.out
// Hello World

#endif

#if SNIPPET02

int test(void)
{
    return 0;
}

int main(void)
{
    return test();
}

// > gcc scratchpad.c; ./a.out

#endif

#if SNIPPET03

int test(void)
{
    return 0;
}

int main(void)
{
    return test();
}

// > gcc scratchpad.c; ./a.out

#endif

#if SNIPPET04

int main(void)
{
    int i;
    int *p = &i;
}

// > gcc scratchpad.c; ./a.out

#endif

#if SNIPPET05

int main(void)
{
    int i;
    void *p = &i;

    int *int_p = p;
    float *float_p = p;
}

// > gcc scratchpad.c; ./a.out

#endif

#if SNIPPET06

#include <stdio.h>

int main(void)
{
    int i = 42;
    int *p = &i;

    if (p) {
        printf("The answer is: %d\n", *p);
    }
}

// > gcc scratchpad.c; ./a.out
// The answer is: 42

#endif

#if SNIPPET07

#include <stdio.h>

int main(void)
{
    int i[2] = {42, 43};
    int *p = i;

    if (p) {
        printf("The answer is: %d and %d\n", i[0], *(p + 0));
        printf("The answer is: %d and %d\n", i[1], *(p + 1));
    }
}

// > gcc scratchpad.c; ./a.out
// The answer is: 42 and 42
// The answer is: 43 and 43

#endif
