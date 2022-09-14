#ifndef G_DEFAULTS_H
#define G_DEFAULTS_H

#define DEFAULT_CONSTRUCTOR(C) C(){}

#define DEFAULT_DECONSTRUCTOR(C) ~C(){}

#define DISABLE_IMPLICIT_CONSTRUCTOR(C)   \
	C(const C&) = delete;

#define DISABLE_ASSIGNMENT_OPERATOR(C)    \
	C& operator=(const C&) = delete;

#endif
