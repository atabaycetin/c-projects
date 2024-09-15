
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************     TASK     *****************************************/
/* Two arrays of float values and length n are given. The first array stores the weights
 * (in kilograms) of a set of n parcels. The second array stores the values (in euros) of
 * the same packages. The parcels have to be uploaded on a truck within its load capacity
 * (we suppose there is no limit in volume). The target is to upload the parcels whose total
 * values (in euros) is maximized.
 * Write a recursive function
 *
 * void load_truck (float *weight, float *value, int n, float load);
 *
 * receiving as parameters the array weight, storing the weights of the packages, the array values,
 * storing their cost, n, representing the number of packages, load, specifying the maximum load
 * capacity of the truck (in kilograms), and it displays the positional number of those parcels
 * that can be loaded to maximize the transported value. For example, let us suppose that the function
 * is called with the following parameters:
 * weight = {10.0, 15.0, 25.5, 39.5, 17.0},
 * value = {19.99, 9.50, 15.00, 27.50, 11.40}, n = 5, and load = 50. The maximum value that can be
 * transported corresponds to one of the parcels 0 and 3, weight 10.0+39.5=49.5, and value in euros
 * of 19.99+27.50=47.49.
 * */


void comb(float *weight, float *value, int *sol, int n, int **rtrn, float *best, int start, int pos, float vSum,
          float wSum, float maxWeight, int *parcelCount);
void load_truck (float *weight, float *value, int n, float load);


int main() {
    float weight[5] = {(float) 10.0, (float) 15.0, (float) 25.5, (float) 39.5, (float) 17.0};
    float value[5] = {(float) 19.99, (float) 9.50, (float) 15.00, (float) 27.5, (float) 11.4};

    int n = 5;
    float load = 50;

    load_truck(weight, value, n, load);

}

void load_truck (float *weight, float *value, int n, float load) {
    int parcelCount = 0;
    int *best = NULL;
    int sol[5];
    float bestValue = 0;

    comb(weight, value, sol, 5, &best, &bestValue, 0, 0, 0, 0, 50, &parcelCount);
    float totalWeight = 0, totalValue = 0;
    for (int i = 0; i < parcelCount; i++) {
        printf("Parcel: %d - Weight: %.2f - Value: %.2f\n", best[i], weight[i], value[i]);
        totalWeight += weight[i];
        totalValue += value[i];
    }
    printf("Total Weight %.2f - Total Value: %.2f", totalWeight, totalValue);
    free(best);
}

void comb(float *weight, float *value, int *sol, int n, int **rtrn, float *best, int start, int pos, float vSum,
          float wSum, float maxWeight, int *parcelCount) {
    if (wSum >= maxWeight) {
        return;
    }
    else {
        if (vSum > *best) {
            *best = vSum;
            *rtrn = (int *) malloc(sizeof(int) * pos);
            for (int i = 0; i < pos; i++) {
                //printf("weight: %.2f value: %.2f\n", weight[sol[i]], value[sol[i]]);
                (*rtrn)[i] = sol[i];
            }
            //printf("total:  %.2f        %.2f\n\n", wSum, vSum);
            *parcelCount = pos;
        }
    }
    for (int i = start; i < n; i++) {
        sol[pos] = i;
        comb(weight, value, sol, n, rtrn, best, i+1, pos+1, vSum + value[i], wSum + weight[i], maxWeight, parcelCount);
    }

}
