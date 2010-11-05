/*
 *Copyright(c)2004,Cisco URP imburses and Network Information Center in Beijing University of Posts and Telecommunications researches.
 *
 *All right reserved
 *
 *File Name: expExpressionTable.c
 *File Description: expExpressionTable MIB operation.
 *
 *Current Version:1.0
 *Author:JianShun Tong
 *Date:2004.8.20
 */

/*
 * This file was generated by mib2c and is intended for use as
 * a mib module for the ucd-snmp snmpd agent. 
 */


/*
 * This should always be included first before anything else 
 */
#include <net-snmp/net-snmp-config.h>
#if HAVE_STDLIB_H
#include <stdlib.h>
#endif
#if HAVE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif
#ifdef HAVE_LIMITS_H
#include <limits.h>
#endif


/*
 * minimal include directives 
 */
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "header_complex.h"
#include "expErrorTable.h"
#include "expExpressionTable.h"
#include "expObjectTable.h"
#include "expValueTable.h"


/*
 * expExpressionTable_variables_oid:
 *   this is the top level oid that we want to register under.  This
 *   is essentially a prefix, with the suffix appearing in the
 *   variable below.
 */

oid             expExpressionTable_variables_oid[] =
    { 1, 3, 6, 1, 2, 1, 90, 1, 2, 1 };

/*
 * variable2 expExpressionTable_variables:
 */

struct variable2 expExpressionTable_variables[] = {
    /*
     * magic number        , variable type , ro/rw , callback fn  , L, oidsuffix 
     */
#define	EXPEXPRESSION  3
    {EXPEXPRESSION,          ASN_OCTET_STR, NETSNMP_OLDAPI_RWRITE,
     var_expExpressionTable, 2, {1, 3}},
#define	EXPEXPRESSIONVALUETYPE 4
    {EXPEXPRESSIONVALUETYPE, ASN_INTEGER,   NETSNMP_OLDAPI_RWRITE,
     var_expExpressionTable, 2, {1, 4}},
#define	EXPEXPRESSIONCOMMENT 5
    {EXPEXPRESSIONCOMMENT,   ASN_OCTET_STR, NETSNMP_OLDAPI_RWRITE,
     var_expExpressionTable, 2, {1, 5}},
#define	EXPEXPRESSIONDELTALNTERVAL 6
    {EXPEXPRESSIONDELTALNTERVAL, ASN_INTEGER, NETSNMP_OLDAPI_RWRITE,
     var_expExpressionTable, 2, {1, 6}},
#define	EXPEXPRESSIONPREFIX 7
    {EXPEXPRESSIONPREFIX,    ASN_OBJECT_ID, NETSNMP_OLDAPI_RONLY,
     var_expExpressionTable, 2, {1, 7}},
#define	EXPEXPRESSIONERRORS 8
    {EXPEXPRESSIONERRORS,    ASN_UNSIGNED,  NETSNMP_OLDAPI_RONLY,
     var_expExpressionTable, 2, {1, 8}},
#define	EXPEXPRESSIONENTRYSTATUS  9
    {EXPEXPRESSIONENTRYSTATUS, ASN_INTEGER, NETSNMP_OLDAPI_RWRITE,
     var_expExpressionTable, 2, {1, 9}}
};

/*
 * global storage of our data, saved in and configured by header_complex() 
 */

struct header_complex_index *expExpressionTableStorage = NULL;
extern struct header_complex_index *expObjectTableStorage;
extern struct header_complex_index *expValueTableStorage;

oid             mmTimeInstance[] = { 1, 3, 6, 1, 2, 1, 1, 3, 0 };

/*
 * init_expExpressionTable():
 *   Initialization routine.  This is called when the agent starts up.
 *   At a minimum, registration of your variables should take place here.
 */
void
init_expExpressionTable(void)
{


    /*
     * register ourselves with the agent to handle our mib tree 
     */
    REGISTER_MIB("expExpressionTable", expExpressionTable_variables,
                 variable2, expExpressionTable_variables_oid);

    /*
     * register our config handler(s) to deal with registrations 
     */
    snmpd_register_config_handler("expExpressionTable",
                                  parse_expExpressionTable, NULL, NULL);


    snmp_register_callback(SNMP_CALLBACK_LIBRARY, SNMP_CALLBACK_STORE_DATA,
                           store_expExpressionTable, NULL);


    DEBUGMSGTL(("expExpressionTable", "done.\n"));
}

struct expExpressionTable_data *
create_expExpressionTable_data(void)
{
    struct expExpressionTable_data *StorageNew;
    StorageNew = SNMP_MALLOC_STRUCT(expExpressionTable_data);
    /*
     * fill in default row values here into StorageNew 
     */
    /*
     * fill in values for all tables (even if not
     * appropriate), since its easier to do here than anywhere
     * else 
     */

    StorageNew->expExpression = strdup("");
    StorageNew->expExpressionValueType = EXPEXPRESSION_COUNTER32;
    StorageNew->expExpressionComment = strdup("");
    StorageNew->expExpressionDeltaInterval = 0;
    StorageNew->expExpressionPrefix = calloc(1, sizeof(oid) * 2);       /* 0.0 */
    StorageNew->expExpressionPrefixLen = 2;
    StorageNew->hc_ObjectTableStorage = NULL;
    StorageNew->hc_ValueTableStorage = NULL;
    StorageNew->storageType = ST_NONVOLATILE;
    return StorageNew;
}

int
expExpressionTable_add(struct expExpressionTable_data *thedata)
{
    netsnmp_variable_list *vars = NULL;


    DEBUGMSGTL(("expExpressionTable", "adding data...  "));
    /*
     * add the index variables to the varbind list, which is 
     * used by header_complex to index the data 
     */
    snmp_varlist_add_variable(&vars, NULL, 0, ASN_OCTET_STR, (char *) thedata->expExpressionOwner, thedata->expExpressionOwnerLen);     /* expExpressionOwner */
    snmp_varlist_add_variable(&vars, NULL, 0, ASN_OCTET_STR, (char *) thedata->expExpressionName, thedata->expExpressionNameLen);       /* expExpressionName */

    header_complex_add_data(&expExpressionTableStorage, vars, thedata);
    DEBUGMSGTL(("expExpressionTable", "registered an entry\n"));


    DEBUGMSGTL(("expExpressionTable", "done.\n"));
    return SNMPERR_SUCCESS;
}



/*
 * parse_mteTriggerTable():
 *   parses .conf file entries needed to configure the mib.
 */
void
parse_expExpressionTable(const char *token, char *line)
{
    size_t          tmpint;
    oid            *tmpoid = NULL;
    struct expExpressionTable_data *StorageTmp =
        SNMP_MALLOC_STRUCT(expExpressionTable_data);

    DEBUGMSGTL(("expExpressionTable", "parsing config...  "));

    if (StorageTmp == NULL) {
        config_perror("malloc failure");
        return;
    }

    line =
        read_config_read_data(ASN_OCTET_STR, line,
                              &StorageTmp->expExpressionOwner,
                              &StorageTmp->expExpressionOwnerLen);
    if (StorageTmp->expExpressionOwner == NULL) {
        config_perror("invalid specification for expExpressionOwner");
        return;
    }

    line =
        read_config_read_data(ASN_OCTET_STR, line,
                              &StorageTmp->expExpressionName,
                              &StorageTmp->expExpressionNameLen);
    if (StorageTmp->expExpressionName == NULL) {
        config_perror("invalid specification for expExpressionName");
        return;
    }

    line =
        read_config_read_data(ASN_OCTET_STR, line,
                              &StorageTmp->expExpression,
                              &StorageTmp->expExpressionLen);

    line =
        read_config_read_data(ASN_INTEGER, line,
                              &StorageTmp->expExpressionValueType,
                              &tmpint);

    line =
        read_config_read_data(ASN_OCTET_STR, line,
                              &StorageTmp->expExpressionComment,
                              &StorageTmp->expExpressionCommentLen);

    line =
        read_config_read_data(ASN_INTEGER, line,
                              &StorageTmp->expExpressionDeltaInterval,
                              &tmpint);

    line =
        read_config_read_data(ASN_OBJECT_ID, line,
                              &StorageTmp->expExpressionPrefix,
                              &StorageTmp->expExpressionPrefixLen);

    line =
        read_config_read_data(ASN_UNSIGNED, line,
                              &StorageTmp->expExpressionErrors, &tmpint);

    line =
        read_config_read_data(ASN_INTEGER, line,
                              &StorageTmp->expExpressionEntryStatus,
                              &tmpint);

    line =
        read_config_read_data(ASN_INTEGER, line,
                              &StorageTmp->have_copied_auth_info, &tmpint);
    if (StorageTmp->have_copied_auth_info) {
        line =
            read_config_read_data(ASN_INTEGER, line,
                                  &StorageTmp->pdu_version, &tmpint);
        line =
            read_config_read_data(ASN_INTEGER, line,
                                  &StorageTmp->pdu_securityModel, &tmpint);
        line =
            read_config_read_data(ASN_INTEGER, line,
                                  &StorageTmp->pdu_securityLevel, &tmpint);
        line =
            read_config_read_data(ASN_OBJECT_ID, line, &tmpoid, &tmpint);
        if (!netsnmp_tdomain_support
            (tmpoid, tmpint, &StorageTmp->pdu_tDomain,
             &StorageTmp->pdu_tDomainLen)) {
            config_perror
                ("unsupported transport domain for mteTriggerEntry");
            return;
        }
        if (tmpoid != NULL) {
            free(tmpoid);
        }

        /*
         * can be NULL?  Yes.  
         */
        line = read_config_read_data(ASN_OCTET_STR, line,
                                     &(StorageTmp->pdu_transport),
                                     &StorageTmp->pdu_transportLen);

        line =
            read_config_read_data(ASN_OCTET_STR, line,
                                  &StorageTmp->pdu_community,
                                  &StorageTmp->pdu_community_len);
        if (StorageTmp->pdu_community == NULL) {
            config_perror("invalid specification for pdu_community");
            return;
        }
        line =
            read_config_read_data(ASN_OCTET_STR, line,
                                  &StorageTmp->pdu_securityName,
                                  &StorageTmp->pdu_securityNameLen);
        if (StorageTmp->pdu_securityName == NULL) {
            config_perror("invalid specification for pdu_securityName");
            return;
        }
    }
    StorageTmp->storageType = ST_NONVOLATILE;
    expExpressionTable_add(StorageTmp);


    DEBUGMSGTL(("expExpressionTable", "done.\n"));
}


/*
 * store_expExpressionTable():
 *   stores .conf file entries needed to configure the mib.
 */
int
store_expExpressionTable(int majorID, int minorID, void *serverarg,
                         void *clientarg)
{
    char            line[SNMP_MAXBUF];
    char           *cptr;
    size_t          tmpint;
    struct expExpressionTable_data *StorageTmp;
    struct header_complex_index *hcindex;

    DEBUGMSGTL(("expExpressionTable", "storing data...  "));

    for (hcindex = expExpressionTableStorage; hcindex != NULL;
         hcindex = hcindex->next) {
        StorageTmp = (struct expExpressionTable_data *) hcindex->data;


        if (StorageTmp->storageType == ST_NONVOLATILE) {

            memset(line, 0, sizeof(line));
            strcat(line, "expExpressionTable ");
            cptr = line + strlen(line);
            /*
             * expExpressionTable
             */


            cptr =
                read_config_store_data(ASN_OCTET_STR, cptr,
                                       &StorageTmp->expExpressionOwner,
                                       &StorageTmp->expExpressionOwnerLen);
            cptr =
                read_config_store_data(ASN_OCTET_STR, cptr,
                                       &StorageTmp->expExpressionName,
                                       &StorageTmp->expExpressionNameLen);
            cptr =
                read_config_store_data(ASN_OCTET_STR, cptr,
                                       &StorageTmp->expExpression,
                                       &StorageTmp->expExpressionLen);
            cptr =
                read_config_store_data(ASN_INTEGER, cptr,
                                       &StorageTmp->expExpressionValueType,
                                       &tmpint);
            cptr =
                read_config_store_data(ASN_OCTET_STR, cptr,
                                       &StorageTmp->expExpressionComment,
                                       &StorageTmp->
                                       expExpressionCommentLen);
            cptr =
                read_config_store_data(ASN_INTEGER, cptr,
                                       &StorageTmp->
                                       expExpressionDeltaInterval,
                                       &tmpint);
            cptr =
                read_config_store_data(ASN_OBJECT_ID, cptr,
                                       &StorageTmp->expExpressionPrefix,
                                       &StorageTmp->
                                       expExpressionPrefixLen);
            cptr =
                read_config_store_data(ASN_UNSIGNED, cptr,
                                       &StorageTmp->expExpressionErrors,
                                       &tmpint);
            cptr =
                read_config_store_data(ASN_INTEGER, cptr,
                                       &StorageTmp->
                                       expExpressionEntryStatus, &tmpint);
            cptr =
                read_config_store_data(ASN_INTEGER, cptr,
                                       &StorageTmp->have_copied_auth_info,
                                       &tmpint);
            if (StorageTmp->have_copied_auth_info) {
                cptr =
                    read_config_store_data(ASN_INTEGER, cptr,
                                           &StorageTmp->pdu_version,
                                           &tmpint);
                cptr =
                    read_config_store_data(ASN_INTEGER, cptr,
                                           &StorageTmp->pdu_securityModel,
                                           &tmpint);
                cptr =
                    read_config_store_data(ASN_INTEGER, cptr,
                                           &StorageTmp->pdu_securityLevel,
                                           &tmpint);
                cptr =
                    read_config_store_data(ASN_OBJECT_ID, cptr,
                                           (void *) (&StorageTmp->
                                                     pdu_tDomain),
                                           &StorageTmp->pdu_tDomainLen);
                cptr =
                    read_config_store_data(ASN_OCTET_STR, cptr,
                                           &StorageTmp->pdu_transport,
                                           &StorageTmp->pdu_transportLen);
                cptr =
                    read_config_store_data(ASN_OCTET_STR, cptr,
                                           &StorageTmp->pdu_community,
                                           &StorageTmp->pdu_community_len);
                cptr =
                    read_config_store_data(ASN_OCTET_STR, cptr,
                                           &StorageTmp->pdu_securityName,
                                           &StorageTmp->
                                           pdu_securityNameLen);
            }


            snmpd_store_config(line);
        }
    }
    DEBUGMSGTL(("expExpressionTable", "storage done.\n"));
    return SNMPERR_SUCCESS;
}




/*
 * var_expExpressionTable():
 *   Handle this table separately from the scalar value case.
 *   The workings of this are basically the same as for var_expExpressionTable above.
 */
unsigned char  *
var_expExpressionTable(struct variable *vp,
                       oid * name,
                       size_t *length,
                       int exact,
                       size_t *var_len, WriteMethod ** write_method)
{
    struct expExpressionTable_data *StorageTmp = NULL;

    DEBUGMSGTL(("expExpressionTable",
                "var_expExpressionTable: Entering...  \n"));

    /*
     * this assumes you have registered all your data properly
     */
    if ((StorageTmp =
         header_complex(expExpressionTableStorage, vp, name, length, exact,
                        var_len, write_method)) == NULL) {
        if (vp->magic == EXPEXPRESSIONENTRYSTATUS)
            *write_method = write_expExpressionEntryStatus;
        return NULL;
    }


    switch (vp->magic) {


    case EXPEXPRESSION:
        *write_method = write_expExpression;
        *var_len = StorageTmp->expExpressionLen;
        return (u_char *) StorageTmp->expExpression;

    case EXPEXPRESSIONVALUETYPE:
        *write_method = write_expExpressionValueType;
        *var_len = sizeof(StorageTmp->expExpressionValueType);
        return (u_char *) & StorageTmp->expExpressionValueType;

    case EXPEXPRESSIONCOMMENT:
        *write_method = write_expExpressionComment;
        *var_len = StorageTmp->expExpressionCommentLen;
        return (u_char *) StorageTmp->expExpressionComment;

    case EXPEXPRESSIONDELTALNTERVAL:
        *write_method = write_expExpressionDeltaInterval;
        *var_len = sizeof(StorageTmp->expExpressionDeltaInterval);
        return (u_char *) & StorageTmp->expExpressionDeltaInterval;

    case EXPEXPRESSIONPREFIX:
        *var_len = StorageTmp->expExpressionPrefixLen * sizeof(oid);
        return (u_char *) StorageTmp->expExpressionPrefix;

    case EXPEXPRESSIONERRORS:
        *var_len = sizeof(StorageTmp->expExpressionErrors);
        return (u_char *) & StorageTmp->expExpressionErrors;

    case EXPEXPRESSIONENTRYSTATUS:
        *write_method = write_expExpressionEntryStatus;
        *var_len = sizeof(StorageTmp->expExpressionEntryStatus);
        return (u_char *) & StorageTmp->expExpressionEntryStatus;

    default:
        ERROR_MSG("");

    }
    return NULL;
}



int
write_expExpression(int action,
                    u_char * var_val,
                    u_char var_val_type,
                    size_t var_val_len,
                    u_char * statP, oid * name, size_t name_len)
{
    static char    *tmpvar;
    struct expExpressionTable_data *StorageTmp = NULL;
    static size_t   tmplen;
    size_t          newlen =
        name_len -
        (sizeof(expExpressionTable_variables_oid) / sizeof(oid) + 3 - 1);


    DEBUGMSGTL(("expExpressionTable",
                "write_expExpression entering action=%d...  \n", action));
    if ((StorageTmp =
         header_complex(expExpressionTableStorage, NULL,
                        &name[sizeof(expExpressionTable_variables_oid) /
                              sizeof(oid) + 3 - 1], &newlen, 1, NULL,
                        NULL)) == NULL)
        return SNMP_ERR_NOSUCHNAME;     /* remove if you support creation here */


    switch (action) {
    case RESERVE1:
        if (var_val_type != ASN_OCTET_STR) {
            snmp_log(LOG_ERR,
                     "write to expExpression not ASN_OCTET_STR\n");
            return SNMP_ERR_WRONGTYPE;
        }
        if (StorageTmp->storageType != ST_NONVOLATILE)
            return SNMP_ERR_NOTWRITABLE;

        break;


    case RESERVE2:
        /*
         * memory reseveration, final preparation... 
         */
        break;


    case FREE:
        /*
         * Release any resources that have been allocated 
         */
        break;


    case ACTION:
        /*
         * The variable has been stored in string for
         * you to use, and you have just been asked to do something with
         * it.  Note that anything done here must be reversable in the UNDO case 
         */
        tmpvar = StorageTmp->expExpression;
        tmplen = StorageTmp->expExpressionLen;
        memdup((u_char **) & StorageTmp->expExpression, var_val,
               var_val_len);
        StorageTmp->expExpressionLen = var_val_len;
        break;


    case UNDO:
        /*
         * Back out any changes made in the ACTION case 
         */
        SNMP_FREE(StorageTmp->expExpression);
        StorageTmp->expExpression = tmpvar;
        StorageTmp->expExpressionLen = tmplen;
        break;


    case COMMIT:
        /*
         * Things are working well, so it's now safe to make the change
         * permanently.  Make sure that anything done here can't fail! 
         */
        SNMP_FREE(tmpvar);
        snmp_store_needed(NULL);
        break;
    }
    return SNMP_ERR_NOERROR;

}



int
write_expExpressionValueType(int action,
                             u_char * var_val,
                             u_char var_val_type,
                             size_t var_val_len,
                             u_char * statP, oid * name, size_t name_len)
{
    static int      tmpvar;
    struct expExpressionTable_data *StorageTmp = NULL;
    size_t          newlen =
        name_len -
        (sizeof(expExpressionTable_variables_oid) / sizeof(oid) + 3 - 1);


    DEBUGMSGTL(("expExpressionTable",
                "write_expExpressionValueType entering action=%d...  \n",
                action));
    if ((StorageTmp =
         header_complex(expExpressionTableStorage, NULL,
                        &name[sizeof(expExpressionTable_variables_oid) /
                              sizeof(oid) + 3 - 1], &newlen, 1, NULL,
                        NULL)) == NULL)
        return SNMP_ERR_NOSUCHNAME;     /* remove if you support creation here */


    switch (action) {
    case RESERVE1:
        if (var_val_type != ASN_INTEGER) {
            snmp_log(LOG_ERR,
                     "write to expExpressionValueType not ASN_INTEGER\n");
            return SNMP_ERR_WRONGTYPE;
        }
        if (StorageTmp->storageType != ST_NONVOLATILE)
            return SNMP_ERR_NOTWRITABLE;

        break;


    case RESERVE2:
        /*
         * memory reseveration, final preparation... 
         */
        break;


    case FREE:
        /*
         * Release any resources that have been allocated 
         */
        break;


    case ACTION:
        /*
         * The variable has been stored in string for
         * you to use, and you have just been asked to do something with
         * it.  Note that anything done here must be reversable in the UNDO case 
         */
        tmpvar = StorageTmp->expExpressionValueType;
        StorageTmp->expExpressionValueType = *((long *) var_val);
        break;


    case UNDO:
        /*
         * Back out any changes made in the ACTION case 
         */
        StorageTmp->expExpressionValueType = tmpvar;
        break;


    case COMMIT:
        /*
         * Things are working well, so it's now safe to make the change
         * permanently.  Make sure that anything done here can't fail! 
         */
        snmp_store_needed(NULL);
        break;
    }
    return SNMP_ERR_NOERROR;

}


int
write_expExpressionComment(int action,
                           u_char * var_val,
                           u_char var_val_type,
                           size_t var_val_len,
                           u_char * statP, oid * name, size_t name_len)
{
    static char    *tmpvar;
    struct expExpressionTable_data *StorageTmp = NULL;
    static size_t   tmplen;
    size_t          newlen =
        name_len -
        (sizeof(expExpressionTable_variables_oid) / sizeof(oid) + 3 - 1);


    DEBUGMSGTL(("expExpressionTable",
                "write_expExpression entering action=%d...  \n", action));
    if ((StorageTmp =
         header_complex(expExpressionTableStorage, NULL,
                        &name[sizeof(expExpressionTable_variables_oid) /
                              sizeof(oid) + 3 - 1], &newlen, 1, NULL,
                        NULL)) == NULL)
        return SNMP_ERR_NOSUCHNAME;     /* remove if you support creation here */


    switch (action) {
    case RESERVE1:
        if (var_val_type != ASN_OCTET_STR) {
            snmp_log(LOG_ERR,
                     "write to expExpressionComment not ASN_OCTET_STR\n");
            return SNMP_ERR_WRONGTYPE;
        }
        if (StorageTmp->storageType != ST_NONVOLATILE)
            return SNMP_ERR_NOTWRITABLE;

        break;


    case RESERVE2:
        /*
         * memory reseveration, final preparation... 
         */
        break;


    case FREE:
        /*
         * Release any resources that have been allocated 
         */
        break;


    case ACTION:
        /*
         * The variable has been stored in string for
         * you to use, and you have just been asked to do something with
         * it.  Note that anything done here must be reversable in the UNDO case 
         */
        tmpvar = StorageTmp->expExpressionComment;
        tmplen = StorageTmp->expExpressionCommentLen;
        memdup((u_char **) & StorageTmp->expExpressionComment, var_val,
               var_val_len);
        StorageTmp->expExpressionCommentLen = var_val_len;
        break;


    case UNDO:
        /*
         * Back out any changes made in the ACTION case 
         */
        SNMP_FREE(StorageTmp->expExpressionComment);
        StorageTmp->expExpressionComment = tmpvar;
        StorageTmp->expExpressionCommentLen = tmplen;
        break;


    case COMMIT:
        /*
         * Things are working well, so it's now safe to make the change
         * permanently.  Make sure that anything done here can't fail! 
         */
        SNMP_FREE(tmpvar);
        snmp_store_needed(NULL);
        break;
    }
    return SNMP_ERR_NOERROR;

}


int
write_expExpressionDeltaInterval(int action,
                                 u_char * var_val,
                                 u_char var_val_type,
                                 size_t var_val_len,
                                 u_char * statP, oid * name,
                                 size_t name_len)
{
    static int      tmpvar;
    struct expExpressionTable_data *StorageTmp = NULL;
    size_t          newlen =
        name_len -
        (sizeof(expExpressionTable_variables_oid) / sizeof(oid) + 3 - 1);


    DEBUGMSGTL(("expExpressionTable",
                "write_expExpressionValueType entering action=%d...  \n",
                action));
    if ((StorageTmp =
         header_complex(expExpressionTableStorage, NULL,
                        &name[sizeof(expExpressionTable_variables_oid) /
                              sizeof(oid) + 3 - 1], &newlen, 1, NULL,
                        NULL)) == NULL)
        return SNMP_ERR_NOSUCHNAME;     /* remove if you support creation here */


    switch (action) {
    case RESERVE1:
        if (var_val_type != ASN_INTEGER) {
            snmp_log(LOG_ERR,
                     "write to expExpressionDeltalnterval not ASN_INTEGER\n");
            return SNMP_ERR_WRONGTYPE;
        }
        if (StorageTmp->storageType != ST_NONVOLATILE)
            return SNMP_ERR_NOTWRITABLE;

        break;


    case RESERVE2:
        /*
         * memory reseveration, final preparation... 
         */
        break;


    case FREE:
        /*
         * Release any resources that have been allocated 
         */
        break;


    case ACTION:
        /*
         * The variable has been stored in string for
         * you to use, and you have just been asked to do something with
         * it.  Note that anything done here must be reversable in the UNDO case 
         */
        tmpvar = StorageTmp->expExpressionDeltaInterval;
        StorageTmp->expExpressionDeltaInterval = *((long *) var_val);
        break;


    case UNDO:
        /*
         * Back out any changes made in the ACTION case 
         */
        StorageTmp->expExpressionDeltaInterval = tmpvar;
        break;


    case COMMIT:
        /*
         * Things are working well, so it's now safe to make the change
         * permanently.  Make sure that anything done here can't fail! 
         */
        snmp_store_needed(NULL);
        break;
    }
    return SNMP_ERR_NOERROR;

}


int
write_expExpressionEntryStatus(int action,
                               u_char * var_val,
                               u_char var_val_type,
                               size_t var_val_len,
                               u_char * statP, oid * name, size_t name_len)
{
    struct expExpressionTable_data *StorageTmp = NULL;
    static struct expExpressionTable_data *StorageNew, *StorageDel;
    size_t          newlen =
        name_len -
        (sizeof(expExpressionTable_variables_oid) / sizeof(oid) + 3 - 1);
    static int      old_value;
    int             set_value;
    static netsnmp_variable_list *vars, *vp;
    struct header_complex_index *hciptr;

    StorageTmp =
        header_complex(expExpressionTableStorage, NULL,
                       &name[sizeof(expExpressionTable_variables_oid) /
                             sizeof(oid) + 3 - 1], &newlen, 1, NULL, NULL);




    if (var_val_type != ASN_INTEGER || var_val == NULL) {
        snmp_log(LOG_ERR,
                 "write to expExpressionEntryStatus not ASN_INTEGER\n");
        return SNMP_ERR_WRONGTYPE;
    }
    set_value = *((long *) var_val);


    /*
     * check legal range, and notReady is reserved for us, not a user 
     */
    if (set_value < 1 || set_value > 6 || set_value == RS_NOTREADY)
        return SNMP_ERR_INCONSISTENTVALUE;


    switch (action) {
    case RESERVE1:
        /*
         * stage one: test validity 
         */
        if (StorageTmp == NULL) {
            /*
             * create the row now? 
             */


            /*
             * ditch illegal values now 
             */
            if (set_value == RS_ACTIVE || set_value == RS_NOTINSERVICE)
                return SNMP_ERR_INCONSISTENTVALUE;


            /*
             * destroying a non-existent row is actually legal 
             */
            if (set_value == RS_DESTROY) {
                return SNMP_ERR_NOERROR;
            }


            /*
             * illegal creation values 
             */
            if (set_value == RS_ACTIVE || set_value == RS_NOTINSERVICE) {
                return SNMP_ERR_INCONSISTENTVALUE;
            }
        } else {
            /*
             * row exists.  Check for a valid state change 
             */
            if (set_value == RS_CREATEANDGO
                || set_value == RS_CREATEANDWAIT) {
                /*
                 * can't create a row that exists 
                 */
                return SNMP_ERR_INCONSISTENTVALUE;
            }

            if (StorageTmp->expExpressionEntryStatus == RS_ACTIVE &&
                set_value != RS_DESTROY) {
                /*
                 * "Once made active an entry may not be modified except to 
                 * delete it."  XXX: doesn't this in fact apply to ALL
                 * columns of the table and not just this one?  
                 */
                return SNMP_ERR_INCONSISTENTVALUE;
            }
            if (StorageTmp->storageType != ST_NONVOLATILE)
                return SNMP_ERR_NOTWRITABLE;
        }
        break;




    case RESERVE2:
        /*
         * memory reseveration, final preparation... 
         */
        if (StorageTmp == NULL) {
            /*
             * creation 
             */
            vars = NULL;


            snmp_varlist_add_variable(&vars, NULL, 0, ASN_OCTET_STR, NULL, 0);  /* expExpressionOwner */
            snmp_varlist_add_variable(&vars, NULL, 0, ASN_OCTET_STR, NULL, 0);  /* expExpressionName */



            if (header_complex_parse_oid
                (&
                 (name
                  [sizeof(expExpressionTable_variables_oid) / sizeof(oid) +
                   2]), newlen, vars) != SNMPERR_SUCCESS) {
                /*
                 * XXX: free, zero vars 
                 */
                return SNMP_ERR_INCONSISTENTNAME;
            }
            vp = vars;


            StorageNew = create_expExpressionTable_data();

            StorageNew->expExpressionOwner = malloc(vp->val_len + 1);
            memcpy(StorageNew->expExpressionOwner, vp->val.string,
                   vp->val_len);
            StorageNew->expExpressionOwner[vp->val_len] = '\0';
            StorageNew->expExpressionOwnerLen = vp->val_len;

            vp = vp->next_variable;
            StorageNew->expExpressionName = malloc(vp->val_len + 1);
            memcpy(StorageNew->expExpressionName, vp->val.string,
                   vp->val_len);
            StorageNew->expExpressionName[vp->val_len] = '\0';
            StorageNew->expExpressionNameLen = vp->val_len;

            vp = vp->next_variable;

            StorageNew->expExpressionEntryStatus = set_value;

        }


        break;




    case FREE:
        /*
         * XXX: free, zero vars 
         */
        /*
         * Release any resources that have been allocated 
         */
        break;




    case ACTION:
        /*
         * The variable has been stored in set_value for you to
         * use, and you have just been asked to do something with
         * it.  Note that anything done here must be reversable in
         * the UNDO case 
         */


        if (StorageTmp == NULL) {
            /*
             * row creation, so add it 
             */
            if (StorageNew != NULL)
                expExpressionTable_add(StorageNew);
            /*
             * XXX: ack, and if it is NULL? 
             */
        } else if (set_value != RS_DESTROY) {
            /*
             * set the flag? 
             */
            old_value = StorageTmp->expExpressionEntryStatus;
            StorageTmp->expExpressionEntryStatus = *((long *) var_val);
        } else {
            /*
             * destroy...  extract it for now 
             */
            hciptr =
                header_complex_find_entry(expExpressionTableStorage,
                                          StorageTmp);
            StorageDel =
                header_complex_extract_entry(&expExpressionTableStorage,
                                             hciptr);
        }
        break;




    case UNDO:
        /*
         * Back out any changes made in the ACTION case 
         */
        if (StorageTmp == NULL) {
            /*
             * row creation, so remove it again 
             */
            hciptr =
                header_complex_find_entry(expExpressionTableStorage,
                                          StorageTmp);
            StorageDel =
                header_complex_extract_entry(&expExpressionTableStorage,
                                             hciptr);
            /*
             * XXX: free it 
             */
        } else if (StorageDel != NULL) {
            /*
             * row deletion, so add it again 
             */
            expExpressionTable_add(StorageDel);
        } else {
            StorageTmp->expExpressionEntryStatus = old_value;
        }
        break;




    case COMMIT:
        /*
         * Things are working well, so it's now safe to make the change
         * permanently.  Make sure that anything done here can't fail! 
         */
        if (StorageDel != NULL) {
            StorageDel = 0;
            /*
             * XXX: free it, its dead 
             */
        } else {
            if (StorageTmp
                && StorageTmp->expExpressionEntryStatus ==
                RS_CREATEANDGO) {
                StorageTmp->expExpressionEntryStatus = RS_ACTIVE;
            } else if (StorageTmp &&
                       StorageTmp->expExpressionEntryStatus ==
                       RS_CREATEANDWAIT) {
                StorageTmp->expExpressionEntryStatus = RS_NOTINSERVICE;
            }
        }
        if (StorageTmp &&
            StorageTmp->expExpressionEntryStatus == RS_ACTIVE &&
            !StorageTmp->have_copied_auth_info) {

            netsnmp_agent_session *asp =
                netsnmp_get_current_agent_session();
            netsnmp_pdu    *pdu = NULL;

            if (!asp) {
                snmp_log(LOG_ERR,
                         "snmpTriggerTable: can't get master session for authentication params\n");
            } else {
                pdu = asp->orig_pdu;
                if (!pdu) {
                    snmp_log(LOG_ERR,
                             "snmpTriggerTable: can't get master pdu for authentication params\n");
                }
            }

            if (pdu) {
                DEBUGMSGTL(("expExpressionTest",
                            "copying PDU auth info\n"));
                StorageTmp->pdu_version = pdu->version;
                StorageTmp->pdu_securityModel = pdu->securityModel;
                StorageTmp->pdu_securityLevel = pdu->securityLevel;
                StorageTmp->pdu_tDomain = pdu->tDomain;
                StorageTmp->pdu_tDomainLen = pdu->tDomainLen;
                if (pdu->transport_data != NULL) {
                    StorageTmp->pdu_transport =
                        malloc(pdu->transport_data_length);
                    memcpy(StorageTmp->pdu_transport, pdu->transport_data,
                           pdu->transport_data_length);
                }
                StorageTmp->pdu_transportLen = pdu->transport_data_length;
                if (pdu->community) {
                    StorageTmp->pdu_community =
                        calloc(1, pdu->community_len + 1);
                    memcpy(StorageTmp->pdu_community, pdu->community,
                           pdu->community_len);
                    StorageTmp->pdu_community_len = pdu->community_len;
                } else {
                    StorageTmp->pdu_community = NULL;
                    StorageTmp->pdu_community_len = 0;
                }
                if (pdu->securityName) {
                    StorageTmp->pdu_securityName =
                        calloc(1, pdu->securityNameLen + 1);
                    memcpy(StorageTmp->pdu_securityName, pdu->securityName,
                           pdu->securityNameLen);
                    StorageTmp->pdu_securityNameLen = pdu->securityNameLen;
                } else {
                    StorageTmp->pdu_securityName = NULL;
                    StorageTmp->pdu_securityNameLen = 0;
                }
                StorageTmp->have_copied_auth_info = 1;
            }
        }
        snmp_store_needed(NULL);
        break;
    }
    return SNMP_ERR_NOERROR;
}
