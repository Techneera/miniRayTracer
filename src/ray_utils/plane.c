#include "ray.h"
#include "vector.h"

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