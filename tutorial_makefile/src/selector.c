#include "en.h"
#include "es.h"
#include "pt_BR.h"
#include "selector.h"

HELLO selector(Lang opt)
{
    void (*hello)();
    switch(opt){
        case pt_BR: 
            hello = &pt_BR_hello;
            break;
        case en: 
            hello = &en_hello; 
            break;
        case es: 
            hello = &es_hello;
            break;    
    } 
    return hello;   
}
