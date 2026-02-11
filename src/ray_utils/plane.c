#include "librt.h"
#include "ray.h"
#include "vector.h"
#include <math.h>

t_plane plane(void)
{
    t_plane     plane;

    plane.shape.id = get_shape_id();
    plane.shape.type = SHAPE_PLANE;
    return (plane);
}

t_vec3  local_normal_at_plane(void)
{
    return (
        vector_constructor(0, 1, 0)
    );
}

t_intersect local_intersect_plane(t_plane *plane, t_ray ray)
{
    t_intersect this;
    float       t;

    this.count = 0;
    if (fabsf(ray.direction.y) < EPSILON)
        return (this);
    t = -ray.origin.y / ray.direction.y;
    this.i[this.count++] = intersection(t, (t_object) {.pl = *plane});
    return (this);
}