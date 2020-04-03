enum MY_ENUM_A { MY_ENUM_a1 = 0, MY_ENUM_a2, MY_ENUM_a3 };

typedef enum _MY_ENUM_B { MY_ENUM_b1 = 0, MY_ENUM_b2, MY_ENUM_b3 } MY_ENUM_B;

struct MY_STRUCT_C {
  int ValueC1;
  int value_c2;
  int iValueC3;
};

typedef struct _MY_STRUCT_D {
  int ValueD1;
  int value_d2;
  int iValueD3;
} MY_STRUCT_D;

int CFunc(int iInputA, float InputB) { return 0; }

class MyClass {
public:
  MyClass();
  ~MyClass();
  bool MyPubFunc(int);
  bool CppFunc(int InputC);

private:
  bool MyPrivFunc(int);
};