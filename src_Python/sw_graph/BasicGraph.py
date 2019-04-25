
# node로 구현 
class node: 
    
    def __init__ (self, name):
        self.name = name
        self.d = 0 
        self.f = 0
        self.pi = 0  
        self.color = 'unknown'

class Graph: 
    
    time = 0
    
    def __init__(self, graph_dict=None):
        if graph_dict == None:
            graph_dict = {}
        self.graph_dict = graph_dict
        
        # node object로 list 만듦
        self.nodes = []
        for n in list(self.graph_dict.keys()):
            self.nodes.append(node(n))
        
        # node object로 dictionary 만듦
        self.nm = {}
        for k in range(len(list(self.graph_dict.keys()))):
            self.nm[self.nodes[k].name] = self.nodes[k]
    
    def showinfo(self):    
        for x in list(self.graph_dict.keys()):
            print("vertex name", self.nm[x].name)
            print("color 값", self.nm[x].color)
            print("d 값", self.nm[x].d)
            print("pi 값", self.nm[x].pi)
        
print("hi! I'm BasicGraph.py file ")