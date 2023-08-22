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
#include "shape.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/* move-by operation */
void Shape_moveBy(Shape * const this, int16_t dx, int16_t dy) {
    this->x += dx;
    this->y += dy;
}


/* "getter" operations implementation */
int16_t Shape_getX(Shape const * const this) {
    return this->x;
}
int16_t Shape_getY(Shape const * const this) {
    return this->y;
}


/* the following code finds the largest-area shape in the collection */
Shape const *largestShape(CFWArray *shapes) {
    Shape const *s = NULL;//(Shape *)0;

    for (int i = 0, max=0; i < cfw_array_size(shapes); ++i) {
        int area = Shape_area(cfw_array_get(shapes, i)); /* virtual call */
        if (area > max) {
            max = area;
            s = cfw_array_get(shapes, i);
        }
    }
    return s; /* the largest shape in the array shapes[] */
}

/* The following code will draw all Shapes on the screen */
void drawAllShapes(CFWArray *shapes) {
    for (int i = 0; i < cfw_array_size(shapes); ++i) {
        Shape_draw(cfw_array_get(shapes, i)); /* virtual call */
    }
}

/**
 * Shape *s = cfw_create(cfw_shape, 10, 10);
 */
static bool ctor(void *ptr, va_list args)
{
	Shape *this = ptr;

    static struct ShapeVtbl const vtbl = { 0 };
    this->vptr = &vtbl;        /* "hook" the vptr to the vtbl */
	this->x = va_arg(args, intmax_t);
	this->y = va_arg(args, intmax_t);

	return true;
}

static bool equal(void *ptr1, void *ptr2)
{
	CFWObject *obj2 = ptr2;
	Shape *shape1, *shape2;

	if (obj2->cls != cfw_shape)
		return false;

	shape1 = ptr1;
	shape2 = ptr2;

	return (shape1->x == shape2->x)
        && (shape1->y == shape2->y);
}

static uint32_t hash(void *ptr)
{
	Shape *this = ptr;

	return *(uint32_t*)this;
}

static void* copy(void *ptr)
{
	return cfw_ref(ptr);
}

static CFWString* toString(void *ptr) 
{
    char* mask = "Shape x:%d y:%d";

    Shape *this = ptr;
    int len = snprintf(NULL, 0, mask, this->x, this->y);
    char* s = calloc(1, len+2);
    if (s == NULL) return NULL;
	snprintf(s, len+1, mask, this->x, this->y);
    CFWString *str = cfw_create(cfw_string, s);
    free(s);
    return str;

}

static CFWClass class = {
	.name = "Shape",
	.size = sizeof(Shape),
	.ctor = ctor,
	.equal = equal,
	.hash = hash,
	.copy = copy,
    .toString = toString
};
CFWClass *cfw_shape = &class;


