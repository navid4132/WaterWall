#include "tunnel.h"
#include "buffer_pool.h"
#include "string.h" // memset
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// `from` upstreams to `to`
void chainUp(tunnel_t *from, tunnel_t *to)
{
    from->up = to;
}
// `to` downstreams to `from`
void chainDown(tunnel_t *from, tunnel_t *to)
{
    // assert(to->dw == NULL); // 2 nodes cannot chain to 1 exact node
    // such chains are possible by a generic listener adapter
    // but the cyclic refrence detection is already done in node map
    to->dw = from;
}
// `from` <-> `to`
void chain(tunnel_t *from, tunnel_t *to)
{
    chainUp(from, to);
    chainDown(from, to);
    to->chain_index = from->chain_index + 1;
}

tunnel_t *newTunnel(void)
{
    tunnel_t *t = malloc(sizeof(tunnel_t));
    *t          = (tunnel_t){
                 .upStream   = &defaultUpStream,
                 .downStream = &defaultDownStream,
    };
    return t;
}

pool_item_t *allocLinePoolHandle(struct generic_pool_s *pool)
{
    (void) pool;
    return malloc(sizeof(line_t));
}
void destroyLinePoolHandle(struct generic_pool_s *pool, pool_item_t *item)
{
    (void) pool;
    free(item);
}

pool_item_t *allocContextPoolHandle(struct generic_pool_s *pool)
{
    (void) pool;
    return malloc(sizeof(context_t));
}

void destroyContextPoolHandle(struct generic_pool_s *pool, pool_item_t *item)
{
    (void) pool;
    free(item);
}

void defaultUpStream(tunnel_t *self, context_t *c)
{
    if (self->up != NULL)
    {
        self->up->upStream(self->up, c);
    }
}

void defaultDownStream(tunnel_t *self, context_t *c)
{
    if (self->dw != NULL)
    {
        self->dw->downStream(self->dw, c);
    }
}
