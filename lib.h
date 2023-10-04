#ifndef lib
#define lib

struct StructOuter{
    struct StructInner{
        int a;
        StructInner(int aa) {
            a = aa;
        }
    };

    static inline thread_local StructInner problemStruct{3};
};

#endif
