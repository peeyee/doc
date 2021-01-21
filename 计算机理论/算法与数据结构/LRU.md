# LRU

Least Recently Used，最近最少使用算法，广泛用于缓存设计，根据计算机的**局部性原理**:

最近使用的东西，以及和它相邻的东西，很可能在近期还会被使用。短时间来说，程度总是访问某个局部的东西。长时间未被访问的东西，近期不太可能被访问。热的东西总是很“热”，冷的东西总是很冷。

## Hash Map 与 双向链表实现LRU

### 思路

找到对应的数据节点，并将查询的节点移动到队列的最前端，在容量满时，删除队列尾端的数据。

* 通过hashMap可以快速的找到O(1)数据节点。

* 通过一个双向链表，可以快速的删除和移动数据节点。
* 数据节点需要带上key，这样才可以通过hashMap删除记录。

```java
class LRUCache {
    private HashMap<Integer,CacheNode> entry;
    private int capacity;
    private CacheNode head;
    private CacheNode tail;
    private CacheNode current;

    public LRUCache(int capacity) {
        this.capacity = capacity;
        entry = new HashMap<>(capacity);
        head = new CacheNode(-1,-1);
        tail = new CacheNode(-1,-1);
        head.next = tail;
        tail.prev = head;
    }

    public int get(int key) {
        if(entry.containsKey(key)) {
            current = entry.get(key);
            //放到队列最前端
            if (head.next != current) {
                reLink(current);
                moveToHead(current);
            }
            return entry.get(key).value;
        }else {
            return -1;
        }
    }

    public void put(int key, int value) {
        //get一下,有的话移到最前端
        if(this.get(key) != -1){
            entry.get(key).value = value;
        } else {
            //满了的话,删除tail前面的节点
            if(entry.size() == capacity)
            {
                //TODO 删除队列尾部的元素
                CacheNode delete = tail.prev;
                reLink(delete);
                entry.remove(delete.key);
            }
            current = new CacheNode(key,value);
            entry.put(key,current);
            //把current节点放到队列最前端
            moveToHead(current);
        }
    }
    
    //链接前后节点
    private void reLink(CacheNode current) {
        current.prev.next = current.next;
        current.next.prev = current.prev;
    }

    //把current节点放到队列最前端
    private void moveToHead(CacheNode current) {
        head.next.prev = current;
        current.next = head.next;
        head.next = current;
        current.prev = head;
    }
    
    private class CacheNode {
        CacheNode prev;
        CacheNode next;
        int key;
        int value;

        public CacheNode(int k,int v){
            this.key = k;
            this.value = v;
        }

    }
}
```

