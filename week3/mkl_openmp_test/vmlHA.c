#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "mkl_vml.h"
#include "mkl_vsl.h"
#include "mkl_vml_functions.h"
#include "all_func.h"

void form_vml_HA()
{
	FILE *fp = fopen("vmlHA.csv", "w+");


	vmlSetMode( VML_HA );
	for(int vec_len = 10; vec_len <= MAX_VEC_LEN; vec_len*=10)
	{
		double *r1 = (double*)malloc(vec_len*sizeof(double));
		double *r2 = (double*)malloc(vec_len*sizeof(double)); /* buffer for random numbers */
		double *r3 = (double*)malloc(vec_len*sizeof(double));
		double s;/* average */
		VSLStreamStatePtr stream1, stream2;


		/* Initializing */ s = 0.0;
		vslNewStream( &stream1, VSL_BRNG_MT19937, 777 );
		vslNewStream( &stream2, VSL_BRNG_MT19937, 777 );

		vdRngGaussian( VSL_RNG_METHOD_GAUSSIAN_ICDF, stream1, vec_len, r1, 5.0, 2.0 );
		vdRngGaussian( VSL_RNG_METHOD_GAUSSIAN_ICDF, stream2, vec_len, r2, 7.0, 3.0 );

		for(int cycle_len = 10; cycle_len <= MAX_CYCLE_LEN; cycle_len*=10)
		{
			double start_time = omp_get_wtime();
			for(int j = 0; j < cycle_len; j++)
			{
				vdAdd(vec_len, r1, r2, r3);
				vdSub(vec_len, r1, r2, r3);
				vdMul(vec_len, r1, r2, r3);
				vdDiv(vec_len, r1, r2, r3);
			}
			double time = omp_get_wtime() - start_time;

			fprintf(fp, "%lf;", time);
		}
		fprintf(fp, "\n");
		free(r1);
		free(r2);
		free(r3);
	}
}
