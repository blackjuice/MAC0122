#ifndef H_SELECTOR_DEFINED
#define H_SELECTOR_DEFINED

enum languages {pt_BR = 0, en = 1, es = 2};   
typedef enum languages Lang;
typedef void (*HELLO)();

HELLO selector(Lang opt);

#endif
