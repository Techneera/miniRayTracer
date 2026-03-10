#include "librt.h"

int	get_shape_id(void)
{
	static int	id;

	return (id++);
}
