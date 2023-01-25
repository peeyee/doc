#include<iostream>
using namespace std;
void printArr(int arr[]);

int main(){

   int arr1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
   cout << "arr is " << arr1;
   printArr(arr1);
}

void printArr(int arr[]){
   for(int i = 0; i < sizeof(arr); i++){
      cout<<"arr at "<< i << ": " << &arr[i] << "\n";
   }
}