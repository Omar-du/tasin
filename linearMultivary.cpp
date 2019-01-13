#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#define ft 5

using namespace std;

double data[18000][ft+1];
double new_o[ft+1],old_o[ft+1];
double sum[ft+1];
string temp,line;
int m;
double a=0.0001;
int i=0,j=0,k;

void fileRead()
{
    ifstream classFile("DATA TEST2.csv");
    while(getline(classFile,line))
    {
        istringstream s(line);
        while(getline(s,temp,','))
        {
            if(j>ft)
            {
                j=0;
                i++;
            }
            //cout<< j << " " << i << endl;
            //cout << temp << endl;
            data[i][j]=atof(temp.c_str());
            j++;
        }
    }
    m=i;
}

void init()
{
    for(i=0;i<6;i++)
    {
        new_o[i]=0;
        old_o[i]=0;
        sum[i]=0;
    }
}

double cal_error()
{
    int lo;
    double sum_error=new_o[0];
    for(j=0;j<m;j++)
    {
        /*for(lo=1;lo<ft;lo++)
        {
            sum_error+=new_o[lo]*data[m][lo];
        }
        sum_error -= data[m][0];*/
        sum_error *= sum_error;

        sum_error= (new_o[0]+new_o[1]*data[m][1]+new_o[2]*data[m][2]+new_o[3]*data[m][3]
                +new_o[4]*data[m][4]+new_o[5]*data[m][5]-data[m][0])*
                (new_o[0]+new_o[1]*data[m][1]+new_o[2]*data[m][2]+new_o[3]*data[m][3]
                +new_o[4]*data[m][4]+new_o[5]*data[m][5]-data[m][0]);
    }
    cout << fixed << sum_error <<endl;
    return sum_error/2/m;
}

void update_o()
{
    for(i=0;i<=ft;i++)
        old_o[i]=new_o[i];
}

int main()
{
    fileRead();
    init();
    cout << m;
    for(k=0;k<5000;k++)
    {
        if(k%100==0)cal_error();
        for(j=0;j<m;j++)
        {
            sum[0]= (old_o[0]
                    +old_o[1]*data[m][1]
                    +old_o[2]*data[m][2]
                    +old_o[3]*data[m][3]
                    +old_o[4]*data[m][4]
                    +old_o[5]*data[m][5]
                    -data[m][0]);
        }
        //cerr << sum[0] << endl;
        new_o[0]=old_o[0]-sum[0]*a/m;
        //cerr << old_o[0]-sum[0]*(1/m)*a << endl;
        for(i=1;i<=ft;i++)
        {
            //cout << new_o[i-1] << endl;
            for(j=0;j<m;j++)
            {
                sum[i]= (old_o[0]
                        +old_o[1]*data[m][1]
                        +old_o[2]*data[m][2]
                        +old_o[3]*data[m][3]
                        +old_o[4]*data[m][4]
                        +old_o[5]*data[m][5]
                        -data[m][0])*data[m][i];
            }
            new_o[i]=old_o[i]-sum[i]*a/ms;
        }
        update_o();
    }
    for(i=0;i<=ft;i++)
    {
        cout << "O(" << i << ") = " << new_o[i] << " " << endl;
    }
double a[ft+1];
    a[0]=1,a[1]=3,a[2]=1,a[3]=1430,a[4]=19901,a[5]=1.5;
    /*a[0]=0;
    a[1]=3;
    a[2]=1;
    a[3]=1430;
    a[4]=19901;
    a[5]=1.5;
    a[6]=0;
    a[7]=0;
    a[8]=4;
    a[9]=7;
    a[10]=1430;
    a[11]=0;
    a[12]=1927;
    a[13]=0;
    a[14]=98028;
    a[15]=47.7558;
    a[16]=-122.229;
    a[17]=1780;
    a[18]=12697;*/
    double summ=0;
    //cin >> a1 >> a2 >> a3 >> a4 >> a5;
    for(i=0;i<=ft;i++)
    {
        summ+=(new_o[i]*a[i]);
    }

    cout << summ << endl;
    return 0;
}

