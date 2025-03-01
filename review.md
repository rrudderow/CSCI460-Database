50% multiple choice
    20 questions
50% read/write code (C++ and SQL)
    4-5 questions

First reading and writing files that have binary data
    read and write functions to write some data
    seek and tell functions
        not just <<, >>
        seekg seekp tellg
        seek and tell for getting or putting in the file
        gives us ability to have "random access files"
    struct vs class
        classes usually have functions associated with them - OOP, as opposed to functional programming
        you can use a class like a struct when reading or writing binary until virtual ketword
            becuase virtual adds a pointer to a function that the subclass can overload
        all functions in java are virtual therefore serializable interface to strip function definitions
        Javascript this is the JSON is Javascript objects minus the functions
    struct vs union
        struct is really a memory footprint for a new type
        union makes one memory footprint that contains one or the other type
    Use to make a simple database table of records (relations) 
        we can read and write any element with the same computational effort
    we can make more interesting CS data structures on disk (ex: LL, Arduino, SDCard)
    --in the near future binary/red-black tree, hash table
    Read and write code from this part of class will be in C++

SQL World
    use of a DB management system
    CRUD - 
        create(insert) - insert new record into existing table 
            keywords - insert, into, values
        retrieve(select) - 90% use case for database, browsing storefront for amazon
            select, from, where
            understand column order and selection feature
                select first,last from names;
                select last,first,id from names;
                where clause - this is how I select rows(relations) to return 
                    select first,last from names where last='Castleton';
        update(update) - happens rarely but want quick and easy, likely where clause
            wo a where clause DB damage is likely
            update, set, where +
        delete(delete) - removes record, always has a where clause
            wo a where clause DB damage is likely
            Delete, from, where ++
            no column selector - delete whole row
            alter table
            delete from names where last='Castleton';
    Not CRUD activities (meta data(data about the data) activites)
        create table, create user

Javascript/HTML/CSS Mini App -- Not on the test

