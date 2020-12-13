/*----------------------------------------------------------------------*/
/*                                                                      */
/*      DATA TYPE DEFINEs                                               */
/*                                                           Norix      */
/*                                               written     2000/11/09 */
/*                                               last modify ----/--/-- */
/*----------------------------------------------------------------------*/
#ifndef	__TYPEDEF_INCLUDED__
#define	__TYPEDEF_INCLUDED__

typedef	int		BOOL;

typedef	unsigned char	BYTE;
typedef	unsigned short	WORD;
typedef	unsigned long	DWORD;
typedef	unsigned __int64 QWORD;

typedef float               FLOAT;
typedef FLOAT*              PFLOAT;

typedef	unsigned char	UBYTE;
typedef	unsigned short	UWORD;
typedef	unsigned long	ULONG;
typedef	unsigned long	UDWORD;
typedef	unsigned __int64 UQWORD;

typedef	signed char	SBYTE;
typedef	signed short	SWORD;
typedef	signed long	SLONG;
typedef	signed long	SDWORD;
typedef	signed __int64	SQWORD;

typedef	signed int	INT;
typedef	unsigned int	UINT;
typedef	signed short	SHORT;
typedef	signed long	LONG;

typedef	BYTE		*LPBYTE;
typedef	WORD		*LPWORD;
typedef	DWORD		*LPDWORD;

typedef	SBYTE		*LPSBYTE;
typedef	SWORD		*LPSWORD;
typedef	SLONG		*LPSLONG;
typedef	SDWORD		*LPSDWORD;

typedef	UBYTE		*LPUBYTE;
typedef	UWORD		*LPUWORD;
typedef	ULONG		*LPULONG;
typedef	UDWORD		*LPUDWORD;

typedef	SHORT		*LPSHORT;
typedef	LONG		*LPLONG;

//
// ANSI (Multi-byte Character) types
//
typedef char CHAR;
typedef CHAR* PCHAR, * LPCH, * PCH;
typedef const CHAR* LPCCH, * PCCH;

typedef CHAR* NPSTR, * LPSTR, * PSTR;
typedef PSTR* PZPSTR;
typedef const PSTR* PCZPSTR;
typedef const CHAR* LPCSTR, * PCSTR;
typedef PCSTR* PZPCSTR;
typedef const PCSTR* PCZPCSTR;

typedef CHAR* PZZSTR;
typedef const CHAR* PCZZSTR;

typedef  CHAR* PNZCH;
typedef  const CHAR* PCNZCH;

// Byte pair
typedef	union	{
	struct	{ BYTE L; BYTE H; } B;
	WORD	W;
} PAIR, *LPPAIR;

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#endif
