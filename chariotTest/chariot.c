/****************************************************************
 *
 *  IxChariot API SDK              File: ChrPairsTest.c
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
 *
 *  EXAMPLE: Endpoint Pairs Test
 *  This program creates and runs a test with just endpoint
 *  pairs, then saves the test to a file.
 *
 *  All attributes of this test are defined by this program.
 *
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <libconfig.h>
#include <ctype.h>
#include "iniparser.h"


/*
 * The header file which defines everything in the Chariot API:
 * functions, constants, etc.
 */
#include "chrapi.h"

/*
 * Data for test:
 * Change these values for your local network if desired.
 */





//static
//CHR_COUNT pairCount = 8;





//static
//CHR_STRING e1Addrs[] = {
//    "192.168.3.100",
//    "192.168.3.100",
//	"192.168.3.100",
//    "192.168.3.100",
//    "192.168.3.100",
//	"192.168.3.100",
//	"192.168.3.100",
//	"192.168.3.100"
//};

//static
//CHR_STRING e2Addrs[] = {
//    "192.168.3.100",
//    "192.168.3.100",
//	"192.168.3.100",
//    "192.168.3.100",
//	"192.168.3.100",
//	"192.168.3.100",
//	"192.168.3.100",
//    "192.168.3.100"
//};

//static
//CHR_PROTOCOL protocols[] = {
//    CHR_PROTOCOL_TCP,
//    CHR_PROTOCOL_TCP,
//	CHR_PROTOCOL_TCP,
//	CHR_PROTOCOL_TCP,
//    CHR_PROTOCOL_TCP,
//	CHR_PROTOCOL_TCP,
//	CHR_PROTOCOL_TCP,
//	CHR_PROTOCOL_TCP,
//	CHR_PROTOCOL_TCP,
//	CHR_PROTOCOL_TCP,
//	CHR_PROTOCOL_TCP,
//    CHR_PROTOCOL_TCP
//};

static
CHR_TEST_END test_end[] = {
    CHR_TEST_END_AFTER_FIXED_DURATION,
    CHR_TEST_END_AFTER_FIXED_DURATION,
	CHR_TEST_END_AFTER_FIXED_DURATION,
	CHR_TEST_END_AFTER_FIXED_DURATION,
    CHR_TEST_END_AFTER_FIXED_DURATION,
	CHR_TEST_END_AFTER_FIXED_DURATION,
	CHR_TEST_END_AFTER_FIXED_DURATION,
    CHR_TEST_END_AFTER_FIXED_DURATION
};


static char*
show_throughput_units_string(
    CHR_THROUGHPUT_UNITS throughputUnits)
{
    switch (throughputUnits) {
        case CHR_THROUGHPUT_UNITS_KB:
            return "KB";
        case CHR_THROUGHPUT_UNITS_kB:
            return "kB";
        case CHR_THROUGHPUT_UNITS_Kb:
            return "Kb";
        case CHR_THROUGHPUT_UNITS_kb:
            return "kb";
        case CHR_THROUGHPUT_UNITS_Mb:
            return "Mb";
        case CHR_THROUGHPUT_UNITS_Gb:
            return "Gb";
        default:
            return "Unknown units or units not set";
    };
}


//static
//CHR_STRING scripts[] = {
//    "c:/Program Files/Ixia/IxChariot/Scripts/High_Performance_Throughput.scr",
//    "c:/Program Files/Ixia/IxChariot/Scripts/High_Performance_Throughput.scr",
//	"c:/Program Files/Ixia/IxChariot/Scripts/High_Performance_Throughput.scr",
//	"c:/Program Files/Ixia/IxChariot/Scripts/High_Performance_Throughput.scr",
//    "c:/Program Files/Ixia/IxChariot/Scripts/High_Performance_Throughput.scr",
//	"c:/Program Files/Ixia/IxChariot/Scripts/High_Performance_Throughput.scr",
//	"c:/Program Files/Ixia/IxChariot/Scripts/High_Performance_Throughput.scr",
//    "c:/Program Files/Ixia/IxChariot/Scripts/High_Performance_Throughput.scr"
//};

static
CHR_COUNT timeout = 1;    /* 5 seconds */
static
CHR_COUNT maxWait = 120;  /* 2 minutes in seconds */





static
CHR_STRING logFile = "pairsTest.log";






/*
 * Local function to log & print information about errors.
 */
static void
show_error(
    CHR_HANDLE handle,
    CHR_API_RC code,
    CHR_STRING where);


static void
show_results(
    CHR_HANDLE handle);

static void
set_runtime(
    
CHR_RUNOPTS_HANDLE run);



/**************************************************************
 *
 * Program main
 *
 * If the return code from any Chariot API function call
 * is not CHR_OK, the show_error() function is called to
 * display information about what happened then exit.
 *
 **************************************************************/
int find_index(int a[], int num_elements, int value)
{
   int i;
   for (i=0; i<num_elements; i++)
   {
	 if (a[i] == value)
	 {
	    return(value);  /* it was found */
	 }
   }
   return(-1);  /* if it was not found */
}

void create_example_ini_file(void)
{
    FILE    *   ini ;

    ini = fopen("example.ini", "w");
    fprintf(ini,
    "#\n"
    "# This is an example of ini file\n"
    "#\n"
    "\n"
    "[Pizza]\n"
    "\n"
    "Ham       = yes ;\n"
    "Mushrooms = TRUE ;\n"
    "Capres    = 0 ;\n"
    "Cheese    = Non ;\n"
    "\n"
    "\n"
    "[Wine]\n"
    "\n"
    "Grape     = Cabernet Sauvignon ;\n"
    "Year      = 1989 ;\n"
    "Country   = Spain ;\n"
    "Alcohol   = 12.5  ;\n"
    "\n");
    fclose(ini);
}


static void
show_results_error(
    CHR_API_RC rc,
    CHR_STRING what)
{
    char msg[CHR_MAX_RETURN_MSG];

    CHR_LENGTH len;

    CHR_API_RC msgRc;


    printf("Get %s failed: ", what);
    msgRc = CHR_api_get_return_msg(rc, msg,
                                   CHR_MAX_RETURN_MSG,
                                  &len);
    if (msgRc == CHR_OK) {
        printf("%s\n", msg);
    }
    else {
        printf("rc = %d\n", rc );
    }
}
 





void main() {

	config_t cfg;               /*Returns all parameters in this structure */
    config_setting_t *setting;
    const char *str1, *str2;
    int tmp;
	
	CHR_STRING e1Addrs[12] ;

	CHR_STRING e2Addrs[12] ;

	CHR_STRING scripts[12] ;

	CHR_PROTOCOL protocols[12] ;

	CHR_STRING testFile[1] ;

	CHR_STRING testFile1[1] ;

	CHR_STRING testFile2[1] ;

	CHR_COUNT pairCount ;

	CHR_COUNT setpair ;

	

	
 
    char *config_file_name = "config.txt";
 
    ///*Initialization */
    //config_init(&cfg);
 
    ///* Read the file. If there is an error, report it and exit. */
    //if (!config_read_file(&cfg, config_file_name))
    //{
    //    printf("\n%s:%d - %s", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
    //    config_destroy(&cfg);
    //    return -1;
    //}
     
    ///* Get the configuration file name. */

    FILE *ptr_file;
    char buf[1000];
	FILE *fp;
    char ch;

	float adr1;
	char adr[1000] ; 
	int x ;
	char name[20]; 
	char tel[50];
	char field[20];
	char areaCode[20];
	char code[20];
	int age;
	int line_num = 1;
	int find_result = 0;
	int duration = 120;
	
	dictionary  *   ini ;

    /* Some temporary variables to hold query results */
	int j;
	int k;
    int             b ;
    int             i ;
    double          d ;
    char        *   s ;
	char        *   s1 ;
	char        *   s2 ;
	char        *   s3 ;
	char        *   s4 ;
	char        *   s5 ;
	char        *   s6 ;
	int            s7 ;
	int            s8 ;

    CHR_TEST_HANDLE test;
    CHR_PAIR_HANDLE pair;
	CHR_RUNOPTS_HANDLE runopts;

    char       errorInfo[CHR_MAX_ERROR_INFO];

	char buffer[CHR_MAX_FILE_PATH];

    CHR_LENGTH errorLen;

    CHR_COUNT index , prIndex;

    CHR_BOOLEAN isStopped;
    CHR_COUNT   timer = 0;

    CHR_API_RC rc;

	CHR_LENGTH len;

	

	CHR_FLOAT  avg;

	CHR_THROUGHPUT_UNITS throughput;


	//create_example_ini_file();

	ini = iniparser_load("config.ini");

	if (ini==NULL) {
        fprintf(stderr, "cannot parse file: %s\n");
    }

	printf("Channel_tst:\n");
    s1 = iniparser_getstring(ini, "Channel_tst:Address_1", NULL);

    printf("Address1:     %s\n", s1 ? s1 : "UNDEF");

    
    s2 = iniparser_getstring(ini, "Channel_tst:Address_2", NULL);
    printf("Address2:      %s\n", s2 ? s2 : "UNDEF");



    i = iniparser_getint(ini, "Channel_tst:pairCount", -1);
    printf("Pair_count:   %d\n", i);

	k = iniparser_getint(ini, "Channel_tst:setpair", -1);
    printf("set_pair:   %d\n", k);

    
    s3 = iniparser_getstring(ini, "Channel_tst:script", NULL);
    printf("Script:   %s\n", s3 ? s3 : "UNDEF");

	s4 = iniparser_getstring(ini, "Channel_tst:File_name_TXRX", NULL);
    printf("Script:   %s\n", s4 ? s4 : "UNDEF");

	s5 = iniparser_getstring(ini, "Channel_tst:File_name_TX", NULL);
    printf("Script:   %s\n", s5 ? s5 : "UNDEF");

	s6 = iniparser_getstring(ini, "Channel_tst:File_name_RX", NULL);
    printf("Script:   %s\n", s6 ? s6 : "UNDEF");

    s7 = iniparser_getint(ini, "Channel_tst:Protocol_1", -1);
    printf("Pair_count:   %d\n", i);

	s8 = iniparser_getint(ini, "Channel_tst:Protocol_2", -1);
    printf("set_pair:   %d\n", k);



	testFile[0] = s4;
	testFile1[0] = s5;
	testFile2[0] = s6;

	


	pairCount = i;

	setpair = k;

	for( j = 0; j < pairCount; j++) {
	    
		
		if (j<setpair/2){
		  e1Addrs[j] = s1;
		  e2Addrs[j] = s2;
		}
		else {
        e1Addrs[j] = s2; 
		e2Addrs[j] = s1;
		}
	
	}

	
	for( j = 0; j < pairCount; j++) {
	    
		
		if (j<setpair/2){
		  protocols[j] = s7;
		  protocols[j] = s7;
		}
		else {
        protocols[j] = s8; 
		protocols[j] = s8;
		}
	
	}




    
	for( j = 0; j < pairCount; j++) {
	    scripts[j] = s3;
	}




	//ptr_file =fopen("input.txt","r");
 //   if (!ptr_file)
 //       	printf("Open fail");

 //   while (fgets(buf,1000, ptr_file)!=NULL)
 //           printf("%s",buf);  
	//        if((strstr(buf, "adr")) != NULL) {
	//		printf("A match found on line: %d\n", line_num);
	//		printf("\n%s\n", buf);
	//		find_result++;
	//	}
	//	line_num++; 
	//			
	//        



 //   fclose(ptr_file);
 //   printf("close successfully\n");










    /* Initialize the Chariot API */
    rc = CHR_api_initialize(CHR_DETAIL_LEVEL_ALL, errorInfo,
                            CHR_MAX_ERROR_INFO, &errorLen);

	//if (config_lookup_string(&cfg, "filename", &str1))
 //       printf("\nFile Type: %s", str1);
 //   else
 //       printf("\nNo 'filename' setting in configuration file.");




    if (rc != CHR_OK) {

        /*
         * Because initialization failed, we can't
         * ask the API for the message for this
         * return code so we can't call our
         * show_error() function. Instead, we'll
         * print what we do know before exiting.
         */
        printf("Initialization failed: rc = %d\n", rc);
        printf("Extended error info:\n%s\n", errorInfo);
        exit(255);
    }

    /* Create a new test */
    printf("Create the test...\n");
    rc = CHR_test_new(&test);
    if (rc != CHR_OK) {
        show_error((CHR_HANDLE)NULL, rc, "test_new");
    }

    /* Set the test filename for saving later */
    rc = CHR_test_set_filename(test, s4, strlen(s4));
    if (rc != CHR_OK) {
        show_error(test, rc, "test_set_filename");
    }

	rc = CHR_test_get_runopts(test,&runopts);

	rc = CHR_runopts_set_test_end(runopts,test_end[0]);

	rc = CHR_runopts_set_test_duration(runopts,duration);


    /* Define some pairs for the test */
    for( index = 0; index < pairCount; index++) {

        char comment[CHR_MAX_PAIR_COMMENT];

        /* Create a pair */
        printf("Create a pair...\n");
        rc = CHR_pair_new(&pair);
        if (rc != CHR_OK) {
            show_error((CHR_HANDLE)NULL, rc, "pair_new");
        }

        /* Set the pair attributes from our lists */
        printf("Set pair attributes...\n");
        sprintf(comment, "Pair %d", index+1);
        rc = CHR_pair_set_comment(pair,
                                  comment,
                           strlen(comment));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_comment");
        }
        rc = CHR_pair_set_e1_addr(pair,
                                  e1Addrs[index],
								  strlen(e1Addrs[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_e1_addr");
        }
        rc = CHR_pair_set_e2_addr(pair,
                                  e2Addrs[index],
                           strlen(e2Addrs[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_e2_addr");
        }
        rc = CHR_pair_set_protocol(pair, protocols[index]);
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_protocol");
        }
        rc = CHR_pair_use_script_filename(pair,
                                          scripts[index],
                                   strlen(scripts[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_use_script_filename");
        }

		

        /* Add the pair to the test */
        rc = CHR_test_add_pair(test, pair);
        if (rc != CHR_OK) {
            show_error(test, rc, "test_add_pair");
        }
    }

    /* The test is defined, so now run it */
    /*printf("Run the test...\n");
    rc = CHR_test_start(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "start_ test");
    }

    /*
     * Wait for the test to stop
     * We'll check in a loop here every 5 seconds
     * then call it an error after two minutes if
     * the test is still not stopped.
     */
    /*printf("Wait for the test to stop...\n");
    isStopped = CHR_FALSE;
    timer = 0;
    while(!isStopped && timer < maxWait) {
        rc = CHR_test_query_stop(test, timeout);
        if (rc == CHR_OK) {
            isStopped = CHR_TRUE;
        }
        else if (rc == CHR_TIMED_OUT) {
            timer += timeout;
            printf("Waiting for test to stop... (%d)\n",
                    timer );
        }
        else {
            show_error(test, rc, "test_query_stop");
        }
    }
    if (!isStopped) {
        show_error(test, CHR_TIMED_OUT, "test_query_stop");
    }

    /* Finally, save the test */
    printf("Save the test..\n");
    rc = CHR_test_save(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "test_save");
    }
	

 //   /*
 //    * The test was successfully saved, so we're done!
 //    */
 //   /*exit(EXIT_SUCCESS);*/

	/*printf("Load the test...\n");
    rc = CHR_test_load(test, buffer, strlen(buffer));
    //if (rc != CHR_OK ) {
    //    show_error(test, rc, "test_load");
    //}

	printf("Test definition and results:\n");
    rc = CHR_test_get_filename(test, buffer,
                               CHR_MAX_FILENAME, &len);
    if (rc != CHR_OK ) {
        show_error(test, rc, "test_get_filename");
    }
    printf("  Filename        : %s\n", buffer);

	rc = CHR_test_get_throughput_units(test, &throughput);
    if (rc != CHR_OK ) {
        show_error(test, rc, "test_get_throughput_units");
    }
    printf("  Throughput units: %s\n", show_throughput_units_string(throughput));

	rc = CHR_test_get_runopts(test,&runopts);
	if (rc != CHR_OK ) {
        show_error(test, rc, "test_get_runopts");
    }
    printf("  Run Options: %s\n", runopts);




	for (prIndex = 0; prIndex < pairCount; prIndex++ ) {

        /* Print pair definition */
        /*printf("\nPair %d:\n", prIndex+1);
        rc = CHR_test_get_pair(test, prIndex, &pair);
        if (rc != CHR_OK ) {
            show_error(test, rc, "test_get_pair");
        }
        rc = CHR_pair_get_comment(pair, buffer,
                                  CHR_MAX_PAIR_COMMENT, &len);
        if (rc != CHR_OK ) {
            show_error(pair, rc, "pair_get_comment");
        }
        printf("  Comment            : %s\n", buffer);
	

        show_results(pair);

	}*/




	rc = CHR_api_initialize(CHR_DETAIL_LEVEL_ALL, errorInfo,
                            CHR_MAX_ERROR_INFO, &errorLen);

	


    if (rc != CHR_OK) {

        /*
         * Because initialization failed, we can't
         * ask the API for the message for this
         * return code so we can't call our
         * show_error() function. Instead, we'll
         * print what we do know before exiting.
         */
        printf("Initialization failed: rc = %d\n", rc);
        printf("Extended error info:\n%s\n", errorInfo);
        exit(255);
    }

    /* Create a new test */
    printf("Create the test...\n");
    rc = CHR_test_new(&test);
    if (rc != CHR_OK) {
        show_error((CHR_HANDLE)NULL, rc, "test_new");
    }

    /* Set the test filename for saving later */
    rc = CHR_test_set_filename(test, s5, strlen(s5));
    if (rc != CHR_OK) {
        show_error(test, rc, "test_set_filename");
    }

	rc = CHR_test_get_runopts(test,&runopts);

	rc = CHR_runopts_set_test_end(runopts,test_end[0]);

	rc = CHR_runopts_set_test_duration(runopts,duration);





    for( j = 0; j < pairCount; j++) {
	    
		
		
		  e1Addrs[j] = s1;
		  e2Addrs[j] = s2;
	
	
	}

	for( j = 0; j < pairCount; j++) {
	    
		
		if (j<setpair/2){
		  protocols[j] = s7;
		  protocols[j] = s7;
		}
		else {
        protocols[j] = s8; 
		protocols[j] = s8;
		}
	
	}


	for( j = 0; j < pairCount; j++) {
	    scripts[j] = s3;
	}



    /* Define some pairs for the test */
    for( index = 0; index < pairCount; index++) {

        char comment[CHR_MAX_PAIR_COMMENT];

        /* Create a pair */
        printf("Create a pair...\n");
        rc = CHR_pair_new(&pair);
        if (rc != CHR_OK) {
            show_error((CHR_HANDLE)NULL, rc, "pair_new");
        }

        /* Set the pair attributes from our lists */
        printf("Set pair attributes...\n");
        sprintf(comment, "Pair %d", index+1);
        rc = CHR_pair_set_comment(pair,
                                  comment,
                           strlen(comment));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_comment");
        }
        rc = CHR_pair_set_e1_addr(pair,
                                  e1Addrs[index],
                           strlen(e1Addrs[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_e1_addr");
        }
        rc = CHR_pair_set_e2_addr(pair,
                                  e2Addrs[index],
                           strlen(e2Addrs[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_e2_addr");
        }
        rc = CHR_pair_set_protocol(pair, protocols[index]);
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_protocol");
        }
        rc = CHR_pair_use_script_filename(pair,
                                          scripts[index],
                                   strlen(scripts[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_use_script_filename");
        }

        /* Add the pair to the test */
        rc = CHR_test_add_pair(test, pair);
        if (rc != CHR_OK) {
            show_error(test, rc, "test_add_pair");
        }
    }

    /* The test is defined, so now run it */
    /*printf("Run the test...\n");
    rc = CHR_test_start(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "start_ test");
    }

    /*
     * Wait for the test to stop
     * We'll check in a loop here every 5 seconds
     * then call it an error after two minutes if
     * the test is still not stopped.
     */
    /*printf("Wait for the test to stop...\n");
    isStopped = CHR_FALSE;
    timer = 0;
    while(!isStopped && timer < maxWait) {
        rc = CHR_test_query_stop(test, timeout);
        if (rc == CHR_OK) {
            isStopped = CHR_TRUE;
        }
        else if (rc == CHR_TIMED_OUT) {
            timer += timeout;
            printf("Waiting for test to stop... (%d)\n",
                    timer );
        }
        else {
            show_error(test, rc, "test_query_stop");
        }
    }
    if (!isStopped) {
        show_error(test, CHR_TIMED_OUT, "test_query_stop");
    }

    /* Finally, save the test */
    printf("Save the test..\n");
    rc = CHR_test_save(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "test_save");
    }

    /*
     * The test was successfully saved, so we're done!
     */
    


    rc = CHR_api_initialize(CHR_DETAIL_LEVEL_ALL, errorInfo,
                            CHR_MAX_ERROR_INFO, &errorLen);

	


    if (rc != CHR_OK) {

        /*
         * Because initialization failed, we can't
         * ask the API for the message for this
         * return code so we can't call our
         * show_error() function. Instead, we'll
         * print what we do know before exiting.
         */
        printf("Initialization failed: rc = %d\n", rc);
        printf("Extended error info:\n%s\n", errorInfo);
        exit(255);
    }

    /* Create a new test */
    printf("Create the test...\n");
    rc = CHR_test_new(&test);
    if (rc != CHR_OK) {
        show_error((CHR_HANDLE)NULL, rc, "test_new");
    }

    /* Set the test filename for saving later */
    rc = CHR_test_set_filename(test, s6, strlen(s6));
    if (rc != CHR_OK) {
        show_error(test, rc, "test_set_filename");
    }

	rc = CHR_test_get_runopts(test,&runopts);

	rc = CHR_runopts_set_test_end(runopts,test_end[0]);

	rc = CHR_runopts_set_test_duration(runopts,duration);


    
	for( j = 0; j < pairCount; j++) {
	    
		
		
		  e1Addrs[j] = s2;
		  e2Addrs[j] = s1;
	
	
	}

	for( j = 0; j < pairCount; j++) {
	    
		
		if (j<setpair/2){
		  protocols[j] = s7;
		  protocols[j] = s7;
		}
		else {
        protocols[j] = s8; 
		protocols[j] = s8;
		}
	
	}


    for( j = 0; j < pairCount; j++) {
	    scripts[j] = s3;
	}




    /* Define some pairs for the test */
    for( index = 0; index < pairCount; index++) {

        char comment[CHR_MAX_PAIR_COMMENT];

        /* Create a pair */
        printf("Create a pair...\n");
        rc = CHR_pair_new(&pair);
        if (rc != CHR_OK) {
            show_error((CHR_HANDLE)NULL, rc, "pair_new");
        }

        /* Set the pair attributes from our lists */
        printf("Set pair attributes...\n");
        sprintf(comment, "Pair %d", index+1);
        rc = CHR_pair_set_comment(pair,
                                  comment,
                           strlen(comment));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_comment");
        }
        rc = CHR_pair_set_e1_addr(pair,
                                  e1Addrs[index],
                           strlen(e1Addrs[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_e1_addr");
        }
        rc = CHR_pair_set_e2_addr(pair,
                                  e2Addrs[index],
                           strlen(e2Addrs[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_e2_addr");
        }
        rc = CHR_pair_set_protocol(pair, protocols[index]);
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_protocol");
        }
        rc = CHR_pair_use_script_filename(pair,
                                          scripts[index],
                                   strlen(scripts[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_use_script_filename");
        }

        /* Add the pair to the test */
        rc = CHR_test_add_pair(test, pair);
        if (rc != CHR_OK) {
            show_error(test, rc, "test_add_pair");
        }
    }

    /* The test is defined, so now run it */
    /*printf("Run the test...\n");
    rc = CHR_test_start(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "start_ test");
    }

    /*
     * Wait for the test to stop
     * We'll check in a loop here every 5 seconds
     * then call it an error after two minutes if
     * the test is still not stopped.
     */
    /*printf("Wait for the test to stop...\n");
    isStopped = CHR_FALSE;
    timer = 0;
    while(!isStopped && timer < maxWait) {
        rc = CHR_test_query_stop(test, timeout);
        if (rc == CHR_OK) {
            isStopped = CHR_TRUE;
        }
        else if (rc == CHR_TIMED_OUT) {
            timer += timeout;
            printf("Waiting for test to stop... (%d)\n",
                    timer );
        }
        else {
            show_error(test, rc, "test_query_stop");
        }
    }
    if (!isStopped) {
        show_error(test, CHR_TIMED_OUT, "test_query_stop");
    }

    /* Finally, save the test */
    printf("Save the test..\n");
    rc = CHR_test_save(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "test_save");
    }

    /*
     * The test was successfully saved, so we're done!
     */
    
	
	printf("Security_tst:     %s\n");

	s1 = iniparser_getstring(ini, "Security_tst:Address_1", NULL);

    printf("Address1:     %s\n", s1 ? s1 : "UNDEF");

    
    s2 = iniparser_getstring(ini, "Security_tst:Address_2", NULL);
    printf("Address2:      %s\n", s2 ? s2 : "UNDEF");



    i = iniparser_getint(ini, "Security_tst:pairCount", -1);
    printf("Pair_count:   %d\n", i);

	k = iniparser_getint(ini, "Security_tst:setpair", -1);
    printf("set_pair:   %d\n", k);

    
    s3 = iniparser_getstring(ini, "Security_tst:script", NULL);
    printf("Script:   %s\n", s3 ? s3 : "UNDEF");

	s4 = iniparser_getstring(ini, "Security_tst:File_name_TXRX", NULL);
    printf("Script:   %s\n", s4 ? s4 : "UNDEF");

	s5 = iniparser_getstring(ini, "Security_tst:File_name_TX", NULL);
    printf("Script:   %s\n", s5 ? s5 : "UNDEF");

	s6 = iniparser_getstring(ini, "Security_tst:File_name_RX", NULL);
    printf("Script:   %s\n", s6 ? s6 : "UNDEF");

	s7 = iniparser_getint(ini, "Security_tst:Protocol_1", -1);
    printf("Pair_count:   %d\n", i);

	s8 = iniparser_getint(ini, "Security_tst:Protocol_2", -1);
    printf("set_pair:   %d\n", k);



	testFile[0]  = s4;
	testFile1[0] = s5;
	testFile2[0] = s6;


	pairCount = i;

	setpair = k;

	for( j = 0; j < pairCount; j++) {
	    
		
		if (j<setpair/2){
		  e1Addrs[j] = s1;
		  e2Addrs[j] = s2;
		}
		else {
        e1Addrs[j] = s2; 
		e2Addrs[j] = s1;
		}
	
	}

	for( j = 0; j < pairCount; j++) {
	    
		
		if (j<setpair/2){
		  protocols[j] = s7;
		  protocols[j] = s7;
		}
		else {
        protocols[j] = s8; 
		protocols[j] = s8;
		}
	
	}

    
	for( j = 0; j < pairCount; j++) {
	    scripts[j] = s3;
	}


	//ptr_file =fopen("input.txt","r");
 //   if (!ptr_file)
 //       	printf("Open fail");

 //   while (fgets(buf,1000, ptr_file)!=NULL)
 //           printf("%s",buf);  
	//        if((strstr(buf, "adr")) != NULL) {
	//		printf("A match found on line: %d\n", line_num);
	//		printf("\n%s\n", buf);
	//		find_result++;
	//	}
	//	line_num++; 
	//			
	//        



 //   fclose(ptr_file);
 //   printf("close successfully\n");





    /* Initialize the Chariot API */
    rc = CHR_api_initialize(CHR_DETAIL_LEVEL_ALL, errorInfo,
                            CHR_MAX_ERROR_INFO, &errorLen);

	//if (config_lookup_string(&cfg, "filename", &str1))
 //       printf("\nFile Type: %s", str1);
 //   else
 //       printf("\nNo 'filename' setting in configuration file.");




    if (rc != CHR_OK) {

        /*
         * Because initialization failed, we can't
         * ask the API for the message for this
         * return code so we can't call our
         * show_error() function. Instead, we'll
         * print what we do know before exiting.
         */
        printf("Initialization failed: rc = %d\n", rc);
        printf("Extended error info:\n%s\n", errorInfo);
        exit(255);
    }

    /* Create a new test */
    printf("Create the test...\n");
    rc = CHR_test_new(&test);
    if (rc != CHR_OK) {
        show_error((CHR_HANDLE)NULL, rc, "test_new");
    }

    /* Set the test filename for saving later */
    rc = CHR_test_set_filename(test, s4, strlen(s4));
    if (rc != CHR_OK) {
        show_error(test, rc, "test_set_filename");
    }



	rc = CHR_test_get_runopts(test,&runopts);

	rc = CHR_runopts_set_test_end(runopts,test_end[0]);

	rc = CHR_runopts_set_test_duration(runopts,duration);






    /* Define some pairs for the test */
    for( index = 0; index < pairCount; index++) {

        char comment[CHR_MAX_PAIR_COMMENT];

        /* Create a pair */
        printf("Create a pair...\n");
        rc = CHR_pair_new(&pair);
        if (rc != CHR_OK) {
            show_error((CHR_HANDLE)NULL, rc, "pair_new");
        }

        /* Set the pair attributes from our lists */
        printf("Set pair attributes...\n");
        sprintf(comment, "Pair %d", index+1);
        rc = CHR_pair_set_comment(pair,
                                  comment,
                           strlen(comment));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_comment");
        }
        rc = CHR_pair_set_e1_addr(pair,
                                  e1Addrs[index],
								  strlen(e1Addrs[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_e1_addr");
        }
        rc = CHR_pair_set_e2_addr(pair,
                                  e2Addrs[index],
                           strlen(e2Addrs[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_e2_addr");
        }
        rc = CHR_pair_set_protocol(pair, protocols[index]);
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_protocol");
        }
        rc = CHR_pair_use_script_filename(pair,
                                          scripts[index],
                                   strlen(scripts[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_use_script_filename");
        }

        /* Add the pair to the test */
        rc = CHR_test_add_pair(test, pair);
        if (rc != CHR_OK) {
            show_error(test, rc, "test_add_pair");
        }
    }

    /* The test is defined, so now run it */
    /*printf("Run the test...\n");
    rc = CHR_test_start(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "start_ test");
    }

    /*
     * Wait for the test to stop
     * We'll check in a loop here every 5 seconds
     * then call it an error after two minutes if
     * the test is still not stopped.
     */
    /*printf("Wait for the test to stop...\n");
    isStopped = CHR_FALSE;
    timer = 0;
    while(!isStopped && timer < maxWait) {
        rc = CHR_test_query_stop(test, timeout);
        if (rc == CHR_OK) {
            isStopped = CHR_TRUE;
        }
        else if (rc == CHR_TIMED_OUT) {
            timer += timeout;
            printf("Waiting for test to stop... (%d)\n",
                    timer );
        }
        else {
            show_error(test, rc, "test_query_stop");
        }
    }
    if (!isStopped) {
        show_error(test, CHR_TIMED_OUT, "test_query_stop");
    }

    /* Finally, save the test */
    printf("Save the test..\n");
    rc = CHR_test_save(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "test_save");
    }

    /*
     * The test was successfully saved, so we're done!
     */
    /*exit(EXIT_SUCCESS);*/



	rc = CHR_api_initialize(CHR_DETAIL_LEVEL_ALL, errorInfo,
                            CHR_MAX_ERROR_INFO, &errorLen);

	


    if (rc != CHR_OK) {

        /*
         * Because initialization failed, we can't
         * ask the API for the message for this
         * return code so we can't call our
         * show_error() function. Instead, we'll
         * print what we do know before exiting.
         */
        printf("Initialization failed: rc = %d\n", rc);
        printf("Extended error info:\n%s\n", errorInfo);
        exit(255);
    }

    /* Create a new test */
    printf("Create the test...\n");
    rc = CHR_test_new(&test);
    if (rc != CHR_OK) {
        show_error((CHR_HANDLE)NULL, rc, "test_new");
    }

    /* Set the test filename for saving later */
    rc = CHR_test_set_filename(test, s5, strlen(s5));
    if (rc != CHR_OK) {
        show_error(test, rc, "test_set_filename");
    }

	rc = CHR_test_get_runopts(test,&runopts);

	rc = CHR_runopts_set_test_end(runopts,test_end[0]);

	rc = CHR_runopts_set_test_duration(runopts,duration);


    for( j = 0; j < pairCount; j++) {
	    
		
		
		  e1Addrs[j] = s1;
		  e2Addrs[j] = s2;
	
	
	}

	for( j = 0; j < pairCount; j++) {
	    
		
		if (j<setpair/2){
		  protocols[j] = s7;
		  protocols[j] = s7;
		}
		else {
        protocols[j] = s8; 
		protocols[j] = s8;
		}
	
	}


	for( j = 0; j < pairCount; j++) {
	    scripts[j] = s3;
	}



    /* Define some pairs for the test */
    for( index = 0; index < pairCount; index++) {

        char comment[CHR_MAX_PAIR_COMMENT];

        /* Create a pair */
        printf("Create a pair...\n");
        rc = CHR_pair_new(&pair);
        if (rc != CHR_OK) {
            show_error((CHR_HANDLE)NULL, rc, "pair_new");
        }

        /* Set the pair attributes from our lists */
        printf("Set pair attributes...\n");
        sprintf(comment, "Pair %d", index+1);
        rc = CHR_pair_set_comment(pair,
                                  comment,
                           strlen(comment));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_comment");
        }
        rc = CHR_pair_set_e1_addr(pair,
                                  e1Addrs[index],
                           strlen(e1Addrs[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_e1_addr");
        }
        rc = CHR_pair_set_e2_addr(pair,
                                  e2Addrs[index],
                           strlen(e2Addrs[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_e2_addr");
        }
        rc = CHR_pair_set_protocol(pair, protocols[index]);
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_protocol");
        }
        rc = CHR_pair_use_script_filename(pair,
                                          scripts[index],
                                   strlen(scripts[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_use_script_filename");
        }

        /* Add the pair to the test */
        rc = CHR_test_add_pair(test, pair);
        if (rc != CHR_OK) {
            show_error(test, rc, "test_add_pair");
        }
    }

    /* The test is defined, so now run it */
    /*printf("Run the test...\n");
    rc = CHR_test_start(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "start_ test");
    }

    /*
     * Wait for the test to stop
     * We'll check in a loop here every 5 seconds
     * then call it an error after two minutes if
     * the test is still not stopped.
     */
    /*printf("Wait for the test to stop...\n");
    isStopped = CHR_FALSE;
    timer = 0;
    while(!isStopped && timer < maxWait) {
        rc = CHR_test_query_stop(test, timeout);
        if (rc == CHR_OK) {
            isStopped = CHR_TRUE;
        }
        else if (rc == CHR_TIMED_OUT) {
            timer += timeout;
            printf("Waiting for test to stop... (%d)\n",
                    timer );
        }
        else {
            show_error(test, rc, "test_query_stop");
        }
    }
    if (!isStopped) {
        show_error(test, CHR_TIMED_OUT, "test_query_stop");
    }

    /* Finally, save the test */
    printf("Save the test..\n");
    rc = CHR_test_save(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "test_save");
    }

    /*
     * The test was successfully saved, so we're done!
     */
    


    rc = CHR_api_initialize(CHR_DETAIL_LEVEL_ALL, errorInfo,
                            CHR_MAX_ERROR_INFO, &errorLen);

	


    if (rc != CHR_OK) {

        /*
         * Because initialization failed, we can't
         * ask the API for the message for this
         * return code so we can't call our
         * show_error() function. Instead, we'll
         * print what we do know before exiting.
         */
        printf("Initialization failed: rc = %d\n", rc);
        printf("Extended error info:\n%s\n", errorInfo);
        exit(255);
    }

    /* Create a new test */
    printf("Create the test...\n");
    rc = CHR_test_new(&test);
    if (rc != CHR_OK) {
        show_error((CHR_HANDLE)NULL, rc, "test_new");
    }

    /* Set the test filename for saving later */
    rc = CHR_test_set_filename(test, s6, strlen(s6));
    if (rc != CHR_OK) {
        show_error(test, rc, "test_set_filename");
    }

	rc = CHR_test_get_runopts(test,&runopts);

	rc = CHR_runopts_set_test_end(runopts,test_end[0]);

	rc = CHR_runopts_set_test_duration(runopts,duration);


    
	for( j = 0; j < pairCount; j++) {
	    
		
		
		  e1Addrs[j] = s2;
		  e2Addrs[j] = s1;
	
	
	}

	for( j = 0; j < pairCount; j++) {
	    
		
		if (j<setpair/2){
		  protocols[j] = s7;
		  protocols[j] = s7;
		}
		else {
        protocols[j] = s8; 
		protocols[j] = s8;
		}
	
	}


    for( j = 0; j < pairCount; j++) {
	    scripts[j] = s3;
	}




    /* Define some pairs for the test */
    for( index = 0; index < pairCount; index++) {

        char comment[CHR_MAX_PAIR_COMMENT];

        /* Create a pair */
        printf("Create a pair...\n");
        rc = CHR_pair_new(&pair);
        if (rc != CHR_OK) {
            show_error((CHR_HANDLE)NULL, rc, "pair_new");
        }

        /* Set the pair attributes from our lists */
        printf("Set pair attributes...\n");
        sprintf(comment, "Pair %d", index+1);
        rc = CHR_pair_set_comment(pair,
                                  comment,
                           strlen(comment));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_comment");
        }
        rc = CHR_pair_set_e1_addr(pair,
                                  e1Addrs[index],
                           strlen(e1Addrs[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_e1_addr");
        }
        rc = CHR_pair_set_e2_addr(pair,
                                  e2Addrs[index],
                           strlen(e2Addrs[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_e2_addr");
        }
        rc = CHR_pair_set_protocol(pair, protocols[index]);
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_protocol");
        }
        rc = CHR_pair_use_script_filename(pair,
                                          scripts[index],
                                   strlen(scripts[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_use_script_filename");
        }

        /* Add the pair to the test */
        rc = CHR_test_add_pair(test, pair);
        if (rc != CHR_OK) {
            show_error(test, rc, "test_add_pair");
        }
    }

    /* The test is defined, so now run it */
    /*printf("Run the test...\n");
    rc = CHR_test_start(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "start_ test");
    }

    /*
     * Wait for the test to stop
     * We'll check in a loop here every 5 seconds
     * then call it an error after two minutes if
     * the test is still not stopped.
     */
    /*printf("Wait for the test to stop...\n");
    isStopped = CHR_FALSE;
    timer = 0;
    while(!isStopped && timer < maxWait) {
        rc = CHR_test_query_stop(test, timeout);
        if (rc == CHR_OK) {
            isStopped = CHR_TRUE;
        }
        else if (rc == CHR_TIMED_OUT) {
            timer += timeout;
            printf("Waiting for test to stop... (%d)\n",
                    timer );
        }
        else {
            show_error(test, rc, "test_query_stop");
        }
    }
    if (!isStopped) {
        show_error(test, CHR_TIMED_OUT, "test_query_stop");
    }

    /* Finally, save the test */
    printf("Save the test..\n");
    rc = CHR_test_save(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "test_save");
    }

    /*
     * The test was successfully saved, so we're done!
     */

	





	iniparser_freedict(ini);
	exit(EXIT_SUCCESS);








}


/***************************************************************
 *
 * Print information about an error and exit. If there is
 * extended error information, log that before exiting.
 *
 * Parameters: handle - what object had the error
 *             code   - the Chariot API return code
 *             where  - what function call failed
 ***************************************************************/

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

    FILE  *fd;
    time_t currentTime;
    char  *timestamp;

    CHR_API_RC rc;


    /*
     * Get the API message for this return code.
     */
    rc = CHR_api_get_return_msg(code, msg,
                                CHR_MAX_RETURN_MSG, &msgLen);
    if (rc != CHR_OK) {

        /* Could not get the message: show why */
        printf("%s failed\n", where);
        printf(
          "Unable to get message for return code %d, rc = %d\n",
           code, rc);
    }
    else {

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
         handle != (CHR_HANDLE)NULL) {

        /* Open the log file */
        fd = fopen(logFile, "a+");

        /* Get the timestamp */
        currentTime = time(NULL);
        timestamp = ctime(&currentTime);

        /* Get the extended error info */
        rc = CHR_common_error_get_info(handle,
                                       CHR_DETAIL_LEVEL_ALL,
                                       errorInfo,
                                       CHR_MAX_ERROR_INFO,
                                      &errorLen);
        if (rc == CHR_OK) {

            /*
             * We can ignore all non-success return codes here
             * because most should not occur (the api's been
             * initialized, the handle is good, the buffer
             * pointer is valid, and the detail level is okay),
             * and the NO_SUCH_VALUE return code here means
             * there is no info available.
             */
            if (fd != NULL) {

                /* Log it if the file was opened successfully */
                fprintf(fd, "%s %s failed\n",
                        timestamp, where );
                fprintf(fd, "%s %s\n",
                        timestamp, errorInfo);
                fclose(fd);
            }
        }
    }

    /*
     * We've told everything we know, so now just exit.
     */
    exit(EXIT_FAILURE);
}


static void
show_common(
    CHR_HANDLE handle)
{
    CHR_API_RC rc;
    CHR_FLOAT  float_result;
    CHR_COUNT  count_result;

    /*
     * These do not have NO_SUCH_VALUE as a possible return,
     * so anything other than success is an error
     */
    rc = CHR_common_results_get_meas_time(handle, &float_result);
    if (rc != CHR_OK ) {
        show_results_error(rc, "meas_time");
        return;
    }
    printf("  Measured time           : %.3f\n", float_result);

    rc = CHR_common_results_get_trans_count(handle, &float_result);
    if (rc != CHR_OK ) {
        show_results_error(rc, "trans_count");
        return;
    }
    printf("  Transaction count       : %.0f\n", float_result);

    /*
     * These could have NO_SUCH_VALUE as a valid return,
     * depending on the specifics of the test.
     */
    /*Please remove this comment if you are not using a VoIPHPP sript
    rc = CHR_common_results_get_bytes_sent_e1(handle, &float_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Bytes sent E1            : n/a\n");
        }
        else {
            show_results_error(rc, "bytes_sent_e1");
            return;
        }
    }
    else {
        printf("  Bytes sent E1           : %.0f\n", float_result);
    }

    rc = CHR_common_results_get_bytes_recv_e1(handle, &float_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Bytes recv E1           : n/a\n");
        }
        else {
            show_results_error(rc, "bytes_recv_e1");
            return;
        }
    }
    else {
        printf("  Bytes recv E1           : %.0f\n", float_result);
    }

    rc = CHR_common_results_get_bytes_recv_e2(handle, &float_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Bytes recv E2           : n/a\n");
        }
        else {
            show_results_error(rc, "bytes_recv_e2");
            return;
        }
    }
    else {
        printf("  Bytes recv E2           : %.0f\n", float_result);
    }

    rc = CHR_common_results_get_dg_sent_e1(handle, &float_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  DGs sent E1             : n/a\n");
        }
        else {
            show_results_error(rc, "dg_sent_e1");
            return;
        }
    }
    else {
        printf("  DGs sent E1             : %.0f\n", float_result);
    }

    rc = CHR_common_results_get_dg_recv_e2(handle, &float_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  DGs recv E2             : n/a\n");
        }
        else {
            show_results_error(rc, "dg_recv_e2");
            return;
        }
    }
    else {
        printf("  DGs recv E2             : %.0f\n", float_result);
    }

    rc = CHR_common_results_get_dg_dup_recv_e2(handle, &float_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  DGs dup recv E2         : n/a\n");
        }
        else {
            show_results_error(rc, "dg_dup_recv_e2");
            return;
        }
    }
    else {
        printf("  DGs dup recv E2         : %.0f\n", float_result);
    }

    rc = CHR_common_results_get_dg_lost_e1_to_e2(handle, &float_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  DGs lost E1 to E2       : n/a\n");
        }
        else {
            show_results_error(rc, "dg_lost_e1_to_e2");
            return;
        }
    }
    else {
        printf("  DGs lost E1 to E2       : %.0f\n", float_result);
    }

    rc = CHR_common_results_get_dg_out_of_order(handle, &float_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  DGs out of order        : n/a\n");
        }
        else {
            show_results_error(rc, "dg_out_of_order");
            return;
        }
    }
    else {
        printf("  DGs out of order        : %.0f\n", float_result);
    }
    */ 
    /* TCP Statistics */
    /*Please remove this comment if you are not using a VoIPHPP sript
    rc = CHR_common_results_get_e1_syn_tx(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Syn sent                : n/a\n");
        }
        else {
            show_results_error(rc, "Syn sent");
            return;
        }
    }
    else {
        printf("  Syn sent                : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_syn_rx(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Syn received            : n/a\n");
        }
        else {
            show_results_error(rc, "Syn received");
            return;
        }
    }
    else {
        printf("  Syn received            : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_syn_failed(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Syn failed              : n/a\n");
        }
        else {
            show_results_error(rc, "Syn failed");
            return;
        }
    }
    else {
        printf("  Syn failed              : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_conn_established(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Connections established : n/a\n");
        }
        else {
            show_results_error(rc, "Connections established");
            return;
        }
    }
    else {
        printf("  Connections established : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_fin_tx(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Fin sent                : n/a\n");
        }
        else {
            show_results_error(rc, "Fin sent");
            return;
        }
    }
    else {
        printf("  Fin sent                : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_fin_rx(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Fin received            : n/a\n");
        }
        else {
            show_results_error(rc, "Fin received");
            return;
        }
    }
    else {
        printf("  Fin received            : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_ack_to_fin_tx(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Ack to Fin sent         : n/a\n");
        }
        else {
            show_results_error(rc, "Ack to Fin sent");
            return;
        }
    }
    else {
        printf("  Ack to Fin sent         : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_ack_to_fin_rx(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Ack to Fin received     : n/a\n");
        }
        else {
            show_results_error(rc, "Ack to Fin received");
            return;
        }
    }
    else {
        printf("  Ack to Fin received     : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_rst_tx(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Reset sent              : n/a\n");
        }
        else {
            show_results_error(rc, "Reset sent");
            return;
        }
    }
    else {
        printf("  Reset sent              : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_rst_rx(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Reset received          : n/a\n");
        }
        else {
            show_results_error(rc, "Reset received");
            return;
        }
    }
    else {
        printf("  Reset received          : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_tcp_retransmissions(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  TCP retransmissions     : n/a\n");
        }
        else {
            show_results_error(rc, "TCP retransmissions");
            return;
        }
    }
    else {
        printf("  TCP retransmissions     : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_tcp_timeouts(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  TCP timeouts            : n/a\n");
        }
        else {
            show_results_error(rc, "TCP timeouts");
            return;
        }
    }
    else {
        printf("  TCP timeouts            : %d\n", count_result);
    }
    */
}








static void
show_results(
    CHR_HANDLE handle)
{
    CHR_FLOAT  avg, min, max;
    CHR_FLOAT  result;
	CHR_COUNT pairindex ,minvalue,maxvalue,number;
    CHR_CHAR   format[1024];
    CHR_API_RC rc;
	


    /*
     * These could have NO_SUCH_VALUE as a valid return,
     * depending on the specifics of the test.
     */
    rc = CHR_pair_results_get_average(handle,
         CHR_RESULTS_TRANSACTION_RATE, &avg);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Transaction rate  : n/a\n");
        }
        else {
            show_results_error(rc, "transaction rate avg");
            return;
        }
    }
    else {

        /*
         * If we get the average, we should be able
         * to get the minimum and maximum too
         */
        rc = CHR_pair_results_get_minimum(handle,
             CHR_RESULTS_TRANSACTION_RATE, &min);
        if (rc != CHR_OK ) {
            show_results_error(rc, "transaction rate min");
            return;
        }
        rc = CHR_pair_results_get_maximum(handle,
             CHR_RESULTS_TRANSACTION_RATE, &max);
        if (rc != CHR_OK ) {
            show_results_error(rc, "transaction rate max");
            return;
        }
        printf("  Transaction rate  :\n");
        printf("    avg %.3f  min %.3f  max %.3f\n",
                    avg, min, max);
    }

    rc = CHR_pair_results_get_average(handle,
        CHR_RESULTS_RESPONSE_TIME, &avg);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Response time     : n/a\n");
        }
        else {
            show_results_error(rc, "response time avg");
            return;
        }
    }
    else {

        rc = CHR_pair_results_get_minimum(handle,
             CHR_RESULTS_RESPONSE_TIME, &min);
        if (rc != CHR_OK ) {
            show_results_error(rc, "response time min");
            return;
        }
        rc = CHR_pair_results_get_maximum(handle,
             CHR_RESULTS_RESPONSE_TIME, &max);
        if (rc != CHR_OK ) {
            show_results_error(rc, "response time max");
            return;
        }
        printf("  Response time     :\n");
        printf("    avg %.5f min %.5f max %.5f\n",
                   avg, min, max);
    }

    rc = CHR_pair_results_get_average(handle,
         CHR_RESULTS_THROUGHPUT, &avg);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Throughput        : n/a\n");
        }
        else {
            show_results_error(rc, "throughput avg");
            return;
        }
    }
    else {

        rc = CHR_pair_results_get_minimum(handle,
             CHR_RESULTS_THROUGHPUT, &min);
        if (rc != CHR_OK ) {
            show_results_error(rc, "throughput min");
            return;
        }
        rc = CHR_pair_results_get_maximum(handle,
             CHR_RESULTS_THROUGHPUT, &max);
        if (rc != CHR_OK ) {
            show_results_error(rc, "throughput max");
            return;
        }
        printf("  Throughput        :\n");
        printf("    avg %.3f   min %.3f   max %.3f\n",
                    avg, min, max);
    }



    rc = CHR_pair_results_get_average(handle,
         CHR_RESULTS_JITTER, &avg);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Jitter            : n/a\n");
        }
        else {
            show_results_error(rc, "jitter avg");
            return;
        }
    }
    else {

        rc = CHR_pair_results_get_minimum(handle,
             CHR_RESULTS_JITTER, &min);
        if (rc != CHR_OK ) {
            show_results_error(rc, "jitter min");
            return;
        }
        rc = CHR_pair_results_get_maximum(handle,
             CHR_RESULTS_JITTER, &max);
        if (rc != CHR_OK ) {
            show_results_error(rc, "jitter max");
            return;
        }
        printf("  Jitter            :\n");
        printf("    avg %.3f   min %.3f   max %.3f\n",
                    avg, min, max);
    }

    /*
     * These do not have NO_SUCH_VALUE as a valid return,
     * so everything other than success is an error.
     */
    /* Please remove this comment if you are not using a VoIPHPP
    rc = CHR_pair_results_get_rel_precision(handle, &result);
    if (rc != CHR_OK ) {
        show_results_error(rc, "rel_precision");
        return;
    }
    printf("  Relative precision: %.3f\n", result);

    rc = CHR_pair_results_get_95pct_confidence(handle, CHR_RESULTS_THROUGHPUT, &result);
    if (rc != CHR_OK) {
        show_results_error(rc, "Throughput 95%% confidence interval");
        return;
    }
    else {
        sprintf(format, "-%.3f / +%.3f", result, result);
        printf("  Throughput 95%% confidence interval       : %s\n", format);
    }
    */

    /*
     * These could have NO_SUCH_VALUE as a valid return,
     * depending on the specifics of the test.
     */
    /* Please remove this comment if you are not using a VoIPHPP
    rc = CHR_pair_results_get_95pct_confidence(handle, CHR_RESULTS_TRANSACTION_RATE, &result);
    if (rc != CHR_OK) {
        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Transaction rate 95%% confidence interval : n/a\n");
        }
        else {
            show_results_error(rc, "Transaction rate 95%% confidence interval");
            return;
        }
    }
    else {
        sprintf(format, "-%.3f / +%.3f", result, result);
        printf("  Transaction rate 95%% confidence interval : %s\n", format);
    }

    rc = CHR_pair_results_get_95pct_confidence(handle, CHR_RESULTS_RESPONSE_TIME, &result);
    if (rc != CHR_OK) {
        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Response time 95%% confidence interval    : n/a\n");
        }
        else {
            show_results_error(rc, "Response time 95%% confidence interval");
            return;
        }
    }
    else {
        sprintf(format, "-%.3f / +%.3f", result, result);
        printf("  Response time 95%% confidence interval    : %s\n", format);
    }

    rc = CHR_pair_results_get_95pct_confidence(handle, CHR_RESULTS_DF, &result);
    if (rc != CHR_OK) {
        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Delay factor 95%% confidence interval     : n/a\n");
        }
        else {
            show_results_error(rc, "Delay factor 95%% confidence interval");
            return;
        }
    }
    else {
        sprintf(format, "-%.3f / +%.3f", result, result);
        printf("  Delay factor 95%% confidence interval     : %s\n", format);
    }

    rc = CHR_pair_results_get_95pct_confidence(handle, CHR_RESULTS_MLR, &result);
    if (rc != CHR_OK) {
        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Media loss rate 95%% confidence interval  : n/a\n");
        }
        else {
            show_results_error(rc, "Media loss rate 95%% confidence interval");
            return;
        }
    }
    else {
        sprintf(format, "-%.3f / +%.3f", result, result);
        printf("  Media loss rate 95%% confidence interval  : %s\n", format);
    }
    */
    /* Show common results */
    show_common(handle);
}