// [General.Rules]
// FileName                = 1 # 1: UpperCamel
// FunctionName            = 3 # 3: lower_snake
// VariableName            = 3 # 3: lower_snake
// AllowedUnderscopeChar   = false

//
// Variables (Pointer)
//
void *m_var_void_ptr       = NULL;
int *m_var_int_ptr         = NULL;
int8_t *m_var_int8_ptr     = NULL;
int16_t *m_var_int16_ptr   = NULL;
int32_t *m_var_int32_ptr   = NULL;
int64_t *m_var_int64_ptr   = NULL;
uint8_t *m_var_uint8_ptr   = NULL;
uint16_t *m_var_uint16_ptr = NULL;
uint32_t *m_var_uint32_ptr = NULL;
uint64_t *m_var_uint64_ptr = NULL;

//
// Variables (Array)
//
int m_var_int[8]         = {0};
int8_t m_var_int8[8]     = {0};
int16_t m_var_int16[8]   = {0};
int32_t m_var_int32[8]   = {0};
int64_t m_var_int64[8]   = {0};
uint8_t m_var_uint8[8]   = {0};
uint16_t m_var_uint16[8] = {0};
uint32_t m_var_uint32[8] = {0};
uint64_t m_var_uint64[8] = {0};

//
// Variables
//
size_t m_var_size                                   = 0;
int8_t m_var_int8                                   = 0;
int16_t m_var_int16                                 = 0;
int32_t m_var_int32                                 = 0;
int64_t m_var_int64                                 = 0;
uint8_t m_var_uint8                                 = 0;
uint16_t m_var_uint16                               = 0;
uint32_t m_var_uint32                               = 0;
uint64_t m_var_uint64                               = 0;
char m_var_cahr                                     = 'C';
_Bool m_var_bool_1                                  = false;
bool m_var_bool_2                                   = false;
wchar_t m_var_wide_char                             = L"WideCharString";
signed char m_var_signed_char                       = 0;
unsigned char m_var_unsigned_char                   = 0;
short m_var_short                                   = 0;
short int m_var_short_int                           = 0;
signed short m_var_signed_short                     = 0;
signed short int m_var_signed_short_int             = 0;
unsigned short m_var_unsigned_short                 = 0;
unsigned short int m_var_unsigned_short_int         = 0;
int m_var_int                                       = 0;
signed m_var_singed                                 = 0;
signed int m_var_signed_int                         = 0;
unsigned m_var_unsigned                             = 0;
unsigned int m_var_unsigned_int                     = 0;
long m_var_long                                     = 0;
long int m_var_long_int                             = 0;
signed long m_var_singed_long                       = 0;
signed long int m_var_singed_long_int               = 0;
unsigned long m_var_unsinged_long                   = 0;
unsigned long int m_var_unsigned_long_int           = 0;
long long m_var_long_long                           = 0;
long long int m_var_long_long_int                   = 0;
signed long long m_var_signed_long_long             = 0;
signed long long int m_var_signedlonglong_int       = 0;
unsigned long long m_var_unsigned_long_long         = 0;
unsigned long long int m_var_unsigned_long_long_int = 0;
float m_var_float                                   = 0.0;
double m_var_double                                 = 0.0;
long double m_var_long_double                       = 0.0;

ULONG m_win_var_ulong       = 0;
DWORD m_win_var_dword       = 0;
DWORD64 m_win_var_dword64   = 0;
WORD m_win_var_word         = 0;
CHAR m_win_var_char         = 'C';
BYTE m_win_var_byte         = 0;
HANDLE m_win_var_handle     = NULL;
BOOLEAN m_win_var_boolean   = FALSE;
LONGLONG m_win_var_longlong = 0;

//
// Function
//
int my_func(int my_val) { return 0; }
int my_func_1(int my_val) { return 0; }

//
// Function (Prefix String)
//
int _my_func(int my_val) { return 0; }
int __my_func(int my_val) { return 0; }
int XXX_my_func(int my_val) { return 0; }

//
// Function (Underscore)
//
int my_func1(int my_val) { return 0; }
int my_func_(int my_val) { return 0; }
int my_func_1(int my_val) { return 0; }
