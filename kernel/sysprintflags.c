#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/proc_fs.h>
#include<linux/seq_file.h>
#include<linux/sched.h>
#include<linux/list.h>
#include<linux/mm.h>
#include<asm/pgtable.h>
#include<asm/page.h>
#include<linux/slab.h>
#include<linux/delay.h>

char* translateFlagsToString(unsigned long flag){
	switch(flag){
		default:
			return "unregistered flag";
		case PG_locked:
			return "PG_locked";
		case PG_error:
			return 	"PG_error";
		case PG_referenced:
			return 	"PG_referenced";
		case PG_uptodate:
			return 	"PG_uptodate";
		case PG_dirty:
			return 	"PG_dirty";
		case PG_lru:
			return 	"PG_lru";
		case PG_active:
			return 	"PG_active";
			/*
			   case PG_waiters:
			   return 	"PG_waiters";
			 */
		case PG_slab:
			return 	"PG_slab";
			/*
			   case PG_owner_priv_1:
			   return 	"PG_owner_priv_1";
			 */
		case PG_arch_1:
			return 	"PG_arch_1";
		case PG_reserved:
			return 	"PG_reserved";
		case PG_private:
			return 	"PG_private";
		case PG_private_2:
			return 	"PG_private_2";
		case PG_writeback:
			return 	"PG_writeback";
		case PG_head:
			return 	"PG_head";
		case PG_mappedtodisk:
			return 	"PG_mappedtodisk";
		case PG_reclaim:
			return 	"PG_reclaim";		
		case PG_swapbacked:
			return 	"PG_swapbacked";
		case PG_unevictable:
			return 	"PG_unevictable";
		case PG_mlocked:
			return "PG_mlocked";
		case PG_uncached:
			return "PG_uncached";
		case PG_hwpoison:
			return "PG_hwpoison";
		case PG_young:
			return "PG_young";
		case PG_idle:
			return "PG_idle";
		case __NR_PAGEFLAGS:
			return "__NR_PAGEFLAGS";
		case PG_checked:
			return "PG_checked ";
		case PG_swapcache:
			return "PG_swapcache ";
	}
}

asmlinkage long sys_printflags(unsigned long addr)
{
	pgd_t * pgd;
	pmd_t * pmd;
	pte_t * pte;
	struct page *page = NULL;
	pud_t * pud;
	struct mm_struct *mm = current->mm;
	int i;

	if(addr){
		pgd = pgd_offset(mm, addr);
		if(!pgd_present(*pgd))
			goto done;
		pud = pud_offset(pgd, addr);
		if(!pud_present(*pud))
			goto done;
		pmd = pmd_offset(pud, addr);
		if(!pmd_present(*pmd))
			goto done;
		pte = pte_offset_map(pmd, addr);
		if(!pte_present(*pte)){
			goto done;
		}
	}
	page = pte_page(*pte);
	for(i=0; i<=PG_unevictable; i++){
		if((page->flags)>>i&1UL){
			printk("%s ",translateFlagsToString(i));
		}
	}
	printk("\n");


	return 0;
done:
	printk("Error at printflags done\n ");
	return -1;
}
