#include <stdio.h>
#include <math.h>

#define ns 6
#define na 2
#define L 100

int action[na]={-1,1};
double gamma = 0.5;
double epsilon = .001;
double q[ns][na];
double q_old[ns][na];
double maxchange,change;

int i,j,k,su;
int flag;

void initialization()
{
    maxchange=0;
    for(i=0;i<ns;i++)
        for(j=0;j<na;j++)
    {
        q[i][j]=0;
        q_old[i][j]=0;
    }
    flag=1;
}
                    /* l   r  */
double reward[ns][na]=  { {0 , 0},
                            {1 , 0},
                            {0 , 0},
                            {0 , 0},
                            {0 , 5},
                            {0 , 0}, };

/*int reward(int s,int a)
{
    if(s==1 && a==0)return 1;
    else if(s==4 && a==1)return 5;
    else 0;
}*/

int successor(int s,int a)
{
    if(s>= 1 && s <= 4) return s+action[a];
    else return 0;
}

double max(double a,double b)
{
    if(a-b>0)return a;
    else return b;
}

double best(int s)
{
    return max(q_old[s][0],q_old[s][1]);
}

void copy()
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
            printf("%.3lf ",q[i][j]);
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
    initialization();
    for(int l=1;l<=L;l++)
    {
        //flag=0;
        for(i=0;i<ns;i++)
        {
            for(j=0;j<na;j++)
            {
                su = successor(i,j);
                q[i][j] = reward[i][j] + gamma * best(su);
                //printf("%lf ",q[i][j]);
                change = fabs(q[i][j]-q_old[i][j]);
                //printf("%lf ",change);
                if(fabs(q[i][j]-q_old[i][j])>epsilon)flag=1;
                change = fabs(q[i][j]-q_old[i][j]);
                if(change>maxchange)maxchange = change;
            }
            //printf("\n");
        }
        if(maxchange>epsilon)copy();
        else break;
        //printf("%d ",l);
        //print_q();
        //if(flag==1)break;
       // copy();
        //printf("%d ",l);
    }
    print_q();
    print();
    return 0;
}
