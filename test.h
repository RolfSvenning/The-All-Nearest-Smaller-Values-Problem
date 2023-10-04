#ifndef test
#define test

struct StructOuter{
    struct StructInner{
        int a;
        StructInner(int aa) {
            a = aa;
        }
    };

    static inline thread_local StructInner problemStruct{3};
};

//static inline StructOuter so{};

#endif
