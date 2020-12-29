
namespace stl_algobase
{
    
template <class OutPutIterator, class Size, class T>
OutPutIterator fill_n(OutPutIterator first, Size n, const T& value)
{
    for (; n>0; --n, ++first)
    {
        *first = value;
    }
    return first;
}

}