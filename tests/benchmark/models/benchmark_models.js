/**********************************************************************
**
** Copyright (C) 2018 Luxoft Sweden AB
**
** This file is part of the FaceLift project
**
** Permission is hereby granted, free of charge, to any person
** obtaining a copy of this software and associated documentation files
** (the "Software"), to deal in the Software without restriction,
** including without limitation the rights to use, copy, modify, merge,
** publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so,
** subject to the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
** NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
** BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
** ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
** CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
** SPDX-License-Identifier: MIT
**
**********************************************************************/


function checkInit() {
    tryVerify(function() { return api.ready; });
    verify(api.smallModel);
    compare(api.smallModel.rowCount(), 2000);
    verify(api.largeModel);
    compare(api.largeModel.rowCount(), 2000);

    // fill cache
    compare(api.largeModel.data(api.largeModel.index(999, 0)).id, 42);
    compare(api.smallModel.data(api.smallModel.index(999, 0)).id, 42);
}


function cached(model) {
    for(var i = 0; i < model.rowCount(); ++i) {
        compare(model.data(model.index(999, 0)).id, 42);
    }
}

function halfCached(model) {
    for(var i = 0; i < model.rowCount(); i+=13) {
        compare(model.data(model.index(i, 0)).id, 42);
    }
}

function notCached(model) {
    for(var i = 12; i < model.rowCount(); i+=25) {
        compare(model.data(model.index(i, 0)).id, 42);
    }
}

function sequentially(model) {
    for(var i = 0; i < model.rowCount(); ++i) {
        compare(model.data(model.index(i, 0)).id, 42);
    }
}


/******************************************************************************

Cached
------
Access: 999 : same item 2000 times

Half cached
-----------
Access: 0, 13, 26,... : in total 2000/13 = 154 items
IPC: every 13th is a cache miss, hence 154 times read of 13 items
     (in total all items instead of only 154)

Not cached
----------
Access: 12, 37, 62, ... : in total 2000/25 = 80 items
IPC: each is a cache miss, hence 80 times read of 25 items
     (in total all items instead of only 80)

Sequentially
------------
Access: 0, 1, 2, ... : in total 2000 items
IPC: every 13th is a cache miss, hence 154 times read of 13 items
     (in total all items are read, of course, as in local case)

Large: ~360 Bytes
Small:    4 Bytes

******************************************************************************/
