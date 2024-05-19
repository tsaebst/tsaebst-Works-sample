template <int n, int val = 1>
struct power 
{
    static void print() 
    {
        std::cout << val;
        if constexpr (n > 0) 
        {
            std::cout << ", ";
            power<n - 1, val * 2>::print();
        }
        else
        {
            std::cout << '\n';
        }
    }
};
