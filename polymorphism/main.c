/*============================================================================
* Code accompanying the Article:
* "Object-Oriented Programming in C"
* https://github.com/QuantumLeaps/OOP-in-C
*
* Copyright (C) 2006-2023 Quantum Leaps, <state-machine.com>.
*
* SPDX-License-Identifier: MIT
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
============================================================================*/
#include "rect.h"   /* Rectangle class interface */
#include "circle.h" /* Circle class interface */
#include <stdio.h>  /* for printf() */

int main() {

	CFWRefPool *pool = cfw_new(cfw_refpool);

	CFWArray *shapes = cfw_create(cfw_array,
        cfw_create(cfw_rectangle, 0, 2, 10, 15),
        cfw_create(cfw_rectangle, -1, 3, 5, 8),
        cfw_create(cfw_circle, 1, -2, 12),
        cfw_create(cfw_circle, 1, -3, 6),
        NULL);

    Shape const *s = largestShape(shapes);

    printf("largestShape s(x=%d,y=%d)\n",
           Shape_getX(s), Shape_getY(s));

    drawAllShapes(shapes);

    for (int i = 0; i < cfw_array_size(shapes); i++) {
        
        CFWString *s = cfw_toString(cfw_array_get(shapes, i));
        printf("%s\n", cfw_string_c(s));
    }

	cfw_unref(pool);
    return 0;
}
