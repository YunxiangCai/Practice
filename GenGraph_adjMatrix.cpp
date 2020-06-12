#include <iostream>
using namespace std;



//图的抽象类
//抽象类主要是规定了这个类需要有哪些操作（使用纯虚函数来规定）
//规定的主要操作有：insert（添加一条边）；remove（删除一条边）；exist（检验一条边是否存在）；numOfEdge(边的个数)；numofVer（结点的个数）
//由于不清楚Vertex和Edge的数据类型，所以使用模版template<class TypeOfVer,class TypeOfEdge>


//注意：纯虚函数需要写返回值（有一个完整的函数原型），只是不需要写实现

template <class TypeOfVer,class TypeOfEdge>
class graph{
protected:
	int Edges,Vers;

public:
	virtual void insert(TypeOfVer x,TypeOfVer y,TypeOfEdge w) = 0;
	virtual void remove(TypeOfVer x,TypeOfVer y) = 0;
	virtual bool exist(TypeOfVer x,TypeOfVer y) = 0;
	virtual int numOfEdge()const {return Edges;}
	virtual int numOfVer()const {return Vers;}
	void showEdges(){cout<<"Num of Edges is "<<Edges<<endl; }
};

//基于邻接矩阵的图类定义
//需要实现父类中的纯虚函数，以及构造和虚构函数
template <class TypeOfVer,class TypeOfEdge>
class adjMatrixGraph:public graph<TypeOfVer,TypeOfEdge>{

public:
	adjMatrixGraph(int size,const TypeOfVer d[],const TypeOfEdge noEdge);
	void insert(TypeOfVer x,TypeOfVer y,TypeOfEdge w);
	void remove(TypeOfVer x,TypeOfVer y);
	bool exist(TypeOfVer x,TypeOfVer y);
	~adjMatrixGraph();


private:
	TypeOfEdge **edge;
	TypeOfVer *ver;
	TypeOfEdge noEdgeFlag;
	int find(TypeOfVer v)const{
		for(int i=0;i<this->Vers;i++)//这里要加this指针 https://www.jb51.net/article/102234.htm
			if(ver[i]==v) return i;
	};
};

//adjMatrixGraph类的构造函数
template<class TypeOfVer,class TypeOfEdge>
adjMatrixGraph<TypeOfVer,TypeOfEdge>::adjMatrixGraph(int size,const TypeOfVer d[],const TypeOfEdge noEdge){

	this->Vers=size;
	this->Edges=0;
	noEdgeFlag=noEdge;

	//初始化结点
	ver= new TypeOfVer[size];
	for(int i=0;i<size;i++)
		ver[i]=d[i];

	//初始化邻接矩阵
	edge = new TypeOfEdge*[size];
	for(int i=0;i<size;i++){
		edge[i]=new TypeOfEdge[size];
		for(int j=0;j<size;j++)edge[i][j]=noEdge;
		edge[i][i]=0;
	}
}


//adjMatrixGraph类的析构函数
template<class TypeOfVer,class TypeOfEdge>
adjMatrixGraph<TypeOfVer,TypeOfEdge>::~adjMatrixGraph(){
	//释放存放结点的内存
	delete[] ver;    //要释放掉数组时用delete[]（可以多次调用数组中每个成员的析构函数），要释放单个对象用delete

	//释放存放edge的内存
	for(int i=0;i<this->Vers;i++)
		delete[] edge[i];
	delete[] edge;
}


//adjMatrixGraph类中的insert函数
template<class TypeOfVer,class TypeOfEdge>
void adjMatrixGraph<TypeOfVer,TypeOfEdge>::insert(TypeOfVer x,TypeOfVer y,TypeOfEdge w){
	int u=adjMatrixGraph<TypeOfVer,TypeOfEdge>::find(x),v=adjMatrixGraph<TypeOfVer,TypeOfEdge>::find(y);
	
	edge[u][v]=w;
	this->Edges++;
}


template<class TypeOfVer,class TypeOfEdge>
void adjMatrixGraph<TypeOfVer,TypeOfEdge>::remove(TypeOfVer x,TypeOfVer y){
	
	int u=adjMatrixGraph<TypeOfVer,TypeOfEdge>::find(x),v=adjMatrixGraph<TypeOfVer,TypeOfEdge>::find(y);
	this->Edges--;
	edge[u][v]=noEdgeFlag;
}

template<class TypeOfVer,class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer,TypeOfEdge>::exist(TypeOfVer x,TypeOfVer y){
	int u=find(x),v=find(y);
	return !(edge[u][v]==noEdgeFlag);
}





int main(){
	cout<<"hello";
	adjMatrixGraph<char,int> g(10,"abcdefghuj",-1);
	g.insert('a','f',9);
	g.showEdges();

	return 0;
}