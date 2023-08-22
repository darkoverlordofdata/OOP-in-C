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
#ifndef SHAPE_H
#define SHAPE_H

#include <stdint.h>
#include <stdio.h>
#include <corefw/corefw.h>

extern CFWClass *cfw_shape;

/* Shape's attributes... */
struct ShapeVtbl; /* forward declaration */
typedef struct {
    CFWObject obj;
    struct ShapeVtbl const *vptr; /* <== Shape's Virtual Pointer */
    int16_t x; /* x-coordinate of Shape's position */
    int16_t y; /* y-coordinate of Shape's position */
} Shape;

/* Shape's virtual table */
struct ShapeVtbl {
    uint32_t (*area)(Shape const * const this);
    void (*draw)(Shape const * const this);
};

/* Shape's operations (Shape's interface)... */
void Shape_moveBy(Shape * const this, int16_t dx, int16_t dy);
int16_t Shape_getX(Shape const * const this);
int16_t Shape_getY(Shape const * const this);

static inline uint32_t Shape_area(Shape * const this) {
    return (*this->vptr->area)(this);
}

static inline void Shape_draw(Shape * const this) {
    (*this->vptr->draw)(this);
}

/* generic operations on collections of Shapes */
Shape const *largestShape(CFWArray *shapes);
void drawAllShapes(CFWArray *shapes);


#endif /* SHAPE_H */
