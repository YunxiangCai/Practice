//To test dynamic array of 1-d, 2-d and 3-d
//To show how to build and free a multi diamension array

#include<iostream>
using namespace std;

int main()
{


/*********   1d   ***********/	
	int n1;
	int *array;
	cin>>n1;

	//array=(int *)calloc(n1,sizeof(int));
	array = (int *)malloc(n1);
	for(int i=0;i<n1;i++){
		array[i]=i;
	}

	for(int i=0;i<n1;i++){
		cout<<array[i]<<"\t"<<endl;
	}

	free(array);//释放一维指针

/*********   2d   ***********/	
	int num1,num2;
	cout<<"input the first diamension:"<<endl;
	cin>>num1;
	cout<<"input the second diamension"<<endl;
	cin>>num2;

	int **array2;
	array2=(int **)calloc(num1,sizeof(int*));
	for(int i=0;i<num1;i++)
		array2[i]=(int*)calloc(num2,sizeof(int));

	for(int i=0;i<num1;i++)
		for(int j=0;j<num2;j++)
			array2[i][j]=i;


	for(int i=0;i<num1;i++){
		for(int j=0;j<num2;j++)
			cout<<array2[i][j]<<"  ";
		cout<<endl;
	}


	for(int i=0;i<num1;i++) //To free a 2-d dynamic array
		free(array2[i]);
	free(array2);


/*********   3d   ***********/	
	int nn1,nn2,nn3;
	cin>>nn1>>nn2>>nn3;
	int*** array3;

	array3 = (int***)calloc(nn1,sizeof(int**));
	for(int i=0;i<nn1;i++)
		array3[i] = (int**)calloc(nn2,sizeof(int*));

	for(int i=0;i<nn1;i++)
		for(int j=0;j<nn2;j++)
			array3[i][j]=(int*)calloc(nn3,sizeof(int));

	for(int i=0;i<nn1;i++)
		for(int j=0;j<nn2;j++){
			for(int k=0;k<nn3;k++){
				array3[i][j][k] = i;
				cout<<array3[i][j][k]<<" ";
			}
			cout<< endl;
		}

	for(int i=0;i<nn1;i++)
		for(int j=0;j<nn2;j++)
			free(array3[i][j]);
	for(int i=0;i<nn1;i++)
		free(array3[i]);
	free(array3);



	return 0;
}