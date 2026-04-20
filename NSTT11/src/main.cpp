#include <iostream>


template <int I> struct IsPrime;

//          IDEA
// template<int N> 
// struct NextPrimeFind {
//     static const int next_prime = IsPrime<N>::value ? N : NextPrimeFind<N+2>::next_prime;
// };

template<int N, bool = IsPrime<N>::value> 
struct NextPrimeFind {
    static const int next_prime = NextPrimeFind<N+2>::next_prime;
};

template<int N> 
struct NextPrimeFind<N, true> {
    static const int next_prime = N;
};

template<int N>
struct NextPrime { 
    static const int value = NextPrimeFind<N + (N % 2) - 1, false>::next_prime;
};


//          IDEA
// template <int N, int J>
// struct IsPrimeFind {
//     static const bool is_prime = (J * J > N) ? true : (N % J) && IsPrimeFind<N, NextPrime<J>::value>::is_prime;
// };

template <int N, int J, bool FlagOutOfRange = (J*J > N)>
struct IsPrimeFind {
    static const bool is_prime = (N % J) && IsPrimeFind<N, NextPrime<J>::value>::is_prime;
};

template <int N, int J>
struct IsPrimeFind<N, J, true> {
    static const bool is_prime = true;
};

template <int N>
struct IsPrime {
    static const bool value = IsPrimeFind<N, 2>::is_prime;
};


template <int K, int CurrentPrime>
struct NthPrimeFind {
    static const int value = NthPrimeFind<K - 1, NextPrime<CurrentPrime>::value>::value;
};

template <int CurrentPrime>
struct NthPrimeFind<1, CurrentPrime> {
    static const int value = CurrentPrime;
};

template <int K>
struct NthPrime {
    static const int value = NthPrimeFind<K, 2>::value;
};


template <> struct NextPrime<2> { static const int value = 3; };
template <> struct NextPrime<1> { static const int value = 2; };

template <> struct IsPrime<2> { static const bool value = true; };
template <> struct IsPrime<1> { static const bool value = false; };
template <> struct IsPrime<0> { static const bool value = false; };


int main() {

    std::cout << "01st prime: " << NthPrime<1>::value << std::endl;   // 2
    std::cout << "02nd prime: " << NthPrime<2>::value << std::endl;   // 3
    std::cout << "05th prime: " << NthPrime<5>::value << std::endl;   // 11
    std::cout << "10th prime: " << NthPrime<10>::value << std::endl;  // 29
    std::cout << "15th prime: " << NthPrime<15>::value << std::endl;  // 47

    return 0;
}