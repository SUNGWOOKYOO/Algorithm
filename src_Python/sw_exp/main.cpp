#if 1
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include "hw.h"

using namespace std;
void writer1(int N)
{
int i;
/*
    int a[N];
    int j;
    int bFound;
    srand((unsigned int)time(NULL));

    for ( i = 0; i < N; ++i )
    {
        while ( 1 )
        {
            a[i] = rand() % N + 1;
            bFound = 0;
            for ( j = 0; j < i; ++j )
            {
                if ( a[j] == a[i] )
                {
                    bFound = 1;
                    break;
                }
            }
            if(!bFound)
                break;
        }
    }
*/
    ofstream fout;
    fout.open("./hw1.txt");
    for ( i = 0; i < N; i++ )
        fout<< (rand()% N +1) << endl;
        //fout<< a[i] <<endl;
    fout.close();

}
void writer2(int *p, int N)
{
    ofstream fout;
    fout.open("./hw2.txt");
    for (int i = 0; i < N; i++ )
        fout<< p[i] <<endl;
    fout.close();

}

void writer3(double *t, int N)
{
    ofstream fout;
    fout.open("./Tn.txt");
    for (int i = 0; i < N; i++ )
        fout<< t[i] <<endl;
    fout.close();

}


void reader1(int *p, int N)
{

    char rd[100];

    ifstream fin;
    fin.open("./hw1.txt");
    for(int i = 0; i<N; i++)
    {
        fin.getline(rd,100);
        p[i] = atoi(rd);
    }
    fin.close();
}

void reader2(int *p, int N)
{

    char rd[100];

    ifstream fin;
    fin.open("./hw2.txt");
    for(int i = 0; i<N; i++)
    {
        fin.getline(rd,100);
        p[i] = atoi(rd);
    }
    fin.close();
}

bool checker(int N)
{
    //int t1[N-1];
    int t2[N-1];
    char rd[100];

/*
    ifstream fin1;
    fin1.open("./hw1.txt");
    for(int i = 0; i<N; i++)
    {
        fin1.getline(rd,100);
        t1[i] = atoi(rd);
    }
    fin1.close();
*/
    ifstream fin2;
    fin2.open("./hw2.txt");
    for(int i = 0; i<N; i++)
    {
        fin2.getline(rd,100);
        t2[i] = atoi(rd);
    }
    fin2.close();

    cout<< "checking result : " << endl;

    for(int i = 1; i<N; i++)
    {
        if(t2[i-1] > t2[i])
        {
            return false;
        }
    }
    return true;

}



void insertion_sort(int* arr, int length)
{
    for(int j=0; j<length; j++)
    {
        int key = arr[j];
        int i = j-1;
        while( i>=0 && (arr[i] > key))    // To find proper position by comparing
        {
            arr[i+1] = arr[i];
            i--;
        }
        arr[i+1] = key;
    }
}

void swp(int* a, int* b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}

void bubble_sort(int* arr,int N){
    int i,j;
    int isSwaped;

    for(i=0; i<(N-1); i++){
        isSwaped=false;
        for(j=0; j<(N-1)-i; j++){
            if(arr[j]>arr[j+1]){
                swp(&arr[j],&arr[j+1]);
                isSwaped=true;
            }
        }
        if(isSwaped==false) {
            break;
        }
    }

}

void quick_sort(int* arr, int start, int ed){

    if(start>=ed) return;

    int mid=(start+ed)/2;
    int pivot=arr[mid];

    swp(&arr[start],&arr[mid]);

    int p=start+1,q=ed;

    while(1){
        while(arr[p]<=pivot){ p++; }
        while(arr[q]>pivot){ q--; }

        if(p>q) break;

        swp(&arr[p],&arr[q]);
    }

    swp(&arr[start],&arr[q]);

    quick_sort(arr,start,q-1);
    quick_sort(arr,q+1,ed);

}

void merg(int* arr, int start, int mid, int ed){
    int* tmp=new int[ed-start+1];
    int tmp_index=0;
    int p=start,q=mid+1;
    int i;

    for(i=tmp_index; i<=ed-start; i++){
        while(p<=mid && q<=ed){
            if(arr[p]>arr[q]){
                tmp[tmp_index]=arr[q];
                q++;
            }else{
                tmp[tmp_index]=arr[p];
                p++;
            }
            tmp_index++;
        }

        if(p>mid){
            while(q<=ed){
                tmp[tmp_index]=arr[q];
                q++;
                tmp_index++;
            }
        }
        else{
            while(p<=mid){
                tmp[tmp_index]=arr[p];
                p++;
                tmp_index++;
            }
        }
    }//end for

    for(i=start; i<=ed; i++){
        arr[i]=tmp[i-start];
    }

    delete[] tmp;
}

void merge_sort(int* arr, int start, int ed){
    if(start>=ed) return;

    int mid=(start+ed)/2;

    merge_sort(arr,start,mid);
    merge_sort(arr,mid+1,ed);

    merg(arr,start,mid,ed);
}

int main()
{
    /*
        int len;
        cout<<"Input an array's length if you want to sort an array: "<<endl;
        cin >> len;
        cout<<"Input an array's key continuously if you want to sort an array: "<<endl;
        int *pA = new int[len];

        for (int l=0; l<len; l++)
        {
            cin>>pA[l];
            cout<<"next!? "<<endl;
        }
        cout << "Thank you! I will let you show sorting the array"<<endl;
    */

    int N[] = {5,10,50,100,500,1000,5000,10000,50000,100000};
    double Tn[sizeof(N)/sizeof(N[0])*4];
    int *pA;

    for(int i=0; i<sizeof(N)/sizeof(N[0]); i++)
    {
        pA = new int[N[i]];

        srand((unsigned)time(NULL));
        writer1(N[i]);
        reader1(pA,N[i]);

        {
                {
                double start = clock();
                insertion_sort(pA, N[i]);
                Tn[i] = clock() - start;
                }

                {
                double start = clock();
                merge_sort(pA, 0, N[i]-1);
                Tn[i + (sizeof(N)/sizeof(N[0]))*1 ] = clock() - start;
                }

                {
                double start = clock();
                bubble_sort(pA, N[i]);
                Tn[i + (sizeof(N)/sizeof(N[0]))*2 ] = clock() - start;
                }
                {
                double start = clock();
                quick_sort(pA, 0,N[i]-1);
                Tn[i+ (sizeof(N)/sizeof(N[0]))*3 ] = clock() - start;

                }

        }

        writer2(pA,N[i]);
        reader2(pA,N[i]);

        cout<<checker(N[i])<< endl;
        /*
            for (int l=0; l<N; l++)
            {
                cout<< pA[l] <<endl;
            }
        */
        delete[] pA;
    }

    for(int i=0; i< (sizeof(N)/sizeof(N[0]))*4; i++)
    {
        cout<< "ruuning time is "<< Tn[i] << "  [microsecond] " <<endl;
    }

    writer3(Tn,sizeof(N)/sizeof(N[0])*4);

    return 0;
}





#endif

#if 0
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(void)
{


    return 0;
}
#endif
