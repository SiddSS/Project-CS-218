#include <iostream>
#include <vector>
#include <list>
using namespace std;

int min(int a, int b)
{
	if(a<b)return a;
	else return b;
}

class Flowedge
{

  public:
  int v,w,capacity;
  int flow;
  Flowedge(int v1,int v2,int a)
  {
    //cout<<"____________class FlowEdge___________"<<endl;
    v=v1;
    w=v2;
    capacity=a;
    flow=0;
  }

  void add_ResidFlow(int from,int to,int d)
  {
    if(from==v&&to==w)
    flow+=d;//forward edge
    else if(from==w&&to==v)
    flow-=d;//backward edge
  }
  int Residual_cap(int from,int to)
  {
    if(from==v&&to==w)
    return capacity-flow;//forward edge
    else if(from==w&&to==v)
    return flow;

  }
  int other(int vertex)
  {
    if(vertex==v)
    return w;
    else if(vertex==w)
    return v;
  }

  int from() {return v;}
  int to() {return w;}

  void print()
  {
    cout<<v<<"---"<<capacity<<"--->"<<w<<endl;
  }
};

class Vertex
{
	public:
	int identity;
	int height;
	int excess;

};
class FlowNetwork
{

  vector <Flowedge> F[100];
	vector <Vertex> V[100];
  public:
  int N;
  FlowNetwork(int N1)
  {
    cout<<"____________class FlowNetwork___________"<<endl;
    N=N1;
    /*for(int i=0;i<N;i++)
    {
      F[i]= new vector<Flowedge>();
    }*/
  	for(int i=0;i<100;i++)
  	{
  		V[i].identity=i;
  		V[i].height=0;
  		V[i].excess=0;
  	}
  }
  void add_edge(Flowedge e)
  {
    cout<<"____________add_Edge___________"<<endl;
    //cout<<e.from()<<"-->"<<e.to()<<endl;
    F[e.from()].push_back(e);
    //cout<<"here";
    F[e.to()].push_back(e);
  }

  void print()
  {
    cout<<"______print_______"<<endl;
    for(int i=0;i<N;i++)
    {
      cout<<i<<endl;
      for(Flowedge w : F[i])
      {
        cout<<w.from()<<"->"<<w.to()<<endl;
      }
    }

  }


};

void demo()
{
  cout<<"____________In main___________"<<endl;
  FlowNetwork *F=new FlowNetwork(10);


  // e->print();
  // F->add_edge(*e);
  // e=new Flowedge(0,2,10)
  //e->print();
  int from,to,cap;
  for(int i=0;i<5;i++)
  {
    cin>>from>>to>>cap;
    Flowedge *e=new Flowedge(from,to,cap);
    e->print();
    F->add_edge(*e);
  }

  F->print();

}



class Pre_flow_push
{
	
	
	 void push(FlowNetwork *G,Vertex *v, Vertex *w)
	{
		char etype;Flowedge *e;int delta;
		for(Flowedge u : G.F[v.identity])
      {
        if((u.from()==v.identity)&&(u.to()==w.identity))
      	{
      		etype='f';
      		e=u;
      		break;
      	}
      	else if ((u.from()==w.identity)&&(u.to()==v.identity))
      	{
      		etype='b';
      		e=u;
      		break;
      	}
      
      
      }
	
		if(etype=='f')
		{
			delta=min(e.Residual_cap(v.identity,w.identity),v.excess);
			e.flow=e.flow+delta;
		
		}
		else if (etype=='e')
		{
			delta=min(e.Residual_cap(v.identity,w.identity),v.excess);
			e.flow=e.flow-delta;
		}	
	}
	
	void relabel(Vertex *v)
	{
		v.height+=1;
	}
  
  void Preflow_push_algo(FlowNetwork *G,Vertex t)
  {
  	for (int i=0;i<t.identity;i++)
  	{
  		for(u:G.F[0])
  		{
  			if(u.from()==0)
  			{
  				u.flow=u.capacity;
  			}
  			else
  			{
  				u.flow=0;
  			}
  		}
  	}
  	int max=G.V[0]
  	int MHV;
  	bool done=false;
  	while(done==false)
		{
			done=true;
			for(int i=0;i<t.identity;i++)
			{
				if((G.V[i].height>=max)&&(G.V[i].excess>0))
				{
					done=false;
					MHV=i;
					max=G.V[i].height;
				}
			}
			Flowedge *w;
			bool rel=true;
			if(done==false)
			{	
		
				for(w:G.F[MHV])
				{
					if(G.V[w.other(MHV)].height==(G.V[MHV].height-1))
					{
						rel=false;
						push(G,G.V[MHV],G.V[w.other(MHV)]);
						
					}
					
				}
				
				if(rel==true)
				{
					relabel(V[MHV]);
				}			
			}  
		
		}  
  
  	
  }
  
};


int main()
{

  demo();
  return 0;
}
