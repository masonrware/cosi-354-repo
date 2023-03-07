# Heap Caveats

- Don't free memory more than once
- Don't read and write once you have freed memory
- always check if your program has run out of memory
  - if the allocator returns NULL

# Memory Heirarchy

### **Bottom Level: L6 Network Storage**
Lots of storage within a local or WAN network
However, slow compared to hardware access

### **L5: Secondary Storage (SS)**


### **L4: Main Memory**
Main Memory (MM) is much slower than close to the CPU storage
about 400x slower

### **L1->L3**
Are staging areas or caches.
These are places where data that we know we will need is loaded and waiting for the CPU to access it quicker.

## Cache

Is a smaller faster memory that acts as a staging area for data stored in larger slower memory

**Memory Units**
4 byte word: size used by CPU   transfer between L1 and CPU
32 byte blocks: size used by C  transfer between Cache levels & MM
4k byte pages: size used by MM  transfer between MM & SS

# Locality
temporal locatlity is when a recently accessed memory location is repeatedly accessed in the near future.

spatial localtiy is when a recently accessed memory location is followed by nearby memory locations being accessed in the near future.

locality is designed into hardware, OS, apps.


The caching system anticipates:
temporal: anticipates data will be reused so it copies and saves in cache.
spatial: anticipates nearby data will be used so it copies and blocks in cache.

cache block is a unit of memory transferred between main memory and cache levels.

### Good or Bad Locality?

sequencing? bad temp, good spatial
selection? bad temp, bad spatial
repetition? good temp, good spatial