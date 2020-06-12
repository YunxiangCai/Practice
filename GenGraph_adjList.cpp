#include <iostream>
using namespace std;

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



//邻接表类的定义
template<class TypeOfVer,class TypeOfEdge>
class adjListGraph:public graph<TypeOfVer,TypeOfEdge>{
public:
	adjListGraph(int size,const TypeOfVer d[],const TypeOfEdge noEdge);
	void insert(TypeOfVer x,TypeOfVer y,TypeOfEdge w);
	void remove(TypeOfVer x,TypeOfVer y);
	bool exist(TypeOfVer x,TypeOfVer y);
	~adjListGraph();
private:
	//存储边的结点类
	struct edgeNode{
		int end;
		TypeOfEdge weight;
		edgeNode *next;
		edgeNode(int e,TypeOfEdge w,edgeNode* n = NULL){//这个很妙啊，每次插入一个节点就是把其直接放进来。这个insert写的不粗
			end=e;weight=w;next=n;
		}
	};

	struct verNode{
		TypeOfVer ver;
		edgeNode* head;
		verNode(edgeNode *h=NULL){head=h;};
	};

	verNode *verList;
	int find(TypeOfVer v)const{
		for(int i=0;i<this->Vers;++i)
			if(verList[i].ver == v) return i;
	}


};

//adjListGraph的构造函数
template<class TypeOfVer,class TypeOfEdge>
adjListGraph<TypeOfVer,TypeOfEdge>::adjListGraph(int size,const TypeOfVer d[],const TypeOfEdge noEdge){
	this->Vers=size;
	this->Edges=0;

	verList=new verNode[size];
	for(int i=0;i<size;i++) verList[i].ver=d[i];

}

//adjListGraph的析构函数
template<class TypeOfVer,class TypeOfEdge>
adjListGraph<TypeOfVer,TypeOfEdge>::~adjListGraph(){
	edgeNode *p;

	for(int i=0;i<this->Vers;i++){
		while((p=verList[i].head)!=NULL){
			verList[i].head = p->next;
			delete p;
		}
	}
	delete [] verList;
}

//adjListGraph的insert
template<class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::insert(TypeOfVer x,TypeOfVer y,TypeOfEdge w){
	int u=find(x),v=find(y);
	verList[u].head = new edgeNode(v,w,verList[u].head);//妙啊 
	this->Edges++;
}

//adjListGraph的remove
template<class TypeOfVer,class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::remove(TypeOfVer x,TypeOfVer y){
	int u=find(x),v=find(y);
	edgeNode *p=verList[u].head,*q;

	//该节点没有连接的边
	if(p==NULL) return;

	//节点要删除的边是第一个（没有头节点的时候删除第一个节点和其他节点操作不同）
	if(p->end==v){
		verList[u].head = p->next;
		delete p;
		--this->Edges;
		return;
	}

	while(p->next!=NULL&&p->next->end!=v) p=p->next;//查找要删除的边

	if(p->next!=NULL){
		q=p->next;
		p->next=q->next;
		delete q;
		--this->Edges;
	}


}
template<class TypeOfVer,class TypeOfEdge>
bool adjListGraph<TypeOfVer,TypeOfEdge>::exist(TypeOfVer x,TypeOfVer y){
	int u=find(x),v=find(y);
	edgeNode *p = verList[u].head;

	while(p!=NULL&&p->end!=v) p=p->next;
	if(p==NULL) return false;
	else return true;
}


int main()
{
	adjListGraph<char,int> g(10,"abcdefghij",-1);
	g.insert('a','b',3);
	g.showEdges();
}






