#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

#define ns 6
#define na 2
#define L 100

int action[na]={-1,1};
double gamma = .5;
double epsilon = .001;
double q[ns][na];
double q_old[na][na];

int i,j,k,su;
int flag;

void initialization()
{
    for(i=0;i<ns;i++)
        for(j=0;j<na;j++)
    {
        q[i][j]=0;
        q_old[i][j]=0;
    }
    flag=1;
}
                    /* l   r  */
/*double reward[ns][na]=  { {0 , 0},
                      {1 , 0},
                      {0 , 0},
                      {0 , 0},
                      {0 , 5},
                      {0 , 0}, };*/
int reward(int s,int a)
{
    if(s==1 && a==0)return 1;
    else if(s==4 && a==1)return 5;
    else 0;
}

int successor(int s,int a)
{
    if(s>= 1 && s <= 4) return s+action[a];
    else return 0;
}

double ma(double a,double b)
{
    if(a-b>0)return a;
    else return b;
}

double best(int s)
{
    return ma(q_old[s][0],q_old[s][1]);
}

void cop()
{
    for(i=0;i<ns;i++)
    {
        for(j=0;j<na;j++)
        {
            q_old[i][j]=q[i][j];
        }
    }
}

void print_q()
{
    for(i=0;i<ns;i++)
    {
        for(j=0;j<na;j++)
        {
            printf("%.2lf ",q[i][j]);
        }
        printf("\n");
    }
}

void print()
{
    for(i=0;i<ns;i++)
    {
        if(i==0||i==5)continue;
        else if(q[i][0]>q[i][1]) printf("L %.2lf",q[i][0]);
        else printf("R %.2lf",q[i][1]);
        printf("\n");
    }
}

int main()
{
    for(int l=1;l<=L;l++)
    {
        initialization();
        for(i=0;i<ns;i++)
        {
            for(j=0;j<na;j++)
            {
                su = successor(i,j);
                q[i][j] = reward(i,j) + gamma * best(su);
                if(fabs(q[i][j]-q_old[i][j])<epsilon)flag=0;
            }
        }
        if(flag==0)break;
        cop();
        //printf("%d ",l);
    }
    //print_q();
    print();
    return 0;
}
