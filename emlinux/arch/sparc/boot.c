/**
 * @file
 * @brief
 * __main is located at 0x40000000 and called by prom.S. it inits mmu, and
 * calls the kernel with adequate parameters. emulates a sparc v0 prom for
 * kernel.
 *
 * @author
 * Copyright (C) 2003 Konrad Eisele <eiselekd@web.de>
 * Copyright (C) 2004 Stefan Holst <mail@s-holst.de>
 */

#include <linux/kernel.h>
#include <asm/asi.h>
#include <asm/pgtsrmmu.h>
#include <asm/leon.h>

#if (KERNEL_VERSION == 33)
#include <asm/leon_amba.h>
#define CONFIG_LEON_3
#endif

#include <asm/page.h>
#include <linux/string.h>
#include <asm/oplib.h>
#include <asm/idprom.h>
#include <asm/machines.h>

/* ram configuration */
#define LEONSETUP_MEM_BASEADDR 0x40000000

/* for __va */
#define phys_base LEONSETUP_MEM_BASEADDR

struct property {
        char *name;
        char *value;
        int length;
};

struct node {
        int level;
        struct property *properties;
};

static void leon_reboot(char *bcommand);
static void leon_halt(void);
static int leon_nbputchar(int c);
static int leon_nbgetchar(void);

static int no_nextnode(int node);
static int no_child(int node);
static int no_proplen(int node,char *name);
static int no_getprop(int node,char *name,char *value);
static int no_setprop(int node,char *name,char *value,int len);
static char *no_nextprop(int node,char *name);

/* a self contained prom info structure */

struct leon_prom_info {
        int freq_khz;
        int leon_nctx;
        int mids[32];
        int baudrates[2];
        struct property root_properties[4];
        struct property cpu_properties[7];
        struct property uart_properties[7];
#undef  CPUENTRY
#define CPUENTRY(idx) struct property cpu_properties##idx[4];
        CPUENTRY(1)
        CPUENTRY(2)
        CPUENTRY(3)
        CPUENTRY(4)
        CPUENTRY(5)
        CPUENTRY(6)
        CPUENTRY(7)
        CPUENTRY(8)
        CPUENTRY(9)
        CPUENTRY(10)
        CPUENTRY(11)
        CPUENTRY(12)
        CPUENTRY(13)
        CPUENTRY(14)
        CPUENTRY(15)
        CPUENTRY(16)
        CPUENTRY(17)
        CPUENTRY(18)
        CPUENTRY(19)
        CPUENTRY(20)
        CPUENTRY(21)
        CPUENTRY(22)
        CPUENTRY(23)
        CPUENTRY(24)
        CPUENTRY(25)
        CPUENTRY(26)
        CPUENTRY(27)
        CPUENTRY(28)
        CPUENTRY(29)
        CPUENTRY(30)
        CPUENTRY(31)
        struct idprom idprom;
        struct linux_nodeops nodeops;
        struct linux_mlist_v0 *totphys_p;
        struct linux_mlist_v0 totphys;
        struct linux_mlist_v0 *avail_p;
        struct linux_mlist_v0 avail;
        struct linux_mlist_v0 *prommap_p;
        void (*synchook)(void);
        struct linux_arguments_v0 *bootargs_p;
        struct linux_arguments_v0 bootargs;
        struct linux_romvec romvec;
        struct node nodes[36];
        char s_device_type[12];
        char s_device_name[5];
        char s_cpu[4];
        char s_mid[4];
        char s_idprom[7];
        char s_compatability[14];
        char s_leon2[6];
        char s_mmu_nctx[9];
        char s_frequency[16];
        char s_uart1_baud[11];
        char s_uart2_baud[11];
        char s_serial[7];
        char pv_stdin;
        char pv_stdout;
        char s_uart_name[16];
        char s_uart_vendor[7];
        char s_uart_device[7];
        char s_uart_interrupts[11];
        char s_uart_reg[4];
        int uart_vendor;
        int uart_device;
        int uart_interrupts;
        int uart_reg;
        char arg[256];
};

/* static prom info */
static struct leon_prom_info spi = {
        20000, /* freq_khz */
        256, /* leon_nctx */
        {
#undef  CPUENTRY
#define CPUENTRY(idx)  idx,
                CPUENTRY(0)
                CPUENTRY(1)
                CPUENTRY(2)
                CPUENTRY(3)
                CPUENTRY(4)
                CPUENTRY(5)
                CPUENTRY(6)
                CPUENTRY(7)
                CPUENTRY(8)
                CPUENTRY(9)
                CPUENTRY(10)
                CPUENTRY(11)
                CPUENTRY(12)
                CPUENTRY(13)
                CPUENTRY(14)
                CPUENTRY(15)
                CPUENTRY(16)
                CPUENTRY(17)
                CPUENTRY(18)
                CPUENTRY(19)
                CPUENTRY(20)
                CPUENTRY(21)
                CPUENTRY(22)
                CPUENTRY(23)
                CPUENTRY(24)
                CPUENTRY(25)
                CPUENTRY(26)
                CPUENTRY(27)
                CPUENTRY(28)
                CPUENTRY(29)
                CPUENTRY(30)
                31
        },
        { /* baudrates */
                38400, 38400
        },
        { /* root_properties */
                {__va(spi.s_device_type), __va(spi.s_idprom), 7},
                {__va(spi.s_idprom), (char *) __va(&spi.idprom), sizeof(struct idprom)},
                {__va(spi.s_compatability), __va(spi.s_leon2), 5},
                {NULL, NULL, -1}
        },
        { /* cpu_properties */
                {__va(spi.s_device_type), __va(spi.s_cpu), 4},
                {__va(spi.s_mid), __va(&spi.mids[0]), 4},
                {__va(spi.s_mmu_nctx), (char *) __va(&spi.leon_nctx), 4},
                {__va(spi.s_frequency), (char *) __va(&spi.freq_khz), 4},
                {__va(spi.s_uart1_baud), (char *) __va(&spi.baudrates[0]), 4},
                {__va(spi.s_uart2_baud), (char *) __va(&spi.baudrates[1]), 4},
                {NULL, NULL, -1}
        },
        { /* uart_properties */
                 {__va(spi.s_device_name), __va(spi.s_uart_name), 16},
                 {__va(spi.s_device_type), __va(spi.s_serial), 7},
                 {__va(spi.s_uart_vendor), (char *) __va(&spi.uart_vendor), 4},
                 {__va(spi.s_uart_device), (char *) __va(&spi.uart_device), 4},
                 {__va(spi.s_uart_interrupts), (char *) __va(&spi.uart_interrupts), 4},
                 {__va(spi.s_uart_reg), (char *) __va(&spi.uart_reg), 4},
                 {NULL, NULL, -1}
        },
#undef  CPUENTRY
#define CPUENTRY(idx)							\
	{ /* cpu_properties */						\
	  {__va(spi.s_device_type), __va(spi.s_cpu), 4},		\
	  {__va(spi.s_mid), __va(&spi.mids[idx]), 4},			\
	  {__va(spi.s_frequency), (char *) __va(&spi.freq_khz), 4},	\
	  {NULL, NULL, -1}						\
	},								\

        CPUENTRY(1)
        CPUENTRY(2)
        CPUENTRY(3)
        CPUENTRY(4)
        CPUENTRY(5)
        CPUENTRY(6)
        CPUENTRY(7)
        CPUENTRY(8)
        CPUENTRY(9)
        CPUENTRY(10)
        CPUENTRY(11)
        CPUENTRY(12)
        CPUENTRY(13)
        CPUENTRY(14)
        CPUENTRY(15)
        CPUENTRY(16)
        CPUENTRY(17)
        CPUENTRY(18)
        CPUENTRY(19)
        CPUENTRY(20)
        CPUENTRY(21)
        CPUENTRY(22)
        CPUENTRY(23)
        CPUENTRY(24)
        CPUENTRY(25)
        CPUENTRY(26)
        CPUENTRY(27)
        CPUENTRY(28)
        CPUENTRY(29)
        CPUENTRY(30)
        CPUENTRY(31)

        { /* idprom */
                0x01, /* format */
		M_LEON | M_LEON3_SOC /* maybe 0x01? */, /* machine type */
                {0,0,0,0,0,0}, /* eth */
                0, /* date */
                0, /* sernum */
                0, /* checksum */
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} /* reserved */
        },
        { /* nodeops */
                __va(no_nextnode),
                __va(no_child),
                __va(no_proplen),
                __va(no_getprop),
                __va(no_setprop),
                __va(no_nextprop)
        },
        __va(&spi.totphys), /* totphys_p */
        { /* totphys */
                NULL,
                (char *) LEONSETUP_MEM_BASEADDR,
                0,
        },
        __va(&spi.avail), /* avail_p */
        { /* avail */
                NULL,
                (char *) LEONSETUP_MEM_BASEADDR,
                0,
        },
        NULL, /* prommap_p */
        NULL, /* synchook  */
        __va(&spi.bootargs), /* bootargs_p */
        { /* bootargs */
                { NULL, __va(spi.arg), NULL /*...*/
                },
                /*...*/
        },
        { /* romvec */
                0,
                0, /* sun4c v0 prom */
                0, 0,
                { __va(&spi.totphys_p), __va(&spi.prommap_p), __va(&spi.avail_p) },
                __va(&spi.nodeops),
                NULL, { NULL /* ... */ },
                __va(&spi.pv_stdin), __va(&spi.pv_stdout),
                NULL, NULL,  /* pv_getchar, pv_putchar */
                __va(leon_nbgetchar), __va(leon_nbputchar),
                NULL,
                __va(leon_reboot),
                NULL,
                NULL,
                NULL,
                __va(leon_halt),
                __va(&spi.synchook),
                { NULL },
                __va(&spi.bootargs_p)
                /*...*/
        },
        { /* nodes */
                { 0, __va(spi.root_properties+3) /* NULL, NULL, -1 */},
                { 0, __va(spi.root_properties) },
                { 1, __va(spi.cpu_properties) }, /* cpu 0, must be spi.nodes[2] see leon_prom_init()*/
                { 1, __va(spi.uart_properties) },
#undef  CPUENTRY
#define CPUENTRY(idx) \
	  { 1, __va(spi.cpu_properties##idx) }, /* cpu <idx> */
                CPUENTRY(1)
                CPUENTRY(2)
                CPUENTRY(3)
                CPUENTRY(4)
                CPUENTRY(5)
                CPUENTRY(6)
                CPUENTRY(7)
                CPUENTRY(8)
                CPUENTRY(9)
                CPUENTRY(10)
                CPUENTRY(11)
                CPUENTRY(12)
                CPUENTRY(13)
                CPUENTRY(14)
                CPUENTRY(15)
                CPUENTRY(16)
                CPUENTRY(17)
                CPUENTRY(18)
                CPUENTRY(19)
                CPUENTRY(20)
                CPUENTRY(21)
                CPUENTRY(22)
                CPUENTRY(23)
                CPUENTRY(24)
                CPUENTRY(25)
                CPUENTRY(26)
                CPUENTRY(27)
                CPUENTRY(28)
                CPUENTRY(29)
                CPUENTRY(30)
                CPUENTRY(31)
        { -1,__va(spi.root_properties+3) /* NULL, NULL, -1 */
        }
        },
        "device_type",
        "name",
        "cpu",
        "mid",
        "idprom",
        "compatability",
        "leon2",
        "mmu-nctx",
        "clock-frequency",
        "uart1_baud",
        "uart2_baud",
        "serial",
        PROMDEV_TTYA,
        PROMDEV_TTYA,
        "GAISLER_APBUART",
        "vendor",
        "device",
        "interrupts",
        "reg",
        0x1,
        0x0C,
        0x2,
        0x80000100,
        "console=ttyS0,38400 rdinit=/sbin/init"
};

static void leon_reboot(char *bcommand) {
	/* Reboot the CPU = jump to beginning of flash again. */

        while (1) {
                printk(__va("Can't reboot\n"));
        };
}

static void leon_halt(void) {
        while (1) {
                printk(__va("Halt\n"));
        };
}

/* get single char, don't care for blocking */
static int leon_nbgetchar(void) {
        return -1;
}

#define LEON_USTAT0 0x80000104
#define LEON_UDATA0 0x80000100

/* put single char, don't care for blocking*/
static int leon_nbputchar(int c) {
//#ifdef CONFIG_LEON_3
//# ifdef CONFIG_GRLIB_GAISLER_APBUART
//        extern void leon3_rs_put_char(char ch);
//        leon3_rs_put_char(c);
//# else
//        BUG();
//# endif
//#else
//        unsigned int old_cr;

//        old_cr = LEON_REGLOAD_PA(LEON_UCTRL0);
//        LEON_REGSTORE_PA(LEON_UCTRL0,(old_cr & ~(LEON_UCTRL_TI)) | (LEON_UCTRL_TE));

        while (!(LEON_BYPASS_LOAD_PA(LEON_USTAT0) & 0x4));
        LEON_BYPASS_STORE_PA(LEON_UDATA0, (unsigned char)c);

//        while (!(LEON_REGLOAD_PA(LEON_USTAT0) & 0x4));
//        LEON_REGSTORE_PA(LEON_UCTRL0,old_cr);
//#endif
        return 0;
}

static int leon_nbputstr(const char *str) {
	char *ptr = (char*) str;
	while (*ptr) {
		leon_nbputchar(*ptr++);
	}
	return leon_nbputchar('\n');
}

/* node ops */

#define bnodes ((struct node *) __va(&spi.nodes))

static int no_nextnode(int node) {
        if (bnodes[node].level == bnodes[node+1].level)
                return node+1;
        return -1;
}

static int no_child(int node) {
        if (bnodes[node].level == bnodes[node+1].level-1)
                return node+1;
        return -1;
}

static struct property *find_property(int node,char *name) {
        struct property *prop = &bnodes[node].properties[0];
        while (prop && prop->name) {
                if (strcmp(prop->name,name) == 0) return prop;
                prop++;
        }
        return NULL;
}

static int no_proplen(int node,char *name) {
        struct property *prop = find_property(node,name);
        if (prop) return prop->length;
        return -1;
}

static int no_getprop(int node,char *name,char *value) {
        struct property *prop = find_property(node,name);
        if (prop) {
                memcpy(value,prop->value,prop->length);
                return 1;
        }
        return -1;
}

static int no_setprop(int node,char *name,char *value,int len) {
        return -1;
}

static char *no_nextprop(int node,char *name) {
        struct property *prop;
        if (!name || !name[0] ) {
                return bnodes[node].properties[0].name;
        }
        prop = find_property(node,name);
        if (prop) return prop[1].name;
        return NULL;
}

#define GETREGSP(sp) __asm__ __volatile__("mov %%sp, %0" : "=r" (sp))

#ifdef CONFIG_LEON_3

#define AMBA_MAX_BUS 2
unsigned int amba_ioarea[AMBA_MAX_BUS] = {
        LEON3_IO_AREA,
        0,
};

unsigned int leon3_ahbslv_scan(register unsigned int ioarea, register unsigned int vendor,
	    register unsigned int driver, int index) {
        register unsigned int conf, i, *confp;
        register unsigned int cfg_area = (unsigned int ) (ioarea | LEON3_CONF_AREA | LEON3_AHB_SLAVE_CONF_AREA);
        register int max = LEON3_AHB_SLAVES;
        if ( ioarea != LEON3_IO_AREA )
                max = 16;
        for (i = 0; i < max; i++) {
                confp = (unsigned int*)(cfg_area + (i * LEON3_AHB_CONF_WORDS * 4));
                conf = *confp;
                if ((amba_vendor(conf) == vendor) && (amba_device(conf) == driver) && (index-- == 0) ) {
                        return (unsigned int)confp;
                }
        }
        return 0;
}

unsigned int *leon3_apbslv_scan(register unsigned int base,
	    register unsigned int vendor, register unsigned int driver) {
        register unsigned int conf, i, *confp;
        for (i = 0; i < LEON3_APB_SLAVES; i++) {
                confp = (unsigned int*)(base + (i * LEON3_APB_CONF_WORDS * 4));
                conf = *confp;
                if ((amba_vendor(conf) == vendor) && (amba_device(conf) == driver)) {
                        return confp;
                }
        }
        return 0;
}

unsigned int *leon3_getbase(register unsigned int *mbar,register unsigned int iobase) {
        register unsigned int conf = mbar[1];
        return (unsigned int *)(((iobase & 0xfff00000) |
                    ((conf & 0xfff00000)>> 12)) & (((conf & 0x0000fff0) <<4) | 0xfff00000));

}

unsigned int *leon3_getapbbase(register unsigned int vendor,register unsigned int driver) {
        unsigned int *b;
        unsigned int apb, ioarea;
        int index;
        int bus;

        for (bus=0; bus<AMBA_MAX_BUS; bus++) {

                ioarea = amba_ioarea[bus];
                if ( ioarea == 0 )
                        break;

                index=0;
                while ( (apb=leon3_ahbslv_scan(ioarea, VENDOR_GAISLER,GAISLER_APBMST, index)) != NULL ) {
                        apb = (*(unsigned int *)(apb + 16)) & LEON3_IO_AREA;
                        apb |= LEON3_CONF_AREA;
                        b = leon3_apbslv_scan(apb,vendor,driver);
                        if ( b )
                                return leon3_getbase(b,apb);
                        index++;
                }
        }
        return NULL;
}

void leon3_amba_init(void) {
        unsigned int *ahb;

        ahb = leon3_ahbslv_scan(amba_ioarea[0], VENDOR_GAISLER, GAISLER_AHB2AHB, 0);
        if ( ahb ) {
                amba_ioarea[1] = ahb[2] & 0xfff00000;
        }
}

#endif

static void leon_prom_init() {
        unsigned long i;
        unsigned char cksum, *ptr;

        unsigned long sp;
        GETREGSP(sp);

        /*
         * the frequency is actually detected using
         * (LEON_REGLOAD_PA(LEON_SRLD)+1) * 1000 * 1000; assuming that
         * bootloader or the dsumon has set up LEON_SRLD, so that timer ticks
         * on 1mhz
         */

#ifdef CONFIG_LEON_3

        leon3_amba_init();

        {
#if (KERNEL_VERSION == 33)
    		struct leon3_gptimer_regs_map *b;
    		b = (struct leon3_gptimer_regs_map *) leon3_getapbbase(VENDOR_GAISLER,GAISLER_GPTIMER);
#else
                LEON3_GpTimer_Regs_Map *b;
                b = (LEON3_GpTimer_Regs_Map *) leon3_getapbbase(VENDOR_GAISLER,GAISLER_GPTIMER);
#endif
                if (b) {
                        spi.freq_khz = ((b->scalar_reload)+1) * 1000;
                }
        }
        {
                int j = 1;
                spi.nodes[3+j].level = -1;
                spi.nodes[3+j].properties = __va(spi.root_properties+3);
        }
#else
        spi.freq_khz = (*((unsigned long*)(LEON_PREGS+LEON_SRLD))+1) * 1000;
#endif

        spi.totphys.num_bytes = 0;

        sp = sp - LEONSETUP_MEM_BASEADDR /*0x40000000*/;
        spi.totphys.num_bytes = (sp + 0x1000) & ~(0xfff);

        spi.avail.num_bytes = spi.totphys.num_bytes;

        ptr = (unsigned char *)&spi.idprom;
        for (i = cksum = 0; i <= 0x0E; i++)
                cksum ^= *ptr++;
        spi.idprom.id_cksum = cksum;
}

__inline__ void mark() {
        __asm__ __volatile__(
                "sethi	%%hi(%0), %%l0    \n\t" \
                "st    %%g0,[%%lo(%0)+%%l0]\n\t" \
        : : "i" (LEONSETUP_MEM_BASEADDR) : "l0" );
}

static inline void set_cache(unsigned long regval) {
	asm volatile("sta %0, [%%g0] %1\n\t" : :
                     "r" (regval), "i" (2) : "memory");
}

extern unsigned short bss_start,bss_end;

/* mark as section .img.main.text, to be referenced in linker script */
int __attribute__ ((__section__ (".img.main.text"))) __main(void) {

        char *c;
        void (*kernel)(struct linux_romvec *);

        /* disable mmu */
        srmmu_set_mmureg(0x00000000);
        __asm__ __volatile__("flush\n\t");

        /* clear bss */
        c = &bss_start;
        while (c < &bss_end) {
                *c=0;
                c++;
        }

        /* init prom info struct */
        leon_prom_init();
        /* mark as used for bootloader */
        mark();

        /* turn on mmu */
        extern unsigned long _bootloader_ph;
        srmmu_set_ctable_ptr(&_bootloader_ph /*LEONSETUP_MEM_BASEADDR + PAGE_SIZE*/);
        srmmu_set_context(0);
        __asm__ __volatile__("flush\n\t");
#if (KERNEL_VERSION == 33)
        srmmu_set_mmureg(0x00000001 | (LEON_PAGE_SIZE_LEON << 16));
#else
        srmmu_set_mmureg(0x00000001 | (CONFIG_PAGE_SIZE_LEON << 16));
#endif
        leon_flush_tlb_all();
        void leon_flush_cache_all();

        /* call kernel */

        kernel = (void (*)(struct linux_romvec*)) KERNBASE+LOAD_ADDR;
        leon_nbputstr("Call kernel");
        kernel(__va(&spi.romvec));

        return 1;
}
