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

import QtTest 1.2
import tests.userData 1.0

TestCase {
    name: "userData"

    ProducerAPI {
        id: producer
    }

    ConsumerAPI {
        id: consumer
    }

    function initTestCase() {
        tryVerify(function() { return producer.ready; });
        tryVerify(function() { return consumer.ready; });
        producer.produceUserData(Type.E_INT);
        verify(consumer.consumeUserData(Type.E_INT, producer.testStruct), "int test")
        producer.produceUserData(Type.E_STRING);
        verify(consumer.consumeUserData(Type.E_STRING, producer.testStruct), "string test")
        producer.produceUserData(Type.E_STRUCT);
        verify(consumer.consumeUserData(Type.E_STRUCT, producer.testStruct), "struct test")
        producer.produceUserData(Type.E_MAP);
        verify(consumer.consumeUserData(Type.E_MAP, producer.testStruct), "map test")
    }
}
