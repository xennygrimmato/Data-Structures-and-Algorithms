#include<iostream>
using namespace std;

int main(){
    int a[100][100];
    int m,n;
    cin>>m>>n;

    int val=1;
    ///Init a 2d array
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            a[i][j] = val;
            val++;
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
    ///Spiral Print
    int startRow=0,startCol=0,endRow=m-1,endCol=n-1;

    while(startRow<=endRow && startCol<=endCol){

        for(int i=startCol;i<=endCol;i++){
            cout<< a[startRow][i]<<" ";
        }
        startRow++;
        for(int i=startRow;i<=endRow;i++){
            cout<< a[i][endCol]<<" ";
        }
        endCol--;

        if(endRow>startRow){
        for(int i=endCol;i>=startCol;i--){
            cout<< a[endRow][i]<<" ";
        }
        endRow--;
        }

        if(startCol<endCol){
        for(int i=endRow;i>=startRow;i--){
            cout<< a[i][startCol]<<" ";
        }
        startCol++;
        }
    }


}
