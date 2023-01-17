/* merge sort */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>


void showElapsed(int id, char *m);
void showVector(int *v, int n, int id);
int * merge(int *A, int asize, int *B, int bsize);
void swap(int *v, int i, int j);
void m_sort(int *A, int min, int max);

double startT,stopT;

double startTime;

void showElapsed(int id, char *m)
{
    printf("%d: %s %f secs\n",id,m,(clock()-startTime)/CLOCKS_PER_SEC);
}

void showVector(int *v, int n, int id)
{
    int i;
    printf("%d: ",id);
    for(i=0;i<n;i++)
        printf("%d ",v[i]);
    putchar('\n');
}

int * merge(int *A, int asize, int *B, int bsize) {
    int ai, bi, ci, i;
    int *C;
    int csize = asize+bsize;

    ai = 0;
    bi = 0;
    ci = 0;

    /* printf("asize=%d bsize=%d\n", asize, bsize); */

    C = (int *)malloc(csize*sizeof(int));
    while ((ai < asize) && (bi < bsize)) {
        if (A[ai] <= B[bi]) {
            C[ci] = A[ai];
            ci++; ai++;
        } else {
            C[ci] = B[bi];
            ci++; bi++;
        }
    }

    if (ai >= asize)
        for (i = ci; i < csize; i++, bi++)
            C[i] = B[bi];
    else if (bi >= bsize)
        for (i = ci; i < csize; i++, ai++)
            C[i] = A[ai];

    for (i = 0; i < asize; i++)
        A[i] = C[i];
    for (i = 0; i < bsize; i++)
        B[i] = C[asize+i];

    /* showVector(C, csize, 0); */
    return C;
}

void swap(int *v, int i, int j)
{
    int t;
    t = v[i];
    v[i] = v[j];
    v[j] = t;
}

void m_sort(int *A, int min, int max)
{
    int *C;		/* dummy, just to fit the function */
    int mid = (min+max)/2;
    int lowerCount = mid - min + 1;
    int upperCount = max - mid;

    /* If the range consists of a single element, it's already sorted */
    if (max == min) {
        return;
    } else {
        /* Otherwise, sort the first half */
        m_sort(A, min, mid);
        /* Now sort the second half */
        m_sort(A, mid+1, max);
        /* Now merge the two halves */
        C = merge(A + min, lowerCount, A + mid + 1, upperCount);
    }
}

int main(int argc, char **argv)
{
    int * data;
    int n = atoi(argv[1]);
    int i;

    startT = clock();
    srandom(clock());
    data = (int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++) {
        data[i] = random();
    }

    m_sort(data, 0, n-1);
    /* showVector(chunk, s, id); */

    stopT = clock();

    FILE * fout;

    printf("%d; %f secs\n",n,(stopT-startT)/CLOCKS_PER_SEC);

    fout = fopen("result_seq","w");
    for(i=0;i<n;i++)
        fprintf(fout,"%d\n",data[i]);
    fclose(fout);
}