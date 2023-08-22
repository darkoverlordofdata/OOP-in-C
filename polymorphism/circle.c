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
#include "circle.h"  /* Circle class interface */
#include "corefw/string.h"
#include <stdio.h> /* for printf() */
#include <stdlib.h>

/* NOTE: the "this" pointer has the type of the superclass to fit the vtable */
static uint32_t Circle_area(Shape const * const ptr);
static void Circle_draw(Shape const * const ptr);


/* Circle's class implementations of its virtual functions... */
static uint32_t Circle_area(Shape const * const ptr) {
    Circle const * const this = (Circle const *)ptr; /* explicit downcast */
    /* pi is approximated as 3 */
    return 3U * (uint32_t)this->rad * (uint32_t)this->rad;
}

static void Circle_draw(Shape const * const ptr) {
    Circle const * const this = (Circle const *)ptr; /* explicit downcast */
    printf("Circle_draw_(x=%d,y=%d,rad=%d)\n",
           Shape_getX(ptr), Shape_getY(ptr), this->rad);
}

/* constructor */
static bool ctor(void *ptr, va_list args)
{
    static struct ShapeVtbl const vtbl = {  /* vtbl of the Circle class */
        &Circle_area,
        &Circle_draw
    };

    Circle *this = ptr;

    cfw_shape->ctor(&this->super, args);    /* call the superclass' ctor */
    this->rad = va_arg(args, intmax_t);     /* and set the radius */
    this->super.vptr = &vtbl;               /* override the vptr */

	return true;
}

static bool equal(void *ptr1, void *ptr2)
{
	CFWObject *obj2 = ptr2;
	Circle *circle1, *circle2;

	if (obj2->cls != cfw_shape)
		return false;

	circle1 = ptr1;
	circle2 = ptr2;

	return (circle1->super.x == circle2->super.x)
        && (circle1->super.y == circle2->super.y)
        && (circle1->rad == circle2->rad);
}

static uint32_t hash(void *ptr)
{
	Circle *circle = ptr;

	return *(uint32_t*)circle;
}

static void* copy(void *ptr)
{
	return cfw_ref(ptr);
}

static CFWString* toString(void *ptr) 
{
    Circle *this = ptr; 
    const char* mask = "\t%s\n\tCircle x:%d y:%d rad:%d\n";

    CFWString *s = cfw_shape->toString(ptr);
	int len = snprintf(NULL, 0, "\t%s\n\tCircle x:%d y:%d rad:%d\n", cfw_string_c(s), this->super.x, this->super.y, this->rad);
    char* buffer = calloc(1, len+2);
	snprintf(buffer, len+1, "\t%s\n\tCircle x:%d y:%d rad:%d\n", cfw_string_c(s), this->super.x, this->super.y, this->rad);
    return cfw_create(cfw_string, buffer);
}


static CFWClass class = {
	.name = "Circle",
	.size = sizeof(Circle),
	.ctor = ctor,
	.equal = equal,
	.hash = hash,
	.copy = copy,
    .toString = toString
};
CFWClass *cfw_circle = &class;


