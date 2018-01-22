struct rect_tag
{
    float left;
    float bottom;
    float top;
    float right;
};
typedef struct rect_tag rect_t;

rect_t intersection(rect_t r1, rect_t r2); 