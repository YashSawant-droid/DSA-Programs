#include<iostream>
#include<cstring>
using namespace std;
struct Student{
	int roll_no;
	string name;
	float sgpa;
	
};
void bubbleSort(Student arr[], int n) 
{ 
    int i, j; 
    for (i = 0; i < n - 1; i++) 
  
        // Last i elements are already 
        // in place 
        for (j = 0; j < n - i - 1; j++) 
            if (arr[j].roll_no > arr[j + 1].roll_no) 
                swap(arr[j], arr[j + 1]); 
}
void insertionSort(Student arr[], int n){
	 int i, j;
	 Student key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1],
        // that are greater than key, 
        // to one position ahead of their
        // current position
        while (j >= 0 && arr[j].name.compare(key.name) > 0) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
int partition(Student arr[],int l,int h)
{
  //choose the pivot
  
  float pivot=arr[l].sgpa;
 
  int i=l, j = h-1;
  
  while(i <= j)
  {
    while(arr[i].sgpa <= pivot)i++;
    while(arr[j].sgpa > pivot)j--;

    if(i > j)
    {
      swap(arr[i],arr[j]);
    }
  }
  swap(arr[j],arr[l]);
  return j;
}

// The Quicksort function Implement
           
void quickSort(Student arr[],int l,int h)
{
  // when low is less than high
  if(l<h)
  {
    // pi is the partition return index of pivot
    
    int pi=partition(arr,l,h);
    
    //Recursion Call
    //smaller element than pivot goes left and
    //higher element goes right
    quickSort(arr,l,pi-1);
    quickSort(arr,pi+1,h);
  }
}
void Create_database(Student* arr,int n){
for (int i = 0; i<n; i++) {
        
		cout <<endl <<"Student "<< i+1<<endl;
		cout <<"Roll No.: ";
		cin>>arr[i].roll_no;
		cout <<"Name:";
		cin>>arr[i].name;
		cout << "SGPA: ";
		cin >> arr[i].sgpa;		
	}
}
void Display_database(Student* s, int n){
for (int i = 0; i<n; i++) {
		cout <<endl<<"Student "<< i+1 <<endl;
		cout << "Roll No.: " << s[i].roll_no << endl;
        cout << "Name: " << s[i].name << endl;
        cout << "SGPA: " << s[i].sgpa << endl;		
	}
}
void Linear_search(Student s[], int n){
	int i = 0, flag = 0;
	float key;
	cout <<endl<<endl<<"Enter search value: ";
	cin >> key;
	while(i < n){
		if(s[i].sgpa == key){
			cout <<endl << s[i].roll_no << " " << s[i].name;
			flag = 1; 
		}
		i++;
	}
	if(flag == 0) cout<<endl<<"No student found with sgpa = "<< key;
}
void Binary_search(Student s[], int n, string key){
	insertionSort(s, n);
	int l = 0, h = n-1, flag = 0;
	int mid = (l + h) / 2;
	cin >> key;
	while(l <= h){
		
		if(s[mid].name.compare(key) == 0){
			cout <<endl << s[mid].roll_no << " " << s[mid].name;
			cout<<endl<<"if executed"<<endl;
			flag = 1;
			break;
		}
		else{
			if(key.compare(s[mid].name) < 0 )h = mid -1;
			else l = mid +1;
		}
		
	}
	if(flag == 1)cout << "No student found with name " << key;	
}
int main(){
	int n;
	cout<<"Enter number of students: ";
	cin>> n;
	struct Student s[n];
	Create_database(s, n);
	//bubbleSort(s, n);
	//Display_database(s, n);
	//insertionSort(s, n);
	//Display_database(s, n);
	//quickSort(s, 0, n-1);
	//Display_database(s, n);
	//Linear_search(s, n);
	Binary_search(s, n);
	
	return 0;
}
