// [General.Rules]
// FileName                = 1 # 1: UpperCamel
// FunctionName            = 1 # 1: UpperCamel
// VariableName            = 1 # 1: UpperCamel
// AllowedUnderscopeChar   = true

// clang-format off

//
// Variables (Pointer)
//
void *m_VarVoidPtr        = NULL;
int *m_VarIntPtr          = NULL;
int8_t *m_VarInt8Ptr      = NULL;
int16_t *m_Var_Int16Ptr   = NULL;
int32_t *m_Var_Int32Ptr   = NULL;
int64_t *m_Var_Int64Ptr   = NULL;
uint8_t *m_Var_Uint8Ptr   = NULL;
uint16_t *m_Var_Uint16Ptr = NULL;
uint32_t *m_Var_Uint32Ptr = NULL;
uint64_t *m_Var_Uint64Ptr = NULL;

//
// Variables (Array)
//
int m_VarInt[8]         = {0};
int8_t m_VarInt8[8]     = {0};
int16_t m_VarInt16[8]   = {0};
int32_t m_VarInt32[8]   = {0};
int64_t m_VarInt64[8]   = {0};
uint8_t m_VarUint8[8]   = {0};
uint16_t m_VarUint16[8] = {0};
uint32_t m_VarUint32[8] = {0};
uint64_t m_VarUint64[8] = {0};

//
// Variables
//
size_t m_VarSize                                = 0;
int8_t m_VarInt8                                = 0;
int16_t m_VarInt16                              = 0;
int32_t m_VarInt32                              = 0;
int64_t m_VarInt64                              = 0;
uint8_t m_VarUint8                              = 0;
uint16_t m_VarUint16                            = 0;
uint32_t m_VarUint32                            = 0;
uint64_t m_VarUint64                            = 0;
char m_VarCahr                                  = 'C';
_Bool m_Var_Bool                                = false;
bool m_VarBool                                  = false;
wchar_t m_VarWideChar                           = L"WideCharString";
signed char m_VarSignedChar                     = 0;
unsigned char m_VarUnsignedChar                 = 0;
short m_VarShort                                = 0;
short int m_VarShortInt                         = 0;
signed short m_VarSignedShort                   = 0;
signed short int m_VarSignedShortInt            = 0;
unsigned short m_VarUnsignedShort               = 0;
unsigned short int m_VarUnsignedShortInt        = 0;
int m_VarInt                                    = 0;
signed m_VarSinged                              = 0;
signed int m_VarSignedInt                       = 0;
unsigned m_VarUnsigned                          = 0;
unsigned int m_VarUnsignedInt                   = 0;
long m_VarLong                                  = 0;
long int m_VarLongInt                           = 0;
signed long m_VarSingedLong                     = 0;
signed long int m_VarSingedLongInt              = 0;
unsigned long m_VarUnsingedLong                 = 0;
unsigned long int m_VarUnsignedLongInt          = 0;
long long m_VarLongLong                         = 0;
long long int m_VarLongLongInt                  = 0;
signed long long m_VarSignedLongLong            = 0;
signed long long int m_VarSignedLongLongInt     = 0;
unsigned long long m_VarUnsignedLongLong        = 0;
unsigned long long int m_VarUnsignedLongLongInt = 0;
float m_VarFloat                                = 0.0;
double m_VarDouble                              = 0.0;
long double m_VarLongDouble                     = 0.0;

ULONG m_WinVarUlong       = 0;
DWORD m_WinVarDword       = 0;
DWORD64 m_WinVarDword64   = 0;
WORD m_WinVarWord         = 0;
CHAR m_WinVarChar         = 'C';
BYTE m_WinVarByte         = 0;
HANDLE m_WinVarHandle     = NULL;
BOOLEAN m_WinVarBoolean   = FALSE;
LONGLONG m_WinVarLongLong = 0;

//
// Function
//
int MyFunc(int Value) { return 0; }

//
// Function (Prefix String)
//
int _MyFunc(int Value) { return 0; }
int __MyFunc(int Value) { return 0; }
int XXX_MyFunc(int Value) { return 0; }

//
// Function (Underscore)
//
int My_Func1(int Value) { return 0; }
int My_Func_(int Value) { return 0; }
int My_Func__(int Value) { return 0; }
int My_Func_1(int Value) { return 0; }

// clang-format ON