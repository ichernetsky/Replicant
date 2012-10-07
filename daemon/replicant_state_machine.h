/* Copyright (c) 2012, Robert Escriva
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Replicant nor the names of its contributors may be
 *       used to endorse or promote products derived from this software without
 *       specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef replicant_state_machine_h_
#define replicant_state_machine_h_
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* C */
#include <stdint.h>
#include <stdlib.h>

struct replicant_state_machine_actions
{
    void* ctx;
    uint64_t (*client)(void* ctx);
    void (*log)(void* ctx, const char* msg);
    int (*set_response)(void* ctx, const char* data, size_t data_sz);
};

typedef void* (*replicant_ctor)(struct replicant_state_machine_actions* actions);
typedef void* (*replicant_rtor)(struct replicant_state_machine_actions* actions,
                                const char* data, size_t sz);
typedef void (*replicant_dtor)(void*);
typedef void (*replicant_snap)(struct replicant_state_machine_actions* actions,
                               void*,
                               char** data, size_t* sz);
typedef void (*replicant_step)(struct replicant_state_machine_actions* actions,
                               void* obj,
                               const char* data,
                               size_t data_sz);

struct replicant_state_machine_step
{
    const char* name;
    replicant_step func;
};

struct replicant_state_machine
{
    replicant_ctor ctor;
    replicant_rtor rtor;
    replicant_dtor dtor;
    replicant_snap snap;
    struct replicant_state_machine_step steps[];
};

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* replicant_state_machine_h_ */
