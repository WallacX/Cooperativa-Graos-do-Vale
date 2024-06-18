#include <stdio.h>
//#define n 15

float pic(float *p, float *q, int n);
float guc(float*p, float *q, float*u, int n);

int main(){

    int n;
    printf("\nDigite o valor de n");
    scanf("%d",&n);

    float p[n],q[n],u[n];
    
    for(int i=0; i<n;i++)
    {
    printf("\np[%d], q[%d], u[%d]", i, i, i);
    scanf("%f %f %f", &p[i], &q[i], &u[i]);
    }

    printf("\nPic: %.2f",pic(p,q,n));
    printf("\nGuc: %.2f",guc(p,q,u,n));

    return 0;

}

float pic(float p[], float q[],int n){

    float somap = 0,somaq = 0, pic;

    for(int i=0;i<n;i++)
    {
        somap += p[i];       
        somaq += q[i];
    }

    pic = somap / somaq;

    return pic;
}

float guc(float p[], float q[] , float u[],int n){

    float x = 0, y = 0 , guc;

    for(int i=0;i<n;i++)
    {
        x +=  u[i] * (p[i] - q[i]);
        y += (p[i]-q[i]);    
    }

    guc = x / y;

    return guc;

}
