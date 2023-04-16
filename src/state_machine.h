#ifndef C_STATE_MACHINE_H_INCLUDED
#define C_STATE_MACHINE_H_INCLUDED


#define STATE_MACHINE_DECLARE(name, event_t)                                                                           \
    uint8_t name##_send_event(name##_state_machine_t *sm, void *user_ptr, event_t event);

#define STATE_MACHINE_DEFINE(name, event_t)                                                                            \
    typedef int (*name##_event_manager_t)(event_t, void *);                                                            \
    typedef struct {                                                                                                   \
        name##_event_manager_t event;                                                                                  \
        void (*entry)(void *);                                                                                         \
        void (*exit)(void *);                                                                                          \
    } name##_node_t;                                                                                                   \
    typedef struct {                                                                                                   \
        name##_node_t *nodes;                                                                                          \
        unsigned int   node_index;                                                                                     \
    } name##_state_machine_t;                                                                                          \
                                                                                                                       \
    int name##_send_event(name##_state_machine_t *sm, void *user_ptr, event_t event) {                                 \
        int res = sm->nodes[sm->node_index].event(event, user_ptr);                                                    \
                                                                                                                       \
        if (res >= 0) {                                                                                                \
            if (sm->nodes[sm->node_index].exit != NULL) {                                                              \
                sm->nodes[sm->node_index].exit(user_ptr);                                                              \
            }                                                                                                          \
            sm->node_index = (unsigned int)res;                                                                        \
            if (sm->nodes[sm->node_index].entry != NULL) {                                                             \
                sm->nodes[sm->node_index].entry(user_ptr);                                                             \
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
