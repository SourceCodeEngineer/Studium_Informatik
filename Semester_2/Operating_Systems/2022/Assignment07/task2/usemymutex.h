#ifndef USEMYMUTEX
#if USE_MY_MUTEX
    #define MUTEX_LOCK my_mutex_lock
    // ... other functions
#else
    #define MUTEX_LOCK pthread_mutex_lock
    // ... other functions
#endif
#endif
