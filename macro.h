#ifndef PARAPHRACE_MACRO
#define PARAPHRACE_MACRO

#define CHECK(check, ret) \
  if(!(check)) { \
    return ret; \
  }

#define CHECKVOID(check) \
 if(!(check)) { \
   return; \
 }

#endif
