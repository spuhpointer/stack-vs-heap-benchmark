#include <stdio.h>
#include <nstdutil.h>
#include <nstopwatch.h>

/* extern NDRX_API int ndrx_bench_write_stats(double msgsize, double callspersec); */

static int M_fill = 0;
long sum, sump;
char rnd_block[1000000];

void fill_block(char *block, int size)
{
	int i;

	if (M_fill)
	{
		memcpy(block, rnd_block, size);
		for (i=0; i<size; i+=10)
		{
			sum+=block[i];
		}
	}
	
	sump += (long)block;

}

int use_stack(int *sizes)
{
	char buf0[sizes[0]];
	char buf1[sizes[1]];
	char buf2[sizes[2]];
	char buf3[sizes[3]];
	char buf4[sizes[4]];
	char buf5[sizes[5]];
	char buf6[sizes[6]];
	char buf7[sizes[7]];
	char buf8[sizes[8]];
	char buf9[sizes[9]];


	
	fill_block(buf0, sizes[0]);
	fill_block(buf1, sizes[1]);
	fill_block(buf2, sizes[2]);
	fill_block(buf3, sizes[3]);
	fill_block(buf4, sizes[4]);
	fill_block(buf5, sizes[5]);
	fill_block(buf6, sizes[6]);
	fill_block(buf7, sizes[7]);
	fill_block(buf8, sizes[8]);
	fill_block(buf9, sizes[9]);
}


int use_heap(int *sizes)
{
	char *buf0 = malloc(sizes[0]);
	char *buf1 = malloc(sizes[1]);
	char *buf2 = malloc(sizes[2]);
	char *buf3 = malloc(sizes[3]);
	char *buf4 = malloc(sizes[4]);
	char *buf5 = malloc(sizes[5]);
	char *buf6 = malloc(sizes[6]);
	char *buf7 = malloc(sizes[7]);
	char *buf8 = malloc(sizes[8]);
	char *buf9 = malloc(sizes[9]);

	fill_block(buf0, sizes[0]);
	fill_block(buf1, sizes[1]);
	fill_block(buf2, sizes[2]);
	fill_block(buf3, sizes[3]);
	fill_block(buf4, sizes[4]);
	fill_block(buf5, sizes[5]);
	fill_block(buf6, sizes[6]);
	fill_block(buf7, sizes[7]);
	fill_block(buf8, sizes[8]);
	fill_block(buf9, sizes[9]);

	free(buf0);
	free(buf1);
	free(buf2);
	free(buf3);
	free(buf4);
	free(buf5);
	free(buf6);
	free(buf7);
	free(buf8);
	free(buf9);
}

long ndrx_stopwatch_get_delta_micro(ndrx_stopwatch_t *timer)
{
    struct timespec t;
    long ret;

    clock_gettime(CLOCK_MONOTONIC, &t);
    
    /* calculate delta */
    ret = (t.tv_sec - timer->t.tv_sec) *10000000/* Convert to microsec */ +
               (t.tv_nsec - timer->t.tv_nsec)/1000; /* Convert to microsec */

    return ret;
}


int main(int argc, char **argv)
{

	int i, j, n;
	int sizes[10];
	int alloc_size;
	ndrx_stopwatch_t w;
	long result;
	long loops;
	time_t t;
	
	if (argc < 5)
	{
		fprintf(stderr, "Usage: %s s|h f|n nrloops 1|2\n", argv[0]);
		fprintf(stderr, "where \n");
		fprintf(stderr, "\ts - stack test\n");
		fprintf(stderr, "\th - heap test\n");
		fprintf(stderr, "\tf - fill data\n");
		fprintf(stderr, "\tn - no data fill\n");
		fprintf(stderr, "\tnrloops - number of iterations per size\n");
		fprintf(stderr, "\t1 - -O1 used\n");
		fprintf(stderr, "\t2 - -O2 used\n");
		return -1;
	}
	
	loops = atol(argv[3]);
	fprintf(stderr, "loops: %ld\n", loops);
	
	if ('f'==argv[2][0])
	{
		M_fill = 1;
	}

	for (i=0; i<sizeof(rnd_block); i++)
	{
		rnd_block[i] = rand() % 255;
	}

	for (i=30; i<8000; i+=1024)
	{
		alloc_size = 0;
		sum = 0;
		sump = 0;
		for (j=0; j<10; j++)
		{
			sizes[j] = i / (j+1) * 3;
			alloc_size+=sizes[j];
		}
		
		ndrx_stopwatch_reset(&w);
		for (n=0; n<loops; n++)
		{
			
			if ('s'==argv[1][0])
			{
				
				use_stack(sizes);
			}
			else
			{
				use_heap(sizes);
			}
		}
		
		/* read in millis */
		result = ndrx_stopwatch_get_delta(&w);
		
		if (0!=ndrx_bench_write_stats(alloc_size, (double)result))
		{
			fprintf(stderr, "Failed to plot results\n");
			return -1;
		}
		fprintf(stderr, "sum %ld ptr %ld\n", sum, sump);
	}
	
}
