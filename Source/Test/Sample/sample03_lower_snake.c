// [General.Rules]
// FileName                = 1 # 1: UpperCamel
// FunctionName            = 3 # 3: lower_snake
// VariableName            = 3 # 3: lower_snake
// AllowedUnderscopeChar   = false

// clang-format OFF

//
// Variables (Pointer)
//
void *var_void_ptr       = NULL;
int *var_int_ptr         = NULL;
int8_t *var_int8_ptr     = NULL;
int16_t *var_int16_ptr   = NULL;
int32_t *var_int32_ptr   = NULL;
int64_t *var_int64_ptr   = NULL;
uint8_t *var_uint8_ptr   = NULL;
uint16_t *var_uint16_ptr = NULL;
uint32_t *var_uint32_ptr = NULL;
uint64_t *var_uint64_ptr = NULL;

//
// Variables (Array)
//
int var_int[8]         = {0};
int8_t var_int8[8]     = {0};
int16_t var_int16[8]   = {0};
int32_t var_int32[8]   = {0};
int64_t var_int64[8]   = {0};
uint8_t var_uint8[8]   = {0};
uint16_t var_uint16[8] = {0};
uint32_t var_uint32[8] = {0};
uint64_t var_uint64[8] = {0};

//
// Variables
//
size_t var_size                                   = 0;
int8_t var_int8                                   = 0;
int16_t var_int16                                 = 0;
int32_t var_int32                                 = 0;
int64_t var_int64                                 = 0;
uint8_t var_uint8                                 = 0;
uint16_t var_uint16                               = 0;
uint32_t var_uint32                               = 0;
uint64_t var_uint64                               = 0;
char var_cahr                                     = 'C';
_Bool var_bool_1                                  = false;
bool var_bool_2                                   = false;
wchar_t var_wide_char                             = L"WideCharString";
signed char var_signed_char                       = 0;
unsigned char var_unsigned_char                   = 0;
short var_short                                   = 0;
short int var_short_int                           = 0;
signed short var_signed_short                     = 0;
signed short int var_signed_short_int             = 0;
unsigned short var_unsigned_short                 = 0;
unsigned short int var_unsigned_short_int         = 0;
int var_int                                       = 0;
signed var_singed                                 = 0;
signed int var_signed_int                         = 0;
unsigned var_unsigned                             = 0;
unsigned int var_unsigned_int                     = 0;
long var_long                                     = 0;
long int var_long_int                             = 0;
signed long var_singed_long                       = 0;
signed long int var_singed_long_int               = 0;
unsigned long var_unsinged_long                   = 0;
unsigned long int var_unsigned_long_int           = 0;
long long var_long_long                           = 0;
long long int var_long_long_int                   = 0;
signed long long var_signed_long_long             = 0;
signed long long int var_signedlonglong_int       = 0;
unsigned long long var_unsigned_long_long         = 0;
unsigned long long int var_unsigned_long_long_int = 0;
float var_float                                   = 0.0;
double var_double                                 = 0.0;
long double var_long_double                       = 0.0;

ULONG win_var_ulong       = 0;
DWORD win_var_dword       = 0;
DWORD64 win_var_dword64   = 0;
WORD win_var_word         = 0;
CHAR win_var_char         = 'C';
BYTE win_var_byte         = 0;
HANDLE win_var_handle     = NULL;
BOOLEAN win_var_boolean   = FALSE;
LONGLONG win_var_longlong = 0;

//
// Function
//
int my_func(int my_value) { return 0; }

// clang-format ON