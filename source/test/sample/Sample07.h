enum MY_STRUCT_A {
    MY_STRUCT_a1 = 0,
    MY_STRUCT_a2,
    MY_STRUCT_a3
};

typedef enum _MY_STRUCT_B {
    MY_STRUCT_b1 = 0,
    MY_STRUCT_b2,
    MY_STRUCT_b3
} MY_STRUCT_B;

class MyClass {
public:
  MyClass();
  ~MyClass();
  bool MyPubFunc(int);

private:
  bool MyPrivFunc(int);
};