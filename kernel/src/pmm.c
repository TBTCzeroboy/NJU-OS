#include <common.h>

#define PAGENUM  32000
#define PAGESIZE (4096)
#define MINSIZE  (128)
#define MAXSIZE  (16<<20)
#define MAXCPU 8

#define orderOfPage(x) ((x-0x300000)>>12)

enum{
  _128=1,_256,_512,_1024,_2048,_4096,_2p,_4p,_8p,_16p,_32p,_64p,_128p,_256p,_512p,_1024p,_2048p,_4096p
};

//static uint8_t sizeOfPage[PAGENUM];

typedef struct lock_t{
  int flag;
}lock_t;

void lockInit(lock_t *lock){
  atomic_xchg(&lock->flag,0);
}

void lock(lock_t *lock){
  while(atomic_xchg(&lock->flag,1)==1);
}

void unlock(lock_t *lock){
  atomic_xchg(&lock->flag,0);
}

typedef struct node_t{
  void *addr128;
  size_t size;
  struct node_t *next;
}node_t;

typedef struct page128{
  uint32_t status;
}page128;



static size_t tableSizeFor(size_t val){
  if (val & (val - 1)){
    val |= val>>1;
    val |= val>>2;
    val |= val>>4;
    val |= val>>8;
    val |= val>>16;
    return val+1;
  }
  else return val == 0 ? 1 : val;
}


static void *kalloc(size_t size) {
  size=tableSizeFor(size);
  return NULL;
}

static void kfree(void *ptr) {
}

static void pmm_init() {
  uintptr_t pmsize = ((uintptr_t)heap.end - (uintptr_t)heap.start);
  printf("Got %d MiB heap: [%p, %p)\n", pmsize >> 20, heap.start, heap.end);
  printf("%d\n",sizeof(void*));
  printf("%d\n",pmsize/PAGESIZE);
  printf("%d\n",cpu_count());
}

MODULE_DEF(pmm) = {
  .init  = pmm_init,
  .alloc = kalloc,
  .free  = kfree,
};