#include "librt.h"
#include "ray.h"
#include "vector.h"
#include <math.h>

t_plane plane(void)
{
    t_plane     plane;

    plane.shape.id = get_shape_id();
    plane.shape.type = SHAPE_PLANE;
	matrix_identity(&plane.shape.transform);
	matrix_identity(&plane.shape.transform_inv);
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

    this.count = 0;
    if (fabsf(ray.direction.y) < EPSILON)
        return (this);
    this.i[this.count].t = -ray.origin.y / ray.direction.y;
    this.i[this.count++] = intersection(this.i[0].t, (t_object) {.pl = *plane});
    return (this);
}
