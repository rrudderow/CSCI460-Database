Test 2 on April 9th at 9:00am
    40% multiple choice ~ 20 Questions
    60% will be reading and writing ~ 4 Questions
        fill-in-the-SQL
        C/C++ should be able to write or read
Intent of the test is to cover all new material since the last test
Final is comprehensive
Emphasis:

C/C++ Data file exploration
    binary tree on disk
    seekg/seekp
    read and write functions on file (random access files)
    You have abstract data types - data structures ON DISK very large structures
    Fill in the blank in code or describe what this code is doing
    
SQL stuff
    Select/Insert/Delete/Update
    Create Table
    Indexes
        why is a query doing more work than it needs to?
        why would a query be "slow"?
        select * from table1 join table2 where table1.id=table2.table1_id;
        select * from students join classes where students.id=classes.students_id;
            table1 has a 1000 records
            table2 has a 1000 records
                100,000 records are tested with the where clause
                if instead:
        select * from table1 join table2 on table1.id=table2.table1_id;
            and table2 has a index on table1_id:
                table1 has a 1000 records
                table2 has a 1000 records
                    1000*log(1000) records are tested with the on clause
            on instead of where for joining
            join w/o where = does all combinations
            on = only create where that statement is true
            left join is better
        select * from table1 left join table2 on table1.id=table2.table1_id;
    ---\timing - will show up later - use to improve performance

Web Server
    Lots, Not requiring you to know how to write anything other than the SQL
        implemented CRUD on minimal javascript based web server/client
    HTML, CSS, Javascript - front end - minimal implementation
        HTML = HyperText Markup Language
        HTML described what should be shown/rendered
        CSS = Cascading Style Sheets
        CSS is how it should be shown - color/spacing
        Javascript = make the page interact with the user - button clicks do something
        +++ NO SQL HERE
        --- SQLite can work on the browser client side(front-end)
    Javascript, Node, Express, Postgres - back end
        Node is the virtual OS that our web server runs within (Javascript based)
        Express is a web server written for Node in Javascript
        Javascript is the programming language for this server environment
        Postgres our database to store information in the back-end
            Javascript code calling to postgres - call appropriate query
    +++ commands we used locally where exactly the same as the commands we used on the server
        psql -h ...
        sudo apt install postgres (Ubuntu/Debian based approach)
        all the SQL we used in psql works on a server just as well
        --- punch a hole in your firewall at the house and you can run a web server at home
