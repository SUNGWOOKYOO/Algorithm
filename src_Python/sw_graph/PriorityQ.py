
class heap:
    
    def __init__(self,a):
        self.heap_size = len(a) - 1 # index 는 0 ~ len(a) - 1 이므로 
        
        # mutable variable 
        self.h = a 
    
    # Binary shifting 으로 생각  python 에서는 index 0 부터 사용 하므로 
    def parent(self,i):
        if i <= self.heap_size:
            return (i - 1) >> 1 
        else: return i # heapify 연산에서 if 문에서 비교 연산에 대해 결과가 Flase가 나와야하고, 마지막에 i로 largest(smalliest) 결정


    def left(self, i):
        if (((i << 1) + 1) <= self.heap_size):
            return (i << 1) + 1  # 2 곱함 ; index 0부터 시작이므로 +1
        else: return i 

    def right(self, i):
        if (((i<<1) + 2) <= self.heap_size):
            return (i << 1) + 2 # 2 곱하고 1더함 ; ndex 0부터 시작이므로 +1
        else: return i 

    
    def min_heapify(self, i):
     
        # smallest = argmin{a[i] , a[l], a[r]} 
        l, r = self.left(i), self.right(i) 
        if (l <= len(self.h)) and (self.h[l] < self.h[i]):
            smallest = l
        else: smallest = i 
        if (r <= len(self.h)) and (self.h[r] < self.h[smallest]):
            smallest = r
    
        # i 가 smallest 가 아니라면 a[smallest] 와 swap     
        if smallest != i:
            self.h[i], self.h[smallest] = self.h[smallest], self.h[i] # swape a[i] with a[min_idx]
            self.min_heapify(smallest)             # recursive call 
    
        # worst case running time : O(lgn)   
    
    def build_min_heap(self):
        self.heap_size = len(self.h) - 1
        for i in range((len(self.h)-1)//2,-1,-1):
            self.min_heapify(i)
            
        #running time : O(nlgn ) -> tighter upper bound : O(n)
            
    def size(self):
        return (self.heap_size + 1)
            
    """ heap sort implementation using heap"""
    def heapsort(self):
        
        # using min heap 
        self.build_min_heap()                     # min heap 을 만들고, 
        for i in range(len(self.h)-1, -1, -1):          # for loop 에서 heap property를 유지시키며, decreasing order로 sorting 
            self.h[0], self.h[i] = self.h[i], self.h[0]                # 그 과정에서 heap에 들어간 array는 점점 줄어든다. 
            self.heap_size = self.heap_size - 1    # [[ heap영역      ]  sorting된 data]  : total data
            self.min_heapify(0)                  # [[null]   sorting completed       ]
        # running time : O(nlgn)
        
        return self.h
    
class priority_queue(heap):
    
    def __init__(self, a):
        self.heap_size = len(a) - 1 # index 는 0 ~ len(a) - 1 이므로 
        
        # self.h have to always maintain min-heap property
        # self.h is a mutable type 
        self.h = a
        self.build_min_heap()  
    
    
    # ※ self.h 는 min heap property를 만족하는 array여야 한다.
    def heap_minimum(self):
        return self.h[0]
    
    def heap_extract_min(self):
        if self.heap_size < 0:
            print("heap underflow: empty array")
            return None
        mn = self.h[0] # heap 에 root 에 있는 min 값 
        
        # mn 값을 빼왔으니, 제일 뒤에있는 index에 있는 element를 빼와서 haep property를 만족하도록 한다.
        self.h[0] = self.h[len(self.h) - 1]
        self.heap_size = self.heap_size - 1
        self.min_heapify(0)
        
        del self.h[self.heap_size + 1]

        #runnig time: O(lgn)
        return mn 
         
    
    
    """ prim Algorithm을 위해 정의(Dijkstra algorithm에서도 쓰임) 
        key_update는 decrease_key function과 동일하게 동작한다. 
        decrease key는 O(lgn)시간이 걸리도록 할 수 있지만, 
        tuple의 값에 대해서 구현하기 어려워서 brutal force 방식으로 만듦 
    """
    # heap property를 만족시키면서 self.h[idex]의 (key, value) = item 을 바꿈  
    def key_update(self, idex, newitem):
        if idex == None:
            return 
        self.h[idex] = newitem
        self.build_min_heap()   
        
    def find_index(self, value):
        for k in range(self.size()):
            if self.h[k][1] == value:
                return k 
            
    def heap_included(self, v):
        for k in range(self.size()):
            if self.h[k][1] == v:
                return True 
            
print("I'm Priority Queue for Graph Algorithm")