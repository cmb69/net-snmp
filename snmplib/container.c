#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/library/container.h>
#include <net-snmp/library/container_binary_array.h>
#include <net-snmp/library/container_list_ssll.h>
#include <net-snmp/library/container_null.h>

/*------------------------------------------------------------------
 */
static netsnmp_container *containers = NULL;

typedef struct container_type_s {
   const char                 *name;
   netsnmp_factory            *factory;
} container_type;

netsnmp_factory *
netsnmp_container_get_factory(const char *type);

static int
_ba_release_with_free(netsnmp_container *container);
void 
_ba_free_container_type(void *data, void *context);
static int
_ba_remove_with_free(netsnmp_container *container, const void *data);

/* return top containers */
netsnmp_container **
netsnmp_get_top_containers(void)
{
    return &containers;
}

void
netsnmp_release_if_top(netsnmp_container *cont)
{
    if (cont == containers) {
        containers = NULL;
    }
}

/*------------------------------------------------------------------
 */
void
netsnmp_container_init_list(void)
{
    container_type *ct;
    
    if (NULL != containers)
        return;

    /*
     * create a binary arry container to hold container
     * factories
     */
    containers = netsnmp_container_get_binary_array();
    containers->compare = netsnmp_compare_cstring;
    containers->cfree = _ba_release_with_free;
    containers->remove = _ba_remove_with_free;

    /*
     * register containers
     */
    netsnmp_container_binary_array_init();
    netsnmp_container_ssll_init();
    netsnmp_container_null_init();

    /*
     * default aliases for some containers
     */
    netsnmp_container_register("table_container",
                               netsnmp_container_get_factory("binary_array"));
    netsnmp_container_register("linked_list",
                               netsnmp_container_get_factory("sorted_singly_linked_list"));
    netsnmp_container_register("ssll_container",
                               netsnmp_container_get_factory("sorted_singly_linked_list"));
}

void
netsnmp_clear_container(void)
{
    DEBUGMSGTL(("container", "netsnmp_clear_container() called\n"));
    if (containers == NULL)
	return;

    CONTAINER_FREE(containers);
    containers = NULL;
}

int
netsnmp_container_register(const char* name, netsnmp_factory *f)
{
    container_type *ct, tmp;

    tmp.name = name;
    ct = CONTAINER_FIND(containers, &tmp);
    if (NULL!=ct) {
        DEBUGMSGT(("container_registry",
                   "replacing previous container factory\n"));
        ct->factory = f;
    }
    else {
        ct = SNMP_MALLOC_TYPEDEF(container_type);
        if (NULL == ct)
            return -1;
        ct->name = strdup(name);
        ct->factory = f;
        CONTAINER_INSERT(containers, ct);
    }
    DEBUGMSGT(("container_registry", "registered container factory %s (%s)\n",
               ct->name, f->product));

    return 0;
}

/*------------------------------------------------------------------
 */
netsnmp_factory *
netsnmp_container_get_factory(const char *type)
{
    container_type ct, *found;
    
    ct.name = type;
    found = CONTAINER_FIND(containers, &ct);

    return found ? found->factory : NULL;
}

netsnmp_factory *
netsnmp_container_find_factory(const char *type_list)
{
    netsnmp_factory   *f = NULL;
    char              *list, *entry;

    if (NULL==type_list)
        return NULL;

    list = strdup(type_list);
    entry = strtok(list, ":");
    while(entry) {
        f = netsnmp_container_get_factory(entry);
        if (NULL != f)
            break;
        entry = strtok(NULL, ":");
    }

    free(list);
    return f;
}

/*------------------------------------------------------------------
 */
netsnmp_container *
netsnmp_container_get(const char *type)
{
    netsnmp_factory *f = netsnmp_container_get_factory(type);
    if (f)
        return f->produce();

    return NULL;
}

int
netsnmp_container_get_noalloc(const char *type, netsnmp_container *mem)
{
    netsnmp_factory *f = netsnmp_container_get_factory(type);
    if (f)
        return f->produce_noalloc(mem);

    return FACTORY_NOTFOUND;
}

/*------------------------------------------------------------------
 */
netsnmp_container *
netsnmp_container_find(const char *type)
{
    netsnmp_factory *f = netsnmp_container_find_factory(type);
    if (f)
        return f->produce();

    return NULL;
}

int
netsnmp_container_find_noalloc(const char *type, netsnmp_container *mem)
{
    netsnmp_factory *f = netsnmp_container_find_factory(type);
    if (f)
        return f->produce_noalloc(mem);

    return FACTORY_NOTFOUND;
}

/*------------------------------------------------------------------
 */
void
netsnmp_container_add_index(netsnmp_container *primary,
                            netsnmp_container *new_index)
{
    while(primary->next)
        primary = primary->next;

    primary->next = new_index;
}

#ifdef DONT_INLINE_CONTAINER_MACROS /* default is to inline */

/*------------------------------------------------------------------
 * These functions should EXACTLY match the inline version in
 * container.h. If you chance one, change them both.
 */
int CONTAINER_INSERT(netsnmp_container *x, const void *k)
{
    int rc;

    rc = x->insert(x,k);
    if (NULL != x->next) {
        netsnmp_container *tmp = x->next;
        int                rc2;
        while(tmp) {
            rc2 = tmp->insert(tmp,k);
            if (rc2)
                snmp_log(LOG_ERR,"error on subcontainer insert (%d)\n", rc2);
            tmp = tmp->next;
        }
    }
    return rc;
}

/*------------------------------------------------------------------
 * These functions should EXACTLY match the inline version in
 * container.h. If you chance one, change them both.
 */
int CONTAINER_REMOVE(netsnmp_container *x, const void *k)
{
    if (NULL != x->next) {
        netsnmp_container *tmp = x->next;
        int                rc;
        while(tmp->next)
            tmp = tmp->next;
        while(tmp) {
            rc = tmp->remove(tmp,k);
            if (rc)
                snmp_log(LOG_ERR,"error on subcontainer remove (%d)\n", rc);
            tmp = tmp->prev;
        }
    }
    return x->remove(x,k);
}

/*------------------------------------------------------------------
 * These functions should EXACTLY match the inline version in
 * container.h. If you chance one, change them both.
 */
int CONTAINER_FREE(netsnmp_container *x)
{
    int                rc;

    if (NULL != x->next) {
        netsnmp_container *tmp = x->next;
        while(tmp->next)
            tmp = tmp->next;
        while(tmp) {
            tmp = tmp->prev;
            rc = tmp->next->cfree(tmp->next);
            if (rc)
                snmp_log(LOG_ERR,"error on subcontainer free (%d)\n", rc);
        }
    }
    rc = x->cfree(x);
    if (rc == 0) {
	if (containers == x) {
	    containers = NULL;
	}
    }

    return rc;
}
#endif


/*------------------------------------------------------------------
 */
void
netsnmp_init_container(netsnmp_container         *c,
                       netsnmp_container_rc      *init,
                       netsnmp_container_rc      *cfree,
                       netsnmp_container_size    *size,
                       netsnmp_container_compare *cmp,
                       netsnmp_container_op      *ins,
                       netsnmp_container_op      *rem,
                       netsnmp_container_rtn     *fnd)
{
    if (c == NULL)
        return;

    c->init = init;
    c->cfree = cfree;
    c->get_size = size;
    c->compare = cmp;
    c->insert = ins;
    c->remove = rem;
    c->find = fnd;
}

/*------------------------------------------------------------------
 *
 * simple comparison routines
 *
 */
int
netsnmp_compare_netsnmp_index(const void *lhs, const void *rhs)
{
    int rc;
#ifndef NDEBUG
    DEBUGIF("compare:index") {
        DEBUGMSGT(("compare:index", "compare "));
        DEBUGMSGOID(("compare:index", ((const netsnmp_index *) lhs)->oids,
                     ((const netsnmp_index *) lhs)->len));
        DEBUGMSG(("compare:index", " to "));
        DEBUGMSGOID(("compare:index", ((const netsnmp_index *) rhs)->oids,
                     ((const netsnmp_index *) rhs)->len));
        DEBUGMSG(("compare:index", "\n"));
    }
#endif
    rc = snmp_oid_compare(((const netsnmp_index *) lhs)->oids,
                          ((const netsnmp_index *) lhs)->len,
                          ((const netsnmp_index *) rhs)->oids,
                          ((const netsnmp_index *) rhs)->len);
    return rc;
}

int
netsnmp_ncompare_netsnmp_index(const void *lhs, const void *rhs)
{
    int rc;
#ifndef NDEBUG
    DEBUGIF("compare:index") {
        DEBUGMSGT(("compare:index", "compare "));
        DEBUGMSGOID(("compare:index", ((const netsnmp_index *) lhs)->oids,
                     ((const netsnmp_index *) lhs)->len));
        DEBUGMSG(("compare:index", " to "));
        DEBUGMSGOID(("compare:index", ((const netsnmp_index *) rhs)->oids,
                     ((const netsnmp_index *) rhs)->len));
        DEBUGMSG(("compare:index", "\n"));
    }
#endif
    rc = snmp_oid_ncompare(((const netsnmp_index *) lhs)->oids,
                           ((const netsnmp_index *) lhs)->len,
                           ((const netsnmp_index *) rhs)->oids,
                           ((const netsnmp_index *) rhs)->len,
                           ((const netsnmp_index *) rhs)->len);
    return rc;
}

int
netsnmp_compare_cstring(const void * lhs, const void * rhs)
{
    return strcmp(((const container_type*)lhs)->name,
                  ((const container_type*)rhs)->name);
}

int
netsnmp_ncompare_cstring(const void * lhs, const void * rhs)
{
    return strncmp(((const container_type*)lhs)->name,
                   ((const container_type*)rhs)->name,
                   strlen(((const container_type*)rhs)->name));
}

int
netsnmp_compare_mem(const char * lhs, size_t lhs_len,
                    const char * rhs, size_t rhs_len)
{
    int rc, min = SNMP_MIN(lhs_len, rhs_len);

    rc = memcmp(lhs, rhs, min);
    if((rc==0) && (lhs_len != rhs_len)) {
        if(lhs_len < rhs_len)
            rc = -1;
        else
            rc = 1;
    }

    return rc;
}

static int
_ba_remove_with_free(netsnmp_container *container, const void *data)
{
    container_type *ct, *tmp;
    int rc;

    ct = SNMP_MALLOC_TYPEDEF(container_type);
    if (NULL == ct)
        return -1;

    tmp = ct;
    rc = netsnmp_binary_array_remove(container, data, (void*)ct);
    
    if (ct != NULL)
	SNMP_FREE(ct);

    if (tmp != NULL)
	SNMP_FREE(tmp);

    return rc;
}


void 
_ba_free_container_type(void *data, void *context)
{
    if (data == NULL)
	return;
    
    if (((container_type *)data)->name != NULL) {
	free(((container_type *)data)->name);
    }
    SNMP_FREE(data);
}


static int
_ba_release_with_free(netsnmp_container *container)
{
    container->for_each(container, _ba_free_container_type, NULL);
    netsnmp_binary_array_release(container);

    return 0;
}


