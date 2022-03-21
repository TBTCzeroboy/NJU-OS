#include <common.h>

static void os_init() {
  pmm->init();
}

static void os_run() {
  for (const char *s = "Hello World from CPU #*\n"; *s; s++) {
    putch(*s == '*' ? '0' + cpu_current() : *s);
  }
  void*a[19];
  for(int i=0;i<19;i++)a[i]=NULL;
  for(int i=15;i;i--){
    a[i]=pmm->alloc(128*i);
    //if(a[i])printf("%x\n",a[i]);
    //if(a[i])printf("%p\n",a[i]),memset(a[i],0x11,i*128);
    if(a[i])
    pmm->free(a[i]);
  }
  for(int i=15;i;i--){
  }
  while (1) ;
}

MODULE_DEF(os) = {
  .init = os_init,
  .run  = os_run,
};
