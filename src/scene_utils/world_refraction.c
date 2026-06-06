#include "librt.h"
#include "refraction.h"
#include "scene.h"
#include "libft.h"

void	set_refractive_indices(t_computation *comps, t_intersection hit,
		t_intersect *xs)
{
	const t_object	*conts[MAX_CONTAINERS];
	int				cont_count;
	int				i;

	ft_bzero((void *)conts, sizeof(conts));
	cont_count = 0;
	i = 0;
	while (i < xs->count)
	{
		if (xs->i[i].t == hit.t && xs->i[i].object == hit.object)
			comps->n1 = 1.0f;
		if (xs->i[i].t == hit.t && xs->i[i].object == hit.object
			&& cont_count > 0)
			comps->n1 = conts[cont_count - 1]->material.refractive_index;
		manage_containers(conts, &cont_count, xs->i[i].object);
		if (xs->i[i].t == hit.t && xs->i[i].object == hit.object)
		{
			comps->n2 = 1.0f;
			if (cont_count > 0)
				comps->n2 = conts[cont_count
					- 1]->material.refractive_index;
			return ;
		}
		i++;
	}
}
