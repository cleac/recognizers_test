#ifndef CRITERIA_STATE_H
#define CRITERIA_STATE_H

#ifdef __cplusplus
extern "C" {
#endif

struct _criteria {
    int lin[3];
    int count;
    _criteria* next;
};

struct _state {
    int index;
    _criteria criteria;
    _state* next;
};
_state* getLastState();
_state* getFirstState();

static _state* state;

_state* getLastState() {
    _state* iter = state;
    while (iter->next)
        iter = iter->next;
    return iter;
}

_state* getFirstState() {
    return state;
}

#ifdef __cplusplus
}
#endif

#endif // CRITERIA_STATE_H
