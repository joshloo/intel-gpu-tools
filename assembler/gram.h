/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_GRAM_H_INCLUDED
# define YY_YY_GRAM_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    COLON = 258,
    SEMICOLON = 259,
    LPAREN = 260,
    RPAREN = 261,
    LANGLE = 262,
    RANGLE = 263,
    LCURLY = 264,
    RCURLY = 265,
    LSQUARE = 266,
    RSQUARE = 267,
    COMMA = 268,
    EQ = 269,
    ABS = 270,
    DOT = 271,
    PLUS = 272,
    MINUS = 273,
    MULTIPLY = 274,
    DIVIDE = 275,
    TYPE_UD = 276,
    TYPE_D = 277,
    TYPE_UW = 278,
    TYPE_W = 279,
    TYPE_UB = 280,
    TYPE_B = 281,
    TYPE_VF = 282,
    TYPE_HF = 283,
    TYPE_V = 284,
    TYPE_F = 285,
    ALIGN1 = 286,
    ALIGN16 = 287,
    SECHALF = 288,
    COMPR = 289,
    SWITCH = 290,
    ATOMIC = 291,
    NODDCHK = 292,
    NODDCLR = 293,
    MASK_DISABLE = 294,
    BREAKPOINT = 295,
    ACCWRCTRL = 296,
    EOT = 297,
    SEQ = 298,
    ANY2H = 299,
    ALL2H = 300,
    ANY4H = 301,
    ALL4H = 302,
    ANY8H = 303,
    ALL8H = 304,
    ANY16H = 305,
    ALL16H = 306,
    ANYV = 307,
    ALLV = 308,
    ZERO = 309,
    EQUAL = 310,
    NOT_ZERO = 311,
    NOT_EQUAL = 312,
    GREATER = 313,
    GREATER_EQUAL = 314,
    LESS = 315,
    LESS_EQUAL = 316,
    ROUND_INCREMENT = 317,
    OVERFLOW = 318,
    UNORDERED = 319,
    GENREG = 320,
    MSGREG = 321,
    ADDRESSREG = 322,
    ACCREG = 323,
    FLAGREG = 324,
    MASKREG = 325,
    AMASK = 326,
    IMASK = 327,
    LMASK = 328,
    CMASK = 329,
    MASKSTACKREG = 330,
    LMS = 331,
    IMS = 332,
    MASKSTACKDEPTHREG = 333,
    IMSD = 334,
    LMSD = 335,
    NOTIFYREG = 336,
    STATEREG = 337,
    CONTROLREG = 338,
    IPREG = 339,
    GENREGFILE = 340,
    MSGREGFILE = 341,
    MOV = 342,
    FRC = 343,
    RNDU = 344,
    RNDD = 345,
    RNDE = 346,
    RNDZ = 347,
    NOT = 348,
    LZD = 349,
    MUL = 350,
    MAC = 351,
    MACH = 352,
    LINE = 353,
    SAD2 = 354,
    SADA2 = 355,
    DP4 = 356,
    DPH = 357,
    DP3 = 358,
    DP2 = 359,
    AVG = 360,
    ADD = 361,
    SEL = 362,
    AND = 363,
    OR = 364,
    XOR = 365,
    SHR = 366,
    SHL = 367,
    ASR = 368,
    CMP = 369,
    CMPN = 370,
    PLN = 371,
    ADDC = 372,
    BFI1 = 373,
    BFREV = 374,
    CBIT = 375,
    F16TO32 = 376,
    F32TO16 = 377,
    FBH = 378,
    FBL = 379,
    SEND = 380,
    SENDC = 381,
    NOP = 382,
    JMPI = 383,
    IF = 384,
    IFF = 385,
    WHILE = 386,
    ELSE = 387,
    BREAK = 388,
    CONT = 389,
    HALT = 390,
    MSAVE = 391,
    PUSH = 392,
    MREST = 393,
    POP = 394,
    WAIT = 395,
    DO = 396,
    ENDIF = 397,
    ILLEGAL = 398,
    MATH_INST = 399,
    MAD = 400,
    LRP = 401,
    BFE = 402,
    BFI2 = 403,
    SUBB = 404,
    CALL = 405,
    RET = 406,
    BRD = 407,
    BRC = 408,
    NULL_TOKEN = 409,
    MATH = 410,
    SAMPLER = 411,
    GATEWAY = 412,
    READ = 413,
    WRITE = 414,
    URB = 415,
    THREAD_SPAWNER = 416,
    VME = 417,
    DATA_PORT = 418,
    CRE = 419,
    MSGLEN = 420,
    RETURNLEN = 421,
    ALLOCATE = 422,
    USED = 423,
    COMPLETE = 424,
    TRANSPOSE = 425,
    INTERLEAVE = 426,
    SATURATE = 427,
    INTEGER = 428,
    STRING = 429,
    NUMBER = 430,
    INV = 431,
    LOG = 432,
    EXP = 433,
    SQRT = 434,
    RSQ = 435,
    POW = 436,
    SIN = 437,
    COS = 438,
    SINCOS = 439,
    INTDIV = 440,
    INTMOD = 441,
    INTDIVMOD = 442,
    SIGNED = 443,
    SCALAR = 444,
    X = 445,
    Y = 446,
    Z = 447,
    W = 448,
    KERNEL_PRAGMA = 449,
    END_KERNEL_PRAGMA = 450,
    CODE_PRAGMA = 451,
    END_CODE_PRAGMA = 452,
    REG_COUNT_PAYLOAD_PRAGMA = 453,
    REG_COUNT_TOTAL_PRAGMA = 454,
    DECLARE_PRAGMA = 455,
    BASE = 456,
    ELEMENTSIZE = 457,
    SRCREGION = 458,
    DSTREGION = 459,
    TYPE = 460,
    DEFAULT_EXEC_SIZE_PRAGMA = 461,
    DEFAULT_REG_TYPE_PRAGMA = 462,
    SUBREGNUM = 463,
    SNDOPR = 464,
    UMINUS = 465,
    STR_SYMBOL_REG = 466,
    EMPTEXECSIZE = 467
  };
#endif
/* Tokens.  */
#define COLON 258
#define SEMICOLON 259
#define LPAREN 260
#define RPAREN 261
#define LANGLE 262
#define RANGLE 263
#define LCURLY 264
#define RCURLY 265
#define LSQUARE 266
#define RSQUARE 267
#define COMMA 268
#define EQ 269
#define ABS 270
#define DOT 271
#define PLUS 272
#define MINUS 273
#define MULTIPLY 274
#define DIVIDE 275
#define TYPE_UD 276
#define TYPE_D 277
#define TYPE_UW 278
#define TYPE_W 279
#define TYPE_UB 280
#define TYPE_B 281
#define TYPE_VF 282
#define TYPE_HF 283
#define TYPE_V 284
#define TYPE_F 285
#define ALIGN1 286
#define ALIGN16 287
#define SECHALF 288
#define COMPR 289
#define SWITCH 290
#define ATOMIC 291
#define NODDCHK 292
#define NODDCLR 293
#define MASK_DISABLE 294
#define BREAKPOINT 295
#define ACCWRCTRL 296
#define EOT 297
#define SEQ 298
#define ANY2H 299
#define ALL2H 300
#define ANY4H 301
#define ALL4H 302
#define ANY8H 303
#define ALL8H 304
#define ANY16H 305
#define ALL16H 306
#define ANYV 307
#define ALLV 308
#define ZERO 309
#define EQUAL 310
#define NOT_ZERO 311
#define NOT_EQUAL 312
#define GREATER 313
#define GREATER_EQUAL 314
#define LESS 315
#define LESS_EQUAL 316
#define ROUND_INCREMENT 317
#define OVERFLOW 318
#define UNORDERED 319
#define GENREG 320
#define MSGREG 321
#define ADDRESSREG 322
#define ACCREG 323
#define FLAGREG 324
#define MASKREG 325
#define AMASK 326
#define IMASK 327
#define LMASK 328
#define CMASK 329
#define MASKSTACKREG 330
#define LMS 331
#define IMS 332
#define MASKSTACKDEPTHREG 333
#define IMSD 334
#define LMSD 335
#define NOTIFYREG 336
#define STATEREG 337
#define CONTROLREG 338
#define IPREG 339
#define GENREGFILE 340
#define MSGREGFILE 341
#define MOV 342
#define FRC 343
#define RNDU 344
#define RNDD 345
#define RNDE 346
#define RNDZ 347
#define NOT 348
#define LZD 349
#define MUL 350
#define MAC 351
#define MACH 352
#define LINE 353
#define SAD2 354
#define SADA2 355
#define DP4 356
#define DPH 357
#define DP3 358
#define DP2 359
#define AVG 360
#define ADD 361
#define SEL 362
#define AND 363
#define OR 364
#define XOR 365
#define SHR 366
#define SHL 367
#define ASR 368
#define CMP 369
#define CMPN 370
#define PLN 371
#define ADDC 372
#define BFI1 373
#define BFREV 374
#define CBIT 375
#define F16TO32 376
#define F32TO16 377
#define FBH 378
#define FBL 379
#define SEND 380
#define SENDC 381
#define NOP 382
#define JMPI 383
#define IF 384
#define IFF 385
#define WHILE 386
#define ELSE 387
#define BREAK 388
#define CONT 389
#define HALT 390
#define MSAVE 391
#define PUSH 392
#define MREST 393
#define POP 394
#define WAIT 395
#define DO 396
#define ENDIF 397
#define ILLEGAL 398
#define MATH_INST 399
#define MAD 400
#define LRP 401
#define BFE 402
#define BFI2 403
#define SUBB 404
#define CALL 405
#define RET 406
#define BRD 407
#define BRC 408
#define NULL_TOKEN 409
#define MATH 410
#define SAMPLER 411
#define GATEWAY 412
#define READ 413
#define WRITE 414
#define URB 415
#define THREAD_SPAWNER 416
#define VME 417
#define DATA_PORT 418
#define CRE 419
#define MSGLEN 420
#define RETURNLEN 421
#define ALLOCATE 422
#define USED 423
#define COMPLETE 424
#define TRANSPOSE 425
#define INTERLEAVE 426
#define SATURATE 427
#define INTEGER 428
#define STRING 429
#define NUMBER 430
#define INV 431
#define LOG 432
#define EXP 433
#define SQRT 434
#define RSQ 435
#define POW 436
#define SIN 437
#define COS 438
#define SINCOS 439
#define INTDIV 440
#define INTMOD 441
#define INTDIVMOD 442
#define SIGNED 443
#define SCALAR 444
#define X 445
#define Y 446
#define Z 447
#define W 448
#define KERNEL_PRAGMA 449
#define END_KERNEL_PRAGMA 450
#define CODE_PRAGMA 451
#define END_CODE_PRAGMA 452
#define REG_COUNT_PAYLOAD_PRAGMA 453
#define REG_COUNT_TOTAL_PRAGMA 454
#define DECLARE_PRAGMA 455
#define BASE 456
#define ELEMENTSIZE 457
#define SRCREGION 458
#define DSTREGION 459
#define TYPE 460
#define DEFAULT_EXEC_SIZE_PRAGMA 461
#define DEFAULT_REG_TYPE_PRAGMA 462
#define SUBREGNUM 463
#define SNDOPR 464
#define UMINUS 465
#define STR_SYMBOL_REG 466
#define EMPTEXECSIZE 467

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 437 "gram.y" /* yacc.c:1909  */

	char *string;
	int integer;
	double number;
	struct brw_program_instruction instruction;
	struct brw_program program;
	struct region region;
	struct regtype regtype;
	struct brw_reg reg;
	struct condition condition;
	struct predicate predicate;
	struct options options;
	struct declared_register symbol_reg;
	imm32_t imm32;

	struct src_operand src_operand;

#line 496 "gram.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_GRAM_H_INCLUDED  */
