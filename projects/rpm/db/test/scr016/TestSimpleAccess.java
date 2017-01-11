/*-
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 1997, 1998, 1999, 2000
 *	Sleepycat Software.  All rights reserved.
 *
 * Id: TestSimpleAccess.java,v 1.2 2001/10/05 02:36:10 bostic Exp 
 */

/*
 * Simple test for get/put of specific values.
 */

package com.sleepycat.test;

import com.sleepycat.db.*;
import java.io.FileNotFoundException;

public class TestSimpleAccess
{
    public static void main(String[] args)
    {
        try {
            Db db = new Db(null, 0);
            db.open("my.db", null, Db.DB_BTREE, Db.DB_CREATE, 0644);

            // populate our massive database.
            Dbt keydbt = new Dbt("key".getBytes());
            Dbt datadbt = new Dbt("data".getBytes());
            db.put(null, keydbt, datadbt, 0);

            // Now, retrieve.  We could use keydbt over again,
            // but that wouldn't be typical in an application.
            Dbt goodkeydbt = new Dbt("key".getBytes());
            Dbt badkeydbt = new Dbt("badkey".getBytes());
            Dbt resultdbt = new Dbt();
            resultdbt.set_flags(Db.DB_DBT_MALLOC);

            int ret;

            if ((ret = db.get(null, goodkeydbt, resultdbt, 0)) != 0) {
                System.out.println("get: " + DbEnv.strerror(ret));
            }
            else {
                String result =
                    new String(resultdbt.get_data(), 0, resultdbt.get_size());
                System.out.println("got data: " + result);
            }

            if ((ret = db.get(null, badkeydbt, resultdbt, 0)) != 0) {
                // We expect this...
                System.out.println("get using bad key: " + DbEnv.strerror(ret));
            }
            else {
                String result =
                    new String(resultdbt.get_data(), 0, resultdbt.get_size());
                System.out.println("*** got data using bad key!!: " + result);
            }
            System.out.println("finished test");
        }
        catch (DbException dbe) {
            System.err.println("Db Exception: " + dbe);
        }
        catch (FileNotFoundException fnfe) {
            System.err.println("FileNotFoundException: " + fnfe);
        }

    }

}
