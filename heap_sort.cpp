
namespace heap_sort_details {

    size_t left(size_t i) {
        return 2*i + 1;
    }

    size_t right(size_t i) {
        return 2*i + 2;
    }

    size_t parent(size_t i) {
        assert(i > 0);
        return (i-1) / 2;
    }

    template <class T>
    void heapify_up(vector<T>& A, size_t i) {
        assert(is_heap(A, i));
        
        if(i == 0) 
            return;

        auto p = parent(i);
        if(A[p] < A[i])
        {
            swap(A[p], A[i]);
            heapify(A, p);
        }

        assert(is_heap(A, i+1));
    }

    template <class T>
    void build_max_heap_up(vector<T>& A) {
        // [0, heap_size) [heap_size, size)
        size_t heap_size = 1;
        while(heap_size < A.size()) {
            heapify_up(A, heap_size);
            heap_size++;
        }
    }


    template <class T>
    void heapify_down(vector<T>& A, size_t i, size_t heap_size) {
        if(i >= A.size())
            return;

        auto max3 = compute_max_3(A, i, left(i), right(i), heap_size);
        if(i != max3)
        {
            swap(A[max3], A[i]);
            heapify_down(A, max3);
        }
    }

    template <class T>
    void build_max_heap_down(vector<T>& A) {
        auto unprocessed_size = A.size()/2;
        while(unprocessed_size > 0)
        {
            unprocessed_size--;
            heapify_down(A, unprocessed_size);
        }
    }


    template <class T>
    void heap_sort(vector<T>& A) {
        build_max_heap_down(A);

        // [heap) [sorted)
        auto begin_sorted = A.size();
        while(begin_sorted > 0) {
            begin_sorted--;
            swap(A[begin_sorted], A[0]);
            auto heap_size = begin_sorted;
            heapify_down(A, 0, heap_size);
        }
    }
        
} // namespace