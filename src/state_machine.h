#ifndef C_STATE_MACHINE_H_INCLUDED
#define C_STATE_MACHINE_H_INCLUDED


#define STATE_MACHINE_DECLARE(name, event_t)                                                                           \
    int name##_send_event(name##_state_machine_t *sm, void *user_ptr, event_t event);

#define STATE_MACHINE_DEFINE(name, event_t)                                                                            \
    typedef int (*name##_event_manager_t)(void *, event_t);                                                            \
    typedef struct {                                                                                                   \
        name##_event_manager_t event;                                                                                  \
        void (*entry)(void *);                                                                                         \
        void (*exit)(void *);                                                                                          \
    } name##_state_manager_t;                                                                                          \
    typedef struct {                                                                                                   \
        name##_state_manager_t *managers;                                                                              \
        unsigned int            state;                                                                                 \
    } name##_state_machine_t;                                                                                          \
                                                                                                                       \
    int name##_send_event(name##_state_machine_t *sm, void *user_ptr, event_t event) {                                 \
        int res = sm->managers[sm->state].event(user_ptr, event);                                                      \
                                                                                                                       \
        if (res >= 0) {                                                                                                \
            if (sm->managers[sm->state].exit != NULL) {                                                                \
                sm->managers[sm->state].exit(user_ptr);                                                                \
            }                                                                                                          \
            sm->state = res;                                                                                           \
            if (sm->managers[sm->state].entry != NULL) {                                                               \
                sm->managers[sm->state].entry(user_ptr);                                                               \
            }                                                                                                          \
            return 1;                                                                                                  \
        }                                                                                                              \
        return 0;                                                                                                      \
    }

#define STATE_MACHINE_EVENT_MANAGER(event_manager)                                                                     \
    { .event = event_manager, .entry = NULL, .exit = NULL }
#define STATE_MACHINE_MANAGER(event_manager, entry_cb, exit_cb)                                                        \
    { .event = event_manager, .entry = entry_cb, .exit = exit_cb }


#endif