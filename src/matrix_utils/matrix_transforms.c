#include "matrix.h"

void	matrix_translation_constructor(double *m_trans, double x, double y, double z)
{
	m_trans[0] = 1.0;
	m_trans[1] = 0.0;
	m_trans[2] = 0.0;
	m_trans[3] = x;

	m_trans[4] = 0.0;
	m_trans[5] = 1.0;
	m_trans[6] = 0.0;
	m_trans[7] = y;

	m_trans[8] = 0.0;
	m_trans[9] = 0.0;
	m_trans[10] = 1.0;
	m_trans[11] = z;

	m_trans[12] = 0.0;
	m_trans[13] = 0.0;
	m_trans[14] = 0.0;
	m_trans[15] = 1.0;
}
