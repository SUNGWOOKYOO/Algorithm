
# node로 구현 
class node: 
    
    def __init__(self, name):
        self.name = name
        self.d = 0 
        self.f = 0
        self.pi = 0  
        self.key = 0
        self.color = 'unknown'
        self.edge = {}
        self.number = float('inf')
        
class Graph: 
    
    time = 0
    
    def __init__(self, graph_dict=None, w = None):
        
        # preprocessing
        vertices = list(graph_dict.keys())
        vertices.sort()
        vertices
        
        if graph_dict == None:
            graph_dict = {}
        self.graph_dict = graph_dict
        
        # node object로 list 만듦
        self.nodes = []
        for n in list(vertices):
            self.nodes.append(node(n))
        
        # node object로 dictionary 만듦
        self.nm = {}
        for k in range(len(vertices)):
            self.nm[self.nodes[k].name] = self.nodes[k]
            self.nodes[k].number = k
        
        # edge 를 w 에 의해 부여 
        for j in range(len(vertices)):  # j vertex
            for i in self.graph_dict[self.nodes[j].name]:      # i edge 
                self.nodes[j].edge[i] = w[self.nodes[j].name][i]             # allocate weight 
        self.weight_dict = w
                
    
    # Graph 의 weight information all pair Matrix return 
    def myweight(self):
        # preprocessing
        vertices = list(self.graph_dict.keys())
        vertices.sort()
        vertices
    
        # node information 
        for v in vertices:
            print("(node.number : ",self.nodes[self.nm[v].number].number, ", node.name : ",self.nodes[self.nm[v].number].name," )" )
        
        import numpy as np
        n = len(self.nodes)
        W = np.ones((n,n))*float('inf')
        
        for i in range(n):
            W[i][i] = 0
        
        for u in self.graph_dict:
            for v in list(self.nm[u].edge):
                if self.nm[u].edge[v] is not None: # from u to v weight
                    W[self.nm[u].number][self.nm[v].number] = self.nm[u].edge[v]
            
        return W
    
    # Graph의 direct edge (0개의 vertex 거치는)Shortest path pi for all pair Information Matrix 
    def myinitialpi(self):
        # preprocessing
        vertices = list(self.graph_dict.keys())
        vertices.sort()
        vertices
        
        for v in vertices:
            print("(node.number : ",self.nodes[self.nm[v].number].number, ", node.name : ",self.nodes[self.nm[v].number].name," )" )
            print(" node.edge : ", self.nodes[self.nm[v].number].edge )

        import numpy as np
        n = len(self.nodes)
        P = np.ones((n,n))*float('inf')
        
        for u in vertices:
            for v in list(self.nm[u].edge):
                if self.nm[u].edge[v] is not None: # from u to v weight
                    P[self.nm[u].number][self.nm[v].number] =(self.nm[u].number) 
        
        return P                 
                
                
                
    # sort the edge of G.E into nondecreasing order by weight w 
    def sort_edge(self):
        import operator
        temp = []
    
        for v in list(self.graph_dict.keys()):
            for i in list(self.nm[v].edge):
                temp.append((v,i,self.nm[v].edge[i]))

        t = sorted(temp, key = operator.itemgetter(2), reverse = False)
        #print(t)

        srt = []
        for m in range(len(t)): 
            srt.append([t[m][0],t[m][1]])
        #print(srt,"sort 이후 edge")
        return srt            
                
    """ DFS Algorithm running time : Θ(|V|+ |E|), 왜냐면, white 인 경우만 DFS_vist을 하므로"""
    # except DFS_vist, T = Θ(|V|)
    def DFS(self, a = []): # a = [] 이면 순서를 dict.keys() 순으로, o.w list (a)  순으로 searching 
    
        # running time O(V + E)
    
        for u in list(self.graph_dict.keys()):   
            self.nm[u].color = 'white'
            self.nm[u].pi = None
        
        self.time = 0
    
        #print("Debug sorting ", a)
        if a == []:
            #print(self.graph_dict.keys()," 순으로 searching 하게 된다.")
            for u in list(self.graph_dict.keys()): 
                if self.nm[u].color == 'white':
                    self.DFS_visit(u)
        else:
            #print(a," 순으로 searching 하게 된다.")
            for u in a: 
                if self.nm[u].color == 'white':
                    self.DFS_visit(u)
    
    
    # each DFS_vist, T = Θ(|V|)    
    def DFS_visit(self,u):
        self.time  = self.time + 1 
        self.nm[u].d = self.time 
        self.nm[u].color = 'gray'
    
        #print(G.graph_dict[u] ," 순으로 vertex", u, " 의 adjoint list를 searching 하게 된다.")
        for v in list(self.graph_dict[u]):
            if self.nm[v].color == 'white':
                self.nm[v].pi  = u
                self.DFS_visit(v)
        self.nm[u].color = 'black'
        self.time = self.time + 1 
        self.nm[u].f = self.time    
    

    # graph 에서 모든 edge들의 우선순위를 지켜주는 linear ordering 을 찾아 주었다. 
    # DAG(directed Acyclic graph) 에서 사용 
    def Topological_sort(self,l = []):
        import operator
        print("Topological_sort사용")
        self.DFS(l)
    
        # node object로 dictionary 만듦a
        topo = {}
        for k in range(len(list(self.graph_dict.keys()))):
            topo[self.nodes[k].name] = self.nodes[k].f
    
        temp = sorted(topo.items(), key = operator.itemgetter(1), reverse = True)
    
        srt = []
        for m in range(0,len(temp)):
            srt.append(temp[m][0])    
        print(srt, "Topological sort 결과 ")
        return srt 
    
    """ single src shortest path operation """
    def initialize_single_source(self,s):
        for v in list(self.graph_dict.keys()):
            self.nm[v].d = float('inf')
            self.nm[v].pi = None
        self.nm[s].d = 0
        # T = O(V)

    def relax(self,u,v):
        if self.nm[v].d > self.nm[u].d + self.nm[u].edge[v]:
            #print(">>> ",v,".d 값을 ",u,".d  + edge(",u,",",v,")로 update ")
            self.nm[v].d = self.nm[u].d + self.nm[u].edge[v]
            self.nm[v].pi = self.nm[u].name
        # T = O(1)
        
    def showinfo(self):
        print(self.graph_dict)
        print(" node dictionary : ")
        print(self.nm)
        
        for v in list(self.graph_dict.keys()):
            print(">> [ ",v, " node Info] : ")
            print(v, ", edge: ", self.nm[v].edge)
            print(v, ", pi: ", self.nm[v].pi)
            print(v, ", d: ", self.nm[v].d)