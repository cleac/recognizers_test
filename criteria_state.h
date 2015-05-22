/*
This file is part of recognizers_test

Copyright (C) 2015  Alexander Nesterenko <nestorf250@gmail.com>

This program is free software: you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see < http : //www.gnu.org/licenses/>.
*/

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
