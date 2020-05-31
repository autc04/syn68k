#ifndef _ccfuncs_h_
#define _ccfuncs_h_

/* This file contains fast versions of addb, addw, addl, subb, subw,
 * subl, cmpb, cmpw, and cmpl that compute cc bits using native
 * hardware.  If the current host has these functions, FAST_CC_FUNCS
 * will be defined.  The add and subtract functions return the sum or
 * difference, respectively.
 */

#ifdef _MSC_VER
    // MSVC won't understand the syntax.
    // Clang on Windows complains that it doesn't have enough free registers.
#define NO_FAST_CC_FUNCS
#endif

#if defined (i386) && !defined (NO_FAST_CC_FUNCS)

#if !defined (CCR_ELEMENT_8_BITS)
# warning "The fast i386 cc funcs assume CCR_ELEMENT_8_BITS is defined; punting them."
#else  /* defined (CCR_ELEMENT_8_BITS) */

/* Indicate that we have the fast inline functions. */
#define FAST_CC_FUNCS


static inline void
inline_cmpb_statep (CPUState *cpu_state_ptr, uint8 n1, uint8 n2)
{
  asm ("cmpb %b4,%b5\n\t"
       "setne %3\n\t"
       "sets %1\n\t"
       "setb %0\n\t"	/* setc */
       "seto %2"
       : "=m" (cpu_state_ptr->ccc), "=m" (cpu_state_ptr->ccn),
       "=m" (cpu_state_ptr->ccv), "=m" (cpu_state_ptr->ccnz)
       : "q" (n1), "qi" (n2)
       : "cc");
}
#define inline_cmpb(n1,n2) inline_cmpb_statep(cpu_state_ptr, n1, n2)

static inline void
inline_cmpw_statep (CPUState *cpu_state_ptr, uint16 n1, uint16 n2)
{
  asm ("cmpw %w4,%w5\n\t"
       "setne %3\n\t"
       "sets %1\n\t"
       "setb %0\n\t"	/* setc */
       "seto %2"
       : "=m" (cpu_state_ptr->ccc), "=m" (cpu_state_ptr->ccn),
       "=m" (cpu_state_ptr->ccv), "=m" (cpu_state_ptr->ccnz)
       : "g" (n1), "ri" (n2)
       : "cc");
}
#define inline_cmpw(n1,n2) inline_cmpw_statep(cpu_state_ptr, n1, n2)


/* This seems to be a popular instruction. */
static inline void
inline_cmpw_cz_statep (CPUState *cpu_state_ptr, uint16 n1, uint16 n2)
{
  asm ("cmpw %w2,%w3\n\t"
       "setne %1\n\t"
       "setb %0"	/* setc */
       : "=m" (cpu_state_ptr->ccc), "=m" (cpu_state_ptr->ccnz)
       : "g" (n1), "ri" (n2)
       : "cc");
}
#define inline_cmpw_cz(n1,n2) inline_cmpw_cz_statep(cpu_state_ptr, n1, n2)

static inline void
inline_cmpl_statep (CPUState *cpu_state_ptr, uint32 n1, uint32 n2)
{
  asm ("cmpl %4,%5\n\t"
       "setne %3\n\t"
       "sets %1\n\t"
       "setb %0\n\t"	/* setc */
       "seto %2"
       : "=m" (cpu_state_ptr->ccc), "=m" (cpu_state_ptr->ccn),
       "=m" (cpu_state_ptr->ccv), "=m" (cpu_state_ptr->ccnz)
       : "g" (n1), "ri" (n2)
       : "cc");
}
#define inline_cmpl(n1,n2) inline_cmpl_statep(cpu_state_ptr, n1, n2)


#define INLINE_ADDB_NOSWAP(n1, n2)					 \
  asm ("addb %b7,%b0\n\t"						 \
       "setne %5\n\t"							 \
       "sets %3\n\t"							 \
       "setb %1\n\t"	/* setc */					 \
       "seto %4\n\t"							 \
       "setb %2"	/* setc */					 \
       : "=g" (n2), "=m" (cpu_state_ptr->ccc), "=m" (cpu_state_ptr->ccx),		 \
       "=m" (cpu_state_ptr->ccn), "=m" (cpu_state_ptr->ccv), "=m" (cpu_state_ptr->ccnz) \
       : "0" (n2), "bi" (n1)						 \
       : "cc")

static inline uint8
inline_addb_statep (CPUState *cpu_state_ptr, uint8 n1, uint8 n2)
{
  INLINE_ADDB_NOSWAP (n1, n2);
  return n2;
}
#define inline_addb(n1,n2) inline_addb_statep(cpu_state_ptr, n1, n2)



#define INLINE_ADDW_NOSWAP(n1, n2)					 \
  asm ("addw %w7,%w0\n\t"						 \
       "setne %5\n\t"							 \
       "sets %3\n\t"							 \
       "setb %1\n\t"	/* setc */					 \
       "seto %4\n\t"							 \
       "setb %2"	/* setc */					 \
       : "=g" (n2), "=m" (cpu_state_ptr->ccc), "=m" (cpu_state_ptr->ccx),		 \
       "=m" (cpu_state_ptr->ccn), "=m" (cpu_state_ptr->ccv), "=m" (cpu_state_ptr->ccnz) \
       : "0" (n2), "ri" (n1)						 \
       : "cc")

static inline uint16
inline_addw_statep (CPUState *cpu_state_ptr, uint16 n1, uint16 n2)
{
  INLINE_ADDW_NOSWAP (n1, n2);
  return n2;
}
#define inline_addw(n1,n2) inline_addw_statep(cpu_state_ptr, n1, n2)



#define INLINE_ADDL_NOSWAP(n1, n2)					 \
  asm ("addl %k7,%k0\n\t"						 \
       "setne %5\n\t"							 \
       "sets %3\n\t"							 \
       "setb %1\n\t"	/* setc */					 \
       "seto %4\n\t"							 \
       "setb %2"	/* setc */					 \
       : "=g" (n2), "=m" (cpu_state_ptr->ccc), "=m" (cpu_state_ptr->ccx),		 \
       "=m" (cpu_state_ptr->ccn), "=m" (cpu_state_ptr->ccv), "=m" (cpu_state_ptr->ccnz) \
       : "0" (n2), "ri" (n1)						 \
       : "cc")

static inline uint32
inline_addl_statep (CPUState *cpu_state_ptr, uint32 n1, uint32 n2)
{
  INLINE_ADDL_NOSWAP (n1, n2);
  return n2;
}
#define inline_addl(n1,n2) inline_addl_statep(cpu_state_ptr, n1, n2)



#define INLINE_SUBB_NOSWAP(n1, n2)					 \
  asm ("subb %b7,%b0\n\t"						 \
       "setne %5\n\t"							 \
       "sets %3\n\t"							 \
       "setb %1\n\t"	/* setc */					 \
       "seto %4\n\t"							 \
       "setb %2"	/* setc */					 \
       : "=g" (n2), "=m" (cpu_state_ptr->ccc), "=m" (cpu_state_ptr->ccx),		 \
       "=m" (cpu_state_ptr->ccn), "=m" (cpu_state_ptr->ccv), "=m" (cpu_state_ptr->ccnz) \
       : "0" (n2), "bi" (n1)						 \
       : "cc")

static inline uint8
inline_subb_statep (CPUState *cpu_state_ptr, uint8 n1, uint8 n2)
{
  INLINE_SUBB_NOSWAP (n1, n2);
  return n2;
}
#define inline_subb(n1,n2) inline_subb_statep(cpu_state_ptr, n1, n2)


#define INLINE_SUBW_NOSWAP(n1, n2)					 \
  asm ("subw %w7,%w0\n\t"						 \
       "setne %5\n\t"							 \
       "sets %3\n\t"							 \
       "setb %1\n\t"	/* setc */					 \
       "seto %4\n\t"							 \
       "setb %2"	/* setc */					 \
       : "=g" (n2), "=m" (cpu_state_ptr->ccc), "=m" (cpu_state_ptr->ccx),		 \
       "=m" (cpu_state_ptr->ccn), "=m" (cpu_state_ptr->ccv), "=m" (cpu_state_ptr->ccnz) \
       : "0" (n2), "ri" (n1)						 \
       : "cc")

static inline uint16
inline_subw_statep (CPUState *cpu_state_ptr, uint16 n1, uint16 n2)
{
  INLINE_SUBW_NOSWAP (n1, n2);
  return n2;
}
#define inline_subw(n1,n2) inline_subw_statep(cpu_state_ptr, n1, n2)



#define INLINE_SUBL_NOSWAP(n1, n2)					 \
  asm ("subl %k7,%k0\n\t"						 \
       "setne %5\n\t"							 \
       "sets %3\n\t"							 \
       "setb %1\n\t"	/* setc */					 \
       "seto %4\n\t"							 \
       "setb %2"	/* setc */					 \
       : "=g" (n2), "=m" (cpu_state_ptr->ccc), "=m" (cpu_state_ptr->ccx),		 \
       "=m" (cpu_state_ptr->ccn), "=m" (cpu_state_ptr->ccv), "=m" (cpu_state_ptr->ccnz) \
       : "0" (n2), "ri" (n1)						 \
       : "cc")

static inline uint32
inline_subl_statep (CPUState *cpu_state_ptr, uint32 n1, uint32 n2)
{
  INLINE_SUBL_NOSWAP (n1, n2);
  return n2;
}
#define inline_subl(n1,n2) inline_subl_statep(cpu_state_ptr, n1, n2)


/* This function computes the c, n, v, and nz bits based on a byte.
 * c and v are always cleared, nz is set iff the byte is nonzero,
 * n is set iff the high bit of the byte is set.
 */
static inline void inline_compute_c_n_v_nz_byte_statep (CPUState *cpu_state_ptr, uint8 n)
{
  asm ("movb %b0,%h0\n\t"
       "andl $0x000080FF,%k0\n\t"
       "movl %k0,%1"
       : "=abcd" (n), "=m" (cpu_state_ptr->ccnz), "=m" (cpu_state_ptr->ccn),
       "=m" (cpu_state_ptr->ccc), "=m" (cpu_state_ptr->ccv)
       : "0" (n)
       : "cc");
}
#define inline_compute_c_n_v_nz_byte(n) inline_compute_c_n_v_nz_byte_statep(cpu_state_ptr, n)

/* This function computes the c, n, v, and nz bits based on a word.
 * c and v are always cleared, nz is set iff the word is nonzero,
 * n is set iff the high bit of the word is set.
 */
static inline void inline_compute_c_n_v_nz_word_statep(CPUState *cpu_state_ptr, uint16 n)
{
  asm ("orb %h0,%b0\n\t"
       "andl $0x000080FF,%k0\n\t"
       "movl %k0,%1"
       : "=abcd" (n), "=m" (cpu_state_ptr->ccnz), "=m" (cpu_state_ptr->ccn),
       "=m" (cpu_state_ptr->ccc), "=m" (cpu_state_ptr->ccv)
       : "0" (n)
       : "cc");
}
#define inline_compute_c_n_v_nz_word(n) inline_compute_c_n_v_nz_word_statep(cpu_state_ptr, n)


/* This function computes the c, n, v, and nz bits based on a long.
 * c and v are always cleared, nz is set iff the long is nonzero,
 * n is set iff the high bit of the long is set.
 */
#define inline_compute_c_n_v_nz_long(n)				\
  asm ("movl $0,%0\n\t"  /* movl is faster than movw. */	\
       "testl %k4,%k4\n\t"					\
       "setne %0\n\t"						\
       "sets %1"						\
       : "=m" (cpu_state_ptr->ccnz), "=m" (cpu_state_ptr->ccn),		\
       "=m" (cpu_state_ptr->ccc), "=m" (cpu_state_ptr->ccv)		\
       : "r" ((uint32)(n))					\
       : "cc")

#endif  /* defined (CCR_ELEMENT_8_BITS) */

#endif   /* i386 */

#endif  /* !_ccfuncs_h_ */
