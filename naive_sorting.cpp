template <class T>
void swap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template <class TIter>
void sort_naive(TIter b, TIter e)
{
    // [b, e) = [sorted) [unsorted)
    // [b, e) = [b, pivot) [pivot, e)
    for(TIter i = b; i < e; ++i)
    {
        for(TIter j = i+1; j < e; ++j)
        {
            if(*j < *i)
                swap(*i, *j);
        }
    }
}


template <class TIter>
TIter min_element(TIter b, TIter e)
{
    TIter result = b;
    while(b < e)
    {
        if(*b < *result)
            result = b;
        ++b;
    }
    return result;
}


template <class TIter>
void sort_selection(TIter b, TIter e)
{
    // [b, e) = [sorted) [unsorted)
    // [b, e) = [b, pivot) [pivot, e)
    for(TIter pivot = b; pivot < e; ++pivot)
    {
        assert(std::is_sorted(b, pivot));
        auto m = min_element(pivot, e);
        if(pivot != m)
            swap(*pivot, *m);
    }
}

template <class TIter>
void sort_selection_fun(TIter b, TIter e)
{
    for(TIter pivot = b; pivot < e; ++pivot)
        swap(*pivot, *min_element(pivot, e));
}




void sort(b, e)
{
    // [b, e) = [sorted) [unsorted)
    // [b, e) = [b, pivot) [pivot, e)
    for()
    {
        assert(is_sorted(b, pivot)); 

        // insert *pivot to [b, pivot)
        // [b, pivot)[*pivot] = [b, pivot)[v]
        // [b, pivot)[v] = [b, i) [v] (i, pivot]
        // [b, pivot)[v] = [b, i) [i] [i+1, pivot]
        for(TIter i = pivot; i != b; --i)
        {
            assert(is_sorted(b, i) && is_sorted(i, pivot+1));

            auto next_i = i+1;
            if(*next_i < *i)
                swap(*i, *next_i);
            else
                break;
            
            assert(is_sorted(b, i) && is_sorted(i, pivot+1));
        }

        assert(is_sorted(b, pivot)); 
    }
}






















// http://collabedit.com/jvumw

template <class TIter>
void sort_bubble(TIter b, TIter e)
{
    // [b, e) = [unsorted) [sorted)
    // [b, e) = [b, pivot) [pivot, e)
    for(TIter pivot = e; pivot != b; --pivot)
    {
        assert(std::is_sorted(pivot, e));
        // [b, pivot) = [b, i) [i, pivot)
        for(TIter next_i = b+1; next_i < pivot; ++next_i)
        {
            auto i = next_i-1;
            assert(i == min_element(b, next_i));   // [b, i]

            if(*next_i < *i)
                swap(*i, *next_i);

            assert(i == min_element(b, next_i));
        }

        assert(std::is_sorted(pivot, e));
    }
}



template <class TIter>
void outer_merge(TIter b1, TIter e1, TIter b2, TIter e2, TIter out) {
    TIter i1 = b1; TIter i2 = b2;
    // [b1, i1) [i1 e1)
    // [b2, i2) [i2 e2)
    // [..., out) [out] (out, ...)
    TIter b_out = out;
    while(i1 < e1 && i2 < e2) {
        assert(is_sorted(b_out, out));
        assert((i1-b1) + (i2-b2) == (out-b_out));
        if(*i1 < *i2)
            *out = *i1++;
        else
            *out = *i2++;

        assert(is_sorted(b_out, out));
        out++;
    }

    out = copy(i1, e1, out);
    out = copy(i2, e2, out);
    assert(is_sorted(b_out, out));
    assert((out-b_out) == (e1-b1) + (e2-b2));
}


template <class TIter>
void merge_sort(TIter b, TIter e, TIter buff)
{
    if(e-b > 1) {
        TIter m = b + (e-b)/2;
        // [b, m) [m, e)
        // [o, o+ms) [o+ms, o+s)
        // s = e-b
        // ms = m-b;
        merge_sort(b, m, buff);
        merge_sort(m, e, buff);
        outer_merge(b, m, m, e, buff);
        copy(buff, buff+(e-b), b);
    }

    assert(is_sorted(b, e));
}


template <class TIter>
void outer_merge_sort(TIter src_b, TIter src_e, TIter dst_b)
{
    if(e-b <= 1) {
        copy(src_b, src_e, dst_b);
        return;
    }

    size_t size = src_e - src_b;
    size_t m = size/2;
    auto src_m = src_b + m;
    auto dst_m = dst_b + m;
    auto dst_e = dst_b + size;

    outer_merge_sort(src_b, src_m, dst_b);
    outer_merge_sort(src_m, src_e, dst_m);
    outer_merge(dst_b, dst_m, dst_m, dst_e, src_b);
    
    assert(is_sorted(b, e));
}






template <class TIter>
void partition(TIter b, TIter pivot,TIter  e)
{
    assert(b <= pivot && pivot <= e);
    assert(e-b > 0);

    // [b, p) U [p] U [p+1, e)
    // [<x) [x] [>=x)
    auto x = *pivot;
    auto m = b;
    while() {
        // [partitioned)            [unpartitioned)
        // [b, m) [m, bu)           [bu, e)
        
        // [b, m) [m] [m+1, bu)     [bu] [bu+1, e)
        if(*bu >= *m) {
            // [b, m)[m, bu] [bu+1, e)
            bu++;
        } else {
            // [b, m) [m] [m+1, bu)     [bu] [bu+1, e)
            
            // [b, , bu] [m] [m+1, bu)[m+1] [bu+1, e)

            swap(*m, *bu); // [b, m, bu) // <x
        }


    }



    assert(*max_element(b, pivot) < *pivot);
    assert(*min_element(pivot, e) >= *pivot);
}


void quick_sort(TIter b, TIter e)
{
    if(e-b <= 1)
        return;

    // TIer pivot = b;    
    TIter pivot = partition(b, e, *b);
    quick_sort(b, pivot);
    quick_sort(pivot+1, e);
}





template <typename T>
void counting_sort(std::vector<T>& v)
{
    size_t counters_size = sizeof(T)*CHAR_BIT;
    size_t counters[counters_size] = { 0 };
    
    for(const auto& x : v)
    {
        ++counters[x];
    }

    size_t pos = 0;
    for(size_t i = 0; i < counters_size; ++i)
    {
        for(size_t j = 0; j < counters[i]; ++j)
        {
            v[pos] = i;
            pos++;
        }
    }
}

template <class T>
uint8_t radix_value(T x, size_t radix)
{
    return static_cast<uint8_t>(x >> (radix*CHAR_BIT));
}

template <class T>
std::vector<size_t> compute_frequencies(const std::vector<T>& v, size_t radix)
{
    size_t counters_size = sizeof(T)*CHAR_BIT;
    std::vector<size_t> freq(counters_size, 0);
    for(const auto& x : v)
    {
        auto digit = radix_value(x, radix)
        ++freq[digit];
    }

    return freq;
}

template <class T>
std::vector<size_t> cumulative_sums(const std::vector<size_t>& freq)
{
    std::vector<size_t> sums(freq.size()+1);
    copy(freq.begin(), freq.end(), back_inserter(sums));
    
    for(size_t i = 1; i < sums.size(); ++i)
    {
        sums[i] += sums[i-1];
    }
    return sums;
}

template <class T>
void radix_sort(std::vector<T>& v)
{
    std::vector<T> buff(v.size());

    auto radix_count = sizeof(T);
    for(size_t radix = 0; radix < radix_count; ++radix)
    {
        auto freq = compute_frequencies(v, radix);
        auto sums = cumulative_sums(freq);

        for(auto x : v)
        {
            auto digit = radix_value(x, radix);
            auto index = sums[digit];
            buff[index] = x;
            ++sums[digit];
        }

        v.swap(buff);
    }


}
















