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
#include "rect.h"  /* Rectangle class interface */
#include <stdio.h> /* for printf() */
#include <stdlib.h>

/* Rectangle's prototypes of its virtual functions */
/* NOTE: the "this" pointer has the type of the superclass to fit the vtable */
static uint32_t Rectangle_area(Shape const * const ptr);
static void Rectangle_draw(Shape const * const ptr);


/* Rectangle's class implementations of its virtual functions... */
static uint32_t Rectangle_area(Shape const * const ptr) {
    Rectangle const * const this = (Rectangle const *)ptr; /* explicit downcast */
    return (uint32_t)this->width * (uint32_t)this->height;
}

static void Rectangle_draw(Shape const * const ptr) {
    Rectangle const * const this = (Rectangle const *)ptr; /* explicit downcast */
    printf("Rectangle_draw_(x=%d,y=%d,width=%d,height=%d)\n",
           Shape_getX(ptr), Shape_getY(ptr), this->width, this->height);
}

/* constructor */
static bool ctor(void *ptr, va_list args)
{

    static struct ShapeVtbl const vtbl = { /* vtbl of the Circle class */
        &Rectangle_area,
        &Rectangle_draw

    };

    Rectangle *this = ptr;

    cfw_shape->ctor(&this->super, args);    /* call the superclass' ctor */
    this->super.vptr = &vtbl;               /* override the vptr */
    this->width = va_arg(args, intmax_t);   /* and set the width */
    this->height = va_arg(args, intmax_t);  /* and set the height */

	return true;
}

static bool equal(void *ptr1, void *ptr2)
{
	CFWObject *obj2 = ptr2;
	Rectangle *rect1, *rect2;

	if (obj2->cls != cfw_shape)
		return false;

	rect1 = ptr1;
	rect2 = ptr2;

	return (rect1->super.x == rect2->super.x)
        && (rect1->super.y == rect2->super.y)
        && (rect1->width == rect2->width)
        && (rect1->width == rect2->height);
}

static uint32_t hash(void *ptr)
{
	Rectangle *rect = ptr;

	return *(uint32_t*)rect;
}

static void* copy(void *ptr)
{
	return cfw_ref(ptr);
}

static CFWString* toString(void *ptr) 
{
    Rectangle *this = ptr; 
    const char* mask = "\t%s\n\tRectangle x:%d y:%d width:%d height:%d\n";

    CFWString *s = cfw_shape->toString(ptr);
    int len = snprintf(NULL, 0, mask, cfw_string_c(s), this->super.x, this->super.y, this->width, this->height);
    char* buffer = calloc(1, len+2);
	snprintf(buffer, len+1, "\t%s\n\tRectangle x:%d y:%d width:%d height:%d\n", cfw_string_c(s), this->super.x, this->super.y, this->width, this->height);
    return cfw_create(cfw_string, buffer);

}

static CFWClass class = {
	.name = "CFWRectangle",
	.size = sizeof(Rectangle),
	.ctor = ctor,
	.equal = equal,
	.hash = hash,
	.copy = copy,
    .toString = toString
};
CFWClass *cfw_rectangle = &class;


