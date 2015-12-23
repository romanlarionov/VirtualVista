
#ifndef VIRTUALVISTA_H
#define VIRTUALVISTA_H

#define MILLISECOND 1000.0 // todo: make sure this doesn't conflict with anything
#define SAFE_DELETE( p ) { if(p) { delete (p); (p) = NULL; } }

#endif // VIRTUALVISTA_H