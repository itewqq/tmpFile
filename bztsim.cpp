#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int T=4;
const int N=100;
const double per=0.5;
const int L=round(per*N);
const int eta=2;//round(0.4*T);
double alpha=0.3;
const double PMAL=0.7;
const double Pfa=0.2;


int LL;//L'
int NN;//N' The number of nodes after removing the Byzantines.

bool sys[T+1];
bool fc_dint[T+1];
bool fc_decision[T+1];

int cal_H1[T+1];
int cal_HH1[T+1];
int err;
double rate_err;

struct node{
    bool isByzantine=false;
    bool report[T+1];
    bool observe[T+1];
    bool isRemoved=false;
    double pmal=0.0;
    int reputation=0;
}nodes[N+1];

bool RandomBool(double lim){
    double r = ((double) rand() / (RAND_MAX));
    return r<lim;
}

void init(){
    for(int i=1;i<=T;++i){
        sys[i]=0;
        fc_dint[i]=0;
        fc_decision[i]=0;
        cal_H1[i]=0;
        cal_HH1[i]=0;
    }
    NN=0;
    LL=0;
    for(int i=1;i<=N;++i){
        nodes[i].isRemoved=0;
        nodes[i].isByzantine=0;
        nodes[i].reputation=0;
    }
    //init_sys
    for(int i=1;i<=T;++i){
        sys[i]=RandomBool(0.5);
    }
    //init_nodes
    for(int i=1;i<=N;++i){
        nodes[i].isByzantine=RandomBool(alpha);
        if(nodes[i].isByzantine){
            nodes[i].pmal=PMAL;
        }//is byzantine
        memcpy(nodes[i].observe,sys,sizeof(sys));
    }
}

void report_sys(){
    for(int i=1;i<=N;++i){
        for(int j=1;j<=T;++j){
            if(RandomBool(2*Pfa)){
                nodes[i].observe[j]=(!nodes[i].observe[j]);//system error
            }
            nodes[i].report[j]=nodes[i].observe[j];
            if(nodes[i].isByzantine){
                if(RandomBool(PMAL)){
                    nodes[i].report[j]=(!nodes[i].report[j]);//byzantine lying error
                }
            }
        }

    }
}

void fc_fusion(){
    for(int i=1;i<=T;++i){
        for(int j=1;j<=N;++j){
            if(nodes[j].report[i]){//error1
                ++cal_H1[i];
            }
        }
        if(L<=cal_H1[i]){
            fc_dint[i]=1;   //temporary fusion
        }
    }
    //reputation
    for(int i=1;i<=N;++i){
        for(int j=1;j<=T;++j){
            if(fc_dint[j]==nodes[i].report[j]){
                ++nodes[i].reputation;
            }
        }
    }
    //remove
    for(int i=1;i<=N;++i){
        if(nodes[i].reputation<eta){
            nodes[i].isRemoved=true;
        }
    }
    //final decision
    for(int i=1;i<=N;++i){
        if(!nodes[i].isRemoved){
            ++NN;
        }
    }
    LL=round(per*NN);

    for(int i=1;i<=T;++i){
        for(int j=1;j<=N;++j){
            if((!nodes[j].isRemoved) && nodes[j].report[i]){//error2
                ++cal_HH1[i];
            }
        }
        if(LL<=cal_HH1[i]){
            fc_decision[i]=1;   //final fusion
        }
    }

}

int cal_error(){
    int tmp=0;
    for(int i=1;i<=T;++i)
        if(fc_decision[i]!=sys[i])
            ++tmp;
    return tmp;
    //rate_err=1.0*err/T;
    //printf("%d %lf",err,rate_err);
}

int main(){
    int tot_err=0;
    srand(time(0));
    for(int i=0;i<50000;++i) {
        //alpha=0.4+0.1*((double) rand() / (RAND_MAX));
        //printf("%f\n",alpha);
        init();
        report_sys();
        fc_fusion();
        tot_err+=cal_error();
    }
    printf("%d %.10f",tot_err,1.0*tot_err/50000/4);
    return 0;
}
