/*
 * SPDX-License-Identifier: BSD-2-Clause-FreeBSD
 *
 * Copyright (c) 2016-2022 Kean Johnston.
 * Copyright (c) 2017 Dell EMC.
 * Copyright (c) 2000, 2001, 2008, 2011, David E. O'Brien.
 * Copyright (c) 1996-1998 John D. Polstra.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#ifndef _ELF_HDR_
#define _ELF_HDR_

#include <stdint.h>

/*
 * ELF data types.
 */
typedef uint32_t	Elf32_Addr;
typedef uint64_t	Elf64_Addr;

typedef uint32_t	Elf32_Off;
typedef uint64_t	Elf64_Off;

typedef uint16_t	Elf32_Half;
typedef uint16_t	Elf64_Half;

typedef int32_t		Elf32_Sword;
typedef int32_t		Elf64_Sword;

typedef uint32_t	Elf32_Word;
typedef uint32_t	Elf64_Word;

typedef uint64_t	Elf32_Lword;
typedef uint64_t	Elf64_Lword;

typedef int64_t		Elf64_Sxword;
typedef uint64_t	Elf64_Xword;

typedef Elf32_Word	Elf32_Hashelt;
typedef Elf64_Word	Elf64_Hashelt;

/* Non-standard class-dependent datatype used for abstraction. */
typedef Elf32_Word	Elf32_Size;
typedef Elf64_Xword	Elf64_Size;

typedef Elf32_Sword	Elf32_Ssize;
typedef Elf64_Sxword	Elf64_Ssize;

/*
 * ELF header.
 */
#define	EI_NIDENT	16	/* Size of e_ident array. */

typedef struct {
	unsigned char	e_ident[EI_NIDENT];	/* File identification. */
	Elf32_Half	e_type;		/* File type. */
	Elf32_Half	e_machine;	/* Machine architecture. */
	Elf32_Word	e_version;	/* ELF format version. */
	Elf32_Addr	e_entry;	/* Entry point. */
	Elf32_Off	e_phoff;	/* Program header file offset. */
	Elf32_Off	e_shoff;	/* Section header file offset. */
	Elf32_Word	e_flags;	/* Architecture-specific flags. */
	Elf32_Half	e_ehsize;	/* Size of ELF header in bytes. */
	Elf32_Half	e_phentsize;	/* Size of program header entry. */
	Elf32_Half	e_phnum;	/* Number of program header entries. */
	Elf32_Half	e_shentsize;	/* Size of section header entry. */
	Elf32_Half	e_shnum;	/* Number of section header entries. */
	Elf32_Half	e_shstrndx;	/* Section name strings section. */
} Elf32_Ehdr;

typedef struct {
	unsigned char	e_ident[EI_NIDENT];	/* File identification. */
	Elf64_Half	e_type;		/* File type. */
	Elf64_Half	e_machine;	/* Machine architecture. */
	Elf64_Word	e_version;	/* ELF format version. */
	Elf64_Addr	e_entry;	/* Entry point. */
	Elf64_Off	e_phoff;	/* Program header file offset. */
	Elf64_Off	e_shoff;	/* Section header file offset. */
	Elf64_Word	e_flags;	/* Architecture-specific flags. */
	Elf64_Half	e_ehsize;	/* Size of ELF header in bytes. */
	Elf64_Half	e_phentsize;	/* Size of program header entry. */
	Elf64_Half	e_phnum;	/* Number of program header entries. */
	Elf64_Half	e_shentsize;	/* Size of section header entry. */
	Elf64_Half	e_shnum;	/* Number of section header entries. */
	Elf64_Half	e_shstrndx;	/* Section name strings section. */
} Elf64_Ehdr;

/* Indexes into the e_ident array.  Keep synced with
   http://www.sco.com/developers/gabi/latest/ch4.eheader.html */
#define	EI_MAG0		0	/* Magic number, byte 0. */
#define	EI_MAG1		1	/* Magic number, byte 1. */
#define	EI_MAG2		2	/* Magic number, byte 2. */
#define	EI_MAG3		3	/* Magic number, byte 3. */
#define	EI_CLASS	4	/* Class of machine. */
#define	EI_DATA		5	/* Data format. */
#define	EI_VERSION	6	/* ELF format version. */
#define	EI_OSABI	7	/* Operating system / ABI identification */
#define	EI_ABIVERSION	8	/* ABI version */
#define	OLD_EI_BRAND	8	/* Start of architecture identification. */
#define	EI_PAD		9	/* Start of padding (per SVR4 ABI). */

/* Values for the magic number bytes. */
#define	ELFMAG0		0x7f
#define	ELFMAG1		'E'
#define	ELFMAG2		'L'
#define	ELFMAG3		'F'
#define	ELFMAG		"\177ELF"	/* magic string */
#define	SELFMAG		4		/* magic string size */

/* Values for e_ident[EI_VERSION] and e_version. */
#define	EV_NONE		0
#define	EV_CURRENT	1

/* Values for e_ident[EI_CLASS]. */
#define	ELFCLASSNONE	0	/* Unknown class. */
#define	ELFCLASS32	1	/* 32-bit architecture. */
#define	ELFCLASS64	2	/* 64-bit architecture. */

/* Values for e_ident[EI_DATA]. */
#define	ELFDATANONE	0	/* Unknown data format. */
#define	ELFDATA2LSB	1	/* 2's complement little-endian. */
#define	ELFDATA2MSB	2	/* 2's complement big-endian. */

/* Values for e_ident[EI_OSABI]. */
#define	ELFOSABI_NONE		0	/* UNIX System V ABI */
#define	ELFOSABI_HPUX		1	/* HP-UX operating system */
#define	ELFOSABI_NETBSD		2	/* NetBSD */
#define	ELFOSABI_LINUX		3	/* GNU/Linux */
#define	ELFOSABI_HURD		4	/* GNU/Hurd */
#define	ELFOSABI_86OPEN		5	/* 86Open common IA32 ABI */
#define	ELFOSABI_SOLARIS	6	/* Solaris */
#define	ELFOSABI_AIX		7	/* AIX */
#define	ELFOSABI_IRIX		8	/* IRIX */
#define	ELFOSABI_FREEBSD	9	/* FreeBSD */
#define	ELFOSABI_TRU64		10	/* TRU64 UNIX */
#define	ELFOSABI_MODESTO	11	/* Novell Modesto */
#define	ELFOSABI_OPENBSD	12	/* OpenBSD */
#define	ELFOSABI_OPENVMS	13	/* Open VMS */
#define	ELFOSABI_NSK		14	/* HP Non-Stop Kernel */
#define	ELFOSABI_AROS		15	/* Amiga Research OS */
#define	ELFOSABI_FENIXOS	16	/* FenixOS */
#define	ELFOSABI_CLOUDABI	17	/* Nuxi CloudABI */
#define	ELFOSABI_ARM_AEABI	64	/* ARM EABI */
#define	ELFOSABI_ARM		97	/* ARM */
#define	ELFOSABI_STANDALONE	255	/* Standalone (embedded) application */

#define	ELFOSABI_SYSV		ELFOSABI_NONE	/* symbol used in old spec */
#define	ELFOSABI_MONTEREY	ELFOSABI_AIX	/* Monterey */
#define	ELFOSABI_GNU		ELFOSABI_LINUX

/* e_ident */
#define	IS_ELF(ehdr)	((ehdr).e_ident[EI_MAG0] == ELFMAG0 && \
			 (ehdr).e_ident[EI_MAG1] == ELFMAG1 && \
			 (ehdr).e_ident[EI_MAG2] == ELFMAG2 && \
			 (ehdr).e_ident[EI_MAG3] == ELFMAG3)

/* Values for e_type. */
#define	ET_NONE		0	/* Unknown type. */
#define	ET_REL		1	/* Relocatable. */
#define	ET_EXEC		2	/* Executable. */
#define	ET_DYN		3	/* Shared object. */
#define	ET_CORE		4	/* Core file. */
#define	ET_LOOS		0xfe00	/* First operating system specific. */
#define	ET_HIOS		0xfeff	/* Last operating system-specific. */
#define	ET_LOPROC	0xff00	/* First processor-specific. */
#define	ET_HIPROC	0xffff	/* Last processor-specific. */

/* Values for e_machine. */
#define	EM_NONE		0	/* Unknown machine. */
#define	EM_M32		1	/* AT&T WE32100. */
#define	EM_SPARC	2	/* Sun SPARC. */
#define	EM_386		3	/* Intel i386. */
#define	EM_68K		4	/* Motorola 68000. */
#define	EM_88K		5	/* Motorola 88000. */
#define	EM_IAMCU	6	/* Intel MCU. */
#define	EM_860		7	/* Intel i860. */
#define	EM_MIPS		8	/* MIPS R3000 Big-Endian only. */
#define	EM_S370		9	/* IBM System/370. */
#define	EM_MIPS_RS3_LE	10	/* MIPS R3000 Little-Endian. */
#define	EM_PARISC	15	/* HP PA-RISC. */
#define	EM_VPP500	17	/* Fujitsu VPP500. */
#define	EM_SPARC32PLUS	18	/* SPARC v8plus. */
#define	EM_960		19	/* Intel 80960. */
#define	EM_PPC		20	/* PowerPC 32-bit. */
#define	EM_PPC64	21	/* PowerPC 64-bit. */
#define	EM_S390		22	/* IBM System/390. */
#define EM_SPU		23	/* IBM SPU/SPC */
#define	EM_V800		36	/* NEC V800. */
#define	EM_FR20		37	/* Fujitsu FR20. */
#define	EM_RH32		38	/* TRW RH-32. */
#define	EM_RCE		39	/* Motorola RCE. */
#define	EM_ARM		40	/* ARM. */
#define	EM_SH		42	/* Hitachi SH. */
#define	EM_SPARCV9	43	/* SPARC v9 64-bit. */
#define	EM_TRICORE	44	/* Siemens TriCore embedded processor. */
#define	EM_ARC		45	/* Argonaut RISC Core. */
#define	EM_H8_300	46	/* Hitachi H8/300. */
#define	EM_H8_300H	47	/* Hitachi H8/300H. */
#define	EM_H8S		48	/* Hitachi H8S. */
#define	EM_H8_500	49	/* Hitachi H8/500. */
#define	EM_IA_64	50	/* Intel IA-64 Processor. */
#define	EM_MIPS_X	51	/* Stanford MIPS-X. */
#define	EM_COLDFIRE	52	/* Motorola ColdFire. */
#define	EM_68HC12	53	/* Motorola M68HC12. */
#define	EM_MMA		54	/* Fujitsu MMA. */
#define	EM_PCP		55	/* Siemens PCP. */
#define	EM_NCPU		56	/* Sony nCPU. */
#define	EM_NDR1		57	/* Denso NDR1 microprocessor. */
#define	EM_STARCORE	58	/* Motorola Star*Core processor. */
#define	EM_ME16		59	/* Toyota ME16 processor. */
#define	EM_ST100	60	/* STMicroelectronics ST100 processor. */
#define	EM_TINYJ	61	/* Advanced Logic Corp. TinyJ processor. */
#define	EM_X86_64	62	/* Advanced Micro Devices x86-64 */
#define	EM_AMD64	EM_X86_64
#define	EM_PDSP		63	/* Sony DSP Processor. */
#define EM_PDP10	64	/* Digital PDP-10 */
#define EM_PDP11	65	/* Digital PDP-11 */
#define	EM_FX66		66	/* Siemens FX66 microcontroller. */
#define	EM_ST9PLUS	67	/* STMicroelectronics ST9+ 8/16 microcontroller. */
#define	EM_ST7		68	/* STmicroelectronics ST7 8-bit microcontroller. */
#define	EM_68HC16	69	/* Motorola MC68HC16 microcontroller. */
#define	EM_68HC11	70	/* Motorola MC68HC11 microcontroller. */
#define	EM_68HC08	71	/* Motorola MC68HC08 microcontroller. */
#define	EM_68HC05	72	/* Motorola MC68HC05 microcontroller. */
#define	EM_SVX		73	/* Silicon Graphics SVx. */
#define	EM_ST19		74	/* STMicroelectronics ST19 8-bit mc. */
#define	EM_VAX		75	/* Digital VAX. */
#define	EM_CRIS		76	/* Axis Communications 32-bit embedded processor. */
#define	EM_JAVELIN	77	/* Infineon Technologies 32-bit embedded processor. */
#define	EM_FIREPATH	78	/* Element 14 64-bit DSP Processor. */
#define	EM_ZSP		79	/* LSI Logic 16-bit DSP Processor. */
#define	EM_MMIX		80	/* Donald Knuth's educational 64-bit proc. */
#define	EM_HUANY	81	/* Harvard University machine-independent object files. */
#define	EM_PRISM	82	/* SiTera Prism. */
#define	EM_AVR		83	/* Atmel AVR 8-bit microcontroller. */
#define	EM_FR30		84	/* Fujitsu FR30. */
#define	EM_D10V		85	/* Mitsubishi D10V. */
#define	EM_D30V		86	/* Mitsubishi D30V. */
#define	EM_V850		87	/* NEC v850. */
#define	EM_M32R		88	/* Mitsubishi M32R. */
#define	EM_MN10300	89	/* Matsushita MN10300. */
#define	EM_MN10200	90	/* Matsushita MN10200. */
#define	EM_PJ		91	/* picoJava. */
#define	EM_OPENRISC	92	/* OpenRISC 32-bit embedded processor. */
#define	EM_ARC_A5	93	/* ARC Cores Tangent-A5. */
#define	EM_XTENSA	94	/* Tensilica Xtensa Architecture. */
#define	EM_VIDEOCORE	95	/* Alphamosaic VideoCore processor. */
#define	EM_TMM_GPP	96	/* Thompson Multimedia General Purpose Processor. */
#define	EM_NS32K	97	/* National Semiconductor 32000 series. */
#define	EM_TPC		98	/* Tenor Network TPC processor. */
#define	EM_SNP1K	99	/* Trebia SNP 1000 processor. */
#define	EM_ST200	100	/* STMicroelectronics ST200 microcontroller. */
#define	EM_IP2K		101	/* Ubicom IP2xxx microcontroller family. */
#define	EM_MAX		102	/* MAX Processor. */
#define	EM_CR		103	/* National Semiconductor CompactRISC microprocessor. */
#define	EM_F2MC16	104	/* Fujitsu F2MC16. */
#define	EM_MSP430	105	/* Texas Instruments embedded microcontroller msp430. */
#define	EM_BLACKFIN	106	/* Analog Devices Blackfin (DSP) processor. */
#define	EM_SE_C33	107	/* S1C33 Family of Seiko Epson processors. */
#define	EM_SEP		108	/* Sharp embedded microprocessor. */
#define	EM_ARCA		109	/* Arca RISC Microprocessor. */
#define	EM_UNICORE	110	/* Microprocessor series from PKU-Unity Ltd.  and MPRC of Peking University */
#define EM_EXCESS	111	/* eXcess configurable cpu */
#define EM_DXP		112	/* Icera Semi. Deep Execution Processor */
#define EM_ALTERA_NIOS2 113	/* Altera Nios II */
#define EM_CRX		114	/* National Semi. CompactRISC CRX */
#define EM_XGATE	115	/* Motorola XGATE */
#define EM_C166		116	/* Infineon C16x/XC16x */
#define EM_M16C		117	/* Renesas M16C */
#define EM_DSPIC30F	118	/* Microchip Technology dsPIC30F */
#define EM_CE		119	/* Freescale Communication Engine RISC */
#define EM_M32C		120	/* Renesas M32C */
#define EM_TSK3000	131	/* Altium TSK3000 */
#define EM_RS08		132	/* Freescale RS08 */
#define EM_SHARC	133	/* Analog Devices SHARC family */
#define EM_ECOG2	134	/* Cyan Technology eCOG2 */
#define EM_SCORE7	135	/* Sunplus S+core7 RISC */
#define EM_DSP24	136	/* New Japan Radio (NJR) 24-bit DSP */
#define EM_VIDEOCORE3	137	/* Broadcom VideoCore III */
#define EM_LATTICEMICO32 138	/* RISC for Lattice FPGA */
#define EM_SE_C17	139	/* Seiko Epson C17 */
#define EM_TI_C6000	140	/* Texas Instruments TMS320C6000 DSP */
#define EM_TI_C2000	141	/* Texas Instruments TMS320C2000 DSP */
#define EM_TI_C5500	142	/* Texas Instruments TMS320C55x DSP */
#define EM_TI_ARP32	143	/* Texas Instruments App. Specific RISC */
#define EM_TI_PRU	144	/* Texas Instruments Prog. Realtime Unit */
#define EM_MMDSP_PLUS	160	/* STMicroelectronics 64bit VLIW DSP */
#define EM_CYPRESS_M8C	161	/* Cypress M8C */
#define EM_R32C		162	/* Renesas R32C */
#define EM_TRIMEDIA	163	/* NXP Semi. TriMedia */
#define EM_QDSP6	164	/* QUALCOMM DSP6 */
#define EM_8051		165	/* Intel 8051 and variants */
#define EM_STXP7X	166	/* STMicroelectronics STxP7x */
#define EM_NDS32	167	/* Andes Tech. compact code emb. RISC */
#define EM_ECOG1X	168	/* Cyan Technology eCOG1X */
#define EM_MAXQ30	169	/* Dallas Semi. MAXQ30 mc */
#define EM_XIMO16	170	/* New Japan Radio (NJR) 16-bit DSP */
#define EM_MANIK	171	/* M2000 Reconfigurable RISC */
#define EM_CRAYNV2	172	/* Cray NV2 vector architecture */
#define EM_RX		173	/* Renesas RX */
#define EM_METAG	174	/* Imagination Tech. META */
#define EM_MCST_ELBRUS	175	/* MCST Elbrus */
#define EM_ECOG16	176	/* Cyan Technology eCOG16 */
#define EM_CR16		177	/* National Semi. CompactRISC CR16 */
#define EM_ETPU		178	/* Freescale Extended Time Processing Unit */
#define EM_SLE9X	179	/* Infineon Tech. SLE9X */
#define EM_L10M		180	/* Intel L10M */
#define EM_K10M		181	/* Intel K10M */
#define	EM_AARCH64	183	/* AArch64 (64-bit ARM) */
#define EM_AVR32	185	/* Amtel 32-bit microprocessor */
#define EM_STM8		186	/* STMicroelectronics STM8 */
#define EM_TILE64	187	/* Tileta TILE64 */
#define EM_TILEPRO	188	/* Tilera TILEPro */
#define EM_MICROBLAZE	189	/* Xilinx MicroBlaze */
#define EM_CUDA		190	/* NVIDIA CUDA */
#define EM_TILEGX	191	/* Tilera TILE-Gx */
#define EM_CLOUDSHIELD	192	/* CloudShield */
#define EM_COREA_1ST	193	/* KIPO-KAIST Core-A 1st gen. */
#define EM_COREA_2ND	194	/* KIPO-KAIST Core-A 2nd gen. */
#define EM_ARC_COMPACT2	195	/* Synopsys ARCompact V2 */
#define EM_OPEN8	196	/* Open8 RISC */
#define EM_RL78		197	/* Renesas RL78 */
#define EM_VIDEOCORE5	198	/* Broadcom VideoCore V */
#define EM_78KOR	199	/* Renesas 78KOR */
#define EM_56800EX	200	/* Freescale 56800EX DSC */
#define EM_BA1		201	/* Beyond BA1 */
#define EM_BA2		202	/* Beyond BA2 */
#define EM_XCORE	203	/* XMOS xCORE */
#define EM_MCHP_PIC	204	/* Microchip 8-bit PIC(r) */
#define EM_KM32		210	/* KM211 KM32 */
#define EM_KMX32	211	/* KM211 KMX32 */
#define EM_EMX16	212	/* KM211 KMX16 */
#define EM_EMX8		213	/* KM211 KMX8 */
#define EM_KVARC	214	/* KM211 KVARC */
#define EM_CDP		215	/* Paneve CDP */
#define EM_COGE		216	/* Cognitive Smart Memory Processor */
#define EM_COOL		217	/* Bluechip CoolEngine */
#define EM_NORC		218	/* Nanoradio Optimized RISC */
#define EM_CSR_KALIMBA	219	/* CSR Kalimba */
#define EM_Z80		220	/* Zilog Z80 */
#define EM_VISIUM	221	/* Controls and Data Services VISIUMcore */
#define EM_FT32		222	/* FTDI Chip FT32 */
#define EM_MOXIE	223	/* Moxie processor */
#define EM_AMDGPU	224	/* AMD GPU */
#define	EM_RISCV	243	/* RISC-V */
#define EM_BPF		247	/* Linux BPF -- in-kernel virtual machine */

/* Non-standard or deprecated. */
#define	EM_486		6	/* Intel i486. */
#define	EM_MIPS_RS4_BE	10	/* MIPS R4000 Big-Endian */
#define	EM_ALPHA_STD	41	/* Digital Alpha (standard value). */
#define	EM_ALPHA	0x9026	/* Alpha (written in the absence of an ABI) */

/**
 * e_flags
 */
#define	EF_ARM_RELEXEC		0x00000001
#define	EF_ARM_HASENTRY		0x00000002
#define	EF_ARM_SYMSARESORTED	0x00000004
#define	EF_ARM_DYNSYMSUSESEGIDX	0x00000008
#define	EF_ARM_MAPSYMSFIRST	0x00000010
#define	EF_ARM_LE8		0x00400000
#define	EF_ARM_BE8		0x00800000
#define	EF_ARM_EABIMASK		0xFF000000
#define	EF_ARM_EABI_UNKNOWN	0x00000000
#define	EF_ARM_EABI_VER1	0x01000000
#define	EF_ARM_EABI_VER2	0x02000000
#define	EF_ARM_EABI_VER3	0x03000000
#define	EF_ARM_EABI_VER4	0x04000000
#define	EF_ARM_EABI_VER5	0x05000000
#define	EF_ARM_INTERWORK	0x00000004
#define	EF_ARM_APCS_26		0x00000008
#define	EF_ARM_APCS_FLOAT	0x00000010
#define	EF_ARM_PIC		0x00000020
#define	EF_ARM_ALIGN8		0x00000040
#define	EF_ARM_NEW_ABI		0x00000080
#define	EF_ARM_OLD_ABI		0x00000100
#define	EF_ARM_SOFT_FLOAT	0x00000200
#define	EF_ARM_VFP_FLOAT	0x00000400
#define	EF_ARM_MAVERICK_FLOAT	0x00000800

#define	EF_MIPS_NOREORDER	0x00000001
#define	EF_MIPS_PIC		0x00000002	/* Contains PIC code */
#define	EF_MIPS_CPIC		0x00000004	/* STD PIC calling sequence */
#define	EF_MIPS_UCODE		0x00000010
#define	EF_MIPS_ABI2		0x00000020	/* N32 */
#define	EF_MIPS_OPTIONS_FIRST	0x00000080
#define	EF_MIPS_ARCH_ASE	0x0F000000	/* Architectural extensions */
#define	EF_MIPS_ARCH_ASE_MDMX	0x08000000	/* MDMX multimedia extension */
#define	EF_MIPS_ARCH_ASE_M16	0x04000000	/* MIPS-16 ISA extensions */
#define	EF_MIPS_ARCH		0xF0000000	/* Architecture field */

#define	EF_PPC_EMB		0x80000000
#define	EF_PPC_RELOCATABLE	0x00010000
#define	EF_PPC_RELOCATABLE_LIB	0x00008000

#define	EF_SPARC_EXT_MASK	0x00ffff00
#define	EF_SPARC_32PLUS		0x00000100
#define	EF_SPARC_SUN_US1	0x00000200
#define	EF_SPARC_HAL_R1		0x00000200
#define	EF_SPARC_SUN_US3	0x00000800

#define	EF_SPARCV9_MM		0x00000003
#define	EF_SPARCV9_TSO		0x00000000
#define	EF_SPARCV9_PSO		0x00000001
#define	EF_SPARCV9_RMO		0x00000002

/*
 * Shared object information.
 */
typedef struct {
	Elf32_Word l_name;		/* The name of a shared object. */
	Elf32_Word l_time_stamp;	/* 32-bit timestamp. */
	Elf32_Word l_checksum;		/* Checksum of visible symbols, sizes. */
	Elf32_Word l_version;		/* Interface version string index. */
	Elf32_Word l_flags;		/* Flags (LL_*). */
} Elf32_Lib;

typedef struct {
	Elf64_Word l_name;		/* The name of a shared object. */
	Elf64_Word l_time_stamp;	/* 64-bit timestamp. */
	Elf64_Word l_checksum;		/* Checksum of visible symbols, sizes. */
	Elf64_Word l_version;		/* Interface version string index. */
	Elf64_Word l_flags;		/* Flags (LL_*). */
} Elf64_Lib;

/* Values for l_flags. */
#define	LL_NONE			0x0000	/* no flags */
#define	LL_EXACT_MATCH		0x0001	/* require an exact match */
#define	LL_IGNORE_INT_VER	0x0002	/* ignore version incompatibilities */
#define	LL_REQUIRE_MINOR	0x0004
#define	LL_EXPORTS		0x0008
#define	LL_DELAY_LOAD		0x0010
#define	LL_DELTA		0x0020

/*
 * Section header.
 */
typedef struct {
	Elf32_Word	sh_name;	/* Section name (index into the section header string table). */
	Elf32_Word	sh_type;	/* Section type. */
	Elf32_Word	sh_flags;	/* Section flags. */
	Elf32_Addr	sh_addr;	/* Address in memory image. */
	Elf32_Off	sh_offset;	/* Offset in file. */
	Elf32_Word	sh_size;	/* Size in bytes. */
	Elf32_Word	sh_link;	/* Index of a related section. */
	Elf32_Word	sh_info;	/* Depends on section type. */
	Elf32_Word	sh_addralign;	/* Alignment in bytes. */
	Elf32_Word	sh_entsize;	/* Size of each entry in section. */
} Elf32_Shdr;

typedef struct {
	Elf64_Word	sh_name;	/* Section name (index into the section header string table). */
	Elf64_Word	sh_type;	/* Section type. */
	Elf64_Xword	sh_flags;	/* Section flags. */
	Elf64_Addr	sh_addr;	/* Address in memory image. */
	Elf64_Off	sh_offset;	/* Offset in file. */
	Elf64_Xword	sh_size;	/* Size in bytes. */
	Elf64_Word	sh_link;	/* Index of a related section. */
	Elf64_Word	sh_info;	/* Depends on section type. */
	Elf64_Xword	sh_addralign;	/* Alignment in bytes. */
	Elf64_Xword	sh_entsize;	/* Size of each entry in section. */
} Elf64_Shdr;

/* Special section indexes. */
#define	SHN_UNDEF	0x0000		/* Undefined, missing, irrelevant. */
#define	SHN_LORESERVE	0xff00		/* First of reserved range. */
#define	SHN_LOPROC	0xff00		/* First processor-specific. */
#define SHN_BEFORE	0xff00		/* Order before (Solaris). */
#define SHN_AFTER	0xff01		/* Order after (Solaris). */
#define	SHN_HIPROC	0xff1f		/* Last processor-specific. */
#define	SHN_LOOS	0xff20		/* First operating system-specific. */
#define	SHN_HIOS	0xff3f		/* Last operating system-specific. */
#define	SHN_ABS		0xfff1		/* Absolute values. */
#define	SHN_COMMON	0xfff2		/* Common data. */
#define	SHN_XINDEX	0xffff		/* Escape -- index stored elsewhere. */
#define	SHN_HIRESERVE	0xffff		/* Last of reserved range. */

/* sh_type */
#define	SHT_NULL		0	/* inactive */
#define	SHT_PROGBITS		1	/* program defined information */
#define	SHT_SYMTAB		2	/* symbol table section */
#define	SHT_STRTAB		3	/* string table section */
#define	SHT_RELA		4	/* relocation section with addends */
#define	SHT_HASH		5	/* symbol hash table section */
#define	SHT_DYNAMIC		6	/* dynamic section */
#define	SHT_NOTE		7	/* note section */
#define	SHT_NOBITS		8	/* no space section */
#define	SHT_REL			9	/* relocation section - no addends */
#define	SHT_SHLIB		10	/* reserved - purpose unknown */
#define	SHT_DYNSYM		11	/* dynamic symbol table section */
#define	SHT_INIT_ARRAY		14	/* Initialization function pointers. */
#define	SHT_FINI_ARRAY		15	/* Termination function pointers. */
#define	SHT_PREINIT_ARRAY	16	/* Pre-initialization function ptrs. */
#define	SHT_GROUP		17	/* Section group. */
#define	SHT_SYMTAB_SHNDX	18	/* Section indexes (see SHN_XINDEX). */
#define	SHT_LOOS		0x60000000	/* First of OS specific semantics */
#define	SHT_LOSUNW		0x6ffffff4
#define	SHT_SUNW_dof		0x6ffffff4
#define	SHT_SUNW_cap		0x6ffffff5
#define	SHT_GNU_ATTRIBUTES	0x6ffffff5
#define	SHT_SUNW_SIGNATURE	0x6ffffff6
#define	SHT_GNU_HASH		0x6ffffff6
#define	SHT_GNU_LIBLIST		0x6ffffff7
#define	SHT_SUNW_ANNOTATE	0x6ffffff7
#define	SHT_SUNW_DEBUGSTR	0x6ffffff8
#define SHT_CHECKSUM	  	0x6ffffff8
#define	SHT_SUNW_DEBUG		0x6ffffff9
#define	SHT_SUNW_move		0x6ffffffa
#define	SHT_SUNW_COMDAT		0x6ffffffb
#define	SHT_SUNW_syminfo	0x6ffffffc
#define	SHT_SUNW_verdef		0x6ffffffd
#define	SHT_GNU_verdef		0x6ffffffd	/* Symbol versions provided */
#define	SHT_SUNW_verneed	0x6ffffffe
#define	SHT_GNU_verneed		0x6ffffffe	/* Symbol versions required */
#define	SHT_SUNW_versym		0x6fffffff
#define	SHT_GNU_versym		0x6fffffff	/* Symbol version table */
#define	SHT_HISUNW		0x6fffffff
#define	SHT_HIOS		0x6fffffff	/* Last of OS specific semantics */
#define	SHT_LOPROC		0x70000000	/* reserved range for processor */
#define	SHT_X86_64_UNWIND	0x70000001	/* unwind information */
#define	SHT_AMD64_UNWIND	SHT_X86_64_UNWIND 

#define	SHT_ARM_EXIDX		0x70000001	/* Exception index table. */
#define	SHT_ARM_PREEMPTMAP	0x70000002	/* BPABI DLL dynamic linking pre-emption map. */
#define	SHT_ARM_ATTRIBUTES	0x70000003	/* Object file compatibility attributes. */
#define	SHT_ARM_DEBUGOVERLAY	0x70000004	/* See DBGOVL for details. */
#define	SHT_ARM_OVERLAYSECTION	0x70000005	/* See DBGOVL for details. */
#define	SHT_MIPS_LIBLIST	0x70000000
#define	SHT_MIPS_MSYM		0x70000001
#define	SHT_MIPS_CONFLICT	0x70000002
#define	SHT_MIPS_GPTAB		0x70000003
#define	SHT_MIPS_UCODE		0x70000004
#define	SHT_MIPS_DEBUG		0x70000005
#define	SHT_MIPS_REGINFO	0x70000006
#define	SHT_MIPS_PACKAGE	0x70000007
#define	SHT_MIPS_PACKSYM	0x70000008
#define	SHT_MIPS_RELD		0x70000009
#define	SHT_MIPS_IFACE		0x7000000b
#define	SHT_MIPS_CONTENT	0x7000000c
#define	SHT_MIPS_OPTIONS	0x7000000d
#define	SHT_MIPS_DELTASYM	0x7000001b
#define	SHT_MIPS_DELTAINST	0x7000001c
#define	SHT_MIPS_DELTACLASS	0x7000001d
#define	SHT_MIPS_DWARF		0x7000001e	/* MIPS gcc uses MIPS_DWARF */
#define	SHT_MIPS_DELTADECL	0x7000001f
#define	SHT_MIPS_SYMBOL_LIB	0x70000020
#define	SHT_MIPS_EVENTS		0x70000021
#define	SHT_MIPS_TRANSLATE	0x70000022
#define	SHT_MIPS_PIXIE		0x70000023
#define	SHT_MIPS_XLATE		0x70000024
#define	SHT_MIPS_XLATE_DEBUG	0x70000025
#define	SHT_MIPS_WHIRL		0x70000026
#define	SHT_MIPS_EH_REGION	0x70000027
#define	SHT_MIPS_XLATE_OLD	0x70000028
#define	SHT_MIPS_PDR_EXCEPTION	0x70000029
#define	SHT_MIPS_ABIFLAGS	0x7000002a

#define	SHT_SPARC_GOTDATA	0x70000000

#define	SHTORDERED
#define	SHT_HIPROC		0x7fffffff	/* specific section header types */
#define	SHT_LOUSER		0x80000000	/* reserved range for application */
#define	SHT_HIUSER		0xffffffff	/* specific indexes */

/* Flags for sh_flags. */
#define	SHF_WRITE		0x00000001	/* Section contains writable data. */
#define	SHF_ALLOC		0x00000002	/* Section occupies memory. */
#define	SHF_EXECINSTR		0x00000004	/* Section contains instructions. */
#define	SHF_MERGE		0x00000010	/* Section may be merged. */
#define	SHF_STRINGS		0x00000020	/* Section contains strings. */
#define	SHF_INFO_LINK		0x00000040	/* sh_info holds section index. */
#define	SHF_LINK_ORDER		0x00000080	/* Special ordering requirements. */
#define	SHF_OS_NONCONFORMING	0x00000100	/* OS-specific processing required. */
#define	SHF_GROUP		0x00000200	/* Member of section group. */
#define	SHF_TLS			0x00000400	/* Section contains TLS data. */
#define	SHF_COMPRESSED		0x00000800	/* Section contains compressed data. */
#define	SHF_MASKOS		0x0ff00000	/* OS-specific semantics. */
#define SHF_ORDERED		0x40000000	/* Solaris special ordering */
#define SHF_EXCLUDE		0x80000000	/* Solaris exclude unless referenced */
#define	SHF_MASKPROC		0xf0000000	/* Processor-specific semantics. */

/*
 * Program header.
 */
typedef struct {
	Elf32_Word	p_type;		/* Entry type. */
	Elf32_Off	p_offset;	/* File offset of contents. */
	Elf32_Addr	p_vaddr;	/* Virtual address in memory image. */
	Elf32_Addr	p_paddr;	/* Physical address (not used). */
	Elf32_Word	p_filesz;	/* Size of contents in file. */
	Elf32_Word	p_memsz;	/* Size of contents in memory. */
	Elf32_Word	p_flags;	/* Access permission flags. */
	Elf32_Word	p_align;	/* Alignment in memory and file. */
} Elf32_Phdr;

typedef struct {
	Elf64_Word	p_type;		/* Entry type. */
	Elf64_Word	p_flags;	/* Access permission flags. */
	Elf64_Off	p_offset;	/* File offset of contents. */
	Elf64_Addr	p_vaddr;	/* Virtual address in memory image. */
	Elf64_Addr	p_paddr;	/* Physical address (not used). */
	Elf64_Xword	p_filesz;	/* Size of contents in file. */
	Elf64_Xword	p_memsz;	/* Size of contents in memory. */
	Elf64_Xword	p_align;	/* Alignment in memory and file. */
} Elf64_Phdr;

/* Values for p_type. */
#define	PT_NULL		0x00000000	/* Unused entry. */
#define	PT_LOAD		0x00000001	/* Loadable segment. */
#define	PT_DYNAMIC	0x00000002	/* Dynamic linking information segment. */
#define	PT_INTERP	0x00000003	/* Pathname of interpreter. */
#define	PT_NOTE		0x00000004	/* Auxiliary information. */
#define	PT_SHLIB	0x00000005	/* Reserved (not used). */
#define	PT_PHDR		0x00000006	/* Location of program header itself. */
#define	PT_TLS		0x00000007	/* Thread local storage segment */
#define	PT_SUNW_UNWIND	0x6464e550	/* amd64 UNWIND program header */
#define	PT_GNU_EH_FRAME	0x6474e550      /* GCC .eh_frame_hdr segment */
#define	PT_GNU_STACK	0x6474e551      /* Executable stack */
#define	PT_GNU_RELRO	0x6474e552      /* Read-only after relocation */
#define	PT_DUMP_DELTA	0x6fb5d000	/* va->pa map for kernel dumps (currently arm). */
#define	PT_LOSUNW	0x6ffffffa
#define	PT_SUNWBSS	0x6ffffffa	/* Sun Specific segment */
#define	PT_SUNWSTACK	0x6ffffffb	/* describes the stack segment */
#define	PT_SUNWDTRACE	0x6ffffffc	/* private */
#define	PT_SUNWCAP	0x6ffffffd	/* hard/soft capabilities segment */
#define	PT_HISUNW	0x6fffffff
#define	PT_HIOS		0x6fffffff	/* Last OS-specific. */
#define	PT_LOPROC	0x70000000	/* First processor-specific type. */
#define	PT_ARM_ARCHEXT	0x70000000	/* ARM arch compat information. */
#define	PT_ARM_EXIDX	0x70000001	/* ARM exception unwind tables. */
#define	PT_HIPROC	0x7fffffff	/* Last processor-specific type. */

/* Values for p_flags. */
#define	PF_X		0x1		/* Executable. */
#define	PF_W		0x2		/* Writable. */
#define	PF_R		0x4		/* Readable. */
#define	PF_MASKOS	0x0ff00000	/* Operating system-specific. */
#define	PF_MASKPROC	0xf0000000	/* Processor-specific. */

/* Extended program header index. */
#define	PN_XNUM		0xffff

/*
 * Dynamic structure.  The ".dynamic" section contains an array of them.
 */
typedef struct {
	Elf32_Sword	d_tag;		/* Entry type. */
	union {
		Elf32_Word	d_val;	/* Integer value. */
		Elf32_Addr	d_ptr;	/* Address value. */
	} d_un;
} Elf32_Dyn;

typedef struct {
	Elf64_Sxword	d_tag;		/* Entry type. */
	union {
		Elf64_Xword	d_val;	/* Integer value. */
		Elf64_Addr	d_ptr;	/* Address value. */
	} d_un;
} Elf64_Dyn;

/* Values for d_tag. */
#define	DT_NULL		0	/* Terminating entry. */
#define	DT_NEEDED	1	/* String table offset of a needed shared library. */
#define	DT_PLTRELSZ	2	/* Total size in bytes of PLT relocations. */
#define	DT_PLTGOT	3	/* Processor-dependent address. */
#define	DT_HASH		4	/* Address of symbol hash table. */
#define	DT_STRTAB	5	/* Address of string table. */
#define	DT_SYMTAB	6	/* Address of symbol table. */
#define	DT_RELA		7	/* Address of ElfNN_Rela relocations. */
#define	DT_RELASZ	8	/* Total size of ElfNN_Rela relocations. */
#define	DT_RELAENT	9	/* Size of each ElfNN_Rela relocation entry. */
#define	DT_STRSZ	10	/* Size of string table. */
#define	DT_SYMENT	11	/* Size of each symbol table entry. */
#define	DT_INIT		12	/* Address of initialization function. */
#define	DT_FINI		13	/* Address of finalization function. */
#define	DT_SONAME	14	/* String table offset of shared object name. */
#define	DT_RPATH	15	/* String table offset of library path. [sup] */
#define	DT_SYMBOLIC	16	/* Indicates "symbolic" linking. [sup] */
#define	DT_REL		17	/* Address of ElfNN_Rel relocations. */
#define	DT_RELSZ	18	/* Total size of ElfNN_Rel relocations. */
#define	DT_RELENT	19	/* Size of each ElfNN_Rel relocation. */
#define	DT_PLTREL	20	/* Type of relocation used for PLT. */
#define	DT_DEBUG	21	/* Reserved (not used). */
#define	DT_TEXTREL	22	/* Indicates there may be relocations in non-writable segments. [sup] */
#define	DT_JMPREL	23	/* Address of PLT relocations. */
#define	DT_BIND_NOW	24	/* [sup] */
#define	DT_INIT_ARRAY	25	/* Address of the array of pointers to initialization functions */
#define	DT_FINI_ARRAY	26	/* Address of the array of pointers to termination functions */
#define	DT_INIT_ARRAYSZ	27	/* Size in bytes of the array of initialization functions. */
#define	DT_FINI_ARRAYSZ	28	/* Size in bytes of the array of termination functions. */
#define	DT_RUNPATH	29	/* String table offset of a null-terminated library search path string. */
#define	DT_FLAGS	30	/* Object specific flag values. */
#define	DT_ENCODING	32	/* Values greater than or equal to DT_ENCODING
				   and less than DT_LOOS follow the rules for
				   the interpretation of the d_un union
				   as follows: even == 'd_ptr', odd == 'd_val'
				   or none */
#define	DT_PREINIT_ARRAY 32	/* Address of the array of pointers to pre-initialization functions. */
#define	DT_PREINIT_ARRAYSZ 33	/* Size in bytes of the array of pre-initialization functions. */
#define DT_SYMTAB_SHNDX	34	/* Address of the SHT_SYMTAB_SHNDX section referenced by the DT_SYMTAB element. */
#define	DT_LOOS			0x6000000d	/* First OS-specific */
#define	DT_SUNW_AUXILIARY	0x6000000d	/* symbol auxiliary name */
#define	DT_SUNW_RTLDINF		0x6000000e	/* ld.so.1 info (private) */
#define	DT_SUNW_FILTER		0x6000000f	/* symbol filter name */
#define	DT_SUNW_CAP		0x60000010	/* hardware/software */
#define	DT_HIOS			0x6ffff000	/* Last OS-specific */

/*
 * DT_* entries which fall between DT_VALRNGHI & DT_VALRNGLO use the
 * Dyn.d_un.d_val field of the Elf*_Dyn structure.
 */
#define	DT_VALRNGLO		0x6ffffd00
#define	DT_GNU_PRELINKED	0x6ffffdf5	/* prelinking timestamp */
#define	DT_GNU_CONFLICTSZ	0x6ffffdf6	/* size of conflict section */
#define	DT_GNU_LIBLISTSZ	0x6ffffdf7	/* size of library list */
#define	DT_CHECKSUM		0x6ffffdf8	/* elf checksum */
#define	DT_PLTPADSZ		0x6ffffdf9	/* pltpadding size */
#define	DT_MOVEENT		0x6ffffdfa	/* move table entry size */
#define	DT_MOVESZ		0x6ffffdfb	/* move table size */
#define	DT_FEATURE		0x6ffffdfc	/* feature holder */
#define	DT_FEATURE_1		DT_FEATURE
#define	DT_POSFLAG_1		0x6ffffdfd	/* flags for DT_* entries, effecting the following DT_* entry. */
#define	DT_SYMINSZ		0x6ffffdfe	/* syminfo table size (in bytes) */
#define	DT_SYMINENT		0x6ffffdff	/* syminfo entry size (in bytes) */
#define	DT_VALRNGHI		0x6ffffdff

/*
 * DT_* entries which fall between DT_ADDRRNGHI & DT_ADDRRNGLO use the
 * Dyn.d_un.d_ptr field of the Elf*_Dyn structure.
 *
 * If any adjustment is made to the ELF object after it has been
 * built, these entries will need to be adjusted.
 */
#define	DT_ADDRRNGLO		0x6ffffe00
#define	DT_GNU_HASH		0x6ffffef5	/* GNU-style hash table */
#define	DT_TLSDESC_PLT		0x6ffffef6	/* loc. of PLT for tlsdesc resolver */
#define	DT_TLSDESC_GOT		0x6ffffef7	/* loc. of GOT for tlsdesc resolver */
#define	DT_GNU_CONFLICT		0x6ffffef8	/* address of conflict section */
#define	DT_GNU_LIBLIST		0x6ffffef9	/* address of library list */
#define	DT_CONFIG		0x6ffffefa	/* configuration information */
#define	DT_DEPAUDIT		0x6ffffefb	/* dependency auditing */
#define	DT_AUDIT		0x6ffffefc	/* object auditing */
#define	DT_PLTPAD		0x6ffffefd	/* pltpadding (sparcv9) */
#define	DT_MOVETAB		0x6ffffefe	/* move table */
#define	DT_SYMINFO		0x6ffffeff	/* syminfo table */
#define	DT_ADDRRNGHI		0x6ffffeff

#define	DT_VERSYM		0x6ffffff0	/* Address of versym section. */
#define	DT_RELACOUNT		0x6ffffff9	/* number of RELATIVE relocations */
#define	DT_RELCOUNT		0x6ffffffa	/* number of RELATIVE relocations */
#define	DT_FLAGS_1		0x6ffffffb	/* state flags - see DF_1_* defs */
#define	DT_VERDEF		0x6ffffffc	/* Address of verdef section. */
#define	DT_VERDEFNUM		0x6ffffffd	/* Number of elems in verdef section */
#define	DT_VERNEED		0x6ffffffe	/* Address of verneed section. */
#define	DT_VERNEEDNUM		0x6fffffff	/* Number of elems in verneed section */

#define	DT_LOPROC		0x70000000	/* First processor-specific type. */

#define	DT_ARM_SYMTABSZ		0x70000001
#define	DT_ARM_PREEMPTMAP	0x70000002

#define	DT_SPARC_REGISTER	0x70000001
#define	DT_DEPRECATED_SPARC_REGISTER	0x7000001

#define	DT_MIPS_RLD_VERSION	0x70000001
#define	DT_MIPS_TIME_STAMP	0x70000002
#define	DT_MIPS_ICHECKSUM	0x70000003
#define	DT_MIPS_IVERSION	0x70000004
#define	DT_MIPS_FLAGS		0x70000005
#define	DT_MIPS_BASE_ADDRESS	0x70000006
#define	DT_MIPS_CONFLICT	0x70000008
#define	DT_MIPS_LIBLIST		0x70000009
#define	DT_MIPS_LOCAL_GOTNO	0x7000000a
#define	DT_MIPS_CONFLICTNO	0x7000000b
#define	DT_MIPS_LIBLISTNO	0x70000010
#define	DT_MIPS_SYMTABNO	0x70000011
#define	DT_MIPS_UNREFEXTNO	0x70000012
#define	DT_MIPS_GOTSYM		0x70000013
#define	DT_MIPS_HIPAGENO	0x70000014
#define	DT_MIPS_RLD_MAP		0x70000016
#define	DT_MIPS_DELTA_CLASS	0x70000017
#define	DT_MIPS_DELTA_CLASS_NO	0x70000018
#define	DT_MIPS_DELTA_INSTANCE	0x70000019
#define	DT_MIPS_DELTA_INSTANCE_NO	0x7000001A
#define	DT_MIPS_DELTA_RELOC	0x7000001B
#define	DT_MIPS_DELTA_RELOC_NO	0x7000001C
#define	DT_MIPS_DELTA_SYM	0x7000001D
#define	DT_MIPS_DELTA_SYM_NO	0x7000001E
#define	DT_MIPS_DELTA_CLASSSYM	0x70000020
#define	DT_MIPS_DELTA_CLASSSYM_NO	0x70000021
#define	DT_MIPS_CXX_FLAGS	0x70000022
#define	DT_MIPS_PIXIE_INIT	0x70000023
#define	DT_MIPS_SYMBOL_LIB	0x70000024
#define	DT_MIPS_LOCALPAGE_GOTIDX	0x70000025
#define	DT_MIPS_LOCAL_GOTIDX	0x70000026
#define	DT_MIPS_HIDDEN_GOTIDX	0x70000027
#define	DT_MIPS_PROTECTED_GOTIDX	0x70000028
#define	DT_MIPS_OPTIONS		0x70000029
#define	DT_MIPS_INTERFACE	0x7000002A
#define	DT_MIPS_DYNSTR_ALIGN	0x7000002B
#define	DT_MIPS_INTERFACE_SIZE	0x7000002C
#define	DT_MIPS_RLD_TEXT_RESOLVE_ADDR	0x7000002D
#define	DT_MIPS_PERF_SUFFIX	0x7000002E
#define	DT_MIPS_COMPACT_SIZE	0x7000002F
#define	DT_MIPS_GP_VALUE	0x70000030
#define	DT_MIPS_AUX_DYNAMIC	0x70000031
#define	DT_MIPS_PLTGOT		0x70000032
#define	DT_MIPS_RLD_OBJ_UPDATE	0x70000033
#define	DT_MIPS_RWPLT		0x70000034

#define	DT_PPC_GOT		0x70000000
#define	DT_PPC_TLSOPT		0x70000001

#define	DT_PPC64_GLINK		0x70000000
#define	DT_PPC64_OPD		0x70000001
#define	DT_PPC64_OPDSZ		0x70000002
#define	DT_PPC64_TLSOPT		0x70000003

#define	DT_AUXILIARY		0x7ffffffd	/* shared library auxiliary name */
#define	DT_USED			0x7ffffffe	/* ignored - same as needed */
#define	DT_FILTER		0x7fffffff	/* shared library filter name */
#define	DT_HIPROC		0x7fffffff	/* Last processor-specific type. */

/* Values for DT_FLAGS */
#define	DF_ORIGIN	0x0001	/* The object being loaded may be using $ORIGIN */
#define	DF_SYMBOLIC	0x0002	/* Indicates "symbolic" linking. */
#define	DF_TEXTREL	0x0004	/* Indicates there may be relocations in non-writable segments. */
#define	DF_BIND_NOW	0x0008	/* Indicates that the dynamic linker should bind all symbols on load */
#define	DF_STATIC_TLS	0x0010	/* Indicates that the shared object or executable uses static TLS */

/* Values for DT_FLAGS_1 */
#define	DF_1_BIND_NOW	0x00000001	/* Same as DF_BIND_NOW */
#define	DF_1_GLOBAL	0x00000002	/* Set the RTLD_GLOBAL for object */
#define	DF_1_NODELETE	0x00000008	/* Set the RTLD_NODELETE for object */
#define	DF_1_LOADFLTR	0x00000010	/* Immediate loading of filtees */
#define DF_1_INITFIRST	0x00000020	/* Set RTLD_INITFIRST for this object*/
#define	DF_1_NOOPEN     0x00000040	/* Do not allow loading on dlopen() */
#define	DF_1_ORIGIN	0x00000080	/* Process $ORIGIN */
#define DF_1_DIRECT	0x00000100	/* Direct binding enabled.  */
#define DF_1_TRANS	0x00000200
#define	DF_1_INTERPOSE	0x00000400	/* Interpose all objects but main */
#define	DF_1_NODEFLIB	0x00000800	/* Do not search default paths */
#define DF_1_NODUMP	0x00001000	/* Object can't be dldump'ed.  */
#define DF_1_CONFALT	0x00002000	/* Configuration alternative created.*/
#define DF_1_ENDFILTEE	0x00004000	/* Filtee terminates filters search. */
#define	DF_1_DISPRELDNE	0x00008000	/* Disp reloc applied at build time. */
#define	DF_1_DISPRELPND	0x00010000	/* Disp reloc applied at run-time.  */
#define	DF_1_NODIRECT	0x00020000	/* Object has no-direct binding. */
#define	DF_1_IGNMULDEF	0x00040000
#define	DF_1_NOKSYMS	0x00080000
#define	DF_1_NOHDR	0x00100000
#define	DF_1_EDITED	0x00200000	/* Object is modified after built.  */
#define	DF_1_NORELOC	0x00400000
#define	DF_1_SYMINTPOSE	0x00800000	/* Object has individual interposers.  */
#define	DF_1_GLOBAUDIT	0x01000000	/* Global auditing required.  */
#define	DF_1_SINGLETON	0x02000000	/* Singleton symbols are used.  */
#define	DF_1_STUB	0x04000000
#define	DF_1_PIE	0x08000000

/* Flags for the feature selection in DT_FEATURE_1.  */
#define DTF_1_PARINIT	0x00000001
#define DTF_1_CONFEXP	0x00000002

/* Flags in the DT_POSFLAG_1 entry effecting only the next DT_* entry.  */
#define DF_P1_LAZYLOAD	0x00000001	/* Lazyload following object.  */
#define DF_P1_GROUPPERM	0x00000002	/* Symbols from next object are not generally available.  */

/*
 * Relocation entries.
 */

/* Relocations that don't need an addend field. */
typedef struct {
	Elf32_Addr	r_offset;	/* Location to be relocated. */
	Elf32_Word	r_info;		/* Relocation type and symbol index. */
} Elf32_Rel;

typedef struct {
	Elf64_Addr	r_offset;	/* Location to be relocated. */
	Elf64_Xword	r_info;		/* Relocation type and symbol index. */
} Elf64_Rel;

/* Relocations that need an addend field. */
typedef struct {
	Elf32_Addr	r_offset;	/* Location to be relocated. */
	Elf32_Word	r_info;		/* Relocation type and symbol index. */
	Elf32_Sword	r_addend;	/* Addend. */
} Elf32_Rela;

typedef struct {
	Elf64_Addr	r_offset;	/* Location to be relocated. */
	Elf64_Xword	r_info;		/* Relocation type and symbol index. */
	Elf64_Sxword	r_addend;	/* Addend. */
} Elf64_Rela;

/* Macros for accessing the fields of r_info. */
#define ELF32_R_SYM(info)	((info) >> 8)
#define	ELF64_R_SYM(info)	((info) >> 32)

#define ELF32_R_TYPE(info)	((unsigned char)(info))
#define	ELF64_R_TYPE(info)	((info) & 0xffffffffL)

/* Macro for constructing r_info from field values. */
#define ELF32_R_INFO(sym, type)	(((sym) << 8) + (unsigned char)(type))
#define	ELF64_R_INFO(sym, type)	(((sym) << 32) + ((type) & 0xffffffffL))

#define	ELF64_R_TYPE_DATA(info)	(((Elf64_Xword)(info)<<32)>>40)
#define	ELF64_R_TYPE_ID(info)	(((Elf64_Xword)(info)<<56)>>56)
#define	ELF64_R_TYPE_INFO(data, type)	\
				(((Elf64_Xword)(data)<<8)+(Elf64_Xword)(type))

/*
 * Note header.  The ".note" section contains an array of notes.  Each
 * begins with this header, aligned to a word boundary.  Immediately
 * following the note header is n_namesz bytes of name, padded to the
 * next word boundary.  Then comes n_descsz bytes of descriptor, again
 * padded to a word boundary.  The values of n_namesz and n_descsz do
 * not include the padding.
 */
typedef struct {
	uint32_t	n_namesz;	/* Length of name. */
	uint32_t	n_descsz;	/* Length of descriptor. */
	uint32_t	n_type;		/* Type of this note. */
} Elf_Note;

/* Values for n_type used in executables. */
#define	NT_FREEBSD_ABI_TAG	1
#define	NT_FREEBSD_NOINIT_TAG	2
#define	NT_FREEBSD_ARCH_TAG	3

/* Values for n_type.  Used in core files. */
#define	NT_PRSTATUS		1	/* Process status. */
#define	NT_FPREGSET		2	/* Floating point registers. */
#define	NT_PRPSINFO		3	/* Process state info. */
#define NT_PRXREG		4	/* Contains copy of prxregset struct */
#define NT_TASKSTRUCT		4	/* Contains copy of task structure */
#define NT_PLATFORM		5	/* String from sysinfo(SI_PLATFORM) */
#define NT_AUXV			6	/* Contains copy of auxv array */
#define	NT_THRMISC		7	/* Thread miscellaneous info. */
#define	NT_PROCSTAT_PROC	8	/* Procstat proc data. */
#define	NT_PROCSTAT_FILES	9	/* Procstat files data. */
#define	NT_PROCSTAT_VMMAP	10	/* Procstat vmmap data. */
#define	NT_PROCSTAT_GROUPS	11	/* Procstat groups data. */
#define	NT_PROCSTAT_UMASK	12	/* Procstat umask data. */
#define	NT_PROCSTAT_RLIMIT	13	/* Procstat rlimit data. */
#define	NT_PROCSTAT_OSREL	14	/* Procstat osreldate data. */
#define	NT_PROCSTAT_PSSTRINGS	15	/* Procstat ps_strings data. */
#define	NT_PROCSTAT_AUXV	16	/* Procstat auxv data. */
#define	NT_PTLWPINFO		17	/* Thread ptrace miscellaneous info. */
#define NT_PRFPXREG		20	/* Contains copy of fprxregset struct */
#define	NT_PPC_VMX		0x100	/* PowerPC Altivec/VMX registers */
#define NT_PPC_SPE		0x101	/* PowerPC SPE/EVR registers */
#define NT_PPC_VSX		0x102	/* PowerPC VSX registers */
#define NT_PPC_TAR		0x103	/* Target Address Register */
#define NT_PPC_PPR		0x104	/* Program Priority Register */
#define NT_PPC_DSCR		0x105	/* Data Stream Control Register */
#define NT_PPC_EBB		0x106	/* Event Based Branch Registers */
#define NT_PPC_PMU		0x107	/* Performance Monitor Registers */
#define NT_PPC_TM_CGPR		0x108	/* TM checkpointed GPR Registers */
#define NT_PPC_TM_CFPR		0x109	/* TM checkpointed FPR Registers */
#define NT_PPC_TM_CVMX		0x10a	/* TM checkpointed VMX Registers */
#define NT_PPC_TM_CVSX		0x10b	/* TM checkpointed VSX Registers */
#define NT_PPC_TM_SPR		0x10c	/* TM Special Purpose Registers */
#define NT_PPC_TM_CTAR		0x10d	/* TM checkpointed Target Address Register */
#define NT_PPC_TM_CPPR		0x10e	/* TM checkpointed Program Priority Register */
#define NT_PPC_TM_CDSCR		0x10f	/* TM checkpointed Data Stream Control Register */
#define NT_386_TLS		0x200	/* i386 TLS slots (struct user_desc) */
#define NT_386_IOPERM		0x201	/* x86 io permission bitmap (1=deny) */
#define	NT_X86_XSTATE		0x202	/* x86 XSAVE extended state. */
#define NT_S390_HIGH_GPRS	0x300	/* s390 upper register halves */
#define NT_S390_TIMER		0x301	/* s390 timer register */
#define NT_S390_TODCMP		0x302	/* s390 TOD clock comparator register */
#define NT_S390_TODPREG		0x303	/* s390 TOD programmable register */
#define NT_S390_CTRS		0x304	/* s390 control registers */
#define NT_S390_PREFIX		0x305	/* s390 prefix register */
#define NT_S390_LAST_BREAK	0x306	/* s390 breaking event address */
#define NT_S390_SYSTEM_CALL	0x307	/* s390 system call restart data */
#define NT_S390_TDB		0x308	/* s390 transaction diagnostic block */
#define	NT_ARM_VFP		0x400	/* ARM VFP registers */
#define NT_ARM_TLS		0x401	/* ARM TLS register */
#define NT_ARM_HW_BREAK		0x402	/* ARM hardware breakpoint registers */
#define NT_ARM_HW_WATCH		0x403	/* ARM hardware watchpoint registers */
#define NT_ARM_SYSTEM_CALL	0x404	/* ARM system call number */
#define NT_ARM_SVE		0x405	/* ARM Scalable Vector Extension registers */

/*
 *	Note entry header
 */
typedef Elf_Note Elf32_Nhdr;
typedef Elf_Note Elf64_Nhdr;

/*
 *	Move entry
 */
typedef struct {
	Elf32_Lword	m_value;	/* symbol value */
	Elf32_Word 	m_info;		/* size + index */
	Elf32_Word	m_poffset;	/* symbol offset */
	Elf32_Half	m_repeat;	/* repeat count */
	Elf32_Half	m_stride;	/* stride info */
} Elf32_Move;

typedef struct {
	Elf64_Lword	m_value;	/* symbol value */
	Elf64_Xword 	m_info;		/* size + index */
	Elf64_Xword	m_poffset;	/* symbol offset */
	Elf64_Half	m_repeat;	/* repeat count */
	Elf64_Half	m_stride;	/* stride info */
} Elf64_Move;

/*
 *	The macros compose and decompose values for Move.r_info
 *
 *	sym = ELF32_M_SYM(M.m_info)
 *	size = ELF32_M_SIZE(M.m_info)
 *	M.m_info = ELF32_M_INFO(sym, size)
 */
#define	ELF32_M_SYM(info)	((info)>>8)
#define	ELF64_M_SYM(info)	((info)>>8)

#define	ELF32_M_SIZE(info)	((unsigned char)(info))
#define	ELF64_M_SIZE(info)	((unsigned char)(info))

#define	ELF32_M_INFO(sym, size)	(((sym)<<8)+(unsigned char)(size))
#define	ELF64_M_INFO(sym, size)	(((sym)<<8)+(unsigned char)(size))

/*
 *	Hardware/Software capabilities entry
 */
typedef struct {
	Elf32_Word	c_tag;		/* how to interpret value */
	union {
		Elf32_Word	c_val;
		Elf32_Addr	c_ptr;
	} c_un;
} Elf32_Cap;

typedef struct {
	Elf64_Xword	c_tag;		/* how to interpret value */
	union {
		Elf64_Xword	c_val;
		Elf64_Addr	c_ptr;
	} c_un;
} Elf64_Cap;

#define	CA_SUNW_NULL	0
#define	CA_SUNW_HW_1	1		/* first hardware capabilities entry */
#define	CA_SUNW_SF_1	2		/* first software capabilities entry */

/*
 * Symbol table entries.
 */
typedef struct {
	Elf32_Word	st_name;	/* String table index of name. */
	Elf32_Addr	st_value;	/* Symbol value. */
	Elf32_Word	st_size;	/* Size of associated object. */
	unsigned char	st_info;	/* Type and binding information. */
	unsigned char	st_other;	/* Reserved (not used). */
	Elf32_Half	st_shndx;	/* Section index of symbol. */
} Elf32_Sym;

typedef struct {
	Elf64_Word	st_name;	/* String table index of name. */
	unsigned char	st_info;	/* Type and binding information. */
	unsigned char	st_other;	/* Reserved (not used). */
	Elf64_Half	st_shndx;	/* Section index of symbol. */
	Elf64_Addr	st_value;	/* Symbol value. */
	Elf64_Xword	st_size;	/* Size of associated object. */
} Elf64_Sym;

/* Macros for accessing the fields of st_info. */
#define ELF32_ST_BIND(info)		((info) >> 4)
#define	ELF64_ST_BIND(info)		((info) >> 4)

#define ELF32_ST_TYPE(info)		((info) & 0xf)
#define	ELF64_ST_TYPE(info)		((info) & 0xf)

/* Macro for constructing st_info from field values. */
#define ELF32_ST_INFO(bind, type)	(((bind) << 4) + ((type) & 0xf))
#define	ELF64_ST_INFO(bind, type)	(((bind) << 4) + ((type) & 0xf))

/* Macro for accessing the fields of st_other. */
#define ELF32_ST_VISIBILITY(oth)	((oth) & 0x3)
#define	ELF64_ST_VISIBILITY(oth)	((oth) & 0x3)

/* Symbol Binding - ELFNN_ST_BIND - st_info */
#define	STB_LOCAL	0	/* Local symbol */
#define	STB_GLOBAL	1	/* Global symbol */
#define	STB_WEAK	2	/* like global - lower precedence */
#define	STB_LOOS	10	/* Start of operating system reserved range. */
#define	STB_GNU_UNIQUE	10	/* Unique symbol (GNU) */
#define	STB_HIOS	12	/* End of operating system reserved range. */
#define	STB_LOPROC	13	/* reserved range for processor */
#define	STB_HIPROC	15	/*   specific semantics. */

/* Symbol type - ELFNN_ST_TYPE - st_info */
#define	STT_NOTYPE	0	/* Unspecified type. */
#define	STT_OBJECT	1	/* Data object. */
#define	STT_FUNC	2	/* Function. */
#define	STT_SECTION	3	/* Section. */
#define	STT_FILE	4	/* Source file. */
#define	STT_COMMON	5	/* Uninitialized common block. */
#define	STT_TLS		6	/* TLS object. */
#define	STT_NUM		7
#define	STT_LOOS	10	/* Reserved range for operating system */
#define	STT_GNU_IFUNC	10
#define	STT_HIOS	12	/*   specific semantics. */
#define	STT_LOPROC	13	/* Start of processor reserved range. */
#define	STT_SPARC_REGISTER 13	/* SPARC register information. */
#define	STT_HIPROC	15	/* End of processor reserved range. */

/* Special symbol table indexes. */
#define	STN_UNDEF	0	/* Undefined symbol index. */

/* Symbol visibility - ELFNN_ST_VISIBILITY - st_other */
#define	STV_DEFAULT	0x0	/* Default visibility (see binding). */
#define	STV_INTERNAL	0x1	/* Special meaning in relocatable objects. */
#define	STV_HIDDEN	0x2	/* Not visible. */
#define	STV_PROTECTED	0x3	/* Visible but not preemptible. */
#define	STV_EXPORTED	0x4
#define	STV_SINGLETON	0x5
#define	STV_ELIMINATE	0x6

/* Structures used by Sun & GNU symbol versioning. */
typedef struct
{
	Elf32_Half	vd_version;
	Elf32_Half	vd_flags;
	Elf32_Half	vd_ndx;
	Elf32_Half	vd_cnt;
	Elf32_Word	vd_hash;
	Elf32_Word	vd_aux;
	Elf32_Word	vd_next;
} Elf32_Verdef;

typedef struct {
	Elf64_Half	vd_version;
	Elf64_Half	vd_flags;
	Elf64_Half	vd_ndx;
	Elf64_Half	vd_cnt;
	Elf64_Word	vd_hash;
	Elf64_Word	vd_aux;
	Elf64_Word	vd_next;
} Elf64_Verdef;

/* Symbol versioning revision (vd_version). */
#define VER_DEF_NONE	0
#define	VER_DEF_CURRENT	1
#define	VER_DEF_NUM	2

/* Symbol versioning flags (vd_flags). */
#define	VER_FLG_BASE	0x01
#define	VER_FLG_WEAK	0x02

#define	VER_NDX_LOCAL		0x0000
#define	VER_NDX_GLOBAL		0x0001
#define	VER_NDX_GIVEN		0x0002
#define	VER_NDX_HIDDEN		0xf000
#define	VER_NDX_LORESERVE	0xff00	/* Beginning of reserved entries.  */
#define	VER_NDX_ELIMINATE	0xff01	/* Symbol is to be eliminated.  */

typedef struct
{
	Elf32_Word	vda_name;
	Elf32_Word	vda_next;
} Elf32_Verdaux;

typedef struct {
	Elf64_Word	vda_name;
	Elf64_Word	vda_next;
} Elf64_Verdaux;

typedef struct
{
	Elf32_Half	vn_version;
	Elf32_Half	vn_cnt;
	Elf32_Word	vn_file;
	Elf32_Word	vn_aux;
	Elf32_Word	vn_next;
} Elf32_Verneed;

typedef struct {
	Elf64_Half	vn_version;
	Elf64_Half	vn_cnt;
	Elf64_Word	vn_file;
	Elf64_Word	vn_aux;
	Elf64_Word	vn_next;
} Elf64_Verneed;

/* vn_version */
#define	VER_NEED_NONE		0x0000
#define	VER_NEED_CURRENT	0x0001
#define	VER_NEED_NUM		0x0002
#define	VER_NEED_WEAK		0xf000
#define	VER_NEED_HIDDEN		VER_NDX_HIDDEN

typedef struct
{
	Elf32_Word	vna_hash;
	Elf32_Half	vna_flags;
	Elf32_Half	vna_other;
	Elf32_Word	vna_name;
	Elf32_Word	vna_next;
} Elf32_Vernaux;

typedef struct {
	Elf64_Word	vna_hash;
	Elf64_Half	vna_flags;
	Elf64_Half	vna_other;
	Elf64_Word	vna_name;
	Elf64_Word	vna_next;
} Elf64_Vernaux;

typedef Elf32_Half Elf32_Versym;
typedef Elf64_Half Elf64_Versym;

typedef struct {
	Elf32_Half	si_boundto;	/* direct bindings - symbol bound to */
	Elf32_Half	si_flags;	/* per symbol flags */
} Elf32_Syminfo;

typedef struct {
	Elf64_Half	si_boundto;	/* direct bindings - symbol bound to */
	Elf64_Half	si_flags;	/* per symbol flags */
} Elf64_Syminfo;

/*
 * Syminfo.si_boundto values.
 */
#define	SYMINFO_BT_SELF		0xffff	/* symbol bound to self */
#define	SYMINFO_BT_PARENT	0xfffe	/* symbol bound to parent */
#define	SYMINFO_BT_NONE		0xfffd	/* no special symbol binding */
#define	SYMINFO_BT_EXTERN	0xfffc	/* symbol defined as external */
#define	SYMINFO_BT_LOWRESERVE	0xff00	/* beginning of reserved entries */

/*
 * Syminfo si_flags values.
 */
#define	SYMINFO_FLG_DIRECT	0x0001	/* symbol ref has direct association */
					/*	to object containing defn. */
#define	SYMINFO_FLG_PASSTHRU	0x0002	/* ignored - see SYMINFO_FLG_FILTER */
#define	SYMINFO_FLG_COPY	0x0004	/* symbol is a copy-reloc */
#define	SYMINFO_FLG_LAZYLOAD	0x0008	/* object containing defn should be */
					/*	lazily-loaded */
#define	SYMINFO_FLG_DIRECTBIND	0x0010	/* ref should be bound directly to */
					/*	object containing defn. */
#define	SYMINFO_FLG_NOEXTDIRECT	0x0020	/* don't let an external reference */
					/*	directly bind to this symbol */
#define	SYMINFO_FLG_FILTER	0x0002	/* symbol ref is associated to a */
#define	SYMINFO_FLG_AUXILIARY	0x0040	/* 	standard or auxiliary filter */

/*
 * Syminfo version values.
 */
#define	SYMINFO_NONE		0	/* Syminfo version */
#define	SYMINFO_CURRENT		1
#define	SYMINFO_NUM		2

typedef struct {
	Elf32_Word	ch_type;
	Elf32_Word	ch_size;
	Elf32_Word	ch_addralign;
} Elf32_Chdr;

typedef struct {
	Elf64_Word	ch_type;
	Elf64_Word	ch_reserved;
	Elf64_Xword	ch_size;
	Elf64_Xword	ch_addralign;
} Elf64_Chdr;

/* Values for ch_type (compressed section headers). */
#define	ELFCOMPRESS_ZLIB	0x00000001	/* ZLIB/DEFLATE */
#define	ELFCOMPRESS_LOOS	0x60000000	/* OS-specific */
#define	ELFCOMPRESS_HIOS	0x6fffffff
#define	ELFCOMPRESS_LOPROC	0x70000000	/* Processor-specific */
#define	ELFCOMPRESS_HIPROC	0x7fffffff

/* Not strictly part of the gABI */
typedef struct {
	uint32_t a_type;		/* Entry type */
	union {
		uint32_t a_val;		/* Integer value */
	} a_un;
} Elf32_Auxv;

typedef struct {
	uint64_t a_type;		/* Entry type */
	union {
		uint64_t a_val;		/* Integer value */
	} a_un;
} Elf64_Auxv;

/* Legal values for a_type (entry type).  */

#define AT_NULL		0		/* End of vector */
#define AT_IGNORE	1		/* Entry should be ignored */
#define AT_EXECFD	2		/* File descriptor of program */
#define AT_PHDR		3		/* Program headers for program */
#define AT_PHENT	4		/* Size of program header entry */
#define AT_PHNUM	5		/* Number of program headers */
#define AT_PAGESZ	6		/* System page size */
#define AT_BASE		7		/* Base address of interpreter */
#define AT_FLAGS	8		/* Flags */
#define AT_ENTRY	9		/* Entry point of program */
#define AT_NOTELF	10		/* Program is not ELF */
#define AT_UID		11		/* Real uid */
#define AT_EUID		12		/* Effective uid */
#define AT_GID		13		/* Real gid */
#define AT_EGID		14		/* Effective gid */
#define AT_PLATFORM	15		/* String identifying platform.  */
#define AT_HWCAP	16		/* Machine-dependent hints about processor capabilities.  */
#define AT_CLKTCK	17		/* Frequency of times() */
#define AT_FPUCW	18		/* Used FPU control word.  */
#define AT_DCACHEBSIZE	19		/* Data cache block size.  */
#define AT_ICACHEBSIZE	20		/* Instruction cache block size.  */
#define AT_UCACHEBSIZE	21		/* Unified cache block size.  */
#define AT_IGNOREPPC	22		/* Entry should be ignored.  */
#define	AT_SECURE	23		/* Boolean, was exec setuid-like?  */
#define AT_BASE_PLATFORM 24		/* String identifying real platforms.*/
#define AT_RANDOM	25		/* Address of 16 random bytes.  */
#define AT_HWCAP2	26		/* More machine-dependent hints about processor capabilities.  */
#define AT_EXECFN	31		/* Filename of executable.  */
#define AT_SYSINFO	32
#define AT_SYSINFO_EHDR	33

/* Shapes of the caches.  Bits 0-3 contains associativity; bits 4-7 contains
   log2 of line size; mask those to get cache size.  */
#define AT_L1I_CACHESHAPE	34
#define AT_L1D_CACHESHAPE	35
#define AT_L2_CACHESHAPE	36
#define AT_L3_CACHESHAPE	37
#define AT_L1I_CACHESIZE	40
#define AT_L1I_CACHEGEOMETRY	41
#define AT_L1D_CACHESIZE	42
#define AT_L1D_CACHEGEOMETRY	43
#define AT_L2_CACHESIZE		44
#define AT_L2_CACHEGEOMETRY	45
#define AT_L3_CACHESIZE		46
#define AT_L3_CACHEGEOMETRY	47

/*
 * Option kinds.
 */
#define	ODK_NULL	0	/* undefined */
#define	ODK_REGINFO	1	/* register usage info */
#define	ODK_EXCEPTIONS	2	/* exception processing info */
#define	ODK_PAD		3	/* section padding */
#define	ODK_HWPATCH	4	/* hardware patch applied */
#define	ODK_FILL	5	/* fill value used by the linker */
#define	ODK_TAGS	6	/* reserved space for tools */
#define	ODK_HWAND	7	/* hardware AND patch applied */
#define	ODK_HWOR	8	/* hardware OR patch applied */
#define	ODK_GP_GROUP	9	/* GP group for text/data sections */
#define	ODK_IDENT	10	/* ID information */
#define	ODK_PAGESIZE	11	/* page size information */

/*
 * ODK_EXCEPTIONS info field masks.
 */
#define	OEX_FPU_MIN	0x0000001f	/* min FPU exception required */
#define	OEX_FPU_MAX	0x00001f00	/* max FPU exception allowed */
#define	OEX_PAGE0	0x00010000	/* page zero must be mapped */
#define	OEX_SMM		0x00020000	/* run in sequential memory mode */
#define	OEX_PRECISEFP	0x00040000	/* run in precise FP exception mode */
#define	OEX_DISMISS	0x00080000	/* dismiss invalid address traps */

#define OEX_FPU_INVAL	0x10
#define OEX_FPU_DIV0	0x08
#define OEX_FPU_OFLO	0x04
#define OEX_FPU_UFLO	0x02
#define OEX_FPU_INEX	0x01

/*
 * ODK_PAD info field masks.
 */
#define	OPAD_PREFIX	0x0001
#define	OPAD_POSTFIX	0x0002
#define	OPAD_SYMBOL	0x0004

/*
 * ODK_HWPATCH info field masks.
 */
#define	OHW_R4KEOP	0x00000001	/* patch for R4000 branch at end-of-page bug */
#define	OHW_R8KPFETCH	0x00000002	/* R8000 prefetch bug may occur */
#define	OHW_R5KEOP	0x00000004	/* patch for R5000 branch at end-of-page bug */
#define	OHW_R5KCVTL	0x00000008	/* R5000 cvt.[ds].l bug: clean == 1 */
#define	OHW_R10KLDL	0x00000010UL	/* need patch for R10000 misaligned load */

/*
 * ODK_HWAND/ODK_HWOR info field and hwp_flags[12] masks.
 */
#define	OHWA0_R4KEOP_CHECKED	0x00000001	/* object checked for R4000 end-of-page bug */
#define	OHWA0_R4KEOP_CLEAN	0x00000002	/* object verified clean for R4000 end-of-page bug */
#define	OHWO0_FIXADE		0x00000001	/* object requires call to fixade */

/*
 * ODK_IDENT/ODK_GP_GROUP info field masks.
 */
#define	OGP_GROUP	0x0000ffff	/* GP group number */
#define	OGP_SELF	0x00010000	/* GP group is self-contained */

/*
 * The header for GNU-style hash sections.
 */
typedef struct {
	uint32_t	gh_nbuckets;	/* Number of hash buckets. */
	uint32_t	gh_symndx;	/* First visible symbol in .dynsym. */
	uint32_t	gh_maskwords;	/* #maskwords used in bloom filter. */
	uint32_t	gh_shift2;	/* Bloom filter shift count. */
} Elf_GNU_Hash_Header;

/* Flags for section groups. */
#define	GRP_COMDAT	0x1	/* COMDAT semantics. */

/*
 * Relocation types.
 *
 * All machine architectures are defined here to allow tools on one to
 * handle others.
 */

#define	R_386_NONE		0	/* No relocation. */
#define	R_386_32		1	/* Add symbol value. */
#define	R_386_PC32		2	/* Add PC-relative symbol value. */
#define	R_386_GOT32		3	/* Add PC-relative GOT offset. */
#define	R_386_PLT32		4	/* Add PC-relative PLT offset. */
#define	R_386_COPY		5	/* Copy data from shared object. */
#define	R_386_GLOB_DAT		6	/* Set GOT entry to data address. */
#define	R_386_JMP_SLOT		7	/* Set GOT entry to code address. */
#define	R_386_RELATIVE		8	/* Add load address of shared object. */
#define	R_386_GOTOFF		9	/* Add GOT-relative symbol address. */
#define	R_386_GOTPC		10	/* Add PC-relative GOT table address. */
#define	R_386_TLS_TPOFF		14	/* Negative offset in static TLS block */
#define	R_386_TLS_IE		15	/* Absolute address of GOT for -ve static TLS */
#define	R_386_TLS_GOTIE		16	/* GOT entry for negative static TLS block */
#define	R_386_TLS_LE		17	/* Negative offset relative to static TLS */
#define	R_386_TLS_GD		18	/* 32 bit offset to GOT (index,off) pair */
#define	R_386_TLS_LDM		19	/* 32 bit offset to GOT (index,zero) pair */
#define	R_386_TLS_GD_32		24	/* 32 bit offset to GOT (index,off) pair */
#define	R_386_TLS_GD_PUSH	25	/* pushl instruction for Sun ABI GD sequence */
#define	R_386_TLS_GD_CALL	26	/* call instruction for Sun ABI GD sequence */
#define	R_386_TLS_GD_POP	27	/* popl instruction for Sun ABI GD sequence */
#define	R_386_TLS_LDM_32	28	/* 32 bit offset to GOT (index,zero) pair */
#define	R_386_TLS_LDM_PUSH	29	/* pushl instruction for Sun ABI LD sequence */
#define	R_386_TLS_LDM_CALL	30	/* call instruction for Sun ABI LD sequence */
#define	R_386_TLS_LDM_POP	31	/* popl instruction for Sun ABI LD sequence */
#define	R_386_TLS_LDO_32	32	/* 32 bit offset from start of TLS block */
#define	R_386_TLS_IE_32		33	/* 32 bit offset to GOT static TLS offset entry */
#define	R_386_TLS_LE_32		34	/* 32 bit offset within static TLS block */
#define	R_386_TLS_DTPMOD32	35	/* GOT entry containing TLS index */
#define	R_386_TLS_DTPOFF32	36	/* GOT entry containing TLS offset */
#define	R_386_TLS_TPOFF32	37	/* GOT entry of -ve static TLS offset */
#define	R_386_IRELATIVE		42	/* PLT entry resolved indirectly at runtime */

#define	R_AARCH64_NONE		0	/* No relocation */
#define	R_AARCH64_ABS64		257	/* Absolute offset */
#define	R_AARCH64_ABS32		258	/* Absolute, 32-bit overflow check */
#define	R_AARCH64_ABS16		259	/* Absolute, 16-bit overflow check */
#define	R_AARCH64_PREL64	260	/* PC relative */
#define	R_AARCH64_PREL32	261	/* PC relative, 32-bit overflow check */
#define	R_AARCH64_PREL16	262	/* PC relative, 16-bit overflow check */
#define	R_AARCH64_COPY		1024	/* Copy data from shared object */
#define	R_AARCH64_GLOB_DAT	1025	/* Set GOT entry to data address */
#define	R_AARCH64_JUMP_SLOT	1026	/* Set GOT entry to code address */
#define	R_AARCH64_RELATIVE 	1027	/* Add load address of shared object */
#define	R_AARCH64_TLS_DTPREL64	1028
#define	R_AARCH64_TLS_DTPMOD64	1029
#define	R_AARCH64_TLS_TPREL64 	1030
#define	R_AARCH64_TLSDESC 	1031	/* Identify the TLS descriptor */
#define	R_AARCH64_IRELATIVE	1032

#define	R_ARM_NONE		0	/* No relocation. */
#define	R_ARM_PC24		1
#define	R_ARM_ABS32		2
#define	R_ARM_REL32		3
#define	R_ARM_PC13		4
#define	R_ARM_ABS16		5
#define	R_ARM_ABS12		6
#define	R_ARM_THM_ABS5		7
#define	R_ARM_ABS8		8
#define	R_ARM_SBREL32		9
#define	R_ARM_THM_PC22		10
#define	R_ARM_THM_PC8		11
#define	R_ARM_AMP_VCALL9	12
#define	R_ARM_SWI24		13
#define	R_ARM_THM_SWI8		14
#define	R_ARM_XPC25		15
#define	R_ARM_THM_XPC22		16
/* TLS relocations */
#define	R_ARM_TLS_DTPMOD32	17	/* ID of module containing symbol */
#define	R_ARM_TLS_DTPOFF32	18	/* Offset in TLS block */
#define	R_ARM_TLS_TPOFF32	19	/* Offset in static TLS block */
#define	R_ARM_COPY		20	/* Copy data from shared object. */
#define	R_ARM_GLOB_DAT		21	/* Set GOT entry to data address. */
#define	R_ARM_JUMP_SLOT		22	/* Set GOT entry to code address. */
#define	R_ARM_RELATIVE		23	/* Add load address of shared object. */
#define	R_ARM_GOTOFF		24	/* Add GOT-relative symbol address. */
#define	R_ARM_GOTPC		25	/* Add PC-relative GOT table address. */
#define	R_ARM_GOT32		26	/* Add PC-relative GOT offset. */
#define	R_ARM_PLT32		27	/* Add PC-relative PLT offset. */
#define	R_ARM_GNU_VTENTRY	100
#define	R_ARM_GNU_VTINHERIT	101
#define	R_ARM_RSBREL32		250
#define	R_ARM_THM_RPC22		251
#define	R_ARM_RREL32		252
#define	R_ARM_RABS32		253
#define	R_ARM_RPC24		254
#define	R_ARM_RBASE		255

/*	Name			Value	   Field	Calculation */
#define	R_IA_64_NONE		0	/* None */
#define	R_IA_64_IMM14		0x21	/* immediate14	S + A */
#define	R_IA_64_IMM22		0x22	/* immediate22	S + A */
#define	R_IA_64_IMM64		0x23	/* immediate64	S + A */
#define	R_IA_64_DIR32MSB	0x24	/* word32 MSB	S + A */
#define	R_IA_64_DIR32LSB	0x25	/* word32 LSB	S + A */
#define	R_IA_64_DIR64MSB	0x26	/* word64 MSB	S + A */
#define	R_IA_64_DIR64LSB	0x27	/* word64 LSB	S + A */
#define	R_IA_64_GPREL22		0x2a	/* immediate22	@gprel(S + A) */
#define	R_IA_64_GPREL64I	0x2b	/* immediate64	@gprel(S + A) */
#define	R_IA_64_GPREL32MSB	0x2c	/* word32 MSB	@gprel(S + A) */
#define	R_IA_64_GPREL32LSB	0x2d	/* word32 LSB	@gprel(S + A) */
#define	R_IA_64_GPREL64MSB	0x2e	/* word64 MSB	@gprel(S + A) */
#define	R_IA_64_GPREL64LSB	0x2f	/* word64 LSB	@gprel(S + A) */
#define	R_IA_64_LTOFF22		0x32	/* immediate22	@ltoff(S + A) */
#define	R_IA_64_LTOFF64I	0x33	/* immediate64	@ltoff(S + A) */
#define	R_IA_64_PLTOFF22	0x3a	/* immediate22	@pltoff(S + A) */
#define	R_IA_64_PLTOFF64I	0x3b	/* immediate64	@pltoff(S + A) */
#define	R_IA_64_PLTOFF64MSB	0x3e	/* word64 MSB	@pltoff(S + A) */
#define	R_IA_64_PLTOFF64LSB	0x3f	/* word64 LSB	@pltoff(S + A) */
#define	R_IA_64_FPTR64I		0x43	/* immediate64	@fptr(S + A) */
#define	R_IA_64_FPTR32MSB	0x44	/* word32 MSB	@fptr(S + A) */
#define	R_IA_64_FPTR32LSB	0x45	/* word32 LSB	@fptr(S + A) */
#define	R_IA_64_FPTR64MSB	0x46	/* word64 MSB	@fptr(S + A) */
#define	R_IA_64_FPTR64LSB	0x47	/* word64 LSB	@fptr(S + A) */
#define	R_IA_64_PCREL60B	0x48	/* immediate60 form1 S + A - P */
#define	R_IA_64_PCREL21B	0x49	/* immediate21 form1 S + A - P */
#define	R_IA_64_PCREL21M	0x4a	/* immediate21 form2 S + A - P */
#define	R_IA_64_PCREL21F	0x4b	/* immediate21 form3 S + A - P */
#define	R_IA_64_PCREL32MSB	0x4c	/* word32 MSB	S + A - P */
#define	R_IA_64_PCREL32LSB	0x4d	/* word32 LSB	S + A - P */
#define	R_IA_64_PCREL64MSB	0x4e	/* word64 MSB	S + A - P */
#define	R_IA_64_PCREL64LSB	0x4f	/* word64 LSB	S + A - P */
#define	R_IA_64_LTOFF_FPTR22	0x52	/* immediate22	@ltoff(@fptr(S + A)) */
#define	R_IA_64_LTOFF_FPTR64I	0x53	/* immediate64	@ltoff(@fptr(S + A)) */
#define	R_IA_64_LTOFF_FPTR32MSB	0x54	/* word32 MSB	@ltoff(@fptr(S + A)) */
#define	R_IA_64_LTOFF_FPTR32LSB	0x55	/* word32 LSB	@ltoff(@fptr(S + A)) */
#define	R_IA_64_LTOFF_FPTR64MSB	0x56	/* word64 MSB	@ltoff(@fptr(S + A)) */
#define	R_IA_64_LTOFF_FPTR64LSB	0x57	/* word64 LSB	@ltoff(@fptr(S + A)) */
#define	R_IA_64_SEGREL32MSB	0x5c	/* word32 MSB	@segrel(S + A) */
#define	R_IA_64_SEGREL32LSB	0x5d	/* word32 LSB	@segrel(S + A) */
#define	R_IA_64_SEGREL64MSB	0x5e	/* word64 MSB	@segrel(S + A) */
#define	R_IA_64_SEGREL64LSB	0x5f	/* word64 LSB	@segrel(S + A) */
#define	R_IA_64_SECREL32MSB	0x64	/* word32 MSB	@secrel(S + A) */
#define	R_IA_64_SECREL32LSB	0x65	/* word32 LSB	@secrel(S + A) */
#define	R_IA_64_SECREL64MSB	0x66	/* word64 MSB	@secrel(S + A) */
#define	R_IA_64_SECREL64LSB	0x67	/* word64 LSB	@secrel(S + A) */
#define	R_IA_64_REL32MSB	0x6c	/* word32 MSB	BD + A */
#define	R_IA_64_REL32LSB	0x6d	/* word32 LSB	BD + A */
#define	R_IA_64_REL64MSB	0x6e	/* word64 MSB	BD + A */
#define	R_IA_64_REL64LSB	0x6f	/* word64 LSB	BD + A */
#define	R_IA_64_LTV32MSB	0x74	/* word32 MSB	S + A */
#define	R_IA_64_LTV32LSB	0x75	/* word32 LSB	S + A */
#define	R_IA_64_LTV64MSB	0x76	/* word64 MSB	S + A */
#define	R_IA_64_LTV64LSB	0x77	/* word64 LSB	S + A */
#define	R_IA_64_PCREL21BI	0x79	/* immediate21 form1 S + A - P */
#define	R_IA_64_PCREL22		0x7a	/* immediate22	S + A - P */
#define	R_IA_64_PCREL64I	0x7b	/* immediate64	S + A - P */
#define	R_IA_64_IPLTMSB		0x80	/* function descriptor MSB special */
#define	R_IA_64_IPLTLSB		0x81	/* function descriptor LSB speciaal */
#define	R_IA_64_SUB		0x85	/* immediate64	A - S */
#define	R_IA_64_LTOFF22X	0x86	/* immediate22	special */
#define	R_IA_64_LDXMOV		0x87	/* immediate22	special */
#define	R_IA_64_TPREL14		0x91	/* imm14	@tprel(S + A) */
#define	R_IA_64_TPREL22		0x92	/* imm22	@tprel(S + A) */
#define	R_IA_64_TPREL64I	0x93	/* imm64	@tprel(S + A) */
#define	R_IA_64_TPREL64MSB	0x96	/* word64 MSB	@tprel(S + A) */
#define	R_IA_64_TPREL64LSB	0x97	/* word64 LSB	@tprel(S + A) */
#define	R_IA_64_LTOFF_TPREL22	0x9a	/* imm22	@ltoff(@tprel(S+A)) */
#define	R_IA_64_DTPMOD64MSB	0xa6	/* word64 MSB	@dtpmod(S + A) */
#define	R_IA_64_DTPMOD64LSB	0xa7	/* word64 LSB	@dtpmod(S + A) */
#define	R_IA_64_LTOFF_DTPMOD22	0xaa	/* imm22	@ltoff(@dtpmod(S+A)) */
#define	R_IA_64_DTPREL14	0xb1	/* imm14	@dtprel(S + A) */
#define	R_IA_64_DTPREL22	0xb2	/* imm22	@dtprel(S + A) */
#define	R_IA_64_DTPREL64I	0xb3	/* imm64	@dtprel(S + A) */
#define	R_IA_64_DTPREL32MSB	0xb4	/* word32 MSB	@dtprel(S + A) */
#define	R_IA_64_DTPREL32LSB	0xb5	/* word32 LSB	@dtprel(S + A) */
#define	R_IA_64_DTPREL64MSB	0xb6	/* word64 MSB	@dtprel(S + A) */
#define	R_IA_64_DTPREL64LSB	0xb7	/* word64 LSB	@dtprel(S + A) */
#define	R_IA_64_LTOFF_DTPREL22	0xba	/* imm22	@ltoff(@dtprel(S+A)) */

#define	R_MIPS_NONE	0	/* No reloc */
#define	R_MIPS_16	1	/* Direct 16 bit */
#define	R_MIPS_32	2	/* Direct 32 bit */
#define	R_MIPS_REL32	3	/* PC relative 32 bit */
#define	R_MIPS_26	4	/* Direct 26 bit shifted */
#define	R_MIPS_HI16	5	/* High 16 bit */
#define	R_MIPS_LO16	6	/* Low 16 bit */
#define	R_MIPS_GPREL16	7	/* GP relative 16 bit */
#define	R_MIPS_LITERAL	8	/* 16 bit literal entry */
#define	R_MIPS_GOT16	9	/* 16 bit GOT entry */
#define	R_MIPS_PC16	10	/* PC relative 16 bit */
#define	R_MIPS_CALL16	11	/* 16 bit GOT entry for function */
#define	R_MIPS_GPREL32	12	/* GP relative 32 bit */
#define	R_MIPS_64	18	/* Direct 64 bit */
#define	R_MIPS_GOT_DISP	19
#define	R_MIPS_GOT_PAGE	20
#define	R_MIPS_GOT_OFST	21
#define	R_MIPS_GOT_HI16	22	/* GOT HI 16 bit */
#define	R_MIPS_GOT_LO16	23	/* GOT LO 16 bit */
#define	R_MIPS_SUB	24
#define	R_MIPS_CALLHI16 30	/* upper 16 bit GOT entry for function */
#define	R_MIPS_CALLLO16 31	/* lower 16 bit GOT entry for function */
#define	R_MIPS_JALR	37
#define	R_MIPS_TLS_GD	42
#define	R_MIPS_COPY	126
#define	R_MIPS_JUMP_SLOT	127

#define	R_PPC_NONE		0	/* No relocation. */
#define	R_PPC_ADDR32		1
#define	R_PPC_ADDR24		2
#define	R_PPC_ADDR16		3
#define	R_PPC_ADDR16_LO		4
#define	R_PPC_ADDR16_HI		5
#define	R_PPC_ADDR16_HA		6
#define	R_PPC_ADDR14		7
#define	R_PPC_ADDR14_BRTAKEN	8
#define	R_PPC_ADDR14_BRNTAKEN	9
#define	R_PPC_REL24		10
#define	R_PPC_REL14		11
#define	R_PPC_REL14_BRTAKEN	12
#define	R_PPC_REL14_BRNTAKEN	13
#define	R_PPC_GOT16		14
#define	R_PPC_GOT16_LO		15
#define	R_PPC_GOT16_HI		16
#define	R_PPC_GOT16_HA		17
#define	R_PPC_PLTREL24		18
#define	R_PPC_COPY		19
#define	R_PPC_GLOB_DAT		20
#define	R_PPC_JMP_SLOT		21
#define	R_PPC_RELATIVE		22
#define	R_PPC_LOCAL24PC		23
#define	R_PPC_UADDR32		24
#define	R_PPC_UADDR16		25
#define	R_PPC_REL32		26
#define	R_PPC_PLT32		27
#define	R_PPC_PLTREL32		28
#define	R_PPC_PLT16_LO		29
#define	R_PPC_PLT16_HI		30
#define	R_PPC_PLT16_HA		31
#define	R_PPC_SDAREL16		32
#define	R_PPC_SECTOFF		33
#define	R_PPC_SECTOFF_LO	34
#define	R_PPC_SECTOFF_HI	35
#define	R_PPC_SECTOFF_HA	36

/*
 * 64-bit relocations
 */
#define	R_PPC64_ADDR64		38
#define	R_PPC64_ADDR16_HIGHER	39
#define	R_PPC64_ADDR16_HIGHERA	40
#define	R_PPC64_ADDR16_HIGHEST	41
#define	R_PPC64_ADDR16_HIGHESTA	42
#define	R_PPC64_UADDR64		43
#define	R_PPC64_REL64		44
#define	R_PPC64_PLT64		45
#define	R_PPC64_PLTREL64	46
#define	R_PPC64_TOC16		47
#define	R_PPC64_TOC16_LO	48
#define	R_PPC64_TOC16_HI	49
#define	R_PPC64_TOC16_HA	50
#define	R_PPC64_TOC		51
#define	R_PPC64_DTPMOD64	68
#define	R_PPC64_TPREL64		73
#define	R_PPC64_DTPREL64	78

/*
 * TLS relocations
 */
#define	R_PPC_TLS		67
#define	R_PPC_DTPMOD32		68
#define	R_PPC_TPREL16		69
#define	R_PPC_TPREL16_LO	70
#define	R_PPC_TPREL16_HI	71
#define	R_PPC_TPREL16_HA	72
#define	R_PPC_TPREL32		73
#define	R_PPC_DTPREL16		74
#define	R_PPC_DTPREL16_LO	75
#define	R_PPC_DTPREL16_HI	76
#define	R_PPC_DTPREL16_HA	77
#define	R_PPC_DTPREL32		78
#define	R_PPC_GOT_TLSGD16	79
#define	R_PPC_GOT_TLSGD16_LO	80
#define	R_PPC_GOT_TLSGD16_HI	81
#define	R_PPC_GOT_TLSGD16_HA	82
#define	R_PPC_GOT_TLSLD16	83
#define	R_PPC_GOT_TLSLD16_LO	84
#define	R_PPC_GOT_TLSLD16_HI	85
#define	R_PPC_GOT_TLSLD16_HA	86
#define	R_PPC_GOT_TPREL16	87
#define	R_PPC_GOT_TPREL16_LO	88
#define	R_PPC_GOT_TPREL16_HI	89
#define	R_PPC_GOT_TPREL16_HA	90

/*
 * The remaining relocs are from the Embedded ELF ABI, and are not in the
 *  SVR4 ELF ABI.
 */

#define	R_PPC_EMB_NADDR32	101
#define	R_PPC_EMB_NADDR16	102
#define	R_PPC_EMB_NADDR16_LO	103
#define	R_PPC_EMB_NADDR16_HI	104
#define	R_PPC_EMB_NADDR16_HA	105
#define	R_PPC_EMB_SDAI16	106
#define	R_PPC_EMB_SDA2I16	107
#define	R_PPC_EMB_SDA2REL	108
#define	R_PPC_EMB_SDA21		109
#define	R_PPC_EMB_MRKREF	110
#define	R_PPC_EMB_RELSEC16	111
#define	R_PPC_EMB_RELST_LO	112
#define	R_PPC_EMB_RELST_HI	113
#define	R_PPC_EMB_RELST_HA	114
#define	R_PPC_EMB_BIT_FLD	115
#define	R_PPC_EMB_RELSDA	116

/*
 * RISC-V relocation types.
 */

/* Relocation types used by the dynamic linker. */
#define	R_RISCV_NONE		0
#define	R_RISCV_32		1
#define	R_RISCV_64		2
#define	R_RISCV_RELATIVE	3
#define	R_RISCV_COPY		4
#define	R_RISCV_JUMP_SLOT	5
#define	R_RISCV_TLS_DTPMOD32	6
#define	R_RISCV_TLS_DTPMOD64	7
#define	R_RISCV_TLS_DTPREL32	8
#define	R_RISCV_TLS_DTPREL64	9
#define	R_RISCV_TLS_TPREL32	10
#define	R_RISCV_TLS_TPREL64	11

/* Relocation types not used by the dynamic linker. */
#define	R_RISCV_BRANCH		16
#define	R_RISCV_JAL		17
#define	R_RISCV_CALL		18
#define	R_RISCV_CALL_PLT	19
#define	R_RISCV_GOT_HI20	20
#define	R_RISCV_TLS_GOT_HI20	21
#define	R_RISCV_TLS_GD_HI20	22
#define	R_RISCV_PCREL_HI20	23
#define	R_RISCV_PCREL_LO12_I	24
#define	R_RISCV_PCREL_LO12_S	25
#define	R_RISCV_HI20		26
#define	R_RISCV_LO12_I		27
#define	R_RISCV_LO12_S		28
#define	R_RISCV_TPREL_HI20	29
#define	R_RISCV_TPREL_LO12_I	30
#define	R_RISCV_TPREL_LO12_S	31
#define	R_RISCV_TPREL_ADD	32
#define	R_RISCV_ADD8		33
#define	R_RISCV_ADD16		34
#define	R_RISCV_ADD32		35
#define	R_RISCV_ADD64		36
#define	R_RISCV_SUB8		37
#define	R_RISCV_SUB16		38
#define	R_RISCV_SUB32		39
#define	R_RISCV_SUB64		40
#define	R_RISCV_GNU_VTINHERIT	41
#define	R_RISCV_GNU_VTENTRY	42
#define	R_RISCV_ALIGN		43
#define	R_RISCV_RVC_BRANCH	44
#define	R_RISCV_RVC_JUMP	45

#define	R_SPARC_NONE		0
#define	R_SPARC_8		1
#define	R_SPARC_16		2
#define	R_SPARC_32		3
#define	R_SPARC_DISP8		4
#define	R_SPARC_DISP16		5
#define	R_SPARC_DISP32		6
#define	R_SPARC_WDISP30		7
#define	R_SPARC_WDISP22		8
#define	R_SPARC_HI22		9
#define	R_SPARC_22		10
#define	R_SPARC_13		11
#define	R_SPARC_LO10		12
#define	R_SPARC_GOT10		13
#define	R_SPARC_GOT13		14
#define	R_SPARC_GOT22		15
#define	R_SPARC_PC10		16
#define	R_SPARC_PC22		17
#define	R_SPARC_WPLT30		18
#define	R_SPARC_COPY		19
#define	R_SPARC_GLOB_DAT	20
#define	R_SPARC_JMP_SLOT	21
#define	R_SPARC_RELATIVE	22
#define	R_SPARC_UA32		23
#define	R_SPARC_PLT32		24
#define	R_SPARC_HIPLT22		25
#define	R_SPARC_LOPLT10		26
#define	R_SPARC_PCPLT32		27
#define	R_SPARC_PCPLT22		28
#define	R_SPARC_PCPLT10		29
#define	R_SPARC_10		30
#define	R_SPARC_11		31
#define	R_SPARC_64		32
#define	R_SPARC_OLO10		33
#define	R_SPARC_HH22		34
#define	R_SPARC_HM10		35
#define	R_SPARC_LM22		36
#define	R_SPARC_PC_HH22		37
#define	R_SPARC_PC_HM10		38
#define	R_SPARC_PC_LM22		39
#define	R_SPARC_WDISP16		40
#define	R_SPARC_WDISP19		41
#define	R_SPARC_GLOB_JMP	42
#define	R_SPARC_7		43
#define	R_SPARC_5		44
#define	R_SPARC_6		45
#define	R_SPARC_DISP64		46
#define	R_SPARC_PLT64		47
#define	R_SPARC_HIX22		48
#define	R_SPARC_LOX10		49
#define	R_SPARC_H44		50
#define	R_SPARC_M44		51
#define	R_SPARC_L44		52
#define	R_SPARC_REGISTER	53
#define	R_SPARC_UA64		54
#define	R_SPARC_UA16		55
#define	R_SPARC_TLS_GD_HI22	56
#define	R_SPARC_TLS_GD_LO10	57
#define	R_SPARC_TLS_GD_ADD	58
#define	R_SPARC_TLS_GD_CALL	59
#define	R_SPARC_TLS_LDM_HI22	60
#define	R_SPARC_TLS_LDM_LO10	61
#define	R_SPARC_TLS_LDM_ADD	62
#define	R_SPARC_TLS_LDM_CALL	63
#define	R_SPARC_TLS_LDO_HIX22	64
#define	R_SPARC_TLS_LDO_LOX10	65
#define	R_SPARC_TLS_LDO_ADD	66
#define	R_SPARC_TLS_IE_HI22	67
#define	R_SPARC_TLS_IE_LO10	68
#define	R_SPARC_TLS_IE_LD	69
#define	R_SPARC_TLS_IE_LDX	70
#define	R_SPARC_TLS_IE_ADD	71
#define	R_SPARC_TLS_LE_HIX22	72
#define	R_SPARC_TLS_LE_LOX10	73
#define	R_SPARC_TLS_DTPMOD32	74
#define	R_SPARC_TLS_DTPMOD64	75
#define	R_SPARC_TLS_DTPOFF32	76
#define	R_SPARC_TLS_DTPOFF64	77
#define	R_SPARC_TLS_TPOFF32	78
#define	R_SPARC_TLS_TPOFF64	79

#define	R_X86_64_NONE		0	/* No relocation. */
#define	R_X86_64_64		1	/* Add 64 bit symbol value. */
#define	R_X86_64_PC32		2	/* PC-relative 32 bit signed sym value. */
#define	R_X86_64_GOT32		3	/* PC-relative 32 bit GOT offset. */
#define	R_X86_64_PLT32		4	/* PC-relative 32 bit PLT offset. */
#define	R_X86_64_COPY		5	/* Copy data from shared object. */
#define	R_X86_64_GLOB_DAT	6	/* Set GOT entry to data address. */
#define	R_X86_64_JMP_SLOT	7	/* Set GOT entry to code address. */
#define	R_X86_64_RELATIVE	8	/* Add load address of shared object. */
#define	R_X86_64_GOTPCREL	9	/* Add 32 bit signed pcrel offset to GOT. */
#define	R_X86_64_32		10	/* Add 32 bit zero extended symbol value */
#define	R_X86_64_32S		11	/* Add 32 bit sign extended symbol value */
#define	R_X86_64_16		12	/* Add 16 bit zero extended symbol value */
#define	R_X86_64_PC16		13	/* Add 16 bit signed extended pc relative symbol value */
#define	R_X86_64_8		14	/* Add 8 bit zero extended symbol value */
#define	R_X86_64_PC8		15	/* Add 8 bit signed extended pc relative symbol value */
#define	R_X86_64_DTPMOD64	16	/* ID of module containing symbol */
#define	R_X86_64_DTPOFF64	17	/* Offset in TLS block */
#define	R_X86_64_TPOFF64	18	/* Offset in static TLS block */
#define	R_X86_64_TLSGD		19	/* PC relative offset to GD GOT entry */
#define	R_X86_64_TLSLD		20	/* PC relative offset to LD GOT entry */
#define	R_X86_64_DTPOFF32	21	/* Offset in TLS block */
#define	R_X86_64_GOTTPOFF	22	/* PC relative offset to IE GOT entry */
#define	R_X86_64_TPOFF32	23	/* Offset in static TLS block */
#define	R_X86_64_PC64		24	/* PC-relative 64 bit signed sym value. */
#define	R_X86_64_GOTOFF64	25
#define	R_X86_64_GOTPC32	26
#define	R_X86_64_GOT64		27
#define	R_X86_64_GOTPCREL64	28
#define	R_X86_64_GOTPC64	29
#define	R_X86_64_GOTPLT64	30
#define	R_X86_64_PLTOFF64	31
#define	R_X86_64_SIZE32		32
#define	R_X86_64_SIZE64		33
#define	R_X86_64_GOTPC32_TLSDESC 34
#define	R_X86_64_TLSDESC_CALL	35
#define	R_X86_64_TLSDESC	36
#define	R_X86_64_IRELATIVE	37

#endif /* !_ELF_HDR_ */
