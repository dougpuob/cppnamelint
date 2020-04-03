enum MY_ENUM_A {
    MY_ENUM_a1 = 0,
    MY_ENUM_a2,
    MY_ENUM_a3
};

typedef enum _MY_ENUM_B {
    MY_ENUM_b1 = 0,
    MY_ENUM_b2,
    MY_ENUM_b3
} MY_ENUM_B;

struct MY_STRUCT_C {
    int iValueC1;
    int iValueC2;
    int iValueC3;
};

typedef struct _MY_STRUCT_D {
    int iValueD1;
    int iValueD2;
    int iValueD3;
} MY_STRUCT_D;

class MyClass {
public:
  MyClass();
  ~MyClass();
  bool MyPubFunc(int);

private:
  bool MyPrivFunc(int);
};