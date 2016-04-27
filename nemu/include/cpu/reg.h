#ifndef __REG_H__
#define __REG_H__


#include "common.h"
#include "../../lib-common/x86-inc/cpu.h"
#include "../../lib-common/x86-inc/mmu.h"



enum { R_EAX, R_ECX, R_EDX, R_EBX, R_ESP, R_EBP, R_ESI, R_EDI };
enum { R_AX, R_CX, R_DX, R_BX, R_SP, R_BP, R_SI, R_DI };
enum { R_AL, R_CL, R_DL, R_BL, R_AH, R_CH, R_DH, R_BH };

/* TODO: Re-organize the `CPU_state' structure to match the register
 * encoding scheme in i386 instruction format. For example, if we
 * access cpu.gpr[3]._16, we will get the `bx' register; if we access
 * cpu.gpr[1]._8[1], we will get the 'ch' register. Hint: Use `union'.
 * For more details about the register encoding scheme, see i386 manual.
 */

typedef union {
	struct {
		uint32_t CF : 1;
		uint32_t ONEF: 1;
		uint32_t PF : 1;	
		uint32_t    : 1;	
		uint32_t AF : 1;
		uint32_t    : 1;
		uint32_t ZF : 1;
		uint32_t SF : 1;
		uint32_t TF : 1;
		uint32_t IF : 1;
		uint32_t DF : 1;	
		uint32_t OF : 1;
		uint32_t OL : 1;
		uint32_t IP : 1;
		uint32_t ND : 1;
		uint32_t RF : 1;
		uint32_t	: 1;
		uint32_t VM : 1;	
		uint32_t	: 14;
	};
	uint32_t all_EFLAGS; 
}EFLAGS_t;

#define eax gpr[0]._32
#define ecx gpr[1]._32
#define edx gpr[2]._32
#define ebx gpr[3]._32
#define esp gpr[4]._32
#define ebp gpr[5]._32
#define esi gpr[6]._32
#define edi gpr[7]._32

#define ax gpr[0]._16
#define cx gpr[1]._16
#define dx gpr[2]._16
#define bx gpr[3]._16/*
#define sp gpr[4]._16
#define bp gpr[5]._16
#define si gpr[6]._16
#define di gpr[7]._16

#define ah gpr[0]._8[0]
#define al gpr[1]._8[1]
#define ch gpr[2]._8[0]
#define cl gpr[3]._8[1]
#define dh gpr[4]._8[0]
#define dl gpr[5]._8[1]
#define bh gpr[6]._8[0]
#define bl gpr[7]._8[1]
*/
typedef struct {

	union cpuUnion{
		uint32_t _32;
		uint16_t _16;
		uint8_t _8[2];
	} gpr[8];//, eax, ecx, edx, ebx, esp, ebp, esi,;w edi;
	/* Do NOT change the order of the GPRs' definitions. */
	
	struct {
		lnaddr_t base;
		size_t limit;
	} GDTR;
	
	union {
		struct {
			CR0 _0;
			CR0 _1;
			CR0 _2;
			CR3 _3;
		};
		uint32_t _[4];
	} cr;
	
	
	union {
		union {
			struct {
				struct {
					uint16_t rpl	:	2;
					uint16_t ti		:	1;
					uint16_t index	:	13;
				};
				SegDesc invi;
			};
			uint16_t _16;
		} sr[4];
		struct {
			uint16_t es	:	16;
			uint64_t	:	64;
		   	uint16_t cs	:	16;
			uint64_t	:	64;
		    uint16_t ss	:	16;
			uint64_t	:	64;
			uint16_t ds	:	16;
			uint64_t	:	64;
		};
	};
	
	swaddr_t eip;
	EFLAGS_t EFLAGS;

} CPU_state;

int get_pf(int a);

extern CPU_state cpu;

static inline int check_reg_index(int index) {
	assert(index >= 0 && index < 8);
	return index;
}

#define reg_l(index) (cpu.gpr[check_reg_index(index)]._32)
#define reg_w(index) (cpu.gpr[check_reg_index(index)]._16)
#define reg_b(index) (cpu.gpr[check_reg_index(index) & 0x3]._8[index >> 2])

static inline void init_reg() {
	cpu.EFLAGS.all_EFLAGS = 2;
	cpu.cr._[0] = 0;
}
extern const char* regsl[];
extern const char* regsw[];
extern const char* regsb[];

#endif
