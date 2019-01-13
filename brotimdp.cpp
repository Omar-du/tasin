#include<iostream>
#include<cmath>
#include<iomanip>

using namespace std;

#define H 5 //height
#define V 6 //vumi
#define NA 4 //actions
int L=100;
double R=-10;
            //   n s e w
int action[NA]= {1,2,3,4};
double gama=1;
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
    if(a-b>0)
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

string policy(int h)
{
    /*int ac;
    if(final_array[h-1][v-1]==0) cout << setw(6) << "wall";
    else
    {
        for(k=0;k<NA;k++)
        {
            if(Q[h][v][k]-final_array[h-1][v-1]==0) ac = k;
        }
        cout << setw(6) << ac+1 << " ";
    }*/
    if(h==1) return "N";
    if(h==2) return "S";
    if(h==3) return "E";
    if(h==4) return "W";
}

bool isterminal(int h,int v)
{
    if(h==3&&v==4) return true;
    else if(h==2&&v==4) return true;
    else return false;
}

double d;
double q;
int o;
int main()
{
    int change,l;
    int max_change=0;
    int Count=0;

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

                q = (q1+q2+q3);

                Q[i][j][k-1]=q;

                //terminal control
                Q[3][4][0]=1;
                Q[3][4][1]=1;
                Q[3][4][2]=1;
                Q[3][4][3]=1;
                Q[2][4][0]=-1;
                Q[2][4][1]=-1;
                Q[2][4][2]=-1;
                Q[2][4][3]=-1;

                final_array[i-1][j-1]=best(best(Q[su_h][su_v][0],Q[su_h][su_v][1]),best(Q[su_h][su_v][2],Q[su_h][su_v][3]));
            }

        }
        Copy(Qold,Q);
    }

/*
   for(int z=H-2;z>0;z--)
        {
        for(int x=1;x<V-1;x++)
            {
                policy(z,x);
            }
            cout << endl;
        }
*/
/*
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
  }*/

    double temp=0;
    int policy_temp=0;
  for(i=H-2;i>0;i--)
  {
    for(j=1;j<V-1;j++)
    {
        if(iswall(i,j))
        {
            cout << setw(10) << "Wall" ;
        }
        else if(isterminal(i,j))
        {
            cout << setw(10) << Q[i][j][0] ;
        }
        else
        {
            temp = -999999.9999;
            policy_temp = 0;
            //cout << setw(10) << final_array[i-1][j-1] << " ";
            for(k=0;k<NA;k++)
            {
                if(Q[i][j][k]-temp>0)
                {
                    temp = Q[i][j][k];
                    policy_temp = k;
                }
            }
            cout << setw(10) << policy(policy_temp+1) ;
        }
    }
    cout << endl;
  }

    return 0;
}
