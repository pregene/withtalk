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
	#warning "thread api on mingw gcc"
	#include <windows.h>
	typedef HANDLE mutex_t;
	typedef HANDLE cond_t;
	typedef HANDLE thread_t;

	#define PRTHAPI 		WINAPI
	typedef DWORD 	PRRET;
	typedef LPARAM  PRPARAM;
	#define PRRETURN(a)  0

	#define mutex_lock(m)           WaitForSingleObject(m, -1)
    #define mutex_unlock(m)         ReleaseMutex(m)
    #define mutex_init(m)           m=CreateMutex(0, FALSE, 0)
    #define mutex_destroy(m)        CloseHandle(m)
    #define cond_init(c)            c=CreateEvent(0, 0, FALSE, 0)
    #define cond_destroy(c)         CloseHandle(c)
    #define cond_wait(c)            ResetEvent(c);WaitForSingleObject(c, -1)
    #define cond_timedwait(c,m,ms,r) ResetEvent(c);r=WaitForSingleObject(c, ms)
    #define cond_signal(c)          SetEvent(c)
    #define thread_create(h,f,p)  	{ DWORD d; h=CreateThread(0, 1024, f, p, 0, &d); }
    #define thread_term(h)          TerminateThread(h, 0)
    #define thread_termwait(h, s)   do { \
                                        if (GetExitCodeThread(h, &(s)) == FALSE) \
                                            break; \
                                        Sleep(100); \
                                    } while (s==STILL_ACTIVE)
#elif defined(__linux__) || defined(__APPLE__) && defined(__MACH__)
	// linux platform
    #warning "thread api on linux gcc"
	#include <pthread.h>
    #include <time.h>
    #include <sys/time.h>

	typedef pthread_mutex_t mutex_t;
	typedef pthread_cond_t  cond_t;
	typedef pthread_t       thread_t;

	#define PRTHAPI 
	typedef void* PRRET;
	typedef void* PRPARAM;
	#define PRRETURN(a) (PRRET) a

	#define mutex_lock(m)           pthread_mutex_lock(&(m))
    #define mutex_unlock(m)         pthread_mutex_unlock(&(m))
    #define mutex_init(m)           pthread_mutex_init(&(m), 0)
    #define mutex_destroy(m)        pthread_mutex_destroy(&(m))
    #define cond_init(c)            pthread_cond_init(&(c), 0)
    #define cond_destroy(c)         pthread_cond_destroy(&(c))
    #define cond_signal(c)          pthread_cond_signal(&(c))
    #define cond_wait(c, m)         pthread_cond_wait(&(c), &(m))
    #define cond_timedwait(c,m,ms)  { \
                                      struct timespec tv; \
                                      struct timeval now; \
                                      gettimeofday(&now, 0); \
                                      tv.tv_sec = now.tv_sec + (ms/1000); \
                                      tv.tv_nsec = (now.tv_usec + (ms % 1000)) * 1000; \
                                      ptrhead_cond_timedwait(&(c), &(m), &tv); \
                                    }
    #define thread_create(h,f,p)    pthread_create(&(h), 0, f, p)
    #define thread_term(h)          pthread_cancel(h)
    #define thread_termwait(h, s)   pthread_join(h, (void**)&(s))
#else
	// unkown platform
    #error "Unknown Platform"
#endif

#endif // __PREGENE_COMMON_THREAD_HEADER__
