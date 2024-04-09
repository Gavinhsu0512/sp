#include<stdio.h>
#include<stdlib.h>

double *AllArr(int R,int C){
    return(double*)malloc( R*C*sizeof(double));
}

void createArr(double *Arr, int R, int C) {
    for (int i=0;i<R;i++) {
        double in[C];
        for (int j=0;j<C;j++) {
            scanf("%lf",&in[j]);
            Arr[i*C+j]=in[j];
        }
    }
}

void dump(double *Arr,int R,int C) {
    for (int i=0;i<R;i++) {
        for (int j=0;j<C;j++) {
            printf("%0.lf",Arr[i*C+j]);
        }
        printf("\n");
    }
}
void Transpose(double *Arr,int R,int C){
    double *temp=AllArr(R,C);
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            temp[j*R+i]=Arr[i*C+j];
        }
    }
    dump(temp,R,C);
}
void Add(double *Arra, double *Arrb,int Ra,int Ca,int Rb,int Cb){
    if (Ra==Rb && Ca==Cb)
    {
        double *temp=AllArr(Ra,Cb);
        for (int i=0;i<Ra;i++)
        {
            for (int j=0;j<Ca;j++)
            {
                temp[i*Ca+j]=Arra[i*Ca+j]+Arrb[i*Ca+j];
            }
        }
        dump(temp,Ra,Ca);
    }
    else printf("error\n");
    
}
void Multiply(double *Arra,double *Arrb,int Ra,int Ca,int Rb,int Cb ){
    if (Ca == Rb) {
        double *temp=AllArr(Ra,Cb);
        for (int i= 0;i<Ra;i++) {
            for (int j=0;j<Cb;j++){
                double sum=0;
                for (int k=0;k<Ca;k++) {
                    sum += Arra[i*Ca+k] * Arrb[k*Cb +j];
                }
                temp[i*Cb+j]=sum;
            }
        }
        printf("Arra * Arrb:\n");
        dump(temp,Ra,Cb);
    }
    else printf("error\n");
}

int main(){
    int Ra,Rb,Ca,Cb;
    printf("input Ra Ca Rb Cb\n");
    scanf("%d%d%d%d",&Ra,&Ca,&Rb,&Cb);
    double *Arra=AllArr(Ra,Ca);
    double *Arrb=AllArr(Rb,Cb);
    printf("createArr Arra:\n");
    createArr(Arra,Ra,Ca);
    printf("createArr Arrb:\n");
    createArr(Arrb,Rb,Cb);
    printf("Transposed Arra:\n");
    Transpose(Arra,Ra,Ca);
    printf("Transposed Arrb:\n");
    Transpose(Arrb,Rb,Cb);
    printf("Arra + Arrb:\n");
    Add(Arra,Arrb,Ra,Ca,Rb,Cb);
    printf("Arra * Arrb:");
    Multiply(Arra,Arrb,Ra,Ca,Rb,Cb);





}
