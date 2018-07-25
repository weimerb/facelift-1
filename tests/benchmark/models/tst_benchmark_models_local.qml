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
import benchmark.models 1.0
import "benchmark_models.js" as Benchmark

TestCase {
    name: "benchmark-model-local"

    BenchmarkModelAPI {
        id: api
    }


    function initTestCase() {
        Benchmark.checkInit();
    }


    function benchmark_large_cached() {
        Benchmark.cached(api.largeModel);
    }

    function benchmark_large_half_cached() {
        Benchmark.halfCached(api.largeModel);
    }

    function benchmark_large_not_cached() {
        Benchmark.notCached(api.largeModel);
    }

    function benchmark_large_sequentially() {
        Benchmark.sequentially(api.largeModel);
    }


    function benchmark_small_cached() {
        Benchmark.cached(api.smallModel);
    }

    function benchmark_small_half_cached() {
        Benchmark.halfCached(api.smallModel);
    }

    function benchmark_small_not_cached() {
        Benchmark.notCached(api.smallModel);
    }

    function benchmark_small_sequentially() {
        Benchmark.sequentially(api.smallModel);
    }
}
