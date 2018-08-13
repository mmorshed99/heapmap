# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    # @param A : list of linked list
    # @return the head node in the linked list
    def mergeKLists(self, A):
        class heap():
            def __init__(self,X):
                self.arr = X
                self.total_nodes = len(self.arr)
            def build_heap(self):
                for idx in reversed(range(len(self.arr)/2)):
                    self.heapify(idx)
                return
            def heapify(self,idx):
                min_idx = idx
                left_idx = 2 * min_idx + 1
                right_idx = 2 * min_idx + 2
                if left_idx < len(self.arr) and self.arr[left_idx].val < self.arr[min_idx].val:
                    min_idx = left_idx
                if right_idx < len(self.arr) and self.arr[right_idx].val < self.arr[min_idx].val:
                    min_idx = right_idx
                if min_idx != idx:
                    self.arr[min_idx],self.arr[idx] = self.arr[idx],self.arr[min_idx]
                    self.heapify(min_idx)
                return
            def extract_min(self):
                head = self.arr[0]
                if head.next == None:
                    self.total_nodes -= 1
                    new_head = self.arr[-1]
                    del self.arr[-1]
                    self.arr[0] = new_head
                else:
                    self.arr[0] = head.next
                self.heapify(0)
                return head
        my_heap = heap(A)
        my_heap.build_heap()
        my_return_head = my_heap.arr[0]
        if my_heap.total_nodes == 0 or my_heap.total_nodes == 1:
            return my_return_head
        prev = None
        while(my_heap.total_nodes >= 2):
            curr = my_heap.extract_min()
            if prev != None:
                prev.next = curr
            prev = curr
            if my_heap.total_nodes == 1:
                prev.next = my_heap.arr[0]
        return my_return_head
