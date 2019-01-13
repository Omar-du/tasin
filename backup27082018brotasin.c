#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

#define H 5 //height
#define V 6 //vumi
#define NA 4 //actions
int L=100;
double R=0;
            //   n s e w
int action[NA]= {1,2,3,4};
double gama=.5;
double epsilon=0.0001;
double Q[H][V][NA];
double Qold[H][V][NA];
double final_array[H-2][V-2];

int i,j,k;

void init()
{
    for(i=0;i<H;i++)
    {
        for(j=0;j<V;j++)
        {
            for(k=0;k<NA;k++)
            {
                Q[i][j][k]=0;
                Qold[i][j][k]=0;
            }
        }
    }
}


double best(double a, double b)
{
    if(a>b)
        return a;
    else
        return b;
}


double Reward(int h,int v,int a)
{
    if(h==3 && v==3 && a==3)
        return 1;
    else if(h==2 && v==3 && a==3)
        return -1;
    else if(h==1 && v==4 && a==1)
        return -1;
    else
        return R;
}

bool iswall(int h,int v)
{
    if(h==0||v==0||h==4||v==5) return true;
    else if(h==2&&v==2) return true;
    else return false;
}

bool terminal(int h,int v)
{
    if(h==3 && v==4)
        return true;
    else if(h==2 && v==4)
        return true;
    else
        return false;
}

int su_h=0;
int su_v=0;

void successor(int h,int v,int a)
{
    if(a==1)
    {
        if(!iswall(h+1,v))
        {
            su_h= h+1;
            su_v= v;
        }
        else
        {
            su_h= h;
            su_v= v;
        }
        return;
    }
    if(a==2)
    {
        if(!iswall(h-1,v))
        {
            su_h= h-1;
            su_v= v;
        }
        else
        {
            su_h= h;
            su_v= v;
        }
        return;
    }
    if(a==3)
    {
        if(!iswall(h,v+1))
        {
            su_h= h;
            su_v= v+1;
        }
        else
        {
            su_h= h;
            su_v= v;
        }
        return;
    }
    if(a==4)
    {
        if(!iswall(h,v-1))
        {
            su_h= h;
            su_v= v-1;
        }
        else
        {
            su_h= h;
            su_v= v;
        }
        return;
    }
}


void Copy(double a[H][V][NA],double b[H][V][NA])
{
    for(k=0;k<H;k++)
    for(i=0;i<V;i++)
    for(j=0;j<NA;j++)
    {
        a[k][i][j]=b[k][i][j];
    }
}

double pro_s = .8;
double pro_o = .1;

double transition(int a)
{
    if(a==1)
    {

    }
    else if(a==2)
    {

    }
    else if(a==3)
    {

    }
    else if(a==4)
    {

    }
}

int sucLeft(int q) // left
{
    if(q==1) return 4;
    if(q==2) return 3;
    if(q==3) return 1;
    if(q==4) return 2;
}


int sucRight(int q) // right
{
    if(q==1) return 3;
    if(q==2) return 4;
    if(q==3) return 2;
    if(q==4) return 1;
}

void policy(int h,int v)
{
    int ac;
    if(final_array[h-1][v-1]==0) cout << setw(6) << "wall";
    else
    {
        for(k=0;k<NA;k++)
        {
            if(Q[h][v][k]-final_array[h-1][v-1]==0) ac = k;
        }
        cout << setw(6) << ac << " ";
    }
}

double d;
double q;
int o;
int main()
{
    int change,l;
    int max_change=0;
    int Count=0;

    R=-2;
    cout << "Enter living reward: " << endl;
    //cin >> R;

    double k1,k2,k3,q1,q2,q3;

    for(l=1;l<=L;l++)
    {
        for(i=1;i<H-1;i++)
        for(j=1;j<V-1;j++)
        {
            if(!iswall(i,j))
            for(k=1;k<=NA;k++)
            {
                k1=k;
                successor(i,j,k1);
                d= best(best(Qold[su_h][su_v][0],Qold[su_h][su_v][1]),best(Qold[su_h][su_v][2],Qold[su_h][su_v][3]));
                q1= .8*(Reward(i,j,k)+gama*d);

                k2= sucLeft(k);
                successor(i,j,k2);
                d= best(best(Qold[su_h][su_v][0],Qold[su_h][su_v][1]),best(Qold[su_h][su_v][2],Qold[su_h][su_v][3]));
                q2= .1*(Reward(i,j,k2)+gama*d);

                k3= sucRight(k);
                successor(i,j,k3);
                d= best(best(Qold[su_h][su_v][0],Qold[su_h][su_v][1]),best(Qold[su_h][su_v][2],Qold[su_h][su_v][3]));
                q3= .1*(Reward(i,j,k3)+gama*d);

                //q = best(best(q1,q2),best(q2,q3));
                q = (q1+q2+q3);

                Q[i][j][k-1]=q;
                final_array[i-1][j-1]=best(best(Q[su_h][su_v][0],Q[su_h][su_v][1]),best(Q[su_h][su_v][2],Q[su_h][su_v][3]));



                /*change=fabs(Q[i][j][k-1]-Qold[i][j][k-1]);
                if(change>max_change)
                max_change=change;*/
                //cout << "try";
            }
            /*else
                cout << "wall " << i << " " << j << " " << endl;*/
        }
        Copy(Qold,Q);
        //cout << "once " << endl;
        /*if(max_change>epsilon)
        {
          Count++;
          Copy(Qold,Q);
          max_change=0;
        }
        else
        break;
*/
    }
/*    for(int z=H-2;z>0;z--)
        {
        for(int x=1;x<V-1;x++)
            {
                policy(z,x);
            }
            cout << endl;
        }
*/
  for(i=1;i<H-1;i++)
  {
    for(j=1;j<V-1;j++)
    {
        //cout << setw(10) << final_array[i-1][j-1] << " ";
        for(k=0;k<NA;k++)
        {
            cout << setw(10) << Q[i][j][k] << " ";
        }
        cout << endl;
    }
    cout << endl;
  }

    return 0;
}
