/****************************************************************
 *
 *  IxChariot API SDK              File: ChrAppGroupsTest.c
 *
 *  This module contains code made available by Ixia on an AS IS
 *  basis.  Any one receiving the module is considered to be 
 *  licensed under Ixia copyrights to use the Ixia-provided 
 *  source code in any way he or she deems fit, including copying
 *  it, compiling it, modifying it, and redistributing it, with 
 *  or without modifications. No license under any Ixia patents
 *  or patent applications is to be implied from this copyright
 *  license.
 *
 *  A user of the module should understand that Ixia cannot 
 *  provide technical support for the module and will not be
 *  responsible for any consequences of use of the program.
 *
 *  Any notices, including this one, are not to be removed from
 *  the module without the prior written consent of Ixia.
 *
 *  For more information, contact:
 *
 *  Ixia
 *  26601 W. Agoura Rd. 
 *  Calabasas, CA 91302 USA
 *  Web:   http://www.ixiacom.com
 *  Phone: 818-871-1800
 *  Fax:   818-871-1805
 *
 *  General Information:
 *    e-mail: info@ixiacom.com
 *
 *  Technical Support:
 *    e-mail: support@ixiacom.com
 *
 *  EXAMPLE: Application Groups Test
 *
 *  This program loads an application group from the disk, sets
 *  some attributes, replicates it, runs the test and finally
 *  saves to the disk both the application groups and the test.
 *
 *  All attributes of this test are defined by this program.
 *
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * The header file which defines everything in the IxChariot API:
 * functions, constants, etc.
 */
#include "chrapi.h"

/*
 * Local function to print information about errors.
 */
static void
show_error(
    CHR_HANDLE handle,
    CHR_API_RC code,
    CHR_STRING where);

/*
 * Data for the test:
 * Change these for your local network if desired.
 */
static
CHR_STRING addr1 = "localhost";
static
CHR_STRING addr2 = "localhost";
static
CHR_STRING appGroupLoadFile = "C:/Program Files/Ixia/IxChariot/Application Groups/active_FTP.iag";
static
CHR_STRING appGroupSaveFile = "api_app_group.iag";
static
CHR_STRING testFile = "appgroups.tst";
static
CHR_STRING appGroupDuplicateName = "Duplicated app group";
static
CHR_STRING appGroupComment = "Sample API app group";
static
CHR_COUNT timeout   = 120;  /* 2 minutes in seconds */


/**************************************************************
 *
 * Program main
 *
 * If the return code from any IxChariot API function call
 * is not CHR_OK, the show_error() function is called to
 * display information about what happened then exit.
 *
 **************************************************************/

void main()
{
    /*
     * The object handles we'll need
     */
    CHR_TEST_HANDLE         test            = (CHR_TEST_HANDLE)NULL;
    CHR_APP_GROUP_HANDLE    appGroupLoaded  = (CHR_APP_GROUP_HANDLE)NULL;
    CHR_APP_GROUP_HANDLE    appGroupNew     = (CHR_APP_GROUP_HANDLE)NULL;

    /*
     * Variables and buffers for the attributes and results
     */
    CHR_LENGTH length;
    CHR_COUNT  appGroupCount;
    CHR_COUNT  pairCount;
    CHR_COUNT  addressCount;
    CHR_CHAR   appGroupName[CHR_MAX_APP_GROUP_NAME];
    CHR_CHAR   address[CHR_MAX_ADDR];

    /*
     * Buffer for extended error info for initialization
     */
    CHR_CHAR errorInfo[CHR_MAX_ERROR_INFO];

    /*
     * IxChariot API return code
     */
    CHR_API_RC rc;


    /* Initialize the IxChariot API */
    rc = CHR_api_initialize(
            CHR_DETAIL_LEVEL_ALL,
            errorInfo,
            CHR_MAX_ERROR_INFO,
            &length);

    if (CHR_OK != rc)
    {
        /*
         * Because initialization failed, we can't
         * ask the API for the message for this
         * return code, so we can't call our
         * show_error() function. Instead, we'll
         * print what we do know before exiting.
         */
        printf("Initialization failed: rc = %d\n", rc);
        printf("Extended error info:\n%s\n", errorInfo);
    }

    /* Create a new test */
    if (CHR_OK == rc)
    {
        printf("Create the test object...\n");
        rc = CHR_test_new(&test);

        if (rc != CHR_OK)
        {
            show_error((CHR_HANDLE)NULL, rc, "CHR_test_new");
        }
    }

    /* Import application groups from the disk to the test */
    if (CHR_OK == rc)
    {
        printf("Import the app groups...\n");
        rc = CHR_test_load_app_groups(
                test,
                appGroupLoadFile,
                strlen(appGroupLoadFile));

        if (rc != CHR_OK)
        {
            show_error(test, rc, "CHR_test_load_app_groups");
        }
    }

    if (CHR_OK == rc)
    {
        printf("Get no of app groups...\n");
        rc = CHR_test_get_app_group_count(test, &appGroupCount);

        if (rc != CHR_OK)
        {
            show_error(test, rc, "CHR_test_get_app_group_count");
        }
        else
        {
            printf("App group count: %d\n", appGroupCount);
        }
    }

    /* Get a handle to the first application group */
    if (CHR_OK == rc)
    {
        printf("Get the app group handle...\n");
        rc = CHR_test_get_app_group_by_index(
                test,
                0,
                &appGroupLoaded);

        if (rc != CHR_OK)
        {
            show_error(test, rc, "CHR_test_get_app_group_by_index");
        }
    }

    /* Get info about the application group */
    if (CHR_OK == rc)
    {
        printf("Get app group name...\n");
        rc = CHR_app_group_get_name(
                appGroupLoaded,
                appGroupName,
                sizeof(appGroupName),
                &length);

        if (rc != CHR_OK)
        {
            show_error(appGroupLoaded, rc, "CHR_app_group_get_name");
        }
        else
        {
            printf("App group name: %s\n", appGroupName);
        }
    }

    if (CHR_OK == rc)
    {
        printf("Get no of pairs...\n");
        rc = CHR_app_group_get_pair_count(appGroupLoaded, &pairCount);

        if (rc != CHR_OK)
        {
            show_error(appGroupLoaded, rc, "CHR_app_group_get_pair_count");
        }
        else
        {
            printf("Pair count: %d\n", pairCount);
        }
    }

    if (CHR_OK == rc)
    {
        printf("Get no of unique network IP addresses...\n");
        rc = CHR_app_group_get_address_count(appGroupLoaded, &addressCount);

        if (rc != CHR_OK)
        {
            show_error(appGroupLoaded, rc, "CHR_app_group_get_address_count");
        }
        else
        {
            printf("Network address count: %d\n", addressCount);
        }
    }

    if (CHR_OK == rc)
    {
        CHR_COUNT i;

        for (i = 0; i < addressCount; i++)
        {
            rc = CHR_app_group_get_address(
                    appGroupLoaded,
                    i,
                    address,
                    sizeof(address),
                    &length);

            if (rc != CHR_OK)
            {
                show_error(appGroupLoaded, rc, "CHR_app_group_get_address");
            }
            else
            {
                printf("%d)  %s\n", i + 1, address);
            }
        }
    }

    if (CHR_OK == rc)
    {
        printf("Get no of unique management IP addresses...\n");
        rc = CHR_app_group_get_management_address_count(appGroupLoaded, &addressCount);

        if (rc != CHR_OK)
        {
            show_error(appGroupLoaded, rc, "CHR_app_group_get_management_address_count");
        }
        else
        {
            printf("Management address count: %d\n", addressCount);
        }
    }

    if (CHR_OK == rc)
    {
        CHR_COUNT i;

        for (i = 0; i < addressCount; i++)
        {
            rc = CHR_app_group_get_management_address(
                    appGroupLoaded,
                    i,
                    address,
                    sizeof(address),
                    &length);

            if (rc != CHR_OK)
            {
                show_error(appGroupLoaded, rc, "CHR_app_group_get_management_address");
            }
            else
            {
                printf("%d)  %s\n", i + 1, address);
            }
        }
    }

    /*
     * The application group is owned by a test. In order to change its
     * attributes, we have to remove it from the test or lock it.
     * For this example, we chose to lock it.
     */
    if (CHR_OK == rc)
    {
        printf("Lock the app group...\n");
        rc = CHR_app_group_set_lock(appGroupLoaded, CHR_TRUE);

        if (rc != CHR_OK)
        {
            show_error(appGroupLoaded, rc, "CHR_app_group_set_lock");
        }
    }

    if (CHR_OK == rc)
    {
        printf("Set the app group comment...\n");
        rc = CHR_app_group_set_comment(
                appGroupLoaded,
                appGroupComment,
                strlen(appGroupComment));

        if (rc != CHR_OK)
        {
            show_error(appGroupLoaded, rc, "CHR_app_group_set_comment");
        }
    }

    /*
     * Change the default IP addresses with our own.
     * It's recommended to change them in reverse order.
     */
    if (CHR_OK == rc)
    {
        printf("Change the second network IP address...\n");
        rc = CHR_app_group_set_address(
                appGroupLoaded,
                1,
                addr2,
                strlen(addr2));

        if (rc != CHR_OK)
        {
            show_error(appGroupLoaded, rc, "CHR_app_group_set_address");
        }
    }

    if (CHR_OK == rc)
    {
        printf("Change the first network IP address...\n");
        rc = CHR_app_group_set_address(
                appGroupLoaded,
                0,
                addr1,
                strlen(addr1));

        if (rc != CHR_OK)
        {
            show_error(appGroupLoaded, rc, "CHR_app_group_set_address");
        }
    }

    if (CHR_OK == rc)
    {
        printf("Set the app group filename...\n");
        rc = CHR_app_group_set_filename(
                appGroupLoaded,
                appGroupSaveFile,
                strlen(appGroupSaveFile));

        if (rc != CHR_OK)
        {
            show_error(appGroupLoaded, rc, "CHR_app_group_set_filename");
        }
    }

    /* We finished the settings, so unlock the app group */
    if (CHR_OK == rc)
    {
        printf("Unlock the app group...\n");
        rc = CHR_app_group_set_lock(appGroupLoaded, CHR_FALSE);

        if (rc != CHR_OK)
        {
            show_error(appGroupLoaded, rc, "CHR_app_group_set_lock");
        }
    }

    /* Save the modified app group to the disk */
    if (CHR_OK == rc)
    {
        printf("Save the app group...\n");
        rc = CHR_app_group_save(appGroupLoaded);

        if (rc != CHR_OK)
        {
            show_error(appGroupLoaded, rc, "CHR_app_group_save");
        }
    }

    /*
     * We want to duplicate the application group.
     * In order to do that, we need a new app group object.
     */
    if (CHR_OK == rc)
    {
        printf("Create a new app group object...\n");
        rc = CHR_app_group_new(&appGroupNew);

        if (rc != CHR_OK)
        {
            show_error((CHR_HANDLE)NULL, rc, "CHR_app_group_new");
        }
    }

    /*
     * If we call CHR_app_group_copy right now, we will end up
     * with 2 application groups with the same name in the test.
     */
    if (CHR_OK == rc)
    {
        printf("Remove the app group from the test...\n");
        rc = CHR_test_remove_app_group(test, appGroupLoaded);

        if (rc != CHR_OK)
        {
            show_error(test, rc, "CHR_test_remove_app_group");
        }
    }

    if (CHR_OK == rc)
    {
        printf("Copy app groups...\n");
        rc = CHR_app_group_copy(appGroupNew, appGroupLoaded);

        if (rc != CHR_OK)
        {
            show_error(appGroupLoaded, rc, "CHR_app_group_copy");
        }
    }

    /* Change the name of the new application group */
    if (CHR_OK == rc)
    {
        printf("Set the app group name...\n");
        rc = CHR_app_group_set_name(
                appGroupNew,
                appGroupDuplicateName,
                strlen(appGroupDuplicateName));

        if (rc != CHR_OK)
        {
            show_error(appGroupNew, rc, "CHR_app_group_set_name");
        }
    }

    /* Add both application groups to the test */
    if (CHR_OK == rc)
    {
        printf("Add the app group to the test...\n");
        rc = CHR_test_add_app_group(test, appGroupLoaded);

        if (rc != CHR_OK)
        {
            show_error(test, rc, "CHR_test_add_app_group");
        }
    }

    if (CHR_OK == rc)
    {
        printf("Add the app group to the test...\n");
        rc = CHR_test_add_app_group(test, appGroupNew);

        if (rc != CHR_OK)
        {
            show_error(test, rc, "CHR_test_add_app_group");
        }
    }

    /* Run the test */
    if (CHR_OK == rc)
    {
        printf("Run the test...\n");
        rc = CHR_test_start(test);

        if (rc != CHR_OK)
        {
            show_error(test, rc, "CHR_test_start");
        }
    }

    /*
     * We have to wait for the test to stop before we can look
     * at the results from it. We'll wait for 2 minutes here,
     * then call it an error if it has not yet stopped.
     */
    if (CHR_OK == rc)
    {
        printf("Wait for the test to stop...\n");
        rc = CHR_test_query_stop(test, timeout);

        if (rc != CHR_OK)
        {
            show_error(test, rc, "CHR_test_query_stop");
        }
    }

    /* Finally, save the test */
    if (CHR_OK == rc)
    {
        printf("Save the test...\n");
        rc = CHR_test_set_filename(
                test,
                testFile,
                strlen(testFile));

        if (rc != CHR_OK)
        {
            show_error(test, rc, "CHR_test_set_filename");
        }
        else
        {
            rc = CHR_test_save(test);
        }

        if (rc != CHR_OK)
        {
            show_error(test, rc, "CHR_test_save");
        }
    }

    /* Explicitly free allocated resources */
    if (test != (CHR_TEST_HANDLE)NULL)
    {
        CHR_test_delete(test);
    }

    if (appGroupLoaded != (CHR_APP_GROUP_HANDLE)NULL)
    {
        CHR_app_group_delete(appGroupLoaded);
    }

    if (appGroupNew != (CHR_APP_GROUP_HANDLE)NULL)
    {
        CHR_app_group_delete(appGroupNew);
    }

    /* Exit test with success or error code */
    exit(rc);
}


/**************************************************************
 *
 * Print information about an error and exit.
 *
 * Parameters: handle - what object had the error
 *             code   - the IxChariot API return code
 *             where  - what function call failed
 *
 **************************************************************/
static void
show_error(
    CHR_HANDLE handle,
    CHR_API_RC code,
    CHR_STRING where)
{
    char       msg[CHR_MAX_RETURN_MSG];
    CHR_LENGTH msgLen;

    char       errorInfo[CHR_MAX_ERROR_INFO];
    CHR_LENGTH errorLen;

    CHR_API_RC rc;


    /*
     * Get the API message for this return code.
     */
    rc = CHR_api_get_return_msg(
            code,
            msg,
            CHR_MAX_RETURN_MSG,
            &msgLen);

    if (rc != CHR_OK)
    {
        /* Could not get the message: show why */
        printf("%s failed\n", where);
        printf("Unable to get message for return code %d, rc = %d\n", code, rc);
    }
    else
    {
        /* Tell the user about the error */
        printf("%s failed: rc = %d (%s)\n", where, code, msg);
    }

    /*
     * See if there is extended error information available.
     * It's meaningful only after some error returns. After 
     * failed "new" function calls, we don't have a handle so 
     * we cannot check for extended error information.
     */
    if ((code == CHR_OPERATION_FAILED || 
         code == CHR_OBJECT_INVALID ||
         code == CHR_APP_GROUP_INVALID) &&
         handle != (CHR_HANDLE)NULL)
    {
        rc = CHR_common_error_get_info(
                handle,
                CHR_DETAIL_LEVEL_ALL,
                errorInfo,
                CHR_MAX_ERROR_INFO,
                &errorLen);

        if (rc == CHR_OK)
        {
            /*
             * We can ignore all non-success return codes here
             * because most should not occur (the api's been
             * initialized, the handle is good, the buffer
             * pointer is valid, and the detail level is okay),
             * and the NO_SUCH_VALUE return code here means
             * there is no info available.
             */
            printf("Extended error info:\n%s\n", errorInfo);
        }
    }
}

