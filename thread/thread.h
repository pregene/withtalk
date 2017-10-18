#if !defined(__PREGENE_COMMON_THREAD_HEADER__)
#define __PREGENE_COMMON_THREAD_HEADER__

#pragma once 

#ifndef __PREGENE_MUTEX
#define __PREGENE_MUTEX
#endif

#ifndef __PREGENE_COND
#define __PREGENE_COND
#endif

#ifndef __PREGENE_THREAD_API
#define __PREGENE_THREAD_API
#endif

#ifdef _WIN32
	// windows platform
	#include <windows.h>
	typedef HANDLE mutex_t;
	typedef HANDLE cond_t;
	typedef HANDLE thread_t;

	#define mutex_lock(m)
	#define mutex_unlock(m)
	#define mutex_init(m)
	#define mutex_destroy(m)
	#define cond_init(c)
	#define cond_destroy(c)
	#define cond_wait(c)
	#define cond_timedwait(c, m, ms)
	#define thread_create(h,f,p,d)
	#define thread_term(h)
	#define thread_termwait(h,s)
#elif defined(__linux__)
	// linux platform
	#include <pthread.h>
	typedef pthread_mutex_t mutex_t;
	typedef pthread_cond_t  cond_t;
	typedef pthread_t       thread_t;

	#define mutex_lock(m)
	#define mutex_unlock(m)
	#define mutex_init(m)
	#define mutex_destroy(m)
	#define cond_init(c)
	#define cond_destroy(c)
	#define cond_wiat(c)
	#define cond_timedwait(c, m, ms)
	#define thread_create(h, f, p)
	#define thread_tern(h)
	#define thread_termwait(h, s)
#else
	// unkown platform
#endif

#endif // __PREGENE_COMMON_THREAD_HEADER__
