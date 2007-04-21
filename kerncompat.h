#ifndef __KERNCOMPAT
#define __KERNCOMPAT
#define gfp_t int
#define get_cpu_var(p) (p)
#define __get_cpu_var(p) (p)
#define BITS_PER_LONG 64
#define __GFP_BITS_SHIFT 20
#define __GFP_BITS_MASK ((int)((1 << __GFP_BITS_SHIFT) - 1))
#define GFP_KERNEL 0
#define GFP_NOFS 0
#define __read_mostly
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define PAGE_SHIFT 12
#define ULONG_MAX       (~0UL)
#define BUG() abort()
#ifdef __CHECKER__
#define __force    __attribute__((force))
#define __bitwise__ __attribute__((bitwise))
#else
#define __force
#define __bitwise__
#endif

typedef unsigned int u32;
typedef u32 __u32;
typedef unsigned long long u64;
typedef unsigned char u8;
typedef unsigned short u16;

typedef unsigned long pgoff_t;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vma_shared { int prio_tree_node; };
struct vm_area_struct {
	unsigned long vm_pgoff;
	unsigned long vm_start;
	unsigned long vm_end;
	struct vma_shared shared;
};

struct page {
	unsigned long index;
};

static inline void preempt_enable(void) { do {; } while(0);}
static inline void preempt_disable(void) { do {; } while(0);}

#define BITOP_MASK(nr)		(1UL << ((nr) % BITS_PER_LONG))
#define BITOP_WORD(nr)		((nr) / BITS_PER_LONG)

/**
 * __set_bit - Set a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * Unlike set_bit(), this function is non-atomic and may be reordered.
 * If it's called on the same region of memory simultaneously, the effect
 * may be that only one operation succeeds.
 */
static inline void __set_bit(int nr, volatile unsigned long *addr)
{
	unsigned long mask = BITOP_MASK(nr);
	unsigned long *p = ((unsigned long *)addr) + BITOP_WORD(nr);

	*p  |= mask;
}

static inline void __clear_bit(int nr, volatile unsigned long *addr)
{
	unsigned long mask = BITOP_MASK(nr);
	unsigned long *p = ((unsigned long *)addr) + BITOP_WORD(nr);

	*p &= ~mask;
}

/**
 * test_bit - Determine whether a bit is set
 * @nr: bit number to test
 * @addr: Address to start counting from
 */
static inline int test_bit(int nr, const volatile unsigned long *addr)
{
	return 1UL & (addr[BITOP_WORD(nr)] >> (nr & (BITS_PER_LONG-1)));
}

#define BUG_ON(c) do { if (c) abort(); } while (0)

#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
	        (type *)( (char *)__mptr - __builtin_offsetof(type,member) );})

#define ENOMEM 5
#define EEXIST 6

#define __CHECK_ENDIAN__
#ifdef __CHECK_ENDIAN__
#define __bitwise __bitwise__
#else
#define __bitwise
#endif

typedef u16 __bitwise __le16;
typedef u16 __bitwise __be16;
typedef u32 __bitwise __le32;
typedef u32 __bitwise __be32;
typedef u64 __bitwise __le64;
typedef u64 __bitwise __be64;

#define cpu_to_le64(x) ((__force __le64)(u64)(x))
#define le64_to_cpu(x) ((__force u64)(__le64)(x))
#define cpu_to_le32(x) ((__force __le32)(u32)(x))
#define le32_to_cpu(x) ((__force u32)(__le32)(x))
#define cpu_to_le16(x) ((__force __le16)(u16)(x))
#define le16_to_cpu(x) ((__force u16)(__le16)(x))
#endif
