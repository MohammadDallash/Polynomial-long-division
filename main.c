#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 10

struct number
{
    float coefficient; 
    int order;
};

int GetInput (float input1[], float input2[]);
void GetValidInput (int* p);
void printPol (float input[]);
struct number GetMax(float arry[]);
void devide (float numerator[], float denominator[]);

void main() 
{
    float polynomial1[SIZE] ={0};
    float polynomial2[SIZE] ={0};
    if (GetInput(polynomial1, polynomial2) == 0)
    {        
        printf("undevidable :(\n");
        return;
    }

    printPol(polynomial1); printf("  devided by  "); printPol(polynomial2);
    devide (polynomial1, polynomial2);
}

void printPol (float input[])
{
    struct number MaxInput = GetMax(input);
    for (int a = MaxInput.order; a >= 2 ; a--)
    {
        if(input[a]!=0)
        {
            if(fabs(input[a])==1.0)
                printf("%sx^%d", ((input[a]>0)?(a == MaxInput.order ?"":" + "):" - "),a);
            else
                printf("%s%0.1fx^%d", (input[a]>0)?(a == MaxInput.order ?"":" + "):" - ",fabs(input[a]) ,a);
        }
    }
    
    if(input[1]!=0)
    {
        if(fabs(input[1])==1.0)
            printf("%sx", (input[1]>0)?(1 == MaxInput.order ?"":" + "):" - ");
        else
            printf("%s%0.1fx", (input[1]>0)?(1 == MaxInput.order ?"":" + "):" - ",fabs(input[1]) );
    }
    
    if (input[0] != 0)
        if (MaxInput.order == 0)
            printf("%0.1f",input[0]);
        else
            printf("%s%0.1f",(input[0]>0)? " + ":" - ", fabs(input[0]));

}


struct number GetMax(float arry[])
{
    struct number max = {0, 0};
    for (int i=0; i <SIZE; i++)
    {
        if (arry[i] != 0)
        {
            max.coefficient = arry[i];
            max.order = i;
        }
    }
    return max;
}

void devide (float numerator[], float denominator[])
{
    static float result[SIZE] = {0};
    struct number MaxNum = GetMax(numerator);
    struct number MaxDen = GetMax(denominator);
    
    if (MaxNum.order < MaxDen.order)
    {
        printf ("  is:-\n" ); printPol(result);
        if (MaxNum.order == 0 && MaxNum.coefficient == 0)
            return;
        printf ("\nand your reminder is:-\n"); printPol(numerator);return;
    }
    float tempArry[SIZE] = {0};
    struct number temp = {MaxNum.coefficient /MaxDen.coefficient ,MaxNum.order - MaxDen.order};
    
    result[temp.order] = temp.coefficient;
    for (int j = 0; j <= MaxDen.order; j++)
    {
        tempArry[j+temp.order] = denominator[j] * temp.coefficient;
    }
    
    for (int k = 0; k <= MaxNum.order; k++)
    {
        numerator[k] =numerator[k]- tempArry[k];
    }
    devide (numerator, denominator);
}

int GetInput (float input1[], float input2[])
{
    int n =0 ,d;
    printf("write down the maximum power of the numerator \n");
    GetValidInput (&n);
    
    for (int i = n; i>=1; i--)
    {
        printf("write down the cooefitient of x^%d\n", i);
        scanf("%f", &input1[i]);
    }

    printf("write down the constant\n");
    scanf("%f", &input1[0]);

    printf("write down the maximum power of the denominator \n");
    GetValidInput (&d);
    for (int j = d; j>=1; j--)
    {
        printf("write down the cooefitient of x^%d\n", j);
        scanf("%f", &input2[j]);
    }

    printf("write down the constant\n");
    scanf("%f", &input2[0]);

    return n/d;
}

void GetValidInput (int* p)
{
    scanf("%d", p);
    if (*p > 0 && *p < SIZE)
        return;
    else
        printf("try again and make sure your input are between 1 and %d\n", SIZE - 1);
        GetValidInput(p);
}
