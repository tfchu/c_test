#include <stdio.h>
#include "c_practice.h"

float min(float f1, float f2)
{
    // compare f1 to f2
    if (f1 < f2)
    {
        // if f1 is smaller than f2, then f1 is your answer
        return f1;
    }
    else
    {
        // otherwise, f2 is your answer
        return f2;
    }
}

float max(float f1, float f2)
{
    // compare f1 to f2
    if (f1 > f2)
    {
        // if f1 is larger than f2, then f1 is your answer
        return f1;
    }
    else
    {
        // otherwise, f2 is your answer
        return f2;
    }
}

// To find the intersection of two rectangles, r1 and r2:
rect_t intersection(rect_t r1, rect_t r2)
{
    // Make a rectangle (called ans) with
    rect_t ans;
    // left: maximum of r1's left and r2's left
    ans.left = max(r1.left, r2.left);
    // bottom: maximum or r1's bottom and r2's bottom
    ans.bottom = max(r1.bottom, r2.bottom);
    // right: minimum of r1's right and r2's right
    ans.right = min(r1.right, r2.right);
    // top: minimum of r1's top and r2's top
    ans.top = min(r1.top, r2.top);
    // The rectangle called ans is your answer
    return ans;
}