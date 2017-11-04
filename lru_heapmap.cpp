struct point{
  int mypoint;
  point *nextpoint;
  point *prevpoint;

  point(int val){
    mypoint = val;
    nextpoint = NULL;
    prevpoint = NULL;
  }
};

map<int, int> Map;
int maximum = 0;
int current = 0;

point* mru;
point* lru;
LRUCache::LRUCache(int capacity) {
Map.erase(Map.begin(),Map.end());
maximum = capacity;
current = 0;
mru = NULL;
lru = NULL;
}

int LRUCache::get(int key) {
    if(current > 0){
      auto mykey = Map.find(key);
      if(mykey != Map.end()){
	int temp = mykey->second;
	int value = mykey->first;
	point* curr = mru;
	while(curr->mypoint != value){
	  curr = curr->nextpoint;
	}
	point* previous = curr->prevpoint;
	point* next = curr->nextpoint;
	if(previous != NULL){
	  previous->nextpoint = next;
	  if(next == NULL){
	    lru = previous;
	  }
	  else{
	    next->prevpoint = previous;
	  }
	  curr->nextpoint = mru;
	  curr->prevpoint = NULL;
	  mru->prevpoint = curr;
	  mru = curr;
	}
	return temp;
      }
    }
return -1;

}

void LRUCache::set(int key, int value) {
if(Map.find(key) == Map.end()){
    Map.insert({key,value});
    point* temp = new point(key);
    if(current != maximum){
      current++;
      if(current==1){
	lru = temp;
	mru = temp;
      }

      else{
	mru->prevpoint = temp;
	temp->nextpoint = mru;
	mru = temp;
      }
    }
      else{ 
	int old = lru->mypoint;
	auto del_elem = Map.find(old);
	Map.erase(del_elem);
	if(lru->prevpoint == NULL){
	  lru = temp;
	  mru = temp;
	}
	else{
	  lru = lru->prevpoint;
	  lru->nextpoint = NULL;
	  mru->prevpoint = temp;
	  temp->nextpoint = mru;
	  mru = temp;
	}
      }
    }
    else{
      Map[key] = value;
      point* curr_point = mru;
      while(curr_point->mypoint != key){
	curr_point = curr_point->nextpoint;
      }
      point* previous = curr_point->prevpoint;
      point* next = curr_point->nextpoint;
      if(previous != NULL){
        previous->nextpoint = next;
	if(next== NULL){
	  lru = previous;
	}
	else{
	  next->prevpoint = previous;
	}
	curr_point->nextpoint = mru;
	curr_point->prevpoint = NULL;
	mru->prevpoint = curr_point;
	mru = curr_point;
      }
}
}
