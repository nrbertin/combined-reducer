#include <Kokkos_Core.hpp>

class ClassBase {
public:
    ClassBase() {}
    virtual ~ClassBase() {}
};

class ClassDerived : public ClassBase {
public:
    Kokkos::View<double*[2]> data;
    double dmax[2];

    KOKKOS_INLINE_FUNCTION
    void operator() (const int& i) const {
        data(i,0) = 1.0*i;
        data(i,1) = 2.0*i;
    }

    KOKKOS_INLINE_FUNCTION
    void operator() (const int& i, double& dmax0, double& dmax1) const {
        double d0 = data(i,0);
        if (d0 > dmax0) dmax0 = d0;
        double d1 = data(i,1);
        if (d1 > dmax1) dmax1 = d1;
    }
    
    ClassDerived()
    {
        int N = 1000;
        data = Kokkos::View<double*[2]>("data", N);

        Kokkos::parallel_for("Fill", N, *this);
        Kokkos::fence();

        Kokkos::parallel_reduce("ReduceMax", N, *this,
            Kokkos::Max<double>(dmax[0]), Kokkos::Max<double>(dmax[1])
        );
        Kokkos::fence();

        printf("Max = %e %e\n", dmax[0], dmax[1]);
    }

    ~ClassDerived() {}
};

int main(int argc, char* argv[])
{
    Kokkos::ScopeGuard guard(argc, argv);

    ClassDerived c;

    return 0;
}

