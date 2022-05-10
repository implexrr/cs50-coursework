/*
In 12.sql, write a SQL query to list the titles of all movies in which both Johnny Depp
and Helena Bonham Carter starred.
Your query should output a table with a single column for the title of each movie.
You may assume that there is only one person in the database with the name Johnny Depp.
You may assume that there is only one person in the database with the name Helena
Bonham Carter.
*/

SELECT m1.title
  FROM movies m1, movies m2
    ON m1.id = m2.id
 WHERE
     (m1.id
               IN
          (SELECT movie_id
             FROM stars
            WHERE person_id
                     IN
                (SELECT id
                   FROM people
                  WHERE name = 'Johnny Depp'
                )
          )
        AND
      m2.id
              IN
            (SELECT movie_id
               FROM stars
              WHERE person_id
                       IN
                  (SELECT id
                     FROM people
                    WHERE name = 'Helena Bonham Carter'
                  )
            )
     );